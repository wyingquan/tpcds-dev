/*
* $Id: misc.h,v 1.2 2004/11/24 23:54:17 jms Exp $
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
* $Log: misc.h,v $
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2002/08/28 21:55:26  jms
* Relocate misplaced declaration of print_date()
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/04 01:20:06  jms
* Added print_boolean() to handle Y/N flags
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef MISC_H
#define MISC_H
int prep_direct(int dialect);
int close_direct(int dialect);
int pick_tbl(char *dname);
int itostr(char *dest, int i);
int char_op(char *dest, int op, char *s1, char *s2);
char *gen_text(char *dest, int min, int max, int stream);
int int_op(int *dest, int op, int arg1, int arg2);

char	*env_config (char *var, char *dflt);
int     a_rnd (int min, int max, int column, char *dest);
#endif
