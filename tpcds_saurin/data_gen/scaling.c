/*
* $Id: scaling.c,v 1.51 2007/10/17 21:51:05 jms Exp $
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
* $Log: scaling.c,v $
* Revision 1.51  2007/10/17 21:51:05  jms
* correcting 32/64 bug found by Meikel
*
* Revision 1.50  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.49  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.48  2007/07/25 19:41:47  jms
* bug 546: remove duplicate printing
*
* Revision 1.47  2007/07/24 19:50:58  jms
* bug 546: s_customer_address
*
* Revision 1.46  2007/07/10 18:49:55  jms
* validate s_customer_address
*
* Revision 1.45  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.44  2007/05/23 23:47:38  jms
* TPCDS Bug 546
*
* Revision 1.43  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.42  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.41  2007/04/26 22:28:49  jms
* TPCDS bug 540
*
* Revision 1.40  2007/02/08 18:22:22  jms
* Bug 515
*
* Revision 1.39  2007/01/09 00:25:39  jms
* Bugs 521-523 (delete file format, update file naming)
*
* Revision 1.38  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.37  2006/10/05 20:11:59  jms
* IBM access() issue
*
* Revision 1.36  2006/10/03 18:32:07  jms
* correct inventory date generation
*
* Revision 1.35  2006/08/29 20:24:03  jms
* remove unused variables
*
* Revision 1.34  2006/08/24 16:45:19  jms
* Bug 486: remove error message if /quiet is set
*
* Revision 1.33  2006/08/23 23:51:02  jms
* Bug 485: inventory on Thursdays
*
* Revision 1.32  2006/08/23 23:09:37  jms
* Bug 485: inventory on Thursdays
*
* Revision 1.31  2006/08/23 22:15:32  jms
* remove unused variable.
*
* Revision 1.30  2006/08/23 22:13:47  jms
* porting issues
*
* Revision 1.29  2006/08/22 21:48:24  jms
* Bug 485
*
* Revision 1.28  2006/08/18 23:18:06  jms
* Bug #475
*
* Revision 1.27  2006/08/17 21:51:08  jms
* Bug 479
*
* Revision 1.26  2006/06/21 00:18:34  jms
* Bug 468
*
* Revision 1.25  2006/06/07 19:55:36  jms
* checkin of revised update scaling
*
* Revision 1.24  2006/06/06 21:41:15  jms
* initial checkin of revised update scaling
*
* Revision 1.23  2006/05/12 21:01:59  jms
* porting cleanup
*
* Revision 1.22  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.21  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.20  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.19  2006/03/24 20:25:09  jms
* Problems identified by Meikel 3/21/06
*
* Revision 1.18  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.17  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.16  2006/02/13 22:06:42  jms
* correct termination condition in get_rowcount
*
* Revision 1.15  2006/02/10 17:14:58  jms
* sf aware QGEN: exapnd ROWCOUNT syntax
*
* Revision 1.14  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.13  2006/02/02 05:01:27  jms
* scale factor aware qgen
*
* Revision 1.12  2006/01/28 23:00:03  jms
* update souce schema scaling based on data from Meikel
*
* Revision 1.11  2006/01/16 23:12:38  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.10  2006/01/02 23:01:29  jms
* Bug #360: sk often default to 1 in update set
*
* Revision 1.9  2005/11/08 23:38:24  jms
* correct scaling overrun
*
* Revision 1.8  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.7  2005/07/20 22:48:25  jms
* add data validation
* relocate dateScaling
*
* Revision 1.6  2005/04/21 18:38:05  jms
* Bug #168: Remove +/- 5% variability
*
* Revision 1.5  2005/04/20 17:01:46  jms
* Bug #168: Generate fact tables in date order
*
* Revision 1.4  2005/03/16 19:48:44  jms
* SCDs double row count
*
* Revision 1.3  2005/01/27 22:08:09  jms
* Correct rowcount calculations for SCDs
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.11  2004/10/19 23:24:15  jms
* correct source schema table scaling
*
* Revision 1.10  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.9  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.8  2004/06/03 21:09:39  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.7  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.6  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.5  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.4  2004/03/26 19:45:04  jms
* rename tdef_funtions.c to tdef_functions.c
*
* Revision 1.3  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.2  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.5  2003/07/21 20:50:56  jms
* change get_rowcount to return long for now
*
* Revision 1.4  2003/07/18 19:59:09  jms
* update for 1.1.9
*
* Revision 1.3  2003/07/15 18:02:34  jms
* only scale actual tables
*
* Revision 1.2  2003/07/14 23:14:54  jms
* enable continuous scaling in integer GB
*
* Revision 1.1  2003/06/24 19:36:35  jms
* Add files to isolate scaling functions and permutation (used for LIST in qgen)
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include "config.h"
#include "porting.h"
#include "dist.h"
#include "constants.h"
#include "genrand.h"
#include "columns.h"
#include "tdefs.h"
#include "error_msg.h"
#include "r_params.h"
#include "tdefs.h"
#include "tdef_functions.h"
#include "w_inventory.h"
#include "scaling.h"
#include "tpcds.idx.h"
#include "print.h"
#include "parallel.h"
#include "scd.h"


static struct SCALING_T {
   ds_key_t kBaseRowcount;
   ds_key_t kNextInsertValue;
   int	nUpdatePercentage;
   ds_key_t kDayRowcount[6];
} arRowcount[MAX_TABLE + 1];
static int arUpdateDates[6];
static int arInventoryUpdateDates[6];

static int arScaleVolume[9] =
   {1, 10, 100, 300, 1000, 3000, 10000, 30000, 100000};

void setUpdateScaling(int table);
int	row_skip(int tbl, ds_key_t count);

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
getScaleSlot(int nTargetGB)
{
   int i;

   for (i=0; nTargetGB > arScaleVolume[i]; i++);

   return(i);
}

/*
* Routine: LogScale(void)
* Purpose: use the command line volume target, in GB, to calculate the global rowcount multiplier
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions: 
* Side Effects: arRowcounts are set to the appropriate number of rows for the target scale factor
* TODO: None
*/
static ds_key_t
LogScale(int nTable, int nTargetGB)
{
	int nIndex = 1,
		nDelta,
      i;
	float fOffset;
	ds_key_t hgRowcount = 0;

	i = getScaleSlot(nTargetGB);

	nDelta = dist_weight(NULL, "rowcounts", nTable + 1, i + 1) - dist_weight(NULL, "rowcounts", nTable + 1, i);
	fOffset = (float)(nTargetGB - arScaleVolume[i - 1])/(float)(arScaleVolume[i] -  arScaleVolume[i - 1]);

	hgRowcount = (int)(fOffset * (float)nDelta);
	hgRowcount += dist_weight(NULL, "rowcounts", nTable + 1, nIndex);


	return(hgRowcount);
}

