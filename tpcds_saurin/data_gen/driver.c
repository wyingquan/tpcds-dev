/*
* $Id: driver.c,v 1.35 2007/12/12 23:42:26 jms Exp $
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
* $Log: driver.c,v $
* Revision 1.35  2007/12/12 23:42:26  jms
* required -update option
*
* Revision 1.34  2007/11/27 00:18:50  jms
* bug 576
*
* Revision 1.33  2007/10/31 17:20:35  jms
* don't build del* files unless updates are being built
*
* Revision 1.32  2007/10/09 21:58:01  jms
* Add command line seeding for validate option
*
* Revision 1.31  2007/10/02 16:28:34  jms
* add -DJMS fixed seed for validation
*
* Revision 1.30  2007/08/29 19:10:25  jms
* Bug 545
*
* Revision 1.29  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.28  2007/07/24 19:51:19  jms
* bug 546
*
* Revision 1.27  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.26  2007/05/23 21:35:57  jms
* TPCDS Bug 546
*
* Revision 1.25  2007/05/23 19:52:03  jms
* TPCDS Bug 546
*
* Revision 1.24  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.23  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.22  2006/11/17 19:59:07  jms
* Checkin for 47 (redo to address sync issues)
*
* Revision 1.21  2006/10/17 22:38:46  jms
* bug 482
*
* Revision 1.20  2006/10/13 23:37:35  jms
* Bug 308: rework date-based tables to focus on orders
*
* Revision 1.19  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.18  2006/08/18 23:18:06  jms
* Bug #475
*
* Revision 1.17  2006/06/07 19:55:36  jms
* checkin of revised update scaling
*
* Revision 1.16  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.15  2006/04/11 16:45:16  jms
* Correct naming of child tables in verbose output
*
* Revision 1.14  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.13  2006/03/01 00:22:39  jms
* Bug 397: catalog_sales dates are generated for 2003
*
* Revision 1.12  2006/02/02 05:06:09  jms
* scale factor aware qgen
*
* Revision 1.11  2006/01/16 23:13:44  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.10  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.9  2006/01/02 19:39:49  jms
* Bug 357: segfault when building updates
*
* Revision 1.8  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.7  2005/10/06 22:11:28  jms
* bug #308: chunked data error. Add skipDays() to adjust date values
*
* Revision 1.6  2005/10/05 20:01:44  jms
* bug #308: chunked data error. Add skipDate() to adjust date values
*
* Revision 1.5  2005/10/05 17:31:35  jms
* bug #239: need data validation method
*
* Revision 1.4  2005/10/04 16:23:33  jms
* Misc cleanup:
* remove un-needed casts
* open DOS files wth WT instead of W
*
* Revision 1.3  2005/07/20 22:48:25  jms
* add data validation
* relocate dateScaling
*
* [ file log truncated at 1/1/2005 as of 17 Feb 2006 ]
*/
#define DECLARER
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef WIN32
#include <process.h>
#include <direct.h>
#endif
#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include "config.h"
#include "date.h"
#include "decimal.h"
#include "genrand.h"
#include "tdefs.h"
#include "tdef_functions.h"
#include "build_support.h"
#include "params.h"
#include "parallel.h"
#include "tables.h"
#include "release.h"
#include "scaling.h"
#include "load.h"
#include "error_msg.h"
#include "print.h"
#include "release.h"
#include "tpcds.idx.h"
#include "grammar_support.h" /* to get definition of file_ref_t */
#include "address.h" /* for access to resetCountyCount() */
#include "scd.h"


extern int optind, opterr;
extern char *optarg;
/* extern tdef w_tdefs[], s_tdefs[]; */
char g_szCommandLine[201];
file_ref_t CurrentFile;
file_ref_t *pCurrentFile;


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
ds_key_t
skipDays(int nTable, ds_key_t *pRemainder)
{
	static int bInit = 0;
   static date_t BaseDate;
   ds_key_t jDate;
	ds_key_t kRowCount,
		kFirstRow,
      kDayCount,
      index = 1;

   if (!bInit)
   {
      strtodt(&BaseDate, DATA_START_DATE);
      bInit = 1;
      *pRemainder = 0;
   }
	
   // set initial conditions
   jDate = BaseDate.julian;
  *pRemainder = dateScaling(nTable, jDate) + index;

  // now check to see if we need to move to the 
  // the next peice of a parallel build
  // move forward one day at a time
  split_work(nTable, &kFirstRow, &kRowCount);
  while (index < kFirstRow)
  {
     kDayCount = dateScaling(nTable, jDate);
     index += kDayCount;
     jDate += 1;
     *pRemainder = index;
  }
  if (index > kFirstRow)
  {
     jDate -= 1;
  }
	
	return(jDate);
}


