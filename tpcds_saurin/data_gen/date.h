/*
* $Id: date.h,v 1.3 2006/05/12 17:09:06 jms Exp $
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
* $Log: date.h,v $
* Revision 1.3  2006/05/12 17:09:06  jms
* print routine cleanup (per RIchard Harlow)
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.6  2004/09/10 19:30:47  jms
* add missing data types to declaration for getDateWeightFromJulian
*
* Revision 1.5  2004/09/10 19:27:32  jms
* qgen updates for simple examples
*
* Revision 1.4  2004/08/25 23:51:35  jms
* port to LINUX
*
* Revision 1.3  2002/08/28 21:55:26  jms
* Relocate misplaced declaration of print_date()
*
* Revision 1.2  2002/06/24 19:54:29  jms
* removed extra comment tag
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef R_DATE_H
#define R_DATE_H
#include "mathops.h"

typedef struct DATE_T {
	int flags;
	int year;
	int month;
	int day;
	int julian;
	} date_t;

date_t *mk_date(void);

int	jtodt(date_t *dest, int i);
int	strtodt(date_t *dest, char *s);
date_t *strtodate(char *str);
int strtotime(char *str);

char		*dttostr(date_t *d);
int			dttoj(date_t *d);

int	date_t_op(date_t *dest, int o, date_t *d1, date_t *d2);
int	set_dow(date_t *d);
int is_leap(int year);
int day_number(date_t *d);
int date_part(date_t *d, int p);
int	set_outfile(int i);
int getDateWeightFromJulian(int jDay, int nDistribution);
#define CENTURY_SHIFT	20	/* years before this are assumed to be 2000's */
/*
 * DATE OPERATORS
 */
#define OP_FIRST_DOM	0x01	/* get date of first day of current month */
#define OP_LAST_DOM		0x02	/* get date of last day of current month; LY == 2/28) */
#define OP_SAME_LY		0x03	/* get date for same day/month, last year */
#define OP_SAME_LQ		0x04	/* get date for same offset in the prior quarter */

extern char *weekday_names[];

#endif /* R_DATE_H */
