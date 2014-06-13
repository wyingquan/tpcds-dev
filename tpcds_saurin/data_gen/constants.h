/*
* $Id: constants.h,v 1.11 2006/10/25 01:00:32 jms Exp $
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
* $Log: constants.h,v $
* Revision 1.11  2006/10/25 01:00:32  jms
* scaling issues
*
* Revision 1.10  2006/03/09 15:08:59  jms
* Bug 360: update scaling and id's
*
* Revision 1.9  2006/02/10 17:15:33  jms
* Correct join calculation on catalog_page
*
* Revision 1.8  2006/02/03 06:01:24  jms
* resolve the catalog join issue
*
* Revision 1.7  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
*
* Revision 1.6  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.5  2005/04/12 21:04:11  jms
* 1.1.25 changes
*
* Revision 1.4  2005/03/15 22:37:03  jms
* Bug 146: invalid data in catalog_returns
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.20  2004/11/01 21:10:35  jms
* Populate birth date info in cusotmer tables
*
* Revision 1.19  2004/10/29 16:44:42  jms
* add s_zip_to_gmt to schema
*
* Revision 1.18  2004/09/23 17:36:03  jms
* Bug #94
*
* Revision 1.17  2004/08/20 19:41:57  jms
* changes from August F-2-F
*
* Revision 1.16  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.15  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.14  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.17  2003/06/10 19:31:10  jms
* Bug 27: base sales date distribution on step-function skew, and return dates as a uniform lag from sales/ship date (based on sales channel)
*
* Revision 1.16  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.15  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.14  2003/04/16 22:40:04  jms
* linux checkin of 1.1.0 pre-release
*
* Revision 1.13  2002/11/07 23:56:47  jms
* changes for DBGEN 1.0.6
*
* Revision 1.12  2002/11/05 06:24:46  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.11  2002/10/14 21:54:50  jms
* change date range for data set (issue 27)
*
* Revision 1.10  2002/09/25 22:46:59  jms
* commit all open changes to allow tighter issue/change tracking
*
* Revision 1.9  2002/09/04 18:26:40  jms
* Corrections to catalog page generation
*
* Revision 1.8  2002/09/04 17:22:31  jms
* Add constant defines for CP, CS, CC, PB
*
* Revision 1.7  2002/08/16 19:30:13  jms
* populate web_page
*
* Revision 1.6  2002/08/15 23:38:45  jms
* removed nested comment that caused compile problems on AIX
*
* Revision 1.5  2002/08/15 20:49:04  jms
* populate web_site
*
* Revision 1.4  2002/07/30 22:30:00  jms
* diff leftovers removed
*
* Revision 1.3  2002/07/27 00:08:30  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.2  2002/07/03 21:59:07  jms
* link content of sales/returns and set return percentage to 10%
*
* Revision 1.1.1.1.2.3  2002/07/18 22:47:33  jms
* xS_QUANTITY_MAX is treated as a string for the time being
*
* Revision 1.1.1.1.2.2  2002/07/18 22:05:23  jms
* isolating pricing calculations for the sales tables
*
* Revision 1.1.1.1.2.1  2002/07/04 01:18:59  jms
* Add C_PREFERRED_PCT to control c_preferred_cust_flag
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H
 /***
 *** Multi-table/Global Defines
 ***/
#define DATA_START_DATE		"1998-01-01"	/* earliest date in the data set */
#define DATA_END_DATE		"2003-12-31"	/* latest date in the data set */
#define LINES_PER_ORDER    16              /* max number of lineitems per order for all channels */

 /***
 *** C_xxx Cutomer Defines
 ***/
#define C_PREFERRED_PCT	50

/***
 *** CC_xxx Call Center Defines
 ***/
#define CC_EMPLOYEE_MAX		7				/* rises ~ scale ^ 2 */


/***
 *** CP_xxx Catalog Page Defines
 ***/
#define CP_CATALOGS_PER_YEAR	18
#define CP_SK(c, s, p)	(c * s + p)

 /***
 *** CR_xxx Catalog Returns Defines
 ***/
#define CR_RETURN_PCT	10	/* percentage of catalog sales that are returned */

 /***
 *** CS_xxx Customer Sales Defines
 ***/
#define CS_QUANTITY_MAX		"100"
#define CS_MARKUP_MAX		"2.00"
#define CS_DISCOUNT_MAX		"1.00"
#define CS_WHOLESALE_MAX	"100.00"
#define CS_COUPON_MAX		"0.50"
#define CS_MIN_SHIP_DELAY	2		/* minimum days from order to ship */
#define CS_MAX_SHIP_DELAY	90		/* maximum days from order to ship */
#define CS_ITEMS_PER_ORDER	10		/* number of items in each order */
#define CS_GIFT_PCT			10		/* ship-to != bill-to */

 /*
 * DATE SETTINGS
 *
 * The benchmarks sense of "today". Should this be a sliding scale/parameter?
 */