/*
* Routine: StaticScale(void)
* Purpose: use the command line volume target, in GB, to calculate the global rowcount multiplier
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions: 
* Side Effects: arRowcounts are set to the appropriate number of rows for the target scale factor
* TODO: None
*/
static ds_key_t
StaticScale(int nTable, int nTargetGB)
{
	return(dist_weight(NULL, "rowcounts", nTable + 1, 1));
}

/*
* Routine: LinearScale(void)
* Purpose: use the command line volume target, in GB, to calculate the global rowcount multiplier
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions: scale factors defined in rowcounts distribution define 1/10/100/1000/... GB 
*	with sufficient accuracy
* Side Effects: arRowcounts are set to the appropriate number of rows for the target scale factor
* TODO: None
*/
static ds_key_t
LinearScale(int nTable, int nTargetGB)
{
	int i;
	ds_key_t hgRowcount = 0;
	
	for (i=8; i >= 0; i--)	/* work from large scales down)*/
	{
		/*
		 * use the defined rowcounts to build up the target GB volume 
		 */
		while (nTargetGB >= arScaleVolume[i])
		{
			hgRowcount += dist_weight(NULL, "rowcounts", nTable + 1, i + 1);
			nTargetGB -= arScaleVolume[i];
		}
	}

	return(hgRowcount);
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
ds_key_t
getIDCount(int nTable)
{
   ds_key_t kRowcount,
      kUniqueCount;
   tdef *pTdef;
   
   kRowcount = get_rowcount(nTable);
   if (nTable >= PSEUDO_TABLE_START)
      return(kRowcount);
   pTdef = getSimpleTdefsByNumber(nTable);
   if (pTdef->flags & FL_TYPE_2)
   {
      kUniqueCount = (kRowcount / 6) * 3;
      switch (kRowcount % 6)
      {
      case 1:
         kUniqueCount += 1;
         break;
     case 2:
     case 3:
         kUniqueCount += 2;
         break;
     case 4:
     case 5:
         kUniqueCount += 3;
         break;
      }
      return(kUniqueCount);
   }
   else
   {
      return(kRowcount);
   }
}

/*
* Routine: get_rowcount(int table)
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
* TODO: 20040820 jms Need to address special case scaling in a more general fashion
*/
ds_key_t
get_rowcount(int table)
{

	static int bScaleSet = 0,
      nScale;
	int nTable,
		nMultiplier,
		i,
		nBadScale = 0,
		nRowcountOffset = 0;
	tdef *pTdef;
	
	if (!bScaleSet)
	{		
		nScale = get_int("SCALE");
		if (nScale > 100000)
			ReportErrorNoLine(QERR_BAD_SCALE, NULL, 1);

		memset(arRowcount, 0, sizeof(long) * MAX_TABLE);
		for (nTable=CALL_CENTER; nTable <= MAX_TABLE; nTable++)
		{
			switch(nScale)
			{
			case 100000:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset + 1, 9);
				break;
			case 30000:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 8);
				break;
			case 10000:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 7);
				break;
			case 3000:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 6);
				break;
			case 1000:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 5);
				break;
			case 300:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 4);
				break;
			case 100:
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 3);
				break;
			case 10:
				nBadScale = QERR_BAD_SCALE;
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 2);
				break;
			case 1:
				nBadScale = QERR_QUALIFICATION_SCALE;
				arRowcount[nTable].kBaseRowcount = dist_weight(NULL, "rowcounts", nTable + nRowcountOffset  + 1, 1);
				break;
			default:
				nBadScale = QERR_BAD_SCALE;
				switch(dist_member(NULL, "rowcounts", nTable + 1, 3))
				{
				case 2:
					arRowcount[nTable].kBaseRowcount = LinearScale(nTable + nRowcountOffset , nScale);
					break;
				case 1:
					arRowcount[nTable].kBaseRowcount = StaticScale(nTable + nRowcountOffset , nScale);
					break;
				case 3:
					arRowcount[nTable].kBaseRowcount = LogScale(nTable + nRowcountOffset , nScale);
					break;
				}	/* switch(FL_SCALE_MASK) */
				break;
			} /* switch(nScale) */

			/* now adjust for the multiplier */
         nMultiplier = 1;
			if (nTable < PSEUDO_TABLE_START)
         {
            pTdef = getSimpleTdefsByNumber(nTable);
			   nMultiplier = (pTdef->flags & FL_TYPE_2)?2:1;
         }
			for (i=1; i <= dist_member(NULL, "rowcounts", nTable + 1, 2); i++)
				nMultiplier *= 10;
			arRowcount[nTable].kBaseRowcount *= nMultiplier;

      } /* for each table */

		
		if (nBadScale && !is_set("QUIET"))
			ReportErrorNoLine(nBadScale, NULL, 0);

		bScaleSet = 1;
	}
	
	if ((table == INVENTORY))
		return(sc_w_inventory(nScale));
	if ((table == S_INVENTORY))
		return(getIDCount(ITEM) * get_rowcount(WAREHOUSE) * 6);

	return(arRowcount[table].kBaseRowcount);

}

