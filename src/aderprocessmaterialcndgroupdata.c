/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialcndgroupdata.c              */
/*                                                                           */
/* Created:       2015/12/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles the linking of group data to material comp lists     */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialCndData and by   */
/*          itself, as well as ADERProcessMaterialCndRtoData.                */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialCndGroupData:"

long ADERProcessMaterialCndGroupData(char *ader_grp_id, long mat)
{

    char *ader_grp_sum_grp_id = NULL, *ader_mat_cmp_id = NULL, *ader_root_grp_id = NULL;
    long ader_data, ader_root_grp = 0, ader_grp_sum_grp_data = 0, ader_mat_cmp = 0;
    long ader_mat_cmp_ele_ptr = 0, ader_mat_cmp_iso_ptr = 0, ader_mat_cmp_sum_grp = 0;
    long ader_mat_data = 0, dep = 0, i = 0;
    long found = 0, total_steps = 0;

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cmp = (long)RDB[ader_mat_data + ADER_MAT_CMPS_PTR];

    while(ader_mat_cmp > VALID_PTR)
    {

        ader_mat_cmp_id = GetText(ader_mat_cmp + ADER_MAT_CMP_ID);

        if(strcmp(ader_mat_cmp_id, ader_grp_id) == 0)
        {

            /* This was a recursive call from ADERProcessCndGroupSumGroups or */
            /* From the rto processor. All these need are the index of the */
            /* desired group */

            return(ader_mat_cmp);

        }

        ader_mat_cmp = NextItem(ader_mat_cmp);

    }

    /* if the group hasn't already been added to the material cmp group's data */
    /* Do so */

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_root_grp = (long)RDB[ader_data + ADER_GROUPS_PTR];

    while(ader_root_grp > VALID_PTR)
    {

        ader_root_grp_id = GetText(ader_root_grp + ADER_GRP_ID);

        if(strcmp(ader_root_grp_id, ader_grp_id) == 0)
        {

            /* Search through ader groups, if it's name matches that of the */
            /* desired group, process it into the material */

            found = 1;

            ader_mat_cmp = NewItem(ader_mat_data + ADER_MAT_CMPS_PTR,
                                   ADER_MAT_CMP_BLOCK_SIZE);

            WDB[ader_mat_cmp + ADER_MAT_CMP_ID] = RDB[ader_root_grp + ADER_GRP_ID];

            WDB[ader_mat_cmp + ADER_MAT_CMP_GRP_PTR] = (double)ader_root_grp;

            /* Go ahead and give this grp data slots for its future burn data */
            /* First we need to count the total number of steps               */

            dep = (long)RDB[DATA_BURN_PTR_DEP];

            while(dep > VALID_PTR)
            {

            	total_steps = total_steps + (long)RDB[dep + DEP_HIS_N_STEPS];

            	dep = NextItem(dep);

            }

            /* Add a step for the final burn interval                         */

            total_steps++;

            /* Now actually create the burn value data holders                */

            for(i = 0; i < total_steps; i++)
            {

            	NewItem(ader_mat_cmp + ADER_MAT_CMP_BURN_STEPS_PTR,
            			ADER_MAT_GRP_BURN_STEP_BLOCK_SIZE);

            }

            /* YOU ARE PASSING THE INDEX NOT THE VALUE AT THE INDEX!!! (next 2) */

            ader_mat_cmp_ele_ptr = (long)(ader_mat_cmp + ADER_MAT_CMP_ELES_PTR);

            ader_mat_cmp_iso_ptr = (long)(ader_mat_cmp + ADER_MAT_CMP_ISOS_PTR);

            ADERProcessMaterialGroupComposition(ader_root_grp,
                                                ader_mat_cmp_ele_ptr,
                                                ader_mat_cmp_iso_ptr,
                                                0, mat, 0);

            ader_grp_sum_grp_data = (long)RDB[ader_root_grp +
                                              ADER_GRP_SUM_GRPS_PTR];

            while(ader_grp_sum_grp_data > VALID_PTR)
            {

                /* If the group has summation groups, process these */

                ader_mat_cmp_sum_grp = NewItem(ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR,
                                               ADER_MAT_GRP_SUM_GRP_BLOCK_SIZE);

                ader_grp_sum_grp_id = GetText(ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_ID);

                WDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_ID] = RDB[ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_ID];

                WDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_WEIGHT] = RDB[ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_WEIGHT];

                WDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_PTR] = (double)ADERProcessMaterialCndGroupData(ader_grp_sum_grp_id, mat);

                ader_grp_sum_grp_data = NextItem(ader_grp_sum_grp_data);

            }

            break;

        }

        ader_root_grp = NextItem(ader_root_grp);

    }

    if(found == 0)
    {

        Error(0, "No matching group definition for ADER conditions entry involving group %s.\n \
WARNING: This may be a recursive call and the named group may be a nested \n \
summation group of another group.\n",
              ader_grp_id);

    }

    return(ader_mat_cmp);

}

