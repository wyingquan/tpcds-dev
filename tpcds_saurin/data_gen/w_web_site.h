/*
* $Id: w_web_site.h,v 1.4 2005/11/06 22:01:13 jms Exp $
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
* $Log: w_web_site.h,v $
* Revision 1.4  2005/11/06 22:01:13  jms
* first rework of source generation
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.5  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.4.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.4  2004/05/26 21:31:19  jms
* sync address elements, ordering (Bug #67, 69, 70, 71)
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
#ifndef W_WEB_SITE_H
#define W_WEB_SITE_H

#include "decimal.h"

#define WEB_MIN_TAX_PERCENTAGE	"0.00"
#define WEB_MAX_TAX_PERCENTAGE	"0.12"


/*
 * WEB_SITE table structure 
 */	
struct W_WEB_SITE_TBL {
	ds_key_t	web_site_sk;
	char		web_site_id[RS_BKEY + 1];
	ds_key_t	web_rec_start_date_id;
	ds_key_t	web_rec_end_date_id;
	char		web_name[RS_WEB_NAME + 1];
	ds_key_t	web_open_date;
	ds_key_t	web_close_date;
	char		web_class[RS_WEB_CLASS + 1];
	char		web_manager[RS_WEB_MANAGER + 1];
	int			web_market_id;
	char		web_market_class[RS_WEB_MARKET_CLASS + 1];
	char		web_market_desc[RS_WEB_MARKET_DESC + 1];
	char		web_market_manager[RS_WEB_MARKET_MANAGER + 1];
	int			web_company_id;
	char		web_company_name[RS_WEB_COMPANY_NAME + 1];
	ds_addr_t	web_address;
	decimal_t	web_tax_percentage;
	};

int mk_w_web_site(void *pDest, ds_key_t kIndex);
int pr_w_web_site(void *pSrc);
int ld_w_web_site(void *pSrc);
#endif

