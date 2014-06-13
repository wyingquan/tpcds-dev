/*
* $Id: keywords.c,v 1.9 2006/02/10 00:12:55 jms Exp $
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
* $Log: keywords.c,v $
* Revision 1.9  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.8  2006/01/16 23:10:37  jms
* bug 369
*
* Revision 1.7  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.6  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.5  2005/02/15 22:54:45  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.4  2004/12/03 19:23:03  jms
* bug #130: stings.h --> strings.h
*
* Revision 1.3  2004/12/02 19:12:57  jms
* include KW_DECIMAL to allow distributions to be parsed by the grammar
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.4  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.3  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.2  2004/02/28 22:44:29  jms
* avoid id conflicts with move to bison/flex on windows
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2003/06/24 19:40:52  jms
* Allow query/stream/template number to occur in query templates
*
* Revision 1.2  2003/04/23 19:00:27  jms
* add keyword output for lex debug
*
* Revision 1.1  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include "keywords.h"
#include "StringBuffer.h"
#include "expr.h"
#include "y.tab.h"
#include "substitution.h"
#include "error_msg.h"
#include "query_handler.h"

extern template_t *g_Template;

/* NOTE: current code requires WORKLOAD to be first entry */
static keyword_t KeyWords[] =
{
	{"ID", 0, 0},
	{"SQL", 0, 0},
	{"DEFINE", 0, 0},
	{"RANDOM", 0, 0},
	{"UNIFORM", 0, 0},
	{"RANGE", 0, 0},
	{"DATE", 0, 0},
	{"INCLUDE", 0, 0},
	{"TEXT", 0, 0},
	{"DIST", 0, 0},
	{"LIST", 0, 0},
	{"ROWCOUNT", 0, 0},
	{"BEGIN", 0, 0},
	{"END", 0, 0},
	{"SALES", 0, 0},
	{"RETURNS", 0, 0},
	{"DISTMEMBER", 0, 0},
   {"DISTWEIGHT", 0, 0},
	{"_QUERY", EXPR_FL_INT, 0},
	{"_STREAM", EXPR_FL_INT, 0},
	{"_TEMPLATE", EXPR_FL_CHAR, 0},
	{"SCALE", 0, 0},
   {"SCALESTEP", 0, 0},
	{"SET", 0, 0},
	{"ADD", 0, 0},
	{"NAMES", 0, 0},
	{"TYPES", 0, 0},
	{"WEIGHTS", 0, 0},
	{"INT", 0, 0},
	{"VARCHAR", 0, 0},
	{"DECIMAL", 0, 0},
	{"_LIMIT", EXPR_FL_INT, 0},
	{"_LIMITA", EXPR_FL_INT, 0},
	{"_LIMITB", EXPR_FL_INT, 0},
	{"_LIMITC", EXPR_FL_INT, 0},
	{NULL, 0}
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
void InitKeywords()
{
	int nIndex = TOK_ID;
	keyword_t *pKW;
	expr_t *pExpr;
	
	g_Template = (template_t *)malloc(sizeof(struct TEMPLATE_T));
	MALLOC_CHECK(g_Template);
	if (!g_Template)
		ReportError(QERR_NO_MEMORY, "InitKeywords()", 1);
	memset(g_Template, 0, sizeof(struct TEMPLATE_T));
	g_Template->SubstitutionList = makeList(L_FL_SORT, compareSubstitution);	
	
	for (pKW = &KeyWords[0]; pKW->szName; pKW++)
	{
		pKW->nIndex = nIndex++;
		if (pKW->nFlags)
		{
			pExpr = MakeIntConstant(pKW->nIndex);
			defineSubstitution(g_Template, pKW->szName, pExpr);
			pExpr->nFlags |= EXPR_FL_KEYWORD;
		}
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
int FindKeyword(char *szWord)
{
	keyword_t *pKW;

	for (pKW = &KeyWords[0]; pKW->szName; pKW++)
	{
		if (strcasecmp(pKW->szName, szWord) == 0)
			return(pKW->nIndex);
#ifdef DEBUG
		else fprintf("comparing '%s' and '%s'\n", pKW->szName, szWord);
#endif /* DEBUG */
	}

	return(-1);
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
char *KeywordText(int nKeyword)
{
	if (nKeyword < TOK_ID)
		return(NULL);

	nKeyword -= TOK_ID;

	if (nKeyword < 0)
		return(NULL);
	
	return(KeyWords[nKeyword].szName);
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
expr_t *
getKeywordValue(int nIndex)
{
	substitution_t *pSub;

	pSub = findSubstitution(pCurrentQuery, KeywordText(nIndex), 0);

	return((pSub)?pSub->pAssignment:NULL);
}
