/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialcompmatrix.c                 */
/*                                                                           */
/* Created:       2016/02/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: If a material is a parent of a cluster ( or a sole member    */
/*              of a cluster ) this function will loop through it's cluster  */
/*              members sending them to                                      */
/*              ADERCreateMaterialClusterMemMatrixSection.                   */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderMaterialAderData     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialCompMatrix:"

void ADERCreateMaterialCompMatrix(long mat)
{

    long mat_ader_data = 0, ader_mat_matrix_data = 0, ader_mat_cluster_ent_data = 0;
    long ader_mat_cluster_ent_mem = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if((long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR] == mat)
    {

        /* only parent materials get matrix data, they will pass on the solution */
        /* to their children */

        ader_mat_matrix_data = NewItem(mat_ader_data + ADER_MAT_MATRIX_PTR,
                                       ADER_MAT_MATRIX_BLOCK_SIZE);

        ader_mat_cluster_ent_data = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

        while(ader_mat_cluster_ent_data > VALID_PTR)
        {

            /* Go through the cluster members, ( the parent is one of them ) */
            /* and process their contributions to the matrix */

            ader_mat_cluster_ent_mem = (long)RDB[ader_mat_cluster_ent_data + ADER_MAT_CLUSTER_MEM_PTR];

            ADERCreateMaterialClusterMemCompMatrixSection(ader_mat_cluster_ent_mem,
                                                          ader_mat_matrix_data);

            ader_mat_cluster_ent_data = NextItem(ader_mat_cluster_ent_data);

        }

        /* Here we create a final row in the matrix for the objective function */

        ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data, 0.0, 0.0);

    }

}
