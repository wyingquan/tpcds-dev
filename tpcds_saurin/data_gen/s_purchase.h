/*
* $Id: s_purchase.h,v 1.6 2007/07/31 16:35:43 jms Exp $
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
* $Log: s_purchase.h,v $
* Revision 1.6  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.5  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
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
#ifndef S_PURCHASE_H
#define S_PURCHASE_H

#define RS_S_PURCHASE_COMMENT	100

struct S_PURCHASE_TBL {
	ds_key_t	kID;
	ds_key_t	kStoreID;
	ds_key_t	kCustomerID;
	date_t		dtPurchaseDate;
	int			nPurchaseTime;
	int			nRegister;
	int			nClerk;
	char		szComment[RS_S_PURCHASE_COMMENT + 1];
};

int mk_s_purchase(void *pDest, ds_key_t kIndex);
int pr_s_purchase(void *pSrc);
int ld_s_purchase(void *pSrc);
int vld_s_purchase(int nTable, ds_key_t kRow, int *pPermute);
#endif
