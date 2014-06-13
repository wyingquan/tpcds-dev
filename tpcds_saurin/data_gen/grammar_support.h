/*
 * @(#) p_gram_support.h 1.2.1.1@(#)
 */

#ifndef GRAMMAR_SUPPORT_H
#define GRAMMAR_SUPPORT_H
 /*
 * entry in the file stack used to manage multiple input file and include files
 */
typedef struct FILE_REF_T
	{
	FILE 	*file;
	char 	*name;
	int		line_number;
	void	*pContext;
	struct FILE_REF_T *pNext;
#if defined(MKS) || defined(FLEX)
	void *pLexState;
#endif
	} file_ref_t;



extern file_ref_t *pCurrentFile;

int yywarn(char *str);
void yyerror(char *msg, ...);
int setup(void);
int include_file(char *fn, void *pContext);
void GetErrorCounts(int *nError, int *nWarning);
#endif
