/*
 * @(#) porting.h 3.1.1.1@(#)
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
 * (C) COPYRIGHT Gradient Systems Inc. 1997 - 2000
 *
 * All Rights Reserved  
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
 * The copyright notice above does not evidence any   
 * actual or intended publication of such source code.
 */
#ifndef PORTING_H
#define PORTING_H

#ifdef USE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

/*
#ifdef USE_VALUES_H
#include <values.h>
#endif
*/

//#ifdef USE_LIMITS_H
#include <limits.h>
//#endif

#ifdef USE_STDLIB_H
#include <stdlib.h>
#endif

#ifndef WIN32
#include <sys/types.h>
#else
#define int32_t   __int32
#define int64_t   __int64
#endif

#ifdef WIN32
#include <sys/timeb.h>
#define timeb _timeb
#define ftime _ftime
#else
#include <sys/timeb.h>
#endif

typedef HUGE_TYPE ds_key_t;

/*
 * add some functions that are not strictly ANSI standard
 */
#ifndef strdup
char *strdup(const char *);
#endif

#ifdef WIN32
#include <windows.h>
#include <winbase.h>
#include <io.h>
#define random rand
#define strncasecmp _strnicmp
#define strcasecmp	_stricmp
#define strdup _strdup
#define access _access
#define isatty	_isatty
#define fileno	_fileno
#define F_OK   0
#define MAXINT INT_MAX
#define THREAD __declspec(thread)
#define MIN_MULTI_NODE_ROWS		100000
#define MIN_MULTI_THREAD_ROWS	5000
#define THREAD __declspec(thread)
/* Lines added by Chuck McDevitt for WIN32 support */
#ifndef _POSIX_
#ifndef S_ISREG
#define S_ISREG(m) ( ((m) & _S_IFMT) == _S_IFREG )
#define S_ISFIFO(m) ( ((m) & _S_IFMT) == _S_IFIFO )
#endif 
#endif
#endif /* WIN32 */

#ifdef INTERIX
#include <limits.h>
#define MAXINT INT_MAX
#endif /* INTERIX */

#ifdef AIX
#define MAXINT INT_MAX
#endif


#define INTERNAL(m) {\
fprintf(stderr, "ERROR: %s\n\tFile: %s\n\tLine: %d\n", \
	m, __FILE__, __LINE__); \
}

#define OPEN_CHECK(var, path) \
    if ((var) == NULL) \
        { \
        fprintf(stderr, "Open failed for %s at %s:%d\n",  \
            path, __FILE__, __LINE__); \
        exit(1);\
        }

#ifdef MEM_TEST
#define MALLOC_CHECK(v)	\
	if (v == NULL)	\
		{	\
		fprintf(stderr, "Malloc Failed at %d in %s\n", __LINE__, __FILE__);	\
		exit(1);	\
		} \
	else \
		{ \
		fprintf(stderr, "Add (%x) %d at %d in %s\n", sizeof(*v), v, __LINE__, __FILE__); \
		}
#else
#define MALLOC_CHECK(v)	\
	if (v == NULL)	\
		{	\
		fprintf(stderr, "Malloc Failed at %d in %s\n", __LINE__, __FILE__);	\
		exit(1);	\
		} 
#endif /* MEM_TEST */
#endif
