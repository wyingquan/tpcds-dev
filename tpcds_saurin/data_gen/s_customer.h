/*
* $Id: s_customer.h,v 1.6 2006/05/08 23:04:59 jms Exp $
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
* $Log: s_customer.h,v $
* Revision 1.6  2006/05/08 23:04:59  jms
* Changes requested by Meikel 5/8/06
*
* Revision 1.5  2006/03/30 16:40:31  jms
* bug reports from Meikel 3/29
*
* Revision 1.4  2006/01/16 23:42:33  jms
* Bug 363: sync souce schema dbgen and WAM model
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
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
*
*/
#ifndef S_CUSTOMER_H
#define S_CUSTOMER_H

#define RS_S_CUST_LOGIN	13
#define RS_S_CUST_EMAIL	50
#define RS_S_CUST_MACHINE	15

struct S_CUSTOMER_TBL {
   ds_key_t	kID;
   char		*pSalutation;
   char		*pLastName;
   char		*pFirstName;
   int			bPreferredFlag;
   date_t		dtBirthDate;
   date_t		dtFirstPurchaseDate;
   date_t		dtFirstShipToDate;
   char		*pBirthCountry;
   char		szLogin[RS_S_CUST_LOGIN + 1];
   char		szEmail[RS_S_CUST_EMAIL + 1];
   date_t		dtLastLogin;
   date_t		dtReview;
   char		szPrimaryMachine[RS_S_CUST_MACHINE + 1];
   char		szSecondaryMachine[RS_S_CUST_MACHINE + 1];
   ds_addr_t	adAddress;
   char		*pLocationType;
   char		sGender[2];
   char		*pMaritalStatus;
   char		*pEducation;
   char		*pCreditRating;
   int	   nPurchaseEstimate;
   char     *pBuyPotential;
   int			nDependents;
   int			nEmployed;
   int			nCollege;
   int			nVehicle;
   decimal_t	dIncome;
};

int mk_s_customer(void *pDest, ds_key_t kIndex);
int pr_s_customer(void *pSrc);
int ld_s_customer(void *pSrc);
#endif
