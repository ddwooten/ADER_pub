/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderparseclpsolution.c                         */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to assign the Clp solution to the ADER       */
/*              entities that need them                                      */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                       TESTADERParseClpSolution            */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERParseClpSolution:"

void ADERParseClpSolution(long adj, long i, long mat, long step,
		                  double *solution)
{

	long ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0, cluster_ader_data = 0;
	long cluster_mem_cmp = 0, cluster_mem_cmp_burn_step = 0, cluster_mem_stream = 0;
	long j = 0, mat_ader_data = 0;

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Loop through ader mat cluster members                                 */

	ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_ent > VALID_PTR)
	{

		/* Get the actual material index                                      */

		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

		cluster_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

		/* Loop through the cluster members cmp groups                        */

		cluster_mem_cmp = (long)RDB[cluster_ader_data + ADER_MAT_CMPS_PTR];

		while(cluster_mem_cmp > VALID_PTR)
		{

			/* Set the cmp's calculated fraction                              */

			WDB[cluster_mem_cmp + ADER_MAT_CMP_CUR_AMT] = solution[(long)RDB[cluster_mem_cmp + ADER_MAT_CMP_COL_ID]];

			/* Loop into the proper burn step and store this value there too  */

			cluster_mem_cmp_burn_step = (long)RDB[cluster_mem_cmp + ADER_MAT_CMP_BURN_STEPS_PTR];

			for(j = 0; j < (long)RDB[DATA_BURN_STEP]; j++)
			{

				cluster_mem_cmp_burn_step = NextItem(cluster_mem_cmp_burn_step);

			}

			WDB[cluster_mem_cmp_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = solution[(long)RDB[cluster_mem_cmp + ADER_MAT_CMP_COL_ID]];

			cluster_mem_cmp = NextItem(cluster_mem_cmp);

		}

		/* Loop through the cluster's streams                                 */

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_FEED_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			ADERParseStreamClpSolution(cluster_mem_stream, adj, solution);

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REAC_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			ADERParseStreamClpSolution(cluster_mem_stream, adj, solution);

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			ADERParseStreamClpSolution(cluster_mem_stream, adj, solution);

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		cluster_mem_stream = (long)RDB[cluster_ader_data + ADER_MAT_REMV_STREAMS_PTR];

		while(cluster_mem_stream > VALID_PTR)
		{

			ADERParseStreamClpSolution(cluster_mem_stream, adj, solution);

			cluster_mem_stream = NextItem(cluster_mem_stream);

		}

		ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

	}

}
