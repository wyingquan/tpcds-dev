/*
* $Id: w_store.h,v 1.5 2006/10/19 23:39:23 jms Exp $
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
* $Log: w_store.h,v $
* Revision 1.5  2006/10/19 23:39:23  jms
* Bug 498: source schema sync
*
* Revision 1.4  2005/10/31 19:29:37  jms
* changes to the source schema to move the views forward
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:22  jms
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
#ifndef W_STORE_H
#define W_STORE_H

#include "address.h"
#include "decimal.h"

#define RS_W_STORE_NAME	50
#define RS_W_STORE_MGR	40
#define RS_W_MARKET_MGR	40
#define RS_W_MARKET_DESC	100
#define STORE_MIN_TAX_PERCENTAGE	"0.00"
#define STORE_MAX_TAX_PERCENTAGE	"0.11"


/*
 * STORE table structure 
 */
struct W_STORE_TBL {
	ds_key_t	store_sk;
	char		store_id[RS_BKEY + 1];
	ds_key_t	rec_start_date_id;
	ds_key_t	rec_end_date_id;
	ds_key_t	closed_date_id;
	char		store_name[RS_W_STORE_NAME + 1];
	int			employees;
	int			floor_space;
	char		*hours;
	char		store_manager[RS_W_STORE_MGR + 1];
	int			market_id;
	decimal_t	dTaxPercentage;
	char		*geography_class;
	char		market_desc[RS_W_MARKET_DESC + 1];
	char		market_manager[RS_W_MARKET_MGR + 1];
	ds_key_t	division_id;
	char		*division_name;
	ds_key_t	company_id;
	char		*company_name;
	ds_addr_t	address;
};

/***
 *** STORE_xxx Store Defines
 ***/
#define STORE_MIN_DAYS_OPEN		5
#define STORE_MAX_DAYS_OPEN		500
#define STORE_CLOSED_PCT		30
#define STORE_MIN_REV_GROWTH	"-0.05"
#define STORE_MAX_REV_GROWTH	 "0.50"
#define STORE_DESC_MIN			15


int mk_w_store(void *pDest, ds_key_t kIndex);
int pr_w_store(void *pSrc);
int ld_w_store(void *pSrc);

#endif

