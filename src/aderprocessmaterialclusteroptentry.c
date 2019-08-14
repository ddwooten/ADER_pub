/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialclusteroptentry.c           */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material cluster to ensure that the parent   */
/*              is given the optimization data. Errors when appropriate      */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialClusterOptEntry:"

void ADERProcessMaterialClusterOptEntry(long mat)
{

    long ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0, ader_mat_opt = 0;
    long ader_parent_mat_opt = 0, mat_ader_data = 0, parent_mat_ader_data = 0;

    parent_mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* We only want to process for the parent of a cluster, so skip if this mat*/
    /* is not a cluster parent                                                */

    if(mat != (long)RDB[parent_mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR])
    {

        return;

    }

    /* Loop through the cluster members                                       */

    ader_mat_cluster_ent = (long)RDB[parent_mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

        ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        if(ader_mat_cluster_mem == mat)
        {

            /* Again, not trying to process the parent, so skip if the cluster*/
            /* mem is the parent                                              */

            ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

            continue;

        }

        mat_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

        ader_mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

        /* If this cluster member has an opt entry, go ahead and check the    */
        /* parent                                                             */

        if(ader_mat_opt > VALID_PTR)
        {

            /* IF the parent already has an opt entry this is a user error    */

            if((long)RDB[parent_mat_ader_data + ADER_MAT_OPT_PTR] > VALID_PTR)
            {

                Error(0, "Parent material, %s, already has an opt entry*.\n \
Cluster** member material, %s, also has an opt entry. Only one opt entry is\n \
is allowed per cluster. This may not be the only excess opt entry. ADER errors\n \
on first multiple opt entry.\n\n *ADER searches a cluster for all opt entries.\n \
If a parent material in a cluster doesn't already have an opt entry and one is \n \
found in a cluster it is attached to the parent. As such, it is possible that \n \
the multiple opt entries ( causing the error ) were never originally associated \n \
with the parent material in the input file but rather with cluster members.\n \
Please check all materials in this cluster.\n\n \
** An ADER 'cluster' is a group of materials which are connected with ADER\n \
'stream' entries. I.e., materials which are sources and sinks for one another.\n",
                      GetText(mat + MATERIAL_PTR_NAME),
                      GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

            }
            else
            {

                /* Otherwise, give the current cluster mem opt data to the    */
                /* parent so that it may be incorporated into the matrix      */

                ader_parent_mat_opt = NewItem(parent_mat_ader_data + ADER_MAT_OPT_PTR,
                                              ADER_MAT_OPT_BLOCK_SIZE);

                WDB[ader_parent_mat_opt + ADER_MAT_OPT_DIR] = RDB[ader_mat_opt + ADER_MAT_OPT_DIR];

                WDB[ader_parent_mat_opt + ADER_MAT_OPT_TYPE] = RDB[ader_mat_opt + ADER_MAT_OPT_TYPE];

                WDB[ader_parent_mat_opt + ADER_MAT_OPT_TYPE_TARGET] = RDB[ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET];

            }

        }

        ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

}
