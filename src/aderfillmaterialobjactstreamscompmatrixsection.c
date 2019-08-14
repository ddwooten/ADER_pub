/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialobjactstreamscompmatrixsection.c*/
/*                                                                           */
/* Created:       2016/03/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's, and its cluster members', streams*/
/*              setting the material composition optimization matrix entries */
/*              in the objective row to optimize all streams                 */
/*                                                                           */
/* Comments:This function is called from ADERFillMaterialCompMatrixObjRow    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialObjActStreamsCompMatrixSection:"

void ADERFillMaterialObjActStreamsCompMatrixSection(long mat)
{

	double adens_corr_factor = 0, parent_mat_adens = 0, src_mat_adens = 0;
    long ader_mat_cluster_ader_data = 0, ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0;
    long ader_mat_matrix_data = 0, ader_mat_stream = 0, ader_mat_stream_shadow = 0;
    long ader_mat_stream_src_mat = 0, mat_ader_data = 0;

    /* This will be needed later for adens normalization                      */

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Only parent materials are processed for this so they have matrix data  */

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Cycle through the cluster members to process their streams             */

    ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

        ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        ader_mat_cluster_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

        /* Process feed streams                                               */

        ader_mat_stream = (long)RDB[ader_mat_cluster_ader_data + ADER_MAT_FEED_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	/* Skip removal tables and destination end streams                */

        	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
        	   (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

				/* If this is the parent material no correction is needed */

				if(ader_mat_cluster_mem == mat)
				{

					adens_corr_factor = 1.0;

				}
				else
				{

					/* The stream must be normalized to the parent material   */

					src_mat_adens = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

					adens_corr_factor = src_mat_adens / parent_mat_adens;

				}

                ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                                 ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1),
                                                 ader_mat_matrix_data, adens_corr_factor);

        	}

            ader_mat_stream = NextItem(ader_mat_stream);

        }

        /* Process redox streams                                              */

        ader_mat_stream = (long)RDB[ader_mat_cluster_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	/* Skip removal tables and destination end streams                */

        	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
        	   (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

				/* If this is the parent material no correction is needed */

				if(ader_mat_cluster_mem == mat)
				{

					adens_corr_factor = 1.0;

				}
				else
				{

					/* The stream must be normalized to the parent material   */

					src_mat_adens = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

					adens_corr_factor = src_mat_adens / parent_mat_adens;

				}

                ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                                 ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1),
                                                 ader_mat_matrix_data, adens_corr_factor);

        	}

            ader_mat_stream = NextItem(ader_mat_stream);

        }

        /* Process reac streams                                               */

        ader_mat_stream = (long)RDB[ader_mat_cluster_ader_data + ADER_MAT_REAC_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	/* Skip removal tables and destination end streams                */

        	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
        	   (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

				/* If this is the parent material no correction is needed */

				if(ader_mat_cluster_mem == mat)
				{

					adens_corr_factor = 1.0;

				}
				else
				{

					/* The stream must be normalized to the parent material   */

					src_mat_adens = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

					adens_corr_factor = src_mat_adens / parent_mat_adens;

				}

                ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                                 ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1),
                                                 ader_mat_matrix_data, adens_corr_factor);

        	}

            ader_mat_stream = NextItem(ader_mat_stream);

        }

        /* Process remv streams                                               */

        ader_mat_stream = (long)RDB[ader_mat_cluster_ader_data + ADER_MAT_REMV_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	/* Skip removal tables and destination end streams                */

        	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
        	   (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

				/* If this is the parent material no correction is needed */

				if(ader_mat_cluster_mem == mat)
				{

					adens_corr_factor = 1.0;

				}
				else
				{

					/* The stream must be normalized to the parent material   */

					src_mat_adens = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

					adens_corr_factor = src_mat_adens / parent_mat_adens;

				}

                ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                                 ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1),
                                                 ader_mat_matrix_data, adens_corr_factor);

        	}

            ader_mat_stream = NextItem(ader_mat_stream);

        }


        ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

}
