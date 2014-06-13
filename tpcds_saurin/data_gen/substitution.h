/*
* $Id: substitution.h,v 1.4 2005/12/09 01:00:49 jms Exp $
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
* $Log: substitution.h,v $
* Revision 1.4  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.3  2005/02/15 22:53:30  jms
* separate multiple SQL statements within a template
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.8  2004/09/29 19:17:30  jms
* add const decl to list comparison functions for Solaris
*
* Revision 1.7  2004/09/27 20:07:49  jms
* cleanup of recursive eval calls to handle nested substitution in decl section
*
* Revision 1.6  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.5  2004/09/10 21:15:32  jms
* correct handling of list() values
* unify flags on expr_t and substitution_t
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
* Revision 1.1  2002/11/20 15:45:33  jms
* QGEN cleanup
*
*/
#ifndef SUBSTITUION_T
#define SUBSTITUION_T
#include "StringBuffer.h"
#include "expr.h"
#include "list.h"
#include "eval.h"

/*
* a substitution is the defintion of one of the macros (textual subtitutions) in a query template
*/
typedef struct SUBSTITUTION_T {
	char *name;
	int flags;
	int nUse;	/* how many unique uses of this substitution in the template */
	int nSubParts; /* are there parts within the substitution? */
	expr_t *pAssignment;
	/* selected values are stored in arValues[] */
	struct EXPR_VAL_T  *arValues;
	int *pPermute;	/* each use may need a permutation */
	struct TEMPLATE_T *pTemplate;
	int nDataType;	/* type of the resulting value */
	int nQueryNumber;
} substitution_t;

/* flag defintions */

/*	a segment is a part of a query template. It is comprised of the static preamble 
	(text) and the optional dynamic placeholder (substitution) 
*/
typedef struct SEGMENT_T {
	char *text;	/* the text preamble to a substitution point */
	int flags;
	substitution_t  *pSubstitution; /* the substitution */
	int nSubCount; /* the usage count of the substitution */
	int nSubUse;	/* the sub component of the substitution */
} segment_t;
#define QS_EOS	0x0001

typedef struct TEMPLATE_T {
	char *name;
	int index;
	int flags;
	int nRowLimit;	/* used with [LIMIT] to control number of rows returned */
	list_t *SubstitutionList;
	list_t *SegmentList;
	list_t *DistributionList;
} template_t;
#define QT_INIT				0x0001

extern template_t *pCurrentQuery;

void		PrintQuery(FILE *fp, template_t *t);
int			AddQuerySegment(template_t *pQuery, char *szSQL);
int			AddQuerySubstitution(template_t *Query, char *szSubName, int nUse, int nSubPart);
int			AddSubstitution(template_t *t, char *s, expr_t *pExpr);
int			SetSegmentFlag(template_t *Query, int nSegmentNumber, int nFlag);
substitution_t *findSubstitution(template_t *t, char *stmt, int *nUse);
int			compareSubstitution(const void *p1, const void *p2);
Expr_Val_t *findValue(segment_t *pSeg);

#endif
