/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixclustermemcolbounds.c */
/*                                                                           */
/* Created:       2017/11/29 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Adjusts column bounds in the comp matrix to account for      */
/*              removal due to removal tables and material present           */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixClusterMemColBounds:"

void ADERSetMaterialCompMatrixClusterMemColBounds(long mat)
{

    long ader_mat_cluster_parent = 0, ader_mat_ele = 0, ader_mat_iso = 0;
    long ader_mat_stream = 0;
    long ader_parent_ader_data = 0, ader_parent_matrix_data = 0;
    long mat_ader_data = 0, mat_iso = 0;

    /* Get the comp matrix                                                    */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cluster_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    ader_parent_ader_data = (long)RDB[ader_mat_cluster_parent + MATERIAL_ADER_DATA];

    ader_parent_matrix_data = (long)RDB[ader_parent_ader_data + ADER_MAT_MATRIX_PTR];

    /* First, clear all the element and isotope future columns of previous    */
    /* data                                                                   */

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	/* Clear the future column                                            */

    	ADERSetMaterialCompMatrixColBounds(1, 0,
    			                           (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
										   ader_parent_matrix_data,
										   0.0);

    	ADERSetMaterialCompMatrixColBounds(2, 0,
    			                           (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
										   ader_parent_matrix_data,
										   1E+18);

    	ader_mat_ele = NextItem(ader_mat_ele);

    }

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	/* Clear the future column                                            */

    	ADERSetMaterialCompMatrixColBounds(1, 0,
    			                           (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
										   ader_parent_matrix_data,
										   0.0);

    	ADERSetMaterialCompMatrixColBounds(2, 0,
    			                           (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
										   ader_parent_matrix_data,
										   1E+18);

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* Loop through all the material's streams, check for rem type streams    */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableColBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
        															 mat);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableColBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
        															 mat);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableColBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
        															 mat);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableColBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
        															 mat);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
