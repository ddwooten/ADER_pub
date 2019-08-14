/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixclustermemrowbounds.c */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Adjusts row bounds in the comp matrix to account for material*/
/*              removal due to removal tables and material present           */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixClusterMemRowBounds:"

void ADERSetMaterialCompMatrixClusterMemRowBounds(long dep, long i, long mat,
		                                          double t1, double t2)
{

    long ader_mat_cluster_parent = 0, ader_mat_ele = 0, ader_mat_iso = 0, ader_mat_oxi = 0;
    long ader_mat_stream = 0;
    long ader_parent_ader_data = 0, ader_parent_matrix_data = 0;
    long mat_ader_data = 0, mat_iso = 0;

    /* Get the comp matrix                                                    */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cluster_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    ader_parent_ader_data = (long)RDB[ader_mat_cluster_parent + MATERIAL_ADER_DATA];

    ader_parent_matrix_data = (long)RDB[ader_parent_ader_data + ADER_MAT_MATRIX_PTR];

    /* Grab any oxidation information                                         */

    ader_mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    /* First, clear all the element and isotope balance  and future rows of   */
    /* previous data                                                          */

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	/* Clear the balance row                                              */

    	ADERSetMaterialCompMatrixRowBounds(0, 0, ader_parent_matrix_data,
    			                           (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID],
										   0.0);

    	ader_mat_ele = NextItem(ader_mat_ele);

    }

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	/* Clear the balance row                                              */

    	ADERSetMaterialCompMatrixRowBounds(0, 0, ader_parent_matrix_data,
    			                           (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID],
										   0.0);

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* Clear the bounds of any preservation rows this material may have       */

    ADERClearMaterialCompMatrixClusterMemPresRowBounds(ader_parent_matrix_data,
    		                                           mat);

    /* Now loop through all the elements and add their current amount to the  */
    /* balance row                                                            */

	ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	ADERSetMaterialCompMatrixRowBounds(0, 0, ader_parent_matrix_data,
    			                           (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID],
										   RDB[ader_mat_ele + ADER_MAT_ELE_FRAC]);

    	ader_mat_ele = NextItem(ader_mat_ele);

    }

    /* Do the same for the isotopes                                           */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	/* Get the actual isotope to get its ADENS                            */

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	ADERSetMaterialCompMatrixRowBounds(0, 0, ader_parent_matrix_data,
    			                           (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID],
										   (RDB[mat_iso + COMPOSITION_ADENS] /
										    RDB[mat + MATERIAL_ADENS]));

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* Loop through all the material's streams, check for rem type streams    */
    /* DO NOT incorporate bounds changes from discrete rem type streams after */
    /* the zeroth criticality iteration - these changes have already been     */
    /* applied                                                                */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
																	 dep,
        															 mat, t1,
																	 t2);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
																	 dep,
        															 mat, t1,
																	 t2);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
																	 dep,
        															 mat, t1,
																	 t2);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

            /* Now call the below function to deal with removal table effects */

            ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds(ader_parent_matrix_data,
            		                                                 ader_mat_stream,
																	 dep,
        															 mat, t1,
																	 t2);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
