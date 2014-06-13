/*
* $Id: params.h,v 1.10 2007/09/10 18:10:36 jms Exp $
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
* $Log: params.h,v $
* Revision 1.10  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.9  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.8  2007/04/26 22:29:45  jms
* TPCDS bug 541
*
* Revision 1.7  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.6  2005/10/03 18:53:54  jms
* seed RNG seed from command line
*
* Revision 1.5  2005/07/20 22:48:25  jms
* add data validation
* relocate dateScaling
*
* Revision 1.4  2005/01/13 22:54:38  jms
* remove collision between FILTER and FORCE
*
* Revision 1.3  2005/01/13 20:10:04  jms
* add FILTER option
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.9  2004/08/24 16:33:14  jms
* add -release option to display version information
*
* Revision 1.8  2004/06/04 00:29:41  jms
* final 1.1.13b corrections
*
* Revision 1.7  2004/05/04 18:43:54  jms
* clarify parallel/child explanation
*
* Revision 1.6  2004/04/02 18:10:01  jms
* enable parallel generation
*
* Revision 1.5  2004/03/27 00:30:25  jms
* add paralellism parameters
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.6  2003/07/14 23:14:54  jms
* enable continuous scaling in integer GB
*
* Revision 1.5  2003/06/24 19:52:55  jms
* clean up command line options, lay ground work for 2-pass qgen (bugs: 26, 36)
*
* Revision 1.4  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*/
#ifndef QGEN_PARAMS_H
#define QGEN_PARAMS_H
#include "r_params.h"
#include "release.h"
#ifdef DECLARER

option_t options[] =
{
{"ABREVIATION",	OPT_STR,			0,"build table with abreviation <s>", NULL, ""}, 
{"DELIMITER",	OPT_STR|OPT_ADV,	1,"use <s> as output field separator", NULL, "|"}, 
{"DIR",			OPT_STR,			2,"generate tables in directory <s>", NULL, "."}, 
{"DISTRIBUTIONS",	OPT_STR|OPT_ADV,		3, "read distributions from file <s>", NULL, "tpcds.idx"}, 
{"FORCE",		OPT_FLG|OPT_ADV,	4,"over-write data files without prompting", NULL, "N"}, 
{"HELP",		OPT_INT,			5, "display this message", usage, "0"},
{"PARAMS",		OPT_STR,			6, "read parameters from file <s>", read_file, ""}, 
{"PROG",		OPT_STR|OPT_HIDE|OPT_SET,	7, "DO NOT MODIFY" , NULL, "DBGEN2"}, 
{"QUIET",		OPT_FLG,			8, "disable all output to stdout/stderr", NULL, "N"}, 
{"SCALE",		OPT_INT,			9,"volume of data to generate in GB", SetScaleIndex, "1"}, 
{"SUFFIX",		OPT_STR|OPT_ADV,	10,"use <s> as output file suffix", NULL, ".dat"}, 
{"TABLE",		OPT_STR,			11,"build only table <s>", NULL, "ALL"}, 
{"TERMINATE",	OPT_FLG|OPT_ADV,	12,"end each record with a field delimiter", NULL, "Y"}, 
{"UPDATE",		OPT_INT,			13,"generate update data set <n>", NULL, ""}, 
{"VERBOSE",		OPT_FLG,			14, "enable verbose output", NULL, "N"}, 
{"_SCALE_INDEX",	OPT_INT|OPT_HIDE,	15, "Scale band; used for dist lookups" , NULL, "1"}, 
{"PARALLEL",	OPT_INT,			16,"build data in <n> separate chunks", NULL, ""}, 
{"CHILD",		OPT_INT,			17,"generate <n>th chunk of the parallelized data", NULL, "1"}, 
{"CHKSEEDS",		OPT_FLG|OPT_HIDE,	18, "validate RNG usage for parallelism", NULL, "N"}, 
{"RELEASE",		OPT_FLG,			19, "display the release information", printReleaseInfo, "N"}, 
{"_FILTER",		OPT_FLG,			20, "output data to stdout", NULL, "N"}, 
{"VALIDATE",	OPT_FLG,			21, "produce rows for data validation", NULL, "N"}, 
{"VCOUNT",		OPT_INT|OPT_ADV,	22, "set number of validation rows to be produced", NULL, "50"}, 
{"VSUFFIX",		OPT_STR|OPT_ADV,	23, "set file suffix for data validation", NULL, ".vld"}, 
{"RNGSEED",		OPT_INT|OPT_ADV,	24, "set RNG seed", NULL, "19620718"}, 
{NULL}
};

char *params[23 + 2];
#else
extern option_t options[];
extern char *params[];
extern char *szTableNames[];
#endif
#endif
