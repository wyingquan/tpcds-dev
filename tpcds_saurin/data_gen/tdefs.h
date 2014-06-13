/*
* $Id: tdefs.h,v 1.13 2007/08/02 18:56:30 jms Exp $
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
* $Log: tdefs.h,v $
* Revision 1.13  2007/08/02 18:56:30  jms
* bug 546
*
* Revision 1.12  2007/07/27 22:05:18  jms
* bug 546
*
* Revision 1.11  2007/07/24 20:07:30  jms
* bug 546
*
* Revision 1.10  2007/07/10 18:49:29  jms
* validate s_customer_address
*
* Revision 1.9  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.8  2006/06/06 21:41:15  jms
* initial checkin of revised update scaling
*
* Revision 1.7  2006/03/09 00:53:50  jms
* Bug 402: assorted data errors in source schema
*
* Revision 1.6  2006/02/02 05:06:09  jms
* scale factor aware qgen
*
* Revision 1.5  2006/01/16 23:12:38  jms
* Bug 141: support 300G, 3T, 30TB
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/01/13 19:53:11  jms
* Bug #136: sparse key support
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:06  jms
* re-establish external server
*
* Revision 1.26  2004/09/08 21:14:21  jms
* add routine to map column id to table id
*
* Revision 1.25  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.24  2004/06/03 21:09:39  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.23  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.22  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.21  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.20  2004/03/27 00:17:10  jms
* correct truncation of child tables
*
* Revision 1.19  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.18  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.17  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.18  2003/07/14 23:14:54  jms
* enable continuous scaling in integer GB
*
* Revision 1.17  2003/03/21 19:56:45  jms
* resync with code on laptap
*
* Revision 1.16  2002/11/07 23:56:47  jms
* changes for DBGEN 1.0.6
*
* Revision 1.15  2002/11/05 06:24:47  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.14  2002/10/30 00:17:59  jms
* correcting scaling error in type-2 tables
*
* Revision 1.13  2002/10/27 17:23:16  jms
* correct scaling for call_center and other type-2 tables
*
* Revision 1.12  2002/09/25 22:46:59  jms
* commit all open changes to allow tighter issue/change tracking
*
* Revision 1.11  2002/09/04 18:26:40  jms
* Corrections to catalog page generation
*
* Revision 1.10  2002/09/04 17:14:02  jms
* Activate promotional_bundle and promotional_bundle_coverage
* Change catalog_returns to be child of catalog sales
* Introduce FL_TYPE_2 (start with call_center)
*
* Revision 1.9  2002/08/18 01:26:08  jms
* corrected scale multiplier on smaller dimenions from 1 to 0
*
* Revision 1.8  2002/08/18 00:39:34  jms
* update scaling to most recent spreadsheet
* enable tdefs[].base for a scaling multiplier (10^x)
* include /scale 0 trap to disable multiplier and allow fast debug
*
* Revision 1.7  2002/08/16 23:52:42  jms
* removal vestigal FL_CHILD flags
*
* Revision 1.6  2002/08/16 23:24:22  jms
* complete linkage of catalog sales and returns and clean up parent child handling
*
* Revision 1.5  2002/08/16 19:30:13  jms
* populate web_page
*
* Revision 1.4  2002/08/16 16:43:51  jms
* pass index into mk_xxx routines to allow them to be called out of sequence in parent/child relationships
*
* Revision 1.3  2002/08/15 19:07:36  jms
* integrate mkheader into RNG usage as prep for parallel generation
*
* Revision 1.2  2002/07/27 00:08:49  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/05 19:11:57  jms
* Display warning when table name is ambiguous, but continue to build first matching table name
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef TDEFS_H
#define TDEFS_H

#include <stdio.h>
#include "tables.h"
#include "columns.h"
#include "tdef_functions.h"

/*
 * Flag field definitions used in tdefs[]
 */
#define FL_NONE			0x0000		/* this table is not defined */
#define FL_NOP			0x0001		/* this table is not defined */
#define FL_DATE_BASED	0x0002		/* this table is produced in date order */
#define FL_CHILD		0x0004		/* this table is the child in a parent/child link */
#define FL_OPEN			0x0008		/* this table has a valid output destination */
#define FL_DUP_NAME		0x0010		/* to keep find_table() from complaining twice */
#define FL_TYPE_2		0x0020		/* this dimension keeps history -- rowcount shows unique entities (not including revisions) */
#define FL_SMALL        0x0040   /* this table has low rowcount; used by address.c */
#define FL_SPARSE    0x0080 
/* unused 0x0100 */
#define FL_NO_UPDATE	0x0200		/* this table is not altered by the update process */
#define FL_SOURCE_DDL	0x0400		/* table in the souce schema */
#define FL_JOIN_ERROR	0x0800		/* join called without an explicit rule */
#define FL_PARENT		0x1000		/* this table has a child in nParam */
#define FL_FACT_TABLE   0x2000
#define FL_PASSTHRU     0x4000   /* verify routine uses warehouse without change */
#define FL_VPRINT   0x8000       /* verify routine includes print function */

/*
* general table descriptions. 
* NOTE: This table contains the constant elements in the table descriptions; it must be kept in sync with the declararions of 
*   assocaited functions, found in tdef_functions.h
*/
typedef struct TDEF_T {
	char *name;		/* -- name of the table; */
	char *abreviation;	/* -- shorthand name of the table */
	int flags;		/* -- control table options */
	int nFirstColumn;	/* -- first column/RNG for this table */
	int nLastColumn;	/* -- last column/RNG for this table */
	int nTableIndex;	/* used for rowcount calculations */
	int nParam;		/* -- additional table param (revision count, child number, etc.) */
	FILE *outfile;		/* -- output destination */
	int nUpdateSize;	/* -- percentage of base rowcount in each update set (basis points) */
	int nNewRowPct;
	int nNullPct;		/* percentage of rows with nulls (basis points) */
	ds_key_t kNullBitMap;	/* colums that should be NULL in the current row */
	ds_key_t kNotNullBitMap;	/* columns that are defined NOT NULL */
	ds_key_t *arSparseKeys;	/* sparse key set for table; used if FL_SPARSE is set */
	} tdef;

/*
extern tdef *tdefs;
extern tdef w_tdefs[];
extern tdef s_tdefs[];
*/

#define tdefIsFlagSet(t, f)	(tdefs[t].flags & f)
ds_key_t GetRowcountByName(char *szName);
int GetTableNumber(char *szName);
char *getTableNameByID(int id);
int getTableFromColumn(int id);
int initSpareKeys(int id);
tdef *getSimpleTdefsByNumber(int nTable);
tdef *getTdefsByNumber(int nTable);


#endif
