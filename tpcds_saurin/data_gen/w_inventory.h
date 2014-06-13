/*
* $Id: w_inventory.h,v 1.4 2005/04/19 16:48:34 jms Exp $
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
* $Log: w_inventory.h,v $
* Revision 1.4  2005/04/19 16:48:34  jms
* Bug #167: Extra column in inventory
*
* Revision 1.3  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.3  2004/08/20 19:40:50  jms
* changes from August F-2-F
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
/*
 * INVENTORY table structure 
 */
struct W_INVENTORY_TBL {
	ds_key_t	inv_date_sk;
	ds_key_t	inv_item_sk;
	ds_key_t	inv_warehouse_sk;
	int			inv_quantity_on_hand;
};


int mk_w_inventory(void *pDest, ds_key_t kIndex);
int pr_w_inventory(void *pSrc);
int ld_w_inventory(void *pSrc);
ds_key_t sc_w_inventory(int nScale);

