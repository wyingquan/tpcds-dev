/*
* $Id: permute.c,v 1.5 2007/05/23 18:11:58 jms Exp $
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
* $Log: permute.c,v $
* Revision 1.5  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.4  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.3  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.5  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.4  2004/08/26 00:07:42  jms
* *** empty log message ***
*
* Revision 1.2  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1  2003/06/24 19:36:35  jms
* Add files to isolate scaling functions and permutation (used for LIST in qgen)
*
*
*/
#include "config.h"
#include "porting.h"
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include <stdio.h>
#include "genrand.h"

/*
* Routine: MakePermutation(int nSize)
* Purpose: Permute the integers in [1..nSize]
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
int *
makePermutation(int *nNumberSet, int nSize, int nStream)
{
	int i,
		nTemp,
		nIndex,
		*pInt;

	if (nSize <= 0)
		return(NULL);

	if (!nNumberSet)
	{
		nNumberSet = (int *)malloc(nSize * sizeof(int));
		MALLOC_CHECK(nNumberSet);
		pInt = nNumberSet;
		for (i=0; i < nSize; i++)
			*pInt++ = i;
	}

	for (i=0; i < nSize; i++)
	{
		nIndex = genrand_integer(NULL, DIST_UNIFORM, 0, nSize - 1, 0, nStream);
		nTemp = nNumberSet[i];
		nNumberSet[i] = nNumberSet[nIndex];
		nNumberSet[nIndex] = nTemp;
	}

	return(nNumberSet);
}

