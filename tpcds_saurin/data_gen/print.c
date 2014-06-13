
/*
* $Id: print.c,v 1.30 2007/08/02 18:56:30 jms Exp $
*
* This software contains proprietarF and confidential information of Gradient
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
* $Log: print.c,v $
* Revision 1.30  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.29  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.28  2007/04/26 22:29:45  jms
* TPCDS bug 541
*
* Revision 1.27  2007/01/09 00:25:39  jms
* Bugs 521-523 (delete file format, update file naming)
*
* Revision 1.26  2006/12/06 19:55:21  jms
* fix null hanlding of s_call_center
*
* Revision 1.25  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.24  2006/11/17 23:45:21  jms
* remove reference to errno
*
* Revision 1.23  2006/11/17 19:59:07  jms
* Checkin for 47 (redo to address sync issues)
*
* Revision 1.22  2006/11/01 00:23:50  jms
* Enclose dates in quotes for _MYSQL
*
* Revision 1.21  2006/10/19 22:42:52  jms
* Testing of drop 44
*
* Revision 1.20  2006/10/17 22:38:46  jms
* bug 482
*
* Revision 1.19  2006/10/05 20:11:59  jms
* IBM access() issue
*
* Revision 1.18  2006/08/23 22:13:47  jms
* porting issues
*
* Revision 1.17  2006/08/22 21:48:24  jms
* Bug 485
*
* Revision 1.16  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.15  2006/06/02 19:25:27  jms
* address portability issues with move to fwrite
*
* Revision 1.14  2006/05/12 21:57:29  jms
* porting cleanup
*
* Revision 1.13  2006/05/12 18:08:22  jms
* porting cleanup
*
* Revision 1.12  2006/05/12 17:38:29  jms
* shift to fwrite for performance (per Richard Harlow)
*
* Revision 1.11  2006/05/12 17:09:06  jms
* print routine cleanup (per RIchard Harlow)
*
* Revision 1.10  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.9  2006/04/28 00:24:52  jms
* addition null checking from Solaris
*
* Revision 1.8  2006/03/17 23:29:36  jms
* print the converted value in print_key
*
* Revision 1.7  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.6  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.5  2005/11/06 22:01:12  jms
* first rework of source generation
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
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.28  2004/11/01 17:38:36  jms
* Bug #109: Output error needs error message
*
* Revision 1.27  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
*
* Revision 1.26  2004/06/10 22:38:29  jms
* correct nullCheck calls in print.c routines
*
* Revision 1.25  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.24  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.23  2004/05/21 23:50:20  jms
* release.h
*
* Revision 1.22  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.21  2004/03/27 00:17:10  jms
* correct truncation of child tables
*
* Revision 1.20  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.19  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.23  2003/07/24 16:19:39  jms
* Change web_site date stamps to be actual dates
*
* Revision 1.22  2003/07/14 23:09:17  jms
* correct data set errors found by Doug Johnson
*
* Revision 1.21  2003/05/07 20:06:43  jms
* convert i_flavor to i_color
*
* Revision 1.20  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.19  2003/04/23 23:47:05  jms
* bug 12: unisys table load errors
*
* Revision 1.18  2002/11/07 23:56:47  jms
* changes for DBGEN 1.0.6
*
* Revision 1.17  2002/11/05 06:24:47  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.16  2002/09/26 00:11:47  jms
* Issue 29: Add a link to Household Demographics to Web Sales and Web Returns as in Catalog
*
* Revision 1.15  2002/09/25 23:56:53  jms
* Issue 29: Add a link to Household Demographics to Web Sales and Web Returns as in Catalog
*
* Revision 1.14  2002/09/25 22:54:25  jms
* remove cr_call_center_id and associated join
*
* Revision 1.13  2002/09/25 22:46:59  jms
* commit all open changes to allow tighter issue/change tracking
*
* Revision 1.12  2002/09/11 22:21:10  jms
* Remove rec_start/end_date_id from Customer_Address
*
* Revision 1.11  2002/09/04 18:26:40  jms
* Corrections to catalog page generation
*
* Revision 1.10  2002/09/04 17:17:13  jms
* Covert xx_id from ds_key_t to char[] for business keys
*
* Revision 1.9  2002/08/28 21:57:20  jms
* Chage xx_rec_{start,end}_date_id to data type DATE (sriram, 8/27)
*
* Revision 1.8  2002/08/17 21:33:14  jms
* complete linkage of store/web sales and returns
*
* Revision 1.7  2002/08/16 23:24:22  jms
* complete linkage of catalog sales and returns and clean up parent child handling
*
* Revision 1.6  2002/08/16 19:30:13  jms
* populate web_page
*
* Revision 1.5  2002/08/15 20:49:04  jms
* populate web_site
*
* Revision 1.4  2002/08/13 23:13:08  jms
* porting to Solaris 9
*
* Revision 1.3  2002/07/27 00:08:30  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
*
* Revision 1.2  2002/07/03 21:55:27  jms
* change fields in ship_mode to use distributions instead of random text
* Revision 1.1.1.1.2.5  2002/07/22 22:46:14  jms
* replacing missing changes to align with WAM 10
* corrections to set_pricing() to align with WAM 10
*
* Revision 1.1.1.1.2.4  2002/07/18 23:51:02  jms
* division should be printed as a key
*
* Revision 1.1.1.1.2.3  2002/07/18 22:09:47  jms
* isolating pricing calculations for the sales tables
* sync column names with WAM 10/11
*
* Revision 1.1.1.1.2.2  2002/07/08 17:51:32  jms
* Remove GMT/Custormer date and time from fact tables (sriram 20020708)
*
* Revision 1.1.1.1.2.1  2002/07/04 01:20:59  jms
* Changes requested by Sriram:
* -- c_preferred_cust_flag is now active; set to 50%
* -- cd_purchase_estimate  hd_vehicle_count, hd_dependent_count
*    now integers
* -- flag values now display as "Y" or "N"
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "tables.h"
#include "print.h"
#include "tdef_functions.h"
#include "r_params.h"
#include "date.h"
#include "decimal.h"
#include "tdefs.h"
#include "nulls.h"
#include "constants.h"
#include "build_support.h"

static FILE *fpOutfile = NULL;
static FILE *fpDeleteFile;
static char *arDeleteFiles[3] = {"", "delete_", "inventory_delete_"};

static int current_table = -1;

int print_jdate (FILE *pFile, ds_key_t kValue);

void 
print_close(int tbl)
{
   tdef *pTdef = getSimpleTdefsByNumber(tbl);

	fpOutfile = NULL;
	if (pTdef->outfile)
	{
		fclose(pTdef->outfile);
		pTdef->outfile = NULL;
	}

	if (pTdef->flags & FL_PARENT)
      print_close(pTdef->nParam);

	return;
}

int
print_separator (int sep)
{
	int res = 0;
	static char *pDelimiter;
	static int init = 0;
	
	if (!init)
	{
        pDelimiter = get_str ("DELIMITER");
        init = 1;
	}
	
	if (sep)
	{
		if (fwrite(pDelimiter, 1, 1, fpOutfile) != 1)
		{
			fprintf(stderr, "ERROR: Failed to write delimiter\n");
			exit(-1);
		}
	}
	   
	return (res);
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
FILE *
print_prep (int table, int update)
{
   return (NULL);
}

/*
* Routine: dbg_print()
* Purpose: genralized data print routine
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20000113 need better separator handling
*		20020125 cast to/from 64b is messy, assumes int/pointer are same size
*/
void
print_integer (int nColumn, int val, int sep)
{
	if (!nullCheck(nColumn))
	{
		if (fprintf (fpOutfile, "%d", val) < 0)
		{
			fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
			exit(-1);
		}
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);
	
	return;
}

