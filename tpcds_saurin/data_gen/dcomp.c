/*
* $Id: dcomp.c,v 1.11 2006/07/13 16:58:42 jms Exp $
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
* $Log: dcomp.c,v $
* Revision 1.11  2006/07/13 16:58:42  jms
* Bug 470: dist read failure on aix 64
*
* Revision 1.10  2006/07/13 12:51:21  jms
* Bug 470: move int to int32_t
*
* Revision 1.9  2006/05/10 23:07:18  jms
* Porting cleanup
*
* Revision 1.8  2006/05/10 22:45:54  jms
* porting cleanup
*
* Revision 1.7  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.6  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.5  2006/01/08 22:20:15  jms
* cleanup of query error reporting
*
* Revision 1.4  2006/01/07 00:44:02  jms
* add MALLOC_CHECK calls
*
* Revision 1.3  2004/12/02 17:45:38  jms
* Bug #126: qgen core dumps on some templates
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.11  2004/10/14 17:52:50  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.10  2004/10/14 16:24:15  jms
* porting changes for w/s segregation
*
* Revision 1.9  2004/10/14 16:06:45  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.8  2004/06/03 21:12:44  jms
* sync unix/windows builds
*
* Revision 1.7  2004/06/03 21:09:38  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.6  2004/06/03 20:35:17  jms
* better handling of tdefs/s_tdefs/w_tdefs
*
* Revision 1.5  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.8  2003/07/15 17:09:08  jms
* add support for HPUX
*
* Revision 1.7  2003/06/05 21:18:30  jms
* generate header file to allow distribution names aliases to be used in C
*
* Revision 1.6  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.5  2003/04/23 19:15:08  jms
* fixes to bug 14: build under MP-RAS
*
* Revision 1.4  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.3  2002/12/04 18:03:24  jms
* Porting changes for AIX 4.3.3
*
* Revision 1.2  2002/08/13 23:13:08  jms
* porting to Solaris 9
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/

#define DECLARER
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#ifdef AIX
#include <sys/mode.h>
#endif
#ifndef WIN32
#include <netinet/in.h>
#endif
#include "r_params.h"
#include "dcomp_params.h"
#include "error_msg.h"
#include "grammar.h"
#include "dist.h"
#include "dcgram.h"
#include "dcomp.h"
#include "substitution.h"
#include "grammar_support.h" /* to get definition of file_ref_t */

char *CurrentFileName = NULL;
distindex_t *pDistIndex;
file_ref_t CurrentFile;
file_ref_t *pCurrentFile;

/*
 * Routine: WriteIndex()
 * Purpose: traverse the distributions list and create the binary 
 *		version of distribution output
 * Algorithm:
 * Data Structures:
 *
 * Params: (list_t)
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 
 * 	19990311 add data file format to header
 * 	20000112 need to allow for changes to an existing index file
 * 	20000112 need to allow for multiple index files
 */