/*
* Routine: setUpdateDates
* Purpose: determine the dates for fact table updates
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
void
setUpdateDates(void)
{
   int nDay,
      nUpdate,
      i;
   date_t dtTemp;

   nUpdate = get_int("UPDATE");
   while (nUpdate--)
   {
      /* pick two adjacent days in the low density zone */
      arUpdateDates[0] = getSkewedJulianDate(calendar_low, 0);
      jtodt(&dtTemp, arUpdateDates[0]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp) + 1, calendar_low);
      if (nDay)
         arUpdateDates[1] = arUpdateDates[0] + 1;
      else
         arUpdateDates[1] = arUpdateDates[0] - 1;

      /* 
       * pick the related Thursdays for inventory 
       * 1. shift first date to the Thursday in the current update week
       * 2. move forward/back to get into correct comparability zone
       * 3. set next date to next/prior Thursday based on comparability zone
       */
      jtodt(&dtTemp, arUpdateDates[0] + (4 - set_dow(&dtTemp)));
      dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_low);
      arInventoryUpdateDates[0] = dtTemp.julian;
      if (!nDay)
      {
        jtodt(&dtTemp, dtTemp.julian - 7);
        arInventoryUpdateDates[0] = dtTemp.julian;
        dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_low);
         if (!nDay)
            arInventoryUpdateDates[0] += 14;
      }

      arInventoryUpdateDates[1] = arInventoryUpdateDates[0] + 7;
      jtodt(&dtTemp, arInventoryUpdateDates[1]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp) + 1, calendar_low);
      if (!nDay)
            arInventoryUpdateDates[1] -= 14;
     
      /* repeat for medium calendar zone */
      arUpdateDates[2] = getSkewedJulianDate(calendar_medium, 0);
      jtodt(&dtTemp, arUpdateDates[2]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp) + 1, calendar_medium);
      if (nDay)
         arUpdateDates[3] = arUpdateDates[2] + 1;
      else
         arUpdateDates[3] = arUpdateDates[2] - 1;

      jtodt(&dtTemp, arUpdateDates[2] + (4 - set_dow(&dtTemp)));
      dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_medium);
      arInventoryUpdateDates[2] = dtTemp.julian;
      if (!nDay)
      {
        jtodt(&dtTemp, dtTemp.julian - 7);
        arInventoryUpdateDates[2] = dtTemp.julian;
        dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_medium);
         if (!nDay)
            arInventoryUpdateDates[2] += 14;
      }

      arInventoryUpdateDates[3] = arInventoryUpdateDates[2] + 7;
      jtodt(&dtTemp, arInventoryUpdateDates[3]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_medium);
      if (!nDay)
            arInventoryUpdateDates[3] -= 14;

      
      /* repeat for high calendar zone */
      arUpdateDates[4] = getSkewedJulianDate(calendar_high, 0);
      jtodt(&dtTemp, arUpdateDates[4]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp) + 1, calendar_high);
      if (nDay)
         arUpdateDates[5] = arUpdateDates[4] + 1;
      else
         arUpdateDates[5] = arUpdateDates[4] - 1;

      jtodt(&dtTemp, arUpdateDates[4] + (4 - set_dow(&dtTemp)));
      dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_high);
      arInventoryUpdateDates[4] = dtTemp.julian;
      if (!nDay)
      {
        jtodt(&dtTemp, dtTemp.julian - 7);
        arInventoryUpdateDates[4] = dtTemp.julian;
        dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_high);
         if (!nDay)
            arInventoryUpdateDates[4] += 14;
      }

      arInventoryUpdateDates[5] = arInventoryUpdateDates[4] + 7;
      jtodt(&dtTemp, arInventoryUpdateDates[5]);
      dist_weight(&nDay, "calendar", day_number(&dtTemp), calendar_high);
      if (!nDay)
            arInventoryUpdateDates[5] -= 14;


   }
   
   /*
   * output the update dates for this update set 
   */
   openDeleteFile(1);
   for (i=0; i < 6; i += 2)
      print_delete(&arUpdateDates[i]);

   /*
    * inventory uses separate dates
    */
   openDeleteFile(2);
   for (i=0; i < 6; i += 2)
      print_delete(&arInventoryUpdateDates[i]);
   openDeleteFile(0);

   return;
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
getUpdateDate(int nTable, ds_key_t kRowcount)
{
   static int nIndex = 0,
      nLastTable = -1;

   if (nLastTable != nTable)
   {
      nLastTable = nTable;
      get_rowcount(nTable);
      nIndex = 0;
   }
   
   for (nIndex = 0; kRowcount > arRowcount[nTable].kDayRowcount[nIndex]; nIndex++)
      if (nIndex == 5) break;

   if (nTable == S_INVENTORY)
   {
      return(arInventoryUpdateDates[nIndex]);
   }
   else
    return(arUpdateDates[nIndex]);
}



