/*
* $Id: dcgram.h,v 1.2 2004/11/24 23:54:15 jms Exp $
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
* $Log: dcgram.h,v $
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
d_idx_t *AddDistribution(distindex_t *pDistIndex, char *szName);
int ProcessSet (char *stmt, token_t * tokens);
int ProcessDistribution (char *stmt, token_t * tokens);
int ProcessTypes (char *stmt, token_t * tokens);
int ProcessInclude (char *stmt, token_t * tokens);
int ProcessOther (char *stmt, token_t * tokens);
int ProcessNames (char *stmt, token_t * tokens);
