/*
* $Id: StringBuffer.h,v 1.3 2007/11/21 19:22:05 jms Exp $
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
* $Log: StringBuffer.h,v $
* Revision 1.3  2007/11/21 19:22:05  jms
* Bug 575
*
* Revision 1.2  2004/11/24 23:54:15  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:05  jms
* re-establish external server
*
* Revision 1.4  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2002/12/04 17:32:59  jms
* Include changes from win2k for porting update
*
* Revision 1.2  2002/11/20 15:52:37  jms
* Missing newline at EOF caused Linux build error
*
* Revision 1.1  2002/11/20 15:45:33  jms
* QGEN cleanup
*
*/

#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#define SB_INIT	0x01

typedef struct STRING_BUFFER_T
{
	int nFlags;
	int nBytesAllocated;
	int nBytesUsed;
	int nIncrement;
	char *pText;
} StringBuffer_t;

StringBuffer_t *InitBuffer(int nSize, int nIncrement);
int AddBuffer(StringBuffer_t *pBuf, char *pStr);
int ResetBuffer(StringBuffer_t *pBuf);
char *GetBuffer(StringBuffer_t *pBuf);
void FreeBuffer(StringBuffer_t *pBuf);
#endif


