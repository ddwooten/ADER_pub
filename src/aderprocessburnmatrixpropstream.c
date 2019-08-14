/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessburnmatrixproxstream.c              */
/*                                                                           */
/* Created:       2016/29/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills in prop stream contributions to isotopic balances and  */
/*              fills in isotopic contributions to prop stream balances      */
/*                                                                           */
/* Comments: This function is called from ADERMakeBurnMatrix                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessBurnMatrixPropStream:"

void ADERProcessBurnMatrixPropStream(long ader_mat_ader_iso, long ader_mat_stream,
		                             double* col_vector, long mat)
{

	double adens_corr_factor = 0.0, lambda = 0, sign = 0;
	double iso_transfer_amount = 0.0;
	long ader_mat_data = 0;
	long ader_stream = 0, ader_mat_stream_iso = 0, ader_mat_stream_shadow_stream = 0;
	long ader_mat_stream_sum_ent = 0, ader_mat_stream_sum_stream = 0, mat_iso = 0, nuc = 0;
	long shadow_mat = 0, shadow_mat_ader_data = 0, shadow_mat_ader_iso = 0, shadow_mat_iso = 0;
	long shadow_mat_nuc = 0;

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Tunnel into the sum streams of the parent stream if they exist         */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	if(ader_mat_stream_sum_ent > VALID_PTR)
	{

		/* If there are sum streams, pass them to this function               */

		while(ader_mat_stream_sum_ent > VALID_PTR)
		{

			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

	    	ADERProcessBurnMatrixPropStream(ader_mat_ader_iso,
	    			                        ader_mat_stream_sum_stream,
											col_vector, mat);

			ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

		}

	}
	else
	{

		/* Determine if this stream is entering or leaving the material       */

		if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
				  GetText(mat + MATERIAL_PTR_NAME)) == 0)
		{

			sign = 1.0;

		}
		else
		{

			sign = -1.0;

		}

		/* Search through the stream's isotopes to see if it has data for the     */
		/* isotope currently being processed. To find matching isotopes simply see*/
		/* if the pointer in the stream iso matches the pointer of the current    */
		/* isotope                                                                */

		ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_iso > VALID_PTR)
		{

			/* Skip isos with zero fraction                                   */

			if(RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] == 0.0)
			{

				ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

				continue;

			}

			if((long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR] ==
			   ader_mat_ader_iso)
			{

				mat_iso = (long)RDB[ader_mat_ader_iso + ADER_MAT_ISO_PTR];

				/* If the stream is a rem type stream, it will be processed   */
				/* differently from a non-rem type stream. Rem type streams   */
				/* have a fixed transfer rate while non-rem type streams have */
				/* a claculated rate                                          */

				if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
				{

					/* The original ader stream will be needed to get the other part  */
					/* of the removal rate                                            */

					ader_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_PTR];

					lambda = RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
							 RDB[ader_stream + ADER_STREAM_OPT1] * sign;

				}
				else
				{

					/* This is a non-rem type stream. It has a target removal */
					/* amount given as its "CUR_AMT". This amount must be     */
					/* converted to an approximate removal rate constant for  */
					/* each isotope in question                               */

					if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
					{

						iso_transfer_amount = (RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] *
							                   RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
								               RDB[ader_mat_data + ADER_MAT_PRE_STEP_ADENS]) /
							                  RDB[mat_iso + COMPOSITION_ADENS];

					}
					else
					{

						iso_transfer_amount = (RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] *
							                   RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
								               RDB[ader_mat_data + ADER_MAT_PRE_STEP_ADENS]) /
							                  RDB[mat_iso + COMPOSITION_ADENS_BOS];

					}

					if(sign > 0)
					{

						lambda = (1.0 / RDB[DATA_BURN_TIME_INTERVAL]) *
								 log(1.0 + iso_transfer_amount);

					}
					else
					{

						if(iso_transfer_amount == 1.0)
						{

							iso_transfer_amount = 0.9999999999;

						}

						lambda = (1.0 / RDB[DATA_BURN_TIME_INTERVAL]) *
								 log(1.0 - iso_transfer_amount);

					}

				}

				col_vector[(long)RDB[ader_mat_ader_iso + ADER_MAT_ISO_BURN_INDEX]] += lambda;

	            /* Add this removal amount to the proportional stream accumulator */
				/* line only if the stream is the source side of a shadow pair or */
				/* a lone stream                                                  */

				if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR)
				{

					col_vector[(long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]] += fabs(lambda);

				}

				/* If this stream is a shadow stream the information for the      */
				/* destination end, as the way this function is called if it is a */
				/* shadow stream it will be the source end, needs to be filled in */
				/* as well                                                        */

				ader_mat_stream_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] * -1;

				if(ader_mat_stream_shadow_stream > VALID_PTR)
				{

					/* Get the mat that the shadow stream belongs to              */

					shadow_mat = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

					if(ader_mat_stream_shadow_stream > VALID_PTR)
					{

						adens_corr_factor = (RDB[mat + MATERIAL_VOLUME] /
								             RDB[shadow_mat + MATERIAL_VOLUME]);

					}

					shadow_mat_ader_data = (long)RDB[shadow_mat + MATERIAL_ADER_DATA];

					/* Get the nuc that is attached to the mat iso that           */
					/* corresponds to the passed in ader_iso                      */

					nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

					/* Loop through the shadow_mat's ader isostopes to find the   */
					/* matching one to the isotope that was passed in             */

					shadow_mat_ader_iso = (long)RDB[shadow_mat_ader_data + ADER_MAT_ISOS_PTR];

					while(shadow_mat_ader_iso > VALID_PTR)
					{

						shadow_mat_iso = (long)RDB[shadow_mat_ader_iso + ADER_MAT_ISO_PTR];

						shadow_mat_nuc = (long)RDB[shadow_mat_iso + COMPOSITION_PTR_NUCLIDE];

						if((long)RDB[nuc + NUCLIDE_ZAI] == (long)RDB[shadow_mat_nuc + NUCLIDE_ZAI])
						{

							/* We use the fraction from the original passed in    */
							/* stream's iso because these are shadow streams,     */
							/* these isos by definition have the same fraction    */
							/* and by not searching for it, we save cpu time      */

							col_vector[(long)RDB[shadow_mat_ader_iso + ADER_MAT_ISO_BURN_INDEX]] += fabs(lambda) * adens_corr_factor;

							break;

						}

						shadow_mat_ader_iso = NextItem(shadow_mat_ader_iso);

					}

				}

				/* Each prop stream can only have one entry for any given isotope,*/
				/* so break                                                       */

				break;

			}

			ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

		}

	}

}
