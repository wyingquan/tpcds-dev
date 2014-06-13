/*
* $Id: s_web_order_lineitem.c,v 1.15 2007/07/31 16:35:43 jms Exp $
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
* $Log: s_web_order_lineitem.c,v $
* Revision 1.15  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.14  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.13  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.12  2007/02/23 22:27:27  jms
* Bug 515
*
* Revision 1.11  2006/08/17 20:44:50  jms
* Bug 481
*
* Revision 1.10  2006/06/02 19:25:05  jms
* add per-item ship cost to source catalog and web lineitems
*
* Revision 1.9  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.8  2006/05/09 21:28:37  jms
* Correct linenumber generation
*
* Revision 1.7  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.6  2006/03/28 19:03:23  jms
* additional testing of updates from Meikel
*
* Revision 1.5  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.4  2005/11/11 18:58:37  jms
* add link between lineitem tables in the source shcema and the promotion table in the warehouse schema
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
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
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
#include "s_web_order_lineitem.h"
#include "s_web_order.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "decimal.h"
#include "w_web_sales.h"
#include "pricing.h"
#include "parallel.h"
#include "permute.h"
#include "scaling.h"
#include "scd.h"

struct S_WEB_ORDER_LINEITEM_TBL g_s_web_order_lineitem;
extern struct S_WEB_ORDER_TBL g_s_web_order;
extern int nItemIndex;

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
mk_s_web_order_lineitem(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_WEB_ORDER_LINEITEM_TBL *r;
	static decimal_t dMin,
		dMax;
	static date_t dtMax;
	int nShipLag;
   static int *pItemPermutation,
      nItemCount;
	
	if (pDest == NULL)
		r = &g_s_web_order_lineitem;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_web_order_lineitem, 0, sizeof(struct S_WEB_ORDER_LINEITEM_TBL));
		strtodec(&dMin, "1.00");
		strtodec(&dMax, "1000.00");
		strtodt(&dtMax, TODAYS_DATE);
      nItemCount = (int)getIDCount(ITEM);
      pItemPermutation = makePermutation(NULL, nItemCount, S_WLIN_PERMUTE);
		bInit = 1;
	}
	
	r->kOrderID = g_s_web_order.kID;
	r->kLineNumber = kIndex;
   if (++nItemIndex  > nItemCount)
      nItemIndex += 1;

   /*
    * select a unique item, and then map to the appropriate business key
	*/
	r->kItemID = getPermutationEntry(pItemPermutation, nItemIndex);
	r->kItemID = getFirstSK(r->kItemID);

	r->kPromotionID = mk_join(S_WLIN_PROMOTION_ID, PROMOTION, 1);
	r->kWarehouseID = mk_join(S_WLIN_WAREHOUSE_ID, WAREHOUSE, 1);
	/*
	 * an order cannot ship until its has been made
	 * an order cannot be recorded as shipping if its is outside the date window
	 */
	genrand_integer(&nShipLag, DIST_UNIFORM, 0, 60, 0, S_WLIN_SHIP_DATE);
	r->dtShipDate.julian = g_s_web_order.dtOrderDate.julian + nShipLag;
	if (r->dtShipDate.julian > dtMax.julian)
		r->dtShipDate.julian = -1;
	r->kWebPageID = mk_join(S_WLIN_WEB_PAGE_ID, WEB_PAGE, 1);
	set_pricing(S_WLIN_PRICING, &r->Pricing);
	
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
pr_s_web_order_lineitem(void *pSrc)
{
	struct S_WEB_ORDER_LINEITEM_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_web_order_lineitem;
	else
		r = pSrc;
	
	print_start(S_WEB_ORDER_LINEITEM);
	print_key(S_WLIN_ID, r->kOrderID, 1);
	print_key(S_WLIN_LINE_NUMBER, r->kLineNumber, 1);
	print_id(S_WLIN_ITEM_ID, r->kItemID, 1);
	print_id(S_WLIN_PROMOTION_ID, r->kPromotionID, 1);
	print_integer(S_WLIN_QUANTITY, r->Pricing.quantity, 1);
	print_decimal(S_WLIN_PRICING, &r->Pricing.sales_price, 1);
	print_decimal(S_WLIN_COUPON_AMT, &r->Pricing.coupon_amt, 1);
	print_id(S_WLIN_WAREHOUSE_ID, r->kWarehouseID, 1);
	print_date(S_WLIN_SHIP_DATE, r->dtShipDate.julian, 1);
	print_decimal(S_WLIN_SHIP_COST, &r->Pricing.ship_cost, 1);
	print_id(S_WLIN_WEB_PAGE_ID, r->kWebPageID, 0);
	print_end(S_WEB_ORDER_LINEITEM);
	
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
ld_s_web_order_lineitem(void *pSrc)
{
	struct S_WEB_ORDER_LINEITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_web_order_lineitem;
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
vld_s_web_order_lineitem(int nTable, ds_key_t kRow, int *Permutation)
{
	row_skip(nTable, kRow - 1);
	row_skip(S_WEB_RETURNS, (kRow - 1) );
   /*
	mk_master(NULL, kRow);
	genrand_integer(&nMaxLineitem, DIST_UNIFORM, 8, 16, 9, CS_ORDER_NUMBER);
	genrand_integer(&nLineitem, DIST_UNIFORM, 1, nMaxLineitem, 0, CS_PRICING_QUANTITY);
	for (i = 1; i < nLineitem; i++)
	{
		mk_detail(NULL, 0);
	}
   mk_detail(NULL, 1);
   */

	return(0);
}

