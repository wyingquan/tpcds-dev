/*
* $Id: date.c,v 1.6 2006/05/12 17:09:06 jms Exp $
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
* $Log: date.c,v $
* Revision 1.6  2006/05/12 17:09:06  jms
* print routine cleanup (per RIchard Harlow)
*
* Revision 1.5  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.4  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.3  2006/03/01 00:22:39  jms
* Bug 397: catalog_sales dates are generated for 2003
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.6  2004/11/01 17:38:36  jms
* Bug #109: Output error needs error message
*
* Revision 1.5  2004/09/10 19:45:28  jms
* build corrections after unix port
* clean up of project files to remove need for lex/yacc on windows
*
* Revision 1.4  2004/09/10 19:27:31  jms
* qgen updates for simple examples
*
* Revision 1.3  2004/08/25 23:51:35  jms
* port to LINUX
*
* Revision 1.2  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2003/04/08 17:49:46  jms
* Release 1.0.9
*
* Revision 1.2  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/

/*** includes ***/
#include <stdlib.h>
#ifndef USE_STDLIB_H
//#include <malloc.h>
#endif
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "porting.h"
#include "date.h"
#include "mathops.h"
#include "dist.h"

#define D_CHARS		"ymdYMD24"	/* valid characters in a DBGDATE setting */
#define MIN_DATE_INT	18000101

