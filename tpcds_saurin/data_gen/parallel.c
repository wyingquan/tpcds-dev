/*
* $Id: parallel.c,v 1.27 2007/08/02 18:56:30 jms Exp $
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
* $Log: parallel.c,v $
* Revision 1.27  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.26  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.25  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.24  2007/05/24 00:19:04  jms
* bug 546
*
* Revision 1.23  2007/05/23 23:47:38  jms
* TPCDS Bug 546
*
* Revision 1.22  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.21  2006/10/11 23:55:37  jms
* minor changes as part of parallelism exploration
*
* Revision 1.20  2006/10/05 16:11:03  jms
* Parallelism checkins
*
* Revision 1.19  2006/08/31 23:24:09  jms
* Fix for bug 308 and 451 (parallel generation)
*
* Revision 1.18  2006/08/17 21:24:33  jms
* Bug 479
*
* Revision 1.17  2006/07/13 16:37:58  jms
* Bug 472: only create the small files once
*
* Revision 1.16  2006/06/21 00:19:06  jms
* Bug 465
*
* Revision 1.15  2006/06/07 23:01:00  jms
* update fixes for linux
*
* Revision 1.14  2006/06/07 19:55:36  jms
* checkin of revised update scaling
*
* Revision 1.13  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.12  2006/05/12 21:57:29  jms
* porting cleanup
*
* Revision 1.11  2006/05/12 20:31:47  jms
* Correct tdef referencing overrun in chk_seeds
*
* Revision 1.10  2006/04/12 23:32:06  jms
* w_item scaling changes
*
* Revision 1.9  2006/04/11 00:07:35  jms
* Invalid index in check_seeds()
*
* Revision 1.8  2006/03/18 00:23:48  jms
* correct erroneous argument to check_seeds
*
* Revision 1.7  2006/03/17 20:53:15  jms
* Clean up calls to check_seeds()
*
* Revision 1.6  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.5  2006/01/18 18:31:31  jms
* remove a redundant rowcount inflator for SCD tables
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/01/13 19:56:34  jms
* Correct join to SCDs
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.11  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.10.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.10  2004/06/03 21:09:39  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.9  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.8  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.7  2004/05/05 16:32:34  jms
* parallel gen caused small tables to be skipped
*
* Revision 1.6  2004/04/08 06:10:32  jms
* correct exception code to keep small tables from being skipped in split_work
*
* Revision 1.5  2004/04/06 17:34:44  jms
* keep small tables from being built repeatedly when called as part of parallel generation
*
* Revision 1.4  2004/03/27 01:02:54  jms
* row ids are 1-based
*
* Revision 1.3  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.2  2004/03/27 00:17:37  jms
* first cut at parallelism
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "r_params.h"
#include "scaling.h"
#include "tdefs.h"
#include "genrand.h"

/*
* Routine: split_work(int tnum, worker_t *w)
* Purpose: allocate work between processes and threads
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
split_work (int tnum, ds_key_t * pkFirstRow, ds_key_t * pkRowCount)
{
  ds_key_t kTotalRows, kRowsetSize, kExtraRows;
  int nParallel, nChild;

  kTotalRows = get_rowcount(tnum);
  nParallel = get_int ("PARALLEL");
  nChild = get_int ("CHILD");

  /* 
   * 1. small tables aren't paralelized 
   * 2. nothing is parallelized unless a command line arg is supplied 
   */
  *pkFirstRow = 1;
  *pkRowCount = kTotalRows;

  if (kTotalRows < 1000000)
	 {
		if (nChild > 1)			  /* small table; only build it once */
		  {
			 *pkFirstRow = 1;
			 *pkRowCount = 0;
			 return (0);
		  }
		return (1);
	 }

  if (!is_set ("PARALLEL"))
	 {
		return (1);
	 }

  /*
   * at this point, do the calculation to set the rowcount for this part of a parallel build
   */
  kExtraRows = kTotalRows % nParallel;
  kRowsetSize = (kTotalRows - kExtraRows) / nParallel;

  /* start the starting row id */
  *pkFirstRow += (nChild - 1) * kRowsetSize;
  if (kExtraRows && (nChild - 1))
	 *pkFirstRow += ((nChild - 1) < kExtraRows) ? (nChild - 1) : kExtraRows;

  /* set the rowcount for this child */
  *pkRowCount = kRowsetSize;
  if (kExtraRows && (nChild <= kExtraRows))
	 *pkRowCount += 1;

  return (1);
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
checkSeeds (tdef * pTdef)
{
  int i, res, nReturnCode = 0;
  static int bInit = 0, bSetSeeds = 0;

  if (!bInit)
	 {
		bSetSeeds = is_set ("CHKSEEDS");
		bInit = 1;
	 }

  for (i = pTdef->nFirstColumn; i <= pTdef->nLastColumn; i++)
	 {
		while (Streams[i].nUsed < Streams[i].nUsedPerRow)
		  genrand_integer (&res, DIST_UNIFORM, 1, 100, 0, i);
		if (bSetSeeds)
		  {
			 if (Streams[i].nUsed > Streams[i].nUsedPerRow)
				{
				  fprintf (stderr, "Seed overrun on column %d. Used: %d\n",
							  i, Streams[i].nUsed);
				  Streams[i].nUsedPerRow = Streams[i].nUsed;
				  nReturnCode = 1;
				}
		  }
		Streams[i].nUsed = 0;	  /* reset for the next time */
	 }

  return (nReturnCode);
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
row_stop (int tbl)
{
  tdef *pTdef;

  pTdef = getSimpleTdefsByNumber (tbl);
  checkSeeds (pTdef);
   if (pTdef->flags & FL_PARENT)
   {
      pTdef = getSimpleTdefsByNumber (pTdef->nParam);
      checkSeeds (pTdef);
      if (pTdef->flags & FL_PARENT)
      {
         pTdef = getSimpleTdefsByNumber (pTdef->nParam);
         checkSeeds (pTdef);
      }
   }

  return (0);
}

/*
 * Routine: row_skip
 * Purpose: skip over un-used rows in a table
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 20020816 jms The second parameter should really be a ds_key_t to allow BIG skips
 */
int
row_skip (int tbl, ds_key_t count)
{
  int i;

  for (i = 0; Streams[i].nColumn != -1; i++)
	 {
		if (Streams[i].nTable == tbl)
		  {
			 skip_random (i, count * Streams[i].nUsedPerRow);
			 Streams[i].nUsed = 0;
			 Streams[i].nTotal = count * Streams[i].nUsedPerRow;
		  }
		if (Streams[i].nDuplicateOf && (Streams[i].nDuplicateOf != i))
		  {
			 skip_random (Streams[i].nDuplicateOf,
							  count * Streams[Streams[i].nDuplicateOf].nUsedPerRow);
			 Streams[Streams[i].nDuplicateOf].nUsed = 0;
			 Streams[Streams[i].nDuplicateOf].nTotal = 
            count * Streams[i].nUsedPerRow;
		  }
	 }

  return (0);
}
