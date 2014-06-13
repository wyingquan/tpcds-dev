/*
* $Id: porting.c,v 1.1 2006/05/04 23:11:08 jms Exp $
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
* $Log: porting.c,v $
* Revision 1.1  2006/05/04 23:11:08  jms
* Correct strdup in porting.c and make declaration conditional
*
*/
/*********************
 ** Define some routines that, while common, are not ANSI standard 
 *********************/
#include "config.h"
#include "porting.h"
#include <stdlib.h>

#ifndef strdup
char *strdup(const char *szSrc)
{
   char *szResult;

   szResult = (char *)malloc(strlen(szSrc) + 1);
   if (szResult)
   {
      strcpy(szResult, szSrc);
   }

   return(szResult);
}
#endif

