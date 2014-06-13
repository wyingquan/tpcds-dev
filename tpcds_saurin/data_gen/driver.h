/*
* $Id: driver.h,v 1.2 2004/11/24 23:54:16 jms Exp $
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
* $Log: driver.h,v $
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:36  jms
* re-establish external server
*
* Revision 1.7  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.11  2003/04/21 19:14:57  jms
* bug 9: lex changes for MP/RAS
*
* Revision 1.10  2003/04/16 23:07:25  jms
* v. 1.1.0 pre-release
*
* Revision 1.9  2003/04/09 20:38:59  jms
* release 1.0.10: qgen range() fixes
*
* Revision 1.8  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.7  2003/03/21 22:32:42  jms
* release 1.0.8
*
* Revision 1.6  2002/12/04 19:02:37  jms
* update release number
*
* Revision 1.5  2002/11/05 06:24:47  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.4  2002/09/04 17:18:07  jms
* Chnage revision to 0.0.5
*
* Revision 1.3  2002/08/14 00:15:49  jms
* unification of columns.h and streams.h
* update of tpcds.sql to match current WAM file
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/22 22:55:51  jms
* Update release to 0.0.3
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef R_DRIVER_H
#define  R_DRIVER_H

/*
 * defines used in the generic portion of r_driver.c
 * table specific defines are built in the output directory
 */
#define NONE	-1
/* note: needs to be kept in sync with a_decimal.h/p_symbol.h */
#define FL_INIT	0x0004
#define FL_FACT	0x8000

#ifdef DECLARER
#define EXTERN
#else
#define EXTERN extern
#endif /* DECLARER */


#include <stdio.h>
#include <stdlib.h>




/******* output macros ********/
#ifndef SEPARATOR
#define SEPARATOR '|' /* field spearator for generated flat files */
#endif



int tbl_init(int tbl, int *s, int *c);

#endif 
