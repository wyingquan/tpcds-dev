/*
* $Id: s_catalog.c,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: s_catalog.c,v $
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.3  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
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
#include "s_catalog.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "misc.h"
#include "tables.h"

struct S_CATALOG_TBL g_s_catalog;

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
mk_s_catalog(void *pDest, ds_key_t kIndex)
{
	struct S_CATALOG_TBL *r;
	static int bInit = 0;
	int nDateDelta;
	static date_t dtStartMin,
		dtStartMax;
	
	if (pDest == NULL)
		r = &g_s_catalog;
	else
		r = pDest;
	
	if (!bInit)
	{
		memset(&g_s_catalog, 0, sizeof(struct S_CATALOG_TBL));
		strtodt(&dtStartMin, "1999-01-01");
		strtodt(&dtStartMax, "2002-12-31");
		bInit = 1;
	}

	r->s_catalog_number = kIndex;
	genrand_date(&r->s_catalog_start_date, DIST_UNIFORM, &dtStartMin, &dtStartMax, NULL, S_CATALOG_START_DATE);
	genrand_integer(&nDateDelta, DIST_UNIFORM, S_CATALOG_DURATION_MIN, S_CATALOG_DURATION_MAX, 0, S_CATALOG_END_DATE);
	jtodt(&r->s_catalog_end_date, r->s_catalog_start_date.julian + nDateDelta);
	gen_text(r->s_catalog_catalog_desc, S_CATALOG_DESC_MIN, S_CATALOG_DESC_MAX, S_CATALOG_DESC);
	genrand_integer(&r->s_catalog_catalog_type, DIST_UNIFORM, 1, S_CATALOG_TYPE_COUNT, 0, S_CATALOG_TYPE);

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
pr_s_catalog(void *pSrc)
{
	struct S_CATALOG_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_catalog;
	else
		r = pSrc;

	print_start(S_CATALOG);
	print_key(S_CATALOG_NUMBER, r->s_catalog_number, 1);
	print_date(S_CATALOG_START_DATE, r->s_catalog_start_date.julian, 1);
	print_date(S_CATALOG_END_DATE, r->s_catalog_end_date.julian, 1);
	print_varchar(S_CATALOG_DESC, r->s_catalog_catalog_desc, 1);
	print_integer(S_CATALOG_TYPE, r->s_catalog_catalog_type, 0);
	print_end(S_CATALOG);

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
ld_s_catalog(void *pSrc)
{
	struct S_CATALOG_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_catalog;
	else
		r = pSrc;

	return(0);
}

