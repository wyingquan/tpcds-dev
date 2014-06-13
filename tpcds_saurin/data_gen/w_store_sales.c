/*
* $Id: w_store_sales.c,v 1.19 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_store_sales.c,v $
* Revision 1.19  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.18  2007/07/24 20:07:30  jms
* bug 546
*
* Revision 1.17  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.16  2006/11/01 00:32:55  jms
* remove unused vars
*
* Revision 1.15  2006/10/13 23:37:35  jms
* Bug 308: rework date-based tables to focus on orders
*
* Revision 1.14  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.13  2006/06/07 20:30:50  jms
* porting cleanup
*
* Revision 1.12  2006/05/09 21:03:45  jms
* correct primary keys in sales tables of warehouse
*
* Revision 1.11  2006/02/02 05:55:45  jms
* fix SCD FK errors resulting from over-corrected key->sk mapping
*
* Revision 1.10  2006/02/02 05:03:08  jms
* fix join with item table
*
* Revision 1.9  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.8  2005/11/12 23:37:07  jms
* remove extraneous debug calls
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
* Revision 1.12  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.11  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.10  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.9  2004/05/26 17:12:25  jms
* Bug #51: ticket numbers were overly constrained
*
* Revision 1.8  2004/05/03 22:37:04  jms
* simplify RNG debugging
*
* Revision 1.7  2004/04/08 06:09:05  jms
* bug #51: ticket number should not be unique
*
* Revision 1.6  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.5  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.4  2004/03/26 22:49:26  jms
* revert to integer _sk fields
*
* Revision 1.3  2004/03/03 17:06:22  jms
* correct datatype for store sales join to store
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
#include "decimal.h"
#include "w_store_sales.h"
#include "w_store_returns.h"
#include "genrand.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "constants.h"
#include "print.h"
#include "nulls.h"
#include "tdefs.h"
#include "scaling.h"
#include "permute.h"
#include "scd.h"
#include "parallel.h"
#ifdef JMS
extern rng_t Streams[];
#endif

struct W_STORE_SALES_TBL g_w_store_sales;
ds_key_t skipDays(int nTable, ds_key_t *pRemainder);
static int *pItemPermutation,
   nItemCount,
	nItemIndex;
static ds_key_t jDate,
   kNewDateIndex;

/*
* mk_store_sales
*/
static void
mk_master (void *row, ds_key_t index)
{
	struct W_STORE_SALES_TBL *r;
	static decimal_t dMin,
		dMax;
	static int bInit = 0,
		nMaxItemCount;
	static ds_key_t kNewDateIndex = 0;

	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

	if (!bInit)
	{
      strtodec (&dMin, "1.00");
      strtodec (&dMax, "100000.00");
		nMaxItemCount = 20;
		jDate = skipDays(STORE_SALES, &kNewDateIndex);
		pItemPermutation = makePermutation(NULL, nItemCount = (int)getIDCount(ITEM), SS_PERMUTATION);
		
		bInit = 1;
	}

	
   while (index > kNewDateIndex)	/* need to move to a new date */
   {
      jDate += 1;
      kNewDateIndex += dateScaling(STORE_SALES, jDate);
   }
		r->ss_sold_store_sk = mk_join (SS_SOLD_STORE_SK, STORE, 1);
		r->ss_sold_time_sk = mk_join (SS_SOLD_TIME_SK, TIME, 1);
		r->ss_sold_date_sk = mk_join (SS_SOLD_DATE_SK, DATE, 1);
		r->ss_sold_customer_sk = mk_join (SS_SOLD_CUSTOMER_SK, CUSTOMER, 1);
		r->ss_sold_cdemo_sk = mk_join (SS_SOLD_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);
		r->ss_sold_hdemo_sk = mk_join (SS_SOLD_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);
		r->ss_sold_addr_sk = mk_join (SS_SOLD_ADDR_SK, CUSTOMER_ADDRESS, 1);
		r->ss_ticket_number = index;
		genrand_integer(&nItemIndex, DIST_UNIFORM, 1, nItemCount, 0, SS_SOLD_ITEM_SK);

      return;
}