void
print_varchar (int nColumn, char *val, int sep)
{
	size_t nLength;

	if (!nullCheck(nColumn) && (val != NULL))
	{
      nLength = strlen(val);
		
#ifdef STR_QUOTES
		if ((fwrite ("\"", 1, 1, fpOutfile) != 1) ||
			(fwrite (val, 1, nLength, fpOutfile) != nLength) ||
			(fwrite ("\"", 1, 1, fpOutfile)) != 1)
#else
		if (fwrite (val, 1, nLength, fpOutfile) != nLength)
#endif
			{
				fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
				exit(-1);
			}
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);
	
   return;
}

void
print_delete (int * val)
{
   if (print_jdate(fpDeleteFile, *val))
	{
      fprintf(stderr, "ERROR: Failed to write delete key\n");
      exit(-1);
	}
   fprintf(fpDeleteFile, "%s", get_str("DELIMITER"));
   if (print_jdate(fpDeleteFile, *(val + 1)))
	{
      fprintf(stderr, "ERROR: Failed to write delete key\n");
      exit(-1);
	}
   if (is_set("TERMINATE"))
	   fprintf(fpDeleteFile, get_str("DELIMITER"));
   fprintf(fpDeleteFile, "\n");
   
   return;
}

/*
void
print_cp_delete (int nCatalog, int nPage)
{
   static int bInit = 0;
   static char *cp;
   
   if (!bInit)
   {
      cp = strdup(get_str("DELIMITER"));
      bInit = 1;
   }
   
   if (fprintf (fpDeleteFile, "%d%s%d\n", nCatalog, cp, nPage) < 0)
	{
      fprintf(stderr, "ERROR: Failed to write delete key\n");
      exit(-1);
	}
   
   return;
}
*/
void
print_char (int nColumn, char val, int sep)
{
	if (!nullCheck(nColumn))
	{
		if (fwrite (&val, 1, 1, fpOutfile) != 1)
		{
			fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
			exit(-1);
		}
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);

   return;
}