#define CURRENT_YEAR	2003
#define CURRENT_MONTH	1
#define CURRENT_DAY		8
#define CURRENT_QUARTER	1
#define CURRENT_WEEK	2
#define DATE_MINIMUM	"1998-01-01"
#define DATE_MAXIMUM	"2002-12-31"
#define YEAR_MINIMUM	1998
#define YEAR_MAXIMUM	2002
#define WAREHOUSE_LOAD_DATE	"2001-07-18"
#define UPDATE_INTERVAL		30	/* refresh interval in days */
#define TODAYS_DATE	"2003-01-08"

/***
 *** INV_xxx Inventory Defines
 ***/
#define INV_QUANTITY_MIN	0
#define INV_QUANTITY_MAX	1000

/***
 *** ITEM_xxx Item Defines
 ***/
#define ITEM_DESC_LEN		5
#define ITEM_NAME_LEN		10
#define ITEM_MANFACTURER_COUNT 1000	/* number of brands handled by a particular manufacturer */

/***
 *** PROMO_xxx Promotions Defines
 ***/
#define PROMO_NAME_LEN		5
#define PROMO_START_MIN		-720
#define PROMO_START_MAX		100
#define PROMO_START_MEAN	0
#define PROMO_LEN_MIN		1
#define PROMO_LEN_MAX		60
#define PROMO_LEN_MEAN		0
#define PROMO_DETAIL_LEN_MIN		20
#define PROMO_DETAIL_LEN_MAX		60

 /***
 *** SR_xxx Store Returns Defines
 ***/
#define SR_RETURN_PCT	10	/* percentage of store sales that are returned */

 /***
 *** SS_xxx Store Sales Defines
 ***/
#define SS_MIN_SHIP_DELAY	2		/* minimum days from order to ship */
#define SS_MAX_SHIP_DELAY	90		/* maximum days from order to ship */
#define SS_QUANTITY_MAX		"100"
#define SS_MARKUP_MAX		"1.00"
#define SS_DISCOUNT_MAX		"1.00"
#define SS_WHOLESALE_MAX	"100.00"
#define SS_COUPON_MAX		"0.50"

 /***
 *** WP_xxx Web Page Defines
 ***/
#define WP_AUTOGEN_PCT	30
#define WP_LINK_MIN		2
#define WP_LINK_MAX		25
#define WP_IMAGE_MIN	1
#define WP_IMAGE_MAX	7
#define WP_AD_MIN		0
#define WP_AD_MAX		4
#define WP_MAX_REC_DURATION	1000	/* maximum time from start to end of record */
#define WP_IDLE_TIME_MAX	100		/* maximum time since last page access */

 /***
 *** W_xxx Warehouse Defines
 ***/
#define W_DESC_MIN		5
#define W_SQFT_MIN		50000
#define W_SQFT_MAX		1000000
#define W_NAME_MIN		10

 /***
 *** WR_xxx Web Returns Defines
 ***/
#define WR_RETURN_PCT	10	/* percentage of web sales that are returned */
#define WR_SHIP_LAG_MIN	2	/* lag time between receiving and returning */
#define WR_SHIP_LAG_MAX	12

 /***
 *** WEB_xxx Web Site Defines
 ***/
#define WEB_START_DATE			DATE_MINIMUM	/* range of open/close dates; actual dates can exceed these values */
#define WEB_END_DATE			DATE_MAXIMUM	/* due to staggered start of each site */
#define WEB_DATE_STAGGER		17				/* time between site creation on leading/trailing edge */
#define WEB_PAGES_PER_SITE		123				/* number of pages on a web site */
/* some of the web sites are completely replaced in the date range. */
#define WEB_MORTALITY			50				/* percentage of sites that "die" between start and end */
#define WEB_IS_REPLACED(j)		((j % (100 / WEB_MORTALITY)) == 0)	/* does this site get replaced? */
#define WEB_IS_REPLACEMENT(j)	((j / (100 / WEB_MORTALITY)) % 2)	/* is this the replacement? */

/***
 *** SOURCE SCHEMA CONSTANTS
 ***/
#define DAYS_PER_UPDATE	3

 /***
 *** RS_xxx: Row and column sizes
 ***/
/* sizes used in various tables */
#define RS_BKEY				16
/* table-specific sizes */

