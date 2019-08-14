/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessaderclustermems.c                   */
/*                                                                           */
/* Created:       2016/03/03 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Based on the status of stream materials belonging or not to  */
/*              an ader cluster this function handles their assignment.      */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderClusters             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderClusterMems:"

void ADERProcessAderClusterMems(long ader_strm, long ader_strm_dest_cluster,
                                char* ader_strm_dest_id,
                                long ader_strm_src_cluster,
                                char* ader_strm_src_id)
{

    long ader_cluster = 0, ader_data = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    if((ader_strm_dest_cluster < 0) && (ader_strm_src_cluster < 0))
    {

        /* Neither material belongs to a cluster, create one and add them */

        ader_cluster = NewItem(ader_data + ADER_CLUSTERS_PTR,
                               ADER_CLUSTER_BLOCK_SIZE);

        if(strncmp("NULL", ader_strm_dest_id, 4) != 0)
        {

            WDB[ader_cluster + ADER_CLUSTER_PARENT_ID] = RDB[ader_strm + ADER_STREAM_DEST];

        }
        else
        {

            WDB[ader_cluster + ADER_CLUSTER_PARENT_ID] = RDB[ader_strm + ADER_STREAM_SRC];

        }

        ADERAddClusterMember(ader_cluster, ader_strm_dest_id,
                             RDB[ader_strm + ADER_STREAM_DEST]);

        ADERAddClusterMember(ader_cluster, ader_strm_src_id,
                             RDB[ader_strm + ADER_STREAM_SRC]);

    }
    else if((ader_strm_dest_cluster > 0) && (ader_strm_src_cluster < 0))
    {

        /* The dest material belongs to a cluster. Add the source to this cluster */

        ADERAddClusterMember(ader_strm_dest_cluster, ader_strm_src_id,
                             RDB[ader_strm + ADER_STREAM_SRC]);

    }
    else if((ader_strm_dest_cluster < 0) && (ader_strm_src_cluster > 0))
    {

        /* The src material belongs to a cluster. Add the dest to this cluster */

        ADERAddClusterMember(ader_strm_src_cluster, ader_strm_dest_id,
                             RDB[ader_strm + ADER_STREAM_DEST]);

    }
    else if((ader_strm_dest_cluster > 0) && (ader_strm_src_cluster > 0) &&
            ader_strm_dest_cluster != ader_strm_src_cluster)
    {

        /* Each material belongs to a different cluster. Merge these two clusters */

        ADERMergeClusters(ader_strm_dest_cluster, ader_strm_src_cluster);

    }
    else if((ader_strm_dest_cluster > 0) && (ader_strm_src_cluster > 0) &&
            ader_strm_dest_cluster == ader_strm_src_cluster)
    {

        /* Both materials already belong to the same cluster, do nothing */

    }
    else
    {

        Error(0, "Attempted to assign materials, \n \
%s, and %s \n \
to an ADER cluster and failed. These materials are part of a 'stream' entry.\n",
              ader_strm_dest_id, ader_strm_src_id);

    }

}
