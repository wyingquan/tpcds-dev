/*
* $Id: pricing.h,v 1.3 2006/06/02 19:25:05 jms Exp $
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
* $Log: pricing.h,v $
* Revision 1.3  2006/06/02 19:25:05  jms
* add per-item ship cost to source catalog and web lineitems
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2002/08/16 23:24:22  jms
* complete linkage of catalog sales and returns and clean up parent child handling
*
* Revision 1.2  2002/07/27 00:08:49  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.2.1  2002/07/18 22:05:23  jms
* isolating pricing calculations for the sales tables
*
*
*/
#ifndef PRICING_H
#define PRICING_H
#include "decimal.h"

typedef struct DS_PRICING_T {
	decimal_t wholesale_cost;
	decimal_t list_price;
	decimal_t sales_price;
	int quantity;
	decimal_t ext_discount_amt;
	decimal_t ext_sales_price;
	decimal_t ext_wholesale_cost;
	decimal_t ext_list_price;
	decimal_t tax_pct;
	decimal_t ext_tax;
	decimal_t coupon_amt;
   decimal_t ship_cost;
	decimal_t ext_ship_cost;
	decimal_t net_paid;
	decimal_t net_paid_inc_tax;
	decimal_t net_paid_inc_ship;
	decimal_t net_paid_inc_ship_tax;
	decimal_t net_profit;
	decimal_t refunded_cash;
	decimal_t reversed_charge;
	decimal_t store_credit;
	decimal_t fee;
	decimal_t net_loss;
} ds_pricing_t;

typedef struct DS_LIMITS_T
{
	int nId;
	char *szQuantity;
	char *szMarkUp;
	char *szDiscount;
	char *szWholesale;
	char *szCoupon;
} ds_limits_t;

void set_pricing(int nTabId, ds_pricing_t *pPricing);
#endif
