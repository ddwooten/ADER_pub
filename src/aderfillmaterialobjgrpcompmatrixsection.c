/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialobjgrpcompmatrixsection.c      */
/*                                                                           */
/* Created:       2016/03/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's, and its cluster members', groups */
/*              setting the material composition optimization matrix entries */
/*              in the objective row to optimize the selected group          */
/*                                                                           */
/* Comments:This function is called from ADERFillMaterialCompMatrixObjRow    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialObjGrpCompMatrixSection:"

void ADERFillMaterialObjGrpCompMatrixSection(char* ader_mat_opt_target, long mat)
{

	double adens_corr_factor = 0, cluster_mem_adens = 0, parent_mat_adens = 0;
    long ader_mat_cluster_ader_data = 0, ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0;
    long ader_mat_matrix_data = 0, ader_mat_cmp, mat_ader_data = 0;

    /* Go ahead and grab the parent mat's adens, it's going to be needed      */

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Only parent materials are processed for this so they have matrix data  */

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Cycle through the cluster members to process their groups              */

    ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

        ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        /* Go ahead and grab the cluster mem's adens, it's going to be needed */

        cluster_mem_adens = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

        ader_mat_cluster_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

        /* Loop through groups                                               */

        ader_mat_cmp = (long)RDB[ader_mat_cluster_ader_data + ADER_MAT_CMPS_PTR];

        while(ader_mat_cmp > VALID_PTR)
        {

            /* If the name of the target and the group match, add to matrix   */

            if(strcmp(GetText(ader_mat_cmp + ADER_MAT_CMP_ID),
               ader_mat_opt_target) == 0)
            {

            	/* If this cluster member is the parent, it doesn't need a    */
            	/* correction factor                                          */

            	if(ader_mat_cluster_mem == mat)
            	{

            		adens_corr_factor = 1.0;

            	}
            	else
            	{

            		/* Else it does                                           */

            		adens_corr_factor = parent_mat_adens / cluster_mem_adens;

            	}

                ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID],
                                                 ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1),
                                                 ader_mat_matrix_data, adens_corr_factor);

            }

            ader_mat_cmp = NextItem(ader_mat_cmp);

        }

        ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

}
