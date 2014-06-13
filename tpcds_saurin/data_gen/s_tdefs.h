/*
* $Id: s_tdefs.h,v 1.24 2007/09/10 18:10:36 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2004
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: s_tdefs.h,v $
* Revision 1.24  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.23  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.22  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.21  2007/07/31 06:07:39  jms
* bug 546: s_promotion
*
* Revision 1.20  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.19  2007/07/24 19:50:59  jms
* bug 546: s_customer_address
*
* Revision 1.18  2007/07/10 18:49:29  jms
* validate s_customer_address
*
* Revision 1.17  2006/08/18 23:18:06  jms
* Bug #475
*
* Revision 1.16  2006/05/12 20:33:01  jms
* Bug 447: add NOT NULL requirements to source schema
*
* Revision 1.15  2006/04/12 23:32:06  jms
* w_item scaling changes
*
* Revision 1.14  2006/04/11 16:45:16  jms
* Correct naming of child tables in verbose output
*
* Revision 1.13  2006/03/28 00:59:47  jms
* Catalog page changes from Meikel (3/27)
*
* Revision 1.12  2006/03/24 20:25:09  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.11  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.10  2006/03/09 16:38:59  jms
* Bug 360: update scaling and id's
*
* Revision 1.9  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.8  2006/03/09 00:53:50  jms
* Bug 402: assorted data errors in source schema
*
* Revision 1.7  2006/02/02 05:02:17  jms
* disable un-needed tables in the source schema
*
* Revision 1.6  2006/01/16 23:12:38  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.5  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.4  2005/04/21 17:56:04  jms
* changes to allow source data to load
*
* Revision 1.3  2005/01/13 19:53:11  jms
* Bug #136: sparse key support
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.4  2004/10/29 16:44:42  jms
* add s_zip_to_gmt to schema
*
* Revision 1.3  2004/10/19 23:24:15  jms
* correct source schema table scaling
*
* Revision 1.2  2004/06/03 21:09:39  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.1  2004/06/03 20:32:53  jms
* better tdefs/w_tdefs/s_tdefs handling
*
*/
tdef s_tdefs[] = { 
{"s_brand",				"s_br", FL_NOP|FL_SOURCE_DDL,  S_BRAND_START, S_BRAND_END, S_BRAND, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_customer_address",  "s_ca", FL_SOURCE_DDL|FL_PASSTHRU,  S_CUSTOMER_ADDRESS_START, S_CUSTOMER_ADDRESS_END, S_CUSTOMER_ADDRESS, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_call_center",		"s_cc", FL_SOURCE_DDL,  S_CALL_CENTER_START, S_CALL_CENTER_END, S_CALL_CENTER, -1, NULL, 0, 0, 0, 0x0, 0x02, NULL},
{"s_catalog",			"s_ct", FL_SOURCE_DDL|FL_NOP,  S_CATALOG_START, S_CATALOG_END, S_CATALOG, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_catalog_order",		"s_cord", FL_SOURCE_DDL|FL_PARENT|FL_DATE_BASED, S_CATALOG_ORDER_START, S_CATALOG_ORDER_END, S_CATALOG_ORDER, S_CATALOG_ORDER_LINEITEM, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_catalog_order_lineitem",  "s_cl", FL_SOURCE_DDL|FL_CHILD|FL_PARENT, S_CATALOG_ORDER_LINEITEM_START, S_CATALOG_ORDER_LINEITEM_END, S_CATALOG_ORDER_LINEITEM, S_CATALOG_RETURNS, NULL, 0, 0, 0, 0x0, 0x07, NULL},
{"s_catalog_page",		"s_cp", FL_SOURCE_DDL|FL_PASSTHRU,  S_CATALOG_PAGE_START, S_CATALOG_PAGE_END, S_CATALOG_PAGE, -1, NULL, 0, 0, 0, 0x0, 0x03, NULL},
{"s_catalog_promotional_item",    "s_ci", FL_NOP|FL_SOURCE_DDL, S_CATALOG_PROMOTIONAL_ITEM_START, S_CATALOG_PROMOTIONAL_ITEM_END, S_CATALOG_PROMOTIONAL_ITEM, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_catalog_returns",   "s_cr", FL_SOURCE_DDL|FL_CHILD, S_CATALOG_RETURNS_START, S_CATALOG_RETURNS_END, S_CATALOG_RETURNS, -1, NULL, 0, 0, 0, 0x0, 0x0E, NULL},
{"s_category",			"s_cg", FL_NOP|FL_SOURCE_DDL,  S_CATEGORY_START, S_CATEGORY_END, S_CATEGORY, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_class",				"s_cl", FL_NOP|FL_SOURCE_DDL,  S_CLASS_START, S_CLASS_END, S_CLASS, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_company",			"s_co", FL_NOP|FL_SOURCE_DDL,  S_COMPANY_START, S_COMPANY_END, S_COMPANY, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_customer",			"s_cu", FL_SOURCE_DDL,  S_CUSTOMER_START, S_CUSTOMER_END, S_CUSTOMER, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_division",			"s_di", FL_NOP|FL_SOURCE_DDL,  S_DIVISION_START, S_DIVISION_END, S_DIVISION, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_inventory",			"s_in", FL_SOURCE_DDL|FL_DATE_BASED,  S_INVENTORY_START, S_INVENTORY_END, S_INVENTORY, -1, NULL, 0, 0, 0, 0x0, 0x07, NULL},
{"s_item",				"s_it", FL_SOURCE_DDL,  S_ITEM_START, S_ITEM_END, S_ITEM, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_manager",			"s_mg", FL_NOP|FL_SOURCE_DDL,  S_MANAGER_START, S_MANAGER_END, S_MANAGER, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_manufacturer",		"s_mn", FL_NOP|FL_SOURCE_DDL,  S_MANUFACTURER_START, S_MANUFACTURER_END, S_MANUFACTURER, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_market",			"s_mk", FL_NOP|FL_SOURCE_DDL,  S_MARKET_START, S_MARKET_END, S_MARKET, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_product",			"s_pr", FL_NOP|FL_SOURCE_DDL,  S_PRODUCT_START, S_PRODUCT_END, S_PRODUCT, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_promotion",			"s_pm", FL_SOURCE_DDL|FL_PASSTHRU,  S_PROMOTION_START, S_PROMOTION_END, S_PROMOTION, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_purchase",			"s_pu", FL_SOURCE_DDL|FL_PARENT|FL_DATE_BASED, S_PURCHASE_START, S_PURCHASE_END, S_PURCHASE, S_PURCHASE_LINEITEM, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_purchase_lineitem", "s_pl", FL_SOURCE_DDL|FL_CHILD|FL_PARENT, S_PURCHASE_LINEITEM_START, S_PURCHASE_LINEITEM_END, S_PURCHASE_LINEITEM, S_STORE_RETURNS, NULL, 0, 0, 0, 0x0, 0x07, NULL},
{"s_reason",			"s_re", FL_NOP|FL_SOURCE_DDL,  S_REASON_START, S_REASON_END, S_REASON, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_store",				"s_st", FL_SOURCE_DDL,  S_STORE_START, S_STORE_END, S_STORE, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_store_promotional_item","s_sp",FL_NOP|FL_SOURCE_DDL,S_STORE_PROMOTIONAL_ITEM_START, S_STORE_PROMOTIONAL_ITEM_END, S_STORE_PROMOTIONAL_ITEM, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_store_returns",		"s_sr", FL_SOURCE_DDL|FL_CHILD, S_STORE_RETURNS_START, S_STORE_RETURNS_END, S_STORE_RETURNS, -1, NULL, 0, 0, 0, 0x0, 0x0E, NULL},
{"s_subcategory",		"s_ct", FL_NOP|FL_SOURCE_DDL,   S_SUBCATEGORY_START, S_SUBCATEGORY_END, S_SUBCATEGORY, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_subclass",			"s_sc", FL_NOP|FL_SOURCE_DDL,   S_SUBCLASS_START, S_SUBCLASS_END, S_SUBCLASS, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_warehouse",			"s_wh", FL_SOURCE_DDL,   S_WAREHOUSE_START, S_WAREHOUSE_END, S_WAREHOUSE, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_web_order",			"s_wo", FL_SOURCE_DDL|FL_PARENT|FL_DATE_BASED, S_WEB_ORDER_START, S_WEB_ORDER_END, S_WEB_ORDER, S_WEB_ORDER_LINEITEM, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_web_order_lineitem","s_wl", FL_SOURCE_DDL|FL_CHILD|FL_PARENT, S_WEB_ORDER_LINEITEM_START, S_WEB_ORDER_LINEITEM_END, S_WEB_ORDER_LINEITEM, S_WEB_RETURNS, NULL, 0, 0, 0, 0x0, 0x07, NULL},
{"s_web_page",			"s_wp", FL_SOURCE_DDL|FL_PASSTHRU,   S_WEB_PAGE_START, S_WEB_PAGE_END, S_WEB_PAGE, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_web_promotional_item","s_wi",FL_NOP|FL_SOURCE_DDL,  S_WEB_PROMOTIONAL_ITEM_START, S_WEB_PROMOTIONAL_ITEM_END, S_WEB_PROMOTIONAL_ITEM, -1, NULL, 0, 0, 0, 0x0, 0x0, NULL},
{"s_web_returns",		"s_wr", FL_SOURCE_DDL|FL_CHILD, S_WEB_RETURNS_START, S_WEB_RETURNS_END, S_WEB_RETURNS, -1, NULL, 0, 0, 0, 0x0, 0x0E, NULL},
{"s_web_site",			"s_ws", FL_SOURCE_DDL,   S_WEB_SITE_START, S_WEB_SITE_END, S_WEB_SITE, -1, NULL, 0, 0, 0, 0x0, 0x01, NULL},
{"s_zip_to_gmt",		"s_zi", FL_SOURCE_DDL|FL_VPRINT,   S_ZIPG_START, S_ZIPG_END, S_ZIPG, -1, NULL, 0, 0, 0, 0x0, 0x03, NULL},
{NULL}
};
