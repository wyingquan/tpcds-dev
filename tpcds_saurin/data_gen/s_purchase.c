/*
* $Id: s_purchase.c,v 1.17 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_purchase.c,v $
* Revision 1.17  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.16  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.15  2006/10/25 01:00:32  jms
* scaling issues
*
* Revision 1.14  2006/08/29 20:24:03  jms
* remove unused variables
*
* Revision 1.13  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.12  2006/05/09 21:25:03  jms
* Correct purchase linenumber generation
*
* Revision 1.11  2006/05/04 23:34:22  jms
* delete files are missing for sales tables
*
* Revision 1.10  2006/03/27 23:36:05  jms
* Problems identified by Meikel 3/27/06
*
* Revision 1.9  2006/03/24 22:38:25  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.8  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.7  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.6  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.5  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
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
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
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
#include "s_purchase.h"
#include "s_pline.h"
#include "s_store_returns.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "r_params.h"
#include "misc.h"
#include "scaling.h"
#include "parallel.h"

struct S_PURCHASE_TBL g_s_purchase;
struct S_PURCHASE_LINEITEM_TBL g_s_purchase_lineitem;
struct S_STORE_RETURNS_TBL g_s_store_return;
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
int
mk_master(void *pDest, ds_key_t kIndex)
{
   static int bInit = 0;
   struct S_PURCHASE_TBL *r;
	
	if (pDest == NULL)
		r = &g_s_purchase;
	else
		r = pDest;


	if (!bInit)
	{
		memset(&g_s_purchase, 0, sizeof(struct S_PURCHASE_TBL));
		bInit = 1;
	}
    
   
   r->kID = kIndex + getUpdateBase(S_PURCHASE);
	r->kStoreID = mk_join(S_PURCHASE_STORE_ID, STORE, 1);
	r->kCustomerID = mk_join(S_PURCHASE_CUSTOMER_ID, CUSTOMER, 1);
	jtodt(&r->dtPurchaseDate, getUpdateDate(S_PURCHASE, kIndex));
	genrand_integer(&r->nRegister, DIST_UNIFORM, 1, 17, 0, S_PURCHASE_REGISTER);
	genrand_integer(&r->nClerk, DIST_UNIFORM, 101, 300, 0, S_PURCHASE_CLERK);
	gen_text(&r->szComment[0], (int)(RS_S_PURCHASE_COMMENT * 0.6), RS_S_PURCHASE_COMMENT, S_PURCHASE_COMMENT);

   return(0);
}

int
mk_detail(int i, int bPrint)
{
   int nTemp;

		mk_s_pline(&g_s_purchase_lineitem, i);
		if (bPrint)
         pr_s_pline(&g_s_purchase_lineitem);
		genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, S_PLINE_IS_RETURNED);
		if (nTemp < WR_RETURN_PCT)
		{
			mk_s_store_returns(&g_s_store_return, 1);
			if (bPrint)
            pr_s_store_returns(&g_s_store_return);
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
pr_s_purchase(void *pSrc)
{
	struct S_PURCHASE_TBL *r;
   char szKey[RS_BKEY + 1];

   if (pSrc == NULL)
		r = &g_s_purchase;
	else
		r = pSrc;
	
	print_start(S_PURCHASE);
	print_key(S_PURCHASE_ID, r->kID, 1);
   mk_bkey(szKey, r->kID, 0);
   mk_bkey(szKey, r->kStoreID, 0);
	print_varchar(S_PURCHASE_STORE_ID, szKey, 1);
   mk_bkey(szKey, r->kCustomerID, 0);
	print_varchar(S_PURCHASE_CUSTOMER_ID, szKey, 1);
	print_date(S_PURCHASE_DATE, r->dtPurchaseDate.julian, 1);
	print_integer(S_PURCHASE_TIME, r->nPurchaseTime, 1);
	print_integer(S_PURCHASE_REGISTER, r->nRegister, 1);
	print_integer(S_PURCHASE_CLERK, r->nClerk, 1);
	print_varchar(S_PURCHASE_COMMENT, r->szComment, 0);
	print_end(S_PURCHASE);

	return(0);
}

int
mk_s_purchase(void *pDest, ds_key_t kIndex)
{
   int i;

   mk_master(pDest, kIndex);
   genrand_integer(&nItemIndex, DIST_UNIFORM, 1, (int)getIDCount(ITEM), 0, S_PLINE_ITEM_ID);
	for (i=1; i <= 12; i++)
	{
      mk_detail(i, 1);
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
ld_s_purchase(void *pSrc)
{
	struct S_PURCHASE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_purchase;
	else
		r = pSrc;
	
	return(0);
}

int 
vld_s_purchase(int nTable, ds_key_t kRow, int* bPermutation)
{
   int nLineitem,
      i;

   row_skip(S_PURCHASE, kRow - 1);
   row_skip(S_PURCHASE_LINEITEM, (kRow - 1));
   row_skip(S_STORE_RETURNS, (kRow - 1));

   mk_master(NULL, kRow);
   genrand_integer(&nLineitem, DIST_UNIFORM, 1, 12, 0, S_PLINE_NUMBER);
   genrand_integer(&nItemIndex, DIST_UNIFORM, 1, (int)getIDCount(ITEM), 0, S_PLINE_ITEM_ID);
   for (i=1; i < nLineitem; i++)
      mk_detail(i, 0);
   print_start(S_PURCHASE_LINEITEM);
   print_key(0, (kRow - 1) * 12 + nLineitem, 1);
   mk_detail(i, 1);

   return(0);
}

