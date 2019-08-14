/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderburnmaterials.c                            */
/*                                                                           */
/* Created:       2016/20/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles stepping through burnup substeps for ADER materials. */
/*              Handles composition vector assignment for ADER material      */
/*              burnup. Calls ADERMakeBurnMatrix to make the burn matrix and */
/*              ships this matrix off to a solver routine. Finally, it parses*/
/*              the results in the material composition lists                */
/*                                                                           */
/* Comments:This function is called from BurnMaterials                       */
/*                                                                           */
/*          DEV WARNING!!!: This function deviates from the forms seen in    */
/*                          BurnMaterials0 and BurnMaterialsCI due to the    */
/*                          nature of how AverageTransmuXS stores its data.  */
/*                          Because the rea structure is shared between      */
/*                          materials when constructing a burnup matrix with */
/*                          multiple materials the XS for each material must */
/*                          be computed just prior to use. As such the XS    */
/*                          calculation steps have been moved inside the     */
/*                          ADERMakeBurnMatrix routine.                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERBurnMaterials:"

void ADERBurnMaterials(long burn_ci_flag, long mat, long mode,
		               long num_sub_steps, long step, long type)
{

	double **ader_burn_matrix_size_data = NULL, *ader_burn_matrix_starts = NULL;
	double *ader_burn_matrix_col_storage  = NULL, *ader_burn_matrix_N0 = NULL;
	double *ader_burn_matrix_num_ents = NULL;
	double *ader_burn_matrix_num_rows = NULL, *solution_vector = NULL, t1 = 0, t2 = 0, total_time = 0;
	long ader_data = 0;
	long ader_mat_data = 0, ader_mat_cluster_mem = 0, ader_mat_cluster_mem_ader_data = 0;
	long ader_mat_cluster_mem_ader_iso = 0, ader_mat_cluster_mem_ent = 0, i = 0, mat_iso = 0;
	long nuc = 0, num_samples = 0, omp_id = 0, predictor = 0, sub_step = 0;
	struct ccsMatrix *burn_matrix = NULL;

	omp_id = OMP_THREAD_NUM;

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Get the step length                                                    */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

#ifdef ADER_TEST

	if((strncmp("FLiBeFuel", GetText(mat + MATERIAL_PTR_NAME), 9) == 0) &&
	   (step == 0))
	{

		TESTADERCountStream(mat);

		TESTADERGetBurnMatrixSizeData(mat);

		TESTADERGetIsoBurnMatrixIndex(mat);

		TESTADERMapDensityVector();

		TESTADERGetBurnMatrixValue();

		TESTADERMakeBurnMatrix();

	}

#endif

	/* Get the burn matrix size data                                          */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

	/* Get the memory and the pointer for the burnup matrix                   */

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

	/* Copy material compositions                                             */

	if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
	{

		predictor = 1;

	}
	else
	{

		predictor = 0;

	}

    /* Now, map to the N0 vector the data it needs for the solution of the*/
    /* burnup matrix                                                      */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, predictor, total_time);

    /* Now, loop through substeps                                             */

    for(sub_step = 0; sub_step < num_sub_steps; sub_step++)
    {

    	/* Get sub step start and end times                                   */

        t1 = total_time * sub_step / num_sub_steps;
        t2 = total_time * (sub_step + 1) / num_sub_steps;

        /* Fill the burnup matrix                                             */

        ADERMakeBurnMatrix(burn_matrix,
        		           ader_burn_matrix_col_storage, mat,
						   (long)ader_burn_matrix_num_ents[0],
						   (long)ader_burn_matrix_num_rows[0], step, type, t1,
						   t2);

#ifdef ADER_DIAG

	ADEROutputBurnMatrixAsCsv(burn_matrix,
							  (long)ader_burn_matrix_num_rows[0],
							  mat, step, sub_step);

	TESTADERCompareBurnMatrices(burn_matrix, mat, step, sub_step);

	if((step == 0) &&
	   ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP) &&
	   omp_id == 0)
	{

	    ADERPrintListsHierarchy();

	}

#endif

#ifdef ADER_TEST

    FinalTestReport((long)RDB[(long)RDB[(long)RDB[DATA_PTR_ADER] + ADER_TEST_INFO_PTR] + ADER_TEST_NUM_PASSED],
                    (long)RDB[(long)RDB[(long)RDB[DATA_PTR_ADER] + ADER_TEST_INFO_PTR] + ADER_TEST_NUM_FAILED],
                    (long)RDB[(long)RDB[(long)RDB[DATA_PTR_ADER] + ADER_TEST_INFO_PTR] + ADER_TEST_NUM_CASES]);

