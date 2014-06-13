/*
* $Id: w_customer.h,v 1.3 2006/11/30 00:18:25 jms Exp $
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
* $Log: w_customer.h,v $
* Revision 1.3  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
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
#ifndef W_CUSTOMER_H
#define W_CUSTOMER_H

/*
 * CUSTOMER table structure 
 */
struct W_CUSTOMER_TBL {
	ds_key_t	c_customer_sk;
	char		c_customer_id[RS_BKEY + 1];
	ds_key_t	c_current_cdemo_sk;
	ds_key_t	c_current_hdemo_sk;
	ds_key_t	c_current_addr_sk;
	int		c_first_shipto_date_id;
	int		c_first_sales_date_id;
	char	*c_salutation;
	char	*c_first_name;
	char	*c_last_name;
	int		c_preferred_cust_flag;
	int		c_birth_day;
	int		c_birth_month;
	int		c_birth_year;
	char	*c_birth_country;
	char	c_login[RS_C_LOGIN + 1];
	char	c_email_address[RS_C_EMAIL + 1];
	int		c_last_review_date;
};


int mk_w_customer(void *pDest, ds_key_t kIndex);
int pr_w_customer(void *pSrc);
int ld_w_customer(void *pSrc);
#endif

