%{
/*
* $Id: tokenizer.l,v 1.11 2007/01/18 22:32:46 jms Exp $
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
* $Log: tokenizer.l,v $
* Revision 1.11  2007/01/18 22:32:46  jms
* solaris (non-flex) porting issue)
*
* Revision 1.10  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.9  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.8  2006/01/07 00:44:42  jms
* correct yywrap oddness under LEX
*
* Revision 1.7  2005/12/09 01:00:49  jms
* Bug 352: need to support rowcount limits
*
* Revision 1.6  2005/10/11 22:47:42  jms
* expand scanner to allow full substitution syntax in DEFINE
*
* Revision 1.5  2005/10/03 18:51:35  jms
* improve output of -DEBUG
*
* Revision 1.4  2005/03/15 22:37:03  jms
* Bug 146: invalid data in catalog_returns
*
* Revision 1.3  2005/02/15 22:52:53  jms
* add support for _QUERY, _STREAM and _TEMPLATE
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.4  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.3  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.2  2004/02/28 22:46:51  jms
* avoid id conflicts with move to bison/flex on windows
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.4  2003/04/23 22:48:24  jms
* compiler errors under MP-RAS
*
* Revision 1.3  2003/04/23 19:01:12  jms
* make scanner state durable across calls to yylex
*
* Revision 1.2  2003/04/21 19:14:57  jms
* bug 9: lex changes for MP/RAS
*
* Revision 1.1  2003/03/21 19:56:45  jms
* resync with code on laptap
*
*
*/

#ifdef SCAN_DEBUG
#define DECLARER
#endif /* SCAN_DEBUG */
#include "config.h"
#include "porting.h"
#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
//#include <malloc.h>
#include "keywords.h"
#include "StringBuffer.h"
#include "expr.h"
#include "y.tab.h"
#include "qgen_params.h"
#include "substitution.h"
#include "grammar_support.h"

#ifdef SCAN_DEBUG
#define RETURN(type)	DisplayAction(type)
#include "qgen_params.h"
extern file_ref_t *pCurrentFile = &CurrentFile;
int LN;
workload_t CurrentWorkload;
template_t CurrentQuery;
workload_t *pCurrentWorkload = &CurrentWorkload;
template_t *pCurrentQuery = &CurrentQuery;
YYSTYPE yylval;
#else
#define RETURN(type)	return(type)
#endif

/* need to keep track of state from one call to the next */
/* #define STATE(type)	printf("<STATE %d>\n", type);nState = type */
#ifndef STATE
#define STATE(type)	nState = type
#endif
static int nState = -1;

int nCharCount;
int bFirstWord = 1;
int nKeyword;
static int nOldState;

int yywrap(void);
int yylook(void);

%}

%{ 
/* macro definitions go here */ 
%}
INT	-?[0-9]+
DECIMAL   -?[0-9]*\.[0-9]+
WS	[ \t]+
ID	[_a-zA-Z][a-zA-Z0-9_]*
SUB_ID	[a-zA-Z_]*
%s SQLTEXT SUBST NORMAL
%%
%{
	switch(nState)
	{
	case NORMAL:	BEGIN(NORMAL);break;
	case SUBST:		BEGIN(SUBST);break;
	case SQLTEXT:	BEGIN(SQLTEXT);break;
	default:			BEGIN(NORMAL);break;
	}
%}
<NORMAL>{WS}			nCharCount += strlen(yytext); /* ignore whitespace */
<NORMAL>--[^\n]*		nCharCount += strlen(yytext); /* ignore comments */
<NORMAL>{DECIMAL}	{ 
				nCharCount += strlen(yytext); 
				bFirstWord = 0; 
				RETURN(TOK_DECIMAL); 
				}
<NORMAL>{INT}			{ 
				nCharCount += strlen(yytext); 
				bFirstWord = 0; 
				yylval.intval = atoi(yytext);
				RETURN(TOK_INT); 
				}
