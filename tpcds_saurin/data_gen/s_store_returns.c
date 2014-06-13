/*
* $Id: s_store_returns.c,v 1.13 2007/09/10 18:10:36 jms Exp $
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
* $Log: s_store_returns.c,v $
* Revision 1.13  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.12  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.11  2006/11/14 19:09:06  jms
* Bug #517
*
* Revision 1.10  2006/06/21 00:18:34  jms
* Bug 468
*
* Revision 1.9  2006/05/04 23:09:52  jms
* Bug 439: s_sret_reason_id should be a business key
*
* Revision 1.8  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.7  2006/03/25 00:42:47  jms
* Problems identified by Meikel 3/21/06
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
* Revision 1.2  2004/11/24 23:54:20  jms
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
#include "s_store_returns.h"
#include "s_purchase.h"
#include "s_pline.h"
#include "s_purchase.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_STORE_RETURNS_TBL g_s_store_returns;
extern struct S_PURCHASE_TBL g_s_purchase;
extern struct S_PURCHASE_LINEITEM_TBL g_s_purchase_lineitem;

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
mk_s_store_returns(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_STORE_RETURNS_TBL *r;
	int nReturnLag;
	
	if (pDest == NULL)
		r = &g_s_store_returns;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_store_returns, 0, sizeof(struct S_STORE_RETURNS_TBL));
		bInit = 1;
	}
	
	genrand_integer(&nReturnLag, DIST_UNIFORM, 0, 60, 0, S_SRET_RETURN_DATE);
   if (g_s_purchase.dtPurchaseDate.julian == -1)
      r->dtReturnDate.julian = -1;
   else
      jtodt(&r->dtReturnDate, g_s_purchase.dtPurchaseDate.julian + nReturnLag);
   r->kReturnTime = mk_join(S_SRET_RETURN_TIME, TIME, 1);
   r->kReasonID = mk_join(S_SRET_REASON_ID, REASON, 1);
	r->Pricing = g_s_purchase_lineitem.Pricing;
   if (g_s_purchase_lineitem.Pricing.quantity != -1)
	   genrand_integer(&r->Pricing.quantity, DIST_UNIFORM, 1, g_s_purchase_lineitem.Pricing.quantity, 0, S_SRET_PRICING);
   else
      r->Pricing.quantity = -1;
	set_pricing(S_SRET_PRICING, &r->Pricing);
	
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
pr_s_store_returns(void *pSrc)
{
	struct S_STORE_RETURNS_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_store_returns;
	else
		r = pSrc;
	
	print_start(S_STORE_RETURNS);
	print_id(S_SRET_STORE_ID, g_s_purchase.kStoreID, 1);
	print_key(S_SRET_PURCHASE_ID, g_s_purchase.kID, 1);
	print_key(S_SRET_LINENUMBER, g_s_purchase_lineitem.kLineNumber, 1);
	print_id(S_SRET_ITEM_ID, g_s_purchase_lineitem.kItemID, 1);
	print_id(S_SRET_CUSTOMER_ID, g_s_purchase.kCustomerID, 1);
	print_date(S_SRET_RETURN_DATE, r->dtReturnDate.julian, 1);
	print_time(S_SRET_RETURN_TIME, r->kReturnTime, 1);
	print_key(S_SRET_TICKET_NUMBER, g_s_purchase.kID, 1);
	print_integer(S_SRET_RETURN_QUANTITY, r->Pricing.quantity, 1);
	print_decimal(S_SRET_RETURN_AMT, &r->Pricing.sales_price, 1);
	print_decimal(S_SRET_RETURN_TAX, &r->Pricing.ext_tax, 1);
	print_decimal(S_SRET_RETURN_FEE, &r->Pricing.fee, 1);
	print_decimal(S_SRET_RETURN_SHIP_COST, &r->Pricing.ext_ship_cost, 1);
	print_decimal(S_SRET_REFUNDED_CASH, &r->Pricing.refunded_cash, 1);
	print_decimal(S_SRET_REVERSED_CHARGE, &r->Pricing.reversed_charge, 1);
	print_decimal(S_SRET_MERCHANT_CREDIT, &r->Pricing.store_credit, 1);
	print_id(S_SRET_REASON_ID, r->kReasonID, 0);
	print_end(S_STORE_RETURNS);
	
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
ld_s_store_returns(void *pSrc)
{
	struct S_STORE_RETURNS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_store_returns;
	else
		r = pSrc;
	
	return(0);
}

