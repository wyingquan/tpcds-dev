/*
* $Id: w_web_page.c,v 1.13 2007/08/02 18:56:31 jms Exp $
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
* $Log: w_web_page.c,v $
* Revision 1.13  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.12  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.11  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.10  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.9  2006/08/28 21:53:30  jms
* Bug 484: remove htonl call since changeSCD now uses arithmetic
*
* Revision 1.8  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.7  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.6  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.5  2006/06/02 12:21:13  jms
* Bug 460: improper NULL handling in ACCESS_DATE
*
* Revision 1.4  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.3  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.11  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.10  2004/08/13 21:52:42  jms
* porting changes for HP/UX
*
* Revision 1.9  2004/08/13 21:48:51  jms
* porting changes for HP/UX
*
* Revision 1.8  2004/08/13 21:10:08  jms
* include <sys/byteorder.h> for SOLARIS
*
* Revision 1.7  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.6.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.6.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.3  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.2  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
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
#include "constants.h"
#include "w_web_page.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "build_support.h"
#include "misc.h"
#include "print.h"
#include "scaling.h"
#include "constants.h"
#include "tables.h"
#include "nulls.h"
#include "tdefs.h"
#include "scd.h"

struct W_WEB_PAGE_TBL g_w_web_page;
static struct W_WEB_PAGE_TBL g_OldValues;

/*
* Routine: mk_web_page()
* Purpose: populate the web_page table
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
* 20020815 jms check text generation/seed usage
*/
int
mk_w_web_page (void * row, ds_key_t index)
{
	int32_t res = 0,
		bFirstRecord = 0,
		nFieldChangeFlags;
	static date_t *dToday;
	static ds_key_t nConcurrent,
		nRevisions;

	/* begin locals declarations */
	int32_t nTemp,
		nAccess;
	char szTemp[16];
	static int32_t bInit = 0;
	struct W_WEB_PAGE_TBL *r,
		*rOldValues = &g_OldValues;
   tdef *pT = getSimpleTdefsByNumber(WEB_PAGE);


	if (row == NULL)
		r = &g_w_web_page;
	else
		r = row;

	if (!bInit)
	{
		/* setup invariant values */
		sprintf(szTemp, "%d-%d-%d", CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
		dToday = strtodate(szTemp);

		/* set up for the SCD handling */
		nConcurrent = (int)get_rowcount(CONCURRENT_WEB_SITES);
		nRevisions = (int)get_rowcount(WEB_PAGE) / nConcurrent;

		bInit = 1;
	}

	nullSet(&pT->kNullBitMap, WP_NULLS);
	r->wp_page_sk = index;

	/* if we have generated the required history for this business key and generate a new one 
	 * then reset associate fields (e.g., rec_start_date minimums)
	 */
	if (setSCDKeys(WP_PAGE_ID, index, r->wp_page_id, &r->wp_rec_start_date_id, &r->wp_rec_end_date_id))
	{

/* 
 * some fields are not changed, even when a new version of the row is written 
 */
		bFirstRecord = 1;
	}
	
 /*
  * this is  where we select the random number that controls if a field changes from 
  * one record to the next. 
  */
	nFieldChangeFlags = next_random(WP_SCD);

	r->wp_creation_date_sk = mk_join(WP_CREATION_DATE_SK, DATE, index);
	changeSCD(SCD_KEY, &r->wp_creation_date_sk, &rOldValues->wp_creation_date_sk,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&nAccess, DIST_UNIFORM, 0, WP_IDLE_TIME_MAX, 0, WP_ACCESS_DATE_SK);
	r->wp_access_date_sk = dToday->julian - nAccess;
	changeSCD(SCD_KEY, &r->wp_access_date_sk, &rOldValues->wp_access_date_sk,  &nFieldChangeFlags,  bFirstRecord);
   if (r->wp_access_date_sk == 0)
      r->wp_access_date_sk = -1;    /* special case for dates */

	genrand_integer(&nTemp, DIST_UNIFORM, 0, 99, 0, WP_AUTOGEN_FLAG);
	r->wp_autogen_flag = (nTemp < WP_AUTOGEN_PCT)?1:0;
	changeSCD(SCD_INT, &r->wp_autogen_flag, &rOldValues->wp_autogen_flag,  &nFieldChangeFlags,  bFirstRecord);

	r->wp_customer_sk = mk_join(WP_CUSTOMER_SK, CUSTOMER, 1);
	changeSCD(SCD_KEY, &r->wp_customer_sk, &rOldValues->wp_customer_sk,  &nFieldChangeFlags,  bFirstRecord);

	if (!r->wp_autogen_flag)
		r->wp_customer_sk = -1;

	genrand_url(r->wp_url, WP_URL);
	changeSCD(SCD_CHAR, &r->wp_url, &rOldValues->wp_url,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution(&r->wp_type, "web_page_use", 1, 1, WP_TYPE);
	changeSCD(SCD_PTR, &r->wp_type, &rOldValues->wp_type,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&r->wp_link_count, DIST_UNIFORM, WP_LINK_MIN, WP_LINK_MAX, 0, WP_LINK_COUNT);
	changeSCD(SCD_INT, &r->wp_link_count, &rOldValues->wp_link_count,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&r->wp_image_count, DIST_UNIFORM, WP_IMAGE_MIN, WP_IMAGE_MAX, 0, WP_IMAGE_COUNT);
	changeSCD(SCD_INT, &r->wp_image_count, &rOldValues->wp_image_count,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&r->wp_max_ad_count, DIST_UNIFORM, WP_AD_MIN, WP_AD_MAX, 0, WP_MAX_AD_COUNT);
	changeSCD(SCD_INT, &r->wp_max_ad_count, &rOldValues->wp_max_ad_count,  &nFieldChangeFlags,  bFirstRecord);

	genrand_integer(&r->wp_char_count, DIST_UNIFORM, 
		r->wp_link_count * 125 + r->wp_image_count * 50, 
		r->wp_link_count * 300 + r->wp_image_count * 150, 0, WP_CHAR_COUNT);
	changeSCD(SCD_INT, &r->wp_char_count, &rOldValues->wp_char_count,  &nFieldChangeFlags,  bFirstRecord);

	
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
pr_w_web_page(void *row)
{
	struct W_WEB_PAGE_TBL *r;

	if (row == NULL)
		r = &g_w_web_page;
	else
		r = row;

	print_start(WEB_PAGE);
	print_key(WP_PAGE_SK, r->wp_page_sk, 1);
	print_varchar(WP_PAGE_ID, r->wp_page_id, 1);
	print_date(WP_REC_START_DATE_ID, r->wp_rec_start_date_id, 1);
	print_date(WP_REC_END_DATE_ID, r->wp_rec_end_date_id, 1);
	print_key(WP_CREATION_DATE_SK, r->wp_creation_date_sk, 1);
	print_key(WP_ACCESS_DATE_SK, r->wp_access_date_sk, 1);
	print_boolean(WP_AUTOGEN_FLAG, r->wp_autogen_flag, 1);
	print_key(WP_CUSTOMER_SK, r->wp_customer_sk, 1);
	print_varchar(WP_URL, &r->wp_url[0], 1);
	print_varchar(WP_TYPE, &r->wp_type[0], 1);
	print_integer(WP_CHAR_COUNT, r->wp_char_count, 1);
	print_integer(WP_LINK_COUNT, r->wp_link_count, 1);
	print_integer(WP_IMAGE_COUNT, r->wp_image_count, 1);
	print_integer(WP_MAX_AD_COUNT, r->wp_max_ad_count, 0);
	print_end(WEB_PAGE);

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
ld_w_web_page(void *pSrc)
{
	struct W_WEB_PAGE_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_web_page;
	else
		r = pSrc;
	
	return(0);
}

