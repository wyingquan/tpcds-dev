/*
* $Id: s_pline.h,v 1.6 2006/05/09 21:25:03 jms Exp $
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
* $Log: s_pline.h,v $
* Revision 1.6  2006/05/09 21:25:03  jms
* Correct purchase linenumber generation
*
* Revision 1.5  2005/11/11 18:58:37  jms
* add link between lineitem tables in the source shcema and the promotion table in the warehouse schema
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/10/31 19:28:45  jms
* changes to the source schema to move the views forward
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.3  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.2  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#ifndef S_PLINE_H
#define S_PLINE_H
#include "pricing.h"

#define RS_S_PLINE_COMMENT	100
#define PLINE_MIN_QUANTITY	1
#define PLINE_MAX_QUANTITY	100
#define PLINE_RETURN_PCT	3

struct S_PURCHASE_LINEITEM_TBL {
	ds_key_t	kPurchaseID;
	ds_key_t	kLineNumber;
	ds_key_t	kItemID;
	ds_key_t	kPromotionID;
	int			nRegister;
	int			nClerk;
	char		szComment[RS_S_PLINE_COMMENT + 1];
	ds_pricing_t	Pricing;
};

int mk_s_pline(void *pDest, ds_key_t kIndex);
int pr_s_pline(void *pSrc);
int ld_s_pline(void *pSrc);
#endif
