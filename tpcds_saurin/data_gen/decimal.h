/*
* $Id: decimal.h,v 1.3 2006/05/12 17:09:06 jms Exp $
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
* $Log: decimal.h,v $
* Revision 1.3  2006/05/12 17:09:06  jms
* print routine cleanup (per RIchard Harlow)
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.7  2004/11/01 17:38:36  jms
* Bug #109: Output error needs error message
*
* Revision 1.6  2004/08/25 23:51:35  jms
* port to LINUX
*
* Revision 1.5  2004/06/03 16:11:10  jms
* Bug #64: Add NULLs to data set
*
* Revision 1.4  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.3  2003/03/21 19:56:44  jms
* resync with code on laptap
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
#ifndef R_DECIMAL_H
#define R_DECIMAL_H
#include "config.h"
#include "porting.h"
#include "mathops.h"
#include <stdio.h>

/*
 * a precise decimal data type, using scaled integer 
 * arithmetic.
 */
typedef struct DECIMAL_T {
	int flags;
	int precision;
	int scale;
	ds_key_t number;
} decimal_t;

#define FL_INIT		0x0004

decimal_t	*mk_decimal(int s, int p);

int itodec(decimal_t *dest, int i);
int ftodec(decimal_t *d, double f);
int strtodec(decimal_t *d, char *src);

int	dectostr(char *dest, decimal_t *d);
int dectof(double *dest, decimal_t *);
#define dectoi(d)	atoi(d->number)

int	decimal_t_op(decimal_t *dest, int o, decimal_t *d1, decimal_t *d2);
void	print_decimal(int nColumn, decimal_t *d, int s);
void	set_precision(decimal_t *d, int sie, int precision);
#define NegateDecimal(d) (d)->number *= -1
#endif /* R_DECIMAL_H */
