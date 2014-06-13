/*
* $Id: s_inventory.h,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: s_inventory.h,v $
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
#ifndef S_INVENTORY_H
#define S_INVENTORY_H

#define INVN_MIN_DATE	"1999-01-01"
#define INVN_MAX_DATE	"2003-12-31"
#define INVN_MIN_UPDATE_DATE	"2004-01-01"
#define INVN_UPDATE_DURATION	30
#define INVN_MIN_QUANTITY	0
#define INVN_MAX_QUANTITY	250

struct S_INVENTORY_TBL {
	ds_key_t	warehouse_id;
	ds_key_t	item_id;
	date_t		invn_date;
	int			quantity;
};

int mk_s_inventory(void *pDest, ds_key_t kIndex);
int pr_s_inventory(void *pSrc);
int ld_s_inventory(void *pSrc);
#endif
