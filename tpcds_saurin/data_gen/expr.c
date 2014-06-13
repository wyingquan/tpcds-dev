/*
* $Id: expr.c,v 1.12 2007/12/19 22:37:43 jms Exp $
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
* $Log: expr.c,v $
* Revision 1.12  2007/12/19 22:37:43  jms
* Bug 582
*
* Revision 1.11  2007/11/21 19:29:16  jms
* Bug 575
*
* Revision 1.10  2007/11/21 18:50:02  jms
* 32/64 issues in qgen
*
* Revision 1.9  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.8  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.7  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.6  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.5  2005/11/23 21:40:55  jms
* alllow limited data type casting in expression
*
* Revision 1.4  2005/10/17 17:58:41  jms
* first cut at allowing multi-part substitutions in DEFINE statements
*
* Revision 1.3  2005/10/11 22:47:41  jms
* expand scanner to allow full substitution syntax in DEFINE
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:37  jms
* re-establish external server
*
* Revision 1.8  2004/09/29 18:30:52  jms
* resolve LIST() bug and standardize argument numbering
*
* Revision 1.7  2004/09/29 01:20:57  jms
* Fixes from review with Meikel:
*  -- add arithmetic expressions and SCALE
*  -- fix LIST/RANGE overrun
*
* Revision 1.6  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.5  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.4  2004/08/25 23:51:35  jms
* port to LINUX
*
* Revision 1.3  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.2  2004/02/28 22:43:30  jms
* convery to list-based segment and substitution management
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.7  2003/06/24 19:40:52  jms
* Allow query/stream/template number to occur in query templates
*
* Revision 1.6  2003/06/10 03:36:47  jms
* Bug 32: TEXT() not responding to weights
*
* Revision 1.5  2003/06/06 19:23:38  jms
* Closure of bug 29: TEXT() substitutions don't work
*
* Revision 1.4  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.3  2003/04/09 20:38:59  jms
* release 1.0.10: qgen range() fixes
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
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#ifndef USE_STRINGS_H
#include <string.h>
#else
#include <strings.h>
#endif
#include "error_msg.h"
#include "StringBuffer.h"
#include "expr.h"
#include "y.tab.h"
#include "substitution.h"
#include "substitution.h"
#include "grammar_support.h"
#include "date.h"
#include "keywords.h"
#include "dist.h"
#include "genrand.h"
#include "permute.h"
#include "list.h"

typedef struct FUNC_INFO_T {
	int nKeyword;
	int nParams;
	int nDataType;
	int nAddFlags;
} func_info_t;

#define MAX_FUNC	9
static func_info_t arFuncInfo[MAX_FUNC + 1] =
{
	{KW_DATE, 3, EXPR_FL_DATE, EXPR_FL_SUFFIX},
	{KW_DIST, 3, EXPR_FL_CHAR, EXPR_FL_SUFFIX},
	{KW_LIST, 2, EXPR_FL_TYPESHIFT, 0},
	{KW_RANGE, 2, EXPR_FL_TYPESHIFT, 0},
	{KW_RANDOM, 3, EXPR_FL_INT, 0},
	{KW_TEXT, 2, EXPR_FL_CHAR, 0},
	{KW_ROWCOUNT, 1, EXPR_FL_INT, 0},
	{KW_DISTMEMBER, 3, EXPR_FL_CHAR, 0},
	{KW_DISTWEIGHT, 3, EXPR_FL_INT, 0},
	{-1, -1, -1}
};
static int arFuncArgs[MAX_FUNC][MAX_ARGS + 1] =
{
	/* KW_DATE */		{EXPR_FL_CHAR, EXPR_FL_CHAR, EXPR_FL_INT, 0},
	/* KW_DIST */		{EXPR_FL_CHAR, EXPR_FL_TYPESHIFT, EXPR_FL_TYPESHIFT, 0},
	/* KW_LIST */		{EXPR_FL_TYPESHIFT, EXPR_FL_INT, 0},
	/* KW_RANGE */		{EXPR_FL_TYPESHIFT, EXPR_FL_INT, 0},
	/* KW_RANDOM */		{EXPR_FL_INT, EXPR_FL_INT, EXPR_FL_INT, 0},
	/* KW_TEXT */		{EXPR_FL_CHAR, EXPR_FL_INT, 0},
	/* KW_ROWCOUNT */	{EXPR_FL_CHAR, 0},
	/* KW_DISTMEMBER */	{EXPR_FL_CHAR, EXPR_FL_TYPESHIFT, EXPR_FL_TYPESHIFT, 0}, /* do the checking at runtime */
	/* KW_DISTWEIGHT */	{EXPR_FL_CHAR, EXPR_FL_TYPESHIFT, EXPR_FL_TYPESHIFT, 0} /* do the checking at runtime */
};

