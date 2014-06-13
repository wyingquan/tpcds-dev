/*
* $Id: s_customer_address.h,v 1.2 2007/07/10 18:49:29 jms Exp $
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
* $Log: s_customer_address.h,v $
* Revision 1.2  2007/07/10 18:49:29  jms
* validate s_customer_address
*
* Revision 1.1  2006/03/17 20:24:19  jms
* rename of s_business_address to align with spec
*
*/
#ifndef S_BUSINESS_ADDRESS_H
#define S_BUSINESS_ADDRESS_H


int pr_s_customer_address(void *pSrc);
int ld_s_customer_address(void *pSrc);
int vld_s_customer_address(int nTable, ds_key_t kRow, int *Permutation);
#endif
