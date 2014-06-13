/*
* $Id: print.h,v 1.10 2007/05/02 19:29:39 jms Exp $
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
* $Log: print.h,v $
* Revision 1.10  2007/05/02 19:29:39  jms
* bug 546
*
* Revision 1.9  2007/01/09 00:25:39  jms
* Bugs 521-523 (delete file format, update file naming)
*
* Revision 1.8  2006/11/17 19:59:07  jms
* Checkin for 47 (redo to address sync issues)
*
* Revision 1.7  2006/06/06 21:41:13  jms
* initial checkin of revised update scaling
*
* Revision 1.6  2006/03/17 23:23:13  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.5  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
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
* Revision 1.4  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.3  2004/05/21 23:50:20  jms
* release.h
*
* Revision 1.2  2003/11/06 00:13:09  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
/*
 * OUTPUT ROUTINES
 */
FILE	*print_prep(int table, int update);
int		dbg_print(int format, ds_key_t data, int len, int sep);
int		print_start(int tbl);
int      openDeleteFile(int bOpen);
int		print_end(int tbl);
void	print_close(int tbl);

void print_integer(int nColumn, int col, int s);
void print_char(int nColumn, char col, int s);
void print_key(int nColumn, ds_key_t col, int s);
void print_id(int nColumn, ds_key_t col, int s);
void print_varchar(int nColumn, char *col, int s);
void print_boolean(int nColumn, int col, int s);
void print_date(int nColumn, ds_key_t, int s);
void print_time(int nColumn, ds_key_t, int s);
void print_delete(int *pnDate);
void print_cp_delete(int nCatalog, int nPage);
void print_string(char *szMessage, ds_key_t kParam);
void print_validation(ds_key_t kRowNumber);

