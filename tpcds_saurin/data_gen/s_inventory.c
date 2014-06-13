/*
* $Id: s_inventory.c,v 1.16 2007/10/17 21:51:05 jms Exp $
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
* $Log: s_inventory.c,v $
* Revision 1.16  2007/10/17 21:51:05  jms
* correcting 32/64 bug found by Meikel
*
* Revision 1.15  2007/07/31 05:19:15  jms
* bug 546: s_inventory
*
* Revision 1.14  2007/02/23 22:27:27  jms
* Bug 515
*
* Revision 1.13  2007/02/23 20:06:56  jms
* Bug 515
*
* Revision 1.12  2006/12/07 20:37:57  jms
* fix to inventory date settings
*
* Revision 1.11  2006/11/30 20:38:05  jms
* Bug 515
*
* Revision 1.10  2006/08/18 23:18:06  jms
* Bug #475
*
* Revision 1.9  2006/06/06 21:41:14  jms
* initial checkin of revised update scaling
*
* Revision 1.8  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.7  2006/03/17 23:41:19  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.5  2006/03/17 22:55:39  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2006/03/09 23:00:09  jms
* dependency cleanup
*
* Revision 1.3  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "genrand.h"
#include "s_inventory.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "r_params.h"
#include "parallel.h"
#include "scaling.h"
#include "scd.h"

struct S_INVENTORY_TBL g_s_inventory;

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
mk_s_inventory(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct S_INVENTORY_TBL *r;
	static ds_key_t item_count;
	static ds_key_t warehouse_count;
	ds_key_t kItem;
	int nTemp;
	
	if (pDest == NULL)
		r = &g_s_inventory;
	else
		r = pDest;

	if (!bInit)
	{
        item_count = getIDCount(ITEM);
        warehouse_count = get_rowcount (WAREHOUSE);
		memset(&g_s_inventory, 0, sizeof(struct S_INVENTORY_TBL));
		bInit = 1;
	}
	
	nTemp = (int) kIndex - 1;
	kItem = (nTemp % item_count) + 1;
	nTemp /= (int) item_count;
	r->warehouse_id = (nTemp % warehouse_count) + 1;


	/*
	 * the generation of SCD ids in the warehouse is tied to the monotonically increasing surrogate key.
	 * this isn't ideal, but changing the data set on the warehouse side is a problem at this late date, so we
	 * need to mimic the behavior.
	 */
   r->invn_date.julian = getUpdateDate(S_INVENTORY, kIndex);
	r->item_id = getFirstSK(kItem);
	genrand_integer(&r->quantity, DIST_UNIFORM, INVN_MIN_QUANTITY, INVN_MAX_QUANTITY, 0, S_INVN_QUANTITY);

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
pr_s_inventory(void *pSrc)
{
	struct S_INVENTORY_TBL *r;
	
	if (pSrc == NULL)
		r = &g_s_inventory;
	else
		r = pSrc;
	
	print_start(S_INVENTORY);
	print_id(S_INVN_WAREHOUSE, r->warehouse_id, 1);
	print_id(S_INVN_ITEM, r->item_id, 1);
	print_date(S_INVN_DATE, r->invn_date.julian, 1);
	print_integer(S_INVN_QUANTITY, r->quantity, 0);
	print_end(S_INVENTORY);
	
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
ld_s_inventory(void *pSrc)
{
	struct S_INVENTORY_TBL *r;
		
	if (pSrc == NULL)
		r = &g_s_inventory;
	else
		r = pSrc;
	
	return(0);
}

