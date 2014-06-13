/*
* $Id: r_params.h,v 1.2 2004/11/24 23:54:19 jms Exp $
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
* $Log: r_params.h,v $
* Revision 1.2  2004/11/24 23:54:19  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:58:03  jms
* re-establish external server
*
* Revision 1.2  2003/10/28 01:46:56  jms
* checkin of ETL generation changes through s_store
*
* Revision 1.3  2003/07/24 16:22:05  jms
* Misc build cleanup
*
* Revision 1.2  2003/06/24 19:52:55  jms
* clean up command line options, lay ground work for 2-pass qgen (bugs: 26, 36)
*
* Revision 1.1.1.1  2002/06/14 17:20:25  jms
* CVS Baseline
*
*/

#ifndef R_PARAMS_H
#define R_PARAMS_H
#define OPT_NONE    0x00 
#define OPT_FLG     0x01 /* option is a flag; no parameter */
#define OPT_INT     0x02 /* argument is an integer */
#define OPT_STR     0x04 /* argument is a string */
#define OPT_NOP     0x08 /* flags non-operational options */
#define OPT_SUB     0x10 /* sub-option defined */
#define OPT_ADV		0x20 /* advanced option */
#define OPT_SET		0x40 /* not changeable -- used for default/file/command precedence */
#define OPT_DFLT	0x80 /* param set to non-zero default */
#define OPT_MULTI	0x100 /* param may be set repeatedly */
#define OPT_HIDE	0x200 /* hidden option -- not listed in usage */
#define TYPE_MASK   0x07

typedef struct OPTION_T
	{
	char    *name;
	int     flags;
	int     index;
	char    *usage;
	int     (*action)(char *szPName, char *optarg);
	char	*dflt;
	} option_t;
#endif
/*
 * function declarations
 */
int	process_options(int count, char **args);
char	*get_str(char *var);
void	set_str(char *param, char *value);
int		get_int(char *var);
void	set_int(char *var, char *val);
int		is_set(char *flag);
void	clr_flg(char *flag);
int		find_table(char *szParamName, char *tname);
int		read_file(char *param_name, char *arg);
int		usage(char *param_name, char *msg);
char	*GetParamName(int nParam);
char	*GetParamValue(int nParam);
int		load_param(int nParam, char *value);
int		fnd_param(char *name);
int		init_params(void);
int		set_option(char *pname, char *value);
void	load_params(void);
int		IsIntParam(char *szName);
int		IsStrParam(char *szName);
