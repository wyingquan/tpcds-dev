/*
* $Id: join.c,v 1.19 2007/08/02 18:56:30 jms Exp $
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
* $Log: join.c,v $
* Revision 1.19  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.18  2006/08/17 21:23:58  jms
* Bug 480
*
* Revision 1.17  2006/05/12 21:01:59  jms
* porting cleanup
*
* Revision 1.16  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.15  2006/02/21 22:20:27  jms
* Bug 373: catalog page join
*
* Revision 1.14  2006/02/03 06:01:24  jms
* resolve the catalog join issue
*
* Revision 1.13  2006/01/02 20:16:31  jms
* Bug #357: update generation segfaults
*
* Revision 1.12  2006/01/02 20:11:33  jms
* Bug 357: segfault when building updates
*
* Revision 1.11  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.10  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.9  2005/10/06 21:54:27  jms
* Bug 320: drop promotional_bundle, promotional_bundle_coverage
*
* Revision 1.8  2005/03/15 22:37:03  jms
* Bug 146: invalid data in catalog_returns
*
* Revision 1.7  2005/01/13 22:54:59  jms
* remove extraneous error condition
*
* Revision 1.6  2005/01/13 19:56:09  jms
* Bug #136: Shift demographic row counts to allow for sparse keys
* [ log truncated at 1 Jan 2005 as of 17 Feb 2006 ]
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "date.h"
#include "decimal.h"
#include "dist.h"
#include "constants.h"
#include "columns.h"
#include "genrand.h"
#include "tdefs.h"
#include "tables.h"
#include "build_support.h"
#include "tpcds.idx.h"
#include "scaling.h"
#include "w_web_sales.h"
#include "error_msg.h"
#include "tdefs.h"
#include "scd.h"
#include "r_params.h"
#include "sparse.h"

static ds_key_t web_join(int col, ds_key_t join_key);

/*
* Routine: date_join(int from_tbl, int join_count)
* Purpose: account for the different date-adjusted patterns in the data set
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: Relies on existing RNG code, which isn't really 64bit; will probably requre a rework of the genrand_xx routines
*/
static ds_key_t
date_join(int from_tbl, int from_col, ds_key_t join_count, int nYear)
{
	int nDay,
		nTemp,
		nMin = -1, 
		nMax = -1,
		nResult;
	static int bInit = 0,
		jToday;
	date_t TempDate;

	if (bInit == 0)
	{
		strtodt(&TempDate, TODAYS_DATE);
		jToday = dttoj(&TempDate);
		bInit = 1;
	}
	
	switch(from_tbl)
	{
	case STORE_SALES:
	case CATALOG_SALES:
	case WEB_SALES:
		pick_distribution(&nDay, "calendar", 1, calendar_sales + is_leap(nYear), from_col);
		break;

	/*
	 * returns are keyed to the sale date, with the lag between sale and return selected within a known range, based on 
	 * sales channel
	 */
	case STORE_RETURNS:
		nMin = SS_MIN_SHIP_DELAY;
		nMax = SS_MAX_SHIP_DELAY;
	case CATALOG_RETURNS:
		if (nMin == -1)
		{
		nMin = CS_MIN_SHIP_DELAY;
		nMax = CS_MAX_SHIP_DELAY;
		}
	case WEB_RETURNS:
		if (nMin == -1)
		{
		nMin = WS_MIN_SHIP_DELAY;
		nMax = WS_MAX_SHIP_DELAY;
		}
		genrand_integer(&nTemp, DIST_UNIFORM, nMin * 2, nMax * 2, 0, from_col);
		return(join_count + nTemp);
		break;
	case WEB_SITE:
	case WEB_PAGE:
		return(web_join(from_col, join_count));
	default:
		pick_distribution(&nDay, "calendar", 1, 1 + is_leap(nYear), from_col);
		break;
	}
	
	TempDate.year = nYear;
	TempDate.month = 1;
	TempDate.day = 1;

	nResult = dttoj(&TempDate) + nDay;

	return((ds_key_t)(nResult > jToday)?-1:nResult);
}

/*
* Routine: time_join(int from_tbl, int join_count)
* Purpose: create joins that are time-skewed
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: Relies on existing RNG code, which isn't really 64bit; will probably requre a rework of the genrand_xx routines
*/
static ds_key_t
time_join(int to_tbl, int to_col, ds_key_t join_count)
{
	int hour,
		secs;
	
	switch(to_tbl)
	{
	case STORE_SALES:
	case STORE_RETURNS:
		pick_distribution(&hour, "hours", 1, 2, to_col);
		break;
	case CATALOG_SALES:
	case WEB_SALES:
	case CATALOG_RETURNS:
	case WEB_RETURNS:
		pick_distribution(&hour, "hours", 1, 3, to_col);
		break;
	default:
		pick_distribution(&hour, "hours", 1, 1, to_col);
		break;
	}
	genrand_integer(&secs, DIST_UNIFORM, 0, 3599, 0, to_col);
	
	
	return((ds_key_t)(hour * 3600 + secs));
}

