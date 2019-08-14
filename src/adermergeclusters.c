/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermergeclusters.c                            */
/*                                                                           */
/* Created:       2016/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: MErges two ader clusters into one cluster list. The          */
/*              deprecated list is left alone but it's parent is changed to  */
/*              "VOID" and is thus skipped for future cluster assignments    */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderClusterMems          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMergeClusters:"

void ADERMergeClusters(long ader_strm_dest_cluster, long ader_strm_src_cluster)
{

    long ader_strm_dest_cluster_ent = 0, ader_strm_src_cluster_ent = 0;
    long found = 0;

    ader_strm_src_cluster_ent = (long)RDB[ader_strm_src_cluster + ADER_CLUSTER_ENT_PTR];

    while(ader_strm_src_cluster_ent > VALID_PTR)
    {

        found = 0;

        ader_strm_dest_cluster_ent = (long)RDB[ader_strm_dest_cluster + ADER_CLUSTER_ENT_PTR];

        while(ader_strm_dest_cluster_ent > VALID_PTR)
        {

            if(strcmp(GetText(ader_strm_src_cluster_ent + ADER_CLUSTER_ENT_ID),
               GetText(ader_strm_dest_cluster_ent + ADER_CLUSTER_ENT_ID)) == 0)
            {

                /* The cluster member from the src cluster is already in the */
                /* dest cluster, we're done on this pass */

                found = 1;

                break;

            }

            ader_strm_dest_cluster_ent = NextItem(ader_strm_dest_cluster_ent);

        }

        if(found == 0)
        {

            /* The src cluster member wasn't found in the dest cluster */
            /* Add it to the dest cluster */

            ADERAddClusterMember(ader_strm_dest_cluster,
                                 GetText(ader_strm_src_cluster_ent + ADER_CLUSTER_ENT_ID),
                                 RDB[ader_strm_src_cluster_ent + ADER_CLUSTER_ENT_ID]);

        }

        ader_strm_src_cluster_ent = NextItem(ader_strm_src_cluster_ent);

    }

    /* 'kill' the src cluster, it has been eaten by the dest cluster! */

    WDB[ader_strm_src_cluster + ADER_CLUSTER_PARENT_ID] = (double)PutText("VOID");

}
