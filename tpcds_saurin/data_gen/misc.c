/*
* $Id: misc.c,v 1.4 2006/05/10 22:03:22 jms Exp $
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
* $Log: misc.c,v $
* Revision 1.4  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.3  2005/02/21 23:25:53  jms
* Porting corrections
*
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.7  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.6  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.7  2003/07/18 19:59:09  jms
* update for 1.1.9
*
* Revision 1.6  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.5  2002/11/05 06:24:47  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.4  2002/08/28 21:58:46  jms
* Rework print_date to rely on julian dates as part of change for data type for xx_rec_{start,end}_id (sriram, 8/27/02)
*
* Revision 1.3  2002/08/19 16:03:14  jms
* Change parameter OUTDIR to DIR and add to help list
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/04 01:20:06  jms
* Added print_boolean() to handle Y/N flags
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/

#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#ifndef _POSIX_SOURCE
//#include <malloc.h>
#endif /* POSIX_SOURCE */
#include <fcntl.h>
#ifdef AIX
#include <sys/mode.h>
#endif /* AIX */
#include <sys/types.h>
#include <sys/stat.h>
#include "date.h"
#include "decimal.h"
#include "dist.h"
#include "misc.h"
#include "tdefs.h"
#include "r_params.h"
#include "genrand.h"

static char alpha_num[65] =
   "0123456789abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ,";


char *getenv (const char *name);
int print_separator (int sep);

extern long Seed[];


#ifdef WIN32
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

int file_num = -1;

/*
 *
 * Various routines that handle distributions, value selections and
 * seed value management for the DSS benchmark. Current functions:
 * env_config -- set config vars with optional environment override
 * a_rnd(min, max) -- random alphanumeric within length range
 */

/*
 * env_config: look for a environmental variable setting and return its
 * value; otherwise return the default supplied
 */
char *
env_config (char *var, char *dflt)
{
   static char *evar;

   if ((evar = getenv (var)) != NULL)
      return (evar);
   else
      return (dflt);
}

/*
 * generate a random string with length randomly selected in [min, max]
 * and using the characters in alphanum (currently includes a space
 * and comma)
 */
int
a_rnd (int min, int max, int column, char *dest)
{
   int i,
     len,
     char_int;

   genrand_integer (&len, DIST_UNIFORM, min, max, 0, column);
   for (i = 0; i < len; i++)
     {
        if (i % 5 == 0)
           genrand_integer (&char_int, DIST_UNIFORM, 0, 1 << 30, 0, column);
        *(dest + i) = alpha_num[char_int & 077];
        char_int >>= 6;
     }
   *(dest + len) = '\0';
   return (len);
}
