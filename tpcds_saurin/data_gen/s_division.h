/*
* $Id: s_division.h,v 1.3 2005/10/17 17:55:45 jms Exp $
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
* $Log: s_division.h,v $
* Revision 1.3  2005/10/17 17:55:45  jms
* add missing source schema columns
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
#ifndef S_DIVISION_H
#define S_DIVISION_H

#define RS_DIVISION_NAME		40
#define RS_DIVISION_COMPANY_NAME			40
#define DIVISIONS_PER_COMPANY	4

struct S_DIVISION_TBL {
	ds_key_t	id;
	char		name[RS_DIVISION_NAME + 1];
	ds_key_t	company;
	char		szCompanyName[RS_DIVISION_COMPANY_NAME + 1];
};

int mk_s_division(void *pDest, ds_key_t kIndex);
int pr_s_division(void *pSrc);
int ld_s_division(void *pSrc);
#endif
