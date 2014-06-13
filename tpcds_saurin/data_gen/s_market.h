/*
* $Id: s_market.h,v 1.2 2004/11/24 23:54:20 jms Exp $
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
* $Log: s_market.h,v $
* Revision 1.2  2004/11/24 23:54:20  jms
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
#ifndef s_market_H
#define s_market_H

#define RS_S_MARKET_CLASS_NAME	50
#define RS_S_MARKET_CLASS_DESC		100

struct S_MARKET_TBL {
	ds_key_t	id;
	char		class_name[RS_S_MARKET_CLASS_NAME + 1];
	char		desc[RS_S_MARKET_CLASS_DESC + 1];
	ds_key_t	manager_id;
};

int mk_s_market(void *pDest, ds_key_t kIndex);
int pr_s_market(void *pSrc);
int ld_s_market(void *pSrc);
#endif
