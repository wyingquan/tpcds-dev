/*
* $Id: mkheader.c,v 1.7 2007/05/24 00:35:41 jms Exp $
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
* $Log: mkheader.c,v $
* Revision 1.7  2007/05/24 00:35:41  jms
* TPCDS Bug 546
*
* Revision 1.6  2006/08/17 19:40:05  jms
* Coversion of VisualStudio 2005
*
* Revision 1.5  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.4  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.3  2005/10/05 17:31:35  jms
* bug #239: need data validation method
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.8  2004/04/02 18:10:01  jms
* enable parallel generation
*
* Revision 1.7  2004/03/27 01:01:42  jms
* externalize RNGUsage for each column for parallelism
*
* Revision 1.6  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.5  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.5  2003/04/23 22:48:24  jms
* compiler errors under MP-RAS
*
* Revision 1.4  2002/10/11 23:43:49  jms
* expanded size of line buffer
*
* Revision 1.3  2002/09/04 17:28:53  jms
* Add support for nDuplicateOf in rng_t
*
* Revision 1.2  2002/08/15 19:07:36  jms
* integrate mkheader into RNG usage as prep for parallel generation
*
* Revision 1.1  2002/08/14 00:15:49  jms
* unification of columns.h and streams.h
* update of tpcds.sql to match current WAM file
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

/*
* Routine: mkheader() 
* Purpose: keep columns.h and streams.h in sync
* Algorithm: this should really be a simple shell script, but need to assure that it will 
* port to non-unix (i.e., windows)
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
main(int ac, char **av)
{
	FILE *pInputFile,
		*pColumnsFile,
		*pStreamsFile,
		*pTablesFile;
	char szColumn[80],
		szTable[80],
		szLine[1024],
		szDuplicate[80],
		szLastTable[80],
		*cp;
	int nLineNumber = 0,
		nColumnCount = 1,
		bError = 0,
		nTableCount = 0,
		nRNGUsage = 1;

	if (ac != 2)
		bError = 1;

	pInputFile = fopen(av[1], "r");
	if (pInputFile == NULL)
		bError = 1;

	pColumnsFile = fopen("columns.h", "w");
	if (pColumnsFile == NULL)
		bError = 1;

	pStreamsFile = fopen("streams.h", "w");
	if (pStreamsFile == NULL)
		bError = 1;

	pTablesFile = fopen("tables.h", "w");
	if (pTablesFile == NULL)
		bError = 1;

	if (bError)
	{
		fprintf(stderr, "USAGE:\n\t%s file -- build headers based on file\n", av[0]);
		fprintf(stderr, "\tcolumns.h and streams.h produced as a result\n");
		exit(-1);
	}

	/* set up varaibles */
	szLastTable[0] = '\0';

	/* put out minimal headers for each file */
	fprintf(pColumnsFile, "/*\n * THIS IS A GENERATED FILE\n * SEE COLUMNS.LIST\n*/\n");
	fprintf(pStreamsFile, "/*\n * THIS IS A GENERATED FILE\n * SEE COLUMNS.LIST\n*/\n");
	fprintf(pTablesFile, "/*\n * THIS IS A GENERATED FILE\n * SEE COLUMNS.LIST\n*/\n");
	fprintf(pColumnsFile, "#ifndef COLUMNS_H\n#define COLUMNS_H\n");
	fprintf(pStreamsFile, "#ifndef STREAMS_H\n#define STREAMS_H\n");
	fprintf(pStreamsFile, "rng_t Streams[] = {\n{0, 0, 0, 0, 0, 0, 0},\n");
	fprintf(pTablesFile, "#ifndef TABLES_H\n#define TABLES_H\n");
	
	/* add an entry to each for each column in the list */
	while (fgets(szLine, 1024, pInputFile) != NULL)
	{
		nLineNumber += 1;
		szColumn[0] = szTable[0] = szDuplicate[0] = '\0';
		nRNGUsage = 1;
		if ((cp = strchr(szLine, '#')) != NULL)
			*cp = '\0';
		if (!strlen(szLine))
			continue;
		if (sscanf(szLine, "%s %s %d %s", szColumn, szTable, &nRNGUsage, szDuplicate) != 4)
		{
		strcpy(szDuplicate, szColumn);
		if (sscanf(szLine, "%s %s %d", szColumn, szTable, &nRNGUsage) != 3)
		{
		if (sscanf(szLine, "%s %s", szColumn, szTable) != 2)
			continue;
		}
		}

		fprintf(pStreamsFile, "{0, %d, 0, 0, %s, %s, %s},\n", nRNGUsage, szColumn, szTable, szDuplicate);
		if (strcmp(szLastTable, szTable))
			{
			if (strlen(szLastTable))
				fprintf(pColumnsFile, "#define %s_END\t%d\n", szLastTable, nColumnCount - 1);
			fprintf(pColumnsFile, "#define %s_START\t%d\n", szTable, nColumnCount);
			fprintf(pTablesFile, "#define %s\t%d\n", szTable, nTableCount++);
			strcpy(szLastTable, szTable);
			}
		fprintf(pColumnsFile, "#define %s\t%d\n", szColumn, nColumnCount++);
	}

	/* close out the files */
	fprintf(pStreamsFile, "{-1, -1, -1, -1, -1, -1, -1}\n};\n");
	fprintf(pStreamsFile, "#endif\n");
	fprintf(pColumnsFile, "#define %s_END\t%d\n", szLastTable, nColumnCount - 1);
	fprintf(pColumnsFile, "#define MAX_COLUMN\t%d\n", nColumnCount - 1);
	fprintf(pColumnsFile, "#endif\n");
	fprintf(pTablesFile, "#define PSEUDO_TABLE_START\t%d\n", nTableCount);
	fprintf(pTablesFile, "/* PSEUDO TABLES from here on; used in hierarchies */\n");
	fprintf(pTablesFile, "#define ITEM_BRAND\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define ITEM_CLASS\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define ITEM_CATEGORY\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define DIVISIONS\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define COMPANY\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define CONCURRENT_WEB_SITES\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define ACTIVE_CITIES\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define ACTIVE_COUNTIES\t%d\n", nTableCount++);
	fprintf(pTablesFile, "#define ACTIVE_STATES\t%d\n", nTableCount);
	fprintf(pTablesFile, "#define MAX_TABLE\t%d\n", nTableCount);	
	fprintf(pTablesFile, "#endif\n");

	/* close the files */
	fclose(pStreamsFile);
	fclose(pColumnsFile);
	fclose(pInputFile);
	fclose(pTablesFile);

	exit(0);
}
