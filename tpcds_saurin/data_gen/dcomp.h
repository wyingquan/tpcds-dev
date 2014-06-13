/*
* $Id: dcomp.h,v 1.2 2004/11/24 23:54:15 jms Exp $
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
* $Log: dcomp.h,v $
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:30  jms
* re-establish external server
*
* Revision 1.2  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.2  2003/05/07 20:05:45  jms
* allow distribution value and weight sets to be referenced by string aliases ("names")
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
#ifndef DCOMP_H
#define  DCOMP_H

#include "config.h"
#include "porting.h"
#include "grammar.h"
#include "dist.h"

/*
 * query template grammar definition
 */
#define TKN_UNKNOWN		0
#define TKN_CREATE		1
#define TKN_WEIGHTS		2
#define TKN_TYPES		3
#define TKN_INCLUDE		4
#define TKN_SET			5
#define TKN_VARCHAR		6
#define TKN_INT			7
#define TKN_ADD			8
#define TKN_DATE		9
#define TKN_DECIMAL		10
#define TKN_NAMES		11
#define MAX_TOKEN		11

int ProcessDistribution(char *s, token_t *t);
int ProcessTypes(char *s, token_t *t);
int ProcessInclude(char *s, token_t *t);
int ProcessSet(char *s, token_t *t);
int ProcessAdd(char *s, token_t *t);

#ifdef DECLARER
token_t dcomp_tokens[MAX_TOKEN + 2] = {
	{ TKN_UNKNOWN,	"",		NULL},
	{ TKN_CREATE,	"create",	ProcessDistribution},
	{ TKN_WEIGHTS,	"weights",	NULL},
	{ TKN_TYPES,	"types",	NULL},
	{ TKN_INCLUDE,	"#include",	ProcessInclude},
	{ TKN_SET,	"set",		ProcessSet},
	{ TKN_VARCHAR,	"varchar",	NULL},
	{ TKN_INT,	"int",		NULL},
	{ TKN_ADD,	"add",		ProcessAdd},
	{ TKN_DATE,	"date",		NULL},
	{ TKN_DECIMAL,	"decimal",	NULL},
	{ TKN_NAMES,	"names",	NULL},
	{ -1,		"",		NULL}
};
#else
extern token_t tokens[];
#endif

#endif            /* DCOMP_H */
