/*
* $Id: list.h,v 1.3 2005/02/15 22:55:08 jms Exp $
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
* $Log: list.h,v $
* Revision 1.3  2005/02/15 22:55:08  jms
* add getTail()
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.3  2004/09/29 19:17:30  jms
* add const decl to list comparison functions for Solaris
*
* Revision 1.2  2004/02/28 22:43:30  jms
* convery to list-based segment and substitution management
*
* Revision 1.1.1.1  2004/01/20 16:45:21  jms
* no message
*
*/
#ifndef LIST_H
#define LIST_H
typedef struct LIST_NODE_T
{
	struct LIST_NODE_T *pNext;
	struct LIST_NODE_T *pPrev;
	void *pData;
} node_t;

typedef struct LIST_T
{
	struct LIST_NODE_T *head;
	struct LIST_NODE_T *tail;
	struct LIST_NODE_T *pCurrent;
	int (*pSortFunc)(const void *pD1, const void *pD2);
	int nMembers;
	int nFlags;
} list_t;

/* list_t flags */
#define L_FL_HEAD		0x01	/* add at head */
#define L_FL_TAIL		0x02	/* add at tail */
#define L_FL_SORT		0x04	/* create sorted list */

#define length(list)	list->nMembers


list_t *makeList(int nFlags, int (*pSortFunc)(const void *pD1, const void *pD2));
list_t *addList(list_t *pList, void *pData);
void *findList(list_t *pList, void *pData);
void *removeItem(list_t *pList, int bFromHead);
void *getHead(list_t *pList);
void *getTail(list_t *pList);
void *getNext(list_t *pList);
void *getItem(list_t *pList, int nIndex);
#endif



