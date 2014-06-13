/*
* $Id: w_timetbl.c,v 1.4 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_timetbl.c,v $
* Revision 1.4  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.3  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
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
#include "constants.h"
#include "w_timetbl.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"

struct W_TIME_TBL g_w_time;

/*
* mk_time
*/
int
mk_w_time(void* row, ds_key_t index)
{
	int res = 0;
	
	/* begin locals declarations */
	int nTemp;
	struct W_TIME_TBL *r;
   tdef *pT = getSimpleTdefsByNumber(TIME);

	if (row == NULL)
		r = &g_w_time;
	else
		r = row;

	
	nullSet(&pT->kNullBitMap, T_NULLS);
	r->t_time_sk = index - 1;
	mk_bkey(&r->t_time_id[0], index, T_TIME_ID);
	r->t_time = (long)index - 1;
	nTemp = (long)index - 1;
	r->t_second = nTemp % 60;
	nTemp /= 60;
	r->t_minute = nTemp % 60;
	nTemp /= 60;
	r->t_hour = nTemp % 24;
	dist_member (&r->t_am_pm, "hours", r->t_hour + 1, 2);
	dist_member (&r->t_shift, "hours", r->t_hour + 1, 3);
	dist_member (&r->t_sub_shift, "hours", r->t_hour + 1, 4);
	dist_member (&r->t_meal_time, "hours", r->t_hour + 1, 5);
	
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
pr_w_time(void *row)
{
	struct W_TIME_TBL *r;

	if (row == NULL)
		r = &g_w_time;
	else
		r = row;

	print_start(TIME);
	print_key(T_TIME_SK, r->t_time_sk, 1);	
	print_varchar(T_TIME_ID, r->t_time_id, 1);	
	print_integer(T_TIME, r->t_time, 1);
	print_integer(T_HOUR, r->t_hour, 1);
	print_integer(T_MINUTE, r->t_minute, 1);
	print_integer(T_SECOND, r->t_second, 1);
	print_varchar(T_AM_PM, r->t_am_pm, 1);
	print_varchar(T_SHIFT, r->t_shift, 1);
	print_varchar(T_SUB_SHIFT, r->t_sub_shift, 1);
	print_varchar(T_MEAL_TIME, r->t_meal_time, 0);
	print_end(TIME);
	
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
ld_w_time(void *pSrc)
{
	struct W_TIME_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_time;
	else
		r = pSrc;
	
	return(0);
}

