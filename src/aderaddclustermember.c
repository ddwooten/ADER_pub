/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderaddclustermember.c                         */
/*                                                                           */
/* Created:       2016/03/03 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Checks to see if passed stream material is real or not.      */
/*              If real, adds to the passed cluster.                         */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderClusterMems          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERAddClusterMember:"

void ADERAddClusterMember(long ader_cluster, char* ader_strm_mem_id,
                         double ader_strm_mem_id_index)
{

    long ader_cluster_ent = 0;

    if(strncmp("NULL", ader_strm_mem_id, 4) != 0)
    {

        /* This is for the initial assignment of stream members to ADER */
        /* clusters. Prevents 'source-less' groups from creating clusters */

        ader_cluster_ent = NewItem(ader_cluster + ADER_CLUSTER_ENT_PTR,
                                   ADER_CLUSTER_ENT_BLOCK_SIZE);

        WDB[ader_cluster_ent + ADER_CLUSTER_ENT_ID] = ader_strm_mem_id_index;

    }

}
