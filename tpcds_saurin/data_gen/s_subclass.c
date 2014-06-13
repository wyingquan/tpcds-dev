/*
* $Id: s_subclass.c,v 1.3 2006/03/09 23:00:09 jms Exp $
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
* $Log: s_subclass.c,v $
* Revision 1.3  2006/03/09 23:00:09  jms
* dependency cleanup
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
#include "s_subclass.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"

struct S_SUBCLASS_TBL g_s_subclass;

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
mk_s_subclass(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_SUBCLASS_TBL *r;
	
	if (pDest == NULL)
		r = &g_s_subclass;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_subclass, 0, sizeof(struct S_SUBCLASS_TBL));
		bInit = 1;
	}
	
	r->kID = kIndex;
	r->kClassID = mk_join(S_SUBC_CLASS_ID, S_CLASS, 1);
	mk_word(r->szName, "Syllables", kIndex, RS_S_SUBC_NAME, S_SUBC_NAME);
	gen_text(r->szDesc, 1, RS_S_SUBC_DESC, S_SUBC_DESC);
	row_stop(S_SUBCLASS);
	
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
pr_s_subclass(void *pSrc)
{
	struct S_SUBCLASS_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_subclass;
	else
		r = pSrc;
	
	print_start(S_SUBCLASS);
	print_key(S_SUBC_ID, r->kID,  1);
	print_key(S_SUBC_CLASS_ID, r->kClassID,  1);
	print_varchar(S_SUBC_NAME, r->szName,  1);
	print_varchar(S_SUBC_DESC, r->szDesc,  0);
	print_end(S_SUBCLASS);
	
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
ld_s_subclass(void *pSrc)
{
	struct S_SUBCLASS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_subclass;
	else
		r = pSrc;
	
	return(0);
}

