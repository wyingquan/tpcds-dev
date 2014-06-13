/*
* $Id: scd.c,v 1.27 2007/10/02 16:31:31 jms Exp $
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
* $Log: scd.c,v $
* Revision 1.27  2007/10/02 16:31:31  jms
* correct changeSCD bug
*
* Revision 1.26  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.25  2007/07/25 18:19:28  jms
* bug 546
*
* Revision 1.24  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.23  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.22  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.21  2006/08/23 22:27:12  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.20  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.19  2006/07/18 23:03:26  jms
* Bug 473
*
* Revision 1.18  2006/06/21 19:14:05  jms
* Bug  461
*
* Revision 1.17  2006/05/12 21:03:02  jms
* porting cleanup
*
* Revision 1.16  2006/05/12 21:01:59  jms
* porting cleanup
*
* Revision 1.15  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.14  2006/03/28 21:19:18  jms
* bougs data in w_web_returns
*
* Revision 1.13  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.12  2006/02/02 05:55:45  jms
* fix SCD FK errors resulting from over-corrected key->sk mapping
*
* Revision 1.11  2006/01/02 19:17:56  jms
* Bug 357: segfault when building updates
*
* Revision 1.10  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.9  2005/12/08 23:57:14  jms
* Bug 354: duplicate values for primary key on inventory
*
* Revision 1.8  2005/11/14 02:06:33  jms
* correct SCD join
*
* Revision 1.7  2005/10/05 22:38:54  jms
* bug #236: acid query fails; appears to be a int/key problem?
*
* Revision 1.6  2005/08/03 22:36:45  jms
* correct join cardinality error in SCD
*
* Revision 1.5  2005/02/15 23:50:20  jms
* Bug #144: end date of last revision of SCD should be NULL
*
* Revision 1.4  2005/01/13 19:54:09  jms
* Correct join to SCDs
*
* Revision 1.3  2004/12/02 17:44:51  jms
* Bug #114: scd joins should be NULL for future dates
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.6  2004/09/08 21:15:25  jms
* use getTableFromColumn()
*
* Revision 1.5  2004/08/13 23:37:17  jms
* HP/UX porting changes
*
* Revision 1.4  2004/08/13 23:36:19  jms
* porting changes for HP/UX
*
* Revision 1.3  2004/08/13 21:17:15  jms
* correct data type of switch() for HP/UX
*
* Revision 1.2  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.1.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.1.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "tdefs.h"
#include "scd.h"
#include "tables.h"
#include "build_support.h"
#include "dist.h"
#include "scaling.h"
#include "genrand.h"
#include "constants.h"
#include "parallel.h"
#include "params.h"
#include "tdef_functions.h"
#include "print.h"
#include "permute.h"

/* an array of the most recent business key for each table */
char arBKeys[MAX_TABLE][17];

