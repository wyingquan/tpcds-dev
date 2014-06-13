/*
* $Id: grammar_support.c,v 1.6 2006/05/10 22:03:22 jms Exp $
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
* $Log: grammar_support.c,v $
* Revision 1.6  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.5  2006/02/10 00:14:15  jms
* lurking include file fix on linux box
*
* Revision 1.4  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.3  2005/02/15 22:58:35  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.3  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.2  2004/02/28 22:44:59  jms
* remove workload and query classes
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.4  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.3  2003/04/21 19:14:57  jms
* bug 9: lex changes for MP/RAS
*
* Revision 1.2  2003/03/21 21:33:00  jms
* compile under linux
*
* Revision 1.1  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*
*/

#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef USE_STRINGS_H
#include <strings.h>
#else
#include <string.h>
#endif

#include "StringBuffer.h"
#include "expr.h"
#include "grammar_support.h"
#include "keywords.h"
#include "error_msg.h"
#include "qgen_params.h"
#include "substitution.h"

extern char yytext[];
extern FILE *yyin;
file_ref_t *pCurrentFile = NULL;
file_ref_t CurrentFile;

extern template_t *pCurrentQuery;
static int nErrcnt = 0;
static int nWarncnt = 0;
/* 
 * different scanner handle yywrap differently
 */

#ifdef MKS
void *yySaveScan(FILE *fp);
int yyRestoreScan(void *pState);
#endif
#ifdef FLEX
/* flex has a slightly different way of handling yywrap. See O'Reilly, p. 155 */
void *yy_create_buffer( FILE *file, int size );
void yy_switch_to_buffer( void *new_buffer );
void yy_delete_buffer( void *b );
#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE 16384
#endif
#endif

/*
 * Routine:  include_file()
 * Purpose: handle #include<> statements
 * Algorithm:
 * Data Structures:
 *
 * Params: char *path, int switch_to (unused?)
 * Returns: 0 on success, -1 on open failure, -2 on malloc failure
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 
 */
int 
include_file(char *fn, void *pC)
{
    FILE *fp;
	file_ref_t *pFileRef;
	template_t *pContext = (template_t *)pC;

    if (fn == NULL)
		return(0);

	if ((fp = fopen(fn, "r")) == NULL)
    	return(-1);
	
	pFileRef = (file_ref_t *)malloc(sizeof(struct FILE_REF_T));
	MALLOC_CHECK(pFileRef);
	if (pFileRef == NULL)
		ReportError(QERR_NO_MEMORY, "include_file()", 1);
	memset(pFileRef, 0, sizeof(struct FILE_REF_T));
	
	pFileRef->name = strdup(fn);
    pFileRef->file = fp;
	pFileRef->line_number = 1;
	pFileRef->pContext = pContext;
	if (pContext)
		pContext->name = strdup(fn);
	pFileRef->pNext = pCurrentFile;
	pCurrentFile = pFileRef;
	SetErrorGlobals(fn, &pFileRef->line_number);

#ifdef MKS
	pCurrentFile->pLexState = (void *)yySaveScan(pCurrentFile->file);
#endif
#ifdef FLEX
	pCurrentFile->pLexState = yy_create_buffer(pFileRef->file, YY_BUF_SIZE);
	yy_switch_to_buffer(pCurrentFile->pLexState);
#endif
#if !defined(MKS) && !defined(FLEX)
	yyin = pCurrentFile->file;
#endif

	if (is_set("DEBUG"))
		printf("STATUS: INCLUDE(%s)\n", fn);

    return(0);
}

/*
 * Routine: yyerror()
 * Purpose: standard error message interface
 * Algorithm:
 * Data Structures:
 *
 * Params: (char *) error message
 * Returns: 0 until 10 errors encountered, then exits
 * Called By: grammar, assorted support routines
 * Calls: None
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
void 
yyerror(char *msg, ...)
{

	printf("ERROR: %s at line %d in file %s\n",
        msg, pCurrentFile->line_number, pCurrentFile->name);
    if (++nErrcnt == 10)
    	{
    	printf("Too many errors. Exiting.\n");
    	exit(1);
    	}
    return;
}    


/*
 * Routine: yywarn()
 * Purpose: standard error message interface
 * Algorithm:
 * Data Structures:
 *
 * Params: (char *) error message
 * Returns: 0 until 10 errors encountered, then exits
 * Called By: grammar, assorted support routines
 * Calls: None
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
#ifndef SCANNER_TEST
int 
yywarn(char *str)
{
	fprintf(stderr, "warning: %s in line %d of file %s\n", 
		str, pCurrentFile->line_number, pCurrentFile->name);
	nWarncnt += 1;

    return(0);
}
#endif

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
* TODO: 
*/
void 
GetErrorCounts(int *nError, int *nWarning)
{
	*nError = nErrcnt;
	*nWarning = nWarncnt;

	return;
}
