/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialadercndoxidata.c            */
/*                                                                           */
/* Created:       2015/1/2 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link read in ader conditions              */
/*              oxidation data with the appropriate material                 */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialConditions      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderCndOxiData:"

void ADERProcessMaterialAderCndOxiData(long ader_cnd_oxi, long mat)
{

    char *ader_cnd_oxi_id = NULL, *ader_first_oxi_id = NULL, *ader_oxi_id = NULL;
    long ader_data, ader_first_oxi = 0, ader_mat_oxi = 0, ader_oxi = 0;
    long mat_ader_data = 0;

    ader_cnd_oxi_id = GetText(ader_cnd_oxi + ADER_CND_OXI_ID);

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_oxi = (long)RDB[ader_data + ADER_OXIS_PTR];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    while(ader_oxi > VALID_PTR)
    {

        /* Find the desired ader oxidation table */

        ader_oxi_id = GetText(ader_oxi + ADER_OXI_TBL_ID);

        if(strcmp(ader_cnd_oxi_id, ader_oxi_id) == 0)
        {

            /* It's a match! Process it! ( Mats are only allowed one oxidation */
            /* table so error out if there is already one */

            if((long)RDB[mat_ader_data + ADER_MAT_OXI_PTR] > VALID_PTR)
            {

                ader_mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

                ader_first_oxi = (long)RDB[ader_mat_oxi + ADER_MAT_OXI_PTR];

                ader_first_oxi_id = GetText(ader_first_oxi + ADER_OXI_TBL_ID);

                Error(0, "Attempting to add oxidation table %s \n \
to material ader data for material %s. Material %s already has oxidation table \n \
%s. Materials are only allowed one oxidation table.\n",
                      ader_oxi_id, GetText(mat + MATERIAL_PTR_NAME),
                      GetText(mat + MATERIAL_PTR_NAME), ader_first_oxi_id);

            }

            ader_mat_oxi = NewItem(mat_ader_data + ADER_MAT_OXI_PTR,
                                   ADER_MAT_OXI_BLOCK_SIZE);

            WDB[ader_mat_oxi + ADER_MAT_OXI_TBL_PTR] = ader_oxi;

            WDB[ader_mat_oxi + ADER_MAT_OXI_MAX] = RDB[ader_cnd_oxi + ADER_CND_OXI_MAX];

            WDB[ader_mat_oxi + ADER_MAT_OXI_MIN] = RDB[ader_cnd_oxi + ADER_CND_OXI_MIN];

            break;

        }

        ader_oxi = NextItem(ader_oxi);

    }

}
