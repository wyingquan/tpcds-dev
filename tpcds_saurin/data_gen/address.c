/*
* $Id: address.c,v 1.9 2006/04/27 18:39:59 jms Exp $
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
* $Log: address.c,v $
* Revision 1.9  2006/04/27 18:39:59  jms
* Bug #432: zip ranges don't match
*
* Revision 1.8  2006/02/21 20:51:59  jms
* make county usage uniform
*
* Revision 1.7  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.6  2006/02/02 05:01:27  jms
* scale factor aware qgen
*
* Revision 1.5  2006/01/16 23:15:17  jms
* Bug 347: need range-based substitutions
*
* Revision 1.4  2005/11/22 22:29:14  jms
* change city selection to assure hits on store city in queries
*
* Revision 1.3  2005/11/22 21:12:44  jms
* add step function to city selection
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.7  2004/10/01 18:27:21  jms
* Bug #89: correct GMT distribution
*
* Revision 1.6  2004/09/23 17:20:54  jms
* Bug #95
*
* Revision 1.5  2004/08/20 20:08:25  jms
* changes from August F-2-F
*
* Revision 1.4  2004/05/14 06:58:13  jms
* changes requrested by Doug Johnson
* corrections to call_center and SCD handling
*
* Revision 1.3  2004/03/26 19:45:04  jms
* rename tdef_funtions.c to tdef_functions.c
*
* Revision 1.2  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "address.h"
#include "dist.h"
#include "r_params.h"
#include "genrand.h"
#include "columns.h"
#include "tables.h"
#include "tdefs.h"
#include "permute.h"
#include "scaling.h"

static int s_nCountyCount = 0;
static int s_nCityCount = 0;

void
resetCountCount(void)
{
   s_nCountyCount = 0;
   s_nCityCount = 0;

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
mk_address(ds_addr_t *pAddr, int nColumn)
{
	int i,
		nRegion;
	char *szZipPrefix,
		szAddr[100];
	static int nMaxCities,
      nMaxCounties,
		bInit = 0;
   tdef *pTdef;
		
	if (!bInit)
	{
      nMaxCities = (int)get_rowcount(ACTIVE_CITIES);
      nMaxCounties = (int)get_rowcount(ACTIVE_COUNTIES);
		bInit = 1;
	}
	
	/* street_number is [1..1000] */
	genrand_integer(&pAddr->street_num, DIST_UNIFORM, 1, 1000, 0, nColumn);

	/* street names are picked from a distribution */
	pick_distribution(&pAddr->street_name1, "street_names",1, 1, nColumn);
	pick_distribution(&pAddr->street_name2, "street_names", 1, 2, nColumn);

	/* street type is picked from a distribution */
	pick_distribution(&pAddr->street_type, "street_type", 1, 1, nColumn);

	/* suite number is alphabetic 50% of the time */
	genrand_integer(&i, DIST_UNIFORM, 1, 100, 0, nColumn);
	if (i & 0x01)
	{
		sprintf(pAddr->suite_num, "Suite %d", (i >> 1) * 10);
	}
	else
	{
		sprintf(pAddr->suite_num, "Suite %c", ((i >> 1) % 25) + 'A');
	}

	pTdef = getTdefsByNumber(getTableFromColumn(nColumn));
   
   /* city is picked from a distribution which maps to large/medium/small */
	if (pTdef->flags & FL_SMALL)
   {
      i = (int)get_rowcount(getTableFromColumn(nColumn));
      genrand_integer(&i, DIST_UNIFORM, 1, (nMaxCities > i)?i:nMaxCities, 0, nColumn);
		dist_member(&pAddr->city, "cities", i, 1);	
   }
	else
		pick_distribution(&pAddr->city, "cities", 1, 6, nColumn);
	

	/* county is picked from a distribution, based on population and keys the rest */
	if (pTdef->flags & FL_SMALL)
   {
      i = (int)get_rowcount(getTableFromColumn(nColumn));
      genrand_integer(&nRegion, DIST_UNIFORM, 1, (nMaxCounties > i)?i:nMaxCounties, 0, nColumn);
		dist_member(&pAddr->county, "fips_county", nRegion, 2);	
   }
   else
      nRegion = pick_distribution(&pAddr->county, "fips_county", 2, 1, nColumn);

   /* match state with the selected region/county */
   dist_member(&pAddr->state, "fips_county", nRegion, 3);
	
   /* match the zip prefix with the selected region/county */
	pAddr->zip = city_hash(0, pAddr->city);
   /* 00000 - 00600 are unused. Avoid them */
   dist_member((void *)&szZipPrefix, "fips_county", nRegion, 5);
   if (!(szZipPrefix[0] - '0') && (pAddr->zip < 9400))
      pAddr->zip += 600;      
	pAddr->zip += (szZipPrefix[0] - '0') * 10000;

	sprintf(szAddr, "%d %s %s %s", 
		pAddr->street_num, pAddr->street_name1, pAddr->street_name2, pAddr->street_type);
	pAddr->plus4 = city_hash(0, szAddr);
	dist_member (&pAddr->gmt_offset, "fips_county", nRegion, 6);
	strcpy(pAddr->country, "United States");

	return(0);
}