/*
* Routine: setSCDKey
* Purpose: handle the versioning and date stamps for slowly changing dimensions
* Algorithm:
* Data Structures:
*
* Params: 1 if there is a new id; 0 otherwise
* Returns:
* Called By: 
* Calls: 
* Assumptions: Table indexs (surrogate keys) are 1-based. This assures that the arBKeys[] entry for each table is 
*	initialized. Otherwise, parallel generation would be more difficult.
* Side Effects:
* TODO: None
*/
int
setSCDKeys(int nColumnID, ds_key_t kIndex, char *szBKey, ds_key_t *pkBeginDateKey, ds_key_t *pkEndDateKey)
{
	int bNewBKey = 0,
		nModulo;
	static int bInit = 0;
	static ds_key_t jMinimumDataDate,
		jMaximumDataDate,
		jH1DataDate,
		jT1DataDate,
		jT2DataDate;
	date_t dtTemp;
	int nTableID;

	if (!bInit)
	{
		strtodt(&dtTemp, DATA_START_DATE);
		jMinimumDataDate = dtTemp.julian;
		strtodt(&dtTemp, DATA_END_DATE);
		jMaximumDataDate = dtTemp.julian;
		jH1DataDate = jMinimumDataDate + (jMaximumDataDate - jMinimumDataDate) / 2;
		jT2DataDate = (jMaximumDataDate - jMinimumDataDate) / 3;
		jT1DataDate = jMinimumDataDate + jT2DataDate;
		jT2DataDate += jT1DataDate; 
		bInit = 1;
	}
	
	nTableID = getTableFromColumn(nColumnID);
	nModulo = (int)(kIndex % 6);
	switch(nModulo)
	{
	case 1: /* 1 revision */
		mk_bkey(arBKeys[nTableID], kIndex, nColumnID);
		bNewBKey = 1;
		*pkBeginDateKey = jMinimumDataDate - nTableID * 6;
		*pkEndDateKey = -1;
		break;
	case 2:	/* 1 of 2 revisions */
		mk_bkey(arBKeys[nTableID], kIndex, nColumnID);
		bNewBKey = 1;
		*pkBeginDateKey = jMinimumDataDate - nTableID * 6;
		*pkEndDateKey = jH1DataDate - nTableID * 6;
		break;
	case 3:	/* 2 of 2 revisions */
		mk_bkey(arBKeys[nTableID], kIndex - 1, nColumnID);
		*pkBeginDateKey = jH1DataDate - nTableID * 6 + 1;
		*pkEndDateKey = -1;
		break;
	case 4:	/* 1 of 3 revisions */
		mk_bkey(arBKeys[nTableID], kIndex, nColumnID);
		bNewBKey = 1;
		*pkBeginDateKey = jMinimumDataDate - nTableID * 6;
		*pkEndDateKey = jT1DataDate - nTableID * 6;
		break;
	case 5:	/* 2 of 3 revisions */
		mk_bkey(arBKeys[nTableID], kIndex - 1, nColumnID);
		*pkBeginDateKey = jT1DataDate - nTableID * 6 + 1;
		*pkEndDateKey = jT2DataDate - nTableID * 6;
		break;
	case 0:	/* 3 of 3 revisions */
		mk_bkey(arBKeys[nTableID], kIndex - 2, nColumnID);
		*pkBeginDateKey = jT2DataDate - nTableID * 6 + 1;
		*pkEndDateKey = -1;
		break;
	}

	/* can't have a revision in the future, per bug 114 */
	if (*pkEndDateKey > jMaximumDataDate)
		*pkEndDateKey = -1;
    
    /* Avoiding nulls! */
    if ( *pkEndDateKey == -1 )
        *pkEndDateKey = jT1DataDate - nTableID * 6;
        
	
	strcpy(szBKey, arBKeys[nTableID]);
	
	return(bNewBKey);
}

/*
* Routine: scd_join(int tbl, int col, ds_key_t jDate)
* Purpose: create joins to slowly changing dimensions
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
scd_join(int tbl, int col, ds_key_t jDate)
{
	ds_key_t res,
		kRowcount;
	static int bInit = 0,
		jMinimumDataDate,
		jMaximumDataDate,
		jH1DataDate,
		jT1DataDate,
		jT2DataDate;
	date_t dtTemp;

	if (!bInit)
	{
		strtodt(&dtTemp, DATA_START_DATE);
		jMinimumDataDate = dtTemp.julian;
		strtodt(&dtTemp, DATA_END_DATE);
		jMaximumDataDate = dtTemp.julian;
		jH1DataDate = jMinimumDataDate + (jMaximumDataDate - jMinimumDataDate) / 2;
		jT2DataDate = (jMaximumDataDate - jMinimumDataDate) / 3;
		jT1DataDate = jMinimumDataDate + jT2DataDate;
		jT2DataDate += jT1DataDate; 
		bInit = 1;
	}

	kRowcount = getIDCount(tbl);
	genrand_key(&res, DIST_UNIFORM, 1, kRowcount, 0, col);	/* pick the id */
	res = matchSCDSK(res, jDate, tbl); /* map to the date-sensitive surrogate key */

	/* can't have a revision in the future, per bug 114 */
	if (jDate > jMaximumDataDate)
		res = -1;
	
	return((res > get_rowcount(tbl))?-1:res);
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
matchSCDSK(ds_key_t kUnique, ds_key_t jDate, int nTable)
{
	ds_key_t kReturn = -1;
	static int bInit = 0;
	int jMinimumDataDate,
		jMaximumDataDate;
	static int jH1DataDate,
		jT1DataDate,
		jT2DataDate;
	date_t dtTemp;
	
	if (!bInit)
	{
		strtodt(&dtTemp, DATA_START_DATE);
		jMinimumDataDate = dtTemp.julian;
		strtodt(&dtTemp, DATA_END_DATE);
		jMaximumDataDate = dtTemp.julian;
		jH1DataDate = jMinimumDataDate + (jMaximumDataDate - jMinimumDataDate) / 2;
		jT2DataDate = (jMaximumDataDate - jMinimumDataDate) / 3;
		jT1DataDate = jMinimumDataDate + jT2DataDate;
		jT2DataDate += jT1DataDate; 
		bInit = 1;
	}
	
	switch(kUnique % 3)	/* number of revisions for the ID */
	{
	case 1:	/* only one occurrence of this ID */
		kReturn = (kUnique / 3) * 6;
		kReturn += 1;
		break;
	case 2: /* two revisions of this ID */
		kReturn = (kUnique / 3) * 6;
		kReturn += 2;
		if (jDate > jH1DataDate)
			kReturn += 1;
		break;
	case 0:	/* three revisions of this ID */
		kReturn = (kUnique / 3) * 6;
		kReturn += - 2;
		if (jDate > jT1DataDate)
			kReturn += 1;
		if (jDate > jT2DataDate)
			kReturn += 1;
		break;
	}

	if (kReturn > get_rowcount(nTable))
      kReturn = get_rowcount(nTable);
   
   return(kReturn);
}

