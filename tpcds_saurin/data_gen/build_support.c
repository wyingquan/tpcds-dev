/*
* $Id: build_support.c,v 1.9 2006/08/24 23:50:58 jms Exp $
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
* $Log: build_support.c,v $
* Revision 1.9  2006/08/24 23:50:58  jms
* remove unused varibles
*
* Revision 1.8  2006/08/24 22:32:06  jms
* bug 351: corrections to bitmap_to_dist
*
* Revision 1.7  2006/08/24 21:53:30  jms
* Bug 351: move bitmap_to_dist to int32_t
*
* Revision 1.6  2006/05/10 22:03:21  jms
* Porting cleanup
*
* Revision 1.5  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.4  2006/04/27 20:18:45  jms
* Bug 423: ltoc was ASCII dependent
*
* Revision 1.3  2006/01/16 23:15:17  jms
* Bug 347: need range-based substitutions
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.20  2004/11/01 18:36:02  jms
* Bug #108: Seg fault of store at sf=1000
*
* Revision 1.19  2004/10/27 22:51:51  jms
* Source data corrections from Ruth's research
*
* Revision 1.18  2004/10/21 23:27:19  jms
* Distribution changes requested by Meikel on 10/15
*
* Revision 1.17  2004/09/23 04:08:58  jms
* Bug #91
*
* Revision 1.16  2004/06/03 20:29:49  jms
* better tdefs/w_tdefs/s_tdefs handling
*
* Revision 1.15  2004/04/06 17:34:44  jms
* keep small tables from being built repeatedly when called as part of parallel generation
*
* Revision 1.14  2004/04/02 18:17:30  jms
* porting concerns around bitmap_to_dist declaration
*
* Revision 1.13  2004/04/02 17:53:09  jms
* add random_to_bitmap() and dist_to_bitmap() to handle joins to demograhics tables which rely on composite keys
*
* Revision 1.12  2004/04/02 00:39:39  jms
* use ds_key_t in bitmap_to_dist for solaris
*
* Revision 1.11  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.10  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.9  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.22  2003/07/15 17:09:08  jms
* add support for HPUX
*
* Revision 1.21  2003/07/15 00:43:46  jms
* Porting changes for Linux
*
* Revision 1.20  2003/07/14 23:14:54  jms
* enable continuous scaling in integer GB
*
* Revision 1.19  2003/06/24 19:47:33  jms
* isolate scaling functions and allow scaling by GB (bug 34)
*
* Revision 1.18  2003/05/07 20:01:55  jms
* add embed_string() to include a random dist value into a pre-existing string of background noise
*
* Revision 1.17  2003/04/29 19:21:16  jms
* solaris porting fixes
*
* Revision 1.16  2003/04/29 00:42:29  jms
* item hierarchy and build changes
*
* Revision 1.15  2003/04/28 22:06:55  jms
* item hierarchy cleanup
*
* Revision 1.14  2003/04/26 01:02:21  jms
* release 1.1.4 to Meikel
*
* Revision 1.13  2003/04/23 22:48:24  jms
* compiler errors under MP-RAS
*
* Revision 1.12  2003/04/16 22:40:04  jms
* linux checkin of 1.1.0 pre-release
*
* Revision 1.11  2003/04/16 00:21:45  jms
* data set alignment
*
* Revision 1.10  2003/04/08 17:49:46  jms
* Release 1.0.9
*
* Revision 1.9  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.8  2002/11/20 01:14:04  jms
* removing multiplier from scale=0
*
* Revision 1.7  2002/11/05 06:24:46  jms
* alignment of WAM and DBGEN schemas to create 0.0.6
*
* Revision 1.6  2002/10/27 17:23:16  jms
* correct scaling for call_center and other type-2 tables
*
* Revision 1.5  2002/09/25 22:46:59  jms
* commit all open changes to allow tighter issue/change tracking
*
* Revision 1.4  2002/09/04 17:30:46  jms
* Isolate mk_join() and related routines to join.c
* Add mk_bkey and related routines
*
* Revision 1.3  2002/08/18 00:39:34  jms
* update scaling to most recent spreadsheet
* enable tdefs[].base for a scaling multiplier (10^x)
* include /scale 0 trap to disable multiplier and allow fast debug
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.1.1.2.1  2002/07/04 01:05:45  jms
* Return type of bitmap_to_dist() now voiid * to allow char/int types
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#ifndef WIN32
#include <netinet/in.h>
#endif
#include <math.h>
#include "decimal.h"
#include "constants.h"
#include "dist.h"
#include "r_params.h"
#include "genrand.h"
#include "tdefs.h"
#include "tables.h"
#include "build_support.h"
#include "genrand.h"
#include "columns.h"
#include "StringBuffer.h"
#include "error_msg.h"
#include "scaling.h"

/*
* Routine: hierarchy_item
* Purpose: 
*	select the hierarchy entry for this level
* Algorithm: Assumes a top-down ordering
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
hierarchy_item(int h_level, ds_key_t *id, char **name, ds_key_t kIndex)
{
	static int bInit = 0,
		nLastCategory = -1,
		nLastClass = -1,
		nBrandBase;
	int nBrandCount;
	static char *szClassDistName = NULL;
	char sTemp[6];

	if (!bInit)
	{
	bInit = 1;
	}
	
	switch(h_level)
	{
		case I_CATEGORY:
			nLastCategory = pick_distribution(name, "categories", 1, 1, h_level);
			*id = nLastCategory;
			nBrandBase = nLastCategory;
			nLastClass = -1;
			break;
		case I_CLASS: 
			if (nLastCategory == -1)
				ReportErrorNoLine(DBGEN_ERROR_HIERACHY_ORDER, "I_CLASS before I_CATEGORY", 1);
			dist_member(&szClassDistName, "categories", nLastCategory, 2);
			nLastClass = pick_distribution(name, szClassDistName, 1, 1, h_level);
			nLastCategory = -1;
			*id = nLastClass;
			break;
		case I_BRAND: 
			if (nLastClass == -1)
				ReportErrorNoLine(DBGEN_ERROR_HIERACHY_ORDER, "I_BRAND before I_CLASS", 1);
			dist_member(&nBrandCount, szClassDistName, nLastClass, 2);
			*id = kIndex % nBrandCount + 1;
			mk_word(*name, "brand_syllables", nBrandBase * 10 + nLastClass, 45, I_BRAND);
			sprintf(sTemp, " #%d", (int)*id);
			strcat(*name, sTemp);
			*id += (nBrandBase * 1000 + nLastClass) * 1000;
			break;
		default:
			printf("ERROR: Invalid call to hierarchy_item with argument '%d'\n",
			h_level);
			exit(1);
	}
	
	return;
}

/*
* Routine: mk_companyname()
* Purpose: 
*	yet another member of a set of routines used for address creation
* Algorithm:
*	create a hash, based on an index value, so that the same result can be derived
*	reliably and then build a word from a syllable set
* Data Structures:
*
* Params:
*	char * dest: target for resulting name
*	int nTable: to allow differing distributions
*	int nCompany: index value
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
*	20010615 JMS return code is meaningless
*	20030422 JMS should be replaced if there is no per-table variation
*/
int mk_companyname(char *dest, int nTable, int nCompany)
{
	mk_word(dest, "syllables", nCompany, 10, CC_COMPANY_NAME);

	return(0);
}

