/*
* $Id: w_store_returns.c,v 1.7 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_store_returns.c,v $
* Revision 1.7  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.6  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.5  2006/04/20 19:32:47  jms
* Release 38c
*
* Revision 1.4  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.3  2006/03/28 19:03:23  jms
* additional testing of updates from Meikel
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.8  2004/09/24 00:54:57  jms
* Bug #90
*
* Revision 1.7  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/07 22:44:25  jms
* changes diagnosing parallelism
*
* Revision 1.3  2004/03/26 19:45:04  jms
* rename tdef_funtions.c to tdef_functions.c
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
#include "w_store_returns.h"
#include "w_store_sales.h"
#include "tables.h"
#include "print.h"
#include "pricing.h"
#include "columns.h"
#include "genrand.h"
#include "build_support.h"
#include "nulls.h"
#include "tdefs.h"

struct W_STORE_RETURNS_TBL g_w_store_returns;
extern struct W_STORE_SALES_TBL g_w_store_sales;

/*
* Routine: mk_store_returns()
* Purpose: populate a return fact *sync'd with a sales fact*
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
mk_w_store_returns (void * row, ds_key_t index)
{
	int res = 0,
		nTemp;
	struct W_STORE_RETURNS_TBL *r;
	struct W_STORE_SALES_TBL *sale = &g_w_store_sales;
	static int bInit = 0;
   tdef *pT = getSimpleTdefsByNumber(STORE_RETURNS);
	
	static decimal_t dMin,
		dMax;
	/* begin locals declarations */
	
	if (row == NULL)
		r = &g_w_store_returns;
	else
		r = row;

	if (!bInit)
	{
        strtodec (&dMin, "1.00");
        strtodec (&dMax, "100000.00");
	}
	
	nullSet(&pT->kNullBitMap, SR_NULLS);
	/*
	* Some of the information in the return is taken from the original sale
	* which has been regenerated
	*/
	r->sr_ticket_number = sale->ss_ticket_number;
	r->sr_item_sk = sale->ss_sold_item_sk;
	memcpy((void *)&r->sr_pricing, (void *)&sale->ss_pricing, sizeof(ds_pricing_t));

	/*
	 * some of the fields are conditionally taken from the sale 
	 */
	r->sr_customer_sk = mk_join (SR_CUSTOMER_SK, CUSTOMER, 1);
	if (genrand_integer(NULL, DIST_UNIFORM, 1, 100, 0, SR_TICKET_NUMBER) < SR_SAME_CUSTOMER)
		r->sr_customer_sk = sale->ss_sold_customer_sk;

	/*
	* the rest of the columns are generated for this specific return
	*/
	/* the items cannot be returned until they are sold; offset is handled in mk_join, based on sales date */
	r->sr_returned_date_sk = mk_join (SR_RETURNED_DATE_SK, DATE, sale->ss_sold_date_sk);
	genrand_integer(&nTemp, DIST_UNIFORM, (8 * 3600) - 1, (17 * 3600) - 1, 0, SR_RETURNED_TIME_SK);
	r->sr_returned_time_sk = nTemp;
	r->sr_cdemo_sk =
		mk_join (SR_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);
	r->sr_hdemo_sk =
		mk_join (SR_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);
	r->sr_addr_sk = mk_join (SR_ADDR_SK, CUSTOMER_ADDRESS, 1);
	r->sr_store_sk = mk_join (SR_STORE_SK, STORE, 1);
	r->sr_reason_sk = mk_join (SR_REASON_SK, REASON, 1);
	genrand_integer(&r->sr_pricing.quantity, DIST_UNIFORM,
		1, sale->ss_pricing.quantity, 0, SR_PRICING);
	set_pricing(SR_PRICING, &r->sr_pricing);
	
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
pr_w_store_returns(void *row)
{
	struct W_STORE_RETURNS_TBL *r;


	if (row == NULL)
		r = &g_w_store_returns;
	else
		r = row;
	print_start(STORE_RETURNS);
	print_key(SR_RETURNED_DATE_SK, r->sr_returned_date_sk, 1);
	print_key(SR_RETURNED_TIME_SK, r->sr_returned_time_sk, 1);
	print_key(SR_ITEM_SK, r->sr_item_sk, 1);
	print_key(SR_CUSTOMER_SK, r->sr_customer_sk, 1);
	print_key(SR_CDEMO_SK, r->sr_cdemo_sk, 1);
	print_key(SR_HDEMO_SK, r->sr_hdemo_sk, 1);
	print_key(SR_ADDR_SK, r->sr_addr_sk, 1);
	print_key(SR_STORE_SK, r->sr_store_sk, 1);
	print_key(SR_REASON_SK, r->sr_reason_sk, 1);
	print_key(SR_TICKET_NUMBER, r->sr_ticket_number, 1);
	print_integer(SR_PRICING_QUANTITY, r->sr_pricing.quantity, 1);
	print_decimal(SR_PRICING_NET_PAID, &r->sr_pricing.net_paid, 1);
	print_decimal(SR_PRICING_EXT_TAX, &r->sr_pricing.ext_tax, 1);
	print_decimal(SR_PRICING_NET_PAID_INC_TAX, &r->sr_pricing.net_paid_inc_tax, 1);
	print_decimal(SR_PRICING_FEE, &r->sr_pricing.fee, 1);
	print_decimal(SR_PRICING_EXT_SHIP_COST, &r->sr_pricing.ext_ship_cost, 1);
	print_decimal(SR_PRICING_REFUNDED_CASH, &r->sr_pricing.refunded_cash, 1);
	print_decimal(SR_PRICING_REVERSED_CHARGE, &r->sr_pricing.reversed_charge, 1);
	print_decimal(SR_PRICING_STORE_CREDIT, &r->sr_pricing.store_credit, 1);
	print_decimal(SR_PRICING_NET_LOSS, &r->sr_pricing.net_loss, 0);
	print_end(STORE_RETURNS);
	
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
ld_w_store_returns(void *pSrc)
{
	struct W_STORE_RETURNS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_store_returns;
	else
		r = pSrc;
	
	return(0);
}

