/*
* $Id: w_datetbl.h,v 1.4 2007/07/07 19:49:12 jms Exp $
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
* $Log: w_datetbl.h,v $
* Revision 1.4  2007/07/07 19:49:12  jms
* s_item passes validation
*
* Revision 1.3  2007/05/08 22:34:54  jms
* bug 546
*
* Revision 1.2  2004/11/24 23:54:21  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:10  jms
* re-establish external server
*
* Revision 1.2  2003/11/06 00:13:10  jms
* Porting to Linux
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/
/*
 * DATE table structure 
 */
#ifndef W_DATETBL_H
#define W_DATETBL_H
#include "constants.h"
struct W_DATE_TBL {
ds_key_t	d_date_sk;
char		d_date_id[RS_BKEY + 1];
/* this is generated at output from d_date_sk */
/* date_t		d_date; */
int			d_month_seq;
int			d_week_seq;
int			d_quarter_seq;
int			d_year;
int			d_dow;
int			d_moy;
int			d_dom;
int			d_qoy;
int			d_fy_year;
int			d_fy_quarter_seq;
int			d_fy_week_seq;
char		*d_day_name;
/* char		d_quarter_name[RS_D_QUARTER_NAME + 1]; derived at print time */
int			d_holiday;
int			d_weekend;
int			d_following_holiday;
int			d_first_dom;
int			d_last_dom;
int			d_same_day_ly;
int			d_same_day_lq;
int			d_current_day;
int			d_current_week;
int			d_current_month;
int			d_current_quarter;
int			d_current_year;
};

int mk_w_date(void *pDest, ds_key_t kIndex);
int pr_w_date(void *pSrc);
int ld_w_date(void *pSrc);
int vld_w_date(int nTable, ds_key_t kRow, int *Permutation);
#endif


