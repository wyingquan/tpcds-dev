/*
* $Id: text.c,v 1.5 2007/08/02 18:56:30 jms Exp $
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
* $Log: text.c,v $
* Revision 1.5  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.4  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.3  2005/02/21 23:25:53  jms
* Porting corrections
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.2  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "decimal.h"
#include "date.h"
#include "genrand.h"
#include "dist.h"

/*
 * Routine: mk_sentence()
 * Purpose: create a sample sentence
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
static int used_space = 0; /* current length of the sentence being built */
#define SPACE_INCREMENT	100

static char *
mk_sentence(int stream)
{
	static char *verbiage = NULL;
	static int allocated_space = 0;
	int word_len;
	char *syntax, 
		*cp,
		*word = NULL,
		temp[2];

	temp[1] = '\0';
	pick_distribution(&syntax, "sentences", 1, 1, stream);

	for (cp = syntax; *cp; cp++)
	{
		switch(*cp)
		{
		case 'N':	/* pick a noun */
			pick_distribution(&word, "nouns", 1, 1, stream);
			break;
		case 'V':	/* pick a verb */
			pick_distribution(&word, "verbs", 1, 1, stream);
			break;
		case 'J':	/* pick a adjective */
			pick_distribution(&word, "adjectives", 1, 1, stream);
			break;
		case 'D':	/* pick a adverb */
			pick_distribution(&word, "adverbs", 1, 1, stream);
			break;
		case 'X':	/* pick a auxiliary verb */
			pick_distribution(&word, "auxiliaries", 1, 1, stream);
			break;
		case 'P':	/* pick a preposition */
			pick_distribution(&word, "prepositions", 1, 1, stream);
			break;
		case 'A':	/* pick an article */
			pick_distribution(&word, "articles", 1, 1, stream);
			break;
		case 'T':	/* pick an terminator */
			pick_distribution(&word, "terminators", 1, 1, stream);
			break;
		default:
			temp[0] = *cp;
			break;
		}

		if (word == NULL)
			word_len = 1;
		else
			word_len = strlen(word);
		
		if (used_space + word_len >= allocated_space)
			{
			verbiage = (char *)realloc(verbiage, allocated_space + SPACE_INCREMENT);
			MALLOC_CHECK(verbiage);
			allocated_space += SPACE_INCREMENT;
			}
		
		if (word == NULL)
			strcpy(&verbiage[used_space], temp);
		else
			strcpy(&verbiage[used_space], word);
		used_space += word_len;
		word = NULL;
	}

	return(verbiage);
}

	




/*
 * Routine: gen_text()
 * Purpose: entry point for this module. Generate a truncated sentence in a
 *			given length range
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
char *
gen_text(char *dest, int min, int max, int stream)
{
	int target_len,
		generated_length,
		capitalize = 1;
	char *s;

	used_space = 0;
	genrand_integer(&target_len, DIST_UNIFORM, min, max, 0, stream);
	if (dest)
		*dest = '\0';
	else
	{
		dest = (char *)malloc((max + 1) * sizeof(char));
		MALLOC_CHECK(dest);
	}


	while (target_len > 0)
		{
		used_space = 0;
		s = mk_sentence(stream);
		if (capitalize)
			*s = toupper(*s);
		generated_length = strlen(s);
		capitalize = (s[generated_length - 1] == '.');
		if (target_len <= generated_length)
			s[target_len] = '\0';
		strcat(dest, s);
		target_len -= generated_length;
		if (target_len > 0)
			{
			strcat(dest, " ");
			target_len -= 1;
			}
		}
	
	return(dest);
}

#ifdef TEST
#define DECLARER
#include "r_driver.h"
#include "r_params.h"

typedef struct {char *name;} tdef;
/* tdef tdefs[] = {NULL}; */


option_t options[] =
{

{"DISTRIBUTIONS", OPT_STR, 0, NULL, NULL, "tester_dist.idx"}, 
NULL
};

char *params[2];

main()
{
	char test_dest[201];
	int i;

	init_params();

	for (i=0; i < 100; i++)
		{
		gen_text(test_dest, 100, 200, 1);
		printf("%s\n", test_dest);
		test_dest[0] = '\0';
		}

	return(0);
}
#endif
