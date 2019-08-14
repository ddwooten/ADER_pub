/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderclearpropstreamamts.c                      */
/*                                                                           */
/* Created:       2017/01/13 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to clear prop stream cur and adj amts        */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                       TESTADERClearPropStreamAmts         */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERClearPropStreamAmts:"

void ADERClearPropStreamAmts(long adj, long mat)
{

	long ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0, cluster_ader_data = 0;
	long cluster_mem_stream = 0;
	long mat_ader_data = 0;

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Loop through ader mat cluster members                                 */

	ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_ent > VALID_PTR)
	{

		/* Get the actual material index                                      */

		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

		cluster_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

		/* Loop through the cluster's streams                                 */

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_FEED_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			/* Select prop streams                                            */

			if(strncmp("prop", GetText(cluster_mem_stream + ADER_MAT_STREAM_FORM), 4) == 0)
			{

				ADERClearTargetPropStreamAmts(cluster_mem_stream, adj);

			}

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REAC_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			/* Select prop streams                                            */

			if(strncmp("prop", GetText(cluster_mem_stream + ADER_MAT_STREAM_FORM), 4) == 0)
			{

				ADERClearTargetPropStreamAmts(cluster_mem_stream, adj);

			}

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			/* Select prop streams                                            */

			if(strncmp("prop", GetText(cluster_mem_stream + ADER_MAT_STREAM_FORM), 4) == 0)
			{

				ADERClearTargetPropStreamAmts(cluster_mem_stream, adj);

			}

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REMV_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			/* Select prop streams                                            */

			if(strncmp("prop", GetText(cluster_mem_stream + ADER_MAT_STREAM_FORM), 4) == 0)
			{

				ADERClearTargetPropStreamAmts(cluster_mem_stream, adj);

			}

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

	}

}
