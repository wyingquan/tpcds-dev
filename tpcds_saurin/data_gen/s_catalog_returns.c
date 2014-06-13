/*
* $Id: s_catalog_returns.c,v 1.13 2007/08/24 22:40:14 jms Exp $
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
* $Log: s_catalog_returns.c,v $
* Revision 1.13  2007/08/24 22:40:14  jms
* checking prior to draft 53
*
* Revision 1.12  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.11  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.10  2007/01/12 19:08:02  jms
* Include fix suggested by Doug Johnson
*
* Revision 1.9  2006/05/12 19:08:11  jms
* Bug 449: missing columns in s_catalog_returns
*
* Revision 1.8  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.7  2006/03/17 22:55:39  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.5  2006/03/09 00:53:49  jms
* Bug 402: assorted data errors in source schema
*
* Revision 1.4  2005/11/11 21:24:41  jms
* add return time to all channels in source schema
*
* Revision 1.3  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
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
#include "s_catalog_returns.h"
#include "s_catalog_order.h"
#include "s_catalog_order_lineitem.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_CATALOG_RETURNS_TBL g_s_catalog_returns;
extern struct S_CATALOG_ORDER_LINEITEM_TBL g_s_catalog_order_lineitem;
extern struct S_CATALOG_ORDER_TBL g_s_catalog_order;

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
mk_s_catalog_returns(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_CATALOG_RETURNS_TBL *r;
	int nReturnLag;
	
	
	if (pDest == NULL)
		r = &g_s_catalog_returns;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_catalog_returns, 0, sizeof(struct S_CATALOG_RETURNS_TBL));
		bInit = 1;
	}

	genrand_integer(&nReturnLag, DIST_UNIFORM, 0, 60, 0, S_CRET_DATE);
	r->kReturnTime = mk_join(S_CRET_TIME, TIME, 1);
   if (g_s_catalog_order_lineitem.dtShipDate.julian == -1)
      r->dtReturnDate.julian = -1;
   else
      jtodt(&r->dtReturnDate, g_s_catalog_order_lineitem.dtShipDate.julian + nReturnLag);
	r->kCallCenterID = mk_join(S_CRET_CALL_CENTER_ID, CALL_CENTER, 1);
	r->kItemID = g_s_catalog_order_lineitem.kItemID;
	r->kReasonID = mk_join(S_CRET_REASON_ID, REASON, 1);
	r->kOrderID = g_s_catalog_order.kID;
	r->kLineNumber = kIndex;
	r->kItemID = g_s_catalog_order_lineitem.kItemID;
	r->kReturnCustomerID= g_s_catalog_order.kShipCustomerID;
	r->kRefundCustomerID = g_s_catalog_order.kShipCustomerID;
   r->Pricing = g_s_catalog_order_lineitem.Pricing;
   genrand_integer(&r->Pricing.quantity, DIST_UNIFORM, 1, g_s_catalog_order_lineitem.Pricing.quantity, 0, S_CRET_PRICING);
   set_pricing(S_CRET_PRICING, &r->Pricing);
	r->kShipModeID = mk_join (S_CRET_SHIPMODE_ID, SHIP_MODE, 1);
	r->kWarehouseID = mk_join (S_CRET_WAREHOUSE_ID, WAREHOUSE, 1);
   r->kCatalogPageID = g_s_catalog_order_lineitem.kCatalogPage;
	
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
pr_s_catalog_returns(void *pSrc)
{
	struct S_CATALOG_RETURNS_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_catalog_returns;
	else
		r = pSrc;
	
	print_start(S_CATALOG_RETURNS);
   print_id(S_CRET_CALL_CENTER_ID, r->kCallCenterID, 1);
	print_key(S_CRET_ORDER_ID, r->kOrderID, 1);
	print_key(S_CRET_LINE_NUMBER, r->kLineNumber, 1);
	print_id(S_CRET_ITEM_ID, r->kItemID, 1);
	print_id(S_CRET_RETURN_CUSTOMER_ID, r->kReturnCustomerID, 1);
	print_id(S_CRET_REFUND_CUSTOMER_ID, r->kRefundCustomerID, 1);
	print_date(S_CRET_DATE, r->dtReturnDate.julian, 1);
	print_time(S_CRET_TIME, r->kReturnTime, 1);
	print_integer(S_CRET_QUANTITY, r->Pricing.quantity, 1);
	print_decimal(S_CRET_AMOUNT, &r->Pricing.net_paid, 1);
	print_decimal(S_CRET_TAX, &r->Pricing.ext_tax, 1);
   print_decimal(S_CRET_FEE, &r->Pricing.fee, 1);
	print_decimal(S_CRET_SHIP_COST, &r->Pricing.ext_ship_cost, 1);
   print_decimal(S_CRET_REFUNDED_CASH, &r->Pricing.refunded_cash, 1);
   print_decimal(S_CRET_REVERSED_CHARGE, &r->Pricing.reversed_charge, 1);
   print_decimal(S_CRET_MERCHANT_CREDIT, &r->Pricing.store_credit, 1);
   print_id(S_CRET_REASON_ID, r->kReasonID, 1);
   print_id(S_CRET_SHIPMODE_ID, r->kShipModeID, 1);
   print_id(S_CRET_WAREHOUSE_ID, r->kWarehouseID, 1);
   print_id(S_CRET_CATALOG_PAGE_ID, r->kCatalogPageID, 0);
   print_end(S_CATALOG_RETURNS);
   
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
ld_s_catalog_returns(void *pSrc)
{
	struct S_CATALOG_RETURNS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_catalog_returns;
	else
		r = pSrc;
	
	return(0);
}

