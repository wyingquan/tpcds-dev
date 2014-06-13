/*
* $Id: s_promotion.c,v 1.14 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_promotion.c,v $
* Revision 1.14  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.13  2007/07/31 06:07:39  jms
* bug 546: s_promotion
*
* Revision 1.12  2007/07/25 19:41:47  jms
* bug 546: remove duplicate printing
*
* Revision 1.11  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.10  2007/07/02 18:37:39  jms
* Bug 546
*
* Revision 1.9  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.8  2006/09/05 18:08:30  jms
* Bug 491: remove p_item_sk from s_promotions
*
* Revision 1.7  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.6  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.5  2006/03/25 00:42:47  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.4  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.3  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.7  2004/10/29 16:45:23  jms
* remove extra terminator from s_promotion
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
#include "genrand.h"
#include "s_promotion.h"
#include "w_promotion.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "parallel.h"
#include "date.h"
#include "permute.h"
#include "scaling.h"
#include "tdef_functions.h"
#include "scd.h"
#include "r_params.h"

extern struct W_PROMOTION_TBL g_w_promotion;


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
mk_s_promotion (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(PROMOTION), S_PROMOTION_ID);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_promotion(NULL, kIndex);
   row_stop(PROMOTION);

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
pr_s_promotion(void *pSrc)
{
	struct W_PROMOTION_TBL *r;

	if (pSrc == NULL)
		r = &g_w_promotion;
	else
		r = pSrc;
	
	print_start(S_PROMOTION);
	print_varchar(P_PROMO_ID, r->p_promo_id, 1);
	print_varchar(P_PROMO_NAME, &r->p_promo_name[0], 1);
   print_date(P_START_DATE_ID, r->p_start_date_id, 1);
   print_date(P_START_DATE_ID, r->p_end_date_id, 1);
	print_decimal(P_COST, &r->p_cost, 1);
	print_integer(P_RESPONSE_TARGET, r->p_response_target, 1);
	print_boolean(P_CHANNEL_DMAIL, r->p_channel_dmail, 1);
	print_boolean(P_CHANNEL_EMAIL, r->p_channel_email, 1);
	print_boolean(P_CHANNEL_CATALOG, r->p_channel_catalog, 1);
	print_boolean(P_CHANNEL_TV, r->p_channel_tv, 1);
	print_boolean(P_CHANNEL_RADIO, r->p_channel_radio, 1);
	print_boolean(P_CHANNEL_PRESS, r->p_channel_press, 1);
	print_boolean(P_CHANNEL_EVENT, r->p_channel_event, 1);
	print_boolean(P_CHANNEL_DEMO, r->p_channel_demo, 1);
	print_varchar(P_CHANNEL_DETAILS, &r->p_channel_details[0], 1);
	print_varchar(P_PURPOSE, r->p_purpose, 1);
	print_boolean(P_DISCOUNT_ACTIVE, r->p_discount_active, 0);
	print_end(S_PROMOTION);
	
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
ld_s_promotion(void *pSrc)
{
	struct W_PROMOTION_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_promotion;
	else
		r = pSrc;
	
	return(0);
}


int
vld_s_promotion(int nTable, ds_key_t kRow, int *Permutation)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;
   table_func_t *pTF = getTdefFunctionsByNumber(PROMOTION);

   if (!bInit)
   {
      pPermutation = 
         makePermutation(NULL, (int)getIDCount(PROMOTION), S_PROMOTION_ID);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)kRow);

   row_skip(PROMOTION, kRow - 1);
	pTF->builder(NULL, kIndex);
   row_stop(PROMOTION);

	return(0);
}