/*
* Routine: getUpdateID(int nTable, ds_key_t *pDest)
* Purpose: select the primary key for an update set row
* Algorithm:
* Data Structures:
*
* Params:
* Returns: 1 if the row is new, 0 if it is reusing an existing ID
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20040326 jms getUpdateID() this MUST be updated for 64bit -- all usages use casts today
* TODO:	20060102 jms this will need to be looked at for parallelism at some point
*/
/*
int
getUpdateID(ds_key_t *pDest, int nTable, int nColumn)
{
	int bIsUpdate = 0,
		nTemp;
	
	if (genrand_integer(NULL, DIST_UNIFORM, 0, 99, 0, nColumn) < arRowcount[nTable].nUpdatePercentage)
	{
		bIsUpdate = 1;
		genrand_integer(&nTemp, DIST_UNIFORM, 1, (int)getIDCount(nTable), 0, nColumn);
		*pDest = (ds_key_t)nTemp;
	}
	else
	{
		*pDest = ++arRowcount[nTable].kNextInsertValue;
	}

	return(bIsUpdate);
}
*/


/*
* Routine: getSkewedJulianDate()
* Purpose: return a julian date based on the given skew and column
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
getSkewedJulianDate(int nWeight, int nColumn)
{
   int i;
   date_t Date;
   
   pick_distribution(&i, "calendar", 1, nWeight, nColumn);
   genrand_integer(&Date.year, DIST_UNIFORM, YEAR_MINIMUM, YEAR_MAXIMUM, 0, nColumn);
   dist_member(&Date.day, "calendar", i, 3);
   dist_member(&Date.month, "calendar", i, 5);
   return(dttoj(&Date));
}

/*
* Routine: initializeOrderUpdate()
* Purpose: skip over prior updates for the named table
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
/*
int
initializeOrderUpdates(int nParent, int nChild, int nIDColumn, int nDateColumn, int *pnOrderNumber)
{
   int i,
      nRowcount,
      nRowsRemaining,
      nStep = 0;
   date_t Date;


		*pnOrderNumber = 0;
      
      for (i=0; i < (get_int("UPDATE") - 1); i++)
		{
			nRowsRemaining = (int)get_rowcount(nParent);
         while (nRowsRemaining > 0)
         {
            nStep = nStep % 3;
            nStep += 1;
            Date.julian = getSkewedJulianDate((nStep++ % 3) + 8, nDateColumn);
            nRowcount = (int)dateScaling(getTableFromColumn(nIDColumn), Date.julian);
            *pnOrderNumber += nRowcount;
            row_skip(nParent, nRowcount);
            row_skip(nChild, LINES_PER_ORDER * nRowcount);
            nRowsRemaining -= nRowcount;
         }
		}

      return(nStep);
}
*/

