/*
* $Id: query_handler.h,v 1.3 2005/10/03 18:55:53 jms Exp $
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
* $Log: query_handler.h,v $
* Revision 1.3  2005/10/03 18:55:53  jms
* add logging of query parameters
* add qualify option remove query permutation
* add filter option to aid debug
*
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:02  jms
* re-establish external server
*
* Revision 1.2  2004/08/25 23:00:47  jms
* initial checkin of revised QGEN
*
* Revision 1.1  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.1  2003/03/21 19:56:45  jms
* resync with code on laptap
*
*/
void GenerateQuery(FILE *pOutFile, FILE *pLogFile, int nQuery);
void PrintTemplate(template_t *t);
void PrintQuery(FILE *pOutput, template_t *t);
substitution_t *defineSubstitution(template_t *pQuery, char *szSubstitutionName, expr_t *pDefinition);