static int m_days[2][13] =
	{
	{0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
	{0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
	};
static char *qtr_start[5] = {NULL, "01-01", "04-01", "07-01", "10-01"};
char *weekday_names[8] = {NULL, "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
/*
 * Routine: mk_date(void)
 * Purpose: initialize a date_t 
 * Algorithm:
 * Data Structures:
 * Params:	
 * Returns: date_t *
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
date_t *
mk_date(void)
{
	date_t *res;

	res = (date_t *)malloc(sizeof(struct DATE_T));
	MALLOC_CHECK(res);

	res->flags = 0;
	res->year = 0;
	res->month = 0;
	res->day = 0;
	res->julian = 0;

	return(res);
}
/*
 * Routine: strtotime(char *str)
 * Purpose: convert a string from the time to the number of seconds since midnight 
 * Algorithm:
 * Data Structures:
 * Params:	
 * Returns: int
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
int
strtotime(char *str)
{
	int hour, min, sec, res;

	if (sscanf(str, "%d:%d:%d", &hour, &min, &sec) != 3)
	{
		if (sscanf(str, "%d:%d", &hour, &min) != 2)
		{
			INTERNAL("Invalid time format");
		}
		sec = 0;
	}

	if (hour > 23 || hour < 0)
		INTERNAL("Invalid time format");
	if (min > 59 || min < 0)
		INTERNAL("Invalid time format");
	if (sec > 59 || sec < 0)
		INTERNAL("Invalid time format");

	res = hour * 3600 + min * 60 + sec;

	return(res);
}

/*
 * Routine: strtodate(char *str)
 * Purpose: initialize a date_t 
 * Algorithm:
 * Data Structures:
 * Params:	
 * Returns: date_t *
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
date_t *
strtodate(char *str)
{
	date_t *res;

	res = (date_t *)malloc(sizeof(struct DATE_T));
	MALLOC_CHECK(res);

	if (sscanf(str, "%d-%d-%d", &res->year, &res->month, &res->day) != 3)
		INTERNAL("Badly formed string in call to strtodate()");
	res->flags = 0;
	res->julian = dttoj(res);

	return(res);
}
/*
 * Routine: jtodt(int src, date_t *dest)
 * Purpose: convert a number of julian days to a date_t
 * Algorithm: Fleigel and Van Flandern (CACM, vol 11, #10, Oct. 1968, p. 657)
 * Data Structures:
 *
 * Params: source integer: days since big bang
 * Returns: date_t *; NULL on failure
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 
 */
int
jtodt(date_t *dest, int src)
{
	long i,
		j,
		l,
		n;

	if (src < 0)
		return(-1);
	
	dest->julian = src;
	l = src + 68569 ;
	n = (int)floor((4*l)/146097) ;
	l = l - (int)floor((146097 * n + 3)/4) ;
	i = (int)floor((4000 *(l + 1)/1461001)) ;
	l = l - (int)floor((1461*i)/4) + 31 ;
	j = (int)floor((80*l)/2447) ;
	dest->day = l - (int)floor((2447*j)/80) ;
	l=(int)floor(j/11) ;
	dest->month = j + 2 - 12*l ;
	dest->year = 100*(n-49) + i + l ;

	return(0);
}

/*
 * Routine: dttoj(date_t *)
 * Purpose: convert a date_t to a number of julian days
 * Algorithm: http://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
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
dttoj(date_t *dt)
{
	int y, m, res;

	y = dt->year;
	m = dt->month;
	if (m <= 2)
	{
		m += 12;
		y -= 1;
	}

/*
 * added 1 to get dttoj and jtodt to match
 */
   res = dt->day + (153 * m - 457) / 5 + 365 * y + (int)floor(y / 4) - (int)floor(y / 100) + (int)floor(y / 400) + 1721118 + 1;

	return(res);
}

/*
 * Routine: strtodt()
 * Purpose: Convert an ascii string to a date_t structure
 * Algorithm:
 * Data Structures:
 *
 * Params: char *s, date_t *dest
 * Returns: int; 0 on success
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: Need to allow for date formats other than Y4MD-
 */
int
strtodt(date_t *dest, char *s)
{
	int nRetCode = 0;
	
	if (s == NULL)
		{
		dest = NULL;
		return(-1);
		}
	
	if (sscanf(s, "%4d-%d-%d", &dest->year, &dest->month, &dest->day) != 3)
		{
		fprintf(stderr, "ERROR: Invalid string to date conversion in strtodt\n");
		nRetCode = -1;	
		}
	
	dest->julian = dttoj(dest);

	return(nRetCode);
}

/*
 * Routine: dttostr(date_t *d)
 * Purpose: convert a date_t structure to a string
 * Algorithm:
 * Data Structures:
 *
 * Params: 
 * Returns: char *; NULL on failure
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 20000110 Need to handle more than Y4MD-
 */
char *
dttostr(date_t *d)
{
	static char 	*res;
	static int init = 0;
	
	if (!init)
		{
		res = (char *)malloc(sizeof(char) * 11);
		MALLOC_CHECK(res);
		init = 1;
		}
		
	if (d == NULL)
		return(NULL);
	
	sprintf(res, "%4d-%02d-%02d", d->year, d->month, d->day);
	
	return(res);
}

/*
 * Routine: date_init
 * Purpose: set the date handling parameters
 * Algorithm:
 * Data Structures:
 *
 * Params: None
 * Returns: int; 0 on success
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: None
 */
int
date_init(void)
{
	printf("date_init is not yet complete\n");
	exit(1);
	return(0);
}

/*
 * Routine: date_t_op(int op, date_t *operand1, date_t *operand2)
 * Purpose: execute arbitrary binary operations on date_t's
 * Algorithm:
 * Data Structures:
 *
 * Params:
 * Returns:
 * Called By: 
 * Calls: 
 * Assumptions:
 * Side Effects:
 * TODO: 
 *	20010806 jms	Return code is meaningless
 */
int
date_t_op(date_t *dest, int op, date_t *d1, date_t *d2)
{
	int tJulian;
	char tString[11];
	date_t tDate;

	switch(op)
		{
	case OP_FIRST_DOM:	/* set to first day of month */
		tJulian = d1->julian - d1->day + 1;
		jtodt(dest, tJulian);
		break;
	case OP_LAST_DOM: /* set to last day of month */
		tJulian = d1->julian - d1->day + m_days[is_leap(d1->year)][d1->month];
		jtodt(dest, tJulian);
		break;
	case OP_SAME_LY:
		if (is_leap(d1->year) && (d1->month == 2) && (d1->day == 29))
			sprintf(tString, "%d-02-28", d1->year - 1);
		else
			sprintf(tString, "%4d-%02d-%02d", d1->year - 1, d1->month, d1->day);
		strtodt(dest, tString);
		break;
	case OP_SAME_LQ:
		switch(d1->month) {
		case 1:
		case 2:
		case 3:
			sprintf(tString, "%4d-%s", d1->year, qtr_start[1]);
			strtodt(&tDate, tString);
			tJulian = d1->julian - tDate.julian;
			sprintf(tString, "%4d-%s", d1->year - 1, qtr_start[4]);
			strtodt(&tDate, tString);
			tJulian += tDate.julian;
			jtodt(dest, tJulian);
			break;
		case 4:
		case 5:
		case 6:
			sprintf(tString, "%4d-%s", d1->year, qtr_start[2]);
			strtodt(&tDate, tString);
			tJulian = d1->julian - tDate.julian;
			sprintf(tString, "%4d-%s", d1->year, qtr_start[1]);
			strtodt(&tDate, tString);
			tJulian += tDate.julian;
			jtodt(dest, tJulian);
			break;
		case 7:
		case 8:
		case 9:
			sprintf(tString, "%4d-%s", d1->year, qtr_start[3]);
			strtodt(&tDate, tString);
			tJulian = d1->julian - tDate.julian;
			sprintf(tString, "%4d-%s", d1->year, qtr_start[2]);
			strtodt(&tDate, tString);
			tJulian += tDate.julian;
			jtodt(dest, tJulian);
			break;
		case 10:
		case 11:
		case 12:
			sprintf(tString, "%4d-%s", d1->year, qtr_start[4]);
			strtodt(&tDate, tString);
			tJulian = d1->julian - tDate.julian;
			sprintf(tString, "%4d-%s", d1->year, qtr_start[3]);
			strtodt(&tDate, tString);
			tJulian += tDate.julian;
			jtodt(dest, tJulian);
			break;
		}
		break;
		}

	return(0);
}

/*
 * Routine: itodt(date_t *d, int src)
 * Purpose:  convert a number of days to a date_t
 * Algorithm: NOTE: sets only julian field
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
itodt(date_t *dest, int src)
{

	dest->julian = src;

	return(0);
}

/*
 * Routine: set_dow(date *d)
 * Purpose: perpetual calendar stuff
 * Algorithm:
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
static int doomsday[4] = {3, 2, 0, 5};
static int known[13] = { 0, 3, 0, 0, 4, 9, 6, 11, 8, 5, 10, 7, 12 };
int
set_dow(date_t *d)
{

	static int last_year = -1, 
		dday;
	int res,
		q, r, s;


	if (d->year != last_year)
		{
		if (is_leap(d->year))
			{
			/* adjust the known dates for january and february */
			known[1] = 4;
			known[2] = 1;
			}
		else
			{
			known[1] = 3;
			known[2] = 0;
			}

		/* calculate the doomsday for the century */
		dday = d->year / 100;
		dday -= 15;
		dday %= 4;
		dday = doomsday[dday];

		/* and then calculate the doomsday for the year */
		q = d->year % 100;
		r = q % 12;
		q /= 12;
		s = r / 4;
		dday += q + r + s;
		dday %= 7;
		last_year = d->year;
		}

	res = d->day;
	res -= known[d->month];
	while (res < 0)
		res += 7;
	while (res > 6)
		res -= 7;
	
	res += dday;
	res %= 7;


	return(res);
}

