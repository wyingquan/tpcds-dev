/*
* $Id: QgenMain.c,v 1.14 2007/11/21 18:50:46 jms Exp $
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
* $Log: QgenMain.c,v $
* Revision 1.14  2007/11/21 18:50:46  jms
* 32/64 issues in qgen
*
* Revision 1.13  2007/05/23 18:11:58  jms
* TPCDS Bug 546
*
* Revision 1.12  2006/08/18 20:35:40  jms
* Bug reported by IBM: don't add in a -directory setting by default, but only when the option is explcitly set from the command line
*
* Revision 1.11  2006/05/12 18:09:29  jms
* add '-directory' option to qgen
*
* Revision 1.10  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.9  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.8  2006/01/07 00:47:21  jms
* add MALLOC_CHECK calls; check include_file return code
*
* Revision 1.7  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.6  2005/10/17 17:58:41  jms
* first cut at allowing multi-part substitutions in DEFINE statements
*
* Revision 1.5  2005/10/03 18:55:53  jms
* add logging of query parameters
* add qualify option remove query permutation
* add filter option to aid debug
*
* Revision 1.4  2005/02/15 22:57:22  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.3  2004/12/02 17:45:38  jms
* Bug #126: qgen core dumps on some templates
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:02  jms
* re-establish external server
*
* Revision 1.14  2004/10/14 17:52:50  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.13  2004/10/14 16:24:15  jms
* porting changes for w/s segregation
*
* Revision 1.12  2004/09/29 19:25:37  jms
* declare yydebug for hpux
*
* Revision 1.11  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.10  2004/09/24 20:01:26  jms
* Bug #97: ability to generate from a single template
*
* Revision 1.9  2004/09/11 18:39:19  jms
* add BEGIN/END markers to queries as temporary fix to comment passthrough
*
* Revision 1.8  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.7  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.6  2004/08/27 18:56:06  jms
* allow comments in query list
*
* Revision 1.5  2004/08/25 23:51:35  jms
* port to LINUX
*
* Revision 1.4  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.3  2004/05/03 22:38:46  jms
* add RNG_SEED argument to init_rand calls
*
* Revision 1.2  2004/02/28 22:49:52  jms
* simplify qgen command line and processing
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.6  2003/07/15 00:43:46  jms
* Porting changes for Linux
*
* Revision 1.5  2003/06/24 19:40:52  jms
* Allow query/stream/template number to occur in query templates
*
* Revision 1.4  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.3  2003/04/21 19:14:57  jms
* bug 9: lex changes for MP/RAS
*
* Revision 1.2  2003/04/16 00:21:44  jms
* data set alignment
*
* Revision 1.1  2003/03/21 19:56:45  jms
* resync with code on laptap
*
*/
#define DECLARER
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include "StringBuffer.h"
#include "expr.h"
#include "grammar_support.h"
#include "keywords.h"
#include "substitution.h"
#include "error_msg.h"
#include "qgen_params.h"
#include "genrand.h"
#include "query_handler.h"
#include "release.h"
#include "list.h"
#include "permute.h"
#include "dist.h"
#include "tdef_functions.h"

template_t *pCurrentQuery,
	*g_Template;
list_t *TemplateList;


int g_nQueryNumber, 
	g_nStreamNumber;
StringBuffer_t *g_sbTemplateName = NULL;


