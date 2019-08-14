/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderclustermems.c           */
/*                                                                           */
/* Created:       2016/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Gets material indices for every material in an ader cluster  */
/*              Assigns this information to the mat ader data that was passed*/
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderClusters     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialAderClusterMems:"

void ADERProcessMaterialAderClusterMems(long ader_cluster, long mat_ader_data)
{

    long ader_cluster_ent = 0, mat = 0, mat_cluster_mem = 0;

    ader_cluster_ent = (long)RDB[ader_cluster + ADER_CLUSTER_ENT_PTR];

    while(ader_cluster_ent > VALID_PTR)
    {

        mat = (long)RDB[DATA_PTR_M0];

        while(mat > VALID_PTR)
        {

            if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                      GetText(ader_cluster_ent + ADER_CLUSTER_ENT_ID)) == 0)
            {

                /* For every member of the cluster, provide the new member */
                /* (who's ader data we have passed in ) with all the other */
                /* cluster member's indices */

                mat_cluster_mem = NewItem(mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR,
                                          ADER_MAT_CLUSTER_MEM_BLOCK_SIZE);

                WDB[mat_cluster_mem + ADER_MAT_CLUSTER_MEM_PTR] = mat;

                break;

            }

            mat = NextItem(mat);

        }

        ader_cluster_ent = NextItem(ader_cluster_ent);

    }

}
