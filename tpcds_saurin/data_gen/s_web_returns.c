/*
* $Id: s_web_returns.c,v 1.12 2007/09/10 18:10:36 jms Exp $
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
* $Log: s_web_returns.c,v $
* Revision 1.12  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.11  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.10  2006/03/30 16:40:31  jms
* bug reports from Meikel 3/29
*
* Revision 1.9  2006/03/28 19:03:23  jms
* additional testing of updates from Meikel
*
* Revision 1.8  2006/03/17 23:23:14  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.7  2006/03/17 22:55:39  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.5  2006/03/09 00:53:50  jms
* Bug 402: assorted data errors in source schema
*
* Revision 1.4  2005/11/11 21:24:41  jms
* add return time to all channels in source schema
*
* Revision 1.3  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.3  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "s_web_returns.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "w_web_sales.h"
#include "s_web_order.h"
#include "s_web_order_lineitem.h"
#include "parallel.h"

struct S_WEB_RETURNS_TBL g_s_web_returns;
extern struct S_WEB_ORDER_TBL g_s_web_order;
extern struct S_WEB_ORDER_LINEITEM_TBL g_s_web_order_lineitem;


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
mk_s_web_return(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_WEB_RETURNS_TBL *r;
	int nReturnLag;
	static date_t MinDataDate,
		MaxDataDate;
	
	if (pDest == NULL)
		r = &g_s_web_returns;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_web_returns, 0, sizeof(struct S_WEB_RETURNS_TBL));
		strtodt(&MinDataDate, DATA_START_DATE);
		strtodt(&MaxDataDate, DATA_END_DATE);
		bInit = 1;
	}

	genrand_integer(&nReturnLag, DIST_UNIFORM, 1, 60, 0, S_WRET_RETURN_DATE);
   if (g_s_web_order.dtOrderDate.julian == -1)
      r->dtReturnDate.julian = -1;
   else
      jtodt(&r->dtReturnDate, g_s_web_order.dtOrderDate.julian + nReturnLag);
	r->kReturnTime = mk_join(S_WRET_RETURN_TIME, TIME, 1);
	r->kReasonID = mk_join(S_WRET_REASON_ID, REASON, 1);
	r->kSiteID = g_s_web_order.kWebSiteID;
	r->kOrderID = g_s_web_order.kID;
	r->nLineNumber = kIndex;
	r->kItemID = g_s_web_order_lineitem.kItemID;
	r->kReturningCustomerID = g_s_web_order.kShipCustomerID;
	r->kRefundedCustomerID = g_s_web_order.kShipCustomerID;
	r->Pricing = g_s_web_order_lineitem.Pricing;
   if (g_s_web_order_lineitem.Pricing.quantity == -1)
      r->Pricing.quantity = -1;
   else
      genrand_integer(&r->Pricing.quantity, DIST_UNIFORM, 1, g_s_web_order_lineitem.Pricing.quantity, 0, S_WRET_PRICING);
	set_pricing(S_WRET_PRICING, &r->Pricing);
	r->kReasonID = mk_join(S_WRET_REASON_ID, REASON, 1);
	
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
pr_s_web_return(void *pSrc)
{
	struct S_WEB_RETURNS_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_web_returns;
	else
		r = pSrc;
	
	print_start(S_WEB_RETURNS);
	print_id(S_WRET_SITE_ID, r->kSiteID, 1);
	print_key(S_WRET_ORDER_ID,r->kOrderID, 1);
	print_integer(S_WRET_LINE_NUMBER, r->nLineNumber, 1);
	print_id(S_WRET_ITEM_ID, r->kItemID, 1);
	print_id(S_WRET_RETURN_CUST_ID, r->kReturningCustomerID, 1);
	print_id(S_WRET_REFUND_CUST_ID,r->kRefundedCustomerID, 1);
	print_date(S_WRET_RETURN_DATE, r->dtReturnDate.julian, 1);
	print_time(S_WRET_RETURN_TIME, r->kReturnTime, 1);
	print_integer(S_WRET_PRICING, r->Pricing.quantity, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.ext_sales_price, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.ext_tax, 1);
   print_decimal(S_WRET_PRICING, &r->Pricing.fee, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.ext_ship_cost, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.refunded_cash, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.reversed_charge, 1);
	print_decimal(S_WRET_PRICING, &r->Pricing.store_credit, 1);
   print_id(S_WRET_REASON_ID, r->kReasonID, 0);
	print_end(S_WEB_RETURNS);
	
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
ld_s_web_return(void *pSrc)
{
	struct S_WEB_RETURNS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_web_returns;
	else
		r = pSrc;
	
	return(0);
}

