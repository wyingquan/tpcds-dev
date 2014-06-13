/*
* $Id: s_item.c,v 1.13 2007/10/02 16:30:34 jms Exp $
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
* $Log: s_item.c,v $
* Revision 1.13  2007/10/02 16:30:34  jms
* null out g_OldValues
*
* Revision 1.12  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.11  2007/07/31 06:07:39  jms
* bug 546: s_promotion
*
* Revision 1.10  2007/07/25 19:41:47  jms
* bug 546: remove duplicate printing
*
* Revision 1.9  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.8  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.7  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.6  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.5  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.3  2005/10/31 19:28:45  jms
* changes to the source schema to move the views forward
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.6  2004/10/27 22:51:51  jms
* Source data corrections from Ruth's research
*
* Revision 1.5  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
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
#include "s_item.h"
#include "w_item.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"
#include "permute.h"
#include "scaling.h"
#include "scd.h"
#include "tdef_functions.h"
#include "r_params.h"

extern struct W_ITEM_TBL g_w_item;
extern struct W_ITEM_TBL g_OldValues;
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
mk_s_item (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(ITEM),
      S_ITEM_PERMUTE);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_item(NULL, getSKFromID(kIndex, S_ITEM_ID));
   row_stop(ITEM);

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
pr_s_item(void *pSrc)
{
	struct W_ITEM_TBL *r;

	if (pSrc == NULL)
		r = &g_w_item;
	else
		r = pSrc;
	
	print_start(S_ITEM);
	print_varchar(S_ITEM_ID, r->i_item_id, 1);
	print_varchar(S_ITEM_DESC, r->i_item_desc, 1);
	print_decimal(S_ITEM_LIST_PRICE, &r->i_current_price, 1);
	print_decimal(S_ITEM_WHOLESALE_COST, &r->i_wholesale_cost, 1);
	print_varchar(S_ITEM_SIZE, r->i_size, 1);
	print_varchar(S_ITEM_FORMULATION, r->i_formulation, 1);
	print_varchar(S_ITEM_FLAVOR, r->i_color, 1);
	print_varchar(S_ITEM_UNITS, r->i_units, 1);
	print_varchar(S_ITEM_CONTAINER, r->i_container, 1);
	print_key(S_ITEM_MANAGER_ID, r->i_manager_id, 0);
	print_end(S_ITEM);
	
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
ld_s_item(void *pSrc)
{
	struct W_ITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_item;
	else
		r = pSrc;
	
	return(0);
}

int
vld_s_item(int nTable, ds_key_t kRow, int *Permutation)
{
   static int bInit = 0;
   static int *pPermutation;
   table_func_t *pTF = getTdefFunctionsByNumber(ITEM);

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(ITEM),
      S_ITEM_PERMUTE);
      bInit = 1;
   }

   memset(&g_OldValues, 0, sizeof(struct W_ITEM_TBL));
   pTF->validate(S_ITEM, kRow, pPermutation);

   return(0);
}


