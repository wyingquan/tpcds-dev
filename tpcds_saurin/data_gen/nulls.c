/*
* $Id: nulls.c,v 1.5 2007/08/02 18:56:30 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2004
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: nulls.c,v $
* Revision 1.5  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.4  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.3  2006/08/17 20:44:50  jms
* Bug 481
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.4  2004/09/08 21:15:25  jms
* use getTableFromColumn()
*
* Revision 1.3  2004/06/04 00:29:41  jms
* final 1.1.13b corrections
*
* Revision 1.2  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.1  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
*
*/
#include "config.h"
#include "porting.h"
#include "nulls.h"
#include "genrand.h"
#include "tdefs.h"
#include "limits.h"

#define MAXINT INT_MAX

/*
* Routine: nullCheck(int nColumn)
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
nullCheck(int nColumn)
{
	static int nLastTable = 0;
	tdef *pTdef;
	ds_key_t kBitMask = 1;

	nLastTable = getTableFromColumn(nColumn);
	pTdef = getSimpleTdefsByNumber(nLastTable);

	kBitMask <<= nColumn - pTdef->nFirstColumn;

	return((pTdef->kNullBitMap & kBitMask) != 0);
}

/*
* Routine: nullSet(int *pDest, int nStream)
* Purpose: set the kNullBitMap for a particular table
* Algorithm:
*	1. if random[1,100] >= table's NULL pct, clear map and return
*	2. set map

* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects: uses 2 RNG calls
* TODO: None
*/
void
nullSet(ds_key_t *pDest, int nStream)
{
	int nThreshold;
   ds_key_t kBitMap;
	static int nLastTable = 0;
   tdef *pTdef;

	nLastTable = getTableFromColumn(nStream);
   pTdef = getSimpleTdefsByNumber(nLastTable);

	/* burn the RNG calls */
	genrand_integer(&nThreshold, DIST_UNIFORM, 0, 9999, 0, nStream);
	genrand_key(&kBitMap, DIST_UNIFORM, 1, MAXINT, 0, nStream);

	/* set the bitmap based on threshold and NOT NULL definitions */
	*pDest = 0;
	pTdef->nNullPct = 0.0;
    if (nThreshold < pTdef->nNullPct)
	{
		*pDest = kBitMap;
		*pDest &= ~pTdef->kNotNullBitMap;
	}

	return;
}