int yydebug;
int yyparse(void);
extern FILE *yyin;
extern 	file_ref_t *pCurrentFile;
table_func_t w_tdef_funcs[MAX_TABLE];

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
parseTemplate(char *szFileName, int nIndex)
{
	int nWarning,
		nError;
	char szPath[1024];
			
		pCurrentQuery = (template_t *)malloc(sizeof(struct TEMPLATE_T));
		MALLOC_CHECK(pCurrentQuery);
		if (!pCurrentQuery)
			ReportErrorNoLine(QERR_NO_MEMORY, "parseQueries()", 1);
		memset(pCurrentQuery, 0, sizeof(struct TEMPLATE_T));
		pCurrentQuery->SegmentList = makeList(L_FL_TAIL, NULL);
		pCurrentQuery->SubstitutionList = makeList(L_FL_SORT, compareSubstitution);	
		pCurrentQuery->DistributionList = makeList(L_FL_SORT, di_compare);

		/*
		 * each query template is parsed as though:
		 *	it had explicitly included the dialect template
		 *	it began the query with a [_begin] substitution
		 *	it ended the query with an [_end] substitution
		 */
		pCurrentFile = NULL;
      if (is_set("DIRECTORY"))
		   sprintf(szPath, "%s/%s", get_str("DIRECTORY"),szFileName);
      else
         strcpy(szPath, szFileName);
		if (include_file(szPath, pCurrentQuery) < 0)
			ReportErrorNoLine(QERR_NO_FILE, szPath, 1);
		sprintf(szPath, "%s/%s.tpl", get_str("DIRECTORY"), get_str("DIALECT"));
		if (include_file(szPath, pCurrentQuery) < 0)
			ReportErrorNoLine(QERR_NO_FILE, szPath, 1);
	
		/* parse the template file */
		yyparse();

		/* 
		 * add in query start substitution, now that it has been defined 
		 */
		pCurrentQuery->SegmentList->nFlags &= ~L_FL_TAIL;
		pCurrentQuery->SegmentList->nFlags |= L_FL_HEAD;
		AddQuerySegment(pCurrentQuery, "\n");
		AddQuerySegment(pCurrentQuery, "");
		((segment_t *)pCurrentQuery->SegmentList->head->pData)->pSubstitution = findSubstitution(pCurrentQuery, "_BEGIN", 0);
		pCurrentQuery->SegmentList->nFlags &= ~L_FL_HEAD;
		pCurrentQuery->SegmentList->nFlags |= L_FL_TAIL;
		
		/* check for any parsing errors */
		GetErrorCounts(&nError, &nWarning);
		if (nError)
		{
			printf("%d Errors encountered parsing %s\n", 
				nError, szFileName);
			exit(1);
		}
		if (nWarning)
		{
			printf("WARRNING: %d warnings encountered parsing %s\nWARNING: Query output may not be correct!\n", 
				nWarning, szFileName);
		}
		
		addList(TemplateList, pCurrentQuery);
		pCurrentQuery->index = nIndex;
		pCurrentQuery->name = strdup(szFileName);

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
void
parseQueries(void)
{
	char szFileName[1024],
		*cp;
	FILE *pInputFile;
	int nIndex = 1;
	
	if (!is_set("INPUT"))
	{
		ReportErrorNoLine(QERR_NO_QUERYLIST, NULL, 1);
	}

	strcpy(szFileName, get_str("INPUT"));
	
#ifndef WIN32
	if ((pInputFile = fopen(szFileName, "r")) == NULL)
#else
	if ((pInputFile = fopen(szFileName, "rt")) == NULL)
#endif
	{
		SetErrorGlobals(szFileName, NULL);
		ReportErrorNoLine(QERR_OPEN_FAILED, szFileName, 1);
	}
	
	while (fgets(szFileName, 1024, pInputFile))
	{
		if (strncmp(szFileName, "--", 2) == 0)
			continue;
		if ((cp = strchr(szFileName, '\n')))
			*cp = '\0';
		if (!strlen(szFileName))
			continue;
			
		parseTemplate(szFileName, nIndex++);
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
void
generateQueryStreams(void)
{
	int nStream,
		nQuery,
		nQueryCount,
		*pPermutation = NULL,
		nVersionCount,
		nCount,
		nQID;
	FILE *pOutFile;
	FILE *pLogFile = NULL;
	char szPath[1024];

	nQueryCount = length(TemplateList);
	nVersionCount = get_int("COUNT");
	
	if (is_set("LOG"))
	{
#ifndef WIN32
		if ((pLogFile = fopen(get_str("LOG"), "w")) == NULL)
#else
		if ((pLogFile = fopen(get_str("LOG"), "wt")) == NULL)
#endif
		{
			SetErrorGlobals(get_str("LOG"), NULL);
			ReportErrorNoLine(QERR_OPEN_FAILED, get_str("LOG"), 1);
		}
	}

	for (nStream=0; nStream < get_int("STREAMS"); nStream++)
	{
		pPermutation = makePermutation(pPermutation, nQueryCount, 0);
	
		sprintf(szPath, "%s%squery_%d.sql",
			get_str("OUTPUT_DIR"),
			get_str("PATH_SEP"),
			nStream);
		if (!is_set("FILTER"))
		{
#ifndef WIN32
			if ((pOutFile = fopen(szPath, "w")) == NULL)
#else
				if ((pOutFile = fopen(szPath, "wt")) == NULL)
#endif
				{
					SetErrorGlobals(szPath, NULL);
					ReportErrorNoLine(QERR_OPEN_FAILED, szPath, 1);
				}
		}
		else
			pOutFile = stdout;

		g_nStreamNumber = nStream;
		if (pLogFile)
			fprintf(pLogFile, "BEGIN STREAM %d\n", nStream);
		for (nQuery = 1; nQuery <= nQueryCount; nQuery++)
		{
			for (nCount = 1; nCount <= nVersionCount; nCount++)
			{
			g_nQueryNumber = nQuery;
			if (is_set("QUALIFY"))
				nQID = nQuery;
			else
				nQID = getPermutationEntry(pPermutation, nQuery);
			GenerateQuery(pOutFile, pLogFile, nQID);
			if (pLogFile)
				fprintf(pLogFile, "\n");
			}
		}
		if (pLogFile)
			fprintf(pLogFile, "END STREAM %d\n", nStream);

		if (!is_set("FILTER"))
			fclose(pOutFile);
	}

	if (pLogFile)
		fclose(pLogFile);

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
main(int ac, char* av[])
{
	template_t *pTemplate;

	process_options (ac, av);

	if (!is_set("QUIET"))
	{
		fprintf (stderr,
		"%s Query Generator (Version %d.%d.%d%s)\n",
		get_str("PROG"), VERSION, RELEASE, MODIFICATION, PATCH);
	fprintf (stderr, "Copyright %s %s\n", COPYRIGHT, C_DATES);
	}

	TemplateList = makeList(L_FL_TAIL, NULL);

	/* sync the keyword defines between lex/yacc/qgen */
	InitKeywords();
	
	if (is_set("YYDEBUG"))
		yydebug = 1;
	

	if (is_set("TEMPLATE"))
      parseTemplate(get_str("TEMPLATE"), 1);
	else
		parseQueries();	/* load the query templates */
	
	
	if (is_set("VERBOSE") && !is_set("QUIET"))
		fprintf(stderr, "Parsed %d templates\n", length(TemplateList));
	if (is_set("DUMP"))
	{
		for (pTemplate = (template_t *)getHead(TemplateList); pTemplate; pTemplate = (template_t *)getNext(TemplateList))
			PrintTemplate(pTemplate);
	}

	init_rand();

	generateQueryStreams();	/* output the resulting SQL */

	exit(0);

}
		

