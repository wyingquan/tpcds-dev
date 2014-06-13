/*
* $Id: release.c,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: release.c,v $
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.1  2004/09/07 22:20:12  jms
* 1.1.17 pre-release for Unisys
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "release.h"
#include "r_params.h"

/*
 * Routine: release(char *param_name, char *msg)
 * Purpose: display version information
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
printReleaseInfo (char *param_name, char *msg)
{
	fprintf (stderr,
		"%s Population Generator (Version %d.%d.%d%s)\n",
		get_str("PROG"), VERSION, RELEASE, MODIFICATION, PATCH);
	fprintf (stderr, "Copyright %s %s\n", COPYRIGHT, C_DATES);
	
	exit(0);
}



