/*
* $Id: dbgen_version.h,v 1.2 2004/11/24 23:54:15 jms Exp $
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
* $Log: dbgen_version.h,v $
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.1  2004/07/16 20:49:16  jms
* Generate dbgen_version table
*
*/
#ifndef DBGEN_VERSION_H
#define DBGEN_VERSION_H

#define RS_VERSION_LENGTH	16
#define RS_CMDLINARGS_LENGTH	200

struct DBGEN_VERSION_TBL {
	char		szVersion[RS_VERSION_LENGTH + 1];
	char		szDate[26];
	char		szTime[26];
	char		szCmdLineArgs[RS_CMDLINARGS_LENGTH + 1];
};

int mk_dbgen_version(void *pDest, ds_key_t kIndex);
int pr_dbgen_version(void *pSrc);
int ld_dbgen_version(void *pSrc);
#endif
