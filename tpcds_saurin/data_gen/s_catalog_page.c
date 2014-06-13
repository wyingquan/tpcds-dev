/*
* $Id: s_catalog_page.c,v 1.12 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_catalog_page.c,v $
* Revision 1.12  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.11  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.10  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.9  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.8  2007/06/13 22:24:51  jms
* Bug 546: s_catalog_page
*
* Revision 1.7  2006/10/23 22:43:35  jms
* Bugs reported during Nashville meeting
*
* Revision 1.6  2006/10/17 22:38:14  jms
* remove calls to print_cp_delete
*
* Revision 1.5  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.4  2006/03/28 00:59:47  jms
* Catalog page changes from Meikel (3/27)
*
* Revision 1.3  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.5  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
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
#include "s_catalog_page.h"
#include "w_catalog_page.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "scaling.h"
#include "tdef_functions.h"
#include "validate.h"
#include "parallel.h"

struct CATALOG_PAGE_TBL g_w_catalog_page;

int
mk_s_catalog_page(void *pDest, ds_key_t kRow)
{
   mk_w_catalog_page(pDest, kRow);
   row_stop(CATALOG_PAGE);

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
pr_s_catalog_page(void *pSrc)
{
	struct CATALOG_PAGE_TBL *r;
	
	if (pSrc == NULL)
		r = &g_w_catalog_page;
	else
		r = pSrc;
	
	print_start(S_CATALOG_PAGE);
	print_integer(CP_CATALOG_NUMBER, r->cp_catalog_number, 1);
	print_integer(CP_CATALOG_PAGE_NUMBER, r->cp_catalog_page_number, 1);
	print_varchar(CP_DEPARTMENT, &r->cp_department[0], 1);
	print_varchar(CP_CATALOG_PAGE_ID, &r->cp_catalog_page_id[0], 1);
   print_date(CP_START_DATE_ID, r->cp_start_date_id, 1);
   print_date(CP_END_DATE_ID, r->cp_end_date_id, 1);
   print_varchar(CP_DESCRIPTION, r->cp_description, 1);
   print_varchar(CP_TYPE, r->cp_type, 0);
	print_end(S_CATALOG_PAGE);
	
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
ld_s_catalog_page(void *pSrc)
{
	struct CATALOG_PAGE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_catalog_page;
	else
		r = pSrc;
	
	return(0);
}

int 
vld_s_catalog_page(int nTable, ds_key_t kRow, int *Permutation)
{
   return(validateGeneric(S_CATALOG_PAGE, kRow, NULL));
}
