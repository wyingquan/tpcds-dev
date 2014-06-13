/*
* $Id: w_household_demographics.c,v 1.11 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_household_demographics.c,v $
* Revision 1.11  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.10  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.9  2006/08/24 22:32:07  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.8  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.7  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.6  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.5  2005/01/13 23:09:11  jms
* Bug #136: sparse key support
*
* Revision 1.4  2005/01/13 22:54:16  jms
* Bug #136: sparse key support
*
* Revision 1.3  2005/01/13 19:50:02  jms
* Use sparse surrogate keys per Bug #136
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.7  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 00:39:39  jms
* use ds_key_t in bitmap_to_dist for solaris
*
* Revision 1.3  2004/03/26 22:06:39  jms
* add ntohl headers
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
#ifdef NCR
#include <sys/types.h>
#endif
#ifndef WIN32
#include <netinet/in.h>
#endif
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include "genrand.h"
#include "w_household_demographics.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"
#include "sparse.h"

struct W_HOUSEHOLD_DEMOGRAPHICS_TBL g_w_household_demographics;

/*
* mk_household_demographics
*/
int
mk_w_household_demographics (void* row, ds_key_t index)
{
	int32_t res = 0;
	/* begin locals declarations */
	ds_key_t nTemp;
	struct W_HOUSEHOLD_DEMOGRAPHICS_TBL *r;
   tdef *pTdef = getSimpleTdefsByNumber(HOUSEHOLD_DEMOGRAPHICS);

	if (row == NULL)
		r = &g_w_household_demographics;
	else
		r = row;

	
	nullSet(&pTdef->kNullBitMap, HD_NULLS);
	r->hd_demo_sk = index;
	nTemp = r->hd_demo_sk;
	r->hd_income_band_id =
		(nTemp % distsize ("income_band")) + 1;
	nTemp /= distsize ("income_band");
	bitmap_to_dist (&r->hd_buy_potential, "buy_potential", &nTemp, 1, HOUSEHOLD_DEMOGRAPHICS);
	bitmap_to_dist (&r->hd_dep_count, "dependent_count", &nTemp, 1, HOUSEHOLD_DEMOGRAPHICS);
	bitmap_to_dist (&r->hd_vehicle_count, "vehicle_count", &nTemp, 1, HOUSEHOLD_DEMOGRAPHICS);
	
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
pr_w_household_demographics(void *row)
{
	struct W_HOUSEHOLD_DEMOGRAPHICS_TBL *r;

	if (row == NULL)
		r = &g_w_household_demographics;
	else
		r = row;

	print_start(HOUSEHOLD_DEMOGRAPHICS);
	print_key(HD_DEMO_SK, r->hd_demo_sk, 1);
	print_key(HD_INCOME_BAND_ID, r->hd_income_band_id, 1);
	print_varchar(HD_BUY_POTENTIAL, r->hd_buy_potential, 1);
	print_integer(HD_DEP_COUNT, r->hd_dep_count, 1);
	print_integer(HD_VEHICLE_COUNT, r->hd_vehicle_count, 0);
	print_end(HOUSEHOLD_DEMOGRAPHICS);

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
ld_w_household_demographics(void *pSrc)
{
	struct W_HOUSEHOLD_DEMOGRAPHICS_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_household_demographics;
	else
		r = pSrc;
	
	return(0);
}

