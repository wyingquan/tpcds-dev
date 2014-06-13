/*
* $Id: s_catalog_returns.h,v 1.5 2007/08/02 18:56:30 jms Exp $
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
* $Log: s_catalog_returns.h,v $
* Revision 1.5  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.4  2006/05/12 19:08:11  jms
* Bug 449: missing columns in s_catalog_returns
*
* Revision 1.3  2005/11/11 21:24:41  jms
* add return time to all channels in source schema
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
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#ifndef S_CATALOG_RETURNS_H
#define S_CATALOG_RETURNS_H

#include "pricing.h"

struct S_CATALOG_RETURNS_TBL {
	ds_key_t	kCallCenterID;
	ds_key_t	kOrderID;
	ds_key_t	kLineNumber;
	ds_key_t	kItemID;
	ds_key_t	kReturnCustomerID;
	ds_key_t	kRefundCustomerID;
	date_t		dtReturnDate;
	ds_key_t	kReturnTime;
	int			nQuantity;
	ds_pricing_t	Pricing;
	ds_key_t	kReasonID;
	ds_key_t	kCatalogPageID;
	ds_key_t	kShipModeID;
	ds_key_t	kWarehouseID;
};

int mk_s_catalog_returns(void *pDest, ds_key_t kIndex);
int pr_s_catalog_returns(void *pSrc);
int ld_s_catalog_returns(void *pSrc);
#endif
