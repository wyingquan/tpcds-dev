/*
* $Id: qgen_params.h,v 1.8 2006/08/18 20:35:40 jms Exp $
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
* $Log: qgen_params.h,v $
* Revision 1.8  2006/08/18 20:35:40  jms
* Bug reported by IBM: don't add in a -directory setting by default, but only when the option is explcitly set from the command line
*
* Revision 1.7  2006/05/12 18:09:29  jms
* add '-directory' option to qgen
*
* Revision 1.6  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.5  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.4  2005/10/03 18:55:53  jms
* add logging of query parameters
* add qualify option remove query permutation
* add filter option to aid debug
*
* Revision 1.3  2005/02/15 22:58:35  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:02  jms
* re-establish external server
*
* Revision 1.8  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.7  2004/09/24 20:01:26  jms
* Bug #97: ability to generate from a single template
*
* Revision 1.6  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.5  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.4  2004/02/28 22:49:52  jms
* simplify qgen command line and processing
*
* Revision 1.3  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.5  2003/06/24 19:52:55  jms
* clean up command line options, lay ground work for 2-pass qgen (bugs: 26, 36)
*
* Revision 1.4  2003/04/21 19:14:57  jms
* bug 9: lex changes for MP/RAS
*
* Revision 1.3  2003/03/21 19:56:45  jms
* resync with code on laptap
*
* Revision 1.2  2002/11/20 00:51:33  jms
* QGEN2 corrections
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef QGEN_PARAMS_H
#define QGEN_PARAMS_H

#include "r_params.h"
#include "release.h"
#define MAX_PARAM	21
#ifdef DECLARER

option_t options[] =
{
/* General Parmeters */
{"PROG",		OPT_STR|OPT_HIDE|OPT_SET,	0, "DO NOT MODIFY" , NULL, "qgen2"}, 
{"FILE",		OPT_STR,			1, "read parameters from file <s>", read_file, ""}, 
{"VERBOSE",		OPT_FLG,			2, "enable verbose output", NULL, "N"}, 
{"HELP",		OPT_FLG,			3, "display this message", usage, "N"},
{"DISTRIBUTIONS",	OPT_STR|OPT_ADV,4, "read distributions from file <s>", NULL, "tpcds.idx"}, 
{"OUTPUT_DIR",	OPT_STR,			5, "write query streams into directory <s>", NULL, "."}, 
#ifndef WIN32
{"PATH_SEP",	OPT_STR|OPT_ADV,	6, "use <s> to separate path elements", NULL, "/"}, 
#else
{"PATH_SEP",	OPT_STR|OPT_ADV,	6, "use <s> to separate path elements", NULL, "\\\\"}, 
#endif
{"DUMP",		OPT_FLG|OPT_ADV|OPT_HIDE,	7,"dump templates as parsed", NULL, "N"}, 
{"YYDEBUG",		OPT_FLG|OPT_ADV|OPT_HIDE,	8,"debug the grammar", NULL, "N"}, 
{"QUIET",		OPT_FLG,			9, "suppress all output (for scripting)", NULL, "N"}, 
{"STREAMS",		OPT_INT,			10, "generate <n> query streams/versions", NULL, "1"}, 
{"INPUT",		OPT_STR,			11, "read template names from <s>", NULL, ""}, 
{"SCALE",		OPT_INT,			12, "assume a database of <n> GB", NULL, "1"}, 
{"RNGSEED",		OPT_INT|OPT_ADV,	13, "seed the RNG with <n>", NULL, "19620718"}, 
{"RELEASE",		OPT_FLG|OPT_ADV,	14, "display QGEN release info", printReleaseInfo, ""}, 
{"TEMPLATE",	OPT_STR|OPT_ADV,	15, "build queries from template <s> ONLY", NULL, ""}, 
{"COUNT",		OPT_INT|OPT_ADV,	16, "generate <n> versions per stream (used with TEMPLATE)", NULL, "1"}, 
{"DEBUG",		OPT_FLG|OPT_ADV,	17,	"minor debugging outptut", NULL, "N"},
{"LOG",			OPT_STR,			18,	"write parameter log to <s>", NULL, ""},
{"FILTER",		OPT_FLG|OPT_ADV,	19,	"write generated queries to stdout", NULL, "N"},
{"QUALIFY",		OPT_FLG,			20,	"generate qualification queries in ascending order", NULL, "N"},
{"DIALECT",		OPT_STR|OPT_ADV,	21, "include query dialect defintions found in <s>.tpl", NULL, "ansi"},
{"DIRECTORY",	OPT_STR|OPT_ADV,	22, "look in <s> for templates", NULL, ""},
{NULL}
};

char *params[MAX_PARAM + 2];
#else
extern option_t options[];
extern char *params[];
extern char *szTableNames[];
#endif
#endif
