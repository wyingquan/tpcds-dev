/*
* $Id: w_call_center.h,v 1.4 2005/11/11 21:58:01 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2003
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: w_call_center.h,v $
* Revision 1.4  2005/11/11 21:58:01  jms
* add tax percentages to all channels in both warehouse and source schemae
*
* Revision 1.3  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.4  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.3  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*/
#ifndef W_CALL_CENTER_H
#define W_CALL_CENTER_H
#include "constants.h"
#include "pricing.h"
#include "address.h"
#include "decimal.h"
#include "date.h"

#define MIN_CC_TAX_PERCENTAGE	"0.00"
#define MAX_CC_TAX_PERCENTAGE	"0.12"

/*
 * CALL_CENTER table structure 
 */
struct CALL_CENTER_TBL {
	ds_key_t	cc_call_center_sk;
	char		cc_call_center_id[RS_BKEY + 1]; 
	ds_key_t	cc_rec_start_date_id;
	ds_key_t	cc_rec_end_date_id;
	ds_key_t	cc_closed_date_id;
	ds_key_t	cc_open_date_id;
	char		cc_name[RS_CC_NAME + 1];
	char		*cc_class;
	int			cc_employees;
	int			cc_sq_ft;
	char		*cc_hours;
	char		cc_manager[RS_CC_MANAGER + 1];
	int			cc_market_id;
	char		cc_market_class[RS_CC_MARKET_CLASS + 1];
	char		cc_market_desc[RS_CC_MARKET_DESC + 1];
	char		cc_market_manager[RS_CC_MARKET_MANAGER + 1];
	int			cc_division_id;
	char		cc_division_name[RS_CC_DIVISION_NAME + 1];
	int			cc_company;
	char		cc_company_name[RS_CC_COMPANY_NAME + 1];
	ds_addr_t	cc_address;
	decimal_t	cc_tax_percentage;
};

int mk_w_call_center(void *pDest, ds_key_t kIndex);
int pr_w_call_center(void *pSrc);
int ld_w_call_center(void *r);

#endif

