/*
* $Id: s_customer.c,v 1.23 2007/07/31 05:16:03 jms Exp $
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
* $Log: s_customer.c,v $
* Revision 1.23  2007/07/31 05:16:03  jms
* bug 546: s_cusomter
*
* Revision 1.22  2007/05/25 15:38:52  jms
* TPCDS Bug 546
*
* Revision 1.21  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.20  2006/08/24 22:32:07  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.19  2006/05/09 00:23:39  jms
* Changes requested by Meikel 5/8/06
*
* Revision 1.18  2006/05/08 23:04:59  jms
* Changes requested by Meikel 5/8/06
*
* Revision 1.17  2006/05/04 23:12:20  jms
* Bug 443: zip codes don't match in s_customer
*
* Revision 1.16  2006/05/02 19:44:17  jms
* bug 443: bad format of s_customer_zip
*
* Revision 1.15  2006/04/10 23:37:31  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.14  2006/03/30 23:23:45  jms
* bug reports from Meikel 3/30
*
* Revision 1.13  2006/03/30 16:40:30  jms
* bug reports from Meikel 3/29
*
* Revision 1.12  2006/03/28 19:03:23  jms
* additional testing of updates from Meikel
*
* Revision 1.11  2006/03/27 23:36:05  jms
* Problems identified by Meikel 3/27/06
*
* Revision 1.10  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.9  2006/03/17 22:55:39  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.8  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.7  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.6  2006/01/02 23:01:28  jms
* Bug #360: sk often default to 1 in update set
*
* Revision 1.5  2006/01/02 21:37:06  jms
* Bug #358: invalid dates in s_customer.csv
*
* Revision 1.4  2006/01/02 20:52:45  jms
* Bug #355: s_customer.csv has (null) for non-generated values
*
* Revision 1.3  2005/10/31 19:28:45  jms
* changes to the source schema to move the views forward
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.11  2004/11/01 21:10:35  jms
* Populate birth date info in cusotmer tables
*
* Revision 1.10  2004/10/27 22:51:51  jms
* Source data corrections from Ruth's research
*
* Revision 1.9  2004/10/20 21:30:00  jms
* add missing static declarations
*
* Revision 1.8  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
*
* Revision 1.7  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.6  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.5  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.4  2004/03/26 22:55:03  jms
* correct arg 1 for call to getUpdateID
*
* Revision 1.3  2004/03/26 22:08:24  jms
* change genrand_address to mk_address
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "s_customer.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "address.h"
#include "scaling.h"
#include "parallel.h"
#include "w_customer_demographics.h"
#include "w_customer_address.h"
#include "permute.h"

struct S_CUSTOMER_TBL g_s_customer;
extern struct W_CUSTOMER_ADDRESS_TBL g_w_customer_address;

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
mk_s_customer (void *pDest, ds_key_t kIndex)
{
  static int bInit = 0;
  struct S_CUSTOMER_TBL *r;
  static date_t dtMin,
    dtMax, dtBirthMin, dtBirthMax, dtToday, dt1YearAgo, dt10YearsAgo;
  static decimal_t dMinIncome, dMaxIncome;
  int nTemp;
  ds_key_t kTempDemographic;
  char *szTemp;
  static int *pPermutation;

  if (pDest == NULL)
    r = &g_s_customer;
  else
    r = pDest;

  if (!bInit)
    {
      memset (&g_s_customer, 0, sizeof (struct S_CUSTOMER_TBL));
      setUpdateDateRange (S_CUSTOMER, &dtMin, &dtMax);
      strtodec (&dMinIncome, "0.00");
      strtodec (&dMaxIncome, "200000.00");
      r->pBirthCountry = strdup ("<UNKNOWN>");
      strtodt (&dtBirthMin, "1924-01-01");
      strtodt (&dtBirthMax, "1992-12-31");
      strtodt (&dtToday, TODAYS_DATE);
      jtodt (&dt1YearAgo, dtToday.julian - 365);
      jtodt (&dt10YearsAgo, dtToday.julian - 365);
      pPermutation =
	makePermutation (NULL, (int) getIDCount (CUSTOMER), S_CUST_ID);

      bInit = 1;
    }

  r->kID = getPermutationEntry (pPermutation, (int) kIndex);
  kTempDemographic = mk_join (S_CUST_GENDER, CUSTOMER_DEMOGRAPHICS, 1) - 1;
  bitmap_to_dist (&szTemp, "gender", &kTempDemographic, 1,
		  CUSTOMER_DEMOGRAPHICS);
  switch (*szTemp)
    {
    case 'M':			/* male */
      r->sGender[0] = 'M';
      pick_distribution (&r->pFirstName, "first_names", 1, 1,
			 S_CUST_FIRST_NAME);
      pick_distribution (&r->pSalutation, "salutations", 1, 2,
			 S_CUST_SALUTATION);
      break;
    case 'F':			/* female */
      r->sGender[0] = 'F';
      pick_distribution (&r->pFirstName, "first_names", 1, 2,
			 S_CUST_FIRST_NAME);
      pick_distribution (&r->pSalutation, "salutations", 1, 3,
			 S_CUST_SALUTATION);
      break;
    default:			/* gender neutral */
      r->sGender[0] = 'U';
      pick_distribution (&r->pFirstName, "first_names", 1, 3,
			 S_CUST_FIRST_NAME);
      pick_distribution (&r->pSalutation, "salutations", 1, 1,
			 S_CUST_SALUTATION);
      break;
    }
  bitmap_to_dist (&r->pMaritalStatus, "marital_status", &kTempDemographic, 1,
		  CUSTOMER_DEMOGRAPHICS);
  bitmap_to_dist (&r->pEducation, "education", &kTempDemographic, 1,
		  CUSTOMER_DEMOGRAPHICS);
  bitmap_to_dist (&r->nPurchaseEstimate, "purchase_band", &kTempDemographic,
		  1, CUSTOMER_DEMOGRAPHICS);
  bitmap_to_dist (&r->pCreditRating, "credit_rating", &kTempDemographic, 1,
		  CUSTOMER_DEMOGRAPHICS);
  r->nDependents = (int) (kTempDemographic % (ds_key_t) CD_MAX_CHILDREN);
  kTempDemographic /= (ds_key_t) CD_MAX_CHILDREN;
  r->nEmployed = (int) (kTempDemographic % (ds_key_t) CD_MAX_EMPLOYED);
  kTempDemographic /= (ds_key_t) CD_MAX_EMPLOYED;
  r->nCollege = (int) (kTempDemographic % (ds_key_t) CD_MAX_COLLEGE);

  pick_distribution (&r->pLastName, "last_names", 1, 1, S_CUST_LAST_NAME);
  r->bPreferredFlag =
    (genrand_integer (NULL, DIST_UNIFORM, 1, 100, 0, S_CUST_PREFERRED_FLAG) >
     50) ? 1 : 0;
  genrand_date (&r->dtBirthDate, DIST_UNIFORM, &dtBirthMin, &dtBirthMax, NULL,
		S_CUST_BIRTH_DATE);
  genrand_date (&r->dtFirstPurchaseDate, DIST_UNIFORM, &dt10YearsAgo,
		&dt1YearAgo, NULL, S_CUST_FIRST_PURCHASE_DATE);
  genrand_integer (&nTemp, DIST_UNIFORM, 1, 30, 0, S_CUST_FIRST_SHIPTO_DATE);
  jtodt (&r->dtFirstShipToDate, r->dtFirstPurchaseDate.julian + nTemp);
  gen_charset (r->szLogin, ALPHANUM, 5, RS_S_CUST_LOGIN, S_CUST_LOGIN);
  genrand_email (r->szEmail, r->pFirstName, r->pLastName, S_CUST_EMAIL);
  genrand_date (&r->dtLastLogin, DIST_UNIFORM, &dt1YearAgo, &dtToday, NULL,
		S_CUST_LAST_LOGIN);
  genrand_date (&r->dtReview, DIST_UNIFORM, &dt1YearAgo, &dtToday, NULL,
		S_CUST_LAST_REVIEW);
  genrand_ipaddr (r->szPrimaryMachine, S_CUST_PRIMARY_MACHINE);
  genrand_ipaddr (r->szSecondaryMachine, S_CUST_SECONDARY_MACHINE);
  pick_distribution (&r->pLocationType, "location_type", 1, 1,
		     S_CUST_LOCATION_TYPE);
  pick_distribution (&r->nVehicle, "vehicle_count", 1, 1, S_CUST_VEHICLE_CNT);
  genrand_decimal (&r->dIncome, DIST_UNIFORM, &dMinIncome, &dMaxIncome, NULL,
		   S_CUST_INCOME);
  pick_distribution (&r->pBuyPotential, "buy_potential", 1, 1,
		     S_CUST_PURCHASE_ESTIMATE);
  mk_w_customer_address (NULL, kIndex);

  return (0);
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
pr_s_customer (void *pSrc)
{
  struct S_CUSTOMER_TBL *r;
  char szTemp[6];

  if (pSrc == NULL)
    r = &g_s_customer;
  else
    r = pSrc;

  print_start (S_CUSTOMER);
  print_id (S_CUST_ID, r->kID, 1);
  print_varchar (S_CUST_SALUTATION, r->pSalutation, 1);
  print_varchar (S_CUST_LAST_NAME, r->pLastName, 1);
  print_varchar (S_CUST_FIRST_NAME, r->pFirstName, 1);
  print_boolean (S_CUST_PREFERRED_FLAG, r->bPreferredFlag, 1);
  print_date (S_CUST_BIRTH_DATE, r->dtBirthDate.julian, 1);
  print_varchar (S_CUST_BIRTH_COUNTRY, r->pBirthCountry, 1);
  print_varchar (S_CUST_LOGIN, r->szLogin, 1);
  print_varchar (S_CUST_EMAIL, r->szEmail, 1);
  print_date (S_CUST_LAST_LOGIN, r->dtLastLogin.julian, 1);
  print_date (S_CUST_FIRST_SHIPTO_DATE, r->dtFirstShipToDate.julian, 1);
  print_date (S_CUST_FIRST_PURCHASE_DATE, r->dtFirstPurchaseDate.julian, 1);
  print_date (S_CUST_LAST_REVIEW, r->dtReview.julian, 1);
  print_varchar (S_CUST_PRIMARY_MACHINE, r->szPrimaryMachine, 1);
  print_varchar (S_CUST_SECONDARY_MACHINE, r->szSecondaryMachine, 1);
  print_integer (S_CUST_ADDRESS_STREET_NUM,
		 g_w_customer_address.ca_address.street_num, 1);
  print_varchar (S_CUST_ADDRESS_SUITE_NUM,
		 g_w_customer_address.ca_address.suite_num, 1);
  print_varchar (S_CUST_ADDRESS_STREET_NAME1,
		 g_w_customer_address.ca_address.street_name1, 1);
  print_varchar (S_CUST_ADDRESS_STREET_NAME2,
		 g_w_customer_address.ca_address.street_name2, 1);
  print_varchar (S_CUST_ADDRESS_STREET_TYPE,
		 g_w_customer_address.ca_address.street_type, 1);
  print_varchar (S_CUST_ADDRESS_CITY, g_w_customer_address.ca_address.city,
		 1);
  sprintf (szTemp, "%05d", g_w_customer_address.ca_address.zip);
  print_varchar (S_CUST_ADDRESS_ZIP, szTemp, 1);
  print_varchar (S_CUST_ADDRESS_COUNTY,
		 g_w_customer_address.ca_address.county, 1);
  print_varchar (S_CUST_ADDRESS_STATE, g_w_customer_address.ca_address.state,
		 1);
  print_varchar (S_CUST_ADDRESS_COUNTRY,
		 g_w_customer_address.ca_address.country, 1);
  print_varchar (S_CUST_LOCATION_TYPE, r->pLocationType, 1);
  print_varchar (S_CUST_GENDER, r->sGender, 1);
  print_varchar (S_CUST_MARITAL_STATUS, r->pMaritalStatus, 1);
  print_varchar (S_CUST_EDUCATION, r->pEducation, 1);
  print_varchar (S_CUST_CREDIT_RATING, r->pCreditRating, 1);
  print_integer (S_CUST_PURCHASE_ESTIMATE, r->nPurchaseEstimate, 1);
  print_varchar (S_CUST_BUY_POTENTIAL, r->pBuyPotential, 1);
  print_integer (S_CUST_DEPENDENT_CNT, r->nDependents, 1);
  print_integer (S_CUST_EMPLOYED_CNT, r->nEmployed, 1);
  print_integer (S_CUST_COLLEGE_CNT, r->nCollege, 1);
  print_integer (S_CUST_VEHICLE_CNT, r->nVehicle, 1);
  print_decimal (S_CUST_INCOME, &r->dIncome, 0);
  print_end (S_CUSTOMER);

  return (0);
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
ld_s_customer (void *pSrc)
{
  struct S_CUSTOMER_TBL *r;

  if (pSrc == NULL)
    r = &g_s_customer;
  else
    r = pSrc;

  return (0);
}
