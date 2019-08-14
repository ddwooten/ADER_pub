/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderburnmatrixcontstream.c                     */
/*                                                                           */
/* Created:       2016/28/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Recursively uncovers summation streams if they exist. Once   */
/*              a base stream is found this function fills in the isotopic   */
/*              fractions for the base stream into its column vector         */
/*                                                                           */
/* Comments:This function is called from ADERMakeBurnMatrix                  */
/*                                       ADERProcessBurnMatrixContStream     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessBurnMatrixContStream:"

long ADERProcessBurnMatrixContStream(struct ccsMatrix* burn_matrix,
		                             long ader_mat_stream, double* col_vector,
		                             long entry_number, long mat, long num_rows,
									 long* return_array)
{

	double volume_corr_factor = 0.0;
	long ader_mat_iso = 0, ader_mat_stream_iso = 0, ader_mat_stream_shadow_stream = 0;
	long ader_mat_stream_sum_ent = 0, ader_mat_stream_sum_stream = 0;
	long ader_shadow_mat = 0, check_column = 0;
	long expected_col_index = 0, found = 0, mat_iso = 0, nuc = 0;
	long rem_stream = 0, sign = 0;

	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
	{

		rem_stream = 1;

	}

	/* Tunnel into the sum streams of the parent stream if they exist         */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	if(ader_mat_stream_sum_ent > VALID_PTR)
	{

		/* If there are sum streams, pass them to this function               */

		while(ader_mat_stream_sum_ent > VALID_PTR)
		{

			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

			entry_number = ADERProcessBurnMatrixContStream(burn_matrix,
					                                       ader_mat_stream_sum_stream,
														   col_vector,
														   entry_number,
														   mat, num_rows,
														   return_array);

			ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

		}

	}
	else
	{

		/* Once the function finds a stream with no sum components, it is time*/
		/* to fill in its isotopic data. First wipe col_vector                */

		memset(col_vector, 0.0, sizeof(double) * num_rows);

		/* This procedure will need to be executed for both sides of a shadow */
		/* pair if this stream has a shadow, which by the way this function is*/
		/* called, will always be a destination side shadow if it exists      */

		/* Now, determine if this stream is entering or leaving the material  */

		if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
				  GetText(mat + MATERIAL_PTR_NAME)) == 0)
		{

			sign = 1;

		}
		else
		{

			sign = -1;
		}

		/* Now, loop through the stream's isotopes to fill in their fractions */
		/* into the burnup matrix                                             */

		ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_iso > VALID_PTR)
		{

			ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

			mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

			/* Do not process isotopes with no contribution rate              */

			if(RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] != 0.0)
			{

				if(rem_stream > 0)
				{

					if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
					{

						col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
								                                                         RDB[mat_iso + COMPOSITION_ADENS] * sign;

					}
					else
					{

						col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
								                                                         RDB[mat_iso + COMPOSITION_ADENS_BOS] * sign;

					}



				}
				else
				{

					col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] * sign;

				}

			}

			ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

		}

		/* Now, if that destination side shadow stream exists, process it     */
		/* The sign will be 1, because it will be a destination side stream   */

		sign = 1;

		ader_mat_stream_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] * -1;

		if(ader_mat_stream_shadow_stream > VALID_PTR)
		{

			/* Get the volume correction factor for the destination material  */

			ader_shadow_mat = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

			volume_corr_factor = RDB[mat + MATERIAL_VOLUME] /
					             RDB[ader_shadow_mat + MATERIAL_VOLUME];

			/* Now, loop through the stream's isotopes to fill in their       */
			/* fractions into the burnup matrix                               */

			ader_mat_stream_iso = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_ISOS_PTR];

			while(ader_mat_stream_iso > VALID_PTR)
			{

				/* Do not process isotopes with no contribution rate          */

				/* NOTICE!!! The mat_iso variable is NOT RESET. IT IS THE SAME*/
				/* FROM THE NON-SHADOW stream iso. This is to give the        */
				/* correct mass transfer rate                                 */

				if(RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] != 0.0)
				{

					/* Find the corresponding isotope in the source side      */
					/* stream for density information                         */

					found = 0;

					mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

					while(mat_iso > VALID_PTR)
					{

						nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

						if((long)RDB[nuc + NUCLIDE_ZAI] == (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI])
						{

							found = 1;

							break;

						}

						mat_iso = NextItem(mat_iso);

					}

					if(found < 1)
					{

						Die(FUNCTION_NAME, "A matching isotope in the source side material %s\n\
was not found for isotope %ld in stream %s in\n\
the destination side material %s\n", GetText(mat + MATERIAL_PTR_NAME),
                            (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI],
							GetText(ader_mat_stream_shadow_stream + ADER_MAT_STREAM_ID),
							GetText((long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR] + MATERIAL_PTR_NAME));

					}

					ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

					if(rem_stream > 0)
					{

						if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
						{

							col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
									                                                         RDB[mat_iso + COMPOSITION_ADENS] * sign * volume_corr_factor;

						}
						else
						{

							col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] *
									                                                         RDB[mat_iso + COMPOSITION_ADENS_BOS] * sign * volume_corr_factor;

						}

					}
					else
					{

						col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] += RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] * sign * volume_corr_factor;

					}

				}

				ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

			}

		}

		/* Now that the col_vector has been populated, it needs to be inserted*/
		/* into the burnup matrix                                             */

#ifdef ADER_DIAG
		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

		    expected_col_index = return_array[0];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

	    entry_number = ADERStoreBurnMatrixColumn(burn_matrix,
	    		                                 (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX],
												 col_vector,
	    		                                 entry_number, num_rows);

	    return_array[0] = return_array[0] + 1;

	}

	return(entry_number);

}
