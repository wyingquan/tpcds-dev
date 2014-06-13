
/*
* $Id: genrand.c,v 1.15 2006/11/17 19:59:07 jms Exp $
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
* $Log: genrand.c,v $
* Revision 1.15  2006/11/17 19:59:07  jms
* Checkin for 47 (redo to address sync issues)
*
* Revision 1.14  2006/11/01 00:30:30  jms
* remove RNG debug statement
*
* Revision 1.13  2006/10/11 23:55:37  jms
* minor changes as part of parallelism exploration
*
* Revision 1.12  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.11  2006/05/12 21:01:58  jms
* porting cleanup
*
* Revision 1.10  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.9  2006/04/28 00:39:51  jms
* header file cleanup
*
* Revision 1.8  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.7  2006/01/02 19:39:49  jms
* Bug 357: segfault when building updates
*
* Revision 1.6  2005/10/05 17:31:35  jms
* bug #239: need data validation method
*
* Revision 1.5  2005/10/03 17:13:28  jms
* seed RNG seed from command line
*
* Revision 1.4  2005/02/21 23:26:31  jms
* source schema data generation
*
* Revision 1.3  2005/01/13 19:46:42  jms
* Add setSeed() to allow temporary use of a RNG stream
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.25  2004/10/19 18:16:25  jms
* Initial cleanup of source schema generation
*
* Revision 1.24  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.23  2004/05/03 22:38:05  jms
* remove double subtraction in RNG skip for parallelism
*
* Revision 1.22  2004/04/30 00:14:28  jms
* ???
*
* Revision 1.21  2004/04/27 21:28:38  jms
* re-introduce the skip_random algorithm from TPCH
*
* Revision 1.20  2004/04/11 18:08:18  jms
* try to speed up skip_row
*
* Revision 1.19  2004/04/08 04:52:11  jms
* reset nUsed after row_skip
*
* Revision 1.18  2004/04/07 22:44:25  jms
* changes diagnosing parallelism
*
* Revision 1.17  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.16  2004/04/02 18:02:58  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.15  2004/03/27 00:37:37  jms
* parallelism and windows porting changes
*
* Revision 1.14  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.13  2003/04/23 18:59:55  jms
* remove qsort from init_rand
*
* Revision 1.12  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.11  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.10  2002/09/04 18:25:55  jms
* last column is MAX_COLUMN not MAX_COLUMNS
*
* Revision 1.9  2002/09/04 17:27:14  jms
* Relocate rng_t genrand.h
* Rework rng_init()
* Add RNGReset
* Correct row_start and row_stop
*
* Revision 1.8  2002/08/19 15:36:27  jms
* fix warning message in call to genrand_integer() from skip_row()
*
* Revision 1.7  2002/08/16 23:23:31  jms
* no message
*
* Revision 1.6  2002/08/15 19:07:36  jms
* integrate mkheader into RNG usage as prep for parallel generation
*
* Revision 1.5  2002/08/14 00:15:49  jms
* unification of columns.h and streams.h
* update of tpcds.sql to match current WAM file
*
* Revision 1.4  2002/07/30 22:30:00  jms
* diff leftovers removed
*
* Revision 1.3  2002/07/27 00:08:30  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
*
* Revision 1.2  2002/07/03 21:57:01  jms
* introduce row_skip() to allow linkage between parent/child while allowing parallel generation
*
* Revision 1.1.1.1.2.1  2002/07/22 22:46:14  jms
* replacing missing changes to align with WAM 10
* corrections to set_pricing() to align with WAM 10
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <search.h>
#endif
#include <limits.h>
//#endif
#include "config.h"
#include "porting.h"
#include "decimal.h"
#include "date.h"
#include "genrand.h"
#include "dist.h"
#include "r_params.h"
#include "params.h"

#include "columns.h"
#include "tables.h"
#include "streams.h"

#define MAXINT	INT_MAX

static long Mult = 16807;       /* the multiplier */
static long nQ = 127773;        /* the quotient MAXINT / Mult */
static long nR = 2836;          /* the remainder MAXINT % Mult */
void NthElement (HUGE_TYPE N, int nStream);

