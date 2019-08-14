/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialshadowstreamcompmatrixsection.c */
/*                                                                           */
/* Created:       2016/03/06 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Copies information from a shadow stream's primary stream.    */
/*              This way the matrix creation routines can be aware of the    */
/*              linked nature of these entities                              */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialStreamCompMatrixSection                        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialShadowStreamCompMatrixSection:"

void ADERProcessMaterialShadowStreamCompMatrixSection(long ader_mat_stream)
{

    long ader_mat_stream_sum_stream = 0, ader_mat_stream_sum_stream_ent = 0;
    long ader_shadow_stream = 0;

    ader_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    /* Copy over the column index */

    WDB[ader_shadow_stream + ADER_MAT_STREAM_COL_ID] = RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID];

    /* Copy over the sum stream row, doesn't matter if there is one or isn't */

    WDB[ader_shadow_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID] = RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID];

    /* If there are sum streams, this will need to be called recursively */

    ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    {

        ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

        ADERProcessMaterialShadowStreamCompMatrixSection(ader_mat_stream_sum_stream);

        ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    }

}
