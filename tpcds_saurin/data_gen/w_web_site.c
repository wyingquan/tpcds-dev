/*
* $Id: w_web_site.c,v 1.18 2007/08/02 18:56:31 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 1997 - 2001
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: w_web_site.c,v $
* Revision 1.18  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.17  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.16  2006/08/29 18:03:39  jms
* bug 351
*
* Revision 1.15  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.14  2006/08/28 21:53:30  jms
* Bug 484: remove htonl call since changeSCD now uses arithmetic
*
* Revision 1.13  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.12  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.11  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.10  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.9  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.8  2006/02/10 22:46:20  jms
* Bug 336: use SCD functions on address components
*
* Revision 1.7  2006/02/10 17:15:52  jms
* Bug 336: use SCD functions on address components
*
* Revision 1.6  2006/02/10 00:57:47  jms
* Bug 336: use SCD functions on address components
*
* Revision 1.5  2005/11/06 22:01:13  jms
* first rework of source generation
*
* Revision 1.4  2005/03/16 00:04:05  jms
* null-related linkage bugs
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.16  2004/09/24 19:07:07  jms
* Bug #89: add comparability to timezones, remove zip+4, skew cities
*
* Revision 1.15  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.14  2004/08/13 21:52:42  jms
* porting changes for HP/UX
*
* Revision 1.13  2004/08/13 21:48:51  jms
* porting changes for HP/UX
*
* Revision 1.12  2004/08/13 21:10:08  jms
* include <sys/byteorder.h> for SOLARIS
*
* Revision 1.11  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.10.2.3  2004/08/06 17:19:55  jms
* Convert open/close to date keys rather than ASCII dates
*
* Revision 1.10.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.10.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.10  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.9  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.8  2004/06/02 17:21:14  jms
* Bug #72: web.web_site_sk not unique
*
* Revision 1.7  2004/05/26 21:31:19  jms
* sync address elements, ordering (Bug #67, 69, 70, 71)
*
* Revision 1.6  2004/05/21 23:49:44  jms
* correct field order for address
*
* Revision 1.5  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.4  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
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
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifdef NCR
#include <sys/types.h>
#endif
#ifndef WIN32
#include <netinet/in.h>
#endif
#include "constants.h"
#include "address.h"
#include "w_web_site.h"
#include "genrand.h"
#include "tables.h"
#include "columns.h"
#include "print.h"
#include "scaling.h"
#include "build_support.h"
#include "misc.h"
#include "nulls.h"
#include "tdefs.h"
#include "scd.h"

struct W_WEB_SITE_TBL g_w_web_site;
static struct W_WEB_SITE_TBL g_OldValues;

/*
* Routine: mk_web_site()
* Purpose: populate the web_site table
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
*/
int
mk_w_web_site (void *row, ds_key_t index)
{
	int32_t res = 0,
		nFieldChangeFlags,
		bFirstRecord = 0;
	static date_t *dToday;
	static decimal_t dMinTaxPercentage,
		dMaxTaxPercentage;
	static int32_t bInit = 0;

	/* begin locals declarations */
	char szTemp[16],
		*sName1,
		*sName2;
	struct W_WEB_SITE_TBL *r,
				*rOldValues = &g_OldValues;
   tdef *pT = getSimpleTdefsByNumber(WEB_SITE);
	
	if (row == NULL)
		r = &g_w_web_site;
	else
		r = row;

	if (!bInit)
	{
		/* setup invariant values */
		sprintf(szTemp, "%d-%d-%d", CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
		dToday = strtodate(szTemp);
		strcpy(r->web_class, "Unknown");
		strtodec(&dMinTaxPercentage, WEB_MIN_TAX_PERCENTAGE);
		strtodec(&dMaxTaxPercentage, WEB_MAX_TAX_PERCENTAGE);

		bInit = 1;
	}

	nullSet(&pT->kNullBitMap, WEB_NULLS);
	r->web_site_sk = index;

	/* if we have generated the required history for this business key and generate a new one 
	 * then reset associate fields (e.g., rec_start_date minimums)
	 */
	if (setSCDKeys(WEB_SITE_ID, index, r->web_site_id, &r->web_rec_start_date_id, &r->web_rec_end_date_id))
	{
		r->web_open_date = mk_join(WEB_OPEN_DATE, DATE, index);
		r->web_close_date = mk_join(WEB_CLOSE_DATE, DATE, index);
	if (r->web_close_date > r->web_rec_end_date_id)
		r->web_close_date = -1;
		sprintf(r->web_name, "site_%d", (int)(index / 6));
		bFirstRecord = 1;
	}
	
 /*
  * this is  where we select the random number that controls if a field changes from 
  * one record to the next.
  */
	nFieldChangeFlags = next_random(WEB_SCD);


	/* the rest of the record in a history-keeping dimension can either be a new data value or not;
	 * use a random number and its bit pattern to determine which fields to replace and which to retain
	 */	
	pick_distribution (&sName1, "first_names", 1, 1, WEB_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, WEB_MANAGER);
	sprintf (r->web_manager, "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->web_manager, &rOldValues->web_manager,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->web_market_id, DIST_UNIFORM, 1, 6, 0, WEB_MARKET_ID);
	changeSCD(SCD_INT, &r->web_market_id, &rOldValues->web_market_id,  &nFieldChangeFlags,  bFirstRecord);

	gen_text (r->web_market_class, 20, RS_WEB_MARKET_CLASS,
		WEB_MARKET_CLASS);
	changeSCD(SCD_CHAR, &r->web_market_class, &rOldValues->web_market_class,  &nFieldChangeFlags,  bFirstRecord);

	gen_text (r->web_market_desc, 20, RS_WEB_MARKET_DESC,
		WEB_MARKET_DESC);
	changeSCD(SCD_CHAR, &r->web_market_desc, &rOldValues->web_market_desc,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&sName1, "first_names", 1, 1, WEB_MARKET_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, WEB_MARKET_MANAGER);
	sprintf (r->web_market_manager, "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->web_market_manager, &rOldValues->web_market_manager,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer (&r->web_company_id, DIST_UNIFORM, 1, 6, 0, 
		WEB_COMPANY_ID);
	changeSCD(SCD_INT, &r->web_company_id, &rOldValues->web_company_id,  &nFieldChangeFlags,  bFirstRecord);

	mk_word(r->web_company_name, "Syllables", r->web_company_id, RS_WEB_COMPANY_NAME, WEB_COMPANY_NAME);
	changeSCD(SCD_CHAR, &r->web_company_name, &rOldValues->web_company_name,  &nFieldChangeFlags,  bFirstRecord);

	mk_address(&r->web_address, WEB_ADDRESS);
	changeSCD(SCD_PTR, &r->web_address.city, &rOldValues->web_address.city,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->web_address.county, &rOldValues->web_address.county,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->web_address.gmt_offset, &rOldValues->web_address.gmt_offset,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->web_address.state, &rOldValues->web_address.state,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->web_address.street_type, &rOldValues->web_address.street_type,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->web_address.street_name1, &rOldValues->web_address.street_name1,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->web_address.street_name2, &rOldValues->web_address.street_name2,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->web_address.street_num, &rOldValues->web_address.street_num,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->web_address.zip, &rOldValues->web_address.zip,  &nFieldChangeFlags,  bFirstRecord);

	genrand_decimal(&r->web_tax_percentage, DIST_UNIFORM, &dMinTaxPercentage, &dMaxTaxPercentage, NULL, WEB_TAX_PERCENTAGE);
	changeSCD(SCD_DEC, &r->web_tax_percentage, &rOldValues->web_tax_percentage,  &nFieldChangeFlags,  bFirstRecord);

	
	return(res);
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
pr_w_web_site(void *row)
{
	struct W_WEB_SITE_TBL *r;
	char szStreetName[128];

		
	if (row == NULL)
		r = &g_w_web_site;
	else
		r = row;

	print_start(WEB_SITE);
	print_key(WEB_SITE_SK, r->web_site_sk, 1);
	print_varchar(WEB_SITE_ID, &r->web_site_id[0], 1);
	print_date(WEB_REC_START_DATE_ID, (int)r->web_rec_start_date_id, 1);
	print_date(WEB_REC_END_DATE_ID, (int)r->web_rec_end_date_id, 1);
	print_varchar(WEB_NAME, &r->web_name[0], 1);
	print_key(WEB_OPEN_DATE, r->web_open_date, 1);
	print_key(WEB_CLOSE_DATE, r->web_close_date, 1);
	print_varchar(WEB_CLASS, &r->web_class[0], 1);
	print_varchar(WEB_MANAGER, &r->web_manager[0], 1);
	print_integer(WEB_MARKET_ID, r->web_market_id, 1);
	print_varchar(WEB_MARKET_CLASS, &r->web_market_class[0], 1);
	print_varchar(WEB_MARKET_DESC, &r->web_market_desc[0], 1);
	print_varchar(WEB_MARKET_MANAGER, &r->web_market_manager[0], 1);
	print_integer(WEB_COMPANY_ID, r->web_company_id, 1);
	print_varchar(WEB_COMPANY_NAME, &r->web_company_name[0], 1);
	print_integer(WEB_ADDRESS_STREET_NUM, r->web_address.street_num, 1);
	if (r->web_address.street_name2)
	{
		sprintf(szStreetName, "%s %s", r->web_address.street_name1, r->web_address.street_name2);
		print_varchar(WEB_ADDRESS_STREET_NAME1, szStreetName, 1);
	}
	else
		print_varchar(WEB_ADDRESS_STREET_NAME1, r->web_address.street_name1, 1);
	print_varchar(WEB_ADDRESS_STREET_TYPE, r->web_address.street_type, 1);
	print_varchar(WEB_ADDRESS_SUITE_NUM, r->web_address.suite_num, 1);
	print_varchar(WEB_ADDRESS_CITY, r->web_address.city, 1);
	print_varchar(WEB_ADDRESS_COUNTY, r->web_address.county, 1);
	print_varchar(WEB_ADDRESS_STATE, r->web_address.state, 1);
	sprintf(szStreetName, "%05d", r->web_address.zip);
	print_varchar(WEB_ADDRESS_ZIP, szStreetName, 1);
	print_varchar(WEB_ADDRESS_COUNTRY, r->web_address.country, 1);
	print_integer(WEB_ADDRESS_GMT_OFFSET, r->web_address.gmt_offset, 1);
	print_decimal(WEB_TAX_PERCENTAGE, &r->web_tax_percentage, 0);
	print_end(WEB_SITE);

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
ld_w_web_site(void *pSrc)
{
	struct W_WEB_SITE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_web_site;
	else
		r = pSrc;
	
	return(0);
}

