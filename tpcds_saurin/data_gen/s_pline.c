/*
* $Id: s_pline.c,v 1.16 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_pline.c,v $
* Revision 1.16  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.15  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.14  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.13  2006/06/21 19:14:04  jms
* Bug  461
*
* Revision 1.12  2006/05/09 21:25:03  jms
* Correct purchase linenumber generation
*
* Revision 1.11  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.10  2006/03/25 00:42:46  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.9  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.8  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.7  2006/01/16 23:59:23  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.6  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.5  2005/11/11 18:58:37  jms
* add link between lineitem tables in the source shcema and the promotion table in the warehouse schema
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/10/31 19:28:45  jms
* changes to the source schema to move the views forward
*
* Revision 1.2  2004/11/24 23:54:20  jms
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
* Revision 1.3  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.2  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "s_pline.h"
#include "s_purchase.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"
#include "scaling.h"
#include "permute.h"
#include "scd.h"

struct S_PURCHASE_LINEITEM_TBL g_s_pline;
extern struct S_PURCHASE_TBL g_s_purchase;
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
mk_s_pline(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_PURCHASE_LINEITEM_TBL *r;
	static decimal_t dMin,
		dMax;
   static int *pItemPermutation,
      nItemIDCount;

	if (pDest == NULL)
		r = &g_s_pline;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_pline, 0, sizeof(struct S_PURCHASE_LINEITEM_TBL));
		strtodec(&dMin, "1.00");
		strtodec(&dMax, "1000.00");
      /*
       * need to assure that a given item only appears in a single lineitem within an order
       * use adjacent orders from within a permutation of possible values;
       * since item is an SCD, use the item count
       */
      nItemIDCount = (int)getIDCount(ITEM);
      pItemPermutation = makePermutation(NULL, nItemIDCount, S_PLINE_PERMUTE);
		bInit = 1;
	}
	
	r->kPurchaseID = g_s_purchase.kID;
	r->kLineNumber = kIndex;
   nItemIndex += 1;
   if (nItemIndex > nItemIDCount)
      nItemIndex = 1;

	/*
    * pick the next entry in the permutation, to assure uniqueness within order
    * shift to SK value to align with printID() expectations
    */
   r->kItemID = getPermutationEntry(pItemPermutation, nItemIndex);
   r->kItemID = getFirstSK(r->kItemID);

	r->kPromotionID = mk_join(S_PLINE_PROMOTION_ID, PROMOTION, 1);
	genrand_integer(&r->Pricing.quantity, DIST_UNIFORM, PLINE_MIN_QUANTITY, PLINE_MAX_QUANTITY, 0, S_PLINE_QUANTITY);
	set_pricing(S_PLINE_PRICING, &r->Pricing);
	gen_text(r->szComment, 1, RS_S_PLINE_COMMENT, S_PLINE_COMMENT);
	/* row_stop(S_PURCHASE_LINEITEM); */
	
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
pr_s_pline(void *pSrc)
{
	struct S_PURCHASE_LINEITEM_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_pline;
	else
		r = pSrc;
	
	print_start(S_PURCHASE_LINEITEM);
	print_key(S_PLINE_PURCHASE_ID, r->kPurchaseID, 1);
	print_key(S_PLINE_NUMBER, r->kLineNumber, 1);
	print_id(S_PLINE_ITEM_ID, r->kItemID, 1);
	print_id(S_PLINE_PROMOTION_ID, r->kPromotionID, 1);
	print_integer(S_PLINE_QUANTITY, r->Pricing.quantity, 1);
	print_decimal(S_PLINE_SALE_PRICE, &r->Pricing.sales_price, 1);
	print_decimal(S_PLINE_COUPON_AMT, &r->Pricing.coupon_amt, 1);
	print_varchar(S_PLINE_COMMENT, r->szComment,0);
	print_end(S_PURCHASE_LINEITEM);
	
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
ld_s_pline(void *pSrc)
{
	struct S_PURCHASE_LINEITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_pline;
	else
		r = pSrc;
	
	return(0);
}

