	/*
* $Id: w_item.c,v 1.32 2007/10/02 16:30:56 jms Exp $
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
* $Log: w_item.c,v $
* Revision 1.32  2007/10/02 16:30:56  jms
* null out g_OldValues
*
* Revision 1.31  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.30  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.29  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.28  2007/01/09 22:11:26  jms
* bug 525
*
* Revision 1.27  2006/10/10 16:37:44  jms
* changes for NullBitMap and chunking
*
* Revision 1.26  2006/08/30 18:28:15  jms
* initialize W_ITEM_TBL structure
*
* Revision 1.25  2006/08/29 18:51:46  jms
* SCD data type changes
*
* Revision 1.24  2006/08/29 18:44:10  jms
* bug 351: correct SCD type for i_brand_id
*
* Revision 1.23  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.22  2006/08/28 21:53:30  jms
* Bug 484: remove htonl call since changeSCD now uses arithmetic
*
* Revision 1.21  2006/08/23 23:08:52  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.20  2006/08/22 21:47:55  jms
* Bug 484/351: requrie 32b data type for SCD decisions
*
* Revision 1.19  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.18  2006/06/21 19:14:05  jms
* Bug  461
*
* Revision 1.17  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.16  2006/04/28 00:39:51  jms
* header file cleanup
*
* Revision 1.15  2006/04/12 23:32:06  jms
* w_item scaling changes
*
* Revision 1.14  2006/02/17 23:59:45  jms
* adjust for new entry in i_current_price distirbution
*
* Revision 1.13  2006/01/13 19:06:16  jms
* Bug #365: tem.i_manager_id range is wrong
*
* Revision 1.12  2005/12/08 20:39:34  jms
* Bug 350: different data with and without table option
*
* Revision 1.11  2005/11/22 19:53:39  jms
* add index to table to allow indirect lookup from qgen
*
* Revision 1.10  2005/11/11 21:14:12  jms
* add i_wholesale_cost
*
* Revision 1.9  2005/11/11 21:09:04  jms
* add i_wholesale_cost
*
* Revision 1.8  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.7  2005/10/06 22:39:34  jms
* bug #304: add initializer for bFirstRecord
*
* Revision 1.6  2005/10/06 22:11:02  jms
* correct a typo
*
* Revision 1.5  2005/10/05 22:38:54  jms
* bug #236: acid query fails; appears to be a int/key problem?
*
* Revision 1.4  2004/12/02 19:13:53  jms
* Bug #129: wrong dist in i_current_price
*
* Revision 1.3  2004/12/01 00:29:33  jms
* fix parallelism
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.13  2004/09/24 19:08:18  jms
* Set up for release 1_1_18
*
* Revision 1.12  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.11  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.10  2004/08/13 21:52:42  jms
* porting changes for HP/UX
*
* Revision 1.9  2004/08/13 21:48:51  jms
* porting changes for HP/UX
*
* Revision 1.8  2004/08/13 21:10:08  jms
* include <sys/byteorder.h> for SOLARIS
*
* Revision 1.7  2004/08/06 23:08:52  jms
* merge in SCD changes
*
* Revision 1.6.2.2  2004/08/03 23:57:28  jms
* Change handling of business keys to use strcpy() whenever a new key is generated
*
* Revision 1.6.2.1  2004/07/30 21:59:30  jms
* Initial checkin of SCD chagnes
*
* Revision 1.6  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/05/14 06:58:14  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
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
#ifdef NCR
#include <sys/types.h>
#endif
#ifndef WIN32
#include <netinet/in.h>
#endif
#include "genrand.h"
#include "w_item.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "nulls.h"
#include "tdefs.h"
#include "scd.h"

/* extern tdef w_tdefs[]; */

struct W_ITEM_TBL g_w_item,
	g_OldValues;