<NORMAL>{ID}			{ 
				if ((nKeyword = FindKeyword(yytext)) >= 0)
					{
					bFirstWord = 0;
					RETURN(nKeyword);
					}
				else
					if (bFirstWord)
						{
						STATE(SQLTEXT);
						BEGIN(SQLTEXT);
						yylval.strval = strdup(yytext);
						return(TOK_SQL);
						}
					else
						{
						yylval.strval = strdup(yytext);
						RETURN(TOK_ID); 
						}
				}
<NORMAL>\"[^\n\"]*\" { 
				nCharCount += strlen(yytext); 
				bFirstWord = 0;
				yytext[yyleng - 1] = '\0';
				yylval.strval = strdup(yytext+1);
				RETURN(TOK_LITERAL); 
				}
<NORMAL>\n			{ nCharCount = 1; pCurrentFile->line_number += 1; bFirstWord = 1; }
<NORMAL>"["	{
			nOldState = NORMAL;
					nCharCount += 1; 
				STATE(SUBST); 
				BEGIN(SUBST); 
				RETURN(yytext[0]); 
			}
<NORMAL>.			{ nCharCount += strlen(yytext); 
				bFirstWord = 0; 
				RETURN(yytext[0]); 
			}

<SUBST>{SUB_ID}		{
				if ((nKeyword = FindKeyword(yytext)) >= 0)
					{
					RETURN(nKeyword);
					}
				else
						{
						yylval.strval = strdup(yytext);
						RETURN(TOK_ID); 
						}
				}

<SUBST>{INT}		{
					nCharCount += strlen(yytext);
					yylval.intval = atoi(yytext);
					return(TOK_INT);
					}
<SUBST>"."			{RETURN('.');}
<SUBST>"]"			{
					STATE(nOldState);
					BEGIN(nOldState);
					RETURN(yytext[0]);
					}
<SQLTEXT>[^;\[\]\n]*\n	{
						nCharCount += strlen(yytext); 
						yylval.strval = strdup(yytext);
						nCharCount = 1; pCurrentFile->line_number += 1;
						if (strlen(yylval.strval))
							RETURN(TOK_SQL); 
						}
<SQLTEXT>[^;\[\]\n]*	{
						nCharCount += strlen(yytext); 
						yylval.strval = strdup(yytext);
						RETURN(TOK_SQL); 
						}
<SQLTEXT>"["		{
					nOldState = SQLTEXT;
					nCharCount += 1; 
					STATE(SUBST); 
					BEGIN(SUBST); 
					RETURN(yytext[0]); 
				}
<SQLTEXT>;		{ STATE(NORMAL);BEGIN(NORMAL);nCharCount += 1;  RETURN(yytext[0]); }
<SQLTEXT>.		{ nCharCount += 1;  RETURN(yytext[0]); }
%%
extern template_t *pCurrentQuery;

/*
 * Routine: yywrap()
 * Purpose: manage the hand off between multiple input files, include files, 
 *			etc.
 * Algorithm:
 * 		MKS lex has special buffer handlers that aren't exposed, so this needs to be included in the LEX source
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
yywrap(void)
{
	file_ref_t *pNext;


	if (is_set("DEBUG"))
		printf("STATUS: CLOSE(%s)\n", pCurrentFile->name);
	fclose(pCurrentFile->file);

    if (pCurrentFile->pNext) 
    	{
#ifdef MKS
		yyRestoreScan(pCurrentFile->pLexState);
#endif
#ifdef FLEX
		yy_switch_to_buffer(pCurrentFile->pNext->pLexState);
		yy_delete_buffer(pCurrentFile->pLexState);
#endif
		pNext = pCurrentFile->pNext;
#if !defined(MKS) && !defined(FLEX)
		yyin = pNext->file;
#endif
		free(pCurrentFile);
		pCurrentFile = pNext;
		if (is_set("DEBUG"))
			printf("STATUS: REOPEN(%s)\n", pCurrentFile->name);
		return(0);
		}

    return(1);
}
#ifdef SCAN_DEBUG
DisplayAction(int d)
{
if (d >= ID)
	printf("<%s: '%s'>\n", KeywordText(d), yytext);
else
	printf ("%s\n", yytext);

return;
}

main(int ac, char **av)
{
LN=1;
nCharCount=1;
InitKeywords();
yylex();
exit(0);
}
#endif
