/*
* $Id: error_msg.c,v 1.10 2007/11/27 00:18:50 jms Exp $
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
* $Log: error_msg.c,v $
* Revision 1.10  2007/11/27 00:18:50  jms
* bug 576
*
* Revision 1.9  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.8  2006/08/17 19:40:05  jms
* Coversion of VisualStudio 2005
*
* Revision 1.7  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.6  2006/01/16 23:13:44  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.5  2006/01/16 23:10:37  jms
* bug 369
*
* Revision 1.4  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.3  2006/01/07 00:46:03  jms
* add location indicator to no memory error
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:37  jms
* re-establish external server
*
* Revision 1.8  2004/09/11 22:10:40  jms
* add more space for error messages
*
* Revision 1.7  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.6  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.5  2004/08/20 19:41:57  jms
* changes from August F-2-F
*
* Revision 1.4  2004/07/14 23:50:23  jms
* Generate dbgen_version table
*
* Revision 1.3  2004/06/03 16:02:31  jms
* Bug #75: catalog_returns not recognized
*
* Revision 1.2  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.8  2003/07/15 18:05:20  jms
* separate ERRORs from Warnings
*
* Revision 1.7  2003/06/24 19:47:33  jms
* isolate scaling functions and allow scaling by GB (bug 34)
*
* Revision 1.6  2003/06/06 19:23:38  jms
* Closure of bug 29: TEXT() substitutions don't work
*
* Revision 1.5  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.4  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.3  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.2  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.1  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "error_msg.h"
#include "grammar_support.h"
static int *LN;
static char *FN;

err_msg_t Errors[MAX_ERROR + 2] = {
	{EFLG_NO_ARG, "", },
	{EFLG_STR_ARG, "File '%s' not found"},
	{EFLG_NO_ARG, "Line exceeds maximum length"},
	{EFLG_STR_ARG, "Memory allocation failed %s"},
	{EFLG_STR_ARG, "Syntax Error: \n'%s'"},
	{EFLG_NO_ARG, "Invalid/Out-of-range Argument"},
	{EFLG_STR_ARG, "'%s' is not a unique name"},
	{EFLG_STR_ARG, "'%s' is not a valid name"},
	{EFLG_NO_ARG, "Command parse failed"},
	{EFLG_NO_ARG, "Invalid tag found"},
	{EFLG_STR_ARG, "Read failed on '%s'"},
	{EFLG_NO_ARG, "Too Many Templates!"},
	{EFLG_NO_ARG, "Each workload definition must be in its own file"},
	{EFLG_NO_ARG, "Query Class name must be unique within a workload definition"},
	{EFLG_NO_ARG, "Query Template must be unique within a query class"},
	{EFLG_STR_ARG|EFLG_SYSTEM, "Open failed on '%s'"},
	{EFLG_STR_ARG, "%s  not yet implemented"},										/* QERR_NOT_IMPLEMENTED */
	{EFLG_STR_ARG, "string trucated to '%s'"},
	{EFLG_NO_ARG, "Non-terminated string"},
	{EFLG_STR_ARG, "failed to write to '%s'"},
	{EFLG_NO_ARG, "No type vector defined for distribution"},
	{EFLG_NO_ARG, "No weight count defined for distribution"},
	{EFLG_NO_ARG, "No limits defined for pricing calculations"},
	{EFLG_STR_ARG, "Percentage is out of bounds in substitution '%s'"},
	{EFLG_STR_ARG, "Name is not a distribution or table name: '%s'"},
	{EFLG_NO_ARG, "Cannot evaluate expression"},
	{EFLG_STR_ARG, "Substitution'%s' is used before being initialized"}, /* QERR_NO_INIT */
	{EFLG_NO_ARG, "RANGE()/LIST() not supported for NORMAL distributions"},
	{EFLG_STR_ARG, "Bad Nesting; '%s' not found"},
	{EFLG_STR_ARG, "Include stack overflow when opening '%s'"},
	{EFLG_STR_ARG, "Bad function call: '%s'"},
	{EFLG_STR_ARG, "Bad Hierarchy Call: '%s'"},
	{EFLG_NO_ARG, "Must set types and weights before defining names"},
	{EFLG_NO_ARG, "More than 20 arguments in definition"},
	{EFLG_NO_ARG, "Argument type mismatch"},
	{EFLG_NO_ARG, "RANGE() and LIST() cannot be used in the same expression"},		/* QERR_RANGE_LIST */
	{EFLG_NO_ARG, "Selected volume is NOT valid for result publication"},
	{EFLG_STR_ARG, "Parameter setting failed for '%s'"},
	{EFLG_STR_ARG, "Table %s is being joined without an explicit rule"},
	{EFLG_STR_ARG, "Table %s is not yet fully defined"},
	{EFLG_STR_ARG, "Table %s is a child; it is populated during the build of its parent (e.g., catalog_sales builds catalog returns)"},
	{EFLG_NO_ARG, "Command line arguments for dbgen_version exceed 200 characters; truncated"},
	{EFLG_NO_ARG, "A query template list must be supplied using the INPUT option"},	/* QERR_NO_QUERYLIST */
	{EFLG_NO_ARG, "Invalid query number found in permutation!"},					/* QERR_QUERY_RANGE */
	{EFLG_NO_ARG, "RANGE/LIST expressions not valid as function parameters"},		/* QERR_MODIFIED_PARAM */
	{EFLG_NO_ARG, "RANGE/LIST truncated to available values"},						/* QERR_MODIFIED_PARAM */
	{EFLG_NO_ARG, "This scale factor is valid for QUALIFICATION ONLY"},				/* QERR_QUALIFICATION_SCALE */
	{EFLG_STR_ARG, "Generating %s requires the '-update' option"},		/* QERR_TABLE_UPDATE */
	{0, NULL}
};

