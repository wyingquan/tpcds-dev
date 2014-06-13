/*
* $Id: w_reason.c,v 1.4 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_reason.c,v $
* Revision 1.4  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.3  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "w_reason.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_REASON_TBL g_w_reason;

/*
* mk_reason
*/
int
mk_w_reason (void* row, ds_key_t index)
{
	int res = 0;
	static int bInit = 0;
	struct W_REASON_TBL *r;
   tdef *pTdef = getSimpleTdefsByNumber(REASON);
	
	if (row == NULL)
		r = &g_w_reason;
	else
		r = row;
	
	if (!bInit)
	{
		memset(&g_w_reason, 0, sizeof(struct W_REASON_TBL));
		bInit = 1;
	}
	
	nullSet(&pTdef->kNullBitMap, R_NULLS);
	r->r_reason_sk = index;
	mk_bkey(&r->r_reason_id[0], index, R_REASON_ID);
	dist_member (&r->r_reason_description, "return_reasons", (int) index, 1);
	
	
	return (res);
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
pr_w_reason(void *row)
{
	struct W_REASON_TBL *r;
	
	if (row == NULL)
		r = &g_w_reason;
	else
		r = row;
	
	print_start(REASON);
	print_key(R_REASON_SK, r->r_reason_sk, 1);
	print_varchar(R_REASON_ID, r->r_reason_id, 1);
	print_varchar(R_REASON_DESCRIPTION, r->r_reason_description, 0);
	print_end(REASON);
	
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
ld_w_reason(void *pSrc)
{
	struct W_REASON_TBL *r;
	
	if (pSrc == NULL)
		r = &g_w_reason;
	else
		r = pSrc;
	
	return(0);
}

