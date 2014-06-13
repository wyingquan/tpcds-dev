/*
* $Id: s_product.c,v 1.4 2006/03/09 23:00:09 jms Exp $
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
* $Log: s_product.c,v $
* Revision 1.4  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.3  2006/01/16 23:16:02  jms
* Bug 366: source schema needs character ids to join with warehouse
*
* Revision 1.2  2004/11/24 23:54:20  jms
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
#include <string.h>
#include "genrand.h"
#include "s_product.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "parallel.h"

struct S_PRODUCT_TBL g_s_product;

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
mk_s_product(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_PRODUCT_TBL *r;
	
	if (pDest == NULL)
		r = &g_s_product;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_s_product, 0, sizeof(struct S_PRODUCT_TBL));
		r->type = strdup("PTYPE");
		bInit = 1;
	}
	
	mk_bkey(r->id, kIndex, S_PRODUCT_ID);
	mk_bkey(r->brand_id, (ds_key_t)mk_join(S_PRODUCT_BRAND_ID, S_BRAND, 1), S_PRODUCT_BRAND_ID);
	mk_word(r->name, "syllables", kIndex, RS_S_PRODUCT_NAME, S_PRODUCT_NAME);
	row_stop(S_PRODUCT);
	
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
pr_s_product(void *pSrc)
{
	struct S_PRODUCT_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_product;
	else
		r = pSrc;
	
	print_start(S_PRODUCT);
	print_varchar(S_PRODUCT_ID, r->id,  1);
	print_varchar(S_PRODUCT_BRAND_ID, r->brand_id,  1);
	print_varchar(S_PRODUCT_NAME, r->name,  1);
	print_varchar(S_PRODUCT_TYPE, r->type,  0);
	print_end(S_PRODUCT);
	
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
ld_s_product(void *pSrc)
{
	struct S_PRODUCT_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_product;
	else
		r = pSrc;
	
	return(0);
}

