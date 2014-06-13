/*
* $Id: release.h,v 1.83 2008/01/22 00:07:49 jms Exp $
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
* $Log: release.h,v $
* Revision 1.83  2008/01/22 00:07:49  jms
* Release 1.0.0d
*
* Revision 1.82  2007/12/19 23:32:26  jms
* bug 582
*
* Revision 1.81  2007/12/18 19:11:29  jms
* 1.0.0c
*
* Revision 1.80  2007/12/13 18:41:53  jms
* aix compilation flag change
*
* Revision 1.79  2007/12/12 23:39:03  jms
* Mail Ballot (v1.0.0) version changes from Meikel
*
* Revision 1.78  2007/12/05 16:34:54  jms
* query fixes, draft 58
*
* Revision 1.77  2007/11/27 20:28:22  jms
* fix to query22.tpl
*
* Revision 1.76  2007/10/31 17:20:44  jms
* draft 57
*
* Revision 1.75  2007/10/18 15:47:40  jms
* fix to s_inventory
*
* Revision 1.74  2007/10/09 21:58:01  jms
* Add command line seeding for validate option
*
* Revision 1.73  2007/10/02 16:29:01  jms
* update to draft 56
*
* Revision 1.72  2007/09/10 18:10:36  jms
* bug 546
*
* Revision 1.71  2007/08/29 18:47:02  jms
* Bug 545
*
* Revision 1.70  2007/08/28 22:49:54  jms
* scaling patch for alain
*
* Revision 1.69  2007/08/24 22:40:14  jms
* checking prior to draft 53
*
* Revision 1.68  2007/02/06 22:06:22  jms
* release 1.1.52
*
* Revision 1.67  2007/01/24 16:44:46  jms
* Bug 530
*
* Revision 1.66  2007/01/18 23:56:23  jms
* change copyright dates
*
* Revision 1.65  2007/01/18 22:45:38  jms
* *** empty log message ***
*
* Revision 1.64  2007/01/12 19:08:02  jms
* Include fix suggested by Doug Johnson
*
* Revision 1.63  2007/01/09 22:12:19  jms
* draft 50
*
* Revision 1.62  2007/01/09 00:25:39  jms
* Bugs 521-523 (delete file format, update file naming)
*
* Revision 1.61  2006/12/11 21:27:51  jms
* rework of project files for qgen compile
*
* Revision 1.60  2006/12/07 23:14:21  jms
* grammar creation changes
*
* Revision 1.59  2006/12/06 19:59:26  jms
* fix null hanlding of s_call_center
*
* Revision 1.58  2006/11/30 20:38:05  jms
* Bug 515
*
* Revision 1.57  2006/11/30 00:18:25  jms
* pre-release of draft 48 for Meikel
*
* Revision 1.56  2006/11/14 19:09:06  jms
* Bug #517
*
* Revision 1.55  2006/10/26 23:42:55  jms
* Correct scaling for web channel
*
* Revision 1.54  2006/10/25 13:57:22  jms
* scaling fixes
*
* Revision 1.53  2006/10/23 22:43:35  jms
* Bugs reported during Nashville meeting
*
* Revision 1.52  2006/10/13 23:37:35  jms
* Bug 308: rework date-based tables to focus on orders
*
* Revision 1.51  2006/10/05 16:11:03  jms
* Parallelism checkins
*
* Revision 1.50  2006/08/23 23:52:35  jms
* Release 42
*
* Revision 1.49  2006/08/21 16:16:50  jms
* Release 1.41
*
* Revision 1.48  2006/07/18 23:03:26  jms
* Bug 473
*
* Revision 1.47  2006/06/21 00:16:34  jms
* Next release to Meikel
*
* Revision 1.46  2006/06/07 23:01:00  jms
* update fixes for linux
*
* Revision 1.45  2006/06/02 19:26:24  jms
* release 39f to meikel (add ship cost to s_clin s_wlin)
*
* Revision 1.44  2006/06/02 12:20:33  jms
* Bug 459: closed date should be printed as date, not SK
*
* Revision 1.43  2006/05/12 19:08:11  jms
* Bug 449: missing columns in s_catalog_returns
*
* Revision 1.42  2006/05/10 22:03:23  jms
* Porting cleanup
*
* Revision 1.41  2006/05/09 21:03:45  jms
* correct primary keys in sales tables of warehouse
*
* Revision 1.40  2006/05/09 00:23:39  jms
* Changes requested by Meikel 5/8/06
*
* Revision 1.39  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.38  2006/04/20 19:31:53  jms
* Release 38c
*
* Revision 1.37  2006/04/12 20:08:43  jms
* adjust scaling of item to assure proper rec-end-date handling for DM functions
*
* Revision 1.36  2006/04/10 23:37:31  jms
* Bug 414: each id in an update set should be unique
*
* Revision 1.35  2006/04/05 19:39:59  jms
* Bug 413
*
* Revision 1.34  2006/03/30 23:23:45  jms
* bug reports from Meikel 3/30
*
* Revision 1.33  2006/03/30 16:40:30  jms
* bug reports from Meikel 3/29
*
* Revision 1.32  2006/03/28 21:48:08  jms
* bougs data in w_web_returns
*
* Revision 1.31  2006/03/28 21:19:18  jms
* bougs data in w_web_returns
*
* Revision 1.30  2006/03/28 19:03:23  jms
* additional testing of updates from Meikel
*
* Revision 1.29  2006/03/28 00:59:47  jms
* Catalog page changes from Meikel (3/27)
*
* Revision 1.28  2006/03/17 20:31:26  jms
* Move to release 37
*
* Revision 1.27  2006/03/13 17:04:10  jms
* move to rev a for makefile cleanup
*
* Revision 1.26  2006/03/01 00:22:39  jms
* Bug 397: catalog_sales dates are generated for 2003
*
* Revision 1.25  2006/02/21 21:29:20  jms
* update copyight notice
*
* Revision 1.24  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.23  2006/02/02 05:07:13  jms
* draft 34 release
*
* Revision 1.22  2006/01/16 23:19:35  jms
* Draft 33
*
* Revision 1.21  2006/01/10 00:30:41  jms
* change patch to 'a' after included files from Meikel
*
* Revision 1.20  2005/12/16 18:28:20  jms
* release 32
*
* Revision 1.19  2005/12/09 20:23:52  jms
* update release tag
*
* Revision 1.18  2005/11/22 22:38:00  jms
* *** empty log message ***
*
* Revision 1.17  2005/11/11 23:33:59  jms
* release 1.1.29
*
* Revision 1.16  2005/11/10 16:50:21  jms
* *** empty log message ***
*
* Revision 1.15  2005/11/08 23:38:24  jms
* correct scaling overrun
*
* Revision 1.14  2005/10/31 19:30:36  jms
* release of draft 28: the first the links spec and tool releases
*
* Revision 1.13  2005/10/18 16:29:16  jms
* correct NOT NULL attributes
*
* Revision 1.12  2005/10/03 18:52:12  jms
* update to release 1.1.27
*
* Revision 1.11  2005/04/20 17:01:46  jms
* Bug #168: Generate fact tables in date order
*
* Revision 1.10  2005/04/19 16:48:51  jms
* Bug #167: Extra column in inventory
*
* Revision 1.9  2005/04/12 21:04:12  jms
* 1.1.25 changes
*
* Revision 1.8  2005/03/15 23:14:07  jms
* change time boundaries
*
* Revision 1.7  2005/02/21 23:25:53  jms
* Porting corrections
*
* Revision 1.6  2005/01/13 20:12:02  jms
* add 2005 to copyright range
*
* Revision 1.5  2004/12/10 20:00:28  jms
* *** empty log message ***
*
* Revision 1.4  2004/12/02 19:14:14  jms
* Release 1.1.21
*
* Revision 1.3  2004/12/01 00:40:40  jms
* fix parallelism
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.24  2004/11/17 21:25:36  jms
* Bug #106: Parallel data doesn't match serrially generated data
*
* Revision 1.23  2004/11/01 17:38:36  jms
* Bug #109: Output error needs error message
*
* Revision 1.22  2004/10/29 16:50:28  jms
* final build for 1.1.20
*
* Revision 1.21  2004/10/27 23:06:43  jms
* Bug 105: date range in store_sales
*
* Revision 1.20  2004/10/19 18:18:04  jms
* change revision for source schema pre-release
*
* Revision 1.19  2004/10/14 16:06:46  jms
* Expand segregation of warehouse and source schema data generation
*
* Revision 1.18  2004/10/06 20:44:45  jms
* Begin work on 1.1.19
*
* Revision 1.17  2004/09/24 19:08:18  jms
* Set up for release 1_1_18
*
* Revision 1.16  2004/08/25 23:49:12  jms
* rework qgen to match revised users guide
*
* Revision 1.15  2004/08/24 16:33:14  jms
* add -release option to display version information
*
* Revision 1.14  2004/08/23 22:57:12  jms
* SOLARIS porting issues
*
* Revision 1.13  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.12  2004/08/13 21:31:26  jms
* correct release number
*
* Revision 1.11  2004/08/13 21:18:51  jms
* minor release (1.1.14a) to address porting concerns to Solaris, HP/UX
*
* Revision 1.10  2004/07/16 20:48:02  jms
* update release number
*
* Revision 1.9  2004/06/08 18:45:26  jms
* correct naming of date dimension
*
* Revision 1.8  2004/06/02 17:21:48  jms
* release 1.1.13b
*
* Revision 1.7  2004/05/26 17:17:26  jms
* release 1.1.13a
*
* Revision 1.6  2004/05/21 23:50:20  jms
* release.h
*
* Revision 1.5  2004/05/12 17:33:17  jms
* release fix for 62 and 63
*
* Revision 1.4  2004/05/05 16:32:34  jms
* parallel gen caused small tables to be skipped
*
* Revision 1.3  2004/05/04 18:21:24  jms
* update release number
*
* Revision 1.2  2004/04/02 18:12:47  jms
* 1.1.11 release
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.13  2003/07/24 16:22:39  jms
* Release 1.1.9a
*
* Revision 1.12  2003/07/18 19:56:46  jms
* update for 1.1.9
*
* Revision 1.11  2003/06/11 06:37:46  jms
* Further changes for step-skewed dates in sales
*
* Revision 1.10  2003/06/10 19:57:49  jms
* Updated for 6/10 release to Meikel
*
* Revision 1.9  2003/06/10 03:37:55  jms
* pre-commit of changes for 1.1.9
*
* Revision 1.8  2003/05/07 20:07:42  jms
* release 1.1.8 pre  for unix porting check
*
* Revision 1.7  2003/04/30 22:53:58  jms
* formal release of 1.1.7 pre
*
* Revision 1.6  2003/04/29 19:21:16  jms
* solaris porting fixes
*
* Revision 1.5  2003/04/28 19:35:10  jms
* remove hierarchy items from product_bundle
*
* Revision 1.4  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.3  2003/04/23 23:47:27  jms
* interim release to unisys
*
* Revision 1.2  2003/04/23 19:15:08  jms
* fixes to bug 14: build under MP-RAS
*
* Revision 1.1  2003/04/21 19:52:29  jms
* isolate revision information
*
*/
#ifndef RELEASE_H
#define  RELEASE_H

/***
 *** RELEASE INFORMATION
 ***/
#define VERSION       1
#define RELEASE       0
#define MODIFICATION  0
#define PATCH         "d"
#define COPYRIGHT     "Transaction Processing Performance Council (TPC)"
#define C_DATES       "2001 - 2007"

int printReleaseInfo(char *param, char *val);

#endif
