/*
* $Id: w_customer_address.c,v 1.5 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_customer_address.c,v $
* Revision 1.5  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.4  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.3  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.8  2004/09/24 19:07:07  jms
* Bug #89: add comparability to timezones, remove zip+4, skew cities
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
#include "w_customer_address.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "columns.h"
#include "build_support.h"
#include "print.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_CUSTOMER_ADDRESS_TBL g_w_customer_address;

/*
* mk_customer_address
*/
int
mk_w_customer_address (void* row, ds_key_t index)
{
	
	int res = 0;
	
	/* begin locals declarations */
	struct W_CUSTOMER_ADDRESS_TBL *r;
   tdef *pTdef = getSimpleTdefsByNumber(CUSTOMER_ADDRESS);

	if (row == NULL)
		r = &g_w_customer_address;
	else
		r = row;
	
	nullSet(&pTdef->kNullBitMap, CA_NULLS);
	r->ca_addr_sk = index;
	mk_bkey(&r->ca_addr_id[0], index, CA_ADDRESS_ID);
	pick_distribution (&r->ca_location_type, "location_type", 1, 1, CA_LOCATION_TYPE);
	mk_address(&r->ca_address, CA_ADDRESS);
	
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
pr_w_customer_address(void *row)
{
	struct W_CUSTOMER_ADDRESS_TBL *r;
	char szTemp[128];

	if (row == NULL)
		r = &g_w_customer_address;
	else
		r = row;

	print_start(CUSTOMER_ADDRESS);
	print_key(CA_ADDRESS_SK, r->ca_addr_sk, 1);
	print_varchar(CA_ADDRESS_ID, r->ca_addr_id, 1);
	print_integer(CA_ADDRESS_STREET_NUM, r->ca_address.street_num, 1);
	if (r->ca_address.street_name2)
	{
		sprintf(szTemp, "%s %s", r->ca_address.street_name1, r->ca_address.street_name2);
		print_varchar(CA_ADDRESS_STREET_NAME1, szTemp, 1);
	}
	else
		print_varchar(CA_ADDRESS_STREET_NAME1, r->ca_address.street_name1, 1);
	print_varchar(CA_ADDRESS_STREET_TYPE, r->ca_address.street_type, 1);
	print_varchar(CA_ADDRESS_SUITE_NUM, &r->ca_address.suite_num[0], 1);
	print_varchar(CA_ADDRESS_CITY, r->ca_address.city, 1);
	print_varchar(CA_ADDRESS_COUNTY, r->ca_address.county, 1);
	print_varchar(CA_ADDRESS_STATE, r->ca_address.state, 1);
	sprintf(szTemp, "%05d", r->ca_address.zip);
	print_varchar(CA_ADDRESS_ZIP, szTemp, 1);
	print_varchar(CA_ADDRESS_COUNTRY, &r->ca_address.country[0], 1);
	print_integer(CA_ADDRESS_GMT_OFFSET, r->ca_address.gmt_offset, 1);
	print_varchar(CA_LOCATION_TYPE, r->ca_location_type, 0);
	print_end(CUSTOMER_ADDRESS);

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
ld_w_customer_address(void *row)
{
	struct W_CUSTOMER_ADDRESS_TBL *r;

	if (row == NULL)
		r = &g_w_customer_address;
	else
		r = row;

	return(0);
}

