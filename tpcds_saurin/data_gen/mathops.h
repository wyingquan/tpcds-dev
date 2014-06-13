/*
* $Id: mathops.h,v 1.2 2004/11/24 23:54:17 jms Exp $
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
* $Log: mathops.h,v $
* Revision 1.2  2004/11/24 23:54:17  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:39  jms
* re-establish external server
*
* Revision 1.1  2004/08/25 23:49:39  jms
* add to release 1.1.17
*
*/
#define OP_PLUS		0x00001
#define OP_MINUS	0x00002
#define OP_MULT		0x00004
#define OP_DIV		0x00008
#define OP_MOD		0x00010	
#define OP_XOR		0x00020	
#define OP_PAREN	0x00040
#define OP_BRACKET	0x00080
#define OP_NEST		0x00100	/* a --> (a) */
#define OP_NEG		0x00200
#define OP_ADDR		0x00400	/* get an address */
#define OP_PTR		0x00800  /* reference through a pointer */
#define OP_FUNC		0x01000	/* user function/macro */
#define OP_UNIQUE	0x02000	/* built in functions start here */
#define OP_TEXT		0x04000	
#define OP_RANDOM	0x08000	
#define OP_RANGE	0x10000	
#define OP_USER		0x20000	/* user defined function */

