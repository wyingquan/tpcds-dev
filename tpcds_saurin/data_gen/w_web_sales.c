/*
* $Id: w_web_sales.c,v 1.21 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_web_sales.c,v $
* Revision 1.21  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.20  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.19  2007/07/25 19:41:47  jms
* bug 546: remove duplicate printing
*
* Revision 1.18  2007/07/24 20:07:30  jms
* bug 546
*
* Revision 1.17  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.16  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.15  2006/11/01 00:32:55  jms
* remove unused vars
*
* Revision 1.14  2006/10/23 22:43:35  jms
* Bugs reported during Nashville meeting
*
* Revision 1.13  2006/10/13 23:37:35  jms
* Bug 308: rework date-based tables to focus on orders
*
* Revision 1.12  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.11  2006/06/07 20:30:50  jms
* porting cleanup
*
* Revision 1.10  2006/02/02 05:55:45  jms
* fix SCD FK errors resulting from over-corrected key->sk mapping
*
* Revision 1.9  2006/02/02 05:03:08  jms
* fix join with item table
*
* Revision 1.8  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.7  2005/10/06 22:09:44  jms
* bug #308: chunked data error. Add skipDate() to adjust date values
*
* Revision 1.6  2005/10/05 20:01:44  jms
* bug #308: chunked data error. Add skipDate() to adjust date values
*
* Revision 1.5  2005/10/05 16:16:36  jms
* correct permute.h include
*
* Revision 1.4  2005/10/04 16:19:13  jms
* bug #305: enforce primary keys for fact tables built from item_sk and order_number
*
* Revision 1.3  2005/04/21 17:18:49  jms
* Bug #168: Generate fact tables in date order
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.8  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.7  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.6  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.5  2004/05/26 17:11:32  jms
* add generation of ws_web_site_sk and standardize column names (sk vs id)
*
* Revision 1.4  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.3  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
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
#include "w_web_sales.h"
#include "w_web_returns.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "tables.h"
#include "constants.h"
#include "nulls.h"
#include "tdefs.h"
#include "scaling.h"
#include "permute.h"
#include "scd.h"
#include "parallel.h"

struct W_WEB_SALES_TBL g_w_web_sales;
ds_key_t skipDays(int nTable, ds_key_t *pRemainder);

static ds_key_t kNewDateIndex = 0;
static ds_key_t jDate;
static int nItemIndex = 0;


/*
 * the validation process requires generating a single lineitem
 * so the main mk_xxx routine has been split into a master record portion
 * and a detail/lineitem portion.
 */
static void
mk_master (void *row, ds_key_t index)
{
   static decimal_t dMin,
      dMax;
   int nGiftPct;
   struct W_WEB_SALES_TBL *r;
   static int bInit = 0,
	   nItemCount;
	
	if (row == NULL)
		r = &g_w_web_sales;
	else
		r = row;

	if (!bInit)
	{
		strtodec (&dMin, "1.00");
		strtodec (&dMax, "100000.00");
		jDate = skipDays(WEB_SALES, &kNewDateIndex);	
		nItemCount = (int)getIDCount(ITEM);
		bInit = 1;
	}
		
	
	/***
	* some attributes reamin the same for each lineitem in an order; others are different
	* for each lineitem. Since the number of lineitems per order is static, we can use a 
	* modulo to determine when to change the semi-static values 
	*/
   while (index > kNewDateIndex)	/* need to move to a new date */
   {
      jDate += 1;
      kNewDateIndex += dateScaling(WEB_SALES, jDate);
   }

   r->ws_sold_date_sk = mk_join (WS_SOLD_DATE_SK, DATE, 1);
   r->ws_sold_time_sk = mk_join(WS_SOLD_TIME_SK, TIME, 1);
   r->ws_bill_customer_sk = mk_join (WS_BILL_CUSTOMER_SK, CUSTOMER, 1);
   r->ws_bill_cdemo_sk = mk_join (WS_BILL_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);
   r->ws_bill_hdemo_sk = mk_join (WS_BILL_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);
   r->ws_bill_addr_sk = mk_join (WS_BILL_ADDR_SK, CUSTOMER_ADDRESS, 1);
		
   /* most orders are for the ordering customers, some are not */
   genrand_integer(&nGiftPct, DIST_UNIFORM, 0, 99, 0, WS_SHIP_CUSTOMER_SK);
   if (nGiftPct > WS_GIFT_PCT)
   {
      r->ws_ship_customer_sk =
         mk_join (WS_SHIP_CUSTOMER_SK, CUSTOMER, 2);
      r->ws_ship_cdemo_sk =
         mk_join (WS_SHIP_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 2);
      r->ws_ship_hdemo_sk =
         mk_join (WS_SHIP_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 2);
      r->ws_ship_addr_sk =
         mk_join (WS_SHIP_ADDR_SK, CUSTOMER_ADDRESS, 2);
   }
   else
   {
      r->ws_ship_customer_sk =	r->ws_bill_customer_sk;
      r->ws_ship_cdemo_sk =	r->ws_bill_cdemo_sk;
      r->ws_ship_hdemo_sk =	r->ws_bill_hdemo_sk;
      r->ws_ship_addr_sk =	r->ws_bill_addr_sk;
   }

   r->ws_order_number = index;
   genrand_integer(&nItemIndex, DIST_UNIFORM, 1, nItemCount, 0, WS_ITEM_SK);

return;
}

