/*
* $Id: s_subclass.h,v 1.2 2004/11/24 23:54:20 jms Exp $
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
* $Log: s_subclass.h,v $
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#ifndef S_SUBCLASS_H
#define S_SUBCLASS_H

#define RS_S_SUBC_NAME	30
#define RS_S_SUBC_DESC	100

struct S_SUBCLASS_TBL {
	ds_key_t	kID;
	ds_key_t	kClassID;
	char		szName[RS_S_SUBC_NAME + 1];
	char		szDesc[RS_S_SUBC_DESC + 1];
};

int mk_s_subclass(void *pDest, ds_key_t kIndex);
int pr_s_subclass(void *pSrc);
int ld_s_subclass(void *pSrc);
#endif
