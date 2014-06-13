/*
* $Id: validate.c,v 1.9 2007/10/18 15:53:02 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2007
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ==============
* $Log: validate.c,v $
* Revision 1.9  2007/10/18 15:53:02  jms
* remove unused variables
*
* Revision 1.8  2007/10/02 16:30:00  jms
* move to recursion for validate routine
*
* Revision 1.7  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.6  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.5  2007/07/31 05:16:03  jms
* bug 546: s_cusomter
*
* Revision 1.4  2007/07/31 04:36:01  jms
* Bug 546: s_catalog_page
*
* Revision 1.3  2007/07/30 18:02:41  jms
* TPCDS Bug 546 catalog_sales
*
* Revision 1.2  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.1  2007/07/27 20:15:13  jms
* isolate validation code
*
*
*/
#include "config.h"
#include "porting.h"
#include "tdefs.h"
#include "tdef_functions.h"
#include "r_params.h"
#include "parallel.h"
#include "constants.h"
#include "scd.h"
#include "permute.h"
#include "print.h"

/* extern tdef w_tdefs[]; */

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
validateGeneric(int nTable, ds_key_t kRow, int *Permute)
{
   tdef *pT = getSimpleTdefsByNumber(nTable);
   tdef *pChild;
   table_func_t *pTF = getTdefFunctionsByNumber(nTable);

	if (is_set("UPDATE") )
   {
      /*
      if (nTable < S_BRAND)
         nTable += S_BRAND;

         */
      if (!(pT->flags & FL_PASSTHRU)) 
         row_skip(nTable, kRow - 1);
      else
      {
         switch(nTable)
         {
         case S_CUSTOMER_ADDRESS: nTable = CUSTOMER_ADDRESS; break;
         case S_CATALOG_PAGE: nTable = CATALOG_PAGE; break;
         }
         pT = getSimpleTdefsByNumber(nTable);
         pTF = getTdefFunctionsByNumber(nTable);
         row_skip(nTable, kRow - 1);
      }
   }
   else
         row_skip(nTable, kRow - 1);
	if (pT->flags & FL_PARENT)
   {
      pChild = getSimpleTdefsByNumber(pT->nParam);
		row_skip(pT->nParam, kRow - 1);
   }
   pTF->builder(NULL, kRow);

	return(0);
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
validateSCD(int nTable, ds_key_t kRow, int *Permutation)
{
	ds_key_t kStart, 
      kEnd;
	char szID[RS_BKEY + 1];
	int nColumn, 
      nOffset = 0,
      nSKColumn,
      nID,
      nSkipTable = 0; /* some source schema tales are generated using the warehouse routine */
   table_func_t *pTF = getTdefFunctionsByNumber(nTable);
   table_func_t *pTS;

   nSkipTable = 0;
   switch(nTable + nOffset)
	{
	case CALL_CENTER: nColumn = CC_CALL_CENTER_ID; break;
	case ITEM: nColumn = I_ITEM_ID; break;
	case S_ITEM: nColumn = I_ITEM_ID; nSkipTable = ITEM; nSKColumn = S_ITEM_ID;break;
	case STORE: nColumn = W_STORE_ID; break;
	case WEB_PAGE: nColumn = WP_PAGE_ID; break;
	case WEB_SITE: nColumn = WEB_SITE_ID; break;
	case S_WEB_PAGE: nColumn = WP_PAGE_SK; nSkipTable = WEB_PAGE; nSKColumn = S_WPAG_ID;break;
	default:
		fprintf(stderr, "ERROR: Invalid table %d at %s:%d!\n", nTable, __FILE__, __LINE__);
		exit(-1);
	}

      row_skip(nTable, kRow - 1);
      if (nSkipTable)
      {
         nID = getPermutationEntry(Permutation, kRow); 
         nID = getSKFromID( nID, nSKColumn); 
         pTS = getTdefFunctionsByNumber(nSkipTable);
      }
      else
         nID = kRow;

      /* back up to the base row for SCD's */
      if ((!setSCDKeys(nColumn, nID, &szID[0], &kStart, &kEnd)) && (kRow > 1))
         validateSCD(nTable, kRow - 1, Permutation);

	/* set up to start building rows */
	row_skip((nSkipTable)?nSkipTable:nTable, kRow - 1);

	/* and output the target */
   if (nSkipTable)
      pTS->builder(NULL, nID);
   else
      pTF->builder(NULL, kRow);


	return(0);
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
printValidation(int nTable, ds_key_t kRow)
{
   table_func_t *pTdef = getTdefFunctionsByNumber(nTable);

   print_start(nTable);

	print_key(0, kRow, 1);
	if (pTdef->loader[is_set("DBLOAD")](NULL))
	{
		fprintf(stderr, "ERROR: Load failed on %s!\n", pTdef->name);
		exit(-1);
	}

   return;
}




