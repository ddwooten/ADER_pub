/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfindshadowstreamsumstreams.c               */
/*                                                                           */
/* Created:       2016/03/07 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Recursively searches sum streams to link primary and shadow  */
/*              streams together at every level of summation.                */
/*                                                                           */
/* Comments:This function is called from ADERFindShadowStream and            */
/*          itself, ADERFindShadowStreamSumStreams                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFindShadowStreamSumStreams:"

void ADERFindShadowStreamSumStreams(long ader_mat_search_stream,
                                    long ader_mat_stream,
                                    long mat)
{

    char *ader_mat_search_stream_sum_stream_id = NULL;
    char *ader_mat_stream_sum_stream_id = NULL;
    long ader_mat_search_stream_sum_stream = 0, ader_mat_search_stream_sum_stream_ent = 0;
    long ader_mat_stream_sum_stream = 0, ader_mat_stream_sum_stream_ent = 0;
    long found = 0;

    ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    /* Search through the primary stream's summation streams */

    while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    {

        /* We will match sum streams by IDs */

        ader_mat_stream_sum_stream_id = GetText(ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID);

        ader_mat_search_stream_sum_stream_ent = (long)RDB[ader_mat_search_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

        /* Search through the shadow stream's sum streams for the match */

        while(ader_mat_search_stream_sum_stream_ent > VALID_PTR)
        {

            ader_mat_search_stream_sum_stream_id = GetText(ader_mat_search_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID);

            /* If the IDs match, the primary stream sum stream gets a positive */
            /* pointer to its shadow while the shadow get's a negative pointer */
            /* to its primary stream                                           */

            if(strcmp(ader_mat_stream_sum_stream_id,
                      ader_mat_search_stream_sum_stream_id) == 0)
            {

                found = 1;

                ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                ader_mat_search_stream_sum_stream = (long)RDB[ader_mat_search_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)ader_mat_search_stream_sum_stream;

                WDB[ader_mat_search_stream_sum_stream + ADER_MAT_STREAM_SHADOW_PTR] = (double)(-1 * ader_mat_stream_sum_stream);

                /* Now, these sum streams may, themselves, have sum streams */
                /* So we pass them to this same function to process those   */

                ADERFindShadowStreamSumStreams(ader_mat_search_stream_sum_stream,
                                               ader_mat_stream_sum_stream, mat);

                break;

            }

            ader_mat_search_stream_sum_stream_ent = NextItem(ader_mat_search_stream_sum_stream_ent);

        }

        /* The shadow stream is an exact duplicate of the primary stream. If they */
        /* both do not have the same sum streams ( which means every stream       */
        /* has a match ) there is a serious problem                               */

        if(found != 1)
        {

            Die(FUNCTION_NAME, "No matching shadow stream found for sum stream stream %s \n \
        in stream %s in mat %s.\n",
                  GetText(ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID),
                  GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                  GetText(mat + MATERIAL_PTR_NAME));

        }

        ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    }

}
