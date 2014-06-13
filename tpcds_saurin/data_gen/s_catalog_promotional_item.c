/*
* $Id: s_catalog_promotional_item.c,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: s_catalog_promotional_item.c,v $
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 18:07:21  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
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
#include "s_catalog_promotional_item.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"

struct S_CATALOG_PROMOTIONAL_ITEM_TBL g_s_catalog_promotional_item;

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
mk_s_catalog_promotional_item(void *pDest, ds_key_t kIndex)
{
	struct S_CATALOG_PROMOTIONAL_ITEM_TBL *r;
	static int bInit = 0;
	
	if (pDest == NULL)
		r = &g_s_catalog_promotional_item;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_catalog_promotional_item, 0, sizeof(struct S_CATALOG_PROMOTIONAL_ITEM_TBL));
		bInit = 1;
	}
	r->catalog_promotional_item_catalog_number = mk_join(S_CATALOG_PROMOTIONAL_ITEM_CATALOG_NUMBER,S_CATALOG, 1);
	genrand_integer(&r->catalog_promotional_item_catalog_page_number, DIST_UNIFORM, 1, PAGES_PER_CATALOG, 0, S_CATALOG_PROMOTIONAL_ITEM_CATALOG_PAGE_NUMBER);
	r->catalog_promotional_item_item_id = mk_join(S_CATALOG_PROMOTIONAL_ITEM_ITEM_ID, S_ITEM, 1);
	r->catalog_promotional_item_promotion_id = kIndex / ITEMS_PER_PROMOTION;
	
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
pr_s_catalog_promotional_item(void *pSrc)
{
	struct S_CATALOG_PROMOTIONAL_ITEM_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_catalog_promotional_item;
	else
		r = pSrc;
	
	print_start(S_CATALOG_PROMOTIONAL_ITEM);
	print_key(S_CATALOG_PROMOTIONAL_ITEM_CATALOG_NUMBER, r->catalog_promotional_item_catalog_number, 1);
	print_key(S_CATALOG_PROMOTIONAL_ITEM_CATALOG_PAGE_NUMBER, r->catalog_promotional_item_catalog_page_number, 1);
	print_key(S_CATALOG_PROMOTIONAL_ITEM_ITEM_ID, r->catalog_promotional_item_item_id, 1);
	print_key(S_CATALOG_PROMOTIONAL_ITEM_PROMOTION_ID, r->catalog_promotional_item_promotion_id, 0);
	print_end(S_CATALOG_PROMOTIONAL_ITEM);
	
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
ld_s_catalog_promotional_item(void *pSrc)
{
	struct S_CATALOG_PROMOTIONAL_ITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_catalog_promotional_item;
	else
		r = pSrc;
	
	return(0);

}
