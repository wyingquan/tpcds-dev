/*
* $Id: load.c,v 1.2 2004/11/24 23:54:17 jms Exp $
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
* $Log: load.c,v $
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.7  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.6  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.5  2002/11/07 23:56:47  jms
* changes for DBGEN 1.0.6
*
* Revision 1.4  2002/11/05 06:24:47  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.3  2002/09/25 22:46:59  jms
* commit all open changes to allow tighter issue/change tracking
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/18 22:10:33  jms
* clean up handling of HUGE_TYPE
* add config.h and/or porting.h where needed
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include "tables.h"

#ifdef SQLSERVER
// ODBC headers
#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>
SQLHENV	henv;
#endif

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
create_table(int nTable)
{
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
load_init(void)

{
#ifdef SQLSERVER
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
#endif

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
load_close(void)
{
#ifdef SQLSERVER
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
#endif

	return;
}
