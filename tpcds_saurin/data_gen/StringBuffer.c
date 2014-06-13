/*
* $Id: StringBuffer.c,v 1.5 2007/11/21 19:22:05 jms Exp $
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
* $Log: StringBuffer.c,v $
* Revision 1.5  2007/11/21 19:22:05  jms
* Bug 575
*
* Revision 1.4  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.3  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.5  2002/12/04 18:54:19  jms
* fixed potential over-run problem with AddBuffer()
*
* Revision 1.4  2002/12/04 17:32:59  jms
* Include changes from win2k for porting update
*
* Revision 1.3  2002/11/27 00:31:23  jms
* fully implement recursive substitution
*
* Revision 1.2  2002/11/20 15:52:37  jms
* Missing newline at EOF caused Linux build error
*
* Revision 1.1  2002/11/20 15:45:33  jms
* QGEN cleanup
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <assert.h>
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include "StringBuffer.h"

/*
* Routine: InitBuffer
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
StringBuffer_t *InitBuffer(int nSize, int nIncrement)
{
	StringBuffer_t *pBuf;

	pBuf = (StringBuffer_t *)malloc(sizeof(struct STRING_BUFFER_T));
	MALLOC_CHECK(pBuf);
	if (pBuf == NULL)
		return(NULL);
	memset((void *)pBuf, 0, sizeof(struct STRING_BUFFER_T));

	pBuf->pText = (char *)malloc(sizeof(char) * nSize);
	MALLOC_CHECK(pBuf->pText);
	if (pBuf->pText == NULL)
		return(NULL);
	memset((void *)pBuf->pText, 0, sizeof(char) * nSize);

	pBuf->nIncrement = nIncrement;
	pBuf->nBytesAllocated = nSize;
	pBuf->nFlags = SB_INIT;

	return(pBuf);
}

/*
* Routine: AddBuffer
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
int AddBuffer(StringBuffer_t *pBuf, char *pStr)
{
	int nRemaining = pBuf->nBytesAllocated - pBuf->nBytesUsed,
		nRequested = strlen(pStr);

	if (!nRequested)
		return(0);
	
	while (nRequested >= nRemaining)
	{
		pBuf->pText = (char *)realloc((void *)pBuf->pText, pBuf->nBytesAllocated + pBuf->nIncrement);
		if (!pBuf->pText)
			return(-1);
		pBuf->nBytesAllocated += pBuf->nIncrement;
		nRemaining += pBuf->nIncrement;
	}

	strcat(pBuf->pText, pStr);
	if (pBuf->nBytesUsed == 0)	/* first string adds a terminator */
		pBuf->nBytesUsed = 1;
	pBuf->nBytesUsed += nRequested;

	return(0);
}


/*
* Routine: ResetStringBuffer
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
int ResetBuffer(StringBuffer_t *pBuf)
{
	pBuf->nBytesUsed = 0;
	if (pBuf->nBytesAllocated)
		pBuf->pText[0] = '\0';

	return(0);
}

/*
* Routine: GetBuffer
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
char *GetBuffer(StringBuffer_t *pBuf)
{
	return(pBuf->pText);
}

/*
* Routine: FreeBuffer
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
void FreeBuffer(StringBuffer_t *pBuf)
{
	if (!pBuf)
		return;
	if (pBuf->pText)
		free((void *)pBuf->pText);
	free((void *)pBuf);

	return;
}


