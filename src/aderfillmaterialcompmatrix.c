/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcompmatrix.c                   */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the members of an ader cluster to call         */
/*              functions to fill their comp matrix data                     */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCompMatrix:"

void ADERFillMaterialCompMatrix(long mat)
{

    long mat_ader_data = 0, ader_mat_matrix_data = 0, ader_mat_cluster_ent_data = 0;
    long ader_mat_cluster_ent_mem = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ader_mat_cluster_ent_data = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent_data > VALID_PTR)
    {

        /* Go through the cluster members, ( the parent is one of them ) */
        /* and fill their matrix entries                                 */

        ader_mat_cluster_ent_mem = (long)RDB[ader_mat_cluster_ent_data + ADER_MAT_CLUSTER_MEM_PTR];

        ADERFillMaterialClusterMemCompMatrixSection(ader_mat_cluster_ent_mem,
                                                    ader_mat_matrix_data);

        ader_mat_cluster_ent_data = NextItem(ader_mat_cluster_ent_data);

    }

}
