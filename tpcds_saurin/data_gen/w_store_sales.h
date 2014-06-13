/*
* $Id: w_store_sales.h,v 1.3 2007/07/24 20:07:30 jms Exp $
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
* $Log: w_store_sales.h,v $
* Revision 1.3  2007/07/24 20:07:30  jms
* bug 546
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.5  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.4  2004/03/26 22:49:26  jms
* revert to integer _sk fields
*
* Revision 1.3  2004/03/03 17:06:36  jms
* correct datatype for store sales join to store
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
#ifndef W_STORE_SALES_H
#define W_STORE_SLAES_H

#include "constants.h"
#include "pricing.h"


/*
 * STORE_SALES table structure 
 */
struct W_STORE_SALES_TBL {
	ds_key_t	ss_sold_date_sk;
	ds_key_t	ss_sold_time_sk;
	ds_key_t	ss_sold_item_sk;
	ds_key_t	ss_sold_customer_sk;
	ds_key_t	ss_sold_cdemo_sk;
	ds_key_t	ss_sold_hdemo_sk;
	ds_key_t	ss_sold_addr_sk;
	ds_key_t	ss_sold_store_sk;
	ds_key_t	ss_sold_promo_sk;
	ds_key_t	ss_ticket_number;
	ds_pricing_t	ss_pricing;
};

int mk_w_store_sales(void *pDest, ds_key_t kIndex);
int pr_w_store_sales(void *pSrc);
int ld_w_store_sales(void *pSrc);
int vld_w_store_sales(int nTable, ds_key_t kRow, int *Permutation);
#endif