int ValidateParams(int nFunc, expr_t *pExpr);
extern template_t *pCurrentQuery;

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
static int
canCast(int nFromDataType, int nToDataType)
{
	int nValidSourceDataType = 0;
	
	switch (nToDataType)
	{
	case EXPR_FL_INT:
		nValidSourceDataType = EXPR_FL_KEYWORD|EXPR_FL_INT|EXPR_FL_CHAR;
		break;
	case EXPR_FL_CHAR:
		nValidSourceDataType = EXPR_FL_CHAR|EXPR_FL_INT;
		break;
	case EXPR_FL_DATE:
		nValidSourceDataType = EXPR_FL_DATE|EXPR_FL_CHAR;
		break;
	case EXPR_FL_TYPESHIFT:
		nValidSourceDataType = EXPR_TYPE_MASK;
		break;
	}
	return(nValidSourceDataType & nFromDataType);
}

/*
* Routine: expr_t *makeExpr(void)
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
makeExpr(void)
{
	expr_t *pResult;

	pResult = (expr_t *)malloc(sizeof(struct EXPR_T));
	MALLOC_CHECK(pResult);
	if (pResult == NULL)
		ReportError(QERR_NO_MEMORY, "in MakeReplacement()", 1);
	memset(pResult, 0, sizeof(struct EXPR_T));
	pResult->nValueCount = 1;
#ifdef MEM_TEST
	fprintf(stderr, "MakeExpr value %x\n", pResult);
#endif
	pResult->Value.pBuf = InitBuffer(10, 10);
	if (pResult->Value.pBuf == NULL)
		ReportError(QERR_NO_MEMORY, "in MakeReplacement()", 1);

	return(pResult);
}



/*
* Routine: MakeReplacement(char *szText, int nValue)
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
MakeReplacement(char *szText, int nValue)
{
	expr_t *pResult;

	pResult = makeExpr();

	AddBuffer(pResult->Value.pBuf, szText);
	pResult->Value.nValue = nValue;
	pResult->nFlags = EXPR_FL_REPL | EXPR_FL_CHAR;

	return(pResult);
}

/*
* Routine: MakeListExpr()
* Purpose: add LIST/RANGE modifiers to an expression
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
MakeListExpr(int nModifier, expr_t *pExpr, int nArg)
{
	int nFlag = (nModifier == KW_LIST)?EXPR_FL_LIST:EXPR_FL_RANGE;
	expr_t *pArgExpr;

	pExpr->nFlags |= nFlag;
	pArgExpr = MakeIntConstant(nArg);
	addList(pExpr->ArgList, pArgExpr);
	switch(nModifier)
	{
	case KW_LIST:
		pExpr->nValueCount = nArg;
		break;
	case KW_RANGE:
		pExpr->nValueCount = 2;
		break;
	default:
		INTERNAL("Bad modifier in MakeListExpr()");
		break;
	}

	return(pExpr);
}

/*
* Routine: MakeStringConstant(char *szText)
* Purpose: add an argument to the pre-existing list
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
MakeStringConstant(char *szText)
{
	expr_t *pResult;

	pResult = makeExpr();
	AddBuffer(pResult->Value.pBuf, szText);
	pResult->nFlags = EXPR_FL_CONST | EXPR_FL_CHAR;
	pResult->Value.bUseInt = 0;

	return(pResult);
}

/*
* Routine: makeArithmeticExpr(int nOp, expr_t *pArg1, expr_t *pArg2);
* Purpose: handle simple arithmetic
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
makeArithmeticExpr(int nOp, expr_t *pArg1, expr_t *pArg2)
{
	expr_t *pResult;
	int nDataType1, nDataType2;

	pResult = makeExpr();
	pResult->ArgList = makeList(L_FL_TAIL, NULL);
	addList(pResult->ArgList, pArg1);
	addList(pResult->ArgList, pArg2);
	pResult->Value.nValue = nOp;
	pResult->nFlags = EXPR_FL_FUNC;

	/* now set the data type of the result */
	nDataType1 = pArg1->nFlags & EXPR_TYPE_MASK;
	nDataType2 = pArg2->nFlags & EXPR_TYPE_MASK;
	if (nDataType1 >= nDataType2)
		pResult->nFlags |= nDataType1;
	else
		pResult->nFlags |= nDataType2;

	return(pResult);
}



