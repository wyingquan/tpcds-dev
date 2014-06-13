/*
* $Id: sparse.h,v 1.1 2005/01/13 19:48:35 jms Exp $
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
* $Log: sparse.h,v $
* Revision 1.1  2005/01/13 19:48:35  jms
* Add sparse.[ch] to handle sparse keys in demographic tables
*
*/
int initSparseKeys(int nTable);				/* populate the set of valid keys */
ds_key_t randomSparseKey(int nTable, int nColumn);	/* select a random sparse key */
