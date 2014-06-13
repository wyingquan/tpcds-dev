/*
* $Id: parallel.h,v 1.4 2006/10/11 23:55:37 jms Exp $
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
* $Log: parallel.h,v $
* Revision 1.4  2006/10/11 23:55:37  jms
* minor changes as part of parallelism exploration
*
* Revision 1.3  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.3  2004/04/06 17:34:44  jms
* keep small tables from being built repeatedly when called as part of parallel generation
*
* Revision 1.2  2004/03/27 00:17:37  jms
* first cut at parallelism
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef PARALLEL_H
#define PARALLEL_H
int split_work(int nTable, ds_key_t *pkFirstRow, ds_key_t *pkRowCount);
int	row_stop(int tbl);
int	row_skip(int tbl, ds_key_t count);
#endif /* PARALLEL_H */
