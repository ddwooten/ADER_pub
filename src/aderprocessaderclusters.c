/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessaderclusters.c                      */
/*                                                                           */
/* Created:       2016/03/03 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Goes through ader streams and determines the index, if any,  */
/*              of the ader cluster to which the streams materials belong to */
/*              Calls ADERProcessAderClusterMems to assign materials to      */
/*              clusters                                                     */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderMainData             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderClusters:"

void ADERProcessAderClusters()
{

    char *ader_cluster_ent_id = NULL, *ader_cluster_parent_id = NULL, *ader_strm_dest_id = NULL;
    char *ader_strm_src_id = NULL;
    long ader_cluster = 0, ader_cluster_ent = 0, ader_data = 0;
    long ader_strm = 0, ader_strm_dest_cluster = 0, ader_strm_src_cluster = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_strm = (long)RDB[ader_data + ADER_STREAMS_PTR];

    while(ader_strm > VALID_PTR)
    {

        ader_strm_dest_cluster = -1;

        ader_strm_src_cluster = -1;

        ader_strm_dest_id = GetText(ader_strm + ADER_STREAM_DEST);

        ader_strm_src_id = GetText(ader_strm + ADER_STREAM_SRC);

        ader_cluster = (long)RDB[ader_data + ADER_CLUSTERS_PTR];

        /* This loop simply finds if the materials in the given stream */
        /* already belongs to an ader cluster group. If they do, we save that */
        /* cluster index, if they don't, their index remains -1 */

        while(ader_cluster > VALID_PTR)
        {

            ader_cluster_parent_id = GetText(ader_cluster + ADER_CLUSTER_PARENT_ID);

            if(strncmp("VOID", ader_cluster_parent_id, 4) != 0)
            {

                ader_cluster_ent = (long)RDB[ader_cluster + ADER_CLUSTER_ENT_PTR];

                while(ader_cluster_ent > VALID_PTR)
                {

                    ader_cluster_ent_id = GetText(ader_cluster_ent + ADER_CLUSTER_ENT_ID);

                    if(strcmp(ader_cluster_ent_id, ader_strm_dest_id) == 0)
                    {

                        ader_strm_dest_cluster = ader_cluster;

                    }

                    if(strcmp(ader_cluster_ent_id, ader_strm_src_id) == 0)
                    {

                        ader_strm_src_cluster = ader_cluster;

                    }

                    ader_cluster_ent = NextItem(ader_cluster_ent);

                }

            }

            ader_cluster = NextItem(ader_cluster);

        }

        /* Now, there are a couple things that can happen once we know the */
        /* cluster indices, these are handled in the function below */

        ADERProcessAderClusterMems(ader_strm, ader_strm_dest_cluster,
                                   ader_strm_dest_id, ader_strm_src_cluster,
                                   ader_strm_src_id);

        ader_strm = NextItem(ader_strm);

    }

}