/*
* mk_item
*/
int
mk_w_item (void* row, ds_key_t index)
{
	
	int32_t res = 0;
	/* begin locals declarations */
	decimal_t dMinPrice, 
		dMaxPrice,
		dMarkdown;
	static decimal_t dMinMarkdown, dMaxMarkdown;
	int32_t bUseSize,
		bFirstRecord = 0,
		nFieldChangeFlags,
		nMin,
		nMax,
		nIndex,
		nTemp;
	char *cp;
	struct W_ITEM_TBL *r;
	static int32_t bInit = 0;
	struct W_ITEM_TBL *rOldValues = &g_OldValues;
	char *szMinPrice = NULL,
		*szMaxPrice = NULL;
   tdef *pT = getSimpleTdefsByNumber(ITEM);


	if (row == NULL)
		r = &g_w_item;
	else
		r = row;
	
	
	if (!bInit)
	{
		/* some fields are static throughout the data set */
		strtodec(&dMinMarkdown, MIN_ITEM_MARKDOWN_PCT);
		strtodec(&dMaxMarkdown, MAX_ITEM_MARKDOWN_PCT);

		bInit = 1;
	}
	
	memset(r, 0, sizeof(struct W_ITEM_TBL));

	/* build the new value */
	nullSet(&pT->kNullBitMap, I_NULLS);
	r->i_item_sk = index;

	nIndex = pick_distribution(&nMin, "i_manager_id", 2, 1, I_MANAGER_ID);
	dist_member(&nMax, "i_manager_id", nIndex, 3);
	genrand_key(&r->i_manager_id, DIST_UNIFORM, 
		(ds_key_t)nMin, 
		(ds_key_t)nMax, 
		0, I_MANAGER_ID);



	/* if we have generated the required history for this business key and generate a new one 
	 * then reset associated fields (e.g., rec_start_date minimums)
	 */
	if (setSCDKeys(I_ITEM_ID, index, r->i_item_id, &r->i_rec_start_date_id, &r->i_rec_end_date_id))
	{
	/* 
	 * some fields are not changed, even when a new version of the row is written 
	 */
		bFirstRecord = 1;
	}
	
	 /*
	  * this is  where we select the random number that controls if a field changes from 
	  * one record to the next. 
	  */
	nFieldChangeFlags = next_random(I_SCD);


	/* the rest of the record in a history-keeping dimension can either be a new data value or not;
	 * use a random number and its bit pattern to determine which fields to replace and which to retain
	 */
	gen_text (r->i_item_desc, 1, RS_I_ITEM_DESC, I_ITEM_DESC);
	changeSCD(SCD_CHAR, &r->i_item_desc, &rOldValues->i_item_desc,  &nFieldChangeFlags,  bFirstRecord);
	
	nIndex = pick_distribution(&szMinPrice, "i_current_price", 2, 1, I_CURRENT_PRICE);
	dist_member(&szMaxPrice, "i_current_price", nIndex, 3);
	strtodec(&dMinPrice, szMinPrice);
	strtodec(&dMaxPrice, szMaxPrice);
	genrand_decimal(&r->i_current_price, DIST_UNIFORM, &dMinPrice, &dMaxPrice, NULL, I_CURRENT_PRICE);
	changeSCD(SCD_INT, &r->i_current_price, &rOldValues->i_current_price,  &nFieldChangeFlags,  bFirstRecord);

	genrand_decimal(&dMarkdown, DIST_UNIFORM, &dMinMarkdown, &dMaxMarkdown, NULL, I_WHOLESALE_COST);
	decimal_t_op(&r->i_wholesale_cost, OP_MULT, &r->i_current_price, &dMarkdown);
	changeSCD(SCD_DEC, &r->i_wholesale_cost, &rOldValues->i_wholesale_cost,  &nFieldChangeFlags,  bFirstRecord);

	hierarchy_item (I_CATEGORY, &r->i_category_id, &r->i_category, index);
	/*
         * changeSCD(SCD_INT, &r->i_category_id, &rOldValues->i_category_id,  &nFieldChangeFlags,  bFirstRecord);
         */

	hierarchy_item (I_CLASS, &r->i_class_id, &r->i_class, index);
	changeSCD(SCD_KEY, &r->i_class_id, &rOldValues->i_class_id,  &nFieldChangeFlags,  bFirstRecord);

	cp = &r->i_brand[0];
	hierarchy_item (I_BRAND, &r->i_brand_id, &cp, index);
	changeSCD(SCD_KEY, &r->i_brand_id, &rOldValues->i_brand_id,  &nFieldChangeFlags,  bFirstRecord);

	/* some categories have meaningful sizes, some don't */
	if (r->i_category_id)
   {
      dist_member(&bUseSize, "categories", (int)r->i_category_id, 3);
	pick_distribution (&r->i_size, "sizes", 1, bUseSize + 2, I_SIZE);
	changeSCD(SCD_PTR, &r->i_size, &rOldValues->i_size,  &nFieldChangeFlags,  bFirstRecord);
   }
   else
   {
      bUseSize = 0;
      r->i_size = NULL;
   }

	nIndex = pick_distribution(&nMin, "i_manufact_id", 2, 1, I_MANUFACT_ID);
	genrand_integer(&nTemp, DIST_UNIFORM, 
		nMin, 
		dist_member(NULL, "i_manufact_id", nIndex, 3), 
		0, I_MANUFACT_ID);
	r->i_manufact_id = nTemp;
	changeSCD(SCD_KEY, &r->i_manufact_id, &rOldValues->i_manufact_id,  &nFieldChangeFlags,  bFirstRecord);

	mk_word (r->i_manufact, "syllables", (int) r->i_manufact_id, RS_I_MANUFACT, ITEM);
	changeSCD(SCD_CHAR, &r->i_manufact, &rOldValues->i_manufact,  &nFieldChangeFlags,  bFirstRecord);

	gen_charset(r->i_formulation, DIGITS, RS_I_FORMULATION, RS_I_FORMULATION, I_FORMULATION);
	embed_string(r->i_formulation, "colors", 1, 2, I_FORMULATION);
	changeSCD(SCD_CHAR, &r->i_formulation, &rOldValues->i_formulation,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->i_color, "colors", 1, 2, I_COLOR);
	changeSCD(SCD_PTR, &r->i_color, &rOldValues->i_color,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->i_units, "units", 1, 1, I_UNITS);
	changeSCD(SCD_PTR, &r->i_units, &rOldValues->i_units,  &nFieldChangeFlags,  bFirstRecord);

	pick_distribution (&r->i_container, "container", 1, 1, ITEM);
	changeSCD(SCD_PTR, &r->i_container, &rOldValues->i_container,  &nFieldChangeFlags,  bFirstRecord);

	mk_word (r->i_product_name, "syllables", (int) index, RS_I_PRODUCT_NAME,
		ITEM);

	r->i_promo_sk = mk_join(I_PROMO_SK, PROMOTION, 1);
	genrand_integer(&nTemp, DIST_UNIFORM, 1, 100, 0, I_PROMO_SK);
	if (nTemp > I_PROMO_PERCENTAGE)
		r->i_promo_sk = -1;

/* 
 * if this is the first of a set of revisions, then baseline the old values
 */
 if (bFirstRecord)
   memcpy(&g_OldValues, r, sizeof(struct W_ITEM_TBL));

 if (index == 1)
   memcpy(&g_OldValues, r, sizeof(struct W_ITEM_TBL));

	return (res);
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
pr_w_item(void *row)
{
	struct W_ITEM_TBL *r;

	if (row == NULL)
		r = &g_w_item;
	else
		r = row;

	print_start(ITEM);
	print_key(I_ITEM_SK, r->i_item_sk, 1);
	print_varchar(I_ITEM_ID, r->i_item_id, 1);
	print_date(I_REC_START_DATE_ID, r->i_rec_start_date_id, 1);
	print_date(I_REC_END_DATE_ID, r->i_rec_end_date_id, 1);
	print_varchar(I_ITEM_DESC, r->i_item_desc, 1);
	print_decimal(I_CURRENT_PRICE, &r->i_current_price, 1);
	print_decimal(I_WHOLESALE_COST, &r->i_wholesale_cost, 1);
	print_key(I_BRAND_ID, r->i_brand_id, 1);
	print_varchar(I_BRAND, r->i_brand, 1);
	print_key(I_CLASS_ID, r->i_class_id, 1);
	print_varchar(I_CLASS, r->i_class, 1);
	print_key(I_CATEGORY_ID, r->i_category_id, 1);
	print_varchar(I_CATEGORY, r->i_category, 1);
	print_key(I_MANUFACT_ID, r->i_manufact_id, 1);
	print_varchar(I_MANUFACT, r->i_manufact, 1);
	print_varchar(I_SIZE, r->i_size, 1);
	print_varchar(I_FORMULATION, r->i_formulation, 1);
	print_varchar(I_COLOR, r->i_color, 1);
	print_varchar(I_UNITS, r->i_units, 1);
	print_varchar(I_CONTAINER, r->i_container, 1);
	print_key(I_MANAGER_ID, r->i_manager_id, 1);
	print_varchar(I_PRODUCT_NAME, r->i_product_name, 0);
	print_end(ITEM);

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
ld_w_item(void *pSrc)
{
	struct W_ITEM_TBL *r;
		
	if (pSrc == NULL)
		r = &g_w_item;
	else
		r = pSrc;
	
	return(0);
}

