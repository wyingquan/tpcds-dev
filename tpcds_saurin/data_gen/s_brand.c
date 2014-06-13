/*
* $Id: s_brand.c,v 1.3 2006/03/09 23:00:08 jms Exp $
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
* $Log: s_brand.c,v $
* Revision 1.3  2006/03/09 23:00:08  jms
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
#include "s_brand.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_BRAND_TBL g_s_brand;

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
mk_s_brand(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_BRAND_TBL *r;
	
	if (pDest == NULL)
		r = &g_s_brand;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_brand, 0, sizeof(struct S_BRAND_TBL));
		bInit = 1;
	}
	
	r->brand_id = kIndex;
	r->subclass_id = (kIndex % BRAND_SUBCLASS_COUNT) + 1;
	r->manager_id = mk_join(S_BRAND_MANAGER_ID, S_MANAGER, 1);
	r->manufacturer_id = mk_join(S_BRAND_MANUFACTURER_ID, S_MANUFACTURER, 1);
	mk_word(r->brand_name, "syllables", kIndex, RS_BRAND_NAME, S_BRAND_NAME);
	row_stop(S_BRAND);
	
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
pr_s_brand(void *pSrc)
{
	struct S_BRAND_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_brand;
	else
		r = pSrc;
	
	print_start(S_BRAND);
	print_key(S_BRAND_ID, r->brand_id, 1);
	print_key(S_BRAND_SUBCLASS_ID, r->subclass_id, 1);
	print_key(S_BRAND_MANAGER_ID, r->manager_id, 1);
	print_key(S_BRAND_MANUFACTURER_ID, r->manufacturer_id, 1);
	print_varchar(S_BRAND_NAME, r->brand_name, 1);
	print_end(S_BRAND);
	
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
ld_s_brand(void *pSrc)
{
	struct S_BRAND_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_brand;
	else
		r = pSrc;
	
	return(0);
}