static void
mk_detail (void *row, int bPrint)
{
int nTemp;
struct W_STORE_RETURNS_TBL ReturnRow;
struct W_STORE_SALES_TBL *r;
tdef *pT = getSimpleTdefsByNumber(STORE_SALES);

	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

   nullSet(&pT->kNullBitMap, SS_NULLS);
	/* 
	 * items need to be unique within an order
	 * use a sequence within the permutation 
	 */
	if (++nItemIndex > nItemCount)
      nItemIndex = 1;
   r->ss_sold_item_sk = matchSCDSK(getPermutationEntry(pItemPermutation, nItemIndex), r->ss_sold_date_sk, ITEM);
	r->ss_sold_promo_sk = mk_join (SS_SOLD_PROMO_SK, PROMOTION, 1);
	set_pricing(SS_PRICING, &r->ss_pricing);

	/** 
	* having gone to the trouble to make the sale, now let's see if it gets returned
	*/
	genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, SR_IS_RETURNED);
	if (nTemp < SR_RETURN_PCT)
	{
		mk_w_store_returns(&ReturnRow, 1);
      if (bPrint)
         pr_w_store_returns(&ReturnRow);
	}

   if (bPrint)
      pr_w_store_sales(NULL);
	
	return;
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
pr_w_store_sales(void *row)
{
	struct W_STORE_SALES_TBL *r;
	
	if (row == NULL)
		r = &g_w_store_sales;
	else
		r = row;

	print_start(STORE_SALES);
	print_key(SS_SOLD_DATE_SK, r->ss_sold_date_sk, 1);
	print_key(SS_SOLD_TIME_SK, r->ss_sold_time_sk, 1);
	print_key(SS_SOLD_ITEM_SK, r->ss_sold_item_sk, 1);
	print_key(SS_SOLD_CUSTOMER_SK, r->ss_sold_customer_sk, 1);
	print_key(SS_SOLD_CDEMO_SK, r->ss_sold_cdemo_sk, 1);
	print_key(SS_SOLD_HDEMO_SK, r->ss_sold_hdemo_sk, 1);
	print_key(SS_SOLD_ADDR_SK, r->ss_sold_addr_sk, 1);
	print_key(SS_SOLD_STORE_SK, r->ss_sold_store_sk, 1);
	print_key(SS_SOLD_PROMO_SK, r->ss_sold_promo_sk, 1);
	print_key(SS_TICKET_NUMBER, r->ss_ticket_number, 1);
	print_integer(SS_PRICING_QUANTITY, r->ss_pricing.quantity, 1);
	print_decimal(SS_PRICING_WHOLESALE_COST, &r->ss_pricing.wholesale_cost, 1);
	print_decimal(SS_PRICING_LIST_PRICE, &r->ss_pricing.list_price, 1);
	print_decimal(SS_PRICING_SALES_PRICE, &r->ss_pricing.sales_price, 1);
	print_decimal(SS_PRICING_COUPON_AMT, &r->ss_pricing.coupon_amt, 1);
	print_decimal(SS_PRICING_EXT_SALES_PRICE, &r->ss_pricing.ext_sales_price, 1);
	print_decimal(SS_PRICING_EXT_WHOLESALE_COST, &r->ss_pricing.ext_wholesale_cost, 1);
	print_decimal(SS_PRICING_EXT_LIST_PRICE, &r->ss_pricing.ext_list_price, 1);
	print_decimal(SS_PRICING_EXT_TAX, &r->ss_pricing.ext_tax, 1);
	print_decimal(SS_PRICING_COUPON_AMT, &r->ss_pricing.coupon_amt, 1);
	print_decimal(SS_PRICING_NET_PAID, &r->ss_pricing.net_paid, 1);
	print_decimal(SS_PRICING_NET_PAID_INC_TAX, &r->ss_pricing.net_paid_inc_tax, 1);
	print_decimal(SS_PRICING_NET_PROFIT, &r->ss_pricing.net_profit, 0);
	print_end(STORE_SALES);

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
ld_w_store_sales(void *pSrc)
{
	struct W_STORE_SALES_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_store_sales;
	else
		r = pSrc;
	
	return(0);
}

/*
* mk_store_sales
*/
int
mk_w_store_sales (void *row, ds_key_t index)
{
	int nLineitems,
		i;

   /* build the static portion of an order */
	mk_master(row, index);

   /* set the number of lineitems and build them */
	genrand_integer(&nLineitems, DIST_UNIFORM, 8, 16, 0, SS_TICKET_NUMBER);
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
vld_w_store_sales(int nTable, ds_key_t kRow, int *Permutation)
{
	int nLineitem,
		nMaxLineitem,
		i;

	row_skip(nTable, kRow - 1);
	row_skip(STORE_RETURNS, kRow - 1);
	jDate = skipDays(STORE_SALES, &kNewDateIndex);		
	mk_master(NULL, kRow);
	genrand_integer(&nMaxLineitem, DIST_UNIFORM, 8, 16, 9, SS_TICKET_NUMBER);
	genrand_integer(&nLineitem, DIST_UNIFORM, 1, nMaxLineitem, 0, SS_PRICING_QUANTITY);
	for (i = 1; i < nLineitem; i++)
	{
		mk_detail(NULL, 0);
	}
	mk_detail(NULL, 1);

	return(0);
}

