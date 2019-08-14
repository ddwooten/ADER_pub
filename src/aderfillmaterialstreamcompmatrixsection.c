/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialstreamcompmatrixsection.c      */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to fill in material comp matrix data for     */
/*              material streams and their sum streams.                      */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialStreamCompMatrixSection:"

void ADERFillMaterialStreamCompMatrixSection(long ader_mat_cluster_ent_mem,
                                             long ader_mat_matrix_data,
                                             long ader_mat_stream)
{

	double dest_mat_adens = 0, adens_multiplier = 0, src_mat_adens = 0;
    long ader_mat_stream_sum_stream = 0, ader_mat_stream_sum_stream_ent = 0;
    long mat_ader_data = 0, shadow_stream = 0, sign = 0, src_mat = 0;

    /* Go ahead and give adens_multiplier a default value of 1                */

    adens_multiplier = 1.0;

    /* If the stream is a rem type, skip it                                   */

    if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
    {

        return;

    }

    /* We need to determine if the stream is leaving or entering the material */
    /* This is most easily done by comparing src and dest names               */

    if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
              GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
    {

        /* Stream is leaving the material                                     */

        sign = -1;

    }
    else
    {

        /* Stream is entering the material                                    */

        sign = 1;

        /* If the stream is entering the material it may be the destination   */
        /* end of a shadow stream pair. If so, it will need special           */
        /* processing to account for the source stream's material density and */
        /* volume                                                             */

        shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

        if(shadow_stream > VALID_PTR)
        {

        	dest_mat_adens = RDB[ader_mat_cluster_ent_mem + MATERIAL_ADENS];

        	src_mat = (long)RDB[shadow_stream + ADER_MAT_STREAM_MAT_PTR];

        	src_mat_adens = RDB[src_mat + MATERIAL_ADENS];

        	adens_multiplier = (src_mat_adens / dest_mat_adens) *
        			           (RDB[src_mat + MATERIAL_VOLUME] /
							    RDB[ader_mat_cluster_ent_mem + MATERIAL_VOLUME]);

        }

    }

    /* We didn't pass in the mat_ader_data, so go ahead and grab it           */

    mat_ader_data = (long)RDB[ader_mat_cluster_ent_mem + MATERIAL_ADER_DATA];

    /* Call the element and isotope processing functions to deal with the     */
    /* stream's elements and isotopes                                         */

    ADERFillMaterialCompMatrixEleData((long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR],
                                      (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                      ader_mat_matrix_data, mat_ader_data,
									  adens_multiplier, sign, 0);

    ADERFillMaterialCompMatrixIsoData((long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR],
                                      (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                      ader_mat_matrix_data, mat_ader_data,
									  adens_multiplier, sign, 0);

    /* Only include the data relating summation streams to their parent if    */
    /* this is NOT the shadow stream                                          */

    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] >= 0)
    {


        /* Now, if there are any sum streams, deal with those, but if so, first   */
        /* set the parent groups value for the sum row to 1                       */

        if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID] >= 0)
        {

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID],
                                             ader_mat_matrix_data,
                                             1.0);

        }

        /* Loop through these sum streams and fill in their matrix data           */

        ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

        while(ader_mat_stream_sum_stream_ent > VALID_PTR)
        {

            ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID],
                                             ader_mat_matrix_data,
                                             -RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_WEIGHT]);

            ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

        }

    }

    /* Now that we've dealt with the relations between a sum stream and its   */
    /* parent we also need to include the sum stream's elemental and isotopic */
    /* information                                                            */

    ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    {

        ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

        ADERFillMaterialStreamCompMatrixSection(ader_mat_cluster_ent_mem,
                                                ader_mat_matrix_data,
                                                ader_mat_stream_sum_stream);

        ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    }

}
