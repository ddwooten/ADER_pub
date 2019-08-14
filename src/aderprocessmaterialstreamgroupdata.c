/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialstreamgroupdata.c           */
/*                                                                           */
/* Created:       2016/1/4   (DDW)                                           */
/* Last modified: 2016/1/4   (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates element and iso lists for streams from group comp    */
/*              data and handles sum groups.                                 */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialStreamData       */
/*          and by itself                                                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialStreamGroupData:"

void ADERProcessMaterialStreamGroupData(long ader_grp, long ader_mat_strm,
                                        long ele_iso_fix_check, long mat)
{

    long ader_grp_sum_grp = 0, ader_grp_sum_grp_data = 0, ader_mat_strm_ele_ptr = 0;
    long ader_mat_strm_iso_ptr = 0, ader_mat_strm_sum_grp_data = 0;
    long ader_mat_strm_sum_grp_strm = 0, dep = 0, i = 0;
    long total_steps = 0;

    /* store the name of the group being moved as the stream name             */

    WDB[ader_mat_strm + ADER_MAT_STREAM_ID] = RDB[ader_grp + ADER_GRP_ID];

    /* Create the burn data storage space                                     */

    /* Count the number of steps                                              */

    dep = (long)RDB[DATA_BURN_PTR_DEP];

    while(dep > VALID_PTR)
    {

    	total_steps = total_steps + (long)RDB[dep + DEP_HIS_N_STEPS];

    	dep = NextItem(dep);

    }

    /* Add a step for the final burn interval                                 */

    total_steps++;

    /* Now actually create the burn value data holders                        */

    for(i = 0; i < total_steps; i++)
    {

    	NewItem(ader_mat_strm + ADER_MAT_STREAM_BURN_STEPS_PTR,
    			ADER_MAT_GRP_BURN_STEP_BLOCK_SIZE);

    }

    /* grab some necessary indices                                            */

    ader_mat_strm_ele_ptr = (long)(ader_mat_strm + ADER_MAT_STREAM_ELES_PTR);

    ader_mat_strm_iso_ptr = (long)(ader_mat_strm + ADER_MAT_STREAM_ISOS_PTR);

    ADERProcessMaterialGroupComposition(ader_grp, ader_mat_strm_ele_ptr,
                                        ader_mat_strm_iso_ptr,
                                        ele_iso_fix_check, mat, 1);

    ader_grp_sum_grp_data = (long)RDB[ader_grp + ADER_GRP_SUM_GRPS_PTR];

    /* Summation streams may not be proportional streams                      */

    if((ader_grp_sum_grp_data > VALID_PTR) && (strcmp("prop", GetText(ader_mat_strm + ADER_MAT_STREAM_FORM)) == 0))
    {

    	Error(0, "Ader stream %s in material %s \n is a 'proportional' form\
stream composed of a 'sum-group'. This structure is not allowed.\n",
              GetText(ader_mat_strm + ADER_MAT_STREAM_ID),
			  GetText(mat + MATERIAL_PTR_NAME));

    }

    /* Handle a groups summation groups if it is a sum group                  */

    while(ader_grp_sum_grp_data > VALID_PTR)
    {

        /* Store sum groups ( which are now sum streams ) inside the parent stream */
        /* This is different from cmp groups which simply link to one another if   */
        /* they are part of a sum group                                       */

        /* So this is the handle for a sum stream                             */

        ader_mat_strm_sum_grp_data = NewItem(ader_mat_strm + ADER_MAT_STREAM_SUM_GRPS_PTR,
                                             ADER_MAT_GRP_SUM_GRP_BLOCK_SIZE);

        WDB[ader_mat_strm_sum_grp_data + ADER_MAT_GRP_SUM_GRP_ID] = RDB[ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_ID];

        WDB[ader_mat_strm_sum_grp_data + ADER_MAT_GRP_SUM_GRP_WEIGHT] = RDB[ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_WEIGHT];

        /* And this is the actual sum stream being stored inside the handle   */

        ader_mat_strm_sum_grp_strm = NewItem(ader_mat_strm_sum_grp_data + ADER_MAT_GRP_SUM_GRP_PTR,
                                             ADER_MAT_STREAM_BLOCK_SIZE);

        /* Populate the sum stream's stream data fields with the relevant     */
        /* parent stream information                                          */

        /* Give the sum stream a ptr back to its parent                       */

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_PTR] = (double)ader_mat_strm;

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_MAT_PTR] = (double)mat;

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_SRC] = RDB[ader_mat_strm + ADER_MAT_STREAM_SRC];

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_DEST] = RDB[ader_mat_strm + ADER_MAT_STREAM_DEST];

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_FORM] = RDB[ader_mat_strm + ADER_MAT_STREAM_FORM];

        WDB[ader_mat_strm_sum_grp_strm + ADER_MAT_STREAM_TYPE] = RDB[ader_mat_strm + ADER_MAT_STREAM_TYPE];

        ader_grp_sum_grp = (long)RDB[ader_grp_sum_grp_data + ADER_GRP_SUM_GRP_PTR];

        /* Process this sum stream just like any other stream. This is recursive */

        ADERProcessMaterialStreamGroupData(ader_grp_sum_grp,
                                           ader_mat_strm_sum_grp_strm,
                                           ele_iso_fix_check, mat);

        ader_grp_sum_grp_data = NextItem(ader_grp_sum_grp_data);

    }

}
