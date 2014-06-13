/*
* $Id: validate.h,v 1.1 2007/07/27 20:15:13 jms Exp $
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
* ==============
* $Log: validate.h,v $
* Revision 1.1  2007/07/27 20:15:13  jms
* isolate validation code
*
*/
#ifndef VALIDATE_H
#define VALIDATE_H
#include "config.h"
#include "porting.h"

int validateGeneric(int nTable, ds_key_t kRow, int *Permute);
void printValidation(int nTable, ds_key_t kRow);
int validateSCD(int nTable, ds_key_t kRow, int *Permutation);
#endif

