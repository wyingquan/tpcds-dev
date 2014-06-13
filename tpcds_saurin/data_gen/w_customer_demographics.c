/*
* $Id: w_customer_demographics.c,v 1.10 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_customer_demographics.c,v $
* Revision 1.10  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.9  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.8  2006/08/24 22:32:07  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.7  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.6  2006/03/27 23:36:05  jms
* Problems identified by Meikel 3/27/06
*
* Revision 1.5  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.4  2005/01/13 22:54:16  jms
* Bug #136: sparse key support
*
* Revision 1.3  2005/01/13 19:50:02  jms
* Use sparse surrogate keys per Bug #136
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.3  2004/04/02 00:39:39  jms
* use ds_key_t in bitmap_to_dist for solaris
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
#include "w_customer_demographics.h"
#include "genrand.h"
#include "columns.h"
#include "build_support.h"
#include "constants.h"
#include "tables.h"
#include "print.h"
#include "nulls.h"
#include "tdefs.h"
#include "sparse.h"

struct W_CUSTOMER_DEMOGRAPHICS_TBL g_w_customer_demographics;

/*
* mk_customer_demographics
*/
int
mk_w_customer_demographics (void* row, ds_key_t index)
{
	int res = 0;
	
	struct W_CUSTOMER_DEMOGRAPHICS_TBL *r;
	ds_key_t kTemp;
   tdef *pTdef = getSimpleTdefsByNumber(CUSTOMER_DEMOGRAPHICS);

	if (row == NULL)
		r = &g_w_customer_demographics;
	else
		r = row;
	
	nullSet(&pTdef->kNullBitMap, CD_NULLS);
	r->cd_demo_sk = index;
	kTemp = r->cd_demo_sk - 1;
	bitmap_to_dist (&r->cd_gender, "gender", &kTemp, 1, CUSTOMER_DEMOGRAPHICS);
	bitmap_to_dist (&r->cd_marital_status, "marital_status", &kTemp, 1,
		CUSTOMER_DEMOGRAPHICS);
	bitmap_to_dist (&r->cd_education_status, "education", &kTemp, 1, CUSTOMER_DEMOGRAPHICS);
	bitmap_to_dist (&r->cd_purchase_estimate, "purchase_band", &kTemp, 1, CUSTOMER_DEMOGRAPHICS);
	bitmap_to_dist (&r->cd_credit_rating, "credit_rating", &kTemp, 1, CUSTOMER_DEMOGRAPHICS);
	r->cd_dep_count =
		(int) (kTemp % (ds_key_t) CD_MAX_CHILDREN);
	kTemp /= (ds_key_t) CD_MAX_CHILDREN;
	r->cd_dep_employed_count =
		(int) (kTemp % (ds_key_t) CD_MAX_EMPLOYED);
	kTemp /= (ds_key_t) CD_MAX_EMPLOYED;
	r->cd_dep_college_count =
		(int) (kTemp % (ds_key_t) CD_MAX_COLLEGE);
	
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
pr_w_customer_demographics(void *row)
{
	struct W_CUSTOMER_DEMOGRAPHICS_TBL *r;

	if (row == NULL)
		r = &g_w_customer_demographics;
	else
		r = row;

	print_start(CUSTOMER_DEMOGRAPHICS);
	print_key(CD_DEMO_SK, r->cd_demo_sk, 1);
	print_varchar(CD_GENDER, r->cd_gender, 1);
	print_varchar(CD_MARITAL_STATUS, r->cd_marital_status, 1);
	print_varchar(CD_EDUCATION_STATUS, r->cd_education_status, 1);
	print_integer(CD_PURCHASE_ESTIMATE, r->cd_purchase_estimate, 1);
	print_varchar(CD_CREDIT_RATING, r->cd_credit_rating, 1);
	print_integer(CD_DEP_COUNT, r->cd_dep_count, 1);
	print_integer(CD_DEP_EMPLOYED_COUNT, r->cd_dep_employed_count, 1);
	print_integer(CD_DEP_COLLEGE_COUNT, r->cd_dep_college_count, 0);
	print_end(CUSTOMER_DEMOGRAPHICS);

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
ld_w_customer_demographics(void *row)
{
	struct W_CUSTOMER_DEMOGRAPHICS_TBL *r;

	if (row == NULL)
		r = &g_w_customer_demographics;
	else
		r = row;

	return(0);
}

