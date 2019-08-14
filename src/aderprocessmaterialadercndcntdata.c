/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialadercndcntdata.c            */
/*                                                                           */
/* Created:       2015/1/2 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link read in ader conditions controlled   */
/*              item data with the appropriate material                      */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialConditions      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderCndCntData:"

void ADERProcessMaterialAderCndCntData(long ader_cnd_cnt, long mat)
{

    char *ader_cnd_cnt_id = 0, *ader_cnt_id = 0;
    long ader_cnt = 0, ader_data = 0, ader_mat_cnt = 0, mat_ader_data = 0;

    ader_cnd_cnt_id = GetText(ader_cnd_cnt + ADER_CND_CNT_ID);

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_cnt = (long)RDB[ader_data + ADER_CONTROL_PTR];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    while(ader_cnt > VALID_PTR)
    {

        ader_cnt_id = GetText(ader_cnt + ADER_CONTROL_TBL_ID);

        if(strcmp(ader_cnd_cnt_id, ader_cnt_id) == 0)
        {

            /* if found the matching control table give the material a pointer */
            /* to its data */

            ader_mat_cnt = NewItem(mat_ader_data + ADER_MAT_CNT_TBLS_PTR,
                                   ADER_MAT_CNT_ENT_BLOCK_SIZE);

            WDB[ader_mat_cnt + ADER_MAT_CNT_TBL_PTR] = ader_cnt;

            break;

        }

        ader_cnt = NextItem(ader_cnt);

    }

}
