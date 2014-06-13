/*
* $Id: w_warehouse.c,v 1.7 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_warehouse.c,v $
* Revision 1.7  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.6  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.5  2007/02/03 00:32:52  jms
* Bug 520: update RNG usage for smaller tables to correct -validate
*
* Revision 1.4  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.3  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.7  2004/09/24 19:07:07  jms
* Bug #89: add comparability to timezones, remove zip+4, skew cities
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
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
#include "constants.h"
#include "w_warehouse.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "address.h"
#include "constants.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_WAREHOUSE_TBL g_w_warehouse;

/*
* mk_warehouse
*/
int
mk_w_warehouse (void* row, ds_key_t index)
{
	int res = 0;
	
	/* begin locals declarations */
	struct W_WAREHOUSE_TBL *r;
   tdef *pT = getSimpleTdefsByNumber(WAREHOUSE);

	if (row == NULL)
		r = &g_w_warehouse;
	else
		r = row;
	
	
	nullSet(&pT->kNullBitMap, W_NULLS);
	r->w_warehouse_sk = index;
	mk_bkey(&r->w_warehouse_id[0], index, W_WAREHOUSE_ID);
	gen_text (&r->w_warehouse_name[0], W_NAME_MIN,
		RS_W_WAREHOUSE_NAME, W_WAREHOUSE_NAME);
	r->w_warehouse_sq_ft =
		genrand_integer (NULL, DIST_UNIFORM,
		W_SQFT_MIN, W_SQFT_MAX, 0, W_WAREHOUSE_SQ_FT);

	mk_address(&r->w_address, W_WAREHOUSE_ADDRESS);
	
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
pr_w_warehouse(void *row)
{
	struct W_WAREHOUSE_TBL *r;
	char szTemp[128];

	if (row == NULL)
		r = &g_w_warehouse;
	else
		r = row;

	print_start(WAREHOUSE);
	print_key(W_WAREHOUSE_SK, r->w_warehouse_sk, 1);
	print_varchar(W_WAREHOUSE_ID, r->w_warehouse_id, 1);
	print_varchar(W_WAREHOUSE_NAME, &r->w_warehouse_name[0], 1);
	print_integer(W_WAREHOUSE_SQ_FT, r->w_warehouse_sq_ft, 1);
	print_integer(W_ADDRESS_STREET_NUM, r->w_address.street_num, 1);
	if (r->w_address.street_name2 != NULL)
	{
		sprintf(szTemp, "%s %s", r->w_address.street_name1, r->w_address.street_name2);
		print_varchar(W_ADDRESS_STREET_NAME1, szTemp, 1);
	}
	else
		print_varchar(W_ADDRESS_STREET_NAME1, r->w_address.street_name1, 1);
	print_varchar(W_ADDRESS_STREET_TYPE, r->w_address.street_type, 1);
	print_varchar(W_ADDRESS_SUITE_NUM, r->w_address.suite_num, 1);
	print_varchar(W_ADDRESS_CITY, r->w_address.city, 1);
	print_varchar(W_ADDRESS_COUNTY, r->w_address.county, 1);
	print_varchar(W_ADDRESS_STATE, r->w_address.state, 1);
	sprintf(szTemp, "%05d", r->w_address.zip);
	print_varchar(W_ADDRESS_ZIP, szTemp, 1);
	print_varchar(W_ADDRESS_COUNTRY, r->w_address.country, 1);
	print_integer(W_ADDRESS_GMT_OFFSET, r->w_address.gmt_offset, 0);
	print_end(WAREHOUSE);

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
ld_w_warehouse(void *pSrc)
{
	struct W_WAREHOUSE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_warehouse;
	else
		r = pSrc;
	
	return(0);
}