void
print_date (int nColumn, ds_key_t val, int sep)
{
	if (!nullCheck(nColumn))
	{
		if (val > 0)
		{
			if (print_jdate(fpOutfile, val))
			{
				fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
				exit(-1);
			}
			
		}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	}
	
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);
	   
	return;
}

void
print_time (int nColumn, ds_key_t val, int sep)
{
	int nHours, nMinutes, nSeconds;

	nHours = (int)(val / 3600);
	val -= 3600 * nHours;
	nMinutes = (int)(val / 60);
	val -= 60 * nMinutes;
	nSeconds = (int)(val % 60);
	
	if (!nullCheck(nColumn))
	{
		if (val != -1)
		{
			fprintf(fpOutfile, "%02d:%02d:%02d", nHours, nMinutes, nSeconds);
		}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	
	print_separator (sep);
	   
	return;
}

void
print_decimal (int nColumn, decimal_t * val, int sep)
{
	int i;
	double dTemp;

	if (!nullCheck(nColumn))
	{
#ifdef WIN32
#pragma warning(disable: 4244)
#endif
	dTemp = val->number;
#ifdef WIN32
#pragma warning(default: 4244)
#endif
		for (i=0; i < val->precision; i++)
			dTemp /= 10.0;

		if (fprintf(fpOutfile, "%.*f", val->precision, dTemp) < 0)
		{
			fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
			exit(-1);
		}
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);
	
	return;
}

void
print_key (int nColumn, ds_key_t val, int sep)
{
	if (!nullCheck(nColumn))
	{
		if (val != (ds_key_t) -1) /* -1 is a special value, indicating NULL */
		{
			if (fprintf (fpOutfile, HUGE_FORMAT, val) < 0)
			{
				fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
				exit(-1);
			}
		}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
	print_separator (sep);
	
	return;
}

void
print_id (int nColumn, ds_key_t val, int sep)
{
   char szID[RS_BKEY + 1];
   
   if (!nullCheck(nColumn))
   {
      if (val != (ds_key_t) -1) /* -1 is a special value, indicating NULL */
      {
         mk_bkey(szID, val, 0);
#ifdef STR_QUOTES
         if ((fwrite ("\"", 1, 1, fpOutfile) < 1) ||
            (fwrite (szID, 1, RS_BKEY, fpOutfile) < RS_BKEY) ||
			(fwrite ("\"", 1, 1, fpOutfile) < 1))
#else
            if (fwrite (szID, 1, RS_BKEY, fpOutfile) < RS_BKEY)
#endif
            {
               fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
               exit(-1);
            }
      }
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
   }
 #ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif
  print_separator (sep);
   
   return;
}

void
print_boolean (int nColumn, int val, int sep)
{
	if (!nullCheck(nColumn))
	{

#ifdef STR_QUOTES
		if (fwrite ((val?"\"Y\"":"\"N\""), 1, 3, fpOutfile) != 3)
#else
		if (fwrite ( ((val)?"Y":"N"), 1, 1, fpOutfile) != 1)
#endif
		{
			fprintf(stderr, "ERROR: Failed to write output for column %d\n", nColumn);
			exit(-1);
		}
	}
#ifdef _MYSQL
		else fwrite("NULL", 1, 4, fpOutfile);
#endif

	print_separator (sep);

	return;
}

/*
* Routine: print_start(tbl)
* Purpose: open the output file for a given table
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
print_start (int tbl)
{
   int res = 0;
   char path[256];
   tdef *pTdef = getSimpleTdefsByNumber(tbl);


   current_table = tbl;

   if (is_set ("FILTER"))
	   fpOutfile = stdout;
   else
   {
	   if (pTdef->outfile == NULL)
	   {
		   if (is_set("PARALLEL"))
			   sprintf (path, "%s%c%s_%d_%d%s",
			   get_str ("DIR"),
			   PATH_SEP, getTableNameByID (tbl), 
			   get_int("CHILD"), get_int("PARALLEL"), (is_set("VALIDATE"))?get_str ("VSUFFIX"):get_str ("SUFFIX"));
		   else 
		   {
			   if (is_set("UPDATE"))
				   sprintf (path, "%s%c%s_%d%s",
				   get_str ("DIR"),
				   PATH_SEP, getTableNameByID (tbl), get_int("UPDATE"), (is_set("VALIDATE"))?get_str ("VSUFFIX"):get_str ("SUFFIX"));
			   else
				   sprintf (path, "%s%c%s%s",
				   get_str ("DIR"),
				   PATH_SEP, getTableNameByID (tbl), (is_set("VALIDATE"))?get_str ("VSUFFIX"):get_str ("SUFFIX"));
		   }
		   if ((access (path, F_OK) != -1) && !is_set ("FORCE"))
		   {
			   fprintf (stderr,
				   "ERROR: %s exists. Either remove it or use the FORCE option to overwrite it.\n",
				   path);
			   exit (-1);
		   }
#ifdef WIN32
		   pTdef->outfile = fopen (path, "wt");
#else
		   pTdef->outfile = fopen (path, "w");
#endif
	   }
   }
   
   fpOutfile = pTdef->outfile;
   res = (fpOutfile != NULL);

   if (!res)                    /* open failed! */
     {
        INTERNAL ("Failed to open output file!");
     }
#ifdef WIN32
   else if (setvbuf (fpOutfile, NULL, _IOFBF, 32767))
     {
        INTERNAL ("setvbuf() FAILED");
     }
#endif

   pTdef->flags |= FL_OPEN;

   return (0);
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
print_end (int tbl)
{
   int res = 0;
   static int init = 0;
   static int add_term = 0;
   static char term[10];
   /*
   if (!init)
     {
         if (is_set ("TERMINATE"))
          {
             strncpy (term, get_str ("DELIMITER"), 9);
             add_term = strlen(term);
          }
         
        init = 1;
     }

   if (add_term)
      fwrite(term, 1, add_term, fpOutfile);
   */
   fprintf (fpOutfile, "\n");
   fflush(fpOutfile);

   return (res);
}

/*
* Routine: openDeleteFile(void)
* Purpose: open the output file for the delete keys for a given table
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
openDeleteFile(int bOpen)
{
   int res = 0;
   char path[256];
   
   if (!bOpen)
      fclose(fpDeleteFile);
   else
   {
      sprintf (path, "%s%c%s%d%s",
         get_str ("DIR"),
         PATH_SEP, arDeleteFiles[bOpen], get_int("UPDATE"), get_str("SUFFIX"));
      if ((access (path, F_OK) != -1) && !is_set ("FORCE"))
      {
         fprintf (stderr,
            "ERROR: %s exists. Either remove it or use the FORCE option to overwrite it.\n",
            path);
         exit (-1);
      }
#ifdef WIN32
      fpDeleteFile = fopen (path, "wt");
#else
      fpDeleteFile = fopen (path, "w");
#endif
      
      res = (fpDeleteFile != NULL);
      
      if (!res)                    /* open failed! */
      {
         INTERNAL ("Failed to open output file!");
      }
#ifdef WIN32
      else if (setvbuf (fpDeleteFile, NULL, _IOFBF, 32767))
      {
         INTERNAL ("setvbuf() FAILED");
      }
#endif
   }
   
   return (0);
}