#define RS_BRND_NAME		50
#define RS_C_SALUTATION		5
#define RS_C_FIRST_NAME		20
#define RS_C_LAST_NAME		30
#define RS_C_BIRTH_COUNTRY	20
#define RS_C_LOGIN			13
#define RS_C_PASSWORD		13
#define RS_C_EMAIL			50
#define RS_C_PRIMARY_MACHINE_ID		15
#define RS_C_SECONDARY_MACHINE_ID	15
#define RS_CA_SUITE_NUMBER	10
#define RS_CA_STREET_NAME	60
#define RS_CA_STREET_TYPE	15
#define RS_CA_CITY			60
#define RS_CA_COUNTY		30
#define RS_CA_STATE			2
#define RS_CA_COUNTRY		20
#define RS_CA_ZIP			10
#define RS_CA_LOCATION_TYPE	20
#define RS_CATG_DESC		20
#define RS_CC_NAME			50
#define RS_CC_CLASS			50
#define RS_CC_HOURS			20
#define RS_CC_MANAGER		40
#define RS_CC_MARKET_MANAGER	40
#define RS_CC_MARKET_CLASS	50
#define RS_CC_MARKET_DESC	100
#define RS_CC_DIVISION_NAME	50
#define RS_CC_COMPANY_NAME	60
#define RS_CC_SUITE_NUM		10
#define RS_CC_STREET_NAME	60
#define RS_CC_STREET_TYPE	15
#define RS_CC_CITY			60
#define RS_CC_COUNTY		30
#define RS_CC_STATE			2
#define RS_CC_COUNTRY		20
#define RS_CC_ZIP			10
#define RS_CD_GENDER		1
#define RS_CD_MARITAL_STATUS	1
#define RS_CD_EDUCATION_STATUS	20
#define RS_CD_CREDIT_RATING	10
#define RS_CP_DEPARTMENT	20
#define RS_CLAS_DESC		100
#define RS_CMPY_NAME	50
#define RS_CP_DESCRIPTION	100
#define RS_CP_TYPE			100
#define RS_CTGR_NAME		25
#define RS_CTGR_DESC		100
#define RS_CUST_CREDIT		100
#define RS_D_DAY_NAME		4
#define RS_D_QUARTER_NAME	4
#define RS_DVSN_NAME		50
#define RS_HD_BUY_POTENTIAL	7
#define RS_I_ITEM_DESC		200
#define RS_I_BRAND			50
#define RS_I_SUBCLASS		50
#define RS_I_CLASS			50
#define RS_I_SUBCATEGORY	50
#define RS_I_CATEGORY		50
#define RS_I_MANUFACT		50
#define RS_I_SIZE			20
#define RS_I_FORMULATION	20
#define RS_I_FLAVOR			20
#define RS_I_UNITS			10
#define	RS_I_CONTAINER		10
#define RS_I_PRODUCT_NAME	50
#define RS_MANF_NAME		50
#define RS_MNGR_NAME		50
#define RS_P_PROMO_NAME		50
#define RS_P_CHANNEL_DETAILS	100
#define RS_P_PURPOSE		15
#define RS_PB_DESCRIPTION	100
#define RS_PLIN_COMMENT		100
#define RS_PROD_NAME		100
#define RS_PROD_TYPE		100
#define RS_R_REASON_DESCRIPTION	100
#define RS_STORE_NAME		50
#define RS_STORE_HOURS			20
#define RS_S_STORE_MANAGER		40
#define RS_S_GEOGRAPHY_CLASS	100
#define RS_S_MARKET_DESC	100
#define RS_S_MARKET_MANAGER		40
#define RS_S_DIVISION_NAME	50
#define RS_S_COMPANY_NAME	50
#define RS_S_SUITE_NUM		10
#define RS_S_STREET_NAME	60
#define RS_S_STREET_TYPE	15
#define RS_S_CITY			60
#define RS_S_STATE			2
#define RS_S_COUNTY			30
#define RS_S_COUNTRY		30
#define RS_S_ZIP			10
#define RS_SM_TYPE			30
#define RS_SM_CODE			10
#define RS_SM_CONTRACT		20
#define RS_SM_CARRIER		20
#define RS_SBCT_NAME		100
#define RS_SBCT_DESC		100
#define RS_SUBC_NAME		100
#define RS_SUBC_DESC		100
#define RS_T_AM_PM			2
#define RS_T_SHIFT			20
#define RS_T_SUB_SHIFT		20
#define RS_T_MEAL_TIME		20
#define RS_W_WAREHOUSE_NAME	20
#define RS_W_STREET_NAME	60
#define RS_W_SUITE_NUM		10
#define RS_W_STREET_TYPE	15
#define RS_W_CITY			60
#define RS_W_COUNTY			30
#define RS_W_STATE			2
#define RS_W_COUNTRY		20
#define RS_W_ZIP			10
#define RS_WEB_MANAGER			50
#define RS_WEB_NAME			50
#define RS_WEB_CLASS		50
#define RS_WEB_MARKET_CLASS	50
#define RS_WEB_MARKET_DESC		100
#define RS_WEB_MARKET_MANAGER		40
#define RS_WEB_COMPANY_NAME	100
#define RS_WEB_SUITE_NUMBER	10
#define RS_WEB_STREET_NAME	60
#define RS_WEB_STREET_TYPE	15
#define RS_WEB_CITY			60
#define RS_WEB_COUNTY		30
#define RS_WEB_STATE		2
#define RS_WEB_COUNTRY		20
#define RS_WEB_ZIP			10
#define RS_WP_URL			100
#define RS_WEB_TYPE			50
#define RS_WRHS_DESC		100
#define RS_WORD_COMMENT		100
#define RS_ZIPG_ZIP			5
#endif /* CONSTANTS_H */
