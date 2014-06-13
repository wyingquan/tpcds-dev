/*
* $Id: dist.c,v 1.13 2006/07/13 17:17:48 jms Exp $
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
* $Log: dist.c,v $
* Revision 1.13  2006/07/13 17:17:48  jms
* bug 470
*
* Revision 1.12  2006/07/13 12:51:21  jms
* Bug 470: move int to int32_t
*
* Revision 1.11  2006/05/12 21:01:58  jms
* porting cleanup
*
* Revision 1.10  2006/05/10 22:03:22  jms
* Porting cleanup
*
* Revision 1.9  2006/04/27 20:58:25  jms
* Bugs 424/425: header file cleanup for portability
*
* Revision 1.8  2006/03/17 20:04:59  jms
* rework update model to match new view definitions (Bugs: 363, 366)
*
* Revision 1.7  2006/01/08 23:37:15  jms
* add additional debug to dist_op
*
* Revision 1.6  2005/12/19 23:18:10  jms
* RI corrections
*
* Revision 1.5  2005/12/08 19:51:57  jms
* Bug 353: add cast to malloc call
*
* Revision 1.4  2005/10/17 17:59:19  jms
* updates to build
*
* Revision 1.3  2005/02/21 23:26:31  jms
* source schema data generation
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.14  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.13  2004/09/08 21:16:23  jms
* clarify error message
*
* Revision 1.12  2004/08/24 16:51:07  jms
* NCR porting changes
*
* Revision 1.11  2004/03/26 22:55:20  jms
* include malloc.h
*
* Revision 1.10  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.9  2004/03/26 19:45:04  jms
* rename tdef_funtions.c to tdef_functions.c
*
* Revision 1.8  2004/03/03 17:05:12  jms
* make distribution name lookup case insensitive
*
* Revision 1.7  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.6  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.14  2003/07/24 16:22:05  jms
* Misc build cleanup
*
* Revision 1.13  2003/07/18 19:59:09  jms
* update for 1.1.9
*
* Revision 1.12  2003/07/15 17:09:08  jms
* add support for HPUX
*
* Revision 1.11  2003/06/10 05:27:11  jms
* Bug 27: edge effect in pick_distribution() sorted out by adjusting random() range
*
* Revision 1.10  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.9  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.8  2003/04/23 19:15:08  jms
* fixes to bug 14: build under MP-RAS
*
* Revision 1.7  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.6  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.5  2002/11/20 00:51:33  jms
* QGEN2 corrections
*
* Revision 1.4  2002/09/04 18:25:05  jms
* d_idx_t entries need to be zero'd to assure dist loading
*
* Revision 1.3  2002/08/13 23:13:08  jms
* porting to Solaris 9
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
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
//#include <malloc.h>
#ifdef WIN32
#include <io.h>
#include <stdlib.h>
#include <search.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#endif
#ifdef NCR
#include <sys/types.h>
#endif
#ifndef USE_STDLIB_H
#include <malloc.h>
#endif
#include "config.h"
#include "decimal.h"
#include "date.h"
#include "dist.h"
#include "genrand.h"
#include "error_msg.h"
#include "r_params.h"
#include "dcomp.h"
#ifdef TEST
option_t options[] =
{
	{"DISTRIBUTIONS", OPT_STR, 2, 
		"read distributions from file <s>", NULL, "tester_dist.idx"},
		NULL
};

char params[2];
struct {char *name;} tdefs[] = {NULL};
#endif

/* NOTE: these need to be in sync with a_dist.h */
#define D_NAME_LEN	20
#define FL_LOADED	0x01
static int load_dist(d_idx_t *d);


