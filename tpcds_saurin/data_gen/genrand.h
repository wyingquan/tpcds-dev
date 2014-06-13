/*
* $Id: genrand.h,v 1.8 2006/10/11 23:55:37 jms Exp $
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
* $Log: genrand.h,v $
* Revision 1.8  2006/10/11 23:55:37  jms
* minor changes as part of parallelism exploration
*
* Revision 1.7  2006/10/10 16:37:43  jms
* changes for NullBitMap and chunking
*
* Revision 1.6  2006/03/09 23:00:08  jms
* dependency cleanup
*
* Revision 1.5  2005/10/05 17:31:35  jms
* bug #239: need data validation method
*
* Revision 1.4  2005/01/13 20:11:32  jms
* add missing parameter types to declaration of setSeed()
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
* Revision 1.11  2004/04/30 00:10:23  jms
* RNG debugging
*
* Revision 1.10  2004/04/07 22:44:25  jms
* changes diagnosing parallelism
*
* Revision 1.9  2004/04/02 23:58:49  jms
* speed up changes to row_start/row_end
*
* Revision 1.8  2004/04/02 18:02:58  jms
* remove RNGUsage now that random usage counts are handled in column_list.txt
*
* Revision 1.7  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.6  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.5  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.5  2003/04/23 18:59:37  jms
* remove MAX_COLUMNS from genrand.h -- defined in columns.h
*
* Revision 1.4  2002/09/04 17:20:03  jms
* Relocate rng_t to genrand.h
* Add nDuplicateOf (to allow shared RNG streams)
* Expose RNGRest() (to allow skip_row to go backwards)
* Export next_random (to get full 32 bits to bkeys)
*
* Revision 1.3  2002/07/27 00:08:30  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
*
* Revision 1.2  2002/07/03 21:57:01  jms
* introduce row_skip() to allow linkage between parent/child while allowing parallel generation
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef GENRAND_H
#define GENRAND_H
#include "decimal.h"
#include "date.h"
#include "dist.h"
#include "address.h"
#define JMS 1

typedef struct RNG_T 
{
int nUsed;
int nUsedPerRow;
long nSeed;
long nInitialSeed; /* used to allow skip_row() to back up */
int nColumn; /* column where this stream is used */
int nTable;	/* table where this stream is used */
int nDuplicateOf;	/* duplicate streams allow independent tables to share data streams */
#ifdef JMS
ds_key_t nTotal;
#endif
} rng_t;
extern rng_t Streams[];

#define FL_SEED_OVERRUN	0x0001

#define ALPHANUM	"abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ0123456789"
#define DIGITS	"0123456789"

#define RNG_SEED	19620718

int		genrand_integer(int *dest, int dist, int min, int max, int mean, int stream);
int		genrand_decimal(decimal_t *dest, int dist, decimal_t *min, decimal_t *max, decimal_t *mean, int stream);
int		genrand_date(date_t *dest, int dist, date_t *min, date_t *max, date_t *mean, int stream);
ds_key_t	genrand_key(ds_key_t *dest, int dist, ds_key_t min, ds_key_t max, ds_key_t mean, int stream);
int		gen_charset(char *dest, char *set, int min, int max, int stream);
int	dump_seeds(int tbl);
void	init_rand(void);
void	skip_random(int s, ds_key_t count);
int	RNGReset(int nTable);
long	next_random(int nStream);
void	genrand_email(char *pEmail, char *pFirst, char *pLast, int nColumn);
void	genrand_ipaddr(char *pDest, int nColumn);
int	genrand_url(char *pDest, int nColumn);
int	setSeed(int nStream, int nValue);
void resetSeeds(int nTable);

#endif
