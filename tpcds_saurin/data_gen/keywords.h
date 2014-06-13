/*
* $Id: keywords.h,v 1.4 2005/12/09 01:00:49 jms Exp $
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
* $Log: keywords.h,v $
* Revision 1.4  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.3  2005/02/15 22:54:45  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1  2003/03/21 19:56:44  jms
* resync with code on laptap
*
*/
#ifndef KEYWORDS_H
#define KEYWORDS_H
#include "expr.h"
typedef struct KEYWORD_T {
	char *szName;
	int nFlags;
	int nIndex;
	} keyword_t;

/* flag values for keywords */
#define KYWD_SUBSTITUION	0x01	/* this is actually a pre-defined substitution */

void InitKeywords();
int FindKeyword(char *szWord);
char *KeywordText(int nKeyword);
expr_t *getKeywordValue(int nIndex);
#endif
