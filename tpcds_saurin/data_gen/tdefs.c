/*
* $Id: tdefs.c,v 1.14 2007/09/04 21:33:05 jms Exp $
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
* $Log: tdefs.c,v $
* Revision 1.14  2007/09/04 21:33:05  jms
* remove unused variable
*
* Revision 1.13  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.12  2007/07/31 16:35:43  jms
* 546: s_web_order
*
* Revision 1.11  2007/07/31 06:07:39  jms
* bug 546: s_promotion
*
* Revision 1.10  2007/07/31 04:36:00  jms
* Bug 546: s_catalog_page
*
* Revision 1.9  2006/08/17 20:44:50  jms
* Bug 481
*
* Revision 1.8  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.7  2006/02/02 05:06:09  jms
* scale factor aware qgen
*
* Revision 1.6  2006/01/08 23:37:51  jms
* ROWCOUNT() handling
*
* Revision 1.5  2006/01/02 19:39:49  jms
* Bug 357: segfault when building updates
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/01/13 19:53:11  jms
* Bug #136: sparse key support
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.11  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
*
* Revision 1.10  2004/10/14 17:52:50  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.9  2004/10/14 16:06:46  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.8  2004/09/08 21:14:21  jms
* add routine to map column id to table id
*
* Revision 1.7  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.6  2004/07/16 20:45:10  jms
* separation of source/warehouse tdefs
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2004/04/06 18:26:02  jms
* child tables need to be advanced along with parent to handle parallel generation
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
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "tables.h"
#include "columns.h"
#include "genrand.h"
#include "tdefs.h"
#include "scaling.h"
#include "w_tdefs.h"
#include "s_tdefs.h"
#include "tdef_functions.h"
#include "r_params.h"

extern tdef w_tdefs[];
extern tdef s_tdefs[];
extern table_func_t s_tdef_funcs[];
extern table_func_t w_tdef_funcs[];

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
* TODO: None
*/
ds_key_t 
GetRowcountByName(char *szName)
{
	int nTable = -1;
	
	nTable = GetTableNumber(szName);
	if (nTable >= 0)
		return(get_rowcount(nTable - 1));

	nTable = distsize(szName);
	return(nTable);

}

/*
* Routine: GetTableNumber(char *szName)
* Purpose: Return size of table, pseudo table or distribution
* Algorithm: Need to use rowcount distribution, since argument could be a pseudo table 
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
GetTableNumber(char *szName)
{
	int i;
	char *szTable;

	for (i=1; i <= distsize("rowcounts"); i++)
	{
		dist_member(&szTable, "rowcounts", i, 1);
		if (strcasecmp(szTable, szName) == 0)
			return(i - 1);
	}

	return(-1);
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
/*
tdef *
getTdefsByNumber(int nTable)
{
   if (is_set("UPDATE"))
   {
      if (s_tdefs[nTable].flags & FL_PASSTHRU)
      {
         switch(nTable + S_BRAND)
         {
         case S_CATALOG_PAGE: nTable = CATALOG_PAGE; break;
         case S_CUSTOMER_ADDRESS: nTable = CUSTOMER_ADDRESS; break;
         case S_PROMOTION: nTable = PROMOTION; break;
         }
         return(&w_tdefs[nTable]);
      }
      else
         return(&s_tdefs[nTable]);
   }
	else
		return(&w_tdefs[nTable]);
}
*/
tdef *
getSimpleTdefsByNumber(nTable)
{
   if (nTable >= S_BRAND)
      return(&s_tdefs[nTable - S_BRAND]);
   return(&w_tdefs[nTable]);
}

tdef *
getTdefsByNumber(int nTable)
{
   if (is_set("UPDATE") && is_set("VALIDATE"))
   {
      if (s_tdefs[nTable].flags & FL_PASSTHRU)
      {
         switch(nTable + S_BRAND)
         {
         case S_CATALOG_PAGE: nTable = CATALOG_PAGE; break;
         case S_CUSTOMER_ADDRESS: nTable = CUSTOMER_ADDRESS; break;
         case S_PROMOTION: nTable = PROMOTION; break;
         }
         return(&w_tdefs[nTable]);
      }
      else
         return(&s_tdefs[nTable]);
   }

   return(getSimpleTdefsByNumber(nTable));
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
char *
getTableNameByID(int i)
{	
   tdef *pT = getSimpleTdefsByNumber(i);

	return(pT->name);
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
getTableFromColumn(int nColumn)
{
	int i;
   tdef *pT;
	
	for (i=0; i <= MAX_TABLE; i++)
	{
      pT = getSimpleTdefsByNumber(i);
      if ((nColumn >= pT->nFirstColumn) && (nColumn <= pT->nLastColumn))
				return(i);
	}
	return(-1);
}