/*
 * Routine: is_leap(year)
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
is_leap(int year)
{

		return (((year % 100) == 0)?((((year % 400) % 2) == 0)?1:0):((year % 4) == 0)?1:0);
}

/*
 * Routine: day_number(date_t *)
 * Purpose: 
 * Algorithm: NOTE: this is NOT the ordinal day in the year, but the ordinal reference into the 
 *	calendar distribution for the day; in particular, this needs to skip over the leap day
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
day_number(date_t *d)
{
	return(m_days[is_leap(d->year)][d->month] + d->day);
}

/*
 * Routine: getDateWeightFromJulian(jDay, nDistribution)
 * Purpose: return the weight associated with a particular julian date and distribution
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
getDateWeightFromJulian(jDay, nDistribution)
{
	date_t dTemp;
	int nDay;

	jtodt(&dTemp, jDay);
	nDay = day_number(&dTemp);

	return(dist_weight(NULL, "calendar", nDay, nDistribution + is_leap(dTemp.year)));
}


/*
 * Routine: date_part(date_t *, int part)
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
date_part(date_t *d, int part)
{
	switch(part)
	{
	case 1:	return(d->year);
	case 2:	return(d->month);
	case 3:	return(d->day);
	default: 
		INTERNAL("Invalid call to date_part()");
		return(-1);
	}
}

#ifdef TEST
main()
{
	date_t *d;
	int ret;

	d = mk_date();
	strtodt(d, "1776-07-04");
	ret = set_dow(d);
	printf("set_dow(\"1776-07-04\"): wanted 4 got %d\n", ret);
	if (ret != 4)
		{
		exit(1);
		}
	strtodt(d, "2000-01-01");
	ret = set_dow(d);
	printf("set_dow(\"2000-01-01\"): wanted 6 got %d\n", ret);
	if (ret != 6)
		{
		exit(1);
		}

	strtodt(d, "1970-01-01");
	if ((ret = dttoj(d)) != 2440588)
		{
		printf("dttoj returned %d\n", ret);
		exit(1);
		}

	d->year = 1;
	d->month = 11;
	d->date = 11;
	jtodt(d, 2440588);
	if ((d->year != 1970) || (d->month != 1) || (d->date != 1))
		{
		printf("jtodt failed got: ");
		printf("%4d-%02d-%02d", d->year, d->month, d->date);
		exit(1);
		}
	return(0);
}
#endif /* TEST */