/*
* Routine: MakeStringConstant(char *szText)
* Purpose: add an argument to the pre-existing list
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
MakeVariableReference(char *szText, int nSuffix)
{
	expr_t *pResult;

	pResult = makeExpr();

	AddBuffer(pResult->Value.pBuf, szText);
	pResult->nFlags = EXPR_FL_SUBST | EXPR_FL_CHAR;
	pResult->nSubElement = (nSuffix >= 1)?nSuffix:1;
	if (!findSubstitution(pCurrentQuery, szText, &nSuffix))
		yywarn("Substitution used before being defined");

	return(pResult);
}
/*
* Routine: MakeIntConstant(int nValue)
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
MakeIntConstant(ds_key_t nValue)
{
	expr_t *pResult;

	pResult = makeExpr();

	pResult->Value.nValue = nValue;
	pResult->nFlags = EXPR_FL_CONST | EXPR_FL_INT;
	pResult->Value.bUseInt = 1;

	return(pResult);
}

/*
* Routine: MakeFunctionCall(int nKeyword, expr_t *pArgList)
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
MakeFunctionCall(int nKeyword, list_t *pArgList)
{
	expr_t *pResult;
	int nFuncNum = -1,
		i;

	pResult = makeExpr();

	for (i=0; arFuncInfo[i].nKeyword >= 0; i++)
	{
		if (nKeyword == arFuncInfo[i].nKeyword)
			nFuncNum = i;
	}
	if (nFuncNum < 0)
		ReportError(QERR_BAD_NAME, NULL, 1);
	pResult->Value.nValue = nKeyword;
	pResult->nFlags = EXPR_FL_FUNC;
	pResult->nFlags |= arFuncInfo[nFuncNum].nDataType;
	pResult->nFlags |= arFuncInfo[nFuncNum].nAddFlags;
	pResult->ArgList = pArgList;

	if (ValidateParams(nFuncNum, pResult))
		ReportError(QERR_SYNTAX, "in MakeFunctionCall()", 1);

	return(pResult);
}

/*
* Routine: PrintExpr(expr_t *)
* Purpose: print out an expression to allow templates to be reconstructed
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
PrintExpr(expr_t *pExpr)
{
	int i,
		bUseComma = 0;
	expr_t *pArg;
   char szFormat[20];

	/* handle the constants */
	if (pExpr->nFlags & EXPR_FL_CONST)
	{
		switch(i = pExpr->nFlags & (EXPR_TYPE_MASK ^ EXPR_FL_KEYWORD))
		{
		case EXPR_FL_INT:
			if (pExpr->nFlags & EXPR_FL_KEYWORD)
				printf("%s", KeywordText((int)pExpr->Value.nValue));
			else
				printf(HUGE_FORMAT, pExpr->Value.nValue);
			break;
		case EXPR_FL_CHAR:
			printf("\"%s\"", GetBuffer(pExpr->Value.pBuf));
			break;
		default:
			fprintf(stderr, "INTERNAL ERROR: unknown constant type %d\n", i);
			exit(1);
		}
		return;
	}
	
	/* handle the parameterized expressions */
	switch(pExpr->nFlags & EXPR_FUNC_MASK)
	{
	case EXPR_FL_FUNC:
		if (pExpr->nFlags & EXPR_FL_FUNC)
		{
			printf("%s(", KeywordText((int)pExpr->Value.nValue));
			for (pArg = (expr_t *)getHead(pExpr->ArgList); pArg; pArg = (expr_t *)getNext(pExpr->ArgList))
			{
				if (bUseComma)
					printf(",\n\t");
				PrintExpr(pArg);
				bUseComma = 1;
			}
			printf(")");
		}
		break;
	case EXPR_FL_REPL:
		sprintf(szFormat, "{\"%%s\", %s}", HUGE_FORMAT);
		printf(szFormat, GetBuffer(pExpr->Value.pBuf), pExpr->Value.nValue);
		break;
	case EXPR_FL_SUBST:
		printf("[%s]", GetBuffer(pExpr->Value.pBuf));
		break;
	default:
		fprintf(stderr, "INTERNAL ERROR: unknown expression type %x\n", pExpr->nFlags);
		exit(1);
	}
	
	return;
	
}

/*
* Routine: ValidateParams(int nFunc, expr_t *pArgs)
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
ValidateParams(int nFunc, expr_t *pArgs)
{
	int i = 0,
		nArgs;
	expr_t *pCurrentArg;
	char msg[80];
	
	pCurrentArg = getHead(pArgs->ArgList);
	if (pCurrentArg)
	{
		
		if (pCurrentArg->nFlags & EXPR_FL_REPL)	/* replacement sets can be arbitrarily long */
			return(0);
	}

	nArgs = length(pArgs->ArgList);
	if (nArgs != arFuncInfo[nFunc].nParams)
	{
		
		sprintf(msg, "wanted %d args, found %d", arFuncInfo[nFunc].nParams, nArgs);
		ReportError(QERR_BAD_PARAMS, msg, 0);
		return(1);
	}
	
	for (pCurrentArg = (expr_t *)getHead(pArgs->ArgList); pCurrentArg; pCurrentArg = (expr_t *)getNext(pArgs->ArgList))
	{
		if (!canCast(pCurrentArg->nFlags & EXPR_TYPE_MASK,arFuncArgs[nFunc][i]) && 
			(arFuncArgs[nFunc][i] != EXPR_FL_TYPESHIFT))
		{
			sprintf(msg, "type mismatch in call to %s() on parameter %d (%d/%d)", 
				KeywordText(arFuncInfo[nFunc].nKeyword), 
				i + 1, 
				(pCurrentArg->nFlags & EXPR_TYPE_MASK), arFuncArgs[nFunc][i]);
			ReportErrorNoLine(QERR_BAD_PARAMS, msg, 0);
			return(1);
		}
		i += 1;
	}

	return(0);
}
