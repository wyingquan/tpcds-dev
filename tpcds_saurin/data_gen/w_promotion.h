/*
* $Id: w_promotion.h,v 1.3 2005/11/06 22:01:13 jms Exp $
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
* $Log: w_promotion.h,v $
* Revision 1.3  2005/11/06 22:01:13  jms
* first rework of source generation
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
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
#ifndef W_PROMOTION_H
#define W_PROMOTION_H
#include "constants.h"
/*
 * PROMOTION table structure 
 */
struct W_PROMOTION_TBL {
	ds_key_t	p_promo_sk;
	char		p_promo_id[RS_BKEY + 1];
	ds_key_t	p_start_date_id;
	ds_key_t	p_end_date_id;
	ds_key_t	p_item_sk;
	decimal_t	p_cost;
	int			p_response_target;
	char		p_promo_name[RS_P_PROMO_NAME + 1];
	int			p_channel_dmail;
	int			p_channel_email;
	int			p_channel_catalog;
	int			p_channel_tv;
	int			p_channel_radio;
	int			p_channel_press;
	int			p_channel_event;
	int			p_channel_demo;
	char		p_channel_details[RS_P_CHANNEL_DETAILS + 1];
	char		*p_purpose;
	int			p_discount_active;
};

int mk_w_promotion(void *pDest, ds_key_t kIndex);
int pr_w_promotion(void *pSrc);
int ld_w_promotion(void *pSrc);
#endif

