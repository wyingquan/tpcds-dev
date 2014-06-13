/*
* $Id: address.h,v 1.3 2006/02/02 05:01:27 jms Exp $
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
* (C) COPYRIGHT Gradient Systems Inc. 2003
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: address.h,v $
* Revision 1.3  2006/02/02 05:01:27  jms
* scale factor aware qgen
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:03  jms
* re-establish external server
*
* Revision 1.2  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
*/

#ifndef DS_ADDRESS_H
#define DS_ADDRESS_H
#include "constants.h"

typedef struct DS_ADDR_T {
	char		suite_num[RS_CC_SUITE_NUM + 1];
	int			street_num;
	char		*street_name1;
	char		*street_name2;
	char		*street_type;
	char		*city;
	char		*county;
	char		*state;
	char		country[RS_CC_COUNTRY + 1];
	int			zip;
	int			plus4;
	int			gmt_offset;
} ds_addr_t;

#define DS_ADDR_SUITE_NUM	0
#define DS_ADDR_STREET_NUM	1
#define DS_ADDR_STREET_NAME1	2
#define DS_ADDR_STREET_NAME2	3
#define DS_ADDR_STREET_TYPE		4
#define DS_ADDR_CITY			5
#define DS_ADDR_COUNTY			6
#define DS_ADDR_STATE			7
#define DS_ADDR_COUNTRY			8
#define DS_ADDR_ZIP				9
#define DS_ADDR_PLUS4			10
#define DS_ADDR_GMT_OFFSET		11

int mk_address(ds_addr_t *pDest, int nColumn);
int mk_streetnumber(int nTable, int *dest);
int	mk_suitenumber(int nTable, char *dest);
int mk_streetname(int nTable, char *dest);
int mk_city(int nTable, char **dest);
int city_hash(int nTable, char *name);
int mk_zipcode(int nTable, char *dest, int nRegion, char *city);
void printAddressPart(FILE *fp, ds_addr_t *pAddr, int nAddressPart);
void resetCountCount(void);
#endif

