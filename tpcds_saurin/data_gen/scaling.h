/*
* $Id: scaling.h,v 1.10 2006/06/07 19:55:36 jms Exp $
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
* $Log: scaling.h,v $
* Revision 1.10  2006/06/07 19:55:36  jms
* checkin of revised update scaling
*
* Revision 1.9  2006/06/06 21:41:15  jms
* initial checkin of revised update scaling
*
* Revision 1.8  2006/03/09 23:00:10  jms
* dependency cleanup
*
* Revision 1.7  2006/03/09 15:09:00  jms
* Bug 360: update scaling and id's
*
* Revision 1.6  2006/02/10 00:12:55  jms
* sf aware QGEN
*
* Revision 1.5  2006/02/02 05:01:27  jms
* scale factor aware qgen
*
* Revision 1.4  2006/01/02 23:01:29  jms
* Bug #360: sk often default to 1 in update set
*
* Revision 1.3  2005/04/20 17:01:46  jms
* Bug #168: Generate fact tables in date order
*
* Revision 1.2  2004/11/24 23:54:20  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.4  2004/08/20 20:05:11  jms
* change return type of getRowcount()
*
* Revision 1.3  2004/01/06 19:45:47  jms
* Checking of fix to bug #6 (scale > 2) and further work on updates/source schema
*
* Revision 1.2  2003/11/05 22:57:32  jms
* complete conversion to file-per-table organization
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.2  2003/07/21 20:50:56  jms
* change get_rowcount to return long for now
*
* Revision 1.1  2003/06/24 19:36:35  jms
* Add files to isolate scaling functions and permutation (used for LIST in qgen)
*
*
*/
#ifndef SCALING_H
#define SCALING_H
ds_key_t get_rowcount(int table);
ds_key_t getIDCount(int nTable);
int getUpdateID(ds_key_t *pDest, int nTable, int nColumn);
int getScaleSlot(int nTargetGB);
int getSkewedJulianDate(int nWeight, int nColumn);
ds_key_t dateScaling(int nColumn, ds_key_t jDate);
int getUpdateDate(int nTable, ds_key_t kRowcount);
void setUpdateDates(void);
void setUpdateScaling(int nTable);
ds_key_t getUpdateBase(int nTable);

#endif
