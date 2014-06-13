/*
* $Id: tdef_functions.h,v 1.6 2007/08/02 18:56:30 jms Exp $
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
* $Log: tdef_functions.h,v $
* Revision 1.6  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.5  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.4  2007/05/21 20:34:16  jms
* TPCDS Bug 546
*
* Revision 1.3  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.5  2004/10/14 17:52:50  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.4  2004/10/14 16:27:00  jms
* LINUX porting changes for segregation of s/w tables
*
* Revision 1.3  2004/10/14 16:06:46  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.2  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.2  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.1  2003/03/21 19:56:45  jms
* resync with code on laptap
*
*/
#ifndef TDEF_FUNCTIONS_H
#define TDEF_FUNCTIONS_H
#include "tables.h"


/*
* table functions. 
* NOTE: This table contains the function declarations in the table descriptions; it must be kept in sync with the 
*    declararions of assocaited constants, found in tdefs.h

*/
typedef struct TABLE_FUNC_T {
	char *name;							/* -- name of the table; */
	int (*builder)(void*, ds_key_t);	/* -- function to prep output */
	int (*loader[2])(void *);			/* -- functions to present output */
   /* -- data validation function */
	int (*validate)(int nTable, ds_key_t kRow, int *Permutation);
	} table_func_t;

extern table_func_t w_tdef_funcs[MAX_TABLE];
extern table_func_t s_tdef_funcs[MAX_TABLE];
extern table_func_t *tdef_funcs;

int validateGeneric(int nTable, ds_key_t kRow, int *Permutation);
int validateSCD(int nTable, ds_key_t kRow, int *Permutation);

#endif /* TDEF_FUNCTIONS_H */
extern table_func_t s_tdef_funcs[];
extern table_func_t w_tdef_funcs[];

table_func_t *getTdefFunctionsByNumber(int nTable);
