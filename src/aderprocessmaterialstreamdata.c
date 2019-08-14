/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialstreamdata.c                */
/*                                                                           */
/* Created:       2016/1/4   (DDW)                                           */
/* Last modified: 2016/1/4   (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Actually links ader stream data to material stream data      */
/*              also calls functions to populate group data                  */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialStreams          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialStreamData:"

void ADERProcessMaterialStreamData(long ader_mat_strm, long ader_strm, long mat)
{

    char *ader_grp_id = NULL, *ader_strm_grp_id = NULL;
    long ader_data = 0, ader_grp = 0;
    long ele_iso_fix_check = 0, found = 0;

    /* Copy information over to the material */

    WDB[ader_mat_strm + ADER_MAT_STREAM_PTR] = (double)ader_strm;

    WDB[ader_mat_strm + ADER_MAT_STREAM_MAT_PTR] = (double)mat;

    WDB[ader_mat_strm + ADER_MAT_STREAM_SRC] = RDB[ader_strm + ADER_STREAM_SRC];

    WDB[ader_mat_strm + ADER_MAT_STREAM_DEST] = RDB[ader_strm + ADER_STREAM_DEST];

    WDB[ader_mat_strm + ADER_MAT_STREAM_FORM] = RDB[ader_strm + ADER_STREAM_FORM];

    WDB[ader_mat_strm + ADER_MAT_STREAM_TYPE] = RDB[ader_strm + ADER_STREAM_GRP_TYPE];

    /* We need to determine if this stream has a destination material and no  */
    /* source material                                                        */

    if((strncmp("NULL", GetText(ader_mat_strm + ADER_MAT_STREAM_DEST), 4) != 0) &&
       (strncmp("NULL", GetText(ader_mat_strm + ADER_MAT_STREAM_SRC), 4) == 0))
    {

        /* This is needed by ADERProcessMaterialStreamGroupData which needs to*/
        /* pass it off to ADERProcessMaterialGroupComposition                 */

        ele_iso_fix_check = 1;

    }

    ader_strm_grp_id = GetText(ader_strm + ADER_STREAM_GRP_ID);

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_grp = (long)RDB[ader_data + ADER_GROUPS_PTR];

    while(ader_grp > VALID_PTR)
    {

        ader_grp_id = GetText(ader_grp + ADER_GRP_ID);

        if(strcmp(ader_strm_grp_id, ader_grp_id) == 0)
        {

            /* find the matching group definition for the group this stream is */
            /* trying to move. Process this group information */

            found = 1;

            ADERProcessMaterialStreamGroupData(ader_grp, ader_mat_strm,
                                               ele_iso_fix_check, mat);

            break;

        }

        ader_grp = NextItem(ader_grp);

    }

    if(found == 0)
    {

        Error(0, "No matching group definition for ADER stream entry involving group %s.\n \
WARNING: This may be a recursive call and the named group may be a nested \n \
summation group of another group.\n",
              ader_strm_grp_id);

    }

}