/*
 * Routine: next_random(int stream)
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
long
next_random (int stream)
{
   long s = Streams[stream].nSeed,
     div_res,
     mod_res;

   div_res = s / nQ;
   mod_res = s - nQ * div_res;  /* i.e., mod_res = s % nQ */
   s = Mult * mod_res - div_res * nR;
   if (s < 0)
      s += MAXINT;
   Streams[stream].nSeed = s;
   Streams[stream].nUsed += 1;
#ifdef JMS
   Streams[stream].nTotal += 1;
#endif
   return (s);
}

/*
 * Routine: next_random_float(int stream)
 * Purpose:  return random in [0..1]
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
double
next_random_float (int stream)
{
   long res;

   res = next_random (stream);

   return ((double) res / (double) MAXINT);
}

/*
 * Routine: skip_random(int stream, int skip_count)
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
skip_random (int nStream, ds_key_t N)
{
   ds_key_t Z;
   ds_key_t M;

#ifdef UNDEF
	fprintf(stderr, "skipping stream %d to %d\n", nStream, N);
   Streams[nStream].nTotal = N;
#endif
   M = Mult;
   Z = (ds_key_t) Streams[nStream].nInitialSeed;
   while (N > 0)
     {
        if (N % 2 != 0)         /* testing for oddness, this seems portable */
           Z = (M * Z) % MAXINT;
        N = N / 2;              /* integer division, truncates */
        M = (M * M) % MAXINT;
     }
   Streams[nStream].nSeed = (long) Z;

   return;
}

/*
 * Routine: genrand_integer(int dist, int min, int max, int mean)
 * Purpose: generate a random integer given the distribution and limits
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns: int
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 */
int
genrand_integer (int *dest, int dist, int min, int max, int mean, int stream)
{
   int res = 0,
     i;
   double fres = 0;

   switch (dist)
     {
     case DIST_UNIFORM:
        res = next_random (stream);
        res %= max - min + 1;
        res += min;
        break;
     case DIST_EXPONENTIAL:
        for (i = 0; i < 12; i++)
           fres += (double) (next_random (stream) / MAXINT) - 0.5;
        res = min + (int) ((max - min + 1) * fres);
        break;
     default:
        INTERNAL ("Undefined distribution");
        break;
     }

   if (dest == NULL)
      return (res);

   *dest = res;

   return (0);
}

/*
 * Routine: genrand_key(ket_t *dest, int dist, ds_key_t min, ds_key_t max, ds_key_t mean, int stream)
 * Purpose: generate a random integer given the distribution and limits
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns: ds_key_t
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: Need to rework to rely on RNG routines that will work for 64 bit return values
 */
ds_key_t
genrand_key (ds_key_t * dest, int dist, ds_key_t min, ds_key_t max,
             ds_key_t mean, int stream)
{
   int res = 0,
     i;
   double fres = 0;

   switch (dist)
     {
     case DIST_UNIFORM:
        res = next_random (stream);
        res %= (int) (max - min + 1);
        res += (int) min;
        break;
     case DIST_EXPONENTIAL:
        for (i = 0; i < 12; i++)
           fres += (double) (next_random (stream) / MAXINT) - 0.5;
        res = (int) min + (int) ((max - min + 1) * fres);
        break;
     default:
        INTERNAL ("Undefined distribution");
        break;
     }

   if (dest == NULL)
      return ((ds_key_t) res);

   *dest = (ds_key_t) res;

   return ((ds_key_t) 0);
}

