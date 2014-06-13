/*
* $Id: grammar.c,v 1.5 2006/05/10 22:03:22 jms Exp $
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
* $Log: grammar.c,v $
* Revision 1.5  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.4  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.3  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.6  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.5  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.6  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.5  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.4  2002/12/04 17:32:59  jms
* Include changes from win2k for porting update
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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "porting.h"
#include "grammar.h"
#include "error_msg.h"
#include "StringBuffer.h"
#include "expr.h"
#include "decimal.h"
#include "date.h"

int nLineNumber = 0;
extern char *CurrentFileName;
token_t *pTokens;
int ProcessOther(char *stmt, token_t *pTokens);


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
char *
ProcessStr (char *stmt, token_t * tokens)
{
   char *cp;

   if ((cp = SafeStrtok (NULL, "\"")) == NULL)
      ReportError (QERR_BAD_STRING, NULL, 1);

   return (cp);
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
int
ProcessComments (char *line)
{
   char *cp;
   int i = 0;

   if (line == NULL)
      return (-1);

   if ((cp = strchr (line, COMMENT_CHAR)) != NULL)
     {
        if (*(cp + 1) == COMMENT_CHAR)
           *cp = '\0';
     }

   cp = line;
   while (*cp && (*cp == ' ' || *cp == '\t' || *cp == '\r'))
     {
        i += 1;
        cp += 1;
     }

   return (i);
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
char *
AddLine (char *line)
{
   static int nCharAllocated = 0;
   static int nCharInUse = 0;
   static char *szResult;
   int nCharAvailable,
     nCharRequested,
     nCharAdditional;

   if (line == NULL)            /*  initialization */
     {
        nCharInUse = 0;
        return (NULL);
     }

   nCharAvailable = nCharAllocated - nCharInUse - 1;
   nCharRequested = strlen (line);

   if (nCharRequested == 0)     /*  asked to add a null line */
      return (szResult);
   nCharRequested += 1; /* add a space between pieces */

   if (nCharAvailable < nCharRequested) /*  need more room */
     {
        nCharAdditional = (nCharRequested > 250) ? nCharRequested : 250;
        szResult =
           (char *) realloc ((void *) szResult,
                             nCharAllocated + nCharAdditional);
        nCharAllocated += 250;
     }

   if (szResult != NULL)
     {
        if (nCharInUse == 0)
           strcpy (szResult, line);
        else
           strcat (szResult, line);
		strcat(szResult, " ");	/* and add the space we reserved room for above */
        nCharInUse += nCharRequested;
     }

   return (szResult);
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
void
SetTokens (token_t * pToken)
{
   pTokens = pToken;

   return;
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
int
FindToken (char *word)
{
   int nRetCode = 0;
   int i;

   /*  Note: linear search should be replaced if the word count gets large */
   for (i = 1; pTokens[i].index != -1; i++)
     {
        if (!strcasecmp (pTokens[i].word, word))
           nRetCode = pTokens[i].index;
     }

   return (nRetCode);
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
int
ParseFile (char *szPath)
{
   FILE *fp;
   char szLine[4096];           /*  is there a good portable constant for this? */
   char *stmt,
    *line_start,
    *cp;
   int i,
     nRetCode = 0;
   StringBuffer_t *pLineBuffer;

   /*  open the template, or return an error */

/*  Gosh, I love non-standard extensions to standard functions! */
#ifdef WIN32
   if ((fp = fopen (szPath, "rt")) == NULL)
#else
   if ((fp = fopen (szPath, "r")) == NULL)
#endif
      return (ReportErrorNoLine(QERR_NO_FILE, szPath, 0));

   /* shift current file indicator for error messages */
   if (CurrentFileName != NULL)
      free (CurrentFileName);
   CurrentFileName = strdup (szPath);
   pLineBuffer = InitBuffer(100, 20);
   nLineNumber = 0;
   SetErrorGlobals(szPath, &nLineNumber);

   while ((fgets (szLine, 4096, fp) != NULL) && (nRetCode >= 0))
     {
        nLineNumber += 1;
        if ((cp = strchr (szLine, '\n')))
           *cp = '\0';
        else
           ReportError (QERR_LINE_TOO_LONG, NULL, 1);

        /*  build a complete statement  */
        i = ProcessComments (szLine);
        if (i < 0)
           return (i);
        line_start = (szLine + i);
        if (strlen (line_start) == 0)
           continue;            /*  nothing to do with an empty line */

        AddBuffer(pLineBuffer, line_start);
        if ((cp = strchr (line_start, STMT_END)) == NULL)
		{
			AddBuffer(pLineBuffer, " ");
           continue;
		}
        if (*(cp - 1) == '\\')
		if ((cp = strchr (cp + 1, STMT_END)) == NULL)
		{
			AddBuffer(pLineBuffer, " ");
           continue;
		}

		/*  
         * NOTE: this assumes that the first word indentifies the statement type 
         */
        stmt = GetBuffer(pLineBuffer);
		cp = SafeStrtok (stmt, " \t");
        i = FindToken (cp);
        if (i != 0)
          {
             if (pTokens[i].handler != NULL)
                nRetCode = pTokens[i].handler (stmt, pTokens);
             else
                nRetCode = -17; /* QERR_SYNTAX; */
          }
        else                    /*  other text (i.e., SQL) possibly with subsitution targets) */
           nRetCode = ProcessOther (stmt, pTokens);

        ResetBuffer(pLineBuffer);
     }

   if (!feof (fp) && (nRetCode >= 0))
      ReportError (QERR_READ_FAILED, szPath, 0);
   if (nRetCode < 0)
	   ReportError(nRetCode, szLine, 0);
	

   fclose (fp);
/* jms -- need to reintroduce this
   FreeBuffer(pLineBuffer);
   */

   return (nRetCode);
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
char *
SafeStrtok (char *string, char *delims)
{
   static char *szScratch = NULL;
   static int nScratchLen = 0;

   if (string != NULL)
     {
        if (szScratch == NULL)
          {
             szScratch = (char *) malloc (strlen (string) + 1);
		MALLOC_CHECK(szScratch);
             if (szScratch == NULL)
                ReportError (QERR_NO_MEMORY, "SafeStrtok", 1);
             else
                nScratchLen = strlen (string);
          }
        else
          {
             if (nScratchLen < (int)strlen (string))
               {
                  szScratch = (char *) realloc (szScratch, strlen (string) + 1);
                  if (szScratch == NULL)
                     ReportError (QERR_NO_MEMORY, "SafeStrtok", 1);
                  else
                     nScratchLen = strlen (string);
               }
          }
        strcpy (szScratch, string);
        return (strtok (szScratch, delims));
     }
   return (strtok (NULL, delims));
}
