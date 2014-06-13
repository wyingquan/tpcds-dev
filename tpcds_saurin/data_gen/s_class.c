/*
* $Id: s_class.c,v 1.3 2006/03/09 23:00:09 jms Exp $
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
* $Log: s_class.c,v $
* Revision 1.3  2006/03/09 23:00:09  jms
* dependency cleanup
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
#include "s_class.h"
#include "print.h"
#include "build_support.h"
#include "columns.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"

struct S_CLASS_TBL g_s_class;

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
* TODO: 
* 20031022 jms RNGUsage for descrition is an estimate
*/
int
mk_s_class(void *pDest, ds_key_t kIndex)
{
	struct S_CLASS_TBL *r;
	static int bInit = 0;
	
	if (pDest == NULL)
		r = &g_s_class;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_class, 0, sizeof(struct S_CLASS_TBL));
		bInit = 1;
	}
	
	r->id = kIndex;
	r->subcat_id = mk_join(S_CLASS_SUBCAT_ID, S_SUBCATEGORY, 1);
	gen_text(r->desc, S_CLASS_DESC_MIN, RS_CLASS_DESC, S_CLASS_DESC);
	row_stop(S_CLASS);

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
pr_s_class(void *pSrc)
{
	struct S_CLASS_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_class;
	else
		r = pSrc;
	
	print_start(S_CLASS);
	print_key(S_CLASS_ID, r->id, 1);
	print_key(S_CLASS_SUBCAT_ID, r->subcat_id, 1);
	print_varchar(S_CLASS_DESC, r->desc, 0);
	print_end(S_CLASS);
	
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
ld_s_class(void *pSrc)
{
	struct S_CLASS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_class;
	else
		r = pSrc;
	
	return(0);
}