/*
* Routine: find_table(char *, char *)
* Purpose: partial match routine for arguments to -T
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
find_table(char *szParamName, char *tname)
{
	int i,
		res = -1,
		nNotSure = -1;
   tdef *pT;
   tdef *pN;
	
	if (!strcmp(tname, "ALL"))
		return(0);
	
	for (i=0; i <= MAX_TABLE; i++)
	{
      pT = getSimpleTdefsByNumber(i);
		if (strcasecmp(szParamName, "ABREVIATION"))
		{
			/* if we match the name exactly, then return the result */
			if (!strcasecmp(tname, pT->name))
				return(i);
			
			/* otherwise, look for sub-string matches */
			if (!strncasecmp(tname, pT->name, strlen(tname)) )
			{
				if (res == -1)
					res = i;
				else
					nNotSure = i;
			}
		}
		else
		{
			if (!strcasecmp(tname, pT->abreviation))
				return(i);
		}
	}
	
	if (res == -1)
	{
		fprintf(stdout, 
			"ERROR: No match found for table name '%s'\n", tname);
		exit(1);
	}

   pT = getSimpleTdefsByNumber(res);
	if ((nNotSure != -1) && !(pT->flags & FL_DUP_NAME))
	{
      pN = getSimpleTdefsByNumber(nNotSure);
		fprintf(stdout, 
		"WARNING: Table name '%s' not unique. Could be '%s' or '%s'. Assuming '%s'\n", 
		tname, pT->name, pN->name, pT->name);
		pT->flags |= FL_DUP_NAME;
	}
	
	return(res);
	
}
/*
* re-set default output file names 
*/
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
set_files (int i)
{
	char line[80], *new_name;
   tdef *pT = getSimpleTdefsByNumber(i);
	
	printf ("Enter new destination for %s data: ",
		pT->name);
	if (fgets (line, sizeof (line), stdin) == NULL)
		return (-1);
	if ((new_name = strchr (line, '\n')) != NULL)
		*new_name = '\0';
	if (strlen (line) == 0)
		return (0);
	new_name = (char *) malloc (strlen (line) + 1);
	MALLOC_CHECK (new_name);
	strcpy (new_name, line);
	pT->name = new_name;
	
	return (0);
}

