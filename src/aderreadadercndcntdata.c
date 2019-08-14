/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndcntdata.c                       */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: If a 'cnt' flag is found in a cnd block this function is     */
/*              is called by aderreadadercnddata to store the id of the      */
/*              desired cnt table                                            */
/*                                                                           */
/* Comments: Called by AderReadAderCndData                                   */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderCndCntData:"

long ADERReadAderCndCntData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    long cnd_cnt_entry = 0;

    /* Create new conditions controlled items entry */

    cnd_cnt_entry = NewItem(cnd_ptr + ADER_CND_CNT_PTR, ADER_CND_CNT_BLOCK_SIZE);

    /* Store the desired table's id */

    WDB[cnd_cnt_entry + ADER_CND_CNT_ID] = (double)PutText(params[j]);

    j++;

    return(j);
}
