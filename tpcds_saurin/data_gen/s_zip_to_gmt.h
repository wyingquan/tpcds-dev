/*
* $Id: s_zip_to_gmt.h,v 1.4 2007/07/07 19:49:12 jms Exp $
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
* $Log: s_zip_to_gmt.h,v $
* Revision 1.4  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.3  2007/06/15 17:50:47  jms
* TPCDS Bug 546
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.1  2004/10/29 16:48:59  jms
* add s_zip_to_gmt.[ch] to distribution
*
*/
#ifndef S_ZIP_H
#define S_ZIP_H

struct S_ZIP_GMT_TBL {
	char		szZip[RS_ZIPG_ZIP + 1];
	int			nGMTOffset;
};

int mk_s_zip(void *pDest, ds_key_t kIndex);
int pr_s_zip(void *pSrc);
int ld_s_zip(void *pSrc);
int vld_s_zip(int nTable, ds_key_t kRow, int *Permutation);
#endif
