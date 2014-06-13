/*
* $Id: build_support.h,v 1.4 2006/08/24 22:32:06 jms Exp $
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
* $Log: build_support.h,v $
* Revision 1.4  2006/08/24 22:32:06  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.3  2006/08/17 21:22:50  jms
* Bug 480
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.10  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.9.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.9  2004/04/02 18:17:30  jms
* porting concerns around bitmap_to_dist declaration
*
* Revision 1.8  2004/04/02 17:53:09  jms
* add random_to_bitmap() and dist_to_bitmap() to handle joins to demograhics tables which rely on composite keys
*
* Revision 1.7  2004/04/02 00:39:39  jms
* use ds_key_t in bitmap_to_dist for solaris
*
* Revision 1.6  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.5  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.10  2003/07/15 00:43:46  jms
* Porting changes for Linux
*
* Revision 1.9  2003/07/14 23:14:54  jms
* enable continuous scaling in integer GB
*
* Revision 1.8  2003/05/07 20:01:55  jms
* add embed_string() to include a random dist value into a pre-existing string of background noise
*
* Revision 1.7  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.6  2003/04/23 22:48:24  jms
* compiler errors under MP-RAS
*
* Revision 1.5  2003/04/16 00:21:45  jms
* data set alignment
*
* Revision 1.4  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.3  2002/09/04 17:23:42  jms
* Add mk_bkey as part of converting xx_id from ds_key_t to char[] for business keys
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.2  2002/07/18 22:08:39  jms
* isolating pricing calculations for the sales tables
* sync column names with WAM 10/11
*
* Revision 1.1.1.1.2.1  2002/07/04 01:05:45  jms
* Return type of bitmap_to_dist() now voiid * to allow char/int types
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef BUILD_SUPPORT_H
#define BUILD_SUPPORT_H
#include "decimal.h"
#include "date.h"
#include "dist.h"
#include "columns.h"
#include "pricing.h"

void bitmap_to_dist(void *pDest, char *distname, ds_key_t *modulus, int vset, int stream);
void dist_to_bitmap(int *pDest, char *szDistName, int nValue, int nWeight, int nStream);
void random_to_bitmap(int *pDest, int nDist, int nMin, int nMax, int nMean, int nStream);
int city_hash(int nTable, char *city);
void hierarchy_item(int h_level, ds_key_t *id, char **name, ds_key_t kIndex);
ds_key_t mk_join(int from_tbl, int to_tbl, ds_key_t ref_key);
ds_key_t getCatalogNumberFromPage(ds_key_t kPageNumber);
void mk_word(char *dest, char *syl_set, ds_key_t src, int char_cnt, int col);
int set_locale(int nRegion, decimal_t *longitude, decimal_t *latitude);
int adj_time(ds_key_t *res_date, ds_key_t *res_time, ds_key_t base_date, ds_key_t base_time, ds_key_t offset_key, int tabid);
void mk_bkey(char *szDest, ds_key_t kPrimary, int nStream);
int embed_string(char *szDest, char *szDist, int nValue, int nWeight, int nStream);
int SetScaleIndex(char *szName, char *szValue);
int mk_companyname(char *dest, int nTable, int nCompany);
void setUpdateDateRange(int nTable, date_t *pMinDate, date_t *pMaxDate);
#endif /* BUILD_SUPPORT_H */
