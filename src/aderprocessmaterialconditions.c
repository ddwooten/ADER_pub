/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderconditions.c            */
/*                                                                           */
/* Created:       2015/12/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link read in ader conditions data with    */
/*              the appropriate material                                     */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialConditions:"

void ADERProcessMaterialConditions(long mat)
{

    char *ader_cnd_id = NULL, *ader_mat_cnd_id = NULL;
    char ader_type[10];
    long ader_data = 0, ader_cnd = 0, ader_cnd_cnt = 0, ader_cnd_rng = 0, ader_cnd_rto = 0;
    long ader_cnd_opt = 0, ader_cnd_oxi = 0, ader_cnd_pres = 0, ader_mat_cnd = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cnd = (long)RDB[mat_ader_data + ADER_MAT_CNDS_PTR];

    ader_data = (long)RDB[DATA_PTR_ADER];

    /* Loop through all ader conditions blocks. If the block id matches */
    /* A condition block id stored for the material ( from its input defintion */
    /* Then add this condition's data to the material */

    while(ader_mat_cnd > VALID_PTR)
    {

        ader_mat_cnd_id = GetText(ader_mat_cnd + ADER_MAT_CND_ID);

        ader_cnd = (long)RDB[ader_data + ADER_CONDITIONS_PTR];

        while(ader_cnd > VALID_PTR)
        {

            ader_cnd_id = GetText(ader_cnd + ADER_CND_ID);

            if(strcmp(ader_cnd_id, ader_mat_cnd_id) == 0)
            {

                /* IT matches, go through its components and process them into */
                /* the material */

                WDB[ader_mat_cnd + ADER_MAT_CND_PTR] = (double)ader_cnd;

                ader_cnd_cnt = (long)RDB[ader_cnd + ADER_CND_CNT_PTR];

                ader_cnd_rng = (long)RDB[ader_cnd + ADER_CND_RNGS_PTR];

                ader_cnd_rto = (long)RDB[ader_cnd + ADER_CND_RTOS_PTR];

                ader_cnd_opt = (long)RDB[ader_cnd + ADER_CND_OPT_PTR];

                ader_cnd_oxi = (long)RDB[ader_cnd + ADER_CND_OXI_PTR];

                ader_cnd_pres = (long)RDB[ader_cnd + ADER_CND_PRES_PTR];

                while(ader_cnd_cnt > VALID_PTR)
                {

                    ADERProcessMaterialAderCndCntData(ader_cnd_cnt, mat);

                    ader_cnd_cnt = NextItem(ader_cnd_cnt);

                }

                while(ader_cnd_rng > VALID_PTR)
                {

                    sprintf(ader_type, "range");

                    ADERProcessMaterialAderCndData(ader_cnd_rng, ader_type, mat);

                    ader_cnd_rng = NextItem(ader_cnd_rng);

                }

                while(ader_cnd_rto > VALID_PTR)
                {

                    sprintf(ader_type, "ratio");

                    ADERProcessMaterialAderCndData(ader_cnd_rto, ader_type, mat);

                    ader_cnd_rto = NextItem(ader_cnd_rto);

                }

                while(ader_cnd_opt > VALID_PTR)
                {

                    ADERProcessMaterialAderCndOptData(ader_cnd_opt, mat);

                    ader_cnd_opt = NextItem(ader_cnd_opt);

                }

                while(ader_cnd_oxi > VALID_PTR)
                {

                    ADERProcessMaterialAderCndOxiData(ader_cnd_oxi, mat);

                    ader_cnd_oxi = NextItem(ader_cnd_oxi);

                }

                while(ader_cnd_pres > VALID_PTR)
                {

                    ADERProcessMaterialAderCndPresData(ader_cnd_pres, mat);

                    ader_cnd_pres = NextItem(ader_cnd_pres);

                }

            }

            ader_cnd = NextItem(ader_cnd);

        }

        ader_mat_cnd = NextItem(ader_mat_cnd);

    }

}