/*
 * Routine: 
 *	genrand_decimal(int dist, decimal_t *min, decimal_t *max, decimal_t *mean)
 * Purpose: create a random decimal_t
 * Algorithm:
 * Data Structures:
 *
 * Params: min/max are char * to allow easy passing of precision
 * Returns: decimal_t *; NULL on failure
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
int
genrand_decimal (decimal_t * dest, int dist, decimal_t * min, decimal_t * max,
                 decimal_t * mean, int stream)
{
   int i;
   decimal_t res;
   double fres = 0.0;

   if (min->precision < max->precision)
      dest->precision = min->precision;
   else
      dest->precision = max->precision;


   switch (dist)
     {
     case DIST_UNIFORM:
        res.number = next_random (stream);
        res.number %= max->number - min->number + 1;
        res.number += min->number;
        break;
     case DIST_EXPONENTIAL:
        for (i = 0; i < 12; i++)
          {
             fres /= 2.0;
             fres +=
                (double) ((double) next_random (stream) / (double) MAXINT) -
                0.5;
          }
        res.number =
           mean->number + (int) ((max->number - min->number + 1) * fres);
        break;
     default:
        INTERNAL ("Undefined distribution");
        break;
     }

   dest->number = res.number;
   i = 0;
   while (res.number > 10)
     {
        res.number /= 10;
        i += 1;
     }
   dest->scale = i;

   return (0);
}


/* Routine: RNGReset(int tbl)
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
RNGReset (int tbl)
{
   int i;

   for (i = 0; Streams[i].nColumn != -1; i++)
      if (Streams[i].nTable == tbl)
         Streams[i].nSeed = Streams[i].nInitialSeed;

   return (0);
}


/* WARNING!  This routine assumes the existence of 64-bit                 */

/* integers.  The notation used here- "HUGE" is *not* ANSI standard. */

/* Hopefully, you have this extension as well.  If not, use whatever      */

/* nonstandard trick you need to in order to get 64 bit integers.         */

/* The book says that this will work if MAXINT for the type you choose    */

/* is at least 2**46  - 1, so 64 bits is more than you *really* need      */

static HUGE_TYPE Multiplier = 16807;    /* or whatever nonstandard */
static HUGE_TYPE Modulus = 2147483647;  /* trick you use to get 64 bit int */

/* Advances value of Seed after N applications of the random number generator
   with multiplier Mult and given Modulus.
   NthElement(Seed[],count);

   Theory:  We are using a generator of the form
        X_n = [Mult * X_(n-1)]  mod Modulus.    It turns out that
        X_n = [(Mult ** n) X_0] mod Modulus.
   This can be computed using a divide-and-conquer technique, see
   the code below.

   In words, this means that if you want the value of the Seed after n
   applications of the generator,  you multiply the initial value of the
   Seed by the "super multiplier" which is the basic multiplier raised
   to the nth power, and then take mod Modulus.
*/

/* Nth Element of sequence starting with StartSeed */
void
NthElement (HUGE_TYPE N, int nStream)
{
   HUGE_TYPE Z;
   HUGE_TYPE Mult;

   Mult = Multiplier;
   Z = (HUGE_TYPE) Streams[nStream].nInitialSeed;
   while (N > 0)
     {
        if (N % 2 != 0)         /* testing for oddness, this seems portable */
          {
#ifdef JMS
             Streams[nStream].nTotal += 1;
#endif
             Z = (Mult * Z) % Modulus;
          }
        N = N / 2;              /* integer division, truncates */
        Mult = (Mult * Mult) % Modulus;
#ifdef JMS
        Streams[nStream].nTotal += 2;
#endif
     }
   Streams[nStream].nSeed = (long) Z;

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
int
dump_seeds (int tbl)
{
   int i;

   for (i = 0; Streams[i].nColumn != -1; i++)
      if (Streams[i].nTable == tbl)
         printf ("%04d\t%09d\t%09ld\n", i, Streams[i].nUsed, Streams[i].nSeed);
   return (0);
}

/*
 * Routine: gen_charset(char *set, int min, int max)
 * Purpose: generate random characters from set for a random length [min..max]
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
gen_charset (char *dest, char *set, int min, int max, int stream)
{
   int len,
     i,
     temp;

   if (set == NULL)
     {
        dest = NULL;
        return (-1);
     }

   genrand_integer (&len, DIST_UNIFORM, min, max, 0, stream);

   for (i = 0; i < max; i++)
     {
        genrand_integer (&temp, DIST_UNIFORM, 0, strlen (set) - 1, 0, stream);
        if (i < len)
			dest[i] = *(set + temp);
     }
   dest[len] = '\0';

   return (0);

}

/*
 * Routine: genrand_date(int dist, date_t *min, date_t *max)
 * Purpose: generate random date within [min..max]
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
genrand_date (date_t * dest, int dist, date_t * min, date_t * max,
              date_t * mean, int stream)
{
   int range,
     imean = 0,
     temp,
     idt,
     nYear,
     nTotalWeight = 0,
     nDayCount;

   idt = dttoj (min);
   range = dttoj (max);
   range -= idt;
   nDayCount = min->day;
   nYear = min->year;

   switch (dist)
     {
     case DIST_SALES:
     case DIST_RETURNS:
        /* walk from min to max to "integrate" the distribution */
        while (range -= 1)
          {
             nTotalWeight +=
                dist_weight (NULL, "calendar", nDayCount,
                             dist + is_leap (nYear));
             if (nDayCount == 365 + is_leap (nYear))
               {
                  nYear += 1;
                  nDayCount = 1;
               }
             else
                nDayCount += 1;
          }
        /* pick a value in the resulting range */
        temp = genrand_integer (NULL, DIST_UNIFORM, 1, nTotalWeight, 0, stream);
        /* and walk it again to translate that back to a date */
        nDayCount = min->day;
        idt = min->julian;
        nYear = min->year;
        while (temp >= 0)
          {
             temp -=
                dist_weight (NULL, "calendar", nDayCount,
                             dist + is_leap (nYear));
             nDayCount += 1;
             idt += 1;
             if (nDayCount > 365 + is_leap (nYear))
               {
                  nYear += 1;
                  nDayCount = 1;
               }
          }
        break;
     case DIST_EXPONENTIAL:
        imean = dttoj (mean);
        imean -= idt;
     case DIST_UNIFORM:
        genrand_integer (&temp, dist, 0, range, imean, stream);
        idt += temp;
        break;
     default:
        break;
     }

   jtodt (dest, idt);

   return (0);

}

