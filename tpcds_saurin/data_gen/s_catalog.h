/*
* $Id: s_catalog.h,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: s_catalog.h,v $
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#ifndef S_CATALOG_H
#define S_CATALOG_H
#include "date.h"

#define RS_S_CATALOG_DESC	50
#define S_CATALOG_DURATION_MIN	50		/* days a catlog is active */
#define S_CATALOG_DURATION_MAX	100
#define S_CATALOG_DESC_MIN		38		/* length of descriptive text */
#define S_CATALOG_DESC_MAX		50
#define S_CATALOG_TYPE_COUNT	10		/* number of catalog types */

/*
 * S_CATALOG table structure 
 */
struct S_CATALOG_TBL {
	ds_key_t	s_catalog_number;
	date_t		s_catalog_start_date;
	date_t		s_catalog_end_date;
	char		s_catalog_catalog_desc[RS_S_CATALOG_DESC + 1];
	int			s_catalog_catalog_type;
	};

int mk_s_catalog(void *pDest, ds_key_t kIndex);
int pr_s_catalog(void *pSrc);
int ld_s_catalog(void *pSrc);
#endif
