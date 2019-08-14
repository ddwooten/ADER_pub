/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderclusters.c              */
/*                                                                           */
/* Created:       2016/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Searches ader clusters to see if current mat is a member     */
/*              If so the cluster, and its parent, are added to the materials*/
/*              ADER data.                                                   */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialAderClusters:"

void ADERProcessMaterialAderClusters(long mat)
{

    char *mat_id = NULL;
    long ader_cluster = 0, ader_cluster_ent = 0, ader_data = 0, mat_ader_data = 0;
    long found = 0;

    mat_id = GetText(mat + MATERIAL_PTR_NAME);

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_cluster = (long)RDB[ader_data + ADER_CLUSTERS_PTR];

    while(ader_cluster > VALID_PTR)
    {

        /* If this is not a voided ader cluster (ie, has been merged ) */
        /* see if it fits this material */

        if(strncmp("VOID", GetText(ader_cluster + ADER_CLUSTER_PARENT_ID), 4) != 0)
        {

            /* If the parent of this cluster is this material, save this material */
            /* as its own parent and create it's cluster list */

            if(strcmp(mat_id, GetText(ader_cluster + ADER_CLUSTER_PARENT_ID)) == 0)
            {

                WDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR] = (double)mat;

                ADERProcessMaterialAderClusterMems(ader_cluster, mat_ader_data);

                break;

            }

            ader_cluster_ent = (long)RDB[ader_cluster + ADER_CLUSTER_ENT_PTR];

            while(ader_cluster_ent > VALID_PTR)
            {

                /* Go through the cluster's members, if this material matches */
                /* one, give it its parent pointer and add itself to the list */

                if(strcmp(mat_id, GetText(ader_cluster_ent + ADER_CLUSTER_ENT_ID)) == 0)
                {

                    ADERProcessMaterialAderClusterParent(ader_cluster, mat_ader_data);

                    ADERProcessMaterialAderClusterMems(ader_cluster, mat_ader_data);

                    found = 1;

                }

                ader_cluster_ent = NextItem(ader_cluster_ent);

            }

            if(found == 1)
            {

                /* If you've already found where the material belongs, quite searching! */

                break;

            }

        }

        ader_cluster = NextItem(ader_cluster);

    }
}
