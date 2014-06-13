/*
* $Id: w_web_returns.c,v 1.7 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_web_returns.c,v $
* Revision 1.7  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.6  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.5  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.4  2005/11/06 22:01:13  jms
* first rework of source generation
*
* Revision 1.3  2005/03/04 22:00:44  jms
* update to WAM, removal of sold_date info from returns tables
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.7  2004/09/24 00:54:57  jms
* Bug #90
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/05/26 17:11:32  jms
* add generation of ws_web_site_sk and standardize column names (sk vs id)
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
#include "pricing.h"
#include "w_web_returns.h"
#include "w_web_sales.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "error_msg.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_WEB_RETURNS_TBL g_w_web_returns;
extern struct W_WEB_SALES_TBL g_w_web_sales;

/*
* Routine: mk_web_returns()
* Purpose: populate a return fact *sync'd with a sales fact*
* Algorithm: Since the returns need to be in line with a prior sale, they are built by a call from
*	the mk_catalog_sales() routine, and then add return-related information
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
mk_w_web_returns (void* row, ds_key_t index)
{
	int res = 0;
	
	static decimal_t dMin,
		dMax;
	static struct W_WEB_SALES_TBL *sale;
	static int bInit = 0;
	struct W_WEB_RETURNS_TBL *r;
   tdef *pT = getSimpleTdefsByNumber(WEB_RETURNS);
	
	if (row == NULL)
		r = &g_w_web_returns;
	else
		r = row;
	
	if (!bInit)
	{
        strtodec (&dMin, "1.00");
        strtodec (&dMax, "100000.00");
		bInit = 1;
	}
		
	nullSet(&pT->kNullBitMap, WR_NULLS);
	
	/*
	* Some of the information in the return is taken from the original sale
	* which has been regenerated
	*/
	sale = &g_w_web_sales;
	r->wr_item_sk = sale->ws_item_sk;
	r->wr_order_number = sale->ws_order_number;
	memcpy((void *)&r->wr_pricing, (void *)&sale->ws_pricing, sizeof(ds_pricing_t));
	r->wr_web_page_sk = sale->ws_web_page_sk;


	/*
	* the rest of the columns are generated for this specific return
	*/
	/* the items cannot be returned until they are shipped; offset is handled in mk_join, based on sales date */
	r->wr_returned_date_sk = mk_join (WR_RETURNED_DATE_SK, DATE, sale->ws_ship_date_sk);
	r->wr_returned_time_sk = mk_join(WR_RETURNED_TIME_SK, TIME, 1);

	/* most items are returned by the people they were shipped to, but some are returned
	* by other folks
	*/
		r->wr_refunded_customer_sk = mk_join (WR_REFUNDED_CUSTOMER_SK, CUSTOMER, 1);
		r->wr_refunded_cdemo_sk =
			mk_join (WR_REFUNDED_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);
		r->wr_refunded_hdemo_sk =
			mk_join (WR_REFUNDED_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);
		r->wr_refunded_addr_sk =
			mk_join (WR_REFUNDED_ADDR_SK, CUSTOMER_ADDRESS, 1);
	if (genrand_integer(NULL, DIST_UNIFORM, 0, 99, 0, WR_RETURNING_CUSTOMER_SK) 
		< WS_GIFT_PCT)
	{
		r->wr_refunded_customer_sk = sale->ws_ship_customer_sk;
		r->wr_refunded_cdemo_sk = sale->ws_ship_cdemo_sk;
		r->wr_refunded_hdemo_sk = sale->ws_ship_hdemo_sk;
		r->wr_refunded_addr_sk = sale->ws_ship_addr_sk;
	}
	r->wr_returning_customer_sk = r->wr_refunded_customer_sk;
	r->wr_returning_cdemo_sk = r->wr_refunded_cdemo_sk;
	r->wr_returning_hdemo_sk = r->wr_refunded_hdemo_sk;
	r->wr_returning_addr_sk = r->wr_refunded_addr_sk;

	r->wr_reason_sk = mk_join (WR_REASON_SK, REASON, 1);
	genrand_integer(&r->wr_pricing.quantity, DIST_UNIFORM,
		1, sale->ws_pricing.quantity, 0, WR_PRICING);
	set_pricing(WR_PRICING, &r->wr_pricing);
	
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
pr_w_web_returns(void *row)
{
	struct W_WEB_RETURNS_TBL *r;
	
	if (row == NULL)
		r = &g_w_web_returns;
	else
		r = row;
	
	print_start(WEB_RETURNS);
	print_key(WR_RETURNED_DATE_SK, r->wr_returned_date_sk, 1);
	print_key(WR_RETURNED_TIME_SK, r->wr_returned_time_sk, 1);
	print_key(WR_ITEM_SK, r->wr_item_sk, 1);
	print_key(WR_REFUNDED_CUSTOMER_SK, r->wr_refunded_customer_sk, 1);
	print_key(WR_REFUNDED_CDEMO_SK, r->wr_refunded_cdemo_sk, 1);
	print_key(WR_REFUNDED_HDEMO_SK, r->wr_refunded_hdemo_sk, 1);
	print_key(WR_REFUNDED_ADDR_SK, r->wr_refunded_addr_sk, 1);
	print_key(WR_RETURNING_CUSTOMER_SK, r->wr_returning_customer_sk, 1);
	print_key(WR_RETURNING_CDEMO_SK, r->wr_returning_cdemo_sk, 1);
	print_key(WR_RETURNING_HDEMO_SK, r->wr_returning_hdemo_sk, 1);
	print_key(WR_RETURNING_ADDR_SK, r->wr_returning_addr_sk, 1);
	print_key(WR_WEB_PAGE_SK, r->wr_web_page_sk, 1);
	print_key(WR_REASON_SK, r->wr_reason_sk, 1);
	print_key(WR_ORDER_NUMBER, r->wr_order_number, 1);
	print_integer(WR_PRICING_QUANTITY, r->wr_pricing.quantity, 1);
	print_decimal(WR_PRICING_NET_PAID, &r->wr_pricing.net_paid, 1);
	print_decimal(WR_PRICING_EXT_TAX, &r->wr_pricing.ext_tax, 1);
	print_decimal(WR_PRICING_NET_PAID_INC_TAX, &r->wr_pricing.net_paid_inc_tax, 1);
	print_decimal(WR_PRICING_FEE, &r->wr_pricing.fee, 1);
	print_decimal(WR_PRICING_EXT_SHIP_COST, &r->wr_pricing.ext_ship_cost, 1);
	print_decimal(WR_PRICING_REFUNDED_CASH, &r->wr_pricing.refunded_cash, 1);
	print_decimal(WR_PRICING_REVERSED_CHARGE, &r->wr_pricing.reversed_charge, 1);
	print_decimal(WR_PRICING_STORE_CREDIT, &r->wr_pricing.store_credit, 1);
	print_decimal(WR_PRICING_NET_LOSS, &r->wr_pricing.net_loss, 0);
	print_end(WEB_RETURNS);

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
ld_w_web_returns(void *pSrc)
{
	struct W_WEB_RETURNS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_web_returns;
	else
		r = pSrc;
	
	return(0);
}

