/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermakeburnmatrix.c                           */
/*                                                                           */
/* Created:       2016/28/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Builds the burnup matrix that can be used to approximate the */
/*              solution to the Bateman equations. This routine will only    */
/*              work with ADER materials                                     */
/*                                                                           */
/* Comments: This function is called from ADERBurnMaterials                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMakeBurnMatrix:"

void ADERMakeBurnMatrix(struct ccsMatrix* burn_matrix, double* col_vector,
		                long mat, long num_ents, long num_rows, long step,
						long step_type, double t1, double t2)
{

	long *return_array = NULL;
	double mat_flux = 0, micro_cross_section = 0, reaction_rate = 0;
	long ader_mat_cluster_mem = 0, ader_mat_cluster_mem_ader_data = 0;
	long ader_mat_cluster_mem_ader_iso = 0;
	long ader_mat_cluster_mem_ent = 0, ader_mat_cluster_mem_iso = 0;
	long ader_mat_cluster_mem_stream = 0, ader_mat_data = 0, check_column = 0;
	long fission_yield_data = 0, nuc = 0, omp_id = 0, rea = 0, reaction_product_nuc = 0, rea_type = 0;
	long expected_col_index = 0, entry_number = 0;
	long *column_starts = NULL;

	/* Allocate the return array for checking column index matching           */

	return_array = calloc(1, sizeof(long));

	/* Get the thread id                                                      */

	omp_id = OMP_THREAD_NUM;

	/* Grab the pointer to the burn matrix column starts array, the streams   */
	/* section will need this                                                 */

	column_starts = burn_matrix -> colptr;

	/* Go ahead and put the 0 in the 0th index for column starts, its just how*/
	/* this sparse matrix format stores information. See TESTADERSolveClpModel*/
	/* for an example. Both matrices are stored the same way                  */

	column_starts[0] = 0;

	/* Loop through the members of the cluster                                */

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_mem_ent > VALID_PTR)
	{

		/* Get the pointer to the actual material                             */

		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

		/* Generate the XS data for this cluster member                       */

		if((step_type != DEP_STEP_DEC_STEP) && (step_type != DEP_STEP_DEC_TOT) &&
		   (step_type != DEP_STEP_ACT_STEP) && (step_type != DEP_STEP_ACT_TOT))
		{

	        /* Calculate transmutation cross sections */

	        CalculateTransmuXS(ader_mat_cluster_mem, omp_id);

	        /* Store the xs from above */

	        StoreTransmuXS(ader_mat_cluster_mem, step, step_type, omp_id, 0);

		}

        /* Get step weighted XS                                               */

        if((step_type != DEP_STEP_DEC_STEP) && (step_type != DEP_STEP_DEC_TOT))
        {

        	/* Need to loop over cluster mems                                 */

          	AverageTransmuXS(ader_mat_cluster_mem, t1, t2, omp_id);

        }

		/* Get the ader data for this material                                */

		ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

        /* Go ahead and give column start information to column_starts from   */
		/* the lost nuclide which has no column information                   */

		column_starts[(long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FAKE_ISO_BURN_INDEX] + 1] = entry_number;

		/* Also, increment the expected col for hte lost nuclide              */

		expected_col_index++;

		/* Get the flux for this material                                     */

		mat_flux = Truncate(RDB[ader_mat_cluster_mem + MATERIAL_BURN_FLUX_SSA], 6);

		/* Loop through the isotopes in this material. We loop over the ader  */
		/* isotopes list as these have pointers to the material isotopes and  */
		/* have their burn matrix index. We do not worry about including the  */
		/* -1 isotope ( which is not in the ader isotope lists ) as, while    */
		/* the -1 isotope is looped over in the SERPENT burnup matrix routine,*/
		/* no information is processed for it unless a nuclide has an         */
		/* undefined fission yeild in which case, as seen below, it's         */
		/* undefined fission products gets "dumped" into this fake nuclide    */

		ader_mat_cluster_mem_ader_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

		while(ader_mat_cluster_mem_ader_iso > VALID_PTR)
		{

			/* Wipe the column vector where iso/stream data is temporarily    */
			/* stored                                                         */

			memset(col_vector, 0.0, sizeof(double) * num_rows);

			/* Get the nuclide associated with this isotope                   */

			ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_PTR];

			nuc = (long)RDB[ader_mat_cluster_mem_iso + COMPOSITION_PTR_NUCLIDE];

			/* Loop over the possible reactions for this isotope              */

			rea = (long)RDB[nuc + NUCLIDE_PTR_REA];

			while(rea > VALID_PTR)
			{

				/* Reset the reaction rate                                    */

				reaction_rate = 0.0;

				/* Get reaction type                                          */

				rea_type = (long)RDB[rea + REACTION_TYPE];

				/* Get pointer to fission yield data                          */

				fission_yield_data = (long)RDB[rea + REACTION_PTR_FISSY];

				/* Get pointer to reaction product "nuc" data                 */

				reaction_product_nuc = (long)RDB[rea + REACTION_PTR_TGT];

				/* If this reaction has fission yield data process that       */

				if(fission_yield_data > VALID_PTR)
				{

					ADERProcessBurnMatrixFissionYield(ader_mat_cluster_mem_ader_iso,
							                          col_vector,
							                          fission_yield_data,
													  ader_mat_cluster_mem,
													  mat_flux, nuc, omp_id,
													  rea, rea_type);

				}
				else if(reaction_product_nuc > VALID_PTR)
				{

					/* If this reaction is a transmutation or decay reaction  */
					/* process the data                                       */

					ADERProcessBurnMatrixTransmutationAndDecay(ader_mat_cluster_mem_ader_iso,
							                                   col_vector,
															   ader_mat_cluster_mem,
															   mat_flux, nuc,
															   omp_id, rea,
															   reaction_product_nuc,
															   rea_type);

				}

				rea = NextItem(rea);

			}

			/* If the fission yield data for this isotope is undefined it will*/
			/* need unique processing                                         */

		    if((long)RDB[nuc + NUCLIDE_PTR_NFY_DATA] < VALID_PTR)
		    {

		    	/* Reset rea to point to total fission data                   */

		    	rea = (long)RDB[nuc + NUCLIDE_PTR_TOTFISS_REA];

		    	/* Now get the cross section                                  */

				micro_cross_section = GetPrivateData(((long)RDB[rea + REACTION_PTR_TRANSMUXS]) + 1,
						                             omp_id);

				/* Make sure a physical answer is provided                    */

				if(micro_cross_section > 0.0)
				{

					/* The branching ratio is purposefully left out           */
					/* here thanks to how the reactions are tabulated         */

					reaction_rate = micro_cross_section * mat_flux * BARN;

					/* Go ahead and add this removal rate to the isotope's    */
					/* own production/destruction rate                        */

					col_vector[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]] -= reaction_rate;

					/* The reaction rate also needs to be added to the -1     */
					/* nuclide in the proper material so we must get it index.*/
					/* which the material has                                 */

					col_vector[(long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FAKE_ISO_BURN_INDEX]] += reaction_rate;

				}
				else
				{

					/* The cross section is not real                          */

					reaction_rate = 0.0;

				}

		    }

		    /* Now the isotope's possible contributions to proportional stream*/
		    /* amounts must be processed, along with prop stream contributions*/
		    /* to isotopes. Loop through the streams, only                    */
		    /* process prop type streams, find the matching isotope if any,   */
		    /* get the transfer rate and include it in the matrix. Only       */
		    /* process the source sides of shadow streams for getting prop    */
		    /* amounts, but the contributions to isotopic amounts will need to*/
		    /* include source and destination ends of streams                 */

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	/* If it's not a prop stream, do not process                  */

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    				4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERProcessBurnMatrixPropStream(ader_mat_cluster_mem_ader_iso,
			    			                        ader_mat_cluster_mem_stream,
													col_vector,
													ader_mat_cluster_mem);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	/* If it's not a prop stream, do not process                  */

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    				4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERProcessBurnMatrixPropStream(ader_mat_cluster_mem_ader_iso,
			    			                        ader_mat_cluster_mem_stream,
													col_vector,
													ader_mat_cluster_mem);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	/* If it's not a prop stream, do not process                  */

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    				4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERProcessBurnMatrixPropStream(ader_mat_cluster_mem_ader_iso,
			    			                        ader_mat_cluster_mem_stream,
													col_vector,
													ader_mat_cluster_mem);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	/* If it's not a prop stream, do not process                  */

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    				4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERProcessBurnMatrixPropStream(ader_mat_cluster_mem_ader_iso,
			    			                        ader_mat_cluster_mem_stream,
													col_vector,
													ader_mat_cluster_mem);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

