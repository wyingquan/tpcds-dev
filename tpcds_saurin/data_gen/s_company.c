/*
* $Id: s_company.c,v 1.3 2006/03/09 23:00:09 jms Exp $
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
* $Log: s_company.c,v $
* Revision 1.3  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.6  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
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
#include "s_company.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_COMPANY_TBL g_s_company;

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
mk_s_company(void *pDest, ds_key_t kIndex)
{
	struct S_COMPANY_TBL *r;
	static int bInit = 0;
	
	if (pDest == NULL)
		r = &g_s_company;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_company, 0, sizeof(struct S_COMPANY_TBL));
		bInit = 1;
	}
	
	r->company_id = kIndex;
	mk_word(r->company_name, "Syllables", kIndex, RS_COMPANY_NAME, S_COMPANY_NAME);
	row_stop(S_COMPANY);
	
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
pr_s_company(void *pSrc)
{
	struct S_COMPANY_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_company;
	else
		r = pSrc;
	
	print_start(S_COMPANY);
	print_key(S_COMPANY_ID, r->company_id, 1);
	print_varchar(S_COMPANY_NAME, r->company_name, 0);
	print_end(S_COMPANY);
	
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
ld_s_company(void *pSrc)
{
	struct S_COMPANY_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_company;
	else
		r = pSrc;
	
	return(0);
}

