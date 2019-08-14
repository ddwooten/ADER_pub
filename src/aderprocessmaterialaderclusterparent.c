/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderclusterparent.c         */
/*                                                                           */
/* Created:       2016/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Searches materials for one whose id matches the selected     */
/*              cluster parent id. Sets this material's index to the parent  */
/*              pointer for the given material ader data block               */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderClusters     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialAderClusterParent:"

void ADERProcessMaterialAderClusterParent(long ader_cluster, long mat_ader_data)
{

    long mat = 0;

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                  GetText(ader_cluster + ADER_CLUSTER_PARENT_ID)) == 0)
        {

            /* find the material who's name matches that of the ader parent */
            /* store this mat's pointer in the current mat's ader data */

            WDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR] = mat;

            break;

        }

        mat = NextItem(mat);

    }

}
