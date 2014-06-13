/*
* $Id: w_customer.c,v 1.7 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_customer.c,v $
* Revision 1.7  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.6  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.5  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.4  2006/05/10 22:03:23  jms
* Porting cleanup
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
* Revision 1.10  2004/11/17 21:25:36  jms
* Bug #106: Parallel data doesn't match serrially generated data
*
* Revision 1.9  2004/11/01 21:10:35  jms
* Populate birth date info in cusotmer tables
*
* Revision 1.8  2004/10/21 23:27:19  jms
* Distribution changes requested by Meikel on 10/15
*
* Revision 1.7  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.6  2004/07/16 22:09:45  jms
* simplify joins from customer to demographic tables
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/08 06:08:18  jms
* bug #56: c_current_cdemo_sk is always 0
*
* Revision 1.3  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
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
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "constants.h"
#include "columns.h"
#include "w_customer.h"
#include "genrand.h"
#include "build_support.h"
#include "tables.h"
#include "print.h"
#include "nulls.h"
#include "tdefs.h"

struct W_CUSTOMER_TBL g_w_customer;
/* extern tdef w_tdefs[]; */

/*
* Routine: mk_customer
* Purpose: populate the customer dimension
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
*/
int
mk_w_customer (void * row, ds_key_t index)
{
	int res = 0,
		nTemp;
	
	static int nBaseDate;
	/* begin locals declarations */
	int nNameIndex,
		nGender;
	struct W_CUSTOMER_TBL *r;
	static int bInit = 0;
	date_t dtTemp;
	static date_t dtBirthMin, 
		dtBirthMax,
		dtToday,
		dt1YearAgo,
		dt10YearsAgo;
   tdef *pT = getSimpleTdefsByNumber(CUSTOMER);

	if (row == NULL)
		r = &g_w_customer;
	else
		r = row;

	if (!bInit)
	{			
        nBaseDate = dttoj (strtodate (DATE_MINIMUM));
		strtodt(&dtBirthMax, "1992-12-31");
		strtodt(&dtBirthMin, "1924-01-01");
		strtodt(&dtToday, TODAYS_DATE);
		jtodt(&dt1YearAgo, dtToday.julian - 365);
		jtodt(&dt10YearsAgo, dtToday.julian - 3650);

		bInit = 1;
	}
	
	nullSet(&pT->kNullBitMap, C_NULLS);
	r->c_customer_sk = index;
	mk_bkey(&r->c_customer_id[0], index, C_CUSTOMER_ID);
	genrand_integer (&nTemp, DIST_UNIFORM, 1, 100, 0, C_PREFERRED_CUST_FLAG);
	r->c_preferred_cust_flag = (nTemp < C_PREFERRED_PCT) ? 1 : 0;

	/* demographic keys are a composite of values. rebuild them a la bitmap_to_dist */
	r->c_current_hdemo_sk = 
		mk_join(C_CURRENT_HDEMO_SK, HOUSEHOLD_DEMOGRAPHICS, 1);

	r->c_current_cdemo_sk = 
		mk_join(C_CURRENT_CDEMO_SK, CUSTOMER_DEMOGRAPHICS, 1);

	r->c_current_addr_sk =
		mk_join (C_CURRENT_ADDR_SK, CUSTOMER_ADDRESS, r->c_customer_sk);
	nNameIndex =
		pick_distribution (&r->c_first_name,
		"first_names", 1, 3, C_FIRST_NAME);
	pick_distribution (&r->c_last_name, "last_names", 1, 1, C_LAST_NAME);
	dist_weight (&nGender, "first_names", nNameIndex, 2);
	pick_distribution (&r->c_salutation,
		"salutations", 1, (nGender == 0) ? 2 : 3, C_SALUTATION);

	genrand_date(&dtTemp, DIST_UNIFORM, &dtBirthMin, &dtBirthMax, NULL, C_BIRTH_DAY);
	r->c_birth_day = dtTemp.day;
	r->c_birth_month = dtTemp.month;
	r->c_birth_year = dtTemp.year;
	genrand_email(r->c_email_address, r->c_first_name, r->c_last_name, C_EMAIL_ADDRESS);
	genrand_date(&dtTemp, DIST_UNIFORM, &dt1YearAgo, &dtToday, NULL, C_LAST_REVIEW_DATE);
	r->c_last_review_date = dtTemp.julian;
	genrand_date(&dtTemp, DIST_UNIFORM, &dt10YearsAgo, &dtToday, NULL, C_FIRST_SALES_DATE_ID);
	r->c_first_sales_date_id = dtTemp.julian;
    r->c_first_shipto_date_id = r->c_first_sales_date_id + 30;

    pick_distribution(&r->c_birth_country, "countries", 1, 1, C_BIRTH_COUNTRY);

	
	return (res);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
int
pr_w_customer(void *row)
{
	struct W_CUSTOMER_TBL *r;

	if (row == NULL)
		r = &g_w_customer;
	else
		r = row;

	print_start(CUSTOMER);
	print_key(C_CUSTOMER_SK, r->c_customer_sk, 1);
	print_varchar(C_CUSTOMER_ID, r->c_customer_id, 1);
	print_key(C_CURRENT_CDEMO_SK, r->c_current_cdemo_sk, 1);
	print_key(C_CURRENT_HDEMO_SK, r->c_current_hdemo_sk, 1);
	print_key(C_CURRENT_ADDR_SK, r->c_current_addr_sk, 1);
	print_integer(C_FIRST_SHIPTO_DATE_ID, r->c_first_shipto_date_id, 1);
	print_integer(C_FIRST_SALES_DATE_ID, r->c_first_sales_date_id, 1);
	print_varchar(C_SALUTATION, r->c_salutation, 1);
	print_varchar(C_FIRST_NAME, r->c_first_name, 1);
	print_varchar(C_LAST_NAME, r->c_last_name, 1);
	print_boolean(C_PREFERRED_CUST_FLAG, r->c_preferred_cust_flag, 1);
	print_integer(C_BIRTH_DAY, r->c_birth_day, 1);
	print_integer(C_BIRTH_MONTH, r->c_birth_month, 1);
	print_integer(C_BIRTH_YEAR, r->c_birth_year, 1);
	print_varchar(C_BIRTH_COUNTRY, r->c_birth_country, 1);
	print_varchar(C_LOGIN, &r->c_login[0], 1);
	print_varchar(C_EMAIL_ADDRESS, &r->c_email_address[0], 1);
	print_integer(C_LAST_REVIEW_DATE, r->c_last_review_date, 0);
	print_end(CUSTOMER);

	return(0);
}

/*
* Routine: 
* Purpose: 
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
int
ld_w_customer(void *row)
{
	struct W_CUSTOMER_TBL *r;

	if (row == NULL)
		r = &g_w_customer;
	else
		r = row;

	return(0);
}

