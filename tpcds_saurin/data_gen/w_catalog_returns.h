/*
* $Id: w_catalog_returns.h,v 1.5 2006/11/14 20:56:09 jms Exp $
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
* $Log: w_catalog_returns.h,v $
* Revision 1.5  2006/11/14 20:56:09  jms
* Bug #516
*
* Revision 1.4  2005/03/04 22:00:44  jms
* update to WAM, removal of sold_date info from returns tables
*
* Revision 1.3  2005/01/28 21:16:12  jms
* add cr_call_center_sk to catalog_returns, taking value from the sale record
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
#ifndef W_CATALOG_RETURNS_H
#define W_CATALOG_RETURNS_H

#include "pricing.h"

/*
 * CATALOG_RETURNS table structure 
 */
struct W_CATALOG_RETURNS_TBL {
	ds_key_t	cr_returned_date_sk;
	ds_key_t	cr_returned_time_sk;
	ds_key_t	cr_item_sk;
	ds_key_t	cr_refunded_customer_sk;
	ds_key_t	cr_refunded_cdemo_sk;
	ds_key_t	cr_refunded_hdemo_sk;
	ds_key_t	cr_refunded_addr_sk;
	ds_key_t	cr_returning_customer_sk;
	ds_key_t	cr_returning_cdemo_sk;
	ds_key_t	cr_returning_hdemo_sk;
	ds_key_t	cr_returning_addr_sk;
	ds_key_t	cr_call_center_sk;
	ds_key_t	cr_catalog_page_sk;
	ds_key_t	cr_ship_mode_sk;
	ds_key_t	cr_warehouse_sk;
	ds_key_t	cr_reason_sk;
	ds_key_t	cr_order_number;
	ds_pricing_t cr_pricing;
	decimal_t	cr_fee;
	decimal_t	cr_refunded_cash;
	decimal_t	cr_reversed_charge;
	decimal_t	cr_store_credit;
	decimal_t	cr_net_loss;
};

int mk_w_catalog_returns(void *pDest, ds_key_t kIndex);
int pr_w_catalog_returns(void *pSrc);
int ld_w_catalog_returns(void *pSrc);
#endif

