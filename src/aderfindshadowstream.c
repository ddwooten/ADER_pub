/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfindshadowstream.c                         */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through materials and their streams looking for a      */
/*              a stream matching the one passed in. Once found the passed   */
/*              in stream's pointer is given to the found stream and it's    */
/*              pointer is returned.                                         */
/*              Additionally ADERFindShadowStreamSumStreams is called to link*/
/*              any sum streams that may be present.                         */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialShadowStreams    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFindShadowStream:"

long ADERFindShadowStream(long ader_mat_stream, long mat)
{

    long ader_search_mat_stream = 0, ader_stream = 0, search_mat = 0, search_mat_ader_data = 0;

    ader_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_PTR];

    search_mat = (long)RDB[DATA_PTR_M0];

    while(search_mat > VALID_PTR)
    {
        /* Don't find the same stream from the same material */

        if(search_mat != mat)
        {

            search_mat_ader_data = (long)RDB[search_mat + MATERIAL_ADER_DATA];

            /* make sure the material is one included in the ader scheme */

            if(search_mat_ader_data > VALID_PTR)
            {

                /* Go through the four types of steams */

                ader_search_mat_stream = (long)RDB[search_mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

                while(ader_search_mat_stream > VALID_PTR)
                {

                    /* If the two streams have the same ader stream parent, we have found our stream */

                    if(ader_stream == (long)RDB[ader_search_mat_stream + ADER_MAT_STREAM_PTR])
                    {

                        WDB[ader_search_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)(-1 * ader_mat_stream);

                        /* These streams may have sum streams, process these */
                        ADERFindShadowStreamSumStreams(ader_search_mat_stream,
                                                       ader_mat_stream, mat);

                        /* We have found our stream, return to the calling function */

                        return(ader_search_mat_stream);

                    }

                    ader_search_mat_stream = NextItem(ader_search_mat_stream);

                }

                ader_search_mat_stream = (long)RDB[search_mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

                while(ader_search_mat_stream > VALID_PTR)
                {

                    /* If the two streams have the same ader stream parent, we have found our stream */

                    if(ader_stream == (long)RDB[ader_search_mat_stream + ADER_MAT_STREAM_PTR])
                    {

                        WDB[ader_search_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)(-1 * ader_mat_stream);

                        /* These streams may have sum streams, process these */
                        ADERFindShadowStreamSumStreams(ader_search_mat_stream,
                                                       ader_mat_stream, mat);

                        /* We have found our stream, return to the calling function */

                        return(ader_search_mat_stream);

                    }

                    ader_search_mat_stream = NextItem(ader_search_mat_stream);

                }

                ader_search_mat_stream = (long)RDB[search_mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

                while(ader_search_mat_stream > VALID_PTR)
                {

                    /* If the two streams have the same ader stream parent, we have found our stream */

                    if(ader_stream == (long)RDB[ader_search_mat_stream + ADER_MAT_STREAM_PTR])
                    {

                        WDB[ader_search_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)(-1 * ader_mat_stream);

                        /* These streams may have sum streams, process these */
                        ADERFindShadowStreamSumStreams(ader_search_mat_stream,
                                                       ader_mat_stream, mat);

                        /* We have found our stream, return to the calling function */

                        return(ader_search_mat_stream);

                    }

                    ader_search_mat_stream = NextItem(ader_search_mat_stream);

                }

                ader_search_mat_stream = (long)RDB[search_mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

                while(ader_search_mat_stream > VALID_PTR)
                {

                    /* If the two streams have the same ader stream parent, we have found our stream */

                    if(ader_stream == (long)RDB[ader_search_mat_stream + ADER_MAT_STREAM_PTR])
                    {

                        WDB[ader_search_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)(-1 * ader_mat_stream);

                        /* These streams may have sum streams, process these */
                        ADERFindShadowStreamSumStreams(ader_search_mat_stream,
                                                       ader_mat_stream, mat);

                        /* We have found our stream, return to the calling function */

                        return(ader_search_mat_stream);

                    }

                    ader_search_mat_stream = NextItem(ader_search_mat_stream);

                }

            }

        }

        search_mat = NextItem(search_mat);

    }

    Error(0, "No matching source stream found for stream %s \n \
in material %s.\n", GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
          GetText(mat + MATERIAL_PTR_NAME));

    return(0);

}