/*
* Routine: cp_join(int from_tbl, int join_count)
* Purpose: create joins to catalog_page
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
static ds_key_t
cp_join(int tbl, int col, ds_key_t jDate)
{
	ds_key_t res;
	static int init = 0,
		nPagePerCatalog;
	int nType,
		nCount,
		nOffset,
		nPage;
	static date_t *dTemp;
	char *szTemp;

	if (!init)
	{
		nPagePerCatalog = ((int)get_rowcount(CATALOG_PAGE) / CP_CATALOGS_PER_YEAR) / (YEAR_MAXIMUM - YEAR_MINIMUM + 2);
		dTemp = strtodate(DATA_START_DATE);
		init = 1;
	}
	
	nType = pick_distribution(&szTemp, "catalog_page_type", 1, 2, col);
	genrand_integer(&nPage, DIST_UNIFORM, 1, nPagePerCatalog, 0, col);
	nOffset = (int)jDate - dTemp->julian - 1;
	nCount = (nOffset / 365) * CP_CATALOGS_PER_YEAR;
	nOffset %= 365;

   switch(nType)
	{
	case 1:	/* bi-annual */
		if (nOffset > 183)
			nCount += 1;
		break;
	case 2:	/* quarterly */
		nCount += (nOffset / 91);
		break;
	case 3:	/* monthly */
		nCount += (nOffset / 31);
		break;
	}

   res = CP_SK(nCount, nPagePerCatalog, nPage) ;

	return(res);
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
ds_key_t
getCatalogNumberFromPage(ds_key_t kPageNumber)
{
	static int bInit = 0;
	static int nPagePerCatalog;

	if (!bInit)
	{
		nPagePerCatalog = ((int)get_rowcount(CATALOG_PAGE) / CP_CATALOGS_PER_YEAR) / (YEAR_MAXIMUM - YEAR_MINIMUM + 2);
		bInit = 1;
	}

	return(kPageNumber / nPagePerCatalog);

}


