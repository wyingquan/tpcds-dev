/*
* $Id: s_store.c,v 1.12 2007/05/23 18:11:59 jms Exp $
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
* $Log: s_store.c,v $
* Revision 1.12  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.11  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.10  2006/06/02 12:20:33  jms
* Bug 459: closed date should be printed as date, not SK
*
* Revision 1.9  2006/05/02 22:26:43  jms
* Bug 442
*
* Revision 1.8  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.7  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.5  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.4  2005/11/11 21:58:01  jms
* add tax percentages to all channels in both warehouse and source schemae
*
* Revision 1.3  2005/10/17 17:55:45  jms
* add missing source schema columns
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.7  2004/10/27 22:51:51  jms
* Source data corrections from Ruth's research
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
* Revision 1.3  2004/03/03 17:07:06  jms
* correct column name in s_store
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
#include "s_store.h"
#include "w_store.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "w_store.h"
#include "parallel.h"
#include "permute.h"
#include "scaling.h"
#include "scd.h"

extern struct W_STORE_TBL g_w_store;

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
mk_s_store (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(STORE), S_STORE_ID);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_store(NULL,getSKFromID(kIndex, S_STORE_ID));
   if (!g_w_store.closed_date_id)
      g_w_store.closed_date_id = -1; /* dates use a special NULL indicator */

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
pr_s_store(void *pSrc)
{
	struct W_STORE_TBL *r;
   
   if (pSrc == NULL)
		r = &g_w_store;
	else
		r = pSrc;
	
	print_start(S_STORE);
	print_varchar(W_STORE_ID, r->store_id, 1);
	print_date(W_STORE_CLOSED_DATE_ID, r->closed_date_id, 1);
	print_varchar(W_STORE_NAME, r->store_name, 1);
	print_integer(W_STORE_EMPLOYEES, r->employees, 1);
	print_integer(W_STORE_FLOOR_SPACE, r->floor_space, 1);
	print_varchar(W_STORE_HOURS, r->hours, 1);
	print_varchar(W_STORE_MANAGER, &r->store_manager[0], 1);
	print_integer(W_STORE_MARKET_ID, r->market_id, 1);
	print_varchar(W_STORE_GEOGRAPHY_CLASS, r->geography_class, 1);
	print_varchar(W_STORE_MARKET_MANAGER, &r->market_manager[0], 1);
   print_decimal(W_STORE_TAX_PERCENTAGE,&r->dTaxPercentage, 0);
	print_end(S_STORE);
	
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
ld_s_store(void *pSrc)
{
	struct W_STORE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_store;
	else
		r = pSrc;
	
	return(0);
}

