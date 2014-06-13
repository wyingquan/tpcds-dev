/*
* $Id: w_web_sales.h,v 1.4 2007/07/07 19:49:12 jms Exp $
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
* $Log: w_web_sales.h,v $
* Revision 1.4  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.3  2007/05/23 18:11:59  jms
* TPCDS Bug 546
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.4  2004/05/26 17:11:32  jms
* add generation of ws_web_site_sk and standardize column names (sk vs id)
*
* Revision 1.3  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
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
/*
 * WEB_SALES table structure 
 */
struct W_WEB_SALES_TBL {
	ds_key_t	ws_sold_date_sk;
	ds_key_t	ws_sold_time_sk;
	ds_key_t	ws_ship_date_sk;
	ds_key_t	ws_item_sk;
	ds_key_t	ws_bill_customer_sk;
	ds_key_t	ws_bill_cdemo_sk;
	ds_key_t	ws_bill_hdemo_sk;
	ds_key_t	ws_bill_addr_sk;
	ds_key_t	ws_ship_customer_sk;
	ds_key_t	ws_ship_cdemo_sk;
	ds_key_t	ws_ship_hdemo_sk;
	ds_key_t	ws_ship_addr_sk;
	ds_key_t	ws_web_page_sk;
	ds_key_t	ws_web_site_sk;
	ds_key_t	ws_ship_mode_sk;
	ds_key_t	ws_warehouse_sk;
	ds_key_t	ws_promo_sk;
	ds_key_t	ws_order_number;
	ds_pricing_t	ws_pricing;
};

 /***
 *** WS_xxx Web Sales Defines
 ***/
#define WS_QUANTITY_MAX		"100"
#define WS_MARKUP_MAX		"2.00"
#define WS_DISCOUNT_MAX		"1.00"
#define WS_WHOLESALE_MAX	"100.00"
#define WS_COUPON_MAX		"0.50"
#define WS_GIFT_PCT			7			/* liklihood that a purchase is shipped to someone else */
#define WS_ITEMS_PER_ORDER	9			/* number of lineitems in an order */
#define WS_MIN_SHIP_DELAY	1			/* time between order date and ship date */
#define WS_MAX_SHIP_DELAY	120


int mk_w_web_sales(void *pDest, ds_key_t kIndex);
int pr_w_web_sales(void *pSrc);
int ld_w_web_sales(void *pSrc);
int vld_web_sales(int nTable, ds_key_t kRow, int *Permutation);