/*
* Routine: di_compare()
* Purpose: comparison routine for two d_idx_t entries; used by qsort
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
di_compare(const void *op1, const void *op2)
{
	d_idx_t *ie1 = (d_idx_t *)op1,
		*ie2 = (d_idx_t *)op2;
	
	return(strcasecmp(ie1->name, ie2->name));
}

/*
* Routine: find_dist(char *name)
* Purpose: translate from dist_t name to d_idx_t *
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
d_idx_t *
find_dist(char *name)
{
	static int index_loaded = 0,
		entry_count;
	static d_idx_t *idx = NULL;
	d_idx_t key,
		*id = NULL;
	int i;
   FILE *ifp;
	int32_t temp;
	
	
	/* load the index if this is the first time through */
	if (!index_loaded)
	{
		/* make sure that this is read one thread at a time */
		if (!index_loaded)	/* make sure no one beat us to it */
		{
			
			/* open the dist file */
			if ((ifp = fopen(get_str("DISTRIBUTIONS"), "rb")) == NULL)
				{
					fprintf(stderr, "Error: open of distributions failed: ");
					perror(get_str("DISTRIBUTIONS"));
					exit(1);
				}
				if (fread( &temp,  1, sizeof(int32_t), ifp) != sizeof(int32_t))
				{
					fprintf(stderr, "Error: read of index count failed: ");
					perror(get_str("DISTRIBUTIONS"));
					exit(2);
				}
				entry_count = ntohl(temp);
				if ((temp = fseek(ifp, -entry_count * IDX_SIZE, SEEK_END)) < 0)
				{
					fprintf(stderr, "Error: lseek to index failed: ");
					fprintf(stderr, "attempting to reach %d\nSystem error: ", 
						(int)(-entry_count * IDX_SIZE));
					perror(get_str("DISTRIBUTIONS"));
					exit(3);
				}
				idx = (d_idx_t *)malloc(entry_count * sizeof(d_idx_t));
				MALLOC_CHECK(idx);
				for (i=0; i < entry_count; i++)
				{
					memset(idx + i, 0, sizeof(d_idx_t));
					if (fread( idx[i].name,  1, D_NAME_LEN, ifp) < D_NAME_LEN)
					{
						fprintf(stderr, "Error: read index failed (1): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].name[D_NAME_LEN] = '\0';
					if (fread( &temp,  1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (2): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].index = ntohl(temp);
					if (fread( &temp,  1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (4): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].offset = ntohl(temp);
					if (fread( &temp,  1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (5): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].str_space = ntohl(temp);
					if (fread( &temp, 1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (6): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].length = ntohl(temp);
					if (fread( &temp, 1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (7): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].w_width = ntohl(temp);
					if (fread( &temp, 1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (8): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].v_width = ntohl(temp);
					if (fread( &temp,  1, sizeof(int32_t), ifp) != sizeof(int32_t))
					{
						fprintf(stderr, "Error: read index failed (9): ");
						perror(get_str("DISTRIBUTIONS"));
						exit(2);
					}
					idx[i].name_space = ntohl(temp);
					idx[i].dist = NULL;
				}
				qsort((void *)idx, entry_count, sizeof(d_idx_t), di_compare);
				index_loaded = 1;
				
				/* make sure that this is read one thread at a time */
			fclose(ifp);
		}
	}
	
	/* find the distribution, if it exists and move to it */
	strcpy(key.name, name);
	id = (d_idx_t *)bsearch((void *)&key, (void *)idx, entry_count, 
		sizeof(d_idx_t), di_compare);
	if (id != NULL)	/* found a valid distribution */
		if (id->flags != FL_LOADED)	 /* but it needs to be loaded */
			load_dist(id);
		
		
		
		return(id);
}

/*
* Routine: load_dist(int fd, dist_t *d)
* Purpose: load a particular distribution
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
static int
load_dist(d_idx_t *di)
{
	int res = 0,
		i,
		j;
	dist_t *d;
	int32_t temp;
	FILE *ifp;
	
	if (di->flags != FL_LOADED)	/* make sure no one beat us to it */
	{
			if ((ifp = fopen(get_str("DISTRIBUTIONS"), "rb")) == NULL)
				{
					fprintf(stderr, "Error: open of distributions failed: ");
					perror(get_str("DISTRIBUTIONS"));
					exit(1);
				}
		
		if ((temp = fseek(ifp, di->offset, SEEK_SET)) < 0)
		{
			fprintf(stderr, "Error: lseek to distribution failed: ");
			perror("load_dist()");
			exit(2);
		}
		
		di->dist = (dist_t *)malloc(sizeof(struct DIST_T));
		MALLOC_CHECK(di->dist);
		d = di->dist;
		
		/* load the type information */
		d->type_vector = (int *)malloc(sizeof(int32_t) * di->v_width);
		MALLOC_CHECK(d->type_vector);
		for (i=0; i < di->v_width; i++)
		{
			if (fread(&temp, 1, sizeof(int32_t), ifp) != sizeof(int32_t))
			{
				fprintf(stderr, "Error: read of type vector failed for '%s': ", di->name);
				perror("load_dist()");
				exit(3);
			}
			d->type_vector[i] = ntohl(temp);
		}
		
		/* load the weights */
		d->weight_sets = (int **)malloc(sizeof(int *) * di->w_width);
		d->maximums = (int *)malloc(sizeof(int32_t) * di->w_width);
		MALLOC_CHECK(d->weight_sets);
		MALLOC_CHECK(d->maximums);
		for (i=0; i < di->w_width; i++)
		{
			*(d->weight_sets + i) = (int *)malloc(di->length * sizeof(int32_t));
			MALLOC_CHECK(*(d->weight_sets + i));
			d->maximums[i] = 0;
			for (j=0; j < di->length; j++)
			{
				if (fread(&temp, 1, sizeof(int32_t), ifp) < 0)
				{
					fprintf(stderr, "Error: read of weights failed: ");
					perror("load_dist()");
					exit(3);
				}
				*(*(d->weight_sets + i) + j) = ntohl(temp);
			/* calculate the maximum weight and convert sets to cummulative */
				d->maximums[i] += d->weight_sets[i][j];
				d->weight_sets[i][j] = d->maximums[i];
			}
		}
		
		/* load the value offsets */
		d->value_sets = (int **)malloc(sizeof(int *) * di->v_width);
		MALLOC_CHECK(d->value_sets);
		for (i=0; i < di->v_width; i++)
		{
			*(d->value_sets + i) = (int *)malloc(di->length * sizeof(int32_t));
			MALLOC_CHECK(*(d->value_sets + i));
			for (j=0; j < di->length; j++)
			{
				if (fread(&temp, 1, sizeof(int32_t), ifp) != sizeof(int32_t))
				{
					fprintf(stderr, "Error: read of values failed: ");
					perror("load_dist()");
					exit(4);
				}
				*(*(d->value_sets + i) + j) = ntohl(temp);
			}
		}
		
		/* load the column aliases, if they were defined */
		if (di->name_space)
		{
			d->names = (char *)malloc(di->name_space);
			MALLOC_CHECK(d->names);
			if (fread(d->names, 1, di->name_space * sizeof(char), ifp) < 0)
			{
				fprintf(stderr, "Error: read of names failed: ");
				perror("load_dist()");
				exit(599);
			}
			
		}

		/* and finally the values themselves */
		d->strings = (char *)malloc(sizeof(char) * di->str_space);
		MALLOC_CHECK(d->strings);
		if (fread(d->strings, 1, di->str_space * sizeof(char), ifp) < 0)
		{
			fprintf(stderr, "Error: read of strings failed: ");
			perror("load_dist()");
			exit(5);
		}
	
	fclose(ifp);
	di->flags = FL_LOADED;
	}

	
	
	return(res);
}

/*
* Routine: void *dist_op()
* Purpose: select a value/weight from a distribution
* Algorithm:
* Data Structures:
*
* Params:	char *d_name
*			int vset: which set of values
*			int wset: which set of weights
* Returns: appropriate data type cast as a void *
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 20000317 Need to be sure this is portable to NT and others
*/
int
dist_op(void *dest, int op, char *d_name, int vset, int wset, int stream)
{
	d_idx_t *d;
	dist_t *dist;
	int	level,
		index = 0,
		dt;
	char *char_val;
	int i_res = 1;
	
	if ((d = find_dist(d_name)) == NULL)
	{
		char msg[80];
		sprintf(msg, "Invalid distribution name '%s'", d_name);
		INTERNAL(msg);
		assert(d != NULL);
	}
		
	dist = d->dist;
	
	if (op == 0)
	{
		genrand_integer(&level, DIST_UNIFORM, 1, 
			dist->maximums[wset - 1], 0, stream);
		while (level > dist->weight_sets[wset - 1][index] && 
			index < d->length)
			index += 1;
		dt = vset - 1;
		if ((index >= d->length) || (dt > d->v_width))
			INTERNAL("Distribution overrun");
		char_val = dist->strings + dist->value_sets[dt][index];
	}
	else
	{ 
		index = vset - 1;
		dt = wset - 1;
		if (index >= d->length || index < 0)
		{
			fprintf(stderr, "Runtime ERROR: Distribution over-run/under-run\n");
			fprintf(stderr, "Check distribution definitions and usage for %s.\n",
			d->name);
			fprintf(stderr, "index = %d, length=%d.\n",
				index, d->length);
			exit(1);
		}
		char_val = dist->strings + dist->value_sets[dt][index];
	}
	
	
	switch(dist->type_vector[dt])
	{
	case TKN_VARCHAR:
		if (dest)
			*(char **)dest = (char *)char_val;
		break;
	case TKN_INT:
		i_res = atoi(char_val);
		if (dest)
			*(int *)dest = i_res;
		break;
	case TKN_DATE:
		if (dest == NULL)
		{
			dest = (date_t *)malloc(sizeof(date_t));
			MALLOC_CHECK(dest);
		}
		strtodt(*(date_t **)dest, char_val);
		break;
	case TKN_DECIMAL:
		if (dest == NULL)
		{
			dest = (decimal_t *)malloc(sizeof(decimal_t));
			MALLOC_CHECK(dest);
		}
		strtodec(*(decimal_t **)dest,char_val);
		break;
	}
	
	return((dest == NULL)?i_res:index + 1);	/* shift back to the 1-based indexing scheme */
}

/*
* Routine: int dist_weight
* Purpose: return the weight of a particular member of a distribution
* Algorithm:
* Data Structures:
*
* Params:	distribution *d
*			int index: which "row"
*			int wset: which set of weights
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: 
*	20000405 need to add error checking
*/
int
dist_weight(int *dest, char *d, int index, int wset)
{
	d_idx_t *d_idx;
	dist_t *dist;
	int res;
	
	if ((d_idx = find_dist(d)) == NULL)
	{
		char msg[80];
		sprintf(msg, "Invalid distribution name '%s'", d);
		INTERNAL(msg);
	}
	
	dist = d_idx->dist;
	
	res = dist->weight_sets[wset - 1][index - 1];
	/* reverse the accumulation of weights */
	if (index > 1)
		res -= dist->weight_sets[wset - 1][index - 2];
	
	if (dest == NULL)
		return(res);
	
	*dest = res;
	
	return(0);
}

/*
* Routine: int DistNameIndex()
* Purpose: return the index of a column alias
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
int
DistNameIndex(char *szDist, int nNameType, char *szName)
{
	d_idx_t *d_idx;
	dist_t *dist;
	int res;
	char *cp = NULL;
	
	if ((d_idx = find_dist(szDist)) == NULL)
		return(-1);	
	dist = d_idx->dist;
	
	if (dist->names == NULL)
		return(-1);

	res = 0;
	cp = dist->names;
	do {
		if (strcasecmp(szName, cp) == 0)
			break;
		cp += strlen(cp) + 1;
		res += 1;
	} while (res < (d_idx->v_width + d_idx->w_width));

	if (res >= 0)
	{
		if ((nNameType == VALUE_NAME) && (res < d_idx->v_width))
			return(res + 1);
		if ((nNameType == WEIGHT_NAME) && (res > d_idx->v_width))
			return(res - d_idx->v_width + 1);
	}

	return(-1);
}


/*
* Routine: int distsize(char *name)
* Purpose: return the size of a distribution
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
*	20000405 need to add error checking
*/
int
distsize(char *name)
{
	d_idx_t *dist;

	dist = find_dist(name);

	if (dist == NULL)
		return(-1);

	return(dist->length);
}

/*
* Routine: int IntegrateDist(char *szDistName, int nPct, int nStartIndex, int nWeightSet)
* Purpose: return the index of the entry which, starting from nStartIndex, would 
*	create a range comprising nPct of the total contained in nWeightSet
*   NOTE: the value can "wrap" -- that is, the returned value can be less than nStartIndex
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

int IntegrateDist(char *szDistName, int nPct, int nStartIndex, int nWeightSet)
{
	d_idx_t *pDistIndex;
	int nGoal,
		nSize;

	if ((nPct <= 0) || (nPct >= 100))
		return(QERR_RANGE_ERROR);
	
	pDistIndex=find_dist(szDistName);
	if (pDistIndex == NULL)
		return(QERR_BAD_NAME);

	if (nStartIndex > pDistIndex->length)
		return(QERR_RANGE_ERROR);

	nGoal = pDistIndex->dist->maximums[nWeightSet];
	nGoal = nGoal * nPct / 100;
	nSize = distsize(szDistName);

	while (nGoal >= 0)
	{
		nStartIndex++;
		nGoal -= dist_weight(NULL, szDistName, nStartIndex % nSize, nWeightSet);
	}
	
	return(nStartIndex);
}


/*
* Routine: int dist_type(char *name, int nValueSet)
* Purpose: return the type of the n-th value set in a distribution
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
int
dist_type(char *name, int nValueSet)
{
	d_idx_t *dist;

	dist = find_dist(name);

	if (dist == NULL)
		return(-1);

	if (nValueSet < 1 || nValueSet > dist->v_width)
		return(-1);
	
	return(dist->dist->type_vector[nValueSet - 1]);
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
dump_dist(char *name)
{
	d_idx_t *pIndex;
	int i, j;
	char *pCharVal = NULL;
	int nVal;

	pIndex = find_dist(name);
	if (pIndex == NULL)
		ReportErrorNoLine(QERR_BAD_NAME, name, 1);
	printf("create %s;\n", pIndex->name);
	printf("set types = (");
	for (i=0; i < pIndex->v_width; i++)
	{
		if (i > 0)
			printf(", ");
		printf("%s", dist_type(name, i + 1) == 7?"int":"varchar");
	}
	printf(");\n");
	printf("set weights = %d;\n", pIndex->w_width);
	for (i=0; i < pIndex->length; i++)
	{
		printf("add(");
		for (j=0; j < pIndex->v_width; j++)
		{
			if (j)
				printf(", ");
			if (dist_type(name, j + 1) != 7)
			{
				dist_member(&pCharVal, name, i + 1, j + 1);
				printf("\"%s\"", pCharVal);
			}
			else
			{
				dist_member(&nVal, name, i + 1, j + 1);
				printf("%d", nVal);
			}
		}
		printf("; ");
		for (j=0; j < pIndex->w_width; j++)
		{
			if (j)
				printf(", ");
			printf("%d", dist_weight(NULL, name, i + 1, j + 1));
		}
		printf(");\n");
	}

	return;
}

/*
* Routine: dist_active(char *szName, int nWeightSet)
* Purpose: return number of entries with non-zero weght values
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
dist_active(char *szName, int nWeightSet)
{
	int nSize,
		nResult = 0,
		i;
	
	nSize = distsize(szName);
	for (i=1; i <= nSize; i++)
	{
		if (dist_weight(NULL, szName, i, nWeightSet) != 0)
			nResult += 1;
	}
	
	return(nResult);
}

/*
* Routine: DistSizeToShiftWidth(char *szDist) 
* Purpose: Determine the number of bits required to select a member of the distribution
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
int DistSizeToShiftWidth(char *szDist, int nWeightSet)
{
	int nBits = 1,
		nTotal = 2,
		nMax;
	d_idx_t *d;

	d = find_dist(szDist);
	nMax = dist_max(d->dist, nWeightSet);
	
	while (nTotal < nMax)
	{
		nBits += 1;
		nTotal <<= 1;
	}

	return(nBits);
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
int MatchDistWeight(void *dest, char *szDist, int nWeight, int nWeightSet, int ValueSet)
{
		d_idx_t *d;
		dist_t *dist;
		int	index = 0,
			dt,
			i_res,
			nRetcode;
		char *char_val;
		
		if ((d = find_dist(szDist)) == NULL)
		{
			char msg[80];
			sprintf(msg, "Invalid distribution name '%s'", szDist);
			INTERNAL(msg);
		}
		
		dist = d->dist;
		nWeight %= dist->maximums[nWeightSet - 1];
		
		while (nWeight > dist->weight_sets[nWeightSet - 1][index] && 
			index < d->length)
			index += 1;
		dt = ValueSet - 1;
		if (index >= d->length)
			index = d->length - 1;
		char_val = dist->strings + dist->value_sets[dt][index];
		
		switch(dist->type_vector[dt])
		{
		case TKN_VARCHAR:
			if (dest)
				*(char **)dest = (char *)char_val;
			break;
		case TKN_INT:
			i_res = atoi(char_val);
			if (dest)
				*(int *)dest = i_res;
			break;
		case TKN_DATE:
			if (dest == NULL)
			{
				dest = (date_t *)malloc(sizeof(date_t));
				MALLOC_CHECK(dest);
			}
			strtodt(*(date_t **)dest, char_val);
			break;
		case TKN_DECIMAL:
			if (dest == NULL)
			{
				dest = (decimal_t *)malloc(sizeof(decimal_t));
				MALLOC_CHECK(dest);
			}
			strtodec(*(decimal_t **)dest,char_val);
			break;
		}
		
		nRetcode = 1;
		index = 1;
		while (index < dist->maximums[nWeightSet - 1])
		{
			nRetcode += 1;
			index *= 2;
		}

		return(nRetcode);
}

/*
* Routine: findDistValue(char *szValue, char *szDistName, int nValueSet)
* Purpose: Return the row number where the entry is found
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
* 20031024 jms this routine needs to handle all data types, not just varchar
*/
int
findDistValue(char *szValue, char *szDistName, int ValueSet)
{
	int nRetValue = 1,
		nDistMax;
	char szDistValue[128];

	nDistMax = distsize(szDistName);

	for (nRetValue = 1; nRetValue < nDistMax; nRetValue++)
	{
		dist_member(&szDistValue, szDistName, nRetValue, ValueSet);
		if (strcmp(szValue, szDistValue) == 0)
			break;
	}

	if (nRetValue <= nDistMax)
		return(nRetValue);
	return(-1);
}





#ifdef TEST
main()
{
	int i_res;
	char *c_res;
	decimal_t dec_res;
	
	init_params();
	
	dist_member(&i_res, "test_dist", 1, 1);
	if (i_res != 10)
	{
		printf("dist_member(\"test_dist\", 1, 1): %d != 10\n", i_res);
		exit(1);
	}
	dist_member(&i_res, "test_dist", 1, 2);
	if (i_res != 60)
	{
		printf("dist_member(\"test_dist\", 1, 2): %d != 60\n", i_res);
		exit(1);
	}
	dist_member((void *)&c_res, "test_dist", 1, 3);
	if (strcmp(c_res, "El Camino"))
	{
		printf("dist_member(\"test_dist\", 1, 3): %s != El Camino\n", 
			c_res);
		exit(1);
	}
	dist_member((void *)&dec_res, "test_dist", 1, 4);
	if (strcmp(dec_res.number, "1") || strcmp(dec_res.fraction, "23"))
	{
		printf("dist_member(\"test_dist\", 1, 4): %s.%s != 1.23\n",
			dec_res.number, dec_res.fraction);
		exit(1);
	}
	dist_weight(&i_res, "test_dist", 2, 2);
	if (3 != i_res)
	{
		printf("dist_weight(\"test_dist\", 2, 2): %d != 3\n", i_res);
		exit(1);
	}
}
#endif /* TEST */