int 
WriteIndex(distindex_t *t)
{
   d_idx_t *idx = NULL;
   dist_t *d;
   int32_t i, j, 
      nDist,
      *pSet,
      err_cnt = 0,
      offset=0,
      data_type,
      temp;
   FILE *fpHeader = NULL;
   FILE *ofp = NULL;
   char *cp;

	if ((ofp = fopen(get_str("OUTPUT"), "wb")) == NULL)
	{
		printf("ERROR: Cannot open output file '%s'\n", 
		get_str("OUTPUT"));
		usage(NULL, NULL);
	}

	/* open the header file */
	if ((fpHeader = fopen(get_str("HEADER"), "w")) == NULL)
		return(99);
	fprintf(fpHeader, "/*\nTHIS IS AN AUTOMATICALLY GENERATED FILE\nDO NOT EDIT\n\nSee distcomp.c for details\n*/\n");
	
	/* output the number of distributions in the file */
	temp = htonl(pDistIndex->nDistCount);
	if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
		return(12);
	offset += sizeof(int32_t);

	/* then walk the distributions and write each one in turn */

	for (nDist=0; nDist < pDistIndex->nDistCount; nDist++)
    	{
		idx = pDistIndex->pEntries + nDist;
		d = idx->dist;
		idx->offset = offset;

		/* and then output the distribution to the file */
		/* format is:
		 * a v_width data types stored as integers
		 * a sequence of weigth sets, each <length> integers
		 * a sequence of string offsets, each <length> integers
		 * a sequence of aliases for values and weights, with each value NULL terminated
		 * the string values for each value vector, with each value NULL
		 *	terminated
		 */
		/* output type data type vector */
		for (i=0; i < idx->v_width; i++)
			{
			data_type = d->type_vector[i];
			temp = htonl(data_type);
			if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
				err_cnt = 12;
			else 
				offset += sizeof(int32_t);
			}

		/* output the weight sets */
		for (i=0; i < idx->w_width; i++)
			{
			pSet = d->weight_sets[i];
			for (j=0; j < idx->length; j++)
				{
				temp = htonl(pSet[j]);
				if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
					err_cnt = 6;
				else 
					offset += sizeof(int32_t);
				}
			}

		/* output the string offsets */
		for (i=0; i < idx->v_width; i++)
			{
			pSet = d->value_sets[i];
			for (j=0; j < idx->length; j++)
				{
				temp = htonl(pSet[j]);
				if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
					err_cnt = 8;
				else 
					offset += sizeof(int32_t);
				}
			}

		/* output the column aliases and generated the associated header file entries */
		fprintf(fpHeader, "\n/* aliases for values/weights in the %s distribution */\n", idx->name);
		if (d->names)
		{
			if (fwrite(d->names, 1, idx->name_space, ofp) < (size_t)idx->name_space)
				err_cnt = 8;
			else 
				offset += idx->name_space;
			
			cp = d->names;
			for (i=0; i < idx->v_width + idx->w_width; i++)
			{
				fprintf(fpHeader, "#define %s_%s\t%d\n",
					idx->name,
					cp,
					(i >= idx->v_width)?i - idx->v_width + 1:i + 1);
				cp += strlen(cp) + 1;
			}
		}
		else
			fprintf(fpHeader, "/* NONE DEFINED */\n");

		/* output the strings themselves */
		if (fwrite(d->strings, 1, idx->str_space, ofp) < (size_t)idx->str_space)
			err_cnt = 8;
		else 
			offset += idx->str_space;

    	}

	/* finally, re-write the index */
	for (i=0; i < pDistIndex->nDistCount; i++)
		{
		idx = pDistIndex->pEntries + i;
		if (fwrite(idx->name, 1, D_NAME_LEN, ofp) < 0)
			{err_cnt = 9; break;}
		temp = htonl(idx->index);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 10; break;}
		temp = htonl(idx->offset);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 12; break;}
		temp = htonl(idx->str_space);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 13; break;}
		temp = htonl(idx->length);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 15; break;}
		temp = htonl(idx->w_width);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 16; break;}
		temp = htonl(idx->v_width);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 17; break;}
		temp = htonl(idx->name_space);
		if (fwrite(&temp, 1, sizeof(int32_t), ofp) < 0)
			{err_cnt = 18; break;}
		}

	fclose(ofp);
	fclose(fpHeader);

   return(err_cnt);
}    

 /*
 * Routine: main()
 * Purpose: provide command line interface to distcomp routines
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: jms 20041013: rework as version/option of qgen
 */

int main(int argc, char* argv[])
{
	int nArgs,
		i;
	char szPath[128];	/*  need file path length define */
	char szHeader[128];
	d_idx_t *pIndexEntry;

	nArgs = process_options(argc, argv);
	if (!is_set("INPUT") || !is_set("OUTPUT"))
		usage(NULL, "Must specify input and output file names");
	if (!is_set("HEADER"))
	{
		strcpy(szHeader, get_str("OUTPUT"));
		strcat(szHeader, ".h");
		set_str("HEADER", szHeader);
	}

	
	
	/* setup the dist index */
	pDistIndex = (distindex_t *)malloc(sizeof(struct DISTINDEX_T));
	MALLOC_CHECK(pDistIndex);
	if (pDistIndex == NULL)
		ReportError(QERR_NO_MEMORY, "main", 1);
	memset((void *)pDistIndex, 0, sizeof(struct DISTINDEX_T));
	/*
	pDistIndex->pEntries = (d_idx_t *)malloc(100 * sizeof(struct D_IDX_T));
	MALLOC_CHECK(pDistIndex->pEntries);
	if (pDistIndex->pEntries == NULL)
		ReportError(QERR_NO_MEMORY, "main", 1);
	pDistIndex->nAllocatedCount = 100;
	for (i=0; i < 100; i++)
		memset(pDistIndex->pEntries + i, 0, sizeof(struct D_IDX_T));
	*/
		

	SetTokens(dcomp_tokens);

	if ((i = ParseFile(get_str("INPUT"))) != 0)
	{
		printf("ERROR: Parse failed for %s\n", 
			get_str("INPUT"));
		ReportError(i, NULL, 1);
		exit(1);
	}

	if (is_set("VERBOSE"))
	{
		printf("Defined %d distributions:\n", pDistIndex->nDistCount);
		for (i=0; i < pDistIndex->nDistCount; i++)
		{
			pIndexEntry = pDistIndex->pEntries + i;
			printf("\t%s[%d] --> (%d,%d)",
				pIndexEntry->name,
				pIndexEntry->length,
				pIndexEntry->v_width,
				pIndexEntry->w_width);
			if (pIndexEntry->name_space)
				printf(" with names");
			printf("\n");
		}
	}

	if ((i = WriteIndex(pDistIndex)) > 0)		
		{
		sprintf(szPath, "WriteDist returned %d writing to %s", 
			i, get_str("OUTPUT"));
		ReportError(QERR_WRITE_FAILED, szPath, 1);
		}

	return 0;
}
