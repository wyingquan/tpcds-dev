/*
* $Id: w_store.c,v 1.24 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_store.c,v $
* Revision 1.24  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.23  2007/07/10 18:16:42  jms
* correct SCD seeding
*
* Revision 1.22  2007/02/03 00:32:52  jms
* Bug 520: update RNG usage for smaller tables to correct -validate
*
* Revision 1.21  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.20  2006/08/29 18:03:39  jms
* bug 351
*
* Revision 1.19  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.18  2006/08/28 21:53:30  jms
* Bug 484: remove htonl call since changeSCD now uses arithmetic
*
* Revision 1.17  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.16  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.15  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.14  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.13  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.12  2006/04/27 18:40:34  jms
* Bug #433: improper NULL handling for s_store_close_date_id
*
* Revision 1.11  2006/03/09 19:41:18  jms
* Bug 405: s_tax_percentage not being generated
*
* Revision 1.10  2006/02/10 22:43:57  jms
* Bug 336: use SCD functions on address components
*
* Revision 1.9  2006/02/10 00:57:47  jms
* Bug 336: use SCD functions on address components
*
* Revision 1.8  2005/10/31 19:29:37  jms
* changes to the source schema to move the views forward
*
* Revision 1.7  2005/10/06 22:11:02  jms
* correct a typo
*
* Revision 1.6  2005/10/05 22:35:11  jms
* revert to print_date for dates not linked to date_dim
*
* Revision 1.5  2005/04/12 22:06:25  jms
* fix invalid declaration
*
* Revision 1.4  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.3  2004/11/26 16:23:11  jms
* correct call to dist_op()
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.13  2004/09/24 19:07:07  jms
* Bug #89: add comparability to timezones, remove zip+4, skew cities
*
* Revision 1.12  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.11  2004/08/13 21:52:42  jms
* porting changes for HP/UX
*
* Revision 1.10  2004/08/13 21:48:51  jms
* porting changes for HP/UX
*
* Revision 1.9  2004/08/13 21:10:08  jms
* include <sys/byteorder.h> for SOLARIS
*
* Revision 1.8  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.7.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.7.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.7  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.6  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.5  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.4  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.3  2004/03/26 22:09:05  jms
* change genrand_address to mk_address
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
#include "w_store.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "tables.h"
#include "scaling.h"
#include "nulls.h"
#include "tdefs.h"
#include "scd.h"

struct W_STORE_TBL g_w_store;
static struct W_STORE_TBL g_OldValues;

/*
* mk_store
*/
int
mk_w_store (void* row, ds_key_t index)
{
	int32_t res = 0,
		nFieldChangeFlags,
		bFirstRecord = 0;
	
	/* begin locals declarations */
	static decimal_t dRevMin,
		dRevMax;
	char *sName1,
		*sName2,
		*szTemp;
	int32_t nHierarchyTotal,
		nStoreType,
		nPercentage,
		nDaysOpen,
		nMin,
		nMax;
	static date_t *tDate;
	static decimal_t min_rev_growth,
		max_rev_growth,
		dMinTaxPercentage,
		dMaxTaxPercentage;
	static int32_t bInit = 0;
	struct W_STORE_TBL *r,
		*rOldValues = &g_OldValues;
   tdef *pT = getSimpleTdefsByNumber(STORE);

	if (row == NULL)
		r = &g_w_store;
	else
		r = row;
	
	
if (!bInit)
	{
        nHierarchyTotal = (int) get_rowcount (DIVISIONS);
        nHierarchyTotal *= (int) get_rowcount (COMPANY);
        tDate = strtodate (DATE_MINIMUM);
        strtodec (&min_rev_growth, STORE_MIN_REV_GROWTH);
        strtodec (&max_rev_growth, STORE_MAX_REV_GROWTH);
        strtodec (&dRevMin, "1.00");
        strtodec (&dRevMax, "1000000.00");
        strtodec (&dMinTaxPercentage, STORE_MIN_TAX_PERCENTAGE);
        strtodec (&dMaxTaxPercentage, STORE_MAX_TAX_PERCENTAGE);
				
		/* columns that should be dynamic */
		r->rec_end_date_id = -1;
    }
	
	nullSet(&pT->kNullBitMap, W_STORE_NULLS);
	r->store_sk = index;

	/* if we have generated the required history for this business key and generate a new one 
	 * then reset associate fields (e.g., rec_start_date minimums)
	 */
	if (setSCDKeys(S_STORE_ID, index, r->store_id, &r->rec_start_date_id, &r->rec_end_date_id))
	{
		bFirstRecord = 1;
	}
	
 /*
  * this is  where we select the random number that controls if a field changes from 
  * one record to the next.
  */
	nFieldChangeFlags = next_random(W_STORE_SCD);


	/* the rest of the record in a history-keeping dimension can either be a new data value or not;
	 * use a random number and its bit pattern to determine which fields to replace and which to retain
	 */	
	nPercentage = genrand_integer (NULL, DIST_UNIFORM, 1, 100, 0, W_STORE_CLOSED_DATE_ID);
	nDaysOpen =
		genrand_integer (NULL, DIST_UNIFORM, STORE_MIN_DAYS_OPEN, STORE_MAX_DAYS_OPEN, 0,
		W_STORE_CLOSED_DATE_ID);
	if (nPercentage < STORE_CLOSED_PCT)
		r->closed_date_id = tDate->julian + nDaysOpen;
	else
		r->closed_date_id = -1;
	changeSCD(SCD_KEY, &r->closed_date_id, &rOldValues->closed_date_id,  &nFieldChangeFlags,  bFirstRecord);
   if (!r->closed_date_id)
      r->closed_date_id = -1; /* dates use a special NULL indicator */

	mk_word (r->store_name, "syllables", (long)index, 5, W_STORE_NAME);
	changeSCD(SCD_CHAR, &r->store_name, &rOldValues->store_name,  &nFieldChangeFlags,  bFirstRecord);
	
	/*
    * use the store type to set the parameters for the rest of the attributes
    */
	nStoreType = pick_distribution (&szTemp, "store_type", 1, 1, W_STORE_TYPE);
	dist_member (&nMin, "store_type", nStoreType, 2);
	dist_member (&nMax, "store_type", nStoreType, 3);
	genrand_integer (&r->employees, DIST_UNIFORM, nMin, nMax, 0, W_STORE_EMPLOYEES);
	changeSCD(SCD_INT, &r->employees, &rOldValues->employees,  &nFieldChangeFlags,  bFirstRecord);

	dist_member (&nMin, "store_type", nStoreType, 4);
	dist_member (&nMax, "store_type", nStoreType, 5),
	genrand_integer (&r->floor_space, DIST_UNIFORM, nMin, nMax, 0, W_STORE_FLOOR_SPACE);
	changeSCD(SCD_INT, &r->floor_space, &rOldValues->floor_space,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->hours, "call_center_hours", 1, 1, W_STORE_HOURS);
	changeSCD(SCD_PTR, &r->hours, &rOldValues->hours,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&sName1, "first_names", 1, 1, W_STORE_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, W_STORE_MANAGER);
	sprintf (r->store_manager, "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->store_manager, &rOldValues->store_manager,  &nFieldChangeFlags,  bFirstRecord);

	r->market_id = genrand_integer (NULL, DIST_UNIFORM, 1, 10, 0, W_STORE_MARKET_ID);
	changeSCD(SCD_INT, &r->market_id, &rOldValues->market_id,  &nFieldChangeFlags,  bFirstRecord);

	genrand_decimal(&r->dTaxPercentage ,DIST_UNIFORM, &dMinTaxPercentage, &dMaxTaxPercentage, NULL, W_STORE_TAX_PERCENTAGE);
	changeSCD(SCD_DEC, &r->dTaxPercentage, &rOldValues->dTaxPercentage,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->geography_class, "geography_class", 1, 1, W_STORE_GEOGRAPHY_CLASS);
	changeSCD(SCD_PTR, &r->geography_class, &rOldValues->geography_class,  &nFieldChangeFlags,  bFirstRecord);

	gen_text (&r->market_desc[0], STORE_DESC_MIN, RS_S_MARKET_DESC, W_STORE_MARKET_DESC);
	changeSCD(SCD_CHAR, &r->market_desc, &rOldValues->market_desc,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&sName1, "first_names", 1, 1, W_STORE_MARKET_MANAGER);
	pick_distribution (&sName2, "last_names", 1, 1, W_STORE_MARKET_MANAGER);
	sprintf (r->market_manager, "%s %s", sName1, sName2);
	changeSCD(SCD_CHAR, &r->market_manager, &rOldValues->market_manager,  &nFieldChangeFlags,  bFirstRecord);

	r->division_id =
		pick_distribution (&r->division_name, "divisions", 1, 1, W_STORE_DIVISION_NAME);
	changeSCD(SCD_KEY, &r->division_id, &rOldValues->division_id,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->division_name, &rOldValues->division_name,  &nFieldChangeFlags,  bFirstRecord);

	r->company_id =
		pick_distribution (&r->company_name, "stores", 1, 1, W_STORE_COMPANY_NAME);
	changeSCD(SCD_KEY, &r->company_id, &rOldValues->company_id,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->company_name, &rOldValues->company_name,  &nFieldChangeFlags,  bFirstRecord);

	mk_address(&r->address, W_STORE_ADDRESS);
	changeSCD(SCD_PTR, &r->address.city, &rOldValues->address.city,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->address.county, &rOldValues->address.county,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->address.gmt_offset, &rOldValues->address.gmt_offset,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->address.state, &rOldValues->address.state,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->address.street_type, &rOldValues->address.street_type,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->address.street_name1, &rOldValues->address.street_name1,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_PTR, &r->address.street_name2, &rOldValues->address.street_name2,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->address.street_num, &rOldValues->address.street_num,  &nFieldChangeFlags,  bFirstRecord);
	changeSCD(SCD_INT, &r->address.zip, &rOldValues->address.zip,  &nFieldChangeFlags,  bFirstRecord);

	
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
pr_w_store(void *row)
{
	struct W_STORE_TBL *r;
	char szTemp[128];

	if (row == NULL)
		r = &g_w_store;
	else
		r = row;

	print_start(STORE);
	print_key(W_STORE_SK, r->store_sk, 1);
	print_varchar(W_STORE_ID, r->store_id, 1);
	print_date(W_STORE_REC_START_DATE_ID, r->rec_start_date_id, 1);
	print_date(W_STORE_REC_END_DATE_ID, r->rec_end_date_id, 1);
	print_key(W_STORE_CLOSED_DATE_ID, r->closed_date_id, 1);
	print_varchar(W_STORE_NAME, r->store_name, 1);
	print_integer(W_STORE_EMPLOYEES, r->employees, 1);
	print_integer(W_STORE_FLOOR_SPACE, r->floor_space, 1);
	print_varchar(W_STORE_HOURS, r->hours, 1);
	print_varchar(W_STORE_MANAGER, &r->store_manager[0], 1);
	print_integer(W_STORE_MARKET_ID, r->market_id, 1);
	print_varchar(W_STORE_GEOGRAPHY_CLASS, r->geography_class, 1);
	print_varchar(W_STORE_MARKET_DESC, &r->market_desc[0], 1);
	print_varchar(W_STORE_MARKET_MANAGER, &r->market_manager[0], 1);
	print_key(W_STORE_DIVISION_ID, r->division_id, 1);
	print_varchar(W_STORE_DIVISION_NAME, r->division_name, 1);
	print_key(W_STORE_COMPANY_ID, r->company_id, 1);
	print_varchar(W_STORE_COMPANY_NAME, r->company_name, 1);
	print_integer(W_STORE_ADDRESS_STREET_NUM, r->address.street_num, 1);
	if (r->address.street_name2)
	{
		sprintf(szTemp, "%s %s", r->address.street_name1, r->address.street_name2);
		print_varchar(W_STORE_ADDRESS_STREET_NAME1, szTemp, 1);
	}
	else
		print_varchar(W_STORE_ADDRESS_STREET_NAME1, r->address.street_name1, 1);
	print_varchar(W_STORE_ADDRESS_STREET_TYPE, r->address.street_type, 1);
	print_varchar(W_STORE_ADDRESS_SUITE_NUM, r->address.suite_num, 1);
	print_varchar(W_STORE_ADDRESS_CITY, r->address.city, 1);
	print_varchar(W_STORE_ADDRESS_COUNTY, r->address.county, 1);
	print_varchar(W_STORE_ADDRESS_STATE, r->address.state, 1);
	sprintf(szTemp, "%05d", r->address.zip);
	print_varchar(W_STORE_ADDRESS_ZIP, szTemp, 1);
	print_varchar(W_STORE_ADDRESS_COUNTRY, r->address.country, 1);
	print_integer(W_STORE_ADDRESS_GMT_OFFSET, r->address.gmt_offset, 1);
   print_decimal(W_STORE_TAX_PERCENTAGE,&r->dTaxPercentage, 0);
	print_end(STORE);
	
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
ld_w_store(void *pSrc)
{
	struct W_STORE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_store;
	else
		r = pSrc;
	
	return(0);
}

