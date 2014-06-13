/*
* $Id: sparse.c,v 1.4 2006/01/07 00:44:02 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 1997 - 2005
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ==============
* $Log: sparse.c,v $
* Revision 1.4  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.3  2006/01/02 20:11:33  jms
* Bug 357: segfault when building updates
*
* Revision 1.2  2005/02/15 23:45:38  jms
* Bug #143: consistent handling of manager names
*
* Revision 1.1  2005/01/13 19:48:35  jms
* Add sparse.[ch] to handle sparse keys in demographic tables
*
*/
#include "config.h"
#include "porting.h"
#include "scaling.h"
#include "genrand.h"
#include "sparse.h"
#include "tdefs.h"
#include "error_msg.h"

/*
* Routine: initSparseKeys()
* Purpose: set up the set of valid key values for a sparse table.
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions: The total population will fit in 32b
* Side Effects:
* TODO: None
*/
int
initSparseKeys(int nTable)
{
	ds_key_t kRowcount,
		kOldSeed;
	int k;
	tdef *pTdef;

	kRowcount = get_rowcount(nTable);
	pTdef = getTdefsByNumber(nTable);
	
	pTdef->arSparseKeys = (ds_key_t *)malloc((long)kRowcount * sizeof(ds_key_t));
	MALLOC_CHECK(pTdef->arSparseKeys);
	if (pTdef->arSparseKeys == NULL)
		ReportError(QERR_NO_MEMORY, "initSparseKeys()", 1);
	memset(pTdef->arSparseKeys, 0, (long)kRowcount * sizeof(ds_key_t));

	kOldSeed = setSeed(0, nTable);
	for (k = 0; k < kRowcount; k++)
		 genrand_key(&pTdef->arSparseKeys[k], DIST_UNIFORM, 1, pTdef->nParam, 0, 0);
	setSeed(0, (int)kOldSeed);

	return(0);
}

/*
* Routine: randomSparseKey()
* Purpose: randomly select one of the valid key values for a sparse table
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
ds_key_t
randomSparseKey(int nTable, int nColumn)
{
	int nKeyIndex;
	ds_key_t kRowcount;
	tdef *pTdef;

	pTdef = getTdefsByNumber(nTable);
	kRowcount = get_rowcount(nTable);
	genrand_integer(&nKeyIndex, DIST_UNIFORM, 1, (long)kRowcount, 0, nColumn);

	return(pTdef->arSparseKeys[nKeyIndex]);
}



