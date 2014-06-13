/*
* $Id: s_catalog_page.h,v 1.6 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_catalog_page.h,v $
* Revision 1.6  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.5  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.4  2007/06/13 22:24:51  jms
* Bug 546: s_catalog_page
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
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#ifndef S_CATALOG_PAGE_H
#define S_CATALOG_PAGE_H
int mk_s_catalog_page(void *pDest, ds_key_t kIndex);
int pr_s_catalog_page(void *pSrc);
int ld_s_catalog_page(void *pSrc);
int vld_s_catalog_page(int nTable, ds_key_t kRow, int *Permutation);
#endif
