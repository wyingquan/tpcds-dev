/*
* $Id: w_ship_mode.c,v 1.6 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_ship_mode.c,v $
* Revision 1.6  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.5  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.4  2006/08/24 22:32:07  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.3  2005/10/03 21:18:53  jms
* bug #316: ship_mode.sm_carrier should be unique
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.3  2004/04/02 00:39:39  jms
* use ds_key_t in bitmap_to_dist for solaris
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
#include "w_ship_mode.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_SHIP_MODE_TBL g_w_ship_mode;


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
mk_w_ship_mode(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct W_SHIP_MODE_TBL *r;
	ds_key_t nTemp;
   tdef *pTdef = getSimpleTdefsByNumber(SHIP_MODE);
	
	if (pDest == NULL)
		r = &g_w_ship_mode;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_w_ship_mode, 0, sizeof(struct W_SHIP_MODE_TBL));
		bInit = 1;
	}
	
	nullSet(&pTdef->kNullBitMap, SM_NULLS);
	r->sm_ship_mode_sk = kIndex;
	mk_bkey(&r->sm_ship_mode_id[0], kIndex, SM_SHIP_MODE_ID);
	nTemp = (long)kIndex;
	bitmap_to_dist (&r->sm_type, "ship_mode_type", &nTemp, 1, SHIP_MODE);
	bitmap_to_dist (&r->sm_code, "ship_mode_code", &nTemp, 1, SHIP_MODE);
	dist_member(&r->sm_carrier, "ship_mode_carrier", (int)kIndex, 1);
	gen_charset (r->sm_contract, ALPHANUM, 1, RS_SM_CONTRACT, 
		SM_CONTRACT);
	
	return (0);
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
pr_w_ship_mode(void *pSrc)
{
	struct W_SHIP_MODE_TBL *r;
	
	if (pSrc == NULL)
		r = &g_w_ship_mode;
	else
		r = pSrc;	
	
	print_start(SHIP_MODE);
	print_key(SM_SHIP_MODE_SK, r->sm_ship_mode_sk, 1);
	print_varchar(SM_SHIP_MODE_ID, r->sm_ship_mode_id, 1);
	print_varchar(SM_TYPE, r->sm_type, 1);
	print_varchar(SM_CODE, r->sm_code, 1);
	print_varchar(SM_CARRIER, r->sm_carrier, 1);
	print_varchar(SM_CONTRACT, &r->sm_contract[0], 0);
	print_end(SHIP_MODE);

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
ld_w_ship_mode(void *pSrc)
{
	struct W_SHIP_MODE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_ship_mode;
	else
		r = pSrc;
	
	return(0);
}

