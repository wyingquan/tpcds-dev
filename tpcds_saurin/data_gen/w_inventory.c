/*
* $Id: w_inventory.c,v 1.13 2007/08/02 18:56:30 jms Exp $
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
* $Log: w_inventory.c,v $
* Revision 1.13  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.12  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.11  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.10  2006/02/17 23:20:18  jms
* Bug 387: inventory doesn't cover full date range
*
* Revision 1.9  2006/02/10 00:24:49  jms
* tie inventory scaling to unique IDs of item, rather than rowcount
*
* Revision 1.8  2006/02/02 05:55:45  jms
* fix SCD FK errors resulting from over-corrected key->sk mapping
*
* Revision 1.7  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.6  2005/12/08 23:57:14  jms
* Bug 354: duplicate values for primary key on inventory
*
* Revision 1.5  2005/04/19 16:48:34  jms
* Bug #167: Extra column in inventory
*
* Revision 1.4  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.3  2005/01/13 19:56:34  jms
* Correct join to SCDs
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.9  2004/10/06 21:40:22  jms
* Bug #98: change inventory granularity to 1 week
*
* Revision 1.8  2004/10/06 21:13:15  jms
* Bug #98: change inventory granularity to 1 week
*
* Revision 1.7  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.6  2004/06/04 00:29:41  jms
* final 1.1.13b corrections
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/04/02 18:05:08  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
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
#include "genrand.h"
#include "w_inventory.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "scaling.h"
#include "constants.h"
#include "date.h"
#include "nulls.h"
#include "tdefs.h"
#include "scd.h"

struct W_INVENTORY_TBL g_w_inventory;

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
mk_w_inventory(void *pDest, ds_key_t index)
{
	static int bInit = 0;
	struct W_INVENTORY_TBL *r;
	static ds_key_t item_count;
	static ds_key_t warehouse_count;
	static int jDate;
	date_t *base_date;
	int nTemp;
   tdef *pTdef = getSimpleTdefsByNumber(INVENTORY);
	
	if (pDest == NULL)
		r = &g_w_inventory;
	else
		r = pDest;

	if (!bInit)
	{
		memset(&g_w_inventory, 0, sizeof(struct W_INVENTORY_TBL));
        item_count = getIDCount(ITEM);
        warehouse_count = get_rowcount (WAREHOUSE);
        base_date = strtodate (DATE_MINIMUM);
        jDate = base_date->julian;
        set_dow(base_date);
        /* Make exceptions to the 1-rng-call-per-row rule */
		bInit = 1;
	}

	nullSet(&pTdef->kNullBitMap, INV_NULLS);
	nTemp = (int) index - 1;
	r->inv_item_sk = (nTemp % item_count) + 1;
	nTemp /= (int) item_count;
	r->inv_warehouse_sk = (nTemp % warehouse_count) + 1;
	nTemp /= (int) warehouse_count;
	r->inv_date_sk = jDate + (nTemp * 7);	/* inventory is updated weekly */

	/* 
	 * the join between item and inventory is tricky. The item_id selected above identifies a unique part num
	 * but item is an SCD, so we need to account for that in selecting the SK to join with
	 */
	r->inv_item_sk = matchSCDSK(r->inv_item_sk, r->inv_date_sk, ITEM);

	genrand_integer (&r->inv_quantity_on_hand, DIST_UNIFORM,
		INV_QUANTITY_MIN, INV_QUANTITY_MAX, 0, INV_QUANTITY_ON_HAND);
	
	
	return (0);
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
pr_w_inventory(void *row)
{
	struct W_INVENTORY_TBL *r;
	
	if (row == NULL)
		r = &g_w_inventory;
	else
		r = row;	
	
	print_start(INVENTORY);
	print_key(INV_DATE_SK, r->inv_date_sk, 1);
	print_key(INV_ITEM_SK, r->inv_item_sk, 1);
	print_key(INV_WAREHOUSE_SK, r->inv_warehouse_sk, 1);
	print_integer(INV_QUANTITY_ON_HAND, r->inv_quantity_on_hand, 0);
	print_end(INVENTORY);

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
ld_w_inventory(void *pSrc)
{
	struct W_INVENTORY_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_inventory;
	else
		r = pSrc;
	
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
ds_key_t 
sc_w_inventory(int nScale)
{
	ds_key_t kRes;
	date_t dTemp;
	int nDays;
	
	kRes = getIDCount(ITEM);
	kRes *= get_rowcount(WAREHOUSE);
	strtodt(&dTemp, DATE_MAXIMUM);
	nDays = dTemp.julian;
	strtodt(&dTemp, DATE_MINIMUM);
	nDays -= dTemp.julian;
   nDays += 1;
	nDays += 6;
	nDays /= 7;	/* each items inventory is updated weekly */
	kRes *= nDays;
	
	return(kRes);
}

