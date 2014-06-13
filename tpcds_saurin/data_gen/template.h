/*
* $Id: template.h,v 1.2 2004/11/24 23:54:21 jms Exp $
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
* $Log: template.h,v $
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.9  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.8  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.7  2004/02/28 22:49:52  jms
* simplify qgen command line and processing
*
* Revision 1.6  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.9  2003/07/24 16:46:27  jms
* Beginnigs of 2 phase qgen
*
* Revision 1.8  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.7  2003/03/21 21:33:01  jms
* compile under linux
*
* Revision 1.6  2003/03/21 19:56:45  jms
* resync with code on laptap
*
* Revision 1.5  2002/12/04 17:32:59  jms
* Include changes from win2k for porting update
*
* Revision 1.4  2002/11/27 00:31:23  jms
* fully implement recursive substitution
*
* Revision 1.3  2002/11/20 00:51:34  jms
* QGEN2 corrections
*
* Revision 1.2  2002/11/14 02:37:37  jms
* correct misc errors in qgen dating from 2001
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "StringBuffer.h"
#include "expr.h"
#include "list.h"
#include "substitution.h"


/*  Replacement flags */
#define REPL_FL_NONE		0x0001	/*  no effect on result set size */
#define REPL_FL_MORE		0x0002	/*  likely to increase result set size */
#define REPL_FL_LESS		0x0004	/*  likely to decrease result set size */




typedef struct TEMPLATE_T {
	char *name;
	int index;
	int flags;
	list_t *SubstitutionList;
	list_t *SegmentList;
	list_t *DistList;
} template_t;
#define QT_INIT				0x0001

extern template_t *pCurrentQuery;

void		PrintQuery(FILE *fp, template_t *t);
int			AddQuerySegment(template_t *pQuery, char *szSQL);
int			AddQuerySubstitution(template_t *Query, char *szSubName, int nUse, int nSubPart);
int			AddSubstitution(template_t *t, char *s, expr_t *pExpr);
int			SetSegmentFlag(template_t *Query, int nSegmentNumber, int nFlag);
substitution_t *FindSubstitution(template_t *t, char *stmt, int *nUse);
#endif


