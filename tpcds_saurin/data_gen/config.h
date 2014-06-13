/*
 * $Id: config.h,v 1.16 2007/12/20 00:40:17 jms Exp $
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
 * 
 * The following #defines will effect the code:
 *   SPAWN             -- name of system call to clone an existing process
 *   SET_HANDLER(proc) -- name of routine to handle signals in parallel load
 *   WAIT(res, pid)    -- how to await the termination of a child
 *   SEPARATOR         -- character used to separate fields in flat files
 *   DBNAME            -- default name of database to be loaded
 *   MDY_DATE          -- generate dates as MM-DD-YY
 *   SUPPORT_64BITS    -- compiler defines a 64 bit datatype
 *   HUGE_TYPE	       -- 64 bit data type
 *   HUGE_FORMAT       -- printf string for 64 bit data type
 *   HUGE_COUNT        -- number of objects in ds_key_t
 *   EOL_HANDLING      -- flat files don't need final column separator
 *
 *   OS defines
 *   ==========
 *   AIX        -- posix source inclusion differences
 *   LINUX      
 *   WIN32		-- support for WindowsNT/Win2K
 *   SOLARIS		-- built with GCC
 *   NCR		-- NCR MP-RAS UNIX
 *   HPUX
 *
 *   Database defines
 *   ================
 *   DB2        -- use DB2 dialect in QGEN
 *   INFORMIX   -- use Informix dialect in QGEN
 *   SQLSERVER  -- use SQLSERVER dialect in QGEN
 *   SYBASE     -- use Sybase dialect in QGEN
 *   TDAT       -- use Teradata dialect in QGEN
 * Revision History
 * ===================
 * $Log: config.h,v $
 * Revision 1.16  2007/12/20 00:40:17  jms
 * assure signed format for ds_key_t for bug 582
 *
 * Revision 1.15  2007/01/18 21:01:51  jms
 * move HPUX to FLEX
 *
 * Revision 1.14  2006/11/30 00:18:25  jms
 * pre-release of draft 48 for Meikel
 *
 * Revision 1.13  2006/11/01 00:23:50  jms
 * Enclose dates in quotes for _MYSQL
 *
 * Revision 1.12  2006/08/30 18:30:00  jms
 * move LINUX to int64_t
 *
 * Revision 1.11  2006/08/24 16:31:55  jms
 * add ifdef to config.h to address NCR porting problem with int32_t
 *
 * Revision 1.10  2006/05/10 23:10:58  jms
 * move solaris to stdlib.h
 *
 * Revision 1.9  2006/05/10 23:09:17  jms
 * move hpux to stdlib.h
 *
 * Revision 1.8  2006/05/10 22:03:21  jms
 * Porting cleanup
 *
 * Revision 1.7  2006/04/27 21:14:03  jms
 * Bug 424: move AIX to limits.h
 *
 * Revision 1.6  2006/01/16 22:15:47  jms
 * bug #362: include stdlib.h
 *
 * Revision 1.5  2006/01/07 00:45:27  jms
 * add FLEX to LINUX defines
 *
 * Revision 1.4  2005/02/21 23:25:53  jms
 * Porting corrections
 *
 * Revision 1.3  2005/02/11 19:42:54  jms
 * Bug #132: values.h needed for NCR MP/RAS
 *
 * Revision 1.2  2004/11/24 23:54:15  jms
 * correct unix/dos line termination
 *
 * Revision 1.1.1.1  2004/11/24 22:57:03  jms
 * re-establish external server
 *
 * Revision 1.8  2004/10/06 20:45:27  jms
 * Bug #83: support for INTERNIX (and cleanup of porting.h/config.h)
 *
 * Revision 1.7  2004/08/25 23:00:47  jms
 * initial checkin of revised QGEN
 *
 * Revision 1.6  2004/08/23 22:06:38  jms
 * change ds_key_t to signed for SOLARIS
 *
 * Revision 1.5  2003/10/28 01:46:56  jms
 * checkin of ETL generation changes through s_store
 *
 * Revision 1.10  2003/07/18 19:59:09  jms
 * update for 1.1.9
 *
 * Revision 1.9  2003/07/15 17:09:08  jms
 * add support for HPUX
 *
 * Revision 1.8  2003/04/26 01:02:21  jms
 * release 1.1.4 to Meikel
 *
 * Revision 1.7  2003/04/23 19:15:08  jms
 * fixes to bug 14: build under MP-RAS
 *
 * Revision 1.6  2003/04/16 22:40:04  jms
 * linux checkin of 1.1.0 pre-release
 *
 * Revision 1.5  2003/03/21 19:56:44  jms
 * resync with code on laptap
 *
 * Revision 1.4  2002/11/05 06:24:46  jms
 * alignment of WAM and DBGEN schemas to create 0.0.6
 *
 * Revision 1.3  2002/08/13 23:13:08  jms
 * porting to Solaris 9
 *
 * Revision 1.2  2002/07/27 00:08:48  jms
 * merge of WAM10 changes from sriram and linkage of sales and returns
 *
 * Revision 1.1.1.1.2.2  2002/07/19 00:21:37  jms
 * update the HUGE_FORMAT for linux
 *
 * Revision 1.1.1.1.2.1  2002/07/18 22:10:33  jms
 * clean up handling of HUGE_TYPE
 * add config.h and/or porting.h where needed
 *
 * Revision 1.1.1.1  2002/06/14 17:20:25  jms
 * CVS Baseline
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef NCR
#define STDLIB_HAS_GETOPT
#define USE_STRING_H
#define USE_VALUES_H
#ifdef SQLSERVER
#define WIN32
#else
/* the 64 bit defines are for the Metaware compiler */
#define SUPPORT_64BITS
#define HUGE_TYPE long long
#define HUGE_COUNT	1
#define HUGE_FORMAT "%LLd"
#define int32_t int
#endif /* SQLSERVER or MP/RAS */
#endif /* NCR */

