/*
* $Id: s_call_center.c,v 1.11 2007/05/23 18:11:58 jms Exp $
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
* $Log: s_call_center.c,v $
* Revision 1.11  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.10  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.9  2006/04/10 23:37:31  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.8  2006/03/28 00:59:47  jms
* Catalog page changes from Meikel (3/27)
*
* Revision 1.7  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.5  2006/01/16 23:59:23  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.4  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.3  2005/11/11 21:58:01  jms
* add tax percentages to all channels in both warehouse and source schemae
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.7  2004/10/27 22:51:51  jms
* Source data corrections from Ruth's research
*
* Revision 1.6  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.5  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.4  2004/04/02 18:23:50  jms
* remove PARALLEL flag from Makefile.suite
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
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <assert.h>
#include <stdio.h>
#include "s_call_center.h"
#include "genrand.h"
#include "r_params.h"
#include "scaling.h"
#include "constants.h"
#include "date.h"
#include "tables.h"
#include "dist.h"
#include "build_support.h"
#include "columns.h"
#include "print.h"
#include "w_call_center.h"
#include "decimal.h"
#include "permute.h"
#include "scd.h"

extern struct CALL_CENTER_TBL g_w_call_center;

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
mk_s_call_center (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(CALL_CENTER), S_CALL_CENTER_ID);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_call_center(NULL, getSKFromID(kIndex, S_CALL_CENTER_ID));

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
pr_s_call_center(void *row)
{
	struct CALL_CENTER_TBL *r;
   
   if (row == NULL)
		r = &g_w_call_center;
	else
		r = row;

	print_start(S_CALL_CENTER);
	print_id(CC_CALL_CENTER_SK, r->cc_call_center_sk, 1);
	print_date(CC_OPEN_DATE_ID, r->cc_open_date_id, 1);
	print_date(CC_CLOSED_DATE_ID, r->cc_closed_date_id, 1);
	print_varchar(CC_NAME, r->cc_name, 1);
	print_varchar(CC_CLASS, &r->cc_class[0], 1);
	print_integer(CC_EMPLOYEES, r->cc_employees, 1);
	print_integer(CC_SQ_FT, r->cc_sq_ft, 1);
	print_varchar(CC_HOURS, r->cc_hours, 1);
	print_varchar(CC_MANAGER, &r->cc_manager[0], 1);
	print_decimal(CC_TAX_PERCENTAGE, &r->cc_tax_percentage, 0);
	print_end(S_CALL_CENTER);

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
ld_s_call_center(void *r)
{
	return(0);
}

