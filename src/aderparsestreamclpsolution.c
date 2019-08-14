/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderparsestreamclpsolution.c                   */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to assign the Clp solution to ADER streams   */
/*                                                                           */
/* Comments:This function is called from ADERParseClpSolution                */
/*                                       ADERParseStreamClpSolution          */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERParseStreamClpSolution:"

void ADERParseStreamClpSolution(long ader_mat_stream, long adj,
		                        double *solution)
{

	double adens_corr_factor = 0.0, density = 0.0;
	long ader_mat_stream_burn_step = 0, ader_mat_shadow_stream = 0;
	long ader_mat_stream_sum = 0, ader_mat_stream_sum_ent = 0, host_mat = 0;
	long i = 0, src_mat = 0;

	host_mat = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_MAT_PTR];

	/* If this stream is a destination end of a shadow stream, it will need   */
	/* a correction factor                                                    */

	ader_mat_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

	if(ader_mat_shadow_stream > VALID_PTR)
	{

		src_mat = (long)RDB[ader_mat_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

		adens_corr_factor = (RDB[src_mat + MATERIAL_VOLUME] /
				             RDB[host_mat + MATERIAL_VOLUME]);

	}
	else
	{

		adens_corr_factor = 1.0;

	}

	/* Rem streams are not given their current amount, that happens earlier   */

	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
	{

		if(adj == 0)
		{

			WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = solution[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]] * adens_corr_factor;

		}
		else
		{

			WDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] = solution[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]] * adens_corr_factor;

		}

	}

	/* Store the amount in the burn step tracker, but not for prop streams    */

	if(strcmp("prop", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)
	{

		ader_mat_stream_burn_step = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_STEPS_PTR];

		for(i = 0; i < (long)RDB[DATA_BURN_STEP]; i++)
		{

			ader_mat_stream_burn_step = NextItem(ader_mat_stream_burn_step);

		}

		/* First, we need the material density for the stream        */
		/* If there is no shadow, or this is the source side of a shadow      */
		/* stream pair, then the stream's host mat has the density information*/

		if(ader_mat_shadow_stream < VALID_PTR)
		{

			density = RDB[host_mat + MATERIAL_ADENS];

		}
		else
		{

			density = RDB[src_mat + MATERIAL_ADENS] *
					  (RDB[src_mat + MATERIAL_VOLUME] /
		               RDB[host_mat + MATERIAL_VOLUME]);

		}

		if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
		{

			if(adj == 0)
			{

				if(strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) == 0)
				{

					WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = solution[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]] * density +
							                                                        RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];
				}
				else
				{

					WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = solution[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]] * density;

				}

			}
			else
			{

				WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = solution[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]] * density +
						                                                        RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];

			}

		}
		else
		{

			WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] * density;

		}

	}

	/* If the stream has summation streams, loop through those                */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	while(ader_mat_stream_sum_ent > VALID_PTR)
	{

		ader_mat_stream_sum = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

		ADERParseStreamClpSolution(ader_mat_stream_sum, adj, solution);

		ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

	}

}
