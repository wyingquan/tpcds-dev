/*
* $Id: w_web_returns.h,v 1.4 2005/11/06 22:01:13 jms Exp $
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
* $Log: w_web_returns.h,v $
* Revision 1.4  2005/11/06 22:01:13  jms
* first rework of source generation
*
* Revision 1.3  2005/03/04 22:00:44  jms
* update to WAM, removal of sold_date info from returns tables
*
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
#ifndef W_WEB_RETURNS_H
#define W_WEB_RETURNS_H
/*
 * WEB_RETURNS table structure 
 */
struct W_WEB_RETURNS_TBL {
	ds_key_t	wr_returned_date_sk;
	ds_key_t	wr_returned_time_sk;
	ds_key_t	wr_item_sk;
	ds_key_t	wr_refunded_customer_sk;
	ds_key_t	wr_refunded_cdemo_sk;
	ds_key_t	wr_refunded_hdemo_sk;
	ds_key_t	wr_refunded_addr_sk;
	ds_key_t	wr_returning_customer_sk;
	ds_key_t	wr_returning_cdemo_sk;
	ds_key_t	wr_returning_hdemo_sk;
	ds_key_t	wr_returning_addr_sk;
	ds_key_t	wr_web_page_sk;
	ds_key_t	wr_reason_sk;
	ds_key_t	wr_order_number;
	ds_pricing_t	wr_pricing;
};

int mk_w_web_returns(void *pDest, ds_key_t kIndex);
int pr_w_web_returns(void *pSrc);
int ld_w_web_returns(void *pSrc);
#endif