/*
* Routine: mk_streetnumber
* Purpose: 
*	one of a set of routines that creates addresses
* Algorithm:
* Data Structures:
*
* Params:
*	nTable: target table (and, by extension, address) to allow differing distributions
*	dest: destination for the random number
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20030422 jms should be replaced if there is no table variation
*/
int mk_streetnumber(int nTable, int *dest)
{
	genrand_integer(dest, DIST_UNIFORM, 1, 1000, 0, nTable);

	return(0);
}

/*
* Routine: mk_suitenumber()
* Purpose: 
*	one of a set of routines that creates addresses
* Algorithm:
* Data Structures:
*
* Params:
*	nTable: target table (and, by extension, address) to allow differing distributions
*	dest: destination for the random number
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20010615 JMS return code is meaningless
*/
int	mk_suitenumber(int nTable, char *dest)
{
	int i;

	genrand_integer(&i, DIST_UNIFORM, 1, 100, 0, nTable);
	if (i <= 50)
	{
		genrand_integer(&i, DIST_UNIFORM, 1, 1000, 0, nTable);
		sprintf(dest, "Suite %d", i);
	}
	else
	{
		genrand_integer(&i, DIST_UNIFORM, 0, 25, 0, nTable);
		sprintf(dest, "Suite %c", i + 'A');
	}

	return(0);
}

/*
* Routine: mk_streetname()
* Purpose: 
*	one of a set of routines that creates addresses
* Algorithm:
*	use a staggered distibution and the 150 most common street names in the US 
* Data Structures:
*
* Params:
*	nTable: target table (and, by extension, address) to allow differing distributions
*	dest: destination for the street name
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20010615 JMS return code is meaningless
*/
int mk_streetname(int nTable, char *dest)
{
	char *pTemp1 = NULL, 
		*pTemp2 = NULL;

	pick_distribution((void *)&pTemp1, "street_names", (int)1, (int)1, nTable);
	pick_distribution((void *)&pTemp2, "street_names", (int)1, (int)2, nTable);
	if (strlen(pTemp2))
		sprintf(dest, "%s %s", pTemp1, pTemp2);
	else
		strcpy(dest, pTemp1);

	return(0);
}

/*
* Routine: mk_city
* Purpose: 
*	one of a set of routines that creates addresses
* Algorithm:
*	use a staggered distibution of 1000 most common place names in the US 
* Data Structures:
*
* Params:
*	nTable: target table (and, by extension, address) to allow differing distributions
*	dest: destination for the city name
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20030423 jms should be replaced if there is no per-table variation
*/
int mk_city(int nTable, char **dest)
{
	pick_distribution((void *)dest, "cities", (int)1, (int)get_int("_SCALE_INDEX"), 11);

	return(0);
}

/*
* Routine: city_hash()
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
city_hash(int nTable, char *name)
{
	char *cp;
	int hash_value = 0,
		res = 0;

	for (cp = name; *cp; cp++)
		{
		hash_value *= 26;
		hash_value -= 'A';
		hash_value += *cp;
		if (hash_value > 1000000)
			{
			hash_value %= 10000;
			res += hash_value;
			hash_value = 0;
			}
		}
	hash_value %= 1000;
	res += hash_value;
	res %= 10000; 	/* looking for a 4 digit result */

	return(res);

}

/*
* Routine: 
*	one of a set of routines that creates addresses
* Algorithm:
*	use a compound distribution of the 3500 counties in the US 
* Data Structures:
*
* Params:
*	nTable: target table (and, by extension, address) to allow differing distributions
*	dest: destination for the city name
*	nRegion: the county selected
*	city: the city name selected
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20010615 JMS return code is meaningless
*/
int mk_zipcode(int nTable, char *dest, int nRegion, char *city)
{
	char *szZipPrefix = NULL;
	int nCityCode;
	int nPlusFour;

	dist_member((void *)&szZipPrefix, "fips_county", nRegion, 5);
	nCityCode = city_hash(nTable, city);
	genrand_integer(&nPlusFour, DIST_UNIFORM, 1, 9999, 0, nTable);
	sprintf(dest, "%s%04d-%04d", szZipPrefix, nCityCode, nPlusFour);

	return(0);
}

