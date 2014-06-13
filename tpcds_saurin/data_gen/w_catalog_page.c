/*
* $Id: w_catalog_page.c,v 1.13 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_catalog_page.c,v $
* Revision 1.13  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.12  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.11  2006/03/28 00:59:47  jms
* Catalog page changes from Meikel (3/27)
*
* Revision 1.10  2006/02/21 22:20:28  jms
* Bug 373: catalog page join
*
* Revision 1.9  2006/02/21 20:53:59  jms
* bug 374: correct page/catalog numbering
*
* Revision 1.8  2006/02/03 06:01:24  jms
* resolve the catalog join issue
*
* Revision 1.7  2006/02/02 06:18:26  jms
* Bug 374: bad join from cp to date
*
* Revision 1.6  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.5  2005/10/18 16:29:16  jms
* correct NOT NULL attributes
*
* Revision 1.4  2005/10/05 22:35:11  jms
* revert to print_date for dates not linked to date_dim
*
* Revision 1.3  2005/03/15 22:37:03  jms
* Bug 146: invalid data in catalog_returns
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
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
#include "w_catalog_page.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "tables.h"
#include "scaling.h"
#include "nulls.h"
#include "tdefs.h"

struct CATALOG_PAGE_TBL g_w_catalog_page;

/*
* Routine: mk_catalog_page()
* Purpose: populate the catalog_page table
* Algorithm:
*	catalogs are issued either monthly, quarterly or bi-annually (cp_type)
*	there is 1 of each type circulating at all times
* Data tdefsures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
* 20020903 jms cp_department needs to be randomized
* 20020903 jms cp_description needs to be randomized
*/
int
mk_w_catalog_page (void *row, ds_key_t index)
{
	int res = 0;
	static date_t *dStartDate;
	static int nCatalogPageMax;
	int nDuration, 
		nOffset,
		nType;
	static int bInit = 0;
	struct CATALOG_PAGE_TBL *r;
	int nCatalogInterval;
   tdef *pTdef = getSimpleTdefsByNumber(CATALOG_PAGE);

	if (row == NULL)
		r = &g_w_catalog_page;
	else
		r = row;
	
	if (!bInit)
	{
		nCatalogPageMax = ((int)get_rowcount(CATALOG_PAGE) / CP_CATALOGS_PER_YEAR) / (YEAR_MAXIMUM - YEAR_MINIMUM + 2); 
		dStartDate = strtodate(DATA_START_DATE);

		/* columns that still need to be populated */
        strcpy (r->cp_department, "DEPARTMENT");

		bInit = 1;
	}
	
	nullSet(&pTdef->kNullBitMap, CP_NULLS);
	r->cp_catalog_page_sk = index;
	mk_bkey(&r->cp_catalog_page_id[0], index, CP_CATALOG_PAGE_ID);
	r->cp_catalog_number = (long)(index - 1) / nCatalogPageMax + 1;
	r->cp_catalog_page_number = (long)(index - 1) % nCatalogPageMax + 1;
	switch(nCatalogInterval = ((r->cp_catalog_number - 1)%CP_CATALOGS_PER_YEAR))
	{
	case 0:			/* bi-annual */
	case 1:
		nType = 1;
		nDuration = 182;
		nOffset = nCatalogInterval * nDuration;
		break;
	case 2:
	case 3:			/* Q2 */
	case 4:			/* Q3 */
	case 5:			/* Q4 */
		nDuration = 91;
		nOffset = (nCatalogInterval- 2) * nDuration;
		nType = 2;
		break;
	default:
		nDuration = 30;
		nOffset = (nCatalogInterval - 6) * nDuration;
		nType = 3;	/* monthly */
	}
	r->cp_start_date_id = dStartDate->julian + nOffset;
   r->cp_start_date_id += ((r->cp_catalog_number - 1) / CP_CATALOGS_PER_YEAR) * 365;
	r->cp_end_date_id = r->cp_start_date_id + nDuration - 1;
	dist_member(&r->cp_type, "catalog_page_type", nType, 1);
	gen_text(&r->cp_description[0], RS_CP_DESCRIPTION / 2, RS_CP_DESCRIPTION - 1, CP_DESCRIPTION);

	return (res);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data tdefsures:
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
pr_w_catalog_page(void *row)
{
	struct CATALOG_PAGE_TBL *r;

	if (row == NULL)
		r = &g_w_catalog_page;
	else
		r = row;

	print_start(CATALOG_PAGE);
	print_key(CP_CATALOG_PAGE_SK, r->cp_catalog_page_sk, 1);
	print_varchar(CP_CATALOG_PAGE_ID, r->cp_catalog_page_id, 1);
	print_key(CP_START_DATE_ID, r->cp_start_date_id, 1);
	print_key(CP_END_DATE_ID, r->cp_end_date_id, 1);
	print_varchar(CP_DEPARTMENT, &r->cp_department[0], 1);
	print_integer(CP_CATALOG_NUMBER, r->cp_catalog_number, 1);
	print_integer(CP_CATALOG_PAGE_NUMBER, r->cp_catalog_page_number, 1);
	print_varchar(CP_DESCRIPTION, &r->cp_description[0], 1);
	print_varchar(CP_TYPE, r->cp_type, 0);
	print_end(CATALOG_PAGE);

	return(0);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data tdefsures:
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
ld_w_catalog_page(void *r)
{
	return(0);
}

