/*
* $Id: s_customer_address.c,v 1.8 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_customer_address.c,v $
* Revision 1.8  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.7  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.6  2007/07/24 20:06:13  jms
* bug 546: s_customer_address
*
* Revision 1.5  2007/07/10 18:49:29  jms
* validate s_customer_address
*
* Revision 1.4  2006/08/17 20:44:24  jms
* Bug 482
*
* Revision 1.3  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.2  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.1  2006/03/17 20:24:19  jms
* rename of s_business_address to align with spec
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "w_customer_address.h"
#include "s_customer_address.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "columns.h"
#include "build_support.h"
#include "print.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"
#include "tdef_functions.h"

extern struct W_CUSTOMER_ADDRESS_TBL g_w_customer_address;

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
pr_s_customer_address(void *row)
{
	struct W_CUSTOMER_ADDRESS_TBL *r;
   char szTemp[11];

   if (row == NULL)
		r = &g_w_customer_address;
	else
		r = row;

	print_start(S_CUSTOMER_ADDRESS);
	print_varchar(S_CADR_ID, r->ca_addr_id, 1);
	print_integer(S_CADR_ADDRESS_STREET_NUMBER, r->ca_address.street_num, 1);
	print_varchar(S_CADR_ADDRESS_STREET_NAME1, r->ca_address.street_name1, 1);
	print_varchar(S_CADR_ADDRESS_STREET_NAME2, r->ca_address.street_name2, 1);
	print_varchar(S_CADR_ADDRESS_STREET_TYPE, r->ca_address.street_type, 1);
	print_varchar(S_CADR_ADDRESS_SUITE_NUM, &r->ca_address.suite_num[0], 1);
	print_varchar(S_CADR_ADDRESS_CITY, r->ca_address.city, 1);
	print_varchar(S_CADR_ADDRESS_COUNTY, r->ca_address.county, 1);
	print_varchar(S_CADR_ADDRESS_STATE, r->ca_address.state, 1);
	sprintf(szTemp, "%05d", r->ca_address.zip);
	print_varchar(S_CADR_ADDRESS_ZIP, szTemp, 1);
	print_varchar(S_CADR_ADDRESS_COUNTRY, &r->ca_address.country[0], 0);
	print_end(S_CUSTOMER_ADDRESS);

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
ld_s_customer_address(void *row)
{
	struct W_CUSTOMER_ADDRESS_TBL *r;

	if (row == NULL)
		r = &g_w_customer_address;
	else
		r = row;

	return(0);
}

int
vld_s_customer_address(int nTable, ds_key_t kRow, int *Permutation)
{
   return(validateGeneric(S_CUSTOMER_ADDRESS, kRow, Permutation));
}
