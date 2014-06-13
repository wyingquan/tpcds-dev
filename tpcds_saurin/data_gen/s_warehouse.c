/*
* $Id: s_warehouse.c,v 1.8 2007/05/23 18:11:59 jms Exp $
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
* $Log: s_warehouse.c,v $
* Revision 1.8  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.7  2006/06/06 21:41:15  jms
* initial checkin of revised update scaling
*
* Revision 1.6  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.5  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.3  2005/04/21 17:56:04  jms
* changes to allow source data to load
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
#include "s_warehouse.h"
#include "w_warehouse.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"
#include "permute.h"
#include "scaling.h"

struct W_WAREHOUSE_TBL g_w_warehouse;

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
mk_s_warehouse (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(WAREHOUSE), S_WRHS_ID);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_warehouse(NULL, kIndex);

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
pr_s_warehouse(void *pSrc)
{
	struct W_WAREHOUSE_TBL *r;

   if (pSrc == NULL)
		r = &g_w_warehouse;
	else
		r = pSrc;
	
	print_start(S_WAREHOUSE);
	print_varchar(W_WAREHOUSE_ID, r->w_warehouse_id, 1);
	print_varchar(W_WAREHOUSE_NAME, &r->w_warehouse_name[0], 1);
	print_integer(W_WAREHOUSE_SQ_FT, r->w_warehouse_sq_ft, 0);
	print_end(S_WAREHOUSE);
	
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
ld_s_warehouse(void *pSrc)
{
	struct W_WAREHOUSE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_warehouse;
	else
		r = pSrc;
	
	return(0);
}

