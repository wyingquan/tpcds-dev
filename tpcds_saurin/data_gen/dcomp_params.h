/*
* $Id: dcomp_params.h,v 1.3 2006/05/10 22:03:22 jms Exp $
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
* $Log: dcomp_params.h,v $
* Revision 1.3  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.2  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2003/06/24 19:52:55  jms
* clean up command line options, lay ground work for 2-pass qgen (bugs: 26, 36)
*
* Revision 1.2  2003/06/05 21:18:30  jms
* generate header file to allow distribution names aliases to be used in C
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef DCOMP_PARAMS_H
#define DCOMP_PARAMS_H

#include "r_params.h"
#define MAX_PARAM	4
#ifdef DECLARER

option_t options[] =
{
/* General Parmeters */
{"PROG",OPT_STR|OPT_HIDE|OPT_SET,0, "DO NOT MODIFY" , NULL, "distcomp"}, 
{"INPUT",OPT_STR,1, "read distributions from file <s>", NULL, ""}, 
{"VERBOSE",OPT_FLG,2, "enable verbose output", NULL, "N"}, 
{"HELP",OPT_FLG,3, "display this message", usage, "N"},
{"OUTPUT",OPT_STR,4, "output the compiled distributions to <s>", NULL, "."}, 
{"HEADER",OPT_STR,5, "output distribution index names to header file <s>", NULL, ""},
{NULL}
};

char *params[MAX_PARAM + 2];
#else
extern option_t options[];
extern char *params[];
extern char *szTableNames[];
#endif
#endif