/*
* Routine: dateScaling(int nTable, ds_key_t jDate)
* Purpose: determine the number of rows to build for a given date and fact table
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
dateScaling(int nTable, ds_key_t jDate)
{
	static int bInit = 0;
	static dist_t *pDist;
	d_idx_t *pDistIndex;
	date_t Date;
	int nDateWeight = 1,
		nCalendarTotal,
		nDayWeight;
	ds_key_t kRowCount = -1;
   tdef *pTdef = getSimpleTdefsByNumber(nTable);

	if (!bInit)
	{
		pDistIndex = find_dist("calendar");
		pDist = pDistIndex->dist;
		if (!pDist)
			ReportError(QERR_NO_MEMORY, "dateScaling()", 1);
		bInit = 1;
	}

	jtodt(&Date, (int)jDate);
	
	switch(nTable)
	{
	case STORE_SALES:
	case CATALOG_SALES:
	case WEB_SALES:
      kRowCount = get_rowcount(nTable);
		nDateWeight = calendar_sales;
		break;
	case S_CATALOG_ORDER:
      kRowCount = get_rowcount(CATALOG_SALES);
		nDateWeight = calendar_sales;
		break;
	case S_PURCHASE:
      kRowCount = get_rowcount(STORE_SALES);
		nDateWeight = calendar_sales;
		break;
	case S_WEB_ORDER:
      kRowCount = get_rowcount(WEB_SALES);
		nDateWeight = calendar_sales;
		break;
	case S_INVENTORY:
   case INVENTORY:
		nDateWeight = calendar_uniform;
      kRowCount = get_rowcount(WAREHOUSE) * getIDCount(ITEM);
		break;
	default:
		ReportErrorNoLine(QERR_TABLE_NOP, pTdef->name, 1);
		break;
	}

	if (nTable != INVENTORY) /* inventory rowcount is uniform thorughout the year */
   {
      if (is_leap(Date.year))
		nDateWeight += 1;

	nCalendarTotal = dist_max(pDist, nDateWeight);
	nCalendarTotal *= 5;	/* assumes date range is 5 years */

	dist_weight(&nDayWeight, "calendar", day_number(&Date), nDateWeight);
	kRowCount *= nDayWeight;
   kRowCount += nCalendarTotal / 2;
	kRowCount /= nCalendarTotal;
   }

	return(kRowCount);
}

