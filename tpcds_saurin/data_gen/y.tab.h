#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union {
    int		intval;
    char	*strval;
	expr_t	*exprval;
	list_t  *list;
    } YYSTYPE;
extern YYSTYPE yylval;
