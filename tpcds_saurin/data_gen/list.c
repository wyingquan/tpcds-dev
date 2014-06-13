/*
* $Id: list.c,v 1.4 2006/01/07 00:44:02 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2003
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: list.c,v $
* Revision 1.4  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.3  2005/02/15 22:55:08  jms
* add getTail()
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.6  2004/09/29 19:17:30  jms
* add const decl to list comparison functions for Solaris
*
* Revision 1.5  2004/09/27 20:06:20  jms
* simplify handling of sorted lists
* allow for recursive use of list functions without affecting l->current
*
* Revision 1.4  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.3  2004/03/26 19:45:04  jms
* rename tdef_funtions.c to tdef_functions.c
*
* Revision 1.2  2004/02/28 22:43:30  jms
* convery to list-based segment and substitution management
*
* Revision 1.1.1.1  2004/01/20 16:45:21  jms
* no message
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "error_msg.h"

list_t *
makeList(int nFlags, int (*SortFunc)(const void *d1, const void *d2))
{
	list_t *pRes;

	pRes = (list_t *)malloc(sizeof(list_t));
	MALLOC_CHECK(pRes);
	if (pRes == NULL)
		ReportError(QERR_NO_MEMORY, "client list", 1);
	memset(pRes, 0, sizeof(list_t));
	pRes->nFlags = nFlags;
	pRes->pSortFunc = SortFunc;

	return(pRes);
}

list_t *
addList(list_t *pList, void *pData)
{
	node_t *pNode;
	node_t *pInsertPoint;
	int bMoveForward = (pList->nFlags & L_FL_HEAD);

   pNode = (node_t *)malloc(sizeof(node_t));
	MALLOC_CHECK(pNode);
   if (!pNode)
      ReportErrorNoLine(QERR_NO_MEMORY, "client node", 1);
	memset(pNode, 0, sizeof(node_t));
	pNode->pData = pData;

	if (pList->nMembers == 0)	/* first node */
	{
		pList->head = pNode;
		pList->tail = pNode;
		pList->nMembers = 1;
		return(pList);
	}

	if (pList->nFlags & L_FL_SORT)
	{
			if (pList->pSortFunc(pData, pList->head->pData) <= 0)
			{
				/* new node become list head */
				pNode->pNext = pList->head;
				pList->head->pPrev = pNode;
				pList->head = pNode;
				pList->nMembers += 1;
				return(pList);
			}
			pInsertPoint = pList->head;

		/* find the correct point to insert new node */
		while (pInsertPoint)
		{
			if (pList->pSortFunc(pInsertPoint->pData, pData) < 0)
				break;
			pInsertPoint = (bMoveForward)?pInsertPoint->pNext:pInsertPoint->pPrev;
		}
		if (pInsertPoint) /* mid-list insert */
		{
			pNode->pNext = pInsertPoint->pNext;
			pNode->pPrev = pInsertPoint;
			pInsertPoint->pNext = pNode;
		}
		else
		{
			if (bMoveForward)
			{
				/* new node becomes list tail */
				pNode->pPrev = pList->tail;
				pList->tail->pNext = pNode;
				pList->tail = pNode;
			}
			else
			{
				/* new node become list head */
				pNode->pNext = pList->head;
				pList->head->pPrev = pNode;
				pList->head = pNode;
			}
		}

		pList->nMembers += 1;
		
		return(pList);
	}

		if (pList->nFlags & L_FL_HEAD)
		{
			pNode->pNext = pList->head;
			pList->head->pPrev = pNode;
			pList->head = pNode;
			pList->nMembers += 1;
		}
		else
		{
			pNode->pPrev = pList->tail;
			pList->tail->pNext = pNode;
			pList->tail = pNode;
			pList->nMembers += 1;
		}

	return(pList);
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
void *
removeItem(list_t *pList, int bHead)
{
	void *pResult;
	
	if (pList->nMembers == 0)
		return(NULL);

	if (!bHead)
	{
		pResult = pList->tail->pData;
		pList->tail = pList->tail->pPrev;
		pList->tail->pNext = NULL;
	}
	else
	{
		pResult = pList->head->pData;
		pList->head = pList->head->pNext;
		pList->head->pPrev = NULL;
	}

	pList->nMembers -= 1;

	return(pResult);
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
void *
getHead(list_t *pList)
{
	assert(pList);

	if (!pList->head)
		return(NULL);

	pList->pCurrent = pList->head;

	return(pList->pCurrent->pData);
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
void *
getTail(list_t *pList)
{
	assert(pList);

	if (!pList->tail)
		return(NULL);

	pList->pCurrent = pList->tail;

	return(pList->pCurrent->pData);
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
void *
getNext(list_t *pList)
{
	assert(pList);

	if (!pList->pCurrent->pNext)
		return(NULL);

	pList->pCurrent = pList->pCurrent->pNext;

	return(pList->pCurrent->pData);
}

/*
* Routine: 
* Purpose: findList(list_t *pList, void *pData)
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
void *
findList(list_t *pList, void *pData)
{
	void *pNode;
	struct LIST_NODE_T *pOldCurrent = pList->pCurrent;
	
	for (pNode = getHead(pList); pNode; pNode = getNext(pList))
		if (pList->pSortFunc(pNode, pData) == 0)
		{
			pList->pCurrent = pOldCurrent;
			return(pNode);
		}

		pList->pCurrent = pOldCurrent;
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
void *
getItem(list_t *pList, int nIndex)
{
	void *pResult;
	struct LIST_NODE_T *pOldCurrent = pList->pCurrent;
	
	if (nIndex > length(pList))
		return(NULL);


	for (pResult = getHead(pList); --nIndex; pResult = getNext(pList));

	pList->pCurrent = pOldCurrent;
	return(pResult);
}

