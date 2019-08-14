/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermapdensityvectorstream.c                   */
/*                                                                           */
/* Created:       2016/21/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Sends cont type stream info to the density vector in "send"  */
/*              mode and gives                                               */
/*              prop type streams their amount transfered in "receive" mode  */
/*                                                                           */
/* Comments:This function is called from ADERMapDensityVector                */
/*                                       ADERMapDensityVectorStream          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMapDensityVectorStream:"

void ADERMapDensityVectorStream(double* ader_burn_matrix_N,
		                        long ader_mat_stream, long adj,
								long direction, double total_time)
{

	double adens_corr_factor = 0.0;
	long ader_mat_data = 0, ader_mat_stream_burn_step = 0;
	long ader_mat_stream_shadow_stream = 0, ader_mat_stream_sum_ent = 0;
	long ader_mat_stream_sum_stream = 0, ader_shadow_mat = 0, ader_stream = 0;
	long host_mat = 0, i = 0, mat = 0;

	/* Tunnel into the sum streams of the parent stream if they exist         */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	if(ader_mat_stream_sum_ent > VALID_PTR)
	{

		/* If there are sum streams, pass them to this function               */

		while(ader_mat_stream_sum_ent > VALID_PTR)
		{

			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

			ADERMapDensityVectorStream(ader_burn_matrix_N,
					                   ader_mat_stream_sum_stream,
									   adj, direction, total_time);

			ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

		}

	}
	else
	{

		/* Now that the function has tunneled down to a non-sum-stream, handle*/
		/* information passing                                                */

		if(direction > 0)
		{

			/* Function is in the receive mode, only prop type streams should */
			/* be processed                                                   */

			if(strncmp("prop", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) != 0)
			{

				Error(0, "Stream %s, of form %s, was passed to ADERMapDensityVectorStream \n \
in 'receive' mode. Without form of 'prop' this is an error. Please report as \n\
many simulation details as possible ( input decks and SERPENT version number \n\
mainly ) to the SPERENT users group forums as a bug.\n",
                      GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
					  GetText(ader_mat_stream + ADER_MAT_STREAM_FORM));

			}

			ader_mat_stream_burn_step = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_STEPS_PTR];

			for(i = 0; i < (long)RDB[DATA_BURN_STEP]; i++)
			{

				ader_mat_stream_burn_step = NextItem(ader_mat_stream_burn_step);

			}

			if(adj == 0)
			{

				WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = ader_burn_matrix_N[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]];

			}
			else
			{

				WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = ader_burn_matrix_N[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]] +
																				RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];

			}

			/* If the stream has a shadow, pass the information there as well */
			/* By nature of how this is called, only source streams are       */
			/* present which means they have negative pointers to destination */
			/* streams                                                        */

			ader_mat_stream_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] * -1;

			if(ader_mat_stream_shadow_stream > VALID_PTR)
			{

				ader_shadow_mat = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

				host_mat = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_MAT_PTR];

				adens_corr_factor = RDB[host_mat + MATERIAL_VOLUME] /
						            RDB[ader_shadow_mat + MATERIAL_VOLUME];

				ader_mat_stream_burn_step = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_BURN_STEPS_PTR];

				for(i = 0; i < (long)RDB[DATA_BURN_STEP]; i++)
				{

					ader_mat_stream_burn_step = NextItem(ader_mat_stream_burn_step);

				}

				if(adj == 0)
				{

					WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = ader_burn_matrix_N[(long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_BURN_INDEX]] *
							                                                        adens_corr_factor;

				}
				else
				{

					WDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] = ader_burn_matrix_N[(long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_BURN_INDEX]]*
							                                                        adens_corr_factor + RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];

				}

			}

		}
		else
		{

			/* The function is in "send" mode, only 'cont' type streams should*/
			/* be sending information                                         */

			if(strncmp("cont", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) != 0)
			{

				Error(0, "Stream %s, of form %s, was passed to ADERMapDensityVectorStream \n \
in 'send' mode. Without form of 'cont' this is an error. Please report as \n\
many simulation details as possible ( input decks and SERPENT version number \n\
mainly ) to the SPERENT users group forums as a bug.\n",
                      GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
					  GetText(ader_mat_stream + ADER_MAT_STREAM_FORM));

			}

			/* This stream is from a source material ( or the destination if  */
			/* the stream does not have a shadow ) and so the material density*/
			/* needed is the host material density. We divide by total_time,  */
			/* or the time in the step, to set the continuous amount from the */
			/* bulk amount calculated by the COIN-OR optimization routine to  */
			/* an amount with units of amount/sec                             */

			mat = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_MAT_PTR];

			ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

			/* If the stream is a removal table it gets different information */

			if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
			{

				if(adj > 0)
				{

					ader_burn_matrix_N[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]] = RDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] * RDB[ader_mat_data + ADER_MAT_PRE_STEP_ADENS] /
							                                                                      total_time;

				}
				else
				{

					ader_burn_matrix_N[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]] = RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] * RDB[ader_mat_data + ADER_MAT_PRE_STEP_ADENS] /
							                                                                      total_time;

				}

			}
			else
			{

				/* The original ader stream will be needed to get the other part  */
				/* of the removal rate                                            */

				ader_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_PTR];

				ader_burn_matrix_N[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]] = RDB[ader_stream + ADER_STREAM_OPT1];

			}

		}

	}

}
