/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialstreams.c                   */
/*                                                                           */
/* Created:       2016/1/2   (DDW)                                           */
/* Last modified: 2016/1/2   (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link ader streams data with the           */
/*              appropriate material and to the appropriate material hook    */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialStreams:"

void ADERProcessMaterialStreams(long mat)
{

    char *ader_strm_dest = NULL, *ader_strm_grp_type = NULL;
    char *ader_strm_src = NULL, *ader_strm_type = NULL;
    char *mat_id = NULL;
    long ader_data = 0, ader_mat_strm = 0, ader_strm = 0, host = 0, mat_ader_data = 0;

    mat_id = GetText(mat + MATERIAL_PTR_NAME);

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_strm = (long)RDB[ader_data + ADER_STREAMS_PTR];

    while(ader_strm > VALID_PTR)
    {

        /* Right now, the current stream does not have the current mat as a */
        /* Source or dest */

    	host = 0;

        /* Grab the necessary information */

        ader_strm_dest = GetText(ader_strm + ADER_STREAM_DEST);

        ader_strm_grp_type = GetText(ader_strm + ADER_STREAM_GRP_TYPE);

        ader_strm_src = GetText(ader_strm + ADER_STREAM_SRC);

        ader_strm_type = GetText(ader_strm + ADER_STREAM_TYPE);

        /* If the stream does have the mat, mark it as a source or dest */

        if(strcmp(mat_id, ader_strm_dest) == 0)
        {

            host = 1;

        }

        if(strcmp(mat_id, ader_strm_src) == 0)
        {

            host = 1;

        }

        /* Sort by criteria */

        if((host == 1) && ((strcmp("feed", ader_strm_type) == 0)))
        {

            ader_mat_strm = NewItem(mat_ader_data + ADER_MAT_FEED_STREAMS_PTR,
                                    ADER_MAT_STREAM_BLOCK_SIZE);

            if(strcmp("rem", ader_strm_grp_type) == 0)
            {

                ADERProcessMaterialRemovalData(ader_mat_strm, ader_strm, mat);

            }
            else
            {

                ADERProcessMaterialStreamData(ader_mat_strm, ader_strm, mat);

            }


        }
        else if((host == 1) && ((strcmp("remv", ader_strm_type) == 0)))
        {

            ader_mat_strm = NewItem(mat_ader_data + ADER_MAT_REMV_STREAMS_PTR,
                                                ADER_MAT_STREAM_BLOCK_SIZE);

            if(strcmp("rem", ader_strm_grp_type) == 0)
            {

            	ADERProcessMaterialRemovalData(ader_mat_strm, ader_strm, mat);

            }
            else
            {

                ADERProcessMaterialStreamData(ader_mat_strm, ader_strm, mat);

            }

        }
        else if((host == 1) && (strcmp("reac", ader_strm_type) == 0))
        {

            ader_mat_strm = NewItem(mat_ader_data + ADER_MAT_REAC_STREAMS_PTR,
                                                            ADER_MAT_STREAM_BLOCK_SIZE);

            if(strcmp("rem", ader_strm_grp_type) == 0)
            {

            	ADERProcessMaterialRemovalData(ader_mat_strm, ader_strm, mat);

            }
            else
            {

                ADERProcessMaterialStreamData(ader_mat_strm, ader_strm, mat);

            }

        }
        else if((host == 1) && (strcmp("redox", ader_strm_type) == 0))
        {

            ader_mat_strm = NewItem(mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR,
                                                            ADER_MAT_STREAM_BLOCK_SIZE);

            if(strcmp("rem", ader_strm_grp_type) == 0)
            {

            	ADERProcessMaterialRemovalData(ader_mat_strm, ader_strm, mat);

            }
            else
            {

                ADERProcessMaterialStreamData(ader_mat_strm, ader_strm, mat);

            }

        }

        ader_strm = NextItem(ader_strm);

    }

}
