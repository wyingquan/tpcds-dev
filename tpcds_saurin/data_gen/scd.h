/*
* $Id: scd.h,v 1.14 2007/07/07 19:49:12 jms Exp $
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
* $Log: scd.h,v $
* Revision 1.14  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.13  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.12  2006/08/29 00:00:28  jms
* Bug 484: pass nFieldChangeFlags by reference
*
* Revision 1.11  2006/08/23 22:27:12  jms
* Bug 484; add SCD func for pointers
*
* Revision 1.10  2006/08/18 12:56:27  jms
* bug 477
*
* Revision 1.9  2006/07/18 23:03:26  jms
* Bug 473
*
* Revision 1.8  2006/07/11 16:16:11  jms
* Bug 351: replace bit twiddling with arithmetic
*
* Revision 1.7  2006/06/21 19:14:05  jms
* Bug  461
*
* Revision 1.6  2006/04/10 23:37:32  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.5  2006/02/02 05:55:45  jms
* fix SCD FK errors resulting from over-corrected key->sk mapping
*
* Revision 1.4  2005/10/31 19:29:36  jms
* changes to the source schema to move the views forward
*
* Revision 1.3  2005/01/13 19:54:09  jms
* Correct join to SCDs
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
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
*
*/
#ifndef SCD_H
#define SCD_H
#include "decimal.h"

extern char arBKeys[MAX_TABLE][17];
int setSCDKeys(int nTableID, ds_key_t hgIndex, char *szBKey, ds_key_t *hgBeginDateKey, ds_key_t *hgEndDateKey);
ds_key_t scd_join(int tbl, int col, ds_key_t jDate);
ds_key_t matchSCDSK(ds_key_t kUnique, ds_key_t jDate, int nTable);
ds_key_t getSKFromID(ds_key_t kID, int nColumn);
ds_key_t getFirstSK(ds_key_t kID);
/* 
 * handle the partial change of a history keeping record 
 * TODO: remove the macros in favor of straight fucntion calls
 */
#define SCD_INT   0
#define SCD_CHAR  1
#define SCD_DEC   2
#define SCD_KEY	  3
#define SCD_PTR	  4
void	changeSCD(int nDataType, void *pNewData, void *pOldData, int *nFlags, int bFirst);
int		validateSCD(int nTable, ds_key_t kRow, int *Permutation);
void     printValidation(int nTable, ds_key_t kRow);
#endif