/**************
 **************
 **
 ** static routines
 **
 **************
 **************/

/*
 * Routine: init_rand()
 * Purpose: Initialize the RNG used throughout the code
 * Algorithm: To allow two columns to use the same stream of numbers (for joins), pre-sort
 *	the streams list by Duplicate and then assign values. Order by column after initialization
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 
 */
void
init_rand (void)
{
   static int bInit = 0;
   int i,
	skip,
	nSeed;

   if (!bInit)
     {
	   if (is_set("RNGSEED"))
		   nSeed =  get_int("RNGSEED");
	   else
		   nSeed = RNG_SEED;
        skip = MAXINT / MAX_COLUMN;
        for (i = 0; i < MAX_COLUMN; i++)
          {
             Streams[i].nInitialSeed = nSeed + skip * i;
             Streams[i].nSeed = nSeed + skip * i;
             Streams[i].nUsed = 0;
          }
        bInit = 1;
     }
   return;
}

void
resetSeeds(int nTable)
{
	int i;
	
	for (i = 0; i < MAX_COLUMN; i++)
		if (Streams[i].nTable == nTable)
			Streams[i].nSeed = Streams[i].nInitialSeed;
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
genrand_email (char *pEmail, char *pFirst, char *pLast, int nColumn)
{
   char *pDomain;
   char szCompany[50];
   int nCompanyLength;

   pick_distribution (&pDomain, "top_domains", 1, 1, nColumn);
   genrand_integer(&nCompanyLength, DIST_UNIFORM, 10, 20, 0, nColumn);
   gen_charset (&szCompany[0], ALPHANUM, 1, 20, nColumn);
   szCompany[nCompanyLength] = '\0';

   sprintf (pEmail, "%s.%s@%s.%s", pFirst, pLast, szCompany, pDomain);

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
genrand_ipaddr (char *pDest, int nColumn)
{
   int arQuads[4],
     i;

   for (i = 0; i < 4; i++)
      genrand_integer (&arQuads[i], DIST_UNIFORM, 1, 255, 0, nColumn);
   sprintf (pDest, "%03d.%03d.%03d.%03d",
            arQuads[0], arQuads[1], arQuads[2], arQuads[3]);

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
int
genrand_url (char *pDest, int nColumn)
{
   strcpy (pDest, "http://www.foo.com");

   return (0);
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
setSeed(int nStream, int nValue)
{
	int nRetValue;

	nRetValue = Streams[nStream].nSeed;
	Streams[nStream].nSeed = nValue;

	return(nRetValue);
}


#ifdef TEST
main ()
{
   printf ("r_genrand:No test routine has been defined for this module\n");

   exit (0);
}
#endif /* TEST */