/*
* Routine: web_join(int col, ds_key_t join_key)
* Purpose: create joins to web_site/web_page. These need to be handled together, since the date of transaction 
*	must fit within the lifetime of a particular page, which must fit within the lifetime of a particular site
* Data Structures:
*
* Params:
*	join_key is one of two things:
*		1. the xxx_sk for a particular row in the dimension for which we need appropriate dates
*		2. a julian date for which we need to pick a valid xxx_sk value
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
static ds_key_t
web_join(int col, ds_key_t join_key)
{
	ds_key_t res = -1,
		kSite;
	static int init = 0,
		nConcurrentSites,
		nSiteDuration,
		nOffset;
	static date_t *dSiteOpen,	/* open/close dates for current web site */
		*dSiteClose;
	int nTemp;
   tdef *pWS = getSimpleTdefsByNumber(WEB_SITE);
   tdef *pWP = getSimpleTdefsByNumber(WEB_PAGE);


	if (!init)
	{
		dSiteClose = strtodate(WEB_END_DATE);
		nSiteDuration = dSiteClose->julian;
		free(dSiteClose);
		nConcurrentSites = (int)get_rowcount(CONCURRENT_WEB_SITES);
		dSiteOpen = strtodate(WEB_START_DATE);
		nSiteDuration -= dSiteOpen->julian;
		free(dSiteOpen);
		nSiteDuration *= nConcurrentSites;
		nOffset = (dSiteClose->julian - dSiteOpen->julian) / (2 * nSiteDuration) ;
		init = 1;
	}
	
	switch(col)
	{
/**************
 * join_key is the xxx_sk value for a dimension
 */
	case WEB_OPEN_DATE:
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - ((join_key * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		if (WEB_IS_REPLACED(join_key))	/* this site is completely replaced */
		{
			if (WEB_IS_REPLACEMENT(join_key))	/* this is the second site */
			{
				/* the open date of the second site needs to align on a revision boundary */
				res += nOffset * nSiteDuration;
			}
		}
		break;
	case WEB_CLOSE_DATE:		
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - ((join_key * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		res += pWS->nParam * nSiteDuration;
		if (WEB_IS_REPLACED(join_key))	/* this site is completely replaced */
		{
			if (!WEB_IS_REPLACEMENT(join_key))	/* this is the first site */
			{
				/* the close date of the first site needs to align on a revision boundary */
				res -= pWS->nParam * nSiteDuration / 2;
			}
		}
		break;
	case WEB_REC_START_DATE_ID:
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - (((join_key - 1) * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		res += (join_key % pWS->nParam)  * nSiteDuration;
		break;
	case WEB_REC_END_DATE_ID:
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - ((join_key * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		res += ((join_key + 1) % pWS->nParam) * nSiteDuration * 5 - 1;
		break;
	case WP_REC_START_DATE_ID:
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - (((join_key - 1) * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		res += (join_key % pWP->nParam)  * nSiteDuration * 5;
		break;
	case WP_REC_END_DATE_ID:
		dSiteOpen = strtodate(DATE_MINIMUM);
		res = dSiteOpen->julian - ((join_key * WEB_DATE_STAGGER) % nSiteDuration / 2);
		free(dSiteOpen);
		res += ((join_key + 1) % pWP->nParam) * nSiteDuration - 1;
		break;
	case WP_CREATION_DATE_SK:
		/* page creation has to happen outside of the page window, to assure a constant number of pages,
		 * so it occurs in the gap between site creation and the site's actual activity. For sites that are replaced 
		 * in the time span of the data set, this will depend on whether they are the first version or the second
		 */
		dSiteOpen = strtodate(DATE_MINIMUM);
		kSite = join_key / WEB_PAGES_PER_SITE + 1;
		res = dSiteOpen->julian - (((int)kSite * WEB_DATE_STAGGER) % nSiteDuration / 2);
		if (((int)kSite % pWP->nParam) == 0)	/* this is a site that gets replaced */
		{
			genrand_integer(&nTemp, DIST_UNIFORM, (int)res, dSiteOpen->julian, 0, col);
			res = nTemp;
		}
		free(dSiteOpen);
		break;
/*****************
 * join key from here on is a date for which a valid site/page must be found
 * the sk for a web page is a compound value: <site id><page id> and each component
 * is a combination of the unique site or page and the active revision to it
 */
	case WR_WEB_PAGE_SK:
	case WS_WEB_PAGE_SK:
		res = genrand_integer(NULL, DIST_UNIFORM, 1, WEB_PAGES_PER_SITE, 0, col);
		break;
	}
	
	return(res);
}

/*
* Routine: mk_join(int from_tbl, int to_tbl, int join_count)
* Purpose: return a primary key for to_tbl, creating a join between from_tbl and to_tbl
* Algorithm: all joins are currently uniformly distributed. The calling convention allows for each 
*	join in the schema to be distributed differently
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: Relies on existing RNG code, which isn't really 64bit; will probably requre a rework of the genrand_xx routines
*/
ds_key_t
mk_join(int from_col, int to_tbl, ds_key_t join_count)
{
	ds_key_t res;
	int nYear,
		nFromTable = 0,
		nTableIndex = to_tbl;
	tdef *pTdef;

	nFromTable = getTableFromColumn(from_col);

	/*
	 * if the table being joined to employs sparse keys, the join gets handled in sparse.c 
	 */
	pTdef = getSimpleTdefsByNumber(to_tbl);
	if (pTdef->flags & FL_SPARSE)
	{
		if (pTdef->arSparseKeys == NULL)
			initSparseKeys(to_tbl);
	}

	switch(to_tbl)
	{
	/* some tables require special handling */
	case CATALOG_PAGE:
		return(cp_join(nFromTable, from_col, join_count));
	case DATE:
		genrand_integer(&nYear, DIST_UNIFORM, YEAR_MINIMUM, YEAR_MAXIMUM, 0, from_col);
		return(date_join(nFromTable, from_col, join_count, nYear));
	case TIME:
		return(time_join(nFromTable, from_col, join_count));
		/* the rest of the tables use standard, uniform joins */	
	default:
	/* 
	 * all TYPE2 tables (i.e., history keeping dimensions) need a special join algorithm
	 */
		if (pTdef->flags & FL_TYPE_2)
			return(scd_join(nTableIndex, from_col, join_count));

		if (pTdef->flags & FL_SPARSE)
			return(randomSparseKey(nTableIndex, from_col));
		
		genrand_key(&res, DIST_UNIFORM, (ds_key_t)1, get_rowcount(nTableIndex), (ds_key_t)0, from_col);
		break;
	}

	
	return((ds_key_t)res);
}
