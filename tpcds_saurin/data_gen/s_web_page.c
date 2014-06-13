/*
* $Id: s_web_page.c,v 1.11 2007/09/10 18:10:36 jms Exp $
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
* $Log: s_web_page.c,v $
* Revision 1.11  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.10  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.9  2006/06/06 21:41:15  jms
* initial checkin of revised update scaling
*
* Revision 1.8  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.7  2006/03/25 00:42:47  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.6  2006/03/24 22:58:26  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.5  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.3  2006/01/02 23:01:28  jms
* Bug #360: sk often default to 1 in update set
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.3  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "s_web_page.h"
#include "w_web_page.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "scaling.h"
#include "parallel.h"
#include "permute.h"
#include "scd.h"
#include "tdef_functions.h"

extern struct W_WEB_PAGE_TBL g_w_web_page;


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
mk_s_web_page (void* row, ds_key_t index)
{
   static int bInit = 0;
   static int *pPermutation;
   ds_key_t kIndex;

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(WEB_PAGE), S_WPAG_PERMUTE);
      bInit = 1;
   }

   kIndex = getPermutationEntry(pPermutation, (int)index);
   mk_w_web_page(NULL, getSKFromID(kIndex, S_WPAG_ID));

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
pr_s_web_page(void *pSrc)
{
	struct W_WEB_PAGE_TBL *r;

	if (pSrc == NULL)
		r = &g_w_web_page;
	else
		r = pSrc;
	
	print_start(S_WEB_PAGE);
	print_varchar(WP_PAGE_ID, r->wp_page_id, 1);
	print_date(WP_CREATION_DATE_SK, r->wp_creation_date_sk, 1);
	print_date(WP_ACCESS_DATE_SK, r->wp_access_date_sk, 1);
	print_boolean(WP_AUTOGEN_FLAG, r->wp_autogen_flag, 1);
	print_varchar(WP_URL, &r->wp_url[0], 1);
	print_varchar(WP_TYPE, &r->wp_type[0], 1);
	print_integer(WP_CHAR_COUNT, r->wp_char_count, 1);
	print_integer(WP_LINK_COUNT, r->wp_link_count, 1);
	print_integer(WP_IMAGE_COUNT, r->wp_image_count, 1);
	print_integer(WP_MAX_AD_COUNT, r->wp_max_ad_count, 0);
	print_end(S_WEB_PAGE);
	
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
ld_s_web_page(void *pSrc)
{
	struct W_WEB_PAGE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_web_page;
	else
		r = pSrc;
	
	return(0);
}

int
vld_s_web_page(int nTable, ds_key_t kRow, int *Permutation)
{
   static int bInit = 0;
   static int *pPermutation;
   table_func_t *pTF = getTdefFunctionsByNumber(WEB_PAGE);

   if (!bInit)
   {
      pPermutation = makePermutation(NULL, (int)getIDCount(WEB_PAGE),
      S_WPAG_PERMUTE);
      bInit = 1;
   }

   pTF->validate(S_WEB_PAGE, kRow, pPermutation);

   return(0);
   }
                                        
