/*
* $Id: expr.h,v 1.6 2007/11/21 18:49:24 jms Exp $
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
* $Log: expr.h,v $
* Revision 1.6  2007/11/21 18:49:24  jms
* 32/64 issues in qgen
*
* Revision 1.5  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
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
* Revision 1.9  2004/09/29 18:30:52  jms
* resolve LIST() bug and standardize argument numbering
*
* Revision 1.8  2004/09/29 01:20:57  jms
* Fixes from review with Meikel:
*  -- add arithmetic expressions and SCALE
*  -- fix LIST/RANGE overrun
*
* Revision 1.7  2004/09/27 20:07:49  jms
* cleanup of recursive eval calls to handle nested substitution in decl section
*
* Revision 1.6  2004/09/10 21:15:32  jms
* correct handling of list() values
* unify flags on expr_t and substitution_t
*
* Revision 1.5  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.4  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.3  2004/08/25 23:52:54  jms
* port to LINUX after makefile changes
*
* Revision 1.2  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.2  2003/03/21 21:32:09  jms
* add newline at end of file
*
* Revision 1.1  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*
*/
#ifndef EXPR_H
#define EXPR_H

#include "StringBuffer.h"
#include "list.h"
#include "mathops.h"

typedef struct EXPR_VAL_T {
	int bUseInt;
	StringBuffer_t *pBuf;
	ds_key_t nValue;
	int nQueryNumber;
} Expr_Val_t;

typedef struct EXPR_T
{
	int nFlags;
	list_t *ArgList;
	Expr_Val_t Value;
	int nValueCount;
	int *pPermute;
	int nSubElement;
} expr_t;

/* expression flags */
/* NOTE: order of data types is important to makeArithmeticExpr() CHANGE WITH CARE */
#define EXPR_FL_CONST		0x00000001
#define EXPR_FL_UNDEF		0x00000002
#define EXPR_FL_FUNC		0x00000004
#define EXPR_FL_INT			0x00000008	/* argument is an integer */
#define EXPR_FL_CHAR		0x00000010	/* argument is a character string */
#define EXPR_FL_SUBST		0x00000020	/* argument is a pre-defined substitution */
#define EXPR_FL_KEYWORD		0x00000040	/* interpret nValue as a keyword index */
#define EXPR_FL_DATE		0x00000080	/* interpret nValue as a julian date */
#define EXPR_FL_TYPESHIFT	0x00000100	/* take type from arguments */
#define EXPR_TYPE_MASK		0x000001D8	/* different data types */
#define EXPR_FUNC_MASK		0x00000224	/* FUNC, REPL, SUBST */
#define EXPR_FL_REPL		0x00000200	/* replacement pair */
#define EXPR_FL_SUFFIX		0x00000400	/* expression can have begin/end tags */
#define EXPR_FL_LIST		0x00000800	/* expression should return a list of values */
#define EXPR_FL_RANGE		0x00001000	/* expression should return a range of values */
#define EXPR_FL_INIT		0x00002000	/* the expression has been initialized */
#define EXPR_FL_TEXT		0x00004000	/*  substitution is a text value */
#define EXPR_FL_DIST		0x00008000	/*  substitution is taken from a distribution */
#define EXPR_FL_RANDOM		0x00010000	/*  substitution is a random integer */
#define EXPR_FL_DISTMEMBER	0x00020000	/*  substitution returns distribution value */
#define EXPR_FL_DISTWEIGHT	0x00040000	/*  substitution returns distribtuion weight */
#define EXPR_FL_ROWCOUNT	0x00080000	/*  substitution table/distribution rowcount */
#define EXPR_FL_UNIFORM		0x00100000	/*  use a uniform distribution */
#define EXPR_FL_NORMAL		0x00200000	/*  use a normal distribution */
#define EXPR_FL_SALES		0x00400000	/*  skew dates for sales */
#define EXPR_FL_TABLENAME	0x00800000	/*	rowcount() argument is a table name */
#define EXPR_FL_VENDOR		0x01000000	/*  do double substitution for vendor syntax */
#define EXPR_FL_TYPE_MASK	(EXPR_FL_TEXT|EXPR_FL_RANDOM|EXPR_FL_DIST)	/*  separate substitution types. */
#define EXPR_FL_DIST_MASK	(EXPR_FL_UNIFORM|EXPR_FL_NORMAL)
#define EXPR_FL_SUFFIX_MASK	(EXPR_FL_LIST|EXPR_FL_RANGE)	/* substitution that allow suffixes */

#define MAX_ARGS	20	/* overly large to allow TEXT() to have a lot of options */

#define DT_NONE		-1
#define DT_INT		0
#define DT_STR		1
#define DT_CHR		2
#define DT_DEC		3
#define DT_DATE		4
#define DT_KEY		5

#define OP_ADD		0
#define OP_SUBTRACT	1
#define OP_MULTIPLY	2
#define OP_DIVIDE	3

void AddArgument(expr_t *pArgList, expr_t *pExpr);
expr_t *MakeStringConstant(char *szText);
expr_t *MakeIntConstant(ds_key_t nValue);
expr_t *MakeFunctionCall(int nKeyword, list_t *pArgList);
expr_t *MakeListExpr(int nModifier, expr_t *pExpr, int nArg);
expr_t *MakeReplacement(char *szText, int nValue);
expr_t *MakeVariableReference(char *szText, int nSuffix);
expr_t *makeArithmeticExpr(int nOp, expr_t *pArg1, expr_t *pArg2);
void PrintExpr(expr_t *pExpr);


int EvalTextExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam);
char *GetParam(expr_t *pExpr, int nParam);
int EvalDistExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam);
int EvalRandomExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam);
int EvalRowcountExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams);
int EvalDateExpr(expr_t *pExpr, Expr_Val_t *pBuf, Expr_Val_t *pParams, int bIsParam);
int EvalArg(expr_t *pArg, Expr_Val_t *pBuf, Expr_Val_t *pParams);
int EvalExpr(expr_t *pExpr, Expr_Val_t *pValue, int bIsParam, int nQueryNumber);
int EvalArithmetic(expr_t *pExpr, Expr_Val_t *pValue, Expr_Val_t *pParams);
#endif