/*
* Routine: getUpdateBase(int nTable)
* Purpose: return the offset to the first order in this update set for a given table
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
getUpdateBase(int nTable)
{
   return(arRowcount[nTable - S_BRAND].kNextInsertValue);
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
void
setUpdateScaling(int nTable)
{
   tdef *pTdef;
   int i,
      nBaseTable;
   ds_key_t kNewRowcount = 0;

   pTdef = getSimpleTdefsByNumber(nTable);
   if (!(pTdef->flags & FL_SOURCE_DDL) ||
      !(pTdef->flags & FL_DATE_BASED) ||
      (pTdef->flags & FL_NOP))
      return;

   switch(nTable)
   {
   case S_PURCHASE: nBaseTable = STORE_SALES; break;
   case S_CATALOG_ORDER: nBaseTable = CATALOG_SALES; break;
   case S_WEB_ORDER: nBaseTable = WEB_SALES; break;
   case S_INVENTORY: nBaseTable = INVENTORY; break;
   default:
      fprintf(stderr, "ERROR: Invalid table in setUpdateScaling\n");
      exit(1);
      break;
   }
   
   arRowcount[nTable].kNextInsertValue = arRowcount[nTable].kBaseRowcount;

   for (i=0; i < 6; i++)
   {
      kNewRowcount += dateScaling(nBaseTable, arUpdateDates[i]);
      arRowcount[nTable].kDayRowcount[i] = kNewRowcount;
   }

   arRowcount[nTable].kBaseRowcount = kNewRowcount;
   arRowcount[nTable].kNextInsertValue += kNewRowcount * (get_int("update") - 1);

   return;
}