/*
* Routine: 
* Purpose: map from a unique ID to a random SK
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
getSKFromID(ds_key_t kID, int nColumn)
{
   ds_key_t kTemp = -1;

   switch(kID % 3)
   {
   case 1:  /* single revision */
      kTemp = kID / 3;
      kTemp *= 6;
      kTemp += 1;
      break;
   case 2:  /* two revisions */
      kTemp = kID / 3;
      kTemp *= 6;
      kTemp += genrand_integer(NULL, DIST_UNIFORM, 2, 3, 0, nColumn);
      break;
   case 0:  /* three revisions */
      kTemp = kID / 3;
      kTemp -= 1;
      kTemp *= 6;
      kTemp += genrand_integer(NULL, DIST_UNIFORM, 4, 6, 0, nColumn);
      break;
   }

   return(kTemp);
}

/*
* Routine: getFirstSK
* Purpose: map from id to an SK that can be mapped back to an id by printID()
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
getFirstSK(ds_key_t kID)
{
   ds_key_t kTemp = -1;

   switch(kID % 3)
   {
   case 1:  /* single revision */
      kTemp = kID / 3;
      kTemp *= 6;
      kTemp += 1;
      break;
   case 2:  /* two revisions */
      kTemp = kID / 3;
      kTemp *= 6;
      kTemp += 2;
      break;
   case 0:  /* three revisions */
      kTemp = kID / 3;
      kTemp -= 1;
      kTemp *= 6;
      kTemp += 4;
      break;
   }

   return(kTemp);
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
changeSCD(int nDataType, void *pNewData, void *pOldData, int *nFlags, int bFirst)
{
   
  /**
   * if nFlags is odd, then this value will be retained
   */
   if ((*nFlags != ((*nFlags / 2) * 2)) && (bFirst == 0))
   {

      /*
       * the method to retain the old value depends on the data type 
       */
      switch(nDataType)
      {
      case SCD_INT:
         *(int *)pNewData = *(int *)pOldData;
         break;
      case SCD_PTR:
         pNewData = pOldData;
         break;
      case SCD_KEY:
         *(ds_key_t *)pNewData = *(ds_key_t *)pOldData;
         break;
     case SCD_CHAR:
         strcpy((char *)pNewData, (char *)pOldData);
         break;
      case SCD_DEC:
         memcpy(pNewData, pOldData, sizeof(decimal_t));
         break;
      }
   }
   else {

      /*
       * the method to set the old value depends on the data type 
       */
      switch(nDataType)
      {
      case SCD_INT:
         *(int *)pOldData = *(int *)pNewData;
         break;
      case SCD_PTR:
         pOldData = pNewData;
         break;
      case SCD_KEY:
         *(ds_key_t *)pOldData = *(ds_key_t *)pNewData;
         break;
      case SCD_CHAR:
         strcpy((char *)pOldData, (char *)pNewData);
         break;
      case SCD_DEC:
         memcpy(pOldData, pNewData, sizeof(decimal_t));
         break;
      }
   }
  
   *nFlags /= 2;
   
   
   return;
}
