/*
* $Id: w_item.h,v 1.7 2007/07/27 22:05:18 jms Exp $
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
* $Log: w_item.h,v $
* Revision 1.7  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.6  2007/01/09 22:11:27  jms
* bug 525
*
* Revision 1.5  2005/11/11 21:09:04  jms
* add i_wholesale_cost
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/10/17 17:58:00  jms
* date join range change
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.3  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS BaselineL
*
*/
#ifndef W_ITEM_H
#define W_ITEM_H
#include "constants.h"

#define I_PROMO_PERCENTAGE	20	/* percent of items that have associated promotions */
#define MIN_ITEM_MARKDOWN_PCT		"0.30"
#define MAX_ITEM_MARKDOWN_PCT		"0.90"

/*
 * ITEM table structure 
 */
struct W_ITEM_TBL {
	ds_key_t	i_item_sk;
	char		i_item_id[RS_BKEY + 1];
	ds_key_t	i_rec_start_date_id;
	ds_key_t	i_rec_end_date_id;
	char		i_item_desc[RS_I_ITEM_DESC + 1];
	decimal_t	i_current_price;	/* list price */
	decimal_t	i_wholesale_cost;
	ds_key_t	i_brand_id;
	char		i_brand[RS_I_BRAND + 1];
	ds_key_t	i_class_id;
	char		*i_class;
	ds_key_t	i_category_id;
	char		*i_category;
	ds_key_t	i_manufact_id;
	char		i_manufact[RS_I_MANUFACT + 1];
	char		*i_size;
	char		i_formulation[RS_I_FORMULATION + 1];
	char		*i_color;
	char		*i_units;
	char		*i_container;
	ds_key_t	i_manager_id;
	char		i_product_name[RS_I_PRODUCT_NAME + 1];
	ds_key_t	i_promo_sk;
};


int mk_w_item(void *pDest, ds_key_t kIndex);
int pr_w_item(void *pSrc);
int ld_w_item(void *pSrc);
int vld_w_item(int nTable, ds_key_t kRow, int *Permutation);
#endif

