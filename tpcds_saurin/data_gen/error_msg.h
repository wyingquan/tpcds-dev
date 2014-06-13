/*
* $Id: error_msg.h,v 1.5 2007/11/27 00:18:50 jms Exp $
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
* $Log: error_msg.h,v $
* Revision 1.5  2007/11/27 00:18:50  jms
* bug 576
*
* Revision 1.4  2006/08/17 19:40:05  jms
* Coversion of VisualStudio 2005
*
* Revision 1.3  2006/01/16 23:13:44  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:37  jms
* re-establish external server
*
* Revision 1.9  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.8  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.7  2004/07/14 23:50:23  jms
* Generate dbgen_version table
*
* Revision 1.6  2004/06/03 16:02:31  jms
* Bug #75: catalog_returns not recognized
*
* Revision 1.5  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.10  2003/06/24 19:47:33  jms
* isolate scaling functions and allow scaling by GB (bug 34)
*
* Revision 1.9  2003/06/06 19:23:38  jms
* Closure of bug 29: TEXT() substitutions don't work
*
* Revision 1.8  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.7  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.6  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.5  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.4  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.3  2002/11/20 00:51:33  jms
* QGEN2 corrections
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/18 23:52:25  jms
* add limit error message
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#define QERR_OK				0
#define QERR_NO_FILE		-1
#define QERR_LINE_TOO_LONG	-2
#define QERR_NO_MEMORY		-3
#define QERR_SYNTAX			-4
#define QERR_RANGE_ERROR	-5
#define QERR_NON_UNIQUE		-6
#define QERR_BAD_NAME		-7
#define QERR_DEFINE_OVERFLOW	-8
#define QERR_INVALID_TAG	-9
#define QERR_READ_FAILED	-10
#define QERR_TEMPLATE_OVERFLOW	-11
#define QERR_ONE_WORKLOAD	-12
#define QERR_CLASS_REDEFINE	-13
#define QERR_DUP_QUERY		-14
#define QERR_OPEN_FAILED	-15
#define QERR_NOT_IMPLEMENTED	-16
#define QERR_STR_TRUNCATED	-17
#define QERR_BAD_STRING	-18
#define QERR_WRITE_FAILED	-19
#define QERR_NO_TYPE	-20
#define QERR_NO_WEIGHT	-21
#define QERR_NO_LIMIT	-22
#define QERR_BAD_PERCENT	-23
#define QERR_ROWCOUNT_NAME	-24
#define QERR_NO_EXPR		-25
#define QERR_NO_INIT		-26
#define QERR_NO_NORMAL_RANGE -27
#define QERR_UNBALANCED		-28
#define QERR_INCLUDE_OVERFLOW	-29
#define QERR_BAD_PARAMS		-30
#define DBGEN_ERROR_HIERACHY_ORDER	-31
#define QERR_NAMES_EARLY	-32
#define QERR_ARG_OVERFLOW	-33
#define QERR_INVALID_ARG	-34
#define QERR_RANGE_LIST		-35
#define QERR_BAD_SCALE		-36
#define QERR_BAD_PARAM		-37
#define QERR_BAD_JOIN		-38
#define QERR_TABLE_NOP		-39
#define QERR_TABLE_CHILD	-40
#define QERR_CMDLINE_TOO_LONG	-41
#define QERR_NO_QUERYLIST	-42
#define QERR_QUERY_RANGE	-43
#define QERR_MODIFIED_PARAM	-44
#define QERR_RANGE_OVERRUN	-45
#define QERR_QUALIFICATION_SCALE -46
#define QERR_TABLE_UPDATE -47
#define MAX_ERROR			47

typedef struct ERR_MSG_T {
	int flags;
	char *prompt;
} err_msg_t;

/*  Flag determine formating */
#define EFLG_NO_ARG		0x0000
#define EFLG_STR_ARG	0x0001
#define EFLG_ARG_MASK	0x0001

#define EFLG_SYSTEM		0x0002



int ReportError(int nError, char *arg, int bExit);
int ReportErrorNoLine(int nError, char *arg, int bExit);
void SetErrorGlobals(char *szFileName, int *pnLineNumber);
