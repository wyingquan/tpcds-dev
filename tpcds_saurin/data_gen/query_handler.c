/*
* $Id: query_handler.c,v 1.11 2007/11/21 19:29:16 jms Exp $
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
* $Log: query_handler.c,v $
* Revision 1.11  2007/11/21 19:29:16  jms
* Bug 575
*
* Revision 1.10  2007/11/21 18:48:42  jms
* 32/64 issue in parameter logging
*
* Revision 1.9  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.8  2006/02/13 22:07:08  jms
* fix sparsely populated list() handling
*
* Revision 1.7  2006/01/08 23:36:44  jms
* add additional debug to query generation
*
* Revision 1.6  2006/01/07 00:46:35  jms
* add MALLOC_CHECK calls
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
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:02  jms
* re-establish external server
*
* Revision 1.10  2004/09/29 18:30:52  jms
* resolve LIST() bug and standardize argument numbering
*
* Revision 1.9  2004/09/29 01:20:57  jms
* Fixes from review with Meikel:
*  -- add arithmetic expressions and SCALE
*  -- fix LIST/RANGE overrun
*
* Revision 1.8  2004/09/27 20:07:49  jms
* cleanup of recursive eval calls to handle nested substitution in decl section
*
* Revision 1.7  2004/09/10 21:15:32  jms
* correct handling of list() values
* unify flags on expr_t and substitution_t
*
* Revision 1.6  2004/09/10 20:15:16  jms
* reset substitution value buffers between query streams
*
* Revision 1.5  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.4  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.3  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.2  2004/02/28 22:49:52  jms
* simplify qgen command line and processing
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.6  2003/06/10 03:35:18  jms
* Rework of back-to-back substitution in a query or a query that starts with a substitution and not with SQL
*
* Revision 1.5  2003/06/06 19:25:18  jms
* Closure of bug 22: Need query termination
*
* Revision 1.4  2003/04/23 23:43:04  jms
* malloc issues under LINUX
*
* Revision 1.3  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.2  2003/03/21 21:33:01  jms
* compile under linux
*
* Revision 1.1  2003/03/21 19:56:45  jms
* resync with code on laptap
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include "StringBuffer.h"
#include "eval.h"
#include "substitution.h"
#include "error_msg.h"
#include "qgen_params.h"
#include "genrand.h"
#include "r_params.h"

extern list_t *TemplateList;
extern StringBuffer_t *g_sbTemplateName;
extern int g_nQueryNumber, g_nStreamNumber;
extern option_t *Options;

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
substitution_t *
defineSubstitution(template_t *pQuery, char *szSubstitutionName, expr_t *pDefinition)
{
	substitution_t *pSub;

	pSub = (substitution_t *)malloc(sizeof(struct SUBSTITUTION_T));
	MALLOC_CHECK(pSub);
	if (pSub == NULL)
		return(NULL);
	memset(pSub, 0, sizeof(struct SUBSTITUTION_T));
	pSub->name = szSubstitutionName;
	pSub->pAssignment = pDefinition;
	pSub->nSubParts = pDefinition->nValueCount;
	addList(pQuery->SubstitutionList, (void *)pSub);

	return(pSub);
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
AddQuerySegment(template_t *pQuery, char *szText)
{
	segment_t *pSegment;

	pSegment = (segment_t *)malloc(sizeof(struct SEGMENT_T));
	MALLOC_CHECK(pSegment);
	if (pSegment == NULL)
		return(-1);
	memset(pSegment, 0, sizeof(struct SEGMENT_T));
	pSegment->text = szText;
	addList(pQuery->SegmentList, (void *)pSegment);

	return(0);
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
Expr_Val_t *
findValue(segment_t *pSegment)
{
	Expr_Val_t *pReturnValue;
	substitution_t *pSub;


	pSub = pSegment->pSubstitution;
	pReturnValue = pSub->arValues;

	pReturnValue += pSub->nSubParts * pSegment->nSubCount;
	pReturnValue += pSegment->nSubUse;

	return(pReturnValue);

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
void PrintTemplate(template_t *t)
{
	substitution_t *pSubstitution;
	segment_t *pSegment;
	
	for (pSubstitution = (substitution_t *)getHead(t->SubstitutionList);
		pSubstitution;
		pSubstitution = (substitution_t *)getNext(t->SubstitutionList))
	{
		printf("DEFINE %s = ", pSubstitution->name);
		PrintExpr(pSubstitution->pAssignment);
		printf(";\n");

	}

	printf("\n\n");

	for (pSegment = (segment_t *)getHead(t->SegmentList); pSegment; pSegment = (segment_t *)getNext(t->SegmentList))
	{
		printf("%s", pSegment->text);
		if (pSegment->pSubstitution)
		{
			printf("[%s]", pSegment->pSubstitution->name);
		}
		printf(" ");
	}

	printf(";\n");

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
void GenerateQuery(FILE *pOutFile, FILE *pLogFile, int nQuery)
{
	int i,
		nBufferCount;
	substitution_t *pSub;
	segment_t *pSegment;
	Expr_Val_t *pValue;
	static int nQueryCount = 1;

	if (pOutFile == NULL)
		pOutFile = stdout;

	/* get the template */
	pCurrentQuery = getItem(TemplateList, nQuery);
	if (!pCurrentQuery)
		ReportError(QERR_QUERY_RANGE, NULL, 1);

	if (g_sbTemplateName == NULL)
	{
		g_sbTemplateName = InitBuffer(20, 10);
	}
	ResetBuffer(g_sbTemplateName);
	AddBuffer(g_sbTemplateName, pCurrentQuery->name);
	if (pLogFile)
		fprintf(pLogFile, "Template: %s\n", pCurrentQuery->name);
	if (is_set("DEBUG"))
		printf("STATUS: Generating Template: %s\n", pCurrentQuery->name);

	/* initialize the template if required */
	if (!(pCurrentQuery->flags & QT_INIT))
	{
		for (pSub = (substitution_t *)getHead(pCurrentQuery->SubstitutionList); 
		pSub; 
		pSub = (substitution_t *)getNext(pCurrentQuery->SubstitutionList))
		{
			nBufferCount = ((pSub->nUse)?pSub->nUse:1) * ((pSub->nSubParts)?pSub->nSubParts:1);
			pSub->arValues = (Expr_Val_t *)malloc(nBufferCount * sizeof(struct EXPR_VAL_T));
			MALLOC_CHECK(pSub->arValues);
			for (i=0; i < nBufferCount; i++)
			{
				memset(&pSub->arValues[i], 0, sizeof(struct EXPR_VAL_T));
#ifdef MEM_TEST
	fprintf(stderr, "pSub arValues %d: %x\n", i, &pSub->arValues[i]);
#endif
				pSub->arValues[i].pBuf = InitBuffer(15, 15);
			}
		}
		pCurrentQuery->flags |= QT_INIT;
	}
	
	/* select the values for this query */
	for (pSub = (substitution_t *)getHead(pCurrentQuery->SubstitutionList); 
	pSub; 
	pSub = (substitution_t *)getNext(pCurrentQuery->SubstitutionList))
	{
		nBufferCount = ((pSub->nUse)?pSub->nUse:1) * ((pSub->nSubParts)?pSub->nSubParts:1);
		for (i=0; i < nBufferCount; i++)
		{
			ResetBuffer(pSub->arValues[i].pBuf);
		}
#ifdef MEM_TEST
	if (pSub->pAssignment->Value.pBuf == NULL) fprintf(stderr, "NULL pBuf %x @ %d\n", pSub->pAssignment, __LINE__);
#endif
		pSub->nDataType = EvalExpr(pSub->pAssignment, pSub->arValues, 0, nQueryCount);
		if (pLogFile)
		{
			for (i=0; i < nBufferCount; i++)
			{
				fprintf(pLogFile, "\t%s.%02d = ", pSub->name, i+1);
			if (!pSub->arValues[i].bUseInt)
				fprintf(pLogFile, "%s\n", GetBuffer(pSub->arValues[i].pBuf));
			else
            {
				fprintf(pLogFile, HUGE_FORMAT, pSub->arValues[i].nValue);
				fprintf(pLogFile, "\n");
            }
			}
		}

	}
	
	/* output the query */
	for (pSegment = (segment_t *)getHead(pCurrentQuery->SegmentList); 
	pSegment; 
	pSegment = (segment_t *)getNext(pCurrentQuery->SegmentList))
	{
		if (pSegment->text)
			fprintf(pOutFile, "%s", pSegment->text);
		if (pSegment->pSubstitution)
		{
			pValue = findValue(pSegment);
         if (!pValue->bUseInt)
				fprintf(pOutFile, "%s", GetBuffer(pValue->pBuf));
			else
            {
				fprintf(pOutFile, HUGE_FORMAT, pValue->nValue);
            }
		}
		if (pSegment->flags & QS_EOS)
			fprintf(pOutFile, ";\n");
	}
	
	nQueryCount += 1;

	
	return;
}

