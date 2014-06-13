/*
* $Id: w_tdefs.h,v 1.28 2007/08/29 19:10:25 jms Exp $
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
* $Log: w_tdefs.h,v $
* Revision 1.28  2007/08/29 19:10:25  jms
* Bug 545
*
* Revision 1.27  2007/08/02 18:56:31  jms
* bug 546
*
* Revision 1.26  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.25  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.24  2006/12/12 18:52:21  jms
* one remaining PK issues for CR
*
* Revision 1.23  2006/12/12 07:15:12  jms
* invalid nulls on cr_order_number
*
* Revision 1.22  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.21  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.20  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.19  2006/03/28 19:25:49  jms
* PK viaolation in web_returns
*
* Revision 1.18  2006/03/28 19:10:19  jms
* PK viaolation in web_returns
*
* Revision 1.17  2006/02/03 06:01:24  jms
* resolve the catalog join issue
*
* Revision 1.16  2006/02/02 05:06:09  jms
* scale factor aware qgen
*
* Revision 1.15  2006/01/16 23:12:38  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.14  2006/01/02 21:37:45  jms
* Bug #356: bad SCD date ranges
*
* Revision 1.13  2005/11/14 15:17:54  jms
* correct NULL mapping
*
* Revision 1.12  2005/10/18 19:36:55  jms
* correct NULL generation
*
* Revision 1.11  2005/10/18 18:17:56  jms
* adjust NOT NULL bitmap
*
* Revision 1.10  2005/10/18 16:31:42  jms
* correct NOT NULL attributes
*
* Revision 1.9  2005/10/18 16:29:16  jms
* correct NOT NULL attributes
*
* Revision 1.8  2005/10/06 21:54:27  jms
* Bug 320: drop promotional_bundle, promotional_bundle_coverage
*
* Revision 1.7  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.6  2005/01/13 23:09:11  jms
* Bug #136: sparse key support
*
* Revision 1.5  2005/01/13 22:54:16  jms
* Bug #136: sparse key support
*
* Revision 1.4  2005/01/13 19:53:11  jms
* Bug #136: sparse key support
*
* Revision 1.3  2004/12/01 00:29:33  jms
* fix parallelism
*
* Revision 1.2  2004/11/24 23:54:22  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:11  jms
* re-establish external server
*
* Revision 1.13  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.12  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.11.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.11  2004/07/28 21:10:08  jms
* change name of time dimension table to match with current spec (bug reported by J. Susag)
*
* Revision 1.10  2004/07/14 23:50:23  jms
* Generate dbgen_version table
*
* Revision 1.9  2004/06/08 18:45:26  jms
* correct naming of date dimension
*
* Revision 1.8  2004/06/04 00:29:41  jms
* final 1.1.13b corrections
*
* Revision 1.7  2004/06/03 21:21:58  jms
* add missing parent/child link
*
* Revision 1.6  2004/06/03 21:09:39  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
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
*
*/
#ifndef W_TDEFS_H
#define W_TDEFS_H
tdef w_tdefs[] = { 
{"call_center", "cc", FL_TYPE_2|FL_SMALL, CALL_CENTER_START, CALL_CENTER_END, CALL_CENTER, -1, NULL, 0, 0, 100, 0, 0x0B, NULL}, 
{"catalog_page", "cp", 0, CATALOG_PAGE_START, CATALOG_PAGE_END, CATALOG_PAGE, -1, NULL, 0, 0, 200, 0, 0x03, NULL}, 
{"catalog_returns", "cr", FL_CHILD, CATALOG_RETURNS_START, CATALOG_RETURNS_END, CATALOG_RETURNS, -1, NULL, 0, 0, 400, 0, 0x10007, NULL}, 
{"catalog_sales", "cs", FL_PARENT|FL_DATE_BASED|FL_VPRINT, CATALOG_SALES_START, CATALOG_SALES_END, CATALOG_SALES, CATALOG_RETURNS, NULL, 0, 0, 100, 0, 0x28000, NULL}, 
{"customer", "cu", 0, CUSTOMER_START, CUSTOMER_END, CUSTOMER, -1, NULL, 0, 0, 700, 0, 0x13, NULL}, 
{"customer_address", "ca", 0, CUSTOMER_ADDRESS_START, CUSTOMER_ADDRESS_END, CUSTOMER_ADDRESS, -1, NULL, 0, 0, 600, 0, 0x03, NULL}, 
{"customer_demographics", "cd", 0, CUSTOMER_DEMOGRAPHICS_START, CUSTOMER_DEMOGRAPHICS_END, CUSTOMER_DEMOGRAPHICS, 823200, NULL, 0, 0, 0, 0, 0x1, NULL}, 
{"date_dim", "da", 0, DATE_START, DATE_END, DATE, -1, NULL, 0, 0, 0, 0, 0x03, NULL}, 
{"household_demographics", "hd", 0, HOUSEHOLD_DEMOGRAPHICS_START, HOUSEHOLD_DEMOGRAPHICS_END, HOUSEHOLD_DEMOGRAPHICS, 7200, NULL, 0, 0, 0, 0, 0x01, NULL}, 
{"income_band", "ib", 0, INCOME_BAND_START, INCOME_BAND_END, INCOME_BAND, -1, NULL, 0, 0, 0, 0, 0x1, NULL}, 
{"inventory", "inv", FL_DATE_BASED, INVENTORY_START, INVENTORY_END, INVENTORY, -1, NULL, 0, 0, 1000, 0, 0x07, NULL}, 
{"item", "it", FL_TYPE_2, ITEM_START, ITEM_END, ITEM, -1, NULL, 0, 0, 50, 0, 0x0B, NULL}, 
{"promotion", "pr", 0, PROMOTION_START, PROMOTION_END, PROMOTION, -1, NULL, 0, 0, 200, 0, 0x03, NULL}, 
{"reason", "re", 0, REASON_START, REASON_END, REASON, -1, NULL, 0, 0, 0, 0, 0x03, NULL}, 
{"ship_mode", "sm", 0, SHIP_MODE_START, SHIP_MODE_END, SHIP_MODE, -1, NULL, 0, 0, 0, 0, 0x03, NULL}, 
{"store", "st", FL_TYPE_2|FL_SMALL, STORE_START, STORE_END, STORE, -1, NULL, 0, 0, 100, 0, 0xB, NULL}, 
{"store_returns", "sr", FL_CHILD, STORE_RETURNS_START, STORE_RETURNS_END, STORE_RETURNS, -1, NULL, 0, 0, 700, 0, 0x204, NULL}, 
{"store_sales", "ss", FL_PARENT|FL_DATE_BASED|FL_VPRINT, STORE_SALES_START, STORE_SALES_END, STORE_SALES, STORE_RETURNS, NULL, 0, 0, 900, 0, 0x204, NULL}, 
{"time_dim", "ti", 0, TIME_START, TIME_END, TIME, -1, NULL, 0, 0, 0, 0, 0x03, NULL}, 
{"warehouse", "wa", FL_SMALL, WAREHOUSE_START, WAREHOUSE_END, WAREHOUSE, -1, NULL, 0, 0, 200, 0, 0x03, NULL}, 
{"web_page", "wp", FL_TYPE_2, WEB_PAGE_START, WEB_PAGE_END, WEB_PAGE, -1, NULL, 0, 0, 250, 0, 0x0B, NULL}, 
{"web_returns", "wr", FL_CHILD, WEB_RETURNS_START, WEB_RETURNS_END, WEB_RETURNS, -1, NULL, 0, 0, 900, 0, 0x2004, NULL}, 
{"web_sales", "ws", FL_VPRINT|FL_PARENT|FL_DATE_BASED, WEB_SALES_START, WEB_SALES_END, WEB_SALES, WEB_RETURNS, NULL, 0, 0, 5, 1100, 0x20008, NULL}, 
{"web_site", "web", FL_TYPE_2|FL_SMALL, WEB_SITE_START, WEB_SITE_END, WEB_SITE, -1, NULL, 0, 0, 100, 0, 0x0B, NULL}, 
{"dbgen_version", "dv", 0, DBGEN_VERSION_START, DBGEN_VERSION_END, DBGEN_VERSION, -1, NULL, 0, 0, 0, 0, 0, NULL}, 
{NULL}
};
#endif