static void
mk_detail (void *row, int bPrint)
{
	static int *pItemPermutation,
		nItemCount,
		bInit = 0;
	struct W_WEB_SALES_TBL *r;
	int nShipLag,
		nTemp;
   struct W_WEB_RETURNS_TBL w_web_returns;
   tdef *pT = getSimpleTdefsByNumber(WEB_SALES);


	if (!bInit)
	{
		jDate = skipDays(WEB_SALES, &kNewDateIndex);
		pItemPermutation = makePermutation(NULL, nItemCount = (int)getIDCount(ITEM), WS_PERMUTATION);
		
		bInit = 1;
	}

	if (row == NULL)
		r = &g_w_web_sales;
	else
		r = row;

	nullSet(&pT->kNullBitMap, WS_NULLS);


      /* orders are shipped some number of days after they are ordered,
      * and not all lineitems ship at the same time
      */
      genrand_integer (&nShipLag, DIST_UNIFORM, 
         WS_MIN_SHIP_DELAY, WS_MAX_SHIP_DELAY, 0, WS_SHIP_DATE_SK);
      r->ws_ship_date_sk = r->ws_sold_date_sk + nShipLag;

      if (++nItemIndex > nItemCount)
         nItemIndex = 1;
      r->ws_item_sk = matchSCDSK(getPermutationEntry(pItemPermutation, nItemIndex), r->ws_sold_date_sk, ITEM);

      /* the web page needs to be valid for the sale date */
      r->ws_web_page_sk = mk_join (WS_WEB_PAGE_SK, WEB_PAGE, r->ws_sold_date_sk);
      r->ws_web_site_sk = mk_join (WS_WEB_SITE_SK, WEB_SITE, r->ws_sold_date_sk);

      r->ws_ship_mode_sk = mk_join (WS_SHIP_MODE_SK, SHIP_MODE, 1);
      r->ws_warehouse_sk = mk_join (WS_WAREHOUSE_SK, WAREHOUSE, 1);
      r->ws_promo_sk = mk_join (WS_PROMO_SK, PROMOTION, 1);
      set_pricing(WS_PRICING, &r->ws_pricing);

      /** 
      * having gone to the trouble to make the sale, now let's see if it gets returned
      */
      genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, WR_IS_RETURNED);
      if (nTemp < WR_RETURN_PCT)
      {
         mk_w_web_returns(&w_web_returns, 1);
         if (bPrint)
			 pr_w_web_returns(&w_web_returns);
      }

      /**
      * now we print out the order and lineitem together as a single row
      */
      if (bPrint)
		  pr_w_web_sales(NULL);

	  return;
}

