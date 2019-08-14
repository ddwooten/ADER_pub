/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialremovaldata.c                 */
/*                                                                           */
/* Created:       2016/1/20   (DDW)                                          */
/* Last modified: 2016/1/20   (DDW)                                          */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link ader streams, of the 'rem' group     */
/*              type, data with the                                          */
/*              appropriate material and to the appropriate material hook    */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialStreams          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialRemovalData:"

void ADERProcessMaterialRemovalData(long ader_mat_strm, long ader_strm, long mat)
{

    char *ader_rem_id = NULL, *ader_strm_rem_id = NULL;
    long ader_data = 0, ader_rem = 0, dep = 0, i = 0;
    long ele_iso_fix_check = 0, found = 0, total_steps = 0;

    /* Copy over some information about the repro table to a material stream */
    /* structure, repro tables are treated as streams */

    WDB[ader_mat_strm + ADER_MAT_STREAM_PTR] = (double)ader_strm;

    WDB[ader_mat_strm + ADER_MAT_STREAM_MAT_PTR] = (double)mat;

    WDB[ader_mat_strm + ADER_MAT_STREAM_SRC] = RDB[ader_strm + ADER_STREAM_SRC];

    WDB[ader_mat_strm + ADER_MAT_STREAM_DEST] = RDB[ader_strm + ADER_STREAM_DEST];

    WDB[ader_mat_strm + ADER_MAT_STREAM_FORM] = RDB[ader_strm + ADER_STREAM_FORM];

    WDB[ader_mat_strm + ADER_MAT_STREAM_TYPE] = RDB[ader_strm + ADER_STREAM_GRP_TYPE];

    WDB[ader_mat_strm + ADER_MAT_STREAM_ID] = RDB[ader_strm + ADER_STREAM_GRP_ID];

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

    /* We need to determine if this stream has a destination material and no  */
    /* source material                                                        */

    if((strncmp("NULL", GetText(ader_mat_strm + ADER_MAT_STREAM_DEST), 4) != 0) &&
       (strncmp("NULL", GetText(ader_mat_strm + ADER_MAT_STREAM_SRC), 4) == 0))
    {

        /* This is needed by ADERProcessMaterialRemovalEntryData                */

        ele_iso_fix_check = 1;

    }

    ader_strm_rem_id = GetText(ader_strm + ADER_STREAM_GRP_ID);

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_rem = (long)RDB[ader_data + ADER_REPROS_PTR];

    while(ader_rem > VALID_PTR)
    {

        ader_rem_id = GetText(ader_rem + ADER_REPRO_TBL_ID);

        if(strcmp(ader_strm_rem_id, ader_rem_id) == 0)
        {

            /* Find the matching removal table for this stream. Process it */

            found = 1;

            ADERProcessMaterialRemovalEntryData(ader_mat_strm,
            	                                               ader_rem,
                                                               ele_iso_fix_check, mat);

            /* Ensure that all repro isos have an element which they are      */
            /* attached to                                                    */

            ADERProcessMaterialRemovalIsos(ader_mat_strm, mat);

            /* We now call the below function as all removal table elements   */
            /* need corresponding isotope entries for matrix creation purposes*/

            ADERProcessMaterialRemovalEle(ader_mat_strm, mat);

            break;

        }

        ader_rem = NextItem(ader_rem);

    }

    if(found == 0)
    {

        Error(0, "No matching removal table definition for ADER stream entry \n \
involving removal table %s.\n", ader_strm_rem_id);

    }

}
