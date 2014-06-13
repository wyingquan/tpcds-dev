/*
* $Id: s_catalog_order_lineitem.c,v 1.19 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_catalog_order_lineitem.c,v $
* Revision 1.19  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.18  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.17  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.16  2007/02/23 22:27:27  jms
* Bug 515
*
* Revision 1.15  2006/08/17 21:22:51  jms
* Bug 480
*
* Revision 1.14  2006/07/18 23:03:26  jms
* Bug 473
*
* Revision 1.13  2006/06/02 19:25:05  jms
* add per-item ship cost to source catalog and web lineitems
*
* Revision 1.12  2006/05/12 19:08:11  jms
* Bug 449: missing columns in s_catalog_returns
*
* Revision 1.11  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.10  2006/05/09 21:28:37  jms
* Correct linenumber generation
*
* Revision 1.9  2006/04/10 23:37:31  jms
* Bug 414: each id in an update set should be unique
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
* Revision 1.4  2005/11/11 18:58:37  jms
* add link between lineitem tables in the source shcema and the promotion table in the warehouse schema
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
* Revision 1.5  2004/10/20 21:30:01  jms
* add missing static declarations
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
#include "s_catalog_order_lineitem.h"
#include "s_catalog_order.h"
#include "w_web_sales.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "pricing.h"
#include "parallel.h"
#include "permute.h"
#include "scaling.h"
#include "constants.h"
#include "scd.h"

extern struct S_CATALOG_ORDER_LINEITEM_TBL g_s_catalog_order_lineitem;
extern struct S_CATALOG_ORDER_TBL g_s_catalog_order;
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
mk_s_catalog_order_lineitem(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_CATALOG_ORDER_LINEITEM_TBL *r;
	static decimal_t dMin,
		dMax;
	static date_t dtMax;
	int nShipLag;
   static int *pItemPermutation;
	
	if (pDest == NULL)
		r = &g_s_catalog_order_lineitem;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_catalog_order_lineitem, 0, sizeof(struct S_CATALOG_ORDER_LINEITEM_TBL));
		strtodec(&dMin, "1.00");
		strtodec(&dMax, "1000.00");
      pItemPermutation = makePermutation(NULL, (int)getIDCount(ITEM), S_CLIN_PERMUTE);
      strtodt(&dtMax, TODAYS_DATE);
		bInit = 1;
	}
	
	r->kOrderID = g_s_catalog_order.kID;
	r->kLineNumber = kIndex;
   nItemIndex += 1;
   if (nItemIndex > getIDCount(ITEM))
      nItemIndex = 1;

   /*
    * select a unique item, and then map to the appropriate business key
	*/
	r->kItemID = getPermutationEntry(pItemPermutation, nItemIndex);
	r->kItemID = getFirstSK(r->kItemID);

	r->kPromotionID = mk_join(S_CLIN_PROMOTION_ID, PROMOTION, 1);
	r->kWarehouseID = mk_join(S_CLIN_WAREHOUSE_ID, WAREHOUSE, 1);
	/*
	 * an order cannot ship until its has been made
	 * an order cannot be recorded as shipping if its is outside the date window
	 */
	genrand_integer(&nShipLag, DIST_UNIFORM, 0, 60, 0, S_CLIN_SHIP_DATE);
	jtodt(&r->dtShipDate, g_s_catalog_order.dtOrderDate.julian + nShipLag);
	if (r->dtShipDate.julian > dtMax.julian)
		r->dtShipDate.julian = -1;
	r->kCatalogPage = mk_join(S_CLIN_CATALOG_PAGE_ID, CATALOG_PAGE, g_s_catalog_order.dtOrderDate.julian);
	r->kCatalogID = getCatalogNumberFromPage(r->kCatalogPage);
	// genrand_integer(&r->Pricing.quantity, DIST_UNIFORM, 1, 100, 0, S_CLIN_QUANTITY);
	set_pricing(S_CLIN_PRICING, &r->Pricing);
	
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
pr_s_catalog_order_lineitem(void *pSrc)
{
	struct S_CATALOG_ORDER_LINEITEM_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_catalog_order_lineitem;
	else
		r = pSrc;
	
	print_start(S_CATALOG_ORDER_LINEITEM);
	print_key(S_CLIN_ORDER_ID, r->kOrderID, 1);
	print_key(S_CLIN_LINE_NUMBER, r->kLineNumber, 1);
	print_id(S_CLIN_ITEM_ID, r->kItemID, 1);
   print_id(S_CLIN_PROMOTION_ID, r->kPromotionID, 1);
	print_integer(S_CLIN_QUANTITY, r->Pricing.quantity, 1);
	print_decimal(S_CLIN_PRICING, &r->Pricing.sales_price, 1);
	print_decimal(S_CLIN_COUPON_AMT, &r->Pricing.coupon_amt, 1);
	print_id(S_CLIN_WAREHOUSE_ID, r->kWarehouseID, 1);
	print_date(S_CLIN_SHIP_DATE, r->dtShipDate.julian, 1);
	print_key(S_CLIN_CATALOG_ID, r->kCatalogID, 1);
	print_key(S_CLIN_CATALOG_PAGE_ID, r->kCatalogPage, 1);
	print_decimal(S_CLIN_SHIP_COST, &r->Pricing.ship_cost, 0);
	print_end(S_CATALOG_ORDER_LINEITEM);

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
ld_s_catalog_order_lineitem(void *pSrc)
{
	struct S_CATALOG_ORDER_LINEITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_catalog_order_lineitem;
	else
		r = pSrc;
	
	return(0);
}