/*
* mk_web_sales
*/
int
mk_w_web_sales (void *row, ds_key_t index)
{
	int nLineitems,
		i;

   /* build the static portion of an order */
	mk_master(row, index);

   /* set the number of lineitems and build them */
	genrand_integer(&nLineitems, DIST_UNIFORM, 8, 16, 9, WS_ORDER_NUMBER);
   for (i = 1; i <= nLineitems; i++)
   {
	   mk_detail(NULL, 1);
   }

   /**
   * and finally return 1 since we have already printed the rows
   */	
   return (1);
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
pr_w_web_sales(void *row)
{
	struct W_WEB_SALES_TBL *r;
	
	if (row == NULL)
		r = &g_w_web_sales;
	else
		r = row;
	
	print_start(WEB_SALES);
	print_key(WS_SOLD_DATE_SK, r->ws_sold_date_sk, 1);
	print_key(WS_SOLD_TIME_SK, r->ws_sold_time_sk, 1);
	print_key(WS_SHIP_DATE_SK, r->ws_ship_date_sk, 1);
	print_key(WS_ITEM_SK, r->ws_item_sk, 1);
	print_key(WS_BILL_CUSTOMER_SK, r->ws_bill_customer_sk, 1);
	print_key(WS_BILL_CDEMO_SK, r->ws_bill_cdemo_sk, 1);
	print_key(WS_BILL_HDEMO_SK, r->ws_bill_hdemo_sk, 1);
	print_key(WS_BILL_ADDR_SK, r->ws_bill_addr_sk, 1);
	print_key(WS_SHIP_CUSTOMER_SK, r->ws_ship_customer_sk, 1);
	print_key(WS_SHIP_CDEMO_SK, r->ws_ship_cdemo_sk, 1);
	print_key(WS_SHIP_HDEMO_SK, r->ws_ship_hdemo_sk, 1);
	print_key(WS_SHIP_ADDR_SK, r->ws_ship_addr_sk, 1);
	print_key(WS_WEB_PAGE_SK, r->ws_web_page_sk, 1);
	print_key(WS_WEB_SITE_SK, r->ws_web_site_sk, 1);
	print_key(WS_SHIP_MODE_SK, r->ws_ship_mode_sk, 1);
	print_key(WS_WAREHOUSE_SK, r->ws_warehouse_sk, 1);
	print_key(WS_PROMO_SK, r->ws_promo_sk, 1);
	print_key(WS_ORDER_NUMBER, r->ws_order_number, 1);
	print_integer(WS_PRICING_QUANTITY, r->ws_pricing.quantity, 1);
	print_decimal(WS_PRICING_WHOLESALE_COST, &r->ws_pricing.wholesale_cost, 1);
	print_decimal(WS_PRICING_LIST_PRICE, &r->ws_pricing.list_price, 1);
	print_decimal(WS_PRICING_SALES_PRICE, &r->ws_pricing.sales_price, 1);
	print_decimal(WS_PRICING_EXT_DISCOUNT_AMT, &r->ws_pricing.ext_discount_amt, 1);
	print_decimal(WS_PRICING_EXT_SALES_PRICE, &r->ws_pricing.ext_sales_price, 1);
	print_decimal(WS_PRICING_EXT_WHOLESALE_COST, &r->ws_pricing.ext_wholesale_cost, 1);
	print_decimal(WS_PRICING_EXT_LIST_PRICE, &r->ws_pricing.ext_list_price, 1);
	print_decimal(WS_PRICING_EXT_TAX, &r->ws_pricing.ext_tax, 1);
	print_decimal(WS_PRICING_COUPON_AMT, &r->ws_pricing.coupon_amt, 1);
	print_decimal(WS_PRICING_EXT_SHIP_COST, &r->ws_pricing.ext_ship_cost, 1);
	print_decimal(WS_PRICING_NET_PAID, &r->ws_pricing.net_paid, 1);
	print_decimal(WS_PRICING_NET_PAID_INC_TAX, &r->ws_pricing.net_paid_inc_tax, 1);
	print_decimal(WS_PRICING_NET_PAID_INC_SHIP, &r->ws_pricing.net_paid_inc_ship, 1);
	print_decimal(WS_PRICING_NET_PAID_INC_SHIP_TAX, &r->ws_pricing.net_paid_inc_ship_tax, 1);
	print_decimal(WS_PRICING_NET_PROFIT, &r->ws_pricing.net_profit, 0);
	print_end(WEB_SALES);

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
ld_w_web_sales(void *pSrc)
{
	struct W_WEB_SALES_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_web_sales;
	else
		r = pSrc;
	
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
vld_web_sales(int nTable, ds_key_t kRow, int *Permutation)
{
	int nLineitem,
		nMaxLineitem,
		i;

	row_skip(nTable, kRow - 1);
	row_skip(WEB_RETURNS, (kRow - 1) );
	jDate = skipDays(WEB_SALES, &kNewDateIndex);		
	mk_master(NULL, kRow);
	genrand_integer(&nMaxLineitem, DIST_UNIFORM, 8, 16, 9, WS_ORDER_NUMBER);
	genrand_integer(&nLineitem, DIST_UNIFORM, 1, nMaxLineitem, 0, WS_PRICING_QUANTITY);
	for (i = 1; i < nLineitem; i++)
	{
		mk_detail(NULL, 0);
	}
   mk_detail(NULL, 1);

	return(0);
}

