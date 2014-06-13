/*
* $Id: w_income_band.c,v 1.4 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_income_band.c,v $
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
* Revision 1.4  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.3  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
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
#include "w_income_band.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_INCOME_BAND_TBL g_w_income_band;

/*
* mk_income_band
*/
int
mk_w_income_band (void* row, ds_key_t index)
{
	int res = 0;
	struct W_INCOME_BAND_TBL *r;
	static int bInit = 0;
   tdef *pTdef = getSimpleTdefsByNumber(INCOME_BAND);

	if (row == NULL)
		r = &g_w_income_band;
	else
		r = row;

	if (!bInit)
	{
        /* Make exceptions to the 1-rng-call-per-row rule */
		bInit = 1;
	}
	
	nullSet(&pTdef->kNullBitMap, IB_NULLS);
	r->ib_income_band_id = (long)index;
	dist_member (&r->ib_lower_bound, "income_band", (long)index, 1);
	dist_member (&r->ib_upper_bound, "income_band", (long)index, 2);
	
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
pr_w_income_band(void *row)
{
	struct W_INCOME_BAND_TBL *r;

	if (row == NULL)
		r = &g_w_income_band;
	else
		r = row;	
	
	print_start(INCOME_BAND);
	print_integer(IB_INCOME_BAND_ID, r->ib_income_band_id, 1);
	print_integer(IB_LOWER_BOUND, r->ib_lower_bound, 1);
	print_integer(IB_UPPER_BOUND, r->ib_upper_bound, 0);
	print_end(INCOME_BAND);

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
ld_w_income_band(void *pSrc)
{
	struct W_INCOME_BAND_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_income_band;
	else
		r = pSrc;
	
	return(0);
}

