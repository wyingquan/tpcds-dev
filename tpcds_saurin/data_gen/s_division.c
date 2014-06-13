/*
* $Id: s_division.c,v 1.4 2006/03/09 23:00:09 jms Exp $
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
* $Log: s_division.c,v $
* Revision 1.4  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.3  2005/10/17 17:55:45  jms
* add missing source schema columns
*
* Revision 1.2  2004/11/24 23:54:19  jms
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
#include "s_division.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_DIVISION_TBL g_s_division;

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
mk_s_division(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_DIVISION_TBL *r;
	
	if (pDest == NULL)
		r = &g_s_division;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_division, 0, sizeof(struct S_DIVISION_TBL));
		bInit = 1;
	}
	
	r->id = kIndex;
	r->company = (kIndex % DIVISIONS_PER_COMPANY) + 1;
	mk_word(r->name, "syllables", kIndex, RS_DIVISION_NAME, S_DIVISION_NAME);
	row_stop(S_DIVISION);
	
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
pr_s_division(void *pSrc)
{
	struct S_DIVISION_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_division;
	else
		r = pSrc;
	
	print_start(S_DIVISION);
	print_key(S_DIVISION_ID, r->id, 1);
	print_varchar(S_DIVISION_NAME, r->name, 1);
	print_key(S_DIVISION_COMPANY, r->company, 1);
	print_end(S_DIVISION);
	
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
ld_s_division(void *pSrc)
{
	struct S_DIVISION_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_division;
	else
		r = pSrc;
	
	return(0);
}