/*
* generate a particular table
*/
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
* TODO: 20011217 JMS need to build date-correlated (i.e. fact) tables in proper order
*/
void
gen_tbl (int tabid, ds_key_t kFirstRow, ds_key_t kRowCount)
{
	int direct,
		bIsVerbose,
		nLifeFreq,
		nMultiplier,
      nChild;
	ds_key_t i,
		kTotalRows;
   tdef *pT = getSimpleTdefsByNumber(tabid);
   tdef *pC;
   table_func_t *pF = getTdefFunctionsByNumber(tabid);
	
	kTotalRows = kRowCount;
	direct = is_set("DBLOAD");
	bIsVerbose = is_set("VERBOSE") && !is_set("QUIET");
	/**
	set the frequency of progress updates for verbose output
	to greater of 1000 and the scale base
	*/
	nLifeFreq = 1;
	nMultiplier = dist_member(NULL, "rowcounts", tabid + 1, 2);
	for (i=0; nLifeFreq < nMultiplier; i++)
		nLifeFreq *= 10;
	if (nLifeFreq < 1000)
		nLifeFreq = 1000;

	if (bIsVerbose)
	{
		if (pT->flags & FL_PARENT)
      {
         nChild = pT->nParam;
         pC = getSimpleTdefsByNumber(nChild);
			fprintf(stderr, "%s %s and %s ... ", 
			(direct)?"Loading":"Writing", 
			pT->name, pC->name);
      }
		else
			fprintf(stderr, "%s %s ... ", 
			(direct)?"Loading":"Writing", 
			pT->name);
	}
		
	/*
    * small tables use a constrained set of geography information
    */
   if (pT->flags & FL_SMALL)
      resetCountCount();
   
   for (i=kFirstRow; kRowCount; i++,kRowCount--)
	{
		if (bIsVerbose && i && (i % nLifeFreq) == 0)
			fprintf(stderr, "%3d%%\b\b\b\b",(int)(((kTotalRows - kRowCount)*100)/kTotalRows));
		
		/* not all rows that are built should be printed. Use return code to deterine output */
		if (!pF->builder(NULL, i))
			if (pF->loader[direct](NULL))
			{
				fprintf(stderr, "ERROR: Load failed on %s!\n", getTableNameByID(tabid));
				exit(-1);
			}
			row_stop(tabid);
	}
	if (bIsVerbose)
			fprintf(stderr, "Done    \n");	
	print_close(tabid);

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
void
validate_options(void)
{
	char msg[1024];

	msg[0] = '\0';
	if (is_set("PARALLEL"))
	{
		if (get_int("PARALLEL") < 2) strcat(msg, "PARALLEL must be >= 2\n");
		if (get_int("CHILD") < 1) strcat(msg, "CHILD must be >= 1\n");
	}

	if (strlen(msg)) usage(NULL, msg);

	return;
}

/*
* MAIN
*
* assumes the existance of getopt() to clean up the command 
* line handling
*/
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
main (int ac, char **av)
{
	int i,
		tabid = -1,
		nCommandLineLength = 0,
		nArgLength;
	char *tname;
	ds_key_t kRowCount,
		kFirstRow,
		kRandomRow,
		kValidateCount;
	struct timeb t;
   tdef *pT;
   table_func_t *pF;
	
	process_options (ac, av);
	validate_options();
	init_rand();

	/* build command line argument string */
	g_szCommandLine[0] = '\0';
	for (i=1; i < ac; i++)
	{
		nArgLength = strlen(av[i]) + 1;
		if ((nCommandLineLength + nArgLength) >= 200)
		{
			ReportError(QERR_CMDLINE_TOO_LONG, NULL, 0);
			break;
		}
		strcat(g_szCommandLine, av[i]);
		strcat(g_szCommandLine, " ");
		nCommandLineLength += nArgLength;
	}

   if (is_set("UPDATE"))
   {
      setUpdateDates();
      setUpdateScaling(S_PURCHASE);
      setUpdateScaling(S_WEB_ORDER);
      setUpdateScaling(S_CATALOG_ORDER);
      setUpdateScaling(S_INVENTORY);
   }
	
	/* if we are using shared memory to pass parameters to/from peers, then read additional
	* parameters here.
	*/
	if (is_set("SHMKEY"))
		load_params();	 
		
	if (!is_set("QUIET"))
	{
		fprintf (stderr,
		"%s Population Generator (Version %d.%d.%d%s)\n",
		get_str("PROG"), VERSION, RELEASE, MODIFICATION, PATCH);
	fprintf (stderr, "Copyright %s %s\n", COPYRIGHT, C_DATES);
	}

	/**
	** actual data generation section starts here
	**/
	
	/*
	* do any global (non-worker thread) initialization
	*/
#ifndef NOLOAD
	if (is_set("DBLOAD"))
		load_init();
#endif /* NOLOAD */
	
	
	
	/***
	* traverse the tables, invoking the appropriate data generation routine 
	* for any to be built; skip any non-op tables or any child tables (their
	* generation routines are called when the parent is built
	*/
	tname = get_str("TABLE");
	if (strcmp(tname, "ALL"))
	{
		tabid = find_table("TABLE", tname);
	}
	else if (is_set("ABREVIATION"))
	{
		tabid = find_table("ABREVIATION", get_str("ABREVIATION"));
	}

	for (i=(is_set("UPDATE"))?S_BRAND:CALL_CENTER; (pT = getSimpleTdefsByNumber(i)); i++)
	{

      if (!pT->name)
         break;
      if (!is_set("UPDATE") && (i == S_BRAND))
         break;

      pF = getTdefFunctionsByNumber(i);

		if (pT->flags & FL_NOP)
		{
			if (tabid == i)
				ReportErrorNoLine(QERR_TABLE_NOP, pT->name, 1);
			continue;	/* skip any tables that are not implemented */	
		}
		if (pT->flags & FL_CHILD)
		{
			if (tabid == i)
				ReportErrorNoLine(QERR_TABLE_CHILD, pT->name, 1);
			continue;	/* children are generated by the parent call */	
		}
		if ((tabid != -1) && (i != tabid))
			continue;	/* only generate a table that is explicitly named */

	/* 
 	 * all source tables require the -update option to be set
	 */
	if ((pT->flags & FL_SOURCE_DDL) && (is_set("UPDATE") == 0))
	{
		ReportErrorNoLine(QERR_TABLE_UPDATE, pT->name, 1);
		continue;	/* update tables require update option */
	}

		
		/*
		 * data validation is a special case 
		 */
		if (is_set("VALIDATE"))
		{
			if (pF->validate == NULL)
				continue;

         kRowCount = get_rowcount(i);

			kValidateCount = get_int("VCOUNT");
			if ((kRowCount > 0) && (kValidateCount > kRowCount))
			{
				kValidateCount = kRowCount;
			}

		if (!is_set("RNGSEED"))
		{
			ftime(&t);
			setSeed(VALIDATE_STREAM, t.millitm);
		} else {
			setSeed(VALIDATE_STREAM, get_int("RNGSEED"));
		}
         print_start(i);

			for (; kValidateCount; kValidateCount--)
			{
				genrand_key(&kRandomRow, DIST_UNIFORM, 1, kRowCount, 0, VALIDATE_STREAM); 
				pF->validate(i, kRandomRow, NULL);
            if (!(pT->flags & FL_VPRINT))
               printValidation(i, kRandomRow);
			}

			print_close(i);
		}
		else
		{
		/**
		 * GENERAL CASE
		 * if there are no rows to build, then loop
		 */
         split_work(i, &kFirstRow, &kRowCount);
         /*
         * if there are rows to skip then skip them 
         */
         if (kFirstRow != 1)
         {
            row_skip(i, (int)(kFirstRow - 1));
            if (pT->flags & FL_PARENT)
               row_skip(pT->nParam, (int)(kFirstRow - 1));
         }
         
         /*
         * now build the actual rows
         */
         gen_tbl(i, kFirstRow, kRowCount);
		}
	}

#ifndef NOLOAD
	if (is_set("DBLOAD"))
		load_close();
#endif
	
	return (0);
}

