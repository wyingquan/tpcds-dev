/*
* $Id: w_call_center.c,v 1.16 2007/08/02 18:56:30 jms Exp $
*
* This software contains proprietary and confidential information of Gradient
* Systems Inc.  By accepting transfer of this copy, Recipient agrees
* to retain this software in confidence, to prevent disclosure to others, and
* to make no use of this software other than that for which it was delivered.
* This is an unpublished copyright work Gradient Systems, Inc.  Execpt as
* permitted by federal law, 17 USC 117, copying is strictly prohibited.
*
* Gradient Systems Inc. CONFIDENTIAL - (Gradient Systems Inc. Confidential
* when combined with the aggregated modules for this product)
* OBJECT CODE ONLY SOURCE MATERIALS
* (C) COPYRIGHT Gradient Systems Inc. 2003
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: w_call_center.c,v $
* Revision 1.16  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.15  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.14  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.13  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.12  2006/08/28 21:53:30  jms
* Bug 484: remove htonl call since changeSCD now uses arithmetic
*
* Revision 1.11  2006/08/23 23:51:02  jms
* Bug 485: inventory on Thursdays
*
* Revision 1.10  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.9  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.8  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.7  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.6  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.5  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2005/11/11 21:58:01  jms
* add tax percentages to all channels in both warehouse and source schemae
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.14  2004/09/24 19:07:07  jms
* Bug #89: add comparability to timezones, remove zip+4, skew cities
*
* Revision 1.13  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.12  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.11.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.11.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.11  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.10  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.9  2004/05/26 21:31:19  jms
* sync address elements, ordering (Bug #67, 69, 70, 71)
*
* Revision 1.8  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.7  2004/04/08 06:07:25  jms
* bug #57: call center sk is always 0
*
* Revision 1.6  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.5  2004/03/26 23:03:36  jms
* AIX porting changes
*
* Revision 1.4  2004/03/26 22:06:39  jms
* add ntohl headers
*
* Revision 1.3  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <assert.h>
#ifdef NCR
#include <sys/types.h>
#endif
#ifndef WIN32
#include <netinet/in.h>
#endif
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include "w_call_center.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "r_params.h"
#include "scaling.h"
#include "columns.h"
#include "tables.h"
#include "misc.h"
#include "dist.h"
#include "build_support.h"
#include "print.h"
#include "tdefs.h"
#include "nulls.h"
#include "scd.h"

struct CALL_CENTER_TBL g_w_call_center;
static struct CALL_CENTER_TBL g_OldValues;

/*
* Routine: mk_w_call_center()
* Purpose: 
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
* 20020830 jms Need to populate open and close dates
*/
int
mk_w_call_center (void* row, ds_key_t index)
{
	int32_t res = 0;
	static int32_t jDateStart,
		nDaysPerRevision;
	int32_t nSuffix,
		bFirstRecord = 0,
		nFieldChangeFlags,
		jDateEnd,
		nDateRange;
	char *cp,
		*sName1,
		*sName2;
	static decimal_t dMinTaxPercentage, dMaxTaxPercentage;
   tdef *pTdef = getSimpleTdefsByNumber(CALL_CENTER);

	/* begin locals declarations */
	date_t dTemp;
	static int bInit = 0,
		nScale;
	struct CALL_CENTER_TBL *r,
		*rOldValues = &g_OldValues;

	if (row == NULL)
		r = &g_w_call_center;
	else
		r = row;

	if (!bInit)
	{
        /* begin locals allocation/initialization */
		strtodt(&dTemp, DATA_START_DATE);
		jDateStart = dttoj(&dTemp) - WEB_SITE;
		strtodt(&dTemp, DATA_END_DATE);
		jDateEnd = dttoj(&dTemp);
		nDateRange = jDateEnd - jDateStart + 1; 
		nDaysPerRevision = nDateRange / pTdef->nParam + 1;
		nScale = get_int("SCALE");
		
		/* these fields need to be handled as part of SCD code or further definition */
		r->cc_division_id = -1;
		r->cc_closed_date_id = -1;
		strcpy(r->cc_division_name, "No Name");

		strtodec(&dMinTaxPercentage, MIN_CC_TAX_PERCENTAGE);
		strtodec(&dMaxTaxPercentage, MAX_CC_TAX_PERCENTAGE);
      bInit = 1;
	}
	
	nullSet(&pTdef->kNullBitMap, CC_NULLS);
	r->cc_call_center_sk = index;

	/* if we have generated the required history for this business key and generate a new one 
	 * then reset associate fields (e.g., rec_start_date minimums)
	 */
	if (setSCDKeys(CC_CALL_CENTER_ID, index, r->cc_call_center_id, &r->cc_rec_start_date_id, &r->cc_rec_end_date_id))
	{
		r->cc_open_date_id = jDateStart 
			- genrand_integer(NULL, DIST_UNIFORM, -365, 0, 0, CC_OPEN_DATE_ID);

/* 
 * some fields are not changed, even when a new version of the row is written 
 */
		nSuffix = (int)index / distsize("call_centers");
		dist_member (&cp, "call_centers", (int) (index % distsize("call_centers")) + 1, 1);
		if (nSuffix > 0)
			sprintf(r->cc_name, "%s_%d", cp, nSuffix);
		else
			strcpy(r->cc_name, cp);
			
		mk_address(&r->cc_address, CC_ADDRESS);
		bFirstRecord = 1;
	}
	
 /*
  * this is  where we select the random number that controls if a field changes from 
  * one record to the next. 
  */
	nFieldChangeFlags = next_random(CC_SCD);


	/* the rest of the record in a history-keeping dimension can either be a new data value or not;
	 * use a random number and its bit pattern to determine which fields to replace and which to retain
	 */
	pick_distribution (&r->cc_class, "call_center_class", 1, 1, CC_CLASS);
	changeSCD(SCD_PTR, &r->cc_class, &rOldValues->cc_class,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->cc_employees, DIST_UNIFORM, 1, CC_EMPLOYEE_MAX * nScale * nScale, 0, CC_EMPLOYEES);
	changeSCD(SCD_INT, &r->cc_employees, &rOldValues->cc_employees,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&r->cc_sq_ft, DIST_UNIFORM, 100, 700, 0, CC_SQ_FT);
	r->cc_sq_ft *= r->cc_employees;
	changeSCD(SCD_INT, &r->cc_sq_ft, &rOldValues->cc_sq_ft,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->cc_hours, "call_center_hours",
		1, 1, CC_HOURS);
	changeSCD(SCD_PTR, &r->cc_hours, &rOldValues->cc_hours,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&sName1, "first_names", 1, 1, CC_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, CC_MANAGER);
	sprintf (&r->cc_manager[0], "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->cc_manager, &rOldValues->cc_manager,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->cc_market_id, DIST_UNIFORM, 1, 6, 0, CC_MARKET_ID);
	changeSCD(SCD_INT, &r->cc_market_id, &rOldValues->cc_market_id,  &nFieldChangeFlags,  bFirstRecord);

	gen_text (r->cc_market_class, 20, RS_CC_MARKET_CLASS, CC_MARKET_CLASS);
	changeSCD(SCD_CHAR, &r->cc_market_class, &rOldValues->cc_market_class,  &nFieldChangeFlags,  bFirstRecord);

	gen_text (r->cc_market_desc, 20, RS_CC_MARKET_DESC, CC_MARKET_DESC);
	changeSCD(SCD_CHAR, &r->cc_market_desc, &rOldValues->cc_market_desc,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&sName1, "first_names", 1, 1, CC_MARKET_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, CC_MARKET_MANAGER);
	sprintf (&r->cc_market_manager[0], "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->cc_market_manager, &rOldValues->cc_market_manager,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->cc_company, DIST_UNIFORM, 1, 6, 0, CC_COMPANY);
	changeSCD(SCD_INT, &r->cc_company, &rOldValues->cc_company,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->cc_division_id, DIST_UNIFORM, 1, 6, 0, CC_COMPANY);
	changeSCD(SCD_INT, &r->cc_division_id, &rOldValues->cc_division_id,  &nFieldChangeFlags,  bFirstRecord);

	mk_word(r->cc_division_name, "syllables", r->cc_division_id, RS_CC_DIVISION_NAME, CC_DIVISION_NAME);
	changeSCD(SCD_CHAR, &r->cc_division_name, &rOldValues->cc_division_name,  &nFieldChangeFlags,  bFirstRecord);
	
	mk_companyname (r->cc_company_name, CC_COMPANY_NAME, r->cc_company);
	changeSCD(SCD_CHAR, &r->cc_company_name, &rOldValues->cc_company_name,  &nFieldChangeFlags,  bFirstRecord);

	genrand_decimal(&r->cc_tax_percentage, DIST_UNIFORM, &dMinTaxPercentage, &dMaxTaxPercentage, NULL, CC_TAX_PERCENTAGE);
	changeSCD(SCD_DEC, &r->cc_tax_percentage, &rOldValues->cc_tax_percentage,  &nFieldChangeFlags,  bFirstRecord);

	return (res);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
int
pr_w_call_center(void *row)
{
	struct CALL_CENTER_TBL *r;
	char szTemp[128];
	
	if (row == NULL)
		r = &g_w_call_center;
	else
		r = row;

	print_start(CALL_CENTER);
	print_key(CC_CALL_CENTER_SK, r->cc_call_center_sk, 1);
	print_varchar(CC_CALL_CENTER_ID, r->cc_call_center_id, 1);
	print_date(CC_REC_START_DATE_ID, r->cc_rec_start_date_id, 1);
	print_date(CC_REC_END_DATE_ID, r->cc_rec_end_date_id, 1);
	print_key(CC_CLOSED_DATE_ID, r->cc_closed_date_id, 1);
	print_key(CC_OPEN_DATE_ID, r->cc_open_date_id, 1);
	print_varchar(CC_NAME, r->cc_name, 1);
	print_varchar(CC_CLASS, &r->cc_class[0], 1);
	print_integer(CC_EMPLOYEES, r->cc_employees, 1);
	print_integer(CC_SQ_FT, r->cc_sq_ft, 1);
	print_varchar(CC_HOURS, r->cc_hours, 1);
	print_varchar(CC_MANAGER, &r->cc_manager[0], 1);
	print_integer(CC_MARKET_ID, r->cc_market_id, 1);
	print_varchar(CC_MARKET_CLASS, &r->cc_market_class[0], 1);
	print_varchar(CC_MARKET_DESC, &r->cc_market_desc[0], 1);
	print_varchar(CC_MARKET_MANAGER, &r->cc_market_manager[0], 1);
	print_integer(CC_DIVISION, r->cc_division_id, 1);
	print_varchar(CC_DIVISION_NAME, &r->cc_division_name[0], 1);
	print_integer(CC_COMPANY, r->cc_company, 1);
	print_varchar(CC_COMPANY_NAME, &r->cc_company_name[0], 1);
	print_integer(CC_ADDRESS, r->cc_address.street_num, 1);
	if (r->cc_address.street_name2)
	{
		sprintf(szTemp, "%s %s", r->cc_address.street_name1, r->cc_address.street_name2);
		print_varchar(CC_ADDRESS, szTemp, 1);
	}
	else
		print_varchar(CC_ADDRESS, r->cc_address.street_name1, 1);
	print_varchar(CC_ADDRESS, r->cc_address.street_type, 1);
	print_varchar(CC_ADDRESS, &r->cc_address.suite_num[0], 1);
	print_varchar(CC_ADDRESS, r->cc_address.city, 1);
	print_varchar(CC_ADDRESS, r->cc_address.county, 1);
	print_varchar(CC_ADDRESS, r->cc_address.state, 1);
	sprintf(szTemp, "%05d", r->cc_address.zip);
	print_varchar(CC_ADDRESS, szTemp, 1);
	print_varchar(CC_ADDRESS, &r->cc_address.country[0], 1);
	print_integer(CC_ADDRESS, r->cc_address.gmt_offset, 1);
	print_decimal(CC_TAX_PERCENTAGE, &r->cc_tax_percentage, 0);
	print_end(CALL_CENTER);

	return(0);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
int
ld_w_call_center(void *r)
{
	return(0);
}

