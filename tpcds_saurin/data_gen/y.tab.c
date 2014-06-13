#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 "qgen.y"
/*
 * @(#) p_dbgengen.yy 1.2.1.25@(#)
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
 * (C) COPYRIGHT Gradient Systems Inc. 1997 - 2000
 *
 * All Rights Reserved  
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
 * The copyright notice above does not evidence any   
 * actual or intended publication of such source code.
 * 
 * the grammar for dbgengen
 *
 */
#include "config.h"
#include "porting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <io.h>
#pragma warning(disable: 4305)
#endif

#include "StringBuffer.h"
#include "expr.h"
#include "grammar_support.h"
#include "keywords.h"
#include "substitution.h"
#include "error_msg.h"
#include "tables.h"
#include "qgen_params.h"
#include "tdefs.h"
#include "query_handler.h"
#include "list.h"
#include "dist.h"
#include "scaling.h"


#define DEBUG0(l, fmt) 				if (l <= verbose) printf(fmt)
#define DEBUG1(l, fmt, arg)			if (l <= verbose) printf(fmt, arg)
#define DEBUG2(l, fmt, arg, arg2)	if (l <= verbose) printf(fmt, arg, arg2)

extern file_ref_t file_stack[];

int yylex(void);

#ifdef WIN32
int yyparse(void);
#endif

/* GLOBAL VARIABLES */
int verbose = 0,
	j,
	nRetCode;
ds_key_t i;
char tmpstr[128];
segment_t *pSegment;
substitution_t *pSub;
#line 75 "qgen.y"
typedef union {
    int		intval;
    char	*strval;
	expr_t	*exprval;
	list_t  *list;
    } YYSTYPE;