#ifdef ADER_DIAG

		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

		    /* Now, store these values in the matrix                          */

		    entry_number = ADERStoreBurnMatrixColumn(burn_matrix,
		    		                                 (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX],
													 col_vector,
		    		                                 entry_number, num_rows);

		    /* Increment the column counter                                   */

		    expected_col_index++;

		    /* And that ends the isotope section                              */

			ader_mat_cluster_mem_ader_iso = NextItem(ader_mat_cluster_mem_ader_iso);

		}

		/* Now that the cluster member's isotopes have been dealt with the    */
		/* streams must be processed                                          */

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* Prop streams are handled at the iso level. As such, if one is  */
	    	/* found, simply store its column_starts info with no additional  */
	    	/* entries and move on, as long as it is not a destination shadow */
	    	/* stream as they do not get a column                             */

	    	if((strncmp("prop",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

#ifdef ADER_DIAG

		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

	    		column_starts[(long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX] + 1] = entry_number;

			    /* Increment the column counter                               */

			    expected_col_index++;

	    	}

	    	/* Cont type streams need to input their isotopic fractions into  */
	    	/* the burnup matrix. Process them here, but skip the destination */
	    	/* side of shadow streams, they are handled inside the process    */
	    	/* function                                                       */

	    	if((strncmp("cont",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

	    		/* Give the value to return array                             */

	    		return_array[0] = expected_col_index;

	    		entry_number = ADERProcessBurnMatrixContStream(burn_matrix,
                                                               ader_mat_cluster_mem_stream,
															   col_vector,
                                                               entry_number,
															   ader_mat_cluster_mem,
															   num_rows,
															   return_array);

	    		/* Retrieve the value from return_array                       */

	    		expected_col_index = return_array[0];

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* Prop streams are handled at the iso level. As such, if one is  */
	    	/* found, simply store its column_starts info with no additional  */
	    	/* entries and move on, as long as it is not a destination shadow */
	    	/* stream as they do not get a column                             */

	    	if((strncmp("prop",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

#ifdef ADER_DIAG

		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

	    		column_starts[(long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX] + 1] = entry_number;

			    /* Increment the column counter                               */

			    expected_col_index++;

	    	}

	    	/* Cont type streams need to input their isotopic fractions into  */
	    	/* the burnup matrix. Process them here, but skip the destination */
	    	/* side of shadow streams, they are handled inside the process    */
	    	/* function                                                       */

	    	if((strncmp("cont",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

	    		/* Give the value to return array                             */

	    		return_array[0] = expected_col_index;

	    		entry_number = ADERProcessBurnMatrixContStream(burn_matrix,
                                                               ader_mat_cluster_mem_stream,
															   col_vector,
                                                               entry_number,
															   ader_mat_cluster_mem,
															   num_rows,
															   return_array);

	    		/* Retrieve the value from return_array                       */

	    		expected_col_index = return_array[0];

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* Prop streams are handled at the iso level. As such, if one is  */
	    	/* found, simply store its column_starts info with no additional  */
	    	/* entries and move on, as long as it is not a destination shadow */
	    	/* stream as they do not get a column                             */

	    	if((strncmp("prop",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

#ifdef ADER_DIAG

		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

	    		column_starts[(long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX] + 1] = entry_number;

			    /* Increment the column counter                               */

			    expected_col_index++;

	    	}

	    	/* Cont type streams need to input their isotopic fractions into  */
	    	/* the burnup matrix. Process them here, but skip the destination */
	    	/* side of shadow streams, they are handled inside the process    */
	    	/* function                                                       */

	    	if((strncmp("cont",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

	    		/* Give the value to return array                             */

	    		return_array[0] = expected_col_index;

	    		entry_number = ADERProcessBurnMatrixContStream(burn_matrix,
                                                               ader_mat_cluster_mem_stream,
															   col_vector,
                                                               entry_number,
															   ader_mat_cluster_mem,
															   num_rows,
															   return_array);

	    		/* Retrieve the value from return_array                       */

	    		expected_col_index = return_array[0];

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* Prop streams are handled at the iso level. As such, if one is  */
	    	/* found, simply store its column_starts info with no additional  */
	    	/* entries and move on, as long as it is not a destination shadow */
	    	/* stream as they do not get a column                             */

	    	if((strncmp("prop",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

#ifdef ADER_DIAG

		    /* Check to make sure column indices match                        */

		    check_column = (long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX];

		    if(expected_col_index != check_column)
		    {

				Die(FUNCTION_NAME, "Expected to store column %ld but got column %ld.\n",
				    expected_col_index, check_column);

		    }

#endif

	    		column_starts[(long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_BURN_INDEX] + 1] = entry_number;

			    /* Increment the column counter                               */

			    expected_col_index++;

	    	}

	    	/* Cont type streams need to input their isotopic fractions into  */
	    	/* the burnup matrix. Process them here, but skip the destination */
	    	/* side of shadow streams, they are handled inside the process    */
	    	/* function                                                       */

	    	if((strncmp("cont",
	    			   GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					   4) == 0) &&
	    	    ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
	    	{

	    		/* Give the value to return array                             */

	    		return_array[0] = expected_col_index;

	    		entry_number = ADERProcessBurnMatrixContStream(burn_matrix,
                                                               ader_mat_cluster_mem_stream,
															   col_vector,
                                                               entry_number,
															   ader_mat_cluster_mem,
															   num_rows,
															   return_array);

	    		/* Retrieve the value from return_array                       */

	    		expected_col_index = return_array[0];

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    /* The stream processing component for cluster members is finished   */

		ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

	}

	/* Give the burnup matrix it's number of non-zero entries                 */

	burn_matrix -> nnz = entry_number;

	/* Free any allocated memory                                              */

	free(return_array);

	/* Done                                                                   */

}
