/*
* $Id: substitution.c,v 1.6 2006/05/10 22:03:23 jms Exp $
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
* substitution.c: routines managing the substitution tags in a query template
*
* Revision History
* ===================
* $Log: substitution.c,v $
* Revision 1.6  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.5  2006/01/07 00:46:35  jms
* add MALLOC_CHECK calls
*
* Revision 1.4  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.3  2005/02/15 22:52:53  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.9  2004/09/29 19:17:30  jms
* add const decl to list comparison functions for Solaris
*
* Revision 1.8  2004/09/29 18:30:52  jms
* resolve LIST() bug and standardize argument numbering
*
* Revision 1.7  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.6  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
* Revision 1.5  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.4  2004/02/28 22:49:52  jms
* simplify qgen command line and processing
*
* Revision 1.3  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.2  2002/11/27 00:31:23  jms
* fully implement recursive substitution
*
* Revision 1.1  2002/11/20 15:45:33  jms
* QGEN cleanup
*

*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_msg.h"
#include "dist.h"
#include "date.h"
#include "decimal.h"
#include "misc.h"
#include "genrand.h"
#include "substitution.h"
#include "StringBuffer.h"

extern template_t *pCurrentTemplate,
	*g_Template;
int ParseFile(char *szPath);

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
compareSubstitution(const void *p1, const void *p2)
{
	substitution_t *pS1 = (substitution_t *)p1,
		*pS2 = (substitution_t *)p2;

	if (pS1 == NULL)
	{
		if (pS2 == NULL)
			return(0);
		else
			return(-1);
	}
	
	if (pS2 == NULL)
		return(1);
	
	return(strcasecmp(pS1->name, pS2->name));
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
substitution_t *
findSubstitution(template_t *t, char *name, int *nUse)
{
	int nChars,
		nUseCount;
	substitution_t *pSub;
	static substitution_t tempSubstitution;
	static int bInit = 0;

	if (!bInit)
	{
		memset(&tempSubstitution, 0, sizeof(struct SUBSTITUTION_T));
		tempSubstitution.name = malloc(100 * sizeof(char));
		MALLOC_CHECK(tempSubstitution.name);
		bInit = 1;
	}
	
	/* exclude any numeric suffix from search, but update nUses */
	nChars = strcspn(name, "0123456789");
	if (strlen(name) > 100)
		tempSubstitution.name = realloc(tempSubstitution.name, strlen(name) + 1);
	strncpy(tempSubstitution.name, name, nChars);
	tempSubstitution.name[nChars] = '\0';
	pSub = findList(t->SubstitutionList, (void *)&tempSubstitution);
	if (!pSub) /* the substitution could be global; add a local reference */
	{
		pSub = findList(g_Template->SubstitutionList, (void *)&tempSubstitution);
		if (pSub)
			addList(t->SubstitutionList, pSub);
	}
	if (pSub)
	{
		nUseCount = atoi(name + nChars);
		if (nUseCount == 0)
			nUseCount = 1;
		if (nUseCount > pSub->nUse)
			pSub->nUse = nUseCount;
		if (nUse)	/* we're interested in the usage number */
			*nUse = nUseCount;
		return(pSub);
	}
	
	return(NULL);
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
AddQuerySubstitution(template_t *t, char *szName, int nUse, int bEndSuffix)
{
	substitution_t *pSub;
	segment_t *pSegment;
	int nSegmentCount;
	
	if ((pSub = findSubstitution(t, szName, NULL)) == NULL)
		ReportError(QERR_NO_INIT, szName, 1);
	nSegmentCount = length(t->SegmentList);
	if (nSegmentCount == 0)	/* template starts with a substitution */
		AddQuerySegment(t, "");
	pSegment = (segment_t *)getItem(t->SegmentList, length(t->SegmentList));
	if (pSegment->pSubstitution)
	{
		AddQuerySegment(t, "");
		pSegment = (segment_t *)getItem(t->SegmentList, length(t->SegmentList));
	}
	pSegment->pSubstitution = pSub;
	pSegment->nSubUse = bEndSuffix;
	if (pSub->pAssignment->nFlags & EXPR_FL_LIST)
		pSegment->nSubUse -= 1;
	pSegment->nSubCount = nUse;
	
	return(0);
}