#line 96 "y.tab.c"
#define YYERRCODE 256
#define TOK_INT 257
#define TOK_LITERAL 258
#define TOK_PATH 259
#define TOK_DECIMAL 260
#define TOK_ID 261
#define TOK_SQL 262
#define KW_DEFINE 263
#define KW_RANDOM 264
#define KW_UNIFORM 265
#define KW_RANGE 266
#define KW_DATE 267
#define KW_INCLUDE 268
#define KW_TEXT 269
#define KW_DIST 270
#define KW_LIST 271
#define KW_ROWCOUNT 272
#define KW_BEGIN 273
#define KW_END 274
#define KW_SALES 275
#define KW_RETURNS 276
#define KW_DISTMEMBER 277
#define KW_DISTWEIGHT 278
#define KW_QUERY 279
#define KW_STREAM 280
#define KW_TEMPLATE 281
#define KW_SCALE 282
#define KW_SCALE_STEP 283
#define KW_SET 284
#define KW_ADD 285
#define KW_NAMES 286
#define KW_TYPES 287
#define KW_WEIGHTS 288
#define KW_INT 289
#define KW_VARCHAR 290
#define KW_DECIMAL 291
#define KW_LIMIT 292
#define KW_LIMITA 293
#define KW_LIMITB 294
#define KW_LIMITC 295
#define WITH 296
#define UMINUS 297
#define TCAST 298
const short yylhs[] = {                                        -1,
    0,   15,   15,   14,   14,   14,   14,   16,   16,   19,
   20,   20,   22,   22,   22,   25,   25,   25,   23,   23,
   23,   24,   24,   21,   21,   26,   29,   29,   29,   27,
   27,   28,   28,   17,   17,    1,    1,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    4,    4,    4,    4,
    4,    4,    4,    4,    5,    5,    5,    5,    2,    2,
    2,    2,    7,    7,    6,    6,    6,    8,    8,    8,
    9,    9,    9,   13,   13,   12,   18,   30,   30,   30,
   30,   31,   31,   31,   31,   31,   31,   31,   31,   11,
   11,   11,   11,   10,
};
const short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    1,    3,    5,    5,
    1,    2,    5,    7,    9,    1,    1,    1,    0,    1,
    3,    1,    3,    1,    2,    7,    1,    1,    1,    1,
    3,    1,    3,    5,    5,    1,    3,    1,    1,    1,
    1,    3,    5,    4,    1,    1,    4,    4,    4,    4,
    6,    3,    6,    6,    3,    3,    3,    3,    1,    1,
    3,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    5,    2,    1,    1,    2,
    2,    4,    5,    3,    3,    3,    3,    3,    3,    0,
    2,    2,    2,    1,
};
const short yydefred[] = {                                      0,
   79,    0,    0,    0,    0,    0,    2,    0,    4,    5,
    6,    7,    0,   78,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,   81,   77,   80,    0,
    0,    0,    0,    0,    0,   84,   85,   86,   87,   88,
   89,   94,    0,    8,   39,   38,   64,   68,    0,   63,
    0,   65,    0,    0,   69,   70,   66,   67,   45,    0,
    0,    0,   40,   46,    0,    0,   41,    0,    0,    0,
   11,    0,   93,   91,   92,   82,    0,    0,    0,    0,
    0,    0,    0,   71,   73,   72,    0,    0,    0,    0,
    0,   34,    0,    0,   35,    0,    0,    0,    0,    0,
   12,   24,   83,    9,    0,    0,   74,    0,    0,    0,
   52,    0,    0,   42,    0,    0,   57,   58,   60,    0,
    0,    0,    0,    0,    0,    0,    0,   25,    0,    0,
   49,    0,    0,   50,    0,    0,   44,   48,    0,   47,
    0,    0,    0,    0,   27,   28,   29,    0,   30,    0,
    0,   75,    0,    0,   43,   62,    0,    0,   22,    0,
   16,   17,   18,    0,   20,   13,    0,    0,   54,    0,
   53,   51,    0,    0,    0,    0,    0,    0,    0,   31,
   76,    0,   23,   14,   21,    0,    0,    0,    0,   26,
   15,
};
const short yydgoto[] = {                                       6,
  122,  120,   62,   63,   64,   65,   66,   67,   87,   44,
   35,  107,  108,    7,    8,    9,   10,   11,   12,   70,
  100,   71,  164,  160,  165,  102,  148,  179,  149,   13,
   14,
};
const short yysindex[] = {                                    -35,
    0, -248, -245, -252, -221,    0,    0,  -35,    0,    0,
    0,    0,  -54,    0,  -10,    2,   29,  -44,   27,   32,
   33,   37,   38,   39,  -56,    0,    0,    0,    0,  -24,
 -124, -150,   89, -235,   43,    0,    0,    0,    0,    0,
    0,    0, -121,    0,    0,    0,    0,    0,   98,    0,
   99,    0,  100,  101,    0,    0,    0,    0,    0,  102,
 -249,   23,    0,    0,  103,  104,    0,   86, -164, -250,
    0,   53,    0,    0,    0,    0,   85,  -24,   25,  -24,
 -109,  109,  -43,    0,    0,    0,   58,  -24,  -24,  -24,
  -24,    0,  -85,  -24,    0,   91,   92,   93,  115, -129,
    0,    0,    0,    0,   30, -101,    0,  -27,   36,   55,
    0,   89,   66,    0,   12,   12,    0,    0,    0,   57,
   42,   59,   42,  118,  120,  -96, -205,    0,  -95,  119,
    0,   25,  -93,    0,  -92,   72,    0,    0,  -46,    0,
  -24,  -94, -162,  110,    0,    0,    0,  -33,    0,  127,
  -87,    0,  130,  133,    0,    0,   42,   42,    0,  -18,
    0,    0,    0,   61,    0,    0, -167, -205,    0,   50,
    0,    0,  -94,  -84,  124, -162,    0,  134,  147,    0,
    0,   63,    0,    0,    0, -163,  135,  136,    0,    0,
    0,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,  189,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  106,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  106,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  106,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  106,    0,    0,    5,   17,    0,    0,    0,    0,
   65,    0,   67,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   69,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   71,   73,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   75,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   77,    0,
    0,
};
const short yygindex[] = {                                      0,
    0,    0,  -70,    0,    0,    0,    0,    0,    0,  153,
  -26,   68,    0,  193,    0,    0,    0,    0,    0,    0,
    0,  137,    0,   31,   34,  105,   49,    0, -153,    0,
  190,
};
#define YYTABLESIZE 271
const short yytable[] = {                                       5,
   10,   34,   34,   43,   28,   61,   72,  105,   18,  109,
  168,   83,   15,  131,  180,   17,  132,  115,  116,  117,
  118,   73,  121,  123,  167,  174,   19,   20,   21,   84,
   85,   86,  180,   69,   99,   10,    4,   74,   75,  173,
   22,   23,   24,   16,   61,   55,   25,   55,   55,   55,
   30,  145,  146,   90,  147,    4,  113,   56,   91,   56,
   56,   56,   31,   55,   90,   88,   61,   89,  157,   91,
  158,   90,   88,  129,   89,   56,   91,   90,   88,  133,
   89,   92,   91,   90,   88,  136,   89,   32,   91,  177,
  146,   10,  147,  189,  146,  134,  147,  138,  135,  140,
  139,  175,  141,  188,  176,   59,  174,   36,   59,   19,
   36,   61,   19,   37,   61,   32,   37,   33,   27,   36,
   27,   96,   97,   98,   37,   38,  161,  162,  163,   39,
   40,   41,   68,   69,   34,   76,   42,   78,   79,   80,
   81,   82,   93,   94,   95,  103,  104,  106,  110,  111,
  114,  124,  125,  126,  127,   99,  130,  142,  137,  143,
  144,  150,  151,  153,  155,  154,  159,  169,  166,  170,
  171,   45,   46,  172,  181,  119,  183,  186,   47,   48,
   49,   50,  184,   51,   52,   53,   54,  187,    1,   55,
   56,   57,   58,  190,  191,   77,   59,   60,   90,  152,
   26,   42,   29,  182,  128,    0,  101,   27,    0,  185,
   45,   46,   33,  112,  156,  178,    0,   47,   48,   49,
   50,    0,   51,   52,   53,   54,    1,    2,   55,   56,
   57,   58,   45,   46,    3,   59,   60,    0,    0,   47,
   48,   49,   50,    0,   51,   52,   53,   54,    0,    0,
   55,   56,   57,   58,    0,    0,    0,   59,   60,    0,
    0,    0,   10,   10,    0,    0,    0,    0,    0,    0,
   10,
};
const short yycheck[] = {                                      35,
    0,   46,   46,   60,   59,   91,   33,   78,  261,   80,
   44,  261,  261,   41,  168,  261,   44,   88,   89,   90,
   91,  257,   93,   94,   58,   44,  279,  280,  281,  279,
  280,  281,  186,  284,  285,   35,   91,  273,  274,   58,
  293,  294,  295,  292,   91,   41,  268,   43,   44,   45,
   61,  257,  258,   42,  260,   91,   83,   41,   47,   43,
   44,   45,   61,   59,   42,   43,   91,   45,  139,   47,
  141,   42,   43,   44,   45,   59,   47,   42,   43,   44,
   45,   59,   47,   42,   43,  112,   45,   59,   47,  257,
  258,   91,  260,  257,  258,   41,  260,   41,   44,   41,
   44,   41,   44,   41,   44,   41,   44,   41,   44,   41,
   44,   41,   44,   41,   44,   41,   44,   41,   44,   93,
   44,  286,  287,  288,   93,   93,  289,  290,  291,   93,
   93,   93,  257,  284,   46,   93,  258,   40,   40,   40,
   40,   40,   40,   40,   59,   93,   62,  123,  258,   41,
   93,   61,   61,   61,   40,  285,  258,   40,   93,   40,
  257,  257,   44,  257,   93,  258,  261,   41,   59,  257,
   41,  257,  258,   41,  125,  261,  261,   44,  264,  265,
  266,  267,   59,  269,  270,  271,  272,   41,    0,  275,
  276,  277,  278,   59,   59,   43,  282,  283,   93,  132,
    8,  258,   13,  173,  100,   -1,   70,  262,   -1,  176,
  257,  258,  257,  257,  261,  167,   -1,  264,  265,  266,
  267,   -1,  269,  270,  271,  272,  262,  263,  275,  276,
  277,  278,  257,  258,  270,  282,  283,   -1,   -1,  264,
  265,  266,  267,   -1,  269,  270,  271,  272,   -1,   -1,
  275,  276,  277,  278,   -1,   -1,   -1,  282,  283,   -1,
   -1,   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
  270,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 298
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'#'",0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,
0,0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"'['",0,"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TOK_INT","TOK_LITERAL",
"TOK_PATH","TOK_DECIMAL","TOK_ID","TOK_SQL","KW_DEFINE","KW_RANDOM",
"KW_UNIFORM","KW_RANGE","KW_DATE","KW_INCLUDE","KW_TEXT","KW_DIST","KW_LIST",
"KW_ROWCOUNT","KW_BEGIN","KW_END","KW_SALES","KW_RETURNS","KW_DISTMEMBER",
"KW_DISTWEIGHT","KW_QUERY","KW_STREAM","KW_TEMPLATE","KW_SCALE","KW_SCALE_STEP",
"KW_SET","KW_ADD","KW_NAMES","KW_TYPES","KW_WEIGHTS","KW_INT","KW_VARCHAR",
"KW_DECIMAL","KW_LIMIT","KW_LIMITA","KW_LIMITB","KW_LIMITC","WITH","UMINUS",
"TCAST",
};
const char * const yyrule[] = {
"$accept : workload_spec",
"workload_spec : statement_list",
"statement_list : statement",
"statement_list : statement_list statement",
"statement : include_statement",
"statement : define_statement",
"statement : query_statement",
"statement : dist_statement",
"include_statement : '#' KW_INCLUDE path",
"include_statement : '#' KW_INCLUDE '<' path '>'",
"dist_statement : KW_DIST TOK_ID ';' dist_argument_list dist_members_list",
"dist_argument_list : dist_argument",
"dist_argument_list : dist_argument_list dist_argument",
"dist_argument : KW_SET KW_WEIGHTS '=' TOK_INT ';'",
"dist_argument : KW_SET KW_TYPES '=' '(' dist_type_list ')' ';'",
"dist_argument : KW_SET KW_NAMES '=' '(' dist_name_list ':' dist_name_list ')' ';'",
"dist_type : KW_INT",
"dist_type : KW_VARCHAR",
"dist_type : KW_DECIMAL",
"dist_type_list :",
"dist_type_list : dist_type",
"dist_type_list : dist_type_list ',' dist_type",
"dist_name_list : TOK_ID",
"dist_name_list : dist_name_list ',' TOK_ID",
"dist_members_list : dist_member",
"dist_members_list : dist_members_list dist_member",
"dist_member : KW_ADD '(' dist_value_list ':' dist_weight_list ')' ';'",
"dist_value : TOK_INT",
"dist_value : TOK_LITERAL",
"dist_value : TOK_DECIMAL",
"dist_value_list : dist_value",
"dist_value_list : dist_value_list ',' dist_value",
"dist_weight_list : TOK_INT",
"dist_weight_list : dist_value_list ',' TOK_INT",
"define_statement : KW_DEFINE TOK_ID '=' expr ';'",
"define_statement : KW_DEFINE KW_LIMIT '=' TOK_INT ';'",
"comma_expr_list : expr",
"comma_expr_list : comma_expr_list ',' expr",
"expr : TOK_LITERAL",
"expr : TOK_INT",
"expr : function_call",
"expr : keyword_expr",
"expr : '[' keyword_value ']'",
"expr : '[' TOK_ID TOK_INT opt_substitution_suffix ']'",
"expr : '[' TOK_ID opt_substitution_suffix ']'",
"expr : KW_SCALE",
"expr : arithmetic_expr",
"function_call : function_name '(' comma_expr_list ')'",
"function_call : dist_function_name '(' dist_expr_list ')'",
"function_call : KW_TEXT '(' replacement_list ')'",
"function_call : KW_ROWCOUNT '(' TOK_LITERAL ')'",
"function_call : KW_ROWCOUNT '(' TOK_LITERAL ',' TOK_LITERAL ')'",
"function_call : KW_SCALE_STEP '(' ')'",
"function_call : KW_LIST '(' expr ',' TOK_INT ')'",
"function_call : KW_RANGE '(' expr ',' TOK_INT ')'",
"arithmetic_expr : expr '+' expr",
"arithmetic_expr : expr '-' expr",
"arithmetic_expr : expr '*' expr",
"arithmetic_expr : expr '/' expr",
"dist_expr_list : expr",
"dist_expr_list : TOK_ID",
"dist_expr_list : dist_expr_list ',' expr",
"dist_expr_list : dist_expr_list ',' TOK_ID",
"function_name : KW_DATE",
"function_name : KW_RANDOM",
"dist_function_name : KW_DIST",
"dist_function_name : KW_DISTMEMBER",
"dist_function_name : KW_DISTWEIGHT",
"keyword_expr : KW_UNIFORM",
"keyword_expr : KW_SALES",
"keyword_expr : KW_RETURNS",
"keyword_value : KW_QUERY",
"keyword_value : KW_TEMPLATE",
"keyword_value : KW_STREAM",
"replacement_list : replacement",
"replacement_list : replacement_list ',' replacement",
"replacement : '{' TOK_LITERAL ',' TOK_INT '}'",
"query_statement : query_component_list ';'",
"query_component_list : substitution",
"query_component_list : TOK_SQL",
"query_component_list : query_component_list substitution",
"query_component_list : query_component_list TOK_SQL",
"substitution : '[' TOK_ID opt_substitution_suffix ']'",
"substitution : '[' TOK_ID TOK_INT opt_substitution_suffix ']'",
"substitution : '[' KW_QUERY ']'",
"substitution : '[' KW_STREAM ']'",
"substitution : '[' KW_TEMPLATE ']'",
"substitution : '[' KW_LIMITA ']'",
"substitution : '[' KW_LIMITB ']'",
"substitution : '[' KW_LIMITC ']'",
"opt_substitution_suffix :",
"opt_substitution_suffix : '.' KW_BEGIN",
"opt_substitution_suffix : '.' KW_END",
"opt_substitution_suffix : '.' TOK_INT",
"path : TOK_LITERAL",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 545 "qgen.y"


#line 454 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 146 "qgen.y"
{
							AddQuerySegment(pCurrentQuery, "\n");
							AddQuerySubstitution(pCurrentQuery, "_END", 0, 0);
							AddQuerySegment(pCurrentQuery, "\n");
						}
break;
case 3:
#line 155 "qgen.y"
{
							if (is_set("DEBUG"))
							{
								if (yyvsp[0].intval != KW_DEFINE)
								{
									printf("STATUS: parsed %s statement at line %d\n", 
										(yyvsp[0].intval == TOK_SQL)?"SQL":KeywordText(yyvsp[0].intval), pCurrentFile->line_number);
								}
							}
						}
break;
case 4:
#line 167 "qgen.y"
{yyval.intval = KW_INCLUDE; }
break;
case 5:
#line 168 "qgen.y"
{yyval.intval = KW_DEFINE; }
break;
case 6:
#line 169 "qgen.y"
{yyval.intval = TOK_SQL; }
break;
case 7:
#line 170 "qgen.y"
{yyval.intval = KW_DIST; }
break;
case 8:
#line 179 "qgen.y"
{
					if (include_file(yyvsp[0].strval, pCurrentQuery) < 0)
						yyerror("File include failed");
					}
break;
case 9:
#line 184 "qgen.y"
{
					yywarn("System include not supported; using relative pathing");
					if (include_file(yyvsp[-1].strval, pCurrentQuery) < 0)
						yyerror("File include failed");
					}
break;
case 34:
#line 245 "qgen.y"
{
						defineSubstitution(pCurrentQuery, yyvsp[-3].strval, yyvsp[-1].exprval);
						if (is_set("DEBUG"))
							printf("STATUS: DEFINED %s\n", yyvsp[-3].strval);
						}
break;
case 35:
#line 251 "qgen.y"
{
						pSub = findSubstitution(pCurrentQuery, "_LIMIT", 0);
						sprintf(tmpstr, "%d", yyvsp[-1].intval);
						ResetBuffer(pSub->pAssignment->Value.pBuf);
						AddBuffer(pSub->pAssignment->Value.pBuf, tmpstr);
						if (is_set("DEBUG"))
							printf("STATUS: SET LIMIT\n");
						}
break;
case 36:
#line 263 "qgen.y"
{
						yyval.list = makeList(L_FL_TAIL, NULL);
						addList(yyval.list, yyvsp[0].exprval);
						}
break;
case 37:
#line 268 "qgen.y"
{
						addList(yyvsp[-2].list, yyvsp[0].exprval);
						yyval.list = yyvsp[-2].list;
						}
break;
case 38:
#line 275 "qgen.y"
{
						yyval.exprval = MakeStringConstant(yyvsp[0].strval);
						}
break;
case 39:
#line 279 "qgen.y"
{
						yyval.exprval = MakeIntConstant(yyvsp[0].intval);
						}
break;
case 41:
#line 284 "qgen.y"
{
						yyval.exprval = MakeIntConstant(yyvsp[0].intval);
						yyval.exprval->nFlags |= EXPR_FL_KEYWORD;
						}
break;
case 42:
#line 289 "qgen.y"
{
						yyval.exprval = getKeywordValue(yyvsp[-1].intval);
						}
break;
case 43:
#line 293 "qgen.y"
{
						yyval.exprval = MakeVariableReference(yyvsp[-3].strval, yyvsp[-2].intval);
						}
break;
case 44:
#line 297 "qgen.y"
{
						yyval.exprval = MakeVariableReference(yyvsp[-2].strval, yyvsp[-1].intval);
						}
break;
case 45:
#line 301 "qgen.y"
{
						yyval.exprval = MakeIntConstant(get_int("SCALE"));
						}
break;
case 47:
#line 308 "qgen.y"
{
						yyval.exprval = MakeFunctionCall(yyvsp[-3].intval, yyvsp[-1].list);
						}
break;
case 48:
#line 312 "qgen.y"
{
						yyval.exprval = MakeFunctionCall(yyvsp[-3].intval, yyvsp[-1].list);
						}
break;
case 49:
#line 316 "qgen.y"
{
						yyval.exprval = MakeFunctionCall(KW_TEXT, yyvsp[-1].list);
						}
break;
case 50:
#line 320 "qgen.y"
{
						i = GetTableNumber(yyvsp[-1].strval);
						if (i == -1)
						{
							i = distsize(yyvsp[-1].strval);
							if (i == -1)
								ReportError(QERR_BAD_NAME, yyvsp[-1].strval, 1);
						}
						else
							i = getIDCount(i);
						yyval.exprval = MakeIntConstant(i);
						}
break;
case 51:
#line 333 "qgen.y"
{
						/* TODO: Need to convert this to DSS_HUGE */
						i = GetTableNumber(yyvsp[-3].strval);
						if (i == -1)
						{
							i = distsize(yyvsp[-3].strval);
							if (i == -1)
								ReportError(QERR_BAD_NAME, yyvsp[-3].strval, 1);
						}
						j = GetTableNumber(yyvsp[-1].strval);
						if (i == -1)
							ReportError(QERR_BAD_NAME, yyvsp[-1].strval, 1);
						i = (int)getIDCount(i);
						j = (int)getIDCount(j);
						yyval.exprval = MakeIntConstant((i>j)?j:i);
						}
break;
case 52:
#line 350 "qgen.y"
{
						yyval.exprval = MakeIntConstant(getScaleSlot(get_int("SCALE")) + 1);
						}
break;
case 53:
#line 354 "qgen.y"
{
						yyval.exprval = MakeListExpr(KW_LIST, yyvsp[-3].exprval, yyvsp[-1].intval);
						}
break;
case 54:
#line 358 "qgen.y"
{
						yyval.exprval = MakeListExpr(KW_RANGE, yyvsp[-3].exprval, yyvsp[-1].intval);
						}
break;
case 55:
#line 364 "qgen.y"
{
						yyval.exprval = makeArithmeticExpr(OP_ADD, yyvsp[-2].exprval, yyvsp[0].exprval);
						}
break;
case 56:
#line 368 "qgen.y"
{
						yyval.exprval = makeArithmeticExpr(OP_SUBTRACT, yyvsp[-2].exprval, yyvsp[0].exprval);
						}
break;
case 57:
#line 372 "qgen.y"
{
						yyval.exprval = makeArithmeticExpr(OP_MULTIPLY, yyvsp[-2].exprval, yyvsp[0].exprval);
						}
break;
case 58:
#line 376 "qgen.y"
{
						yyval.exprval = makeArithmeticExpr(OP_DIVIDE, yyvsp[-2].exprval, yyvsp[0].exprval);
						}
break;
case 59:
#line 381 "qgen.y"
{
						yyval.list = makeList(L_FL_TAIL, NULL);
						addList(yyval.list, yyvsp[0].exprval);
						}
break;
case 60:
#line 386 "qgen.y"
{
						yyval.list = makeList(L_FL_TAIL, NULL);
						addList(yyval.list, MakeStringConstant(yyvsp[0].strval));
						}
break;
case 61:
#line 391 "qgen.y"
{
						addList(yyvsp[-2].list, yyvsp[0].exprval);
						yyval.list = yyvsp[-2].list;
						}
break;
case 62:
#line 396 "qgen.y"
{
						addList(yyvsp[-2].list, MakeStringConstant(yyvsp[0].strval));
						yyval.list = yyvsp[-2].list;
						}
break;
case 63:
#line 402 "qgen.y"
{yyval.intval = KW_DATE;}
break;
case 64:
#line 403 "qgen.y"
{yyval.intval = KW_RANDOM;}
break;
case 65:
#line 406 "qgen.y"
{yyval.intval = KW_DIST;}
break;
case 66:
#line 407 "qgen.y"
{yyval.intval = KW_DISTMEMBER;}
break;
case 67:
#line 408 "qgen.y"
{yyval.intval = KW_DISTWEIGHT;}
break;
case 68:
#line 411 "qgen.y"
{yyval.intval = KW_UNIFORM;}
break;
case 69:
#line 412 "qgen.y"
{yyval.intval = KW_SALES;}
break;
case 70:
#line 413 "qgen.y"
{yyval.intval = KW_RETURNS;}
break;
case 71:
#line 416 "qgen.y"
{yyval.intval = KW_QUERY;}
break;
case 72:
#line 417 "qgen.y"
{yyval.intval = KW_TEMPLATE;}
break;
case 73:
#line 418 "qgen.y"
{yyval.intval = KW_STREAM;}
break;
case 74:
#line 422 "qgen.y"
{
						yyval.list = makeList(L_FL_TAIL, NULL);
						addList(yyval.list, yyvsp[0].exprval);
						}
break;
case 75:
#line 427 "qgen.y"
{
						addList(yyval.list, yyvsp[0].exprval);
						yyval.list = yyvsp[-2].list;
						}
break;
case 76:
#line 434 "qgen.y"
{
						yyval.exprval = MakeReplacement(yyvsp[-3].strval, yyvsp[-1].intval);
						}
break;
case 77:
#line 447 "qgen.y"
{
							pSegment = getTail(pCurrentQuery->SegmentList);
							pSegment->flags |= QS_EOS;
							}
break;
case 79:
#line 456 "qgen.y"
{
							if ((nRetCode = AddQuerySegment(pCurrentQuery, yyvsp[0].strval)) != 0)
								yyerror("SQL parse failed");
							}
break;
case 81:
#line 463 "qgen.y"
{
							if ((nRetCode = AddQuerySegment(pCurrentQuery, yyvsp[0].strval)) != 0)
								yyerror("SQL parse failed");
							}
break;
case 82:
#line 470 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, yyvsp[-2].strval, 0, yyvsp[-1].intval)) < 0)
								{
								sprintf(tmpstr, "Substitution match failed on %s", yyvsp[-2].strval);
								yyerror(tmpstr);
								}
						}
break;
case 83:
#line 478 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, yyvsp[-3].strval, yyvsp[-2].intval, yyvsp[-1].intval)) < 0)
								{
								sprintf(tmpstr, "Substitution match failed on %s", yyvsp[-3].strval);
								yyerror(tmpstr);
								}
						}
break;
case 84:
#line 486 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_QUERY", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 85:
#line 493 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_STREAM", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 86:
#line 500 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_TEMPLATE", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 87:
#line 507 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITA", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 88:
#line 514 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITB", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 89:
#line 521 "qgen.y"
{
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITC", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
break;
case 90:
#line 529 "qgen.y"
{yyval.intval = 0;}
break;
case 91:
#line 530 "qgen.y"
{yyval.intval = 0;}
break;
case 92:
#line 531 "qgen.y"
{yyval.intval = 1;}
break;
case 93:
#line 532 "qgen.y"
{yyval.intval = yyvsp[0].intval;}
break;
case 94:
#line 540 "qgen.y"
{ yyval.strval = yyvsp[0].strval; }
break;
#line 1078 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
