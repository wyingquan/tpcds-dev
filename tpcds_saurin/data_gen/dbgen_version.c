/*
* $Id: dbgen_version.c,v 1.3 2006/03/13 17:48:21 jms Exp $
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
* $Log: dbgen_version.c,v $
* Revision 1.3  2006/03/13 17:48:21  jms
* Bug 406: bad parameter to time()
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.1  2004/07/16 20:49:16  jms
* Generate dbgen_version table
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <time.h>
#include "dbgen_version.h"
#include "print.h"
#include "columns.h"
#include "build_support.h"
#include "tables.h"
#include "misc.h"
#include "release.h"

struct DBGEN_VERSION_TBL g_dbgen_version;
extern char g_szCommandLine[];

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
mk_dbgen_version(void *pDest, ds_key_t kIndex)
{
	static int bInit = 0;
	struct DBGEN_VERSION_TBL *r;
	time_t ltime;
	struct tm *pTimeStamp;
	
	if (pDest == NULL)
		r = &g_dbgen_version;
	else
		r = pDest;
	
	if (!bInit)
	{
		memset(&g_dbgen_version, 0, sizeof(struct DBGEN_VERSION_TBL));
		bInit = 1;
	}
	
	
	time( &ltime );                 /* Get time in seconds */
	pTimeStamp = localtime( &ltime );  /* Convert time to struct */
	
	sprintf(r->szDate, "%4d-%02d-%02d", pTimeStamp->tm_year + 1900, pTimeStamp->tm_mon + 1, pTimeStamp->tm_mday);
	sprintf(r->szTime, "%02d:%02d:%02d", pTimeStamp->tm_hour, pTimeStamp->tm_min, pTimeStamp->tm_sec);
	sprintf (r->szVersion,"%d.%d.%d%s", VERSION, RELEASE, MODIFICATION, PATCH);
	strcpy(r->szCmdLineArgs, g_szCommandLine);
	
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
int
pr_dbgen_version(void *pSrc)
{
	struct DBGEN_VERSION_TBL *r;
	
	if (pSrc == NULL)
		r = &g_dbgen_version;
	else
		r = pSrc;
	
	print_start(DBGEN_VERSION);
	print_varchar(DV_VERSION, r->szVersion, 1);
	print_varchar(DV_CREATE_DATE, r->szDate, 1);
	print_varchar(DV_CREATE_TIME, r->szTime, 1);
	print_varchar(DV_CMDLINE_ARGS, r->szCmdLineArgs, 0);
	print_end(DBGEN_VERSION);
	
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
int 
ld_dbgen_version(void *pSrc)
{
	struct DBGEN_VERSION_TBL *r;
		
	if (pSrc == NULL)
		r = &g_dbgen_version;
	else
		r = pSrc;
	
	return(0);
}

