/*
* $Id: grammar.h,v 1.2 2004/11/24 23:54:16 jms Exp $
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
* $Log: grammar.h,v $
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.4  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.3  2002/11/20 00:51:33  jms
* QGEN2 corrections
*
* Revision 1.2  2002/11/14 02:37:37  jms
* correct misc errors in qgen dating from 2001
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef GRAMMAR_H
#define GRAMMAR_H

typedef struct TOKEN_T {
	int index;
	char word[40];
	int (*handler)(char *s, struct TOKEN_T *t);
} token_t;

#define COMMENT_CHAR	'-'
#define STMT_END		';'
int ParseFile(char *szPath);
int FindToken(char *name);
void SetTokens(token_t *t);
char *ProcessStr(char *stmt, token_t *pTokens);
char	*SafeStrtok(char *string, char *delims);
extern token_t *pTokens;

#endif /* GRAMMAR_H */
