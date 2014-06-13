/*
* $Id: dist.h,v 1.3 2005/04/20 17:01:46 jms Exp $
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
* $Log: dist.h,v $
* Revision 1.3  2005/04/20 17:01:46  jms
* Bug #168: Generate fact tables in date order
*
* Revision 1.2  2004/11/24 23:54:16  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.5  2004/09/25 00:40:18  jms
* checkin to allow unix debug
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.8  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.7  2003/04/28 21:59:50  jms
* item hierarchy cleanup
*
* Revision 1.6  2003/04/09 20:38:59  jms
* release 1.0.10: qgen range() fixes
*
* Revision 1.5  2003/04/08 17:49:47  jms
* Release 1.0.9
*
* Revision 1.4  2003/03/21 19:56:44  jms
* resync with code on laptap
*
* Revision 1.3  2002/11/27 00:26:49  jms
* removed erroneous semicolon from #define
*
* Revision 1.2  2002/11/20 00:51:33  jms
* QGEN2 corrections
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef R_DIST_H
#define R_DIST_H

#define D_NAME_LEN	20

typedef struct DIST_T {
	int *type_vector;
	int **weight_sets;
	int *maximums;
	int **value_sets;
	char *strings;
	char *names;
	int	size;
	} dist_t;

typedef struct D_IDX_T {
	char name[D_NAME_LEN + 1];
	int index;
	int nAllocatedLength;
	int nRemainingStrSpace;
	int offset;
	int str_space;
	int name_space;
	int length;
	int w_width;
	int v_width;
	int flags;
	dist_t *dist;
} d_idx_t;

typedef struct DISTINDEX_T {
	int nDistCount;
	int nAllocatedCount;
	d_idx_t *pEntries;
	} distindex_t;

/* must match WriteDist() in dcomp.c */
#define IDX_SIZE	(D_NAME_LEN + 7 * sizeof(int))	

int	dist_op(void *dest, int op, char *d_name, int vset, int wset, int stream);
#define pick_distribution(dest, dist, v, w, s)	dist_op(dest, 0, dist, v, w, s)
#define dist_member(dest, dist, v, w)		dist_op(dest, 1, dist, v, w, 0)
#define	dist_max(dist, w)		dist->maximums[w - 1]
int dist_weight(int *dest, char *d, int index, int wset);
int distsize(char *szDistname);
int dist_type(char *szDistName, int vset);
d_idx_t *find_dist(char *name);
int IntegrateDist(char *szDistName, int nPct, int nStartIndex, int nWeightSet);
void dump_dist(char *szName);
int dist_active(char *szName, int nWeightSet);
int DistNameIndex(char *szDist, int nNameType, char *szName);
int DistSizeToShiftWidth(char *szDist, int nWeightSet);
int MatchDistWeight(void *dest, char *szDist, int nWeight, int nWeightSet, int ValueSet);
int findDistValue(char *szValue, char *szDistName, int ValueSet);
int di_compare(const void *op1, const void *op2);


#define DIST_UNIFORM		0x0001
#define DIST_EXPONENTIAL	0x0002
/* sales and returns are special; they must match calendar.dst */
#define DIST_SALES			3
#define DIST_RETURNS		5
#define DIST_CHAR			0x0004
#define DIST_INT            0x0008
#define DIST_NAMES_SET		0xff00

/* DistNameIndex needs to know what sort of name we are trying to match */
#define VALUE_NAME			0x0000
#define WEIGHT_NAME			0x0001
#endif /* R_DIST_H */
