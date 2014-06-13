/*
* $Id: s_catalog_order.c,v 1.19 2007/08/24 22:40:14 jms Exp $
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
* $Log: s_catalog_order.c,v $
* Revision 1.19  2007/08/24 22:40:14  jms
* checking prior to draft 53
*
* Revision 1.18  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.17  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.16  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.15  2006/10/25 01:00:32  jms
* scaling issues
*
* Revision 1.14  2006/08/29 20:24:03  jms
* remove unused variables
*
* Revision 1.13  2006/08/17 21:51:08  jms
* Bug 479
*
* Revision 1.12  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.11  2006/05/09 21:28:37  jms
* Correct linenumber generation
*
* Revision 1.10  2006/05/04 23:34:22  jms
* delete files are missing for sales tables
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
* Revision 1.5  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.4  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
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
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.3  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
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
#include "s_catalog_order.h"
#include "s_catalog_order_lineitem.h"
#include "s_catalog_returns.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "scaling.h"
#include "params.h"
#include "w_web_sales.h"
#include "parallel.h"

struct S_CATALOG_ORDER_TBL g_s_catalog_order;
struct S_CATALOG_ORDER_LINEITEM_TBL g_s_catalog_order_lineitem;
struct S_CATALOG_RETURNS_TBL	g_s_catalog_return;
int nItemIndex;

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
static int
mk_master(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_CATALOG_ORDER_TBL *r;
	int nGiftPct;
	
	if (pDest == NULL)
		r = &g_s_catalog_order;
	else
		r = pDest;


	if (!bInit)
	{
		memset(&g_s_catalog_order, 0, sizeof(struct S_CATALOG_ORDER_TBL));
		bInit = 1;
	}
    
	jtodt(&r->dtOrderDate, getUpdateDate(S_CATALOG_ORDER, kIndex));
	r->kID = getUpdateBase(S_CATALOG_ORDER) + kIndex;
	genrand_integer(&r->nOrderTime , DIST_UNIFORM, 0, (24 * 3600) - 1, 0, S_CORD_ORDER_TIME);
	r->kBillCustomerID = mk_join(S_CORD_BILL_CUSTOMER_ID, CUSTOMER, 1);

	/* most orders are for the ordering customers, some are not */
	genrand_integer(&nGiftPct, DIST_UNIFORM, 0, 99, 0, S_CORD_SHIP_CUSTOMER_ID);
	if (nGiftPct > WS_GIFT_PCT)
		r->kShipCustomerID =
			mk_join (S_CORD_SHIP_CUSTOMER_ID, CUSTOMER, 2);
	else
		r->kShipCustomerID = r->kBillCustomerID;
	r->kShipModeID = mk_join(S_CORD_SHIP_MODE_ID, SHIP_MODE, 1);
	gen_text(&r->szComment[0], (int)(RS_S_CATALOG_ORDER_COMMENT * 0.6), RS_S_CATALOG_ORDER_COMMENT, S_CORD_COMMENT);

   return(0);
}

static int
mk_detail(void *pDest, int nLine, int bPrint)
{
      int nTemp;

		mk_s_catalog_order_lineitem(pDest, nLine);
		if (bPrint)
         pr_s_catalog_order_lineitem(pDest);
      genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, S_CLIN_IS_RETURNED);
      if (nTemp < WR_RETURN_PCT)
      {
         mk_s_catalog_returns(&g_s_catalog_return, nLine);
         if (bPrint)
            pr_s_catalog_returns(&g_s_catalog_return);
      }

	return(0);
}

int
mk_s_catalog_order(void *pDest, ds_key_t kIndex)
{
   int i;

   mk_master(pDest, kIndex);
   genrand_integer(&nItemIndex, DIST_UNIFORM, 1, (int)getIDCount(ITEM), 0, S_CLIN_ITEM_ID);
	for (i=1; i <= 9; i++)
	{
      mk_detail(&g_s_catalog_order_lineitem, i, 1);
   }

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
pr_s_catalog_order(void *pSrc)
{
	struct S_CATALOG_ORDER_TBL *r;

	if (pSrc == NULL)
		r = &g_s_catalog_order;
	else
		r = pSrc;
	
	print_start(S_CATALOG_ORDER);
	print_key(S_CORD_ID, r->kID, 1);
	print_id(S_CORD_BILL_CUSTOMER_ID, r->kBillCustomerID, 1);
	print_id(S_CORD_SHIP_CUSTOMER_ID, r->kShipCustomerID, 1);
	print_date(S_CORD_ORDER_DATE, r->dtOrderDate.julian, 1);
	print_integer(S_CORD_ORDER_TIME, r->nOrderTime, 1);
	print_id(S_CORD_SHIP_MODE_ID, r->kShipModeID, 1);
	print_id(S_CORD_CALL_CENTER_ID, r->kCallCenterID, 1);
	print_varchar(S_CORD_COMMENT, r->szComment, 0);
	print_end(S_CATALOG_ORDER);

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
ld_s_catalog_order(void *pSrc)
{
	struct S_CATALOG_ORDER_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_catalog_order;
	else
		r = pSrc;
	
	return(0);
}

int 
vld_s_catalog_order(int nTable, ds_key_t kRow, int* bPermutation)
{
   int nLineitem,
      i;

   row_skip(S_CATALOG_ORDER, kRow - 1);
   row_skip(S_CATALOG_ORDER_LINEITEM, (kRow - 1)*9);
   row_skip(S_CATALOG_RETURNS, kRow - 1);

   mk_master(NULL, kRow);
   genrand_integer(&nLineitem, DIST_UNIFORM, 1, 9, 0, S_CLIN_LINE_NUMBER);
   genrand_integer(&nItemIndex, DIST_UNIFORM, 1, (int)getIDCount(ITEM), 0, S_CLIN_ITEM_ID);
   for (i=1; i < nLineitem; i++)
      mk_detail(&g_s_catalog_order_lineitem, i, 0);
   print_start(S_CATALOG_ORDER_LINEITEM);
   print_key(0, (kRow - 1) * 9 + nLineitem, 1);
   mk_detail(&g_s_catalog_order_lineitem, nLineitem, 1);

   return(0);
}