/*
* Routine: set_locale()
* Purpose: 
*	generate a reasonable lattitude and longitude based on a region and the USGS data on 
*	3500 counties in the US
* Algorithm:
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20011230 JMS set_locale() is just a placeholder; do we need geographic coords?
*/
int set_locale(int nRegion, decimal_t *longitude, decimal_t *latitude)
{
	static int init = 0;
	static decimal_t dZero;
	
	if (!init)
	{
		strtodec(&dZero, "0.00");
		init = 1;
	}
	
	memcpy(longitude, &dZero, sizeof(decimal_t));
	memcpy(latitude, &dZero, sizeof(decimal_t));

	return(0);
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
bitmap_to_dist(void *pDest, char *distname, ds_key_t *modulus, int vset, int stream)
{
	int32_t m,
		s;
	char msg[80];
	
	if ((s = distsize(distname)) == -1)
	{
		sprintf(msg, "Invalid distribution name '%s'", distname);
		INTERNAL(msg);
	}
	m = (int32_t)((*modulus % s) + 1);
	*modulus /= s;
	
	dist_member(pDest, distname, m, vset);
	
	return;
}

/*
* Routine: void dist_to_bitmap(int *pDest, char *szDistName, int nValueSet, int nWeightSet, int nStream)
* Purpose: Reverse engineer a composite key based on distributions
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
dist_to_bitmap(int *pDest, char *szDistName, int nValue, int nWeight, int nStream)
{
	*pDest *= distsize(szDistName);
	*pDest += pick_distribution(NULL, szDistName, nValue, nWeight, nStream);

	return;
}

/*
* Routine: void random_to_bitmap(int *pDest, int nDist, int nMin, int nMax, int nMean, int nStream)
* Purpose: Reverse engineer a composite key based on an integer range
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
random_to_bitmap(int *pDest, int nDist, int nMin, int nMax, int nMean, int nStream)
{
	*pDest *= nMax;
	*pDest += genrand_integer(NULL, nDist, nMin, nMax, nMean, nStream);

	return;
}


/*
* Routine: mk_word()
* Purpose: 
*	generate a gibberish word from a given syllable set
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
void
mk_word(char *dest, char *syl_set, ds_key_t src, int char_cnt, int col)
{
	ds_key_t i = src,
		nSyllableCount;
	char *cp;

	*dest = '\0';
	while (i > 0)
	{
		nSyllableCount = distsize(syl_set);
		dist_member(&cp, syl_set, (int)(i % nSyllableCount) + 1, 1);
		i /= nSyllableCount;
		if ((int)(strlen(dest) + strlen(cp)) <= char_cnt)
			strcat(dest, cp);
		else
			break;
	}

	return;
}

/*
* Routine: mk_surrogate()
* Purpose: create a character based surrogate key from a 64-bit value
* Algorithm: since the RNG routines produce a 32bit value, and surrogate keys can 
*	reach beyond that, use the RNG output to generate the lower end of a random string,
*	and build the upper end from a ds_key_t
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: ltoc()
* Assumptions: output is a 16 character string. Space is not checked
* Side Effects:
* TODO: 
* 20020830 jms may need to define a 64-bit form of htonl() for portable shift operations
*/
static char szXlate[16] = "ABCDEFGHIJKLMNOP";
static void ltoc(char *szDest, unsigned long nVal)
{
	int i; 
	char c;

	for (i=0; i < 8; i++)
	{
		c = szXlate[(nVal & 0xF)];
		*szDest++ = c;
		nVal >>= 4;
	}
	*szDest = '\0';
}

void 
mk_bkey(char *szDest, ds_key_t kPrimary, int nStream)
{
	unsigned long nTemp;

	nTemp = (unsigned long)(kPrimary >> 32);
	ltoc(szDest, nTemp);

	nTemp = (unsigned long)(kPrimary & 0xFFFFFFFF);
	ltoc(szDest + 8, nTemp);

	return;
}

/*
* Routine: embed_string(char *szDest, char *szDist, int nValue, int nWeight, int nStream)
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
embed_string(char *szDest, char *szDist, int nValue, int nWeight, int nStream)
{
	int nPosition;
	char *szWord = NULL;

	pick_distribution(&szWord, szDist, nValue, nWeight, nStream);
	nPosition = genrand_integer(NULL, DIST_UNIFORM, 0, strlen(szDest) - strlen(szWord) - 1, 0, nStream);
	strncpy(&szDest[nPosition], szWord, strlen(szWord));

	return(0);
}

/*
* Routine: set_scale()
* Purpose: link SCALE and SCALE_INDEX
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
SetScaleIndex(char *szName, char *szValue)
{
	int nScale;
	char szScale[2];
	
	if ((nScale = atoi(szValue)) == 0)
		nScale = 1;

	nScale = 1 + (int)log10(nScale);
	szScale[0] = '0' + nScale;
	szScale[1] = '\0';

	set_int("_SCALE_INDEX", szScale);

	return(atoi(szValue));
}

/*
* Routine: adjust the valid date window for source schema tables, based on
*	based on the update count, update window size, etc.
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
setUpdateDateRange(int nTable, date_t *pMinDate, date_t *pMaxDate)
{
	static int nUpdateNumber,
		bInit = 0;

	if (!bInit)
	{
		nUpdateNumber = get_int("UPDATE");
		bInit = 1;
	}

	switch(nTable)	/* no per-table changes at the moment; but could be */
	{
	default:
		strtodt(pMinDate, WAREHOUSE_LOAD_DATE);
		pMinDate->julian += UPDATE_INTERVAL * (nUpdateNumber - 1);
		jtodt(pMinDate, pMinDate->julian);
		jtodt(pMaxDate, pMinDate->julian + UPDATE_INTERVAL);
		break;
	}

	return;
}