/*
* Routine: print_string()
* Purpose: genralized data print routine
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
*/
void
print_string (char *szMessage, ds_key_t val)
{
	if (fprintf (fpOutfile, szMessage, val) < 0)
	{
		fprintf(stderr, "ERROR: Failed to write string\n");
		exit(-1);
	}

	return;
}

/*
* Routine: print_jdate()
* Purpose: genralized data print routine
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
*/
int
print_jdate (FILE *pFile, ds_key_t kValue)
{

	date_t dTemp;

	jtodt (&dTemp, (int) kValue);
#if (defined(STR_QUOTES) && !defined(_MYSQL))
	if ((fwrite ("\"", 1, 1, pFile) != 1) ||
		(fwrite(dttostr(&dTemp), 1, 10, pFile) != 10) ||
		(fwrite ("\"", 1, 1, pFile)) != 1)
#else
	if (fwrite(dttostr(&dTemp), 1, 10, pFile) != 10)
#endif
		return(-1);
	return(0);
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
print_validation(ds_key_t kRowNumber)
{
	static int bInit = 0;
	static char szValidateFormat[20];

	if (!bInit)
	{
		sprintf(szValidateFormat, "Row #%s: ", HUGE_FORMAT);
		bInit = 1;
	}
	
	if (is_set("VALIDATE"))
	{
		print_string(szValidateFormat, kRowNumber);
	}

	return;
}
