/*
* $Id: w_warehouse.h,v 1.2 2004/11/24 23:54:22 jms Exp $
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
* $Log: w_warehouse.h,v $
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef W_WAREHOUSE_H
#define W_WAREHOUSE_H

#include "address.h"

/*
 * WAREHOUSE table structure 
 */
struct W_WAREHOUSE_TBL {
	ds_key_t	w_warehouse_sk;
	char		w_warehouse_id[RS_BKEY + 1];
	char		w_warehouse_name[RS_W_WAREHOUSE_NAME + 1];
	int			w_warehouse_sq_ft;
	ds_addr_t	w_address;
};

int mk_w_warehouse(void *pDest, ds_key_t kIndex);
int pr_w_warehouse(void *pSrc);
int ld_w_warehouse(void *pSrc);

#endif

