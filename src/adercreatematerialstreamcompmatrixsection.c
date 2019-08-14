/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialstreamcompmatrixsection.c    */
/*                                                                           */
/* Created:       2016/02/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates a column for a stream group. If the stream group is  */
/*              a summation group a row is created the function is called    */
/*              again to create a column for the sum groups.                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialStreamCompMatrixSection:"

void ADERCreateMaterialStreamCompMatrixSection(long ader_mat_matrix_data,
                                               long ader_mat_stream)
{

    long ader_mat_stream_col = 0, ader_mat_stream_row = 0;
    long ader_mat_stream_sum_grp = 0, ader_mat_stream_sum_grp_ent = 0;

    /* If this stream is a shadow of another, i.e. the source end of a two */
    /* material stream, skip processing it. Same if it's a rem type stream */

    if(((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < 0) ||
       (strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0))
    {

    	/* Set the sum row for rem type streams to -1 before leaving, this    */
    	/* helps with testing                                                 */

    	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
    	{

            WDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID] = -1.0;

    	}

        return;

    }
    else
    {

        /* Give the stream its column index along with actually creating  */
        /* the column and setting the bounds                              */

        ader_mat_stream_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                              0.0,
                                                              1E+18);

        WDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID] = (double)ader_mat_stream_col;

        ader_mat_stream_sum_grp_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

        /* If this is a sum-stream, we will need a row for its calculation */

        if(ader_mat_stream_sum_grp_ent > VALID_PTR)
        {

            ader_mat_stream_row = (double)ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data, 0.0, 0.0);

            WDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID] = (double)ader_mat_stream_row;

        }
        else
        {

            /* Otherwise, set this to a negative value so it is not processed */

            WDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID] = -1.0;

        }

        /* Now loop through those sum groups and create matrix entries for them as well */

        ader_mat_stream_sum_grp_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

        while(ader_mat_stream_sum_grp_ent > VALID_PTR)
        {

            ader_mat_stream_sum_grp = (long)RDB[ader_mat_stream_sum_grp_ent + ADER_MAT_GRP_SUM_GRP_PTR];

            ADERCreateMaterialStreamCompMatrixSection(ader_mat_matrix_data,
                                                      ader_mat_stream_sum_grp);

            ader_mat_stream_sum_grp_ent = NextItem(ader_mat_stream_sum_grp_ent);

        }

        /* Now, if this stream has a shadow, i.e. it is a stream in a         */
        /* destination material and has a valid source material, now provide  */
        /* the column and row information to the 'shadow' stream              */

        if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR)
        {

            ADERProcessMaterialShadowStreamCompMatrixSection(ader_mat_stream);

        }

    }

}