#ifdef AIX
#define _ALL_SOURCE
#define USE_STRING_H
#define USE_LIMITS_H
/*
 * if the C compiler is 3.1 or later, then uncomment the
 * lines for 64 bit seed generation
 */
#define SUPPORT_64BITS
#define HUGE_TYPE long long
#define HUGE_COUNT	1
#define HUGE_FORMAT	"%lld"
#define STDLIB_HAS_GETOPT
#define USE_STDLIB_H
#define FLEX
#endif /* AIX */

#ifdef CYGWIN
#define USE_STRING_H
#define PATH_SEP	'\\'
#define SUPPORT_64BITS
#define HUGE_TYPE __int64
#define HUGE_COUNT	1
#define HUGE_FORMAT "%I64d"
#endif /* WIN32 */

#ifdef HPUX
#define SUPPORT_64BITS
#define HUGE_TYPE	long long int
#define HUGE_FORMAT	"%lld"
#define HUGE_COUNT	1
#define USE_STRING_H
#define USE_VALUES_H
#define USE_STDLIB_H
#define FLEX
#endif /* HPUX */

#ifdef INTERIX
#define USE_LIMITS_H
#define SUPPORT_64BITS
#define HUGE_TYPE long long int
#define HUGE_FORMAT "%lld"
#define HUGE_COUNT 1
#endif /* INTERIX */

#ifdef LINUX
#define SUPPORT_64BITS
#define HUGE_TYPE	int64_t
#define HUGE_FORMAT	"%lld"
#define HUGE_COUNT	1
#define USE_STRING_H
#define USE_VALUES_H
#define USE_STDLIB_H
#define FLEX
#endif /* LINUX */

#ifdef SOLARIS
#define SUPPORT_64BITS
#define HUGE_TYPE	long long 
#define HUGE_FORMAT	"%lld"
#define HUGE_COUNT	1
#define USE_STRING_H
#define USE_VALUES_H
#define USE_STDLIB_H
#endif /* SOLARIS */

#ifdef WIN32
#define USE_STRING_H
#define USE_LIMITS_H
#define PATH_SEP	'\\'
#define SUPPORT_64BITS
#define HUGE_TYPE __int64
#define HUGE_COUNT	1
#define HUGE_FORMAT "%I64d"
#endif /* WIN32 */

/* preliminary defines for 64-bit windows compile */
#ifdef WIN64
#define USE_STRING_H
#define PATH_SEP	'\\'
#define SUPPORT_64BITS
#define HUGE_TYPE __int64
#define HUGE_COUNT	1
#define HUGE_FORMAT "%I64d"
#endif /* WIN32 */

#ifndef PATH_SEP
#define PATH_SEP '/'
#endif /* PATH_SEP */

#ifndef HUGE_TYPE
#error The code now requires 64b support
#endif

/***
 ** DATABASE DEFINES
 ***/
#ifdef _MYSQL
#define STR_QUOTES
#endif
#endif /* CONFIG_H */