/*
 * Routine: 
 * Purpose: 
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
void
ProcessErrorCode (int nErrorCode, char *szRoutineName, char *szParam,
                  int nParam)
{
   switch (nErrorCode)
     {
     case QERR_NO_FILE:
        ReportError (QERR_NO_FILE, szParam, 1);
        break;
     case QERR_SYNTAX:
     case QERR_RANGE_ERROR:
     case QERR_NON_UNIQUE:
     case QERR_BAD_NAME:
     case QERR_DEFINE_OVERFLOW:
     case QERR_INVALID_TAG:
     case QERR_READ_FAILED:
     case QERR_NO_MEMORY:
     case QERR_LINE_TOO_LONG:
        ReportError (nErrorCode, szRoutineName, 1);
        break;
     }
   return;
}

/*
 * Routine: 
 * Purpose: 
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
int
ReportError (int nError, char *msg, int bExit)
{
   char e_msg[128];

   if (nError < MAX_ERROR)
     {
        switch (Errors[-nError].flags & EFLG_ARG_MASK)
          {
          case EFLG_NO_ARG:
             fprintf (stderr, "ERROR: %s at line %d in %s\n",
                      Errors[-nError].prompt, pCurrentFile->line_number, pCurrentFile->name);
             break;
          case EFLG_STR_ARG:
             sprintf (e_msg, Errors[-nError].prompt, msg);
             fprintf (stderr, "ERROR: %s at line %d in %s\n",
                      e_msg, pCurrentFile->line_number, pCurrentFile->name);
             break;
          }

        if (Errors[-nError].flags & EFLG_SYSTEM)
           perror (msg);
     }

   if (bExit)
      exit (nError);
   else
      return (nError);
}

/*
 * Routine: 
 * Purpose: 
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
int
ReportErrorNoLine (int nError, char *msg, int bExit)
{
   char e_msg[1024];

   if (nError < MAX_ERROR)
     {
        switch (Errors[-nError].flags & EFLG_ARG_MASK)
          {
          case EFLG_NO_ARG:
			  fprintf (stderr, "%s: %s\n", (bExit)?"ERROR":"Warning", Errors[-nError].prompt);
             break;
          case EFLG_STR_ARG:
             sprintf (e_msg, Errors[-nError].prompt, msg);
             fprintf (stderr, "%s: %s\n", (bExit)?"ERROR":"Warning", e_msg);
             break;
          }

        if (Errors[-nError].flags & EFLG_SYSTEM)
           perror (msg);
     }

   if (bExit)
      exit (nError);
   else
      return (nError);
}

/*
 * Routine: 
 * Purpose: 
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
void
SetErrorGlobals (char *szFileName, int *nLineNumber)
{
	FN = szFileName;
	LN = nLineNumber;

	return;
}
