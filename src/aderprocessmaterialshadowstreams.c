/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialshadowstreams.c             */
/*                                                                           */
/* Created:       2015/03/05 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's streams. If these streams are     */
/*              connected with another actual material this material and     */
/*              its matching stream ( the shadow stream ) are searched for   */
/*              by ADERFindShadowStream.                                     */
/*              The shadow stream and the 'host' stream are given pointers   */
/*              to eachother. Destination streams have pointers with positive*/
/*              values while source streams have their pointer ( to the dest)*/
/*              multiplied by negative one.                                  */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialShadowStreams:"

void ADERProcessMaterialShadowStreams(long mat)
{

    char *ader_mat_stream_dest_id = NULL, *ader_mat_stream_src_id = NULL, *mat_id = NULL;
    long ader_mat_stream = 0, mat_ader_data = 0, shadow_stream = 0;

    mat_id = GetText(mat + MATERIAL_PTR_NAME);

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Go through the four types of steams */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ader_mat_stream_dest_id = GetText(ader_mat_stream + ADER_MAT_STREAM_DEST);

        /* If this material is the destination for this stream, proceed */

        if(strcmp(ader_mat_stream_dest_id, mat_id) == 0)
        {

            ader_mat_stream_src_id = GetText(ader_mat_stream + ADER_MAT_STREAM_SRC);

            /* If the source is an actual material, proceed */

            if(strcmp(ader_mat_stream_src_id, "NULL") != 0)
            {

                /* Find the matching stream in another material */

                shadow_stream = ADERFindShadowStream(ader_mat_stream, mat);

                /* Store that pointer */

                WDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)shadow_stream;

            }

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ader_mat_stream_dest_id = GetText(ader_mat_stream + ADER_MAT_STREAM_DEST);

        if(strcmp(ader_mat_stream_dest_id, mat_id) == 0)
        {

            ader_mat_stream_src_id = GetText(ader_mat_stream + ADER_MAT_STREAM_SRC);

            if(strcmp(ader_mat_stream_src_id, "NULL") != 0)
            {

                shadow_stream = ADERFindShadowStream(ader_mat_stream, mat);

                WDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)shadow_stream;

            }

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ader_mat_stream_dest_id = GetText(ader_mat_stream + ADER_MAT_STREAM_DEST);

        if(strcmp(ader_mat_stream_dest_id, mat_id) == 0)
        {

            ader_mat_stream_src_id = GetText(ader_mat_stream + ADER_MAT_STREAM_SRC);

            if(strcmp(ader_mat_stream_src_id, "NULL") != 0)
            {

                shadow_stream = ADERFindShadowStream(ader_mat_stream, mat);

                WDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)shadow_stream;

            }

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ader_mat_stream_dest_id = GetText(ader_mat_stream + ADER_MAT_STREAM_DEST);

        if(strcmp(ader_mat_stream_dest_id, mat_id) == 0)
        {

            ader_mat_stream_src_id = GetText(ader_mat_stream + ADER_MAT_STREAM_SRC);

            if(strcmp(ader_mat_stream_src_id, "NULL") != 0)
            {

                shadow_stream = ADERFindShadowStream(ader_mat_stream, mat);

                WDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)shadow_stream;

            }

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
