/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialadercnddata.c            */
/*                                                                           */
/* Created:       2015/12/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Assigns ader condition entries to material composition groups*/
/*              If no composition group exists, it calls                     */
/*              ADERProcessMaterialCndGroupData to create the composition    */
/*              group and then calls itself again to assign the condition.   */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialConditions      */
/*          and itself.                                                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderCndData:"

void ADERProcessMaterialAderCndData(long ader_cnd_ent, char *ader_type, long mat)
{

    char *ader_cnd_ent_grp_id = NULL, *ader_mat_cmp_id = NULL;
    long ader_mat_cmp = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the name of the group which has conditions which are being processed */

    if(strncmp("range", ader_type, 5) == 0)
    {

        ader_cnd_ent_grp_id = GetText(ader_cnd_ent + ADER_CND_RNG_GRP_ID);

    }
    else if(strncmp("ratio", ader_type, 5) == 0)
    {

        ader_cnd_ent_grp_id = GetText(ader_cnd_ent + ADER_CND_RTO_GRP1_ID);

    }
    else
    {

        Die(FUNCTION_NAME, "ader_type pased to ADERProcessMaterialCndData is not of string 'range' or 'ratio'.\n");

    }

    ader_mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    /* check to see if that group already has an entry in that material */

    while(ader_mat_cmp > VALID_PTR)
    {

        ader_mat_cmp_id = GetText(ader_mat_cmp + ADER_MAT_CMP_ID);

        if(strcmp(ader_cnd_ent_grp_id, ader_mat_cmp_id) == 0)
        {

            /* if name matches attach the cnd data to the material cmp group */

            if(strncmp("range", ader_type, 5) == 0)
            {

                ADERProcessMaterialCndRngData(ader_cnd_ent, ader_mat_cmp, mat);

                return;

            }
            else if(strncmp("ratio", ader_type, 5) == 0)
            {

                ADERProcessMaterialCndRtoData(ader_cnd_ent, ader_mat_cmp, mat);

                return;

            }
            else
            {

                Die(FUNCTION_NAME, "ader_type of %s did not match either \n \
'range' or 'ratio' for ader_cnd_ent_grp_id of %s and ader_mat_cmp_id of \
%s.\n", ader_type, ader_cnd_ent_grp_id, ader_mat_cmp_id);

            }

        }

        ader_mat_cmp = NextItem(ader_mat_cmp);

    }

    /* If not, create the entry, call again to process the ader_cnd_ent */

    ADERProcessMaterialCndGroupData(ader_cnd_ent_grp_id,
                                    mat);

    ADERProcessMaterialAderCndData(ader_cnd_ent, ader_type, mat);

    return;

}