#endif

        /* Get the material burnup for each cluster member                    */

        if((type != DEP_STEP_DEC_STEP) && (type != DEP_STEP_DEC_TOT) &&
           (burn_ci_flag < 1))
        {

            /* Map to the N0 vector for MaterialBurnup                        */

            if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
            {

                ADERMapDensityVector(ader_burn_matrix_col_storage,
                		             ader_burn_matrix_starts,
                		             0, 0, mat, predictor, total_time);

            }
            else
            {

            	/* On correctors the col_storage vector needs the iso adens   */
            	/* information, not the BOS values                            */

                ADERMapDensityVector(ader_burn_matrix_col_storage,
                		             ader_burn_matrix_starts, 0, 0, mat, 1,
									 total_time);

            }

        	ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

        	while(ader_mat_cluster_mem_ent > VALID_PTR)
        	{

        		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

        		if(MyParallelMat(ader_mat_cluster_mem, YES) == YES)
        		{

        			/* The double use of the ader_burn_matrix-col_storage     */
        			/* vector is correct. The first instance is only used in  */
        			/* predictor steps and the second only on corrector steps */
        			/* The vector is appropriately filled by the above if logic*/

                    MaterialBurnup(mat, ader_burn_matrix_col_storage,
                    		       ader_burn_matrix_col_storage, t1, t2,
								   sub_step, omp_id);

        		}

        		ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

        	}

        }

		/* Start burnup equation timers                                       */

		ResetTimer(TIMER_BATEMAN);
		StartTimer(TIMER_BATEMAN);
		StartTimer(TIMER_BATEMAN_TOTAL);

		/* ADDER's modified burnup matrix is only solved appropriately by the */
		/* CRAM solver                                                        */

		solution_vector = MatrixExponential(burn_matrix,
				                            ader_burn_matrix_N0, (t2 - t1));

		/* Stop the timers                                                    */

		StopTimer(TIMER_BATEMAN);
		StopTimer(TIMER_BATEMAN_TOTAL);

		/* Map the solution_vector over to the N0 vector for the next loop    */

		for(i = 0; i < ader_burn_matrix_num_rows[0]; i++)
		{

			ader_burn_matrix_N0[i] = solution_vector[i];

		}

		/* Check for negative adens in isotopes. This is possible because of  */
		/* mass transfers. Only do this if the user requested it              */

		ader_data = (long)RDB[DATA_PTR_ADER];

		if((long)RDB[ader_data + ADER_NEG_ADENS_OPT] > 0)
		{

	    	ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

	    	while(ader_mat_cluster_mem_ent > VALID_PTR)
	    	{

	    		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

	    		if(MyParallelMat(ader_mat_cluster_mem, YES) == YES)
	    		{

	    			ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

	    			ader_mat_cluster_mem_ader_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

	    			while(ader_mat_cluster_mem_ader_iso > VALID_PTR)
	    			{

	    				if(ader_burn_matrix_N0[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]] < 0.0)
	    				{

	    					mat_iso = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_PTR];

	    					nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

	    					Warn(FUNCTION_NAME, "Isotope %ld in material %s\n\
on burnup substep %ld for burnup step %ld s\n\
has value %1.12E.", (long)RDB[nuc + NUCLIDE_ZAI],
                                 GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME),
								 sub_step, step,
								 ader_burn_matrix_N0[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]]);

	    					ader_burn_matrix_N0[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]] = 0.0;

	    				}

	    				ader_mat_cluster_mem_ader_iso = NextItem(ader_mat_cluster_mem_ader_iso);

	    			}

	    		}

	    		ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

	    	}

		}

    }

    /* Now, this function serves as both BurnMaterialsCI and BurnMaterials0   */
    /* for ADER materials. The following logic control mimics how             */
    /* BurnMaterialsCI and BurnMaterials0 are executed by BurnMaterials       */

    if((burn_ci_flag > 0) && !(((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP) &&
                               ((long)RDB[DATA_BURN_STEP] != 0)))
    {

    	/* Loop through all the materials in this cluster and update their CI */
    	/* stop criterion                                                     */

    	ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

    	while(ader_mat_cluster_mem_ent > VALID_PTR)
    	{

    		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

    		if(MyParallelMat(ader_mat_cluster_mem, YES) == YES)
    		{

    			UpdateCIStop(ader_mat_cluster_mem, ader_burn_matrix_N0, omp_id);

    			/* Additionally and necessarily store the averaged atomic     */
    			/* densities                                                  */

    			num_samples = RDB[DATA_BURN_CI_I] + 1.0;

    			ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

    			ader_mat_cluster_mem_ader_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

    			while(ader_mat_cluster_mem_ader_iso > VALID_PTR)
    			{

    				mat_iso = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_PTR];

    				WDB[mat_iso + COMPOSITION_ADENS_AVE] = (((num_samples - 1) / num_samples) *
    						                                RDB[mat_iso + COMPOSITION_ADENS_AVE]) +
														   ((1 / num_samples) *
														    ader_burn_matrix_N0[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]]);

    				ader_mat_cluster_mem_ader_iso = NextItem(ader_mat_cluster_mem_ader_iso);

    			}

    		}

    		ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

    	}

    }
    else
    {

    	/* Function was run in "BurnMaterials0" mode. The below control logic */
    	/* is needed for when a depletion calculation is run in SIE mode in   */
    	/* which case atomic densities are only updated on the first predictor*/
    	/* and all corrector steps                                            */

        if((RDB[DATA_BURN_SIE] == (double)NO) ||
  	       (!((long)(RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP) &&
  	        (RDB[DATA_BURN_STEP] != 0.0))))
        {

            ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 1,
            		             mat, predictor, total_time);

        }

    }

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

	/* Deallocate the burn matrix                                             */

	ccsMatrixFree(burn_matrix);

	/* Deallocate the solution_vector                                         */

	free(solution_vector);

}
