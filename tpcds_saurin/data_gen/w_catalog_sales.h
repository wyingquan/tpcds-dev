/*
* $Id: w_catalog_sales.h,v 1.3 2007/07/27 22:05:18 jms Exp $
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
* $Log: w_catalog_sales.h,v $
* Revision 1.3  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
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
#ifndef W_CATALOG_SALES_H
#define W_CATALOG_SALES_H

#include "pricing.h"

/*
 * CATALOG_SALES table structure 
 */
struct W_CATALOG_SALES_TBL {
	ds_key_t	cs_sold_date_sk;
	ds_key_t	cs_sold_time_sk;
	ds_key_t	cs_ship_date_sk;
	ds_key_t	cs_bill_customer_sk;
	ds_key_t	cs_bill_cdemo_sk;
	ds_key_t	cs_bill_hdemo_sk;
	ds_key_t	cs_bill_addr_sk;
	ds_key_t	cs_ship_customer_sk;
	ds_key_t	cs_ship_cdemo_sk;
	ds_key_t	cs_ship_hdemo_sk;
	ds_key_t	cs_ship_addr_sk;
	ds_key_t	cs_call_center_sk;
	ds_key_t	cs_catalog_page_sk;
	ds_key_t	cs_ship_mode_sk;
	ds_key_t	cs_warehouse_sk;
	ds_key_t	cs_sold_item_sk;
	ds_key_t	cs_promo_sk;
	ds_key_t	cs_order_number;
	ds_pricing_t	cs_pricing;
};

int mk_w_catalog_sales(void *row, ds_key_t index);
int pr_w_catalog_sales(void *r);
int ld_w_catalog_sales(void *r);
int vld_w_catalog_sales(int nTable, ds_key_t kRow, int *Permutation);
#endif

