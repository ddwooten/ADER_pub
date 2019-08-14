/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoperatematerial.c                          */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function, which will only operate on ADER controlled    */
/*              materials ( returns with no action otherwise ), calls the    */
/*              various functions needed to update the material composition  */
/*              matrix, solves this matrix, updates the material ader data   */
/*              ( these updates will be used in another routine ), adjusts   */
/*              the material composition as needed as well as the density    */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROperateMaterial:"

void ADEROperateMaterial(long adj, long dep, long i, long mat, long step,
		                 double t1, double t2)
{

    long ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0;
    long ader_mat_cluster_mem_ader_data = 0, ader_mat_matrix_data = 0, ader_mat_pres = 0;
    long ader_mat_stream = 0, mat_ader_data = 0;
    long omp_id = 0;
    long stream_counter = 0;

    omp_id = OMP_THREAD_NUM;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if(mat_ader_data < VALID_PTR)
    {

        /* If this material is not under ADER control, do not operate on it   */

        return;

    }

    if((long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR] != mat)
    {

        /* IF this material is not the parent material for an ADER cluster, do*/
        /* not operate on it                                                  */

        return;

    }

    /* Grab the ader_mat_matrix data, its needed later                        */

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    if((long)RDB[mat_ader_data + ADER_MAT_OPT_PTR] > VALID_PTR)
    {

        /* Re-fill the objective row in case material density adjustments     */
        /* are needed, this function only takes parent mats                   */

        ADERFillMaterialCompMatrixObjRow(mat);

    }

    /* Loop through all the members of the cluster                            */

    ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

        /* Get the index of the cluster member ( this is like a 'mat' entry   */
        /* elsewhere                                                          */

        ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        /* Give every ader material a copy of its pre stream adjustment       */
        /* density                                                            */

        ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

        WDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRE_STEP_ADENS] = RDB[ader_mat_cluster_mem + MATERIAL_ADENS];

        /* Update the cluster member's elemental isotopics                    */

        ADERGetMatEleIsoFrac(ader_mat_cluster_mem);

        if(adj < 1)
        {

            /* If this is not an adjustment cycle ( adj = 1 )...              */

            /* Update the cluster member's stream's un-fixed elemental        */
            /* isotopics                                                      */

            ADERProcessMaterialStreamUnFixedEleIsoFracs(ader_mat_cluster_mem);

            /* Fill in any preserve row entries, many require density         */
            /* adjustment                                                     */

            ader_mat_pres = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRESERVES_PTR];

            while(ader_mat_pres > VALID_PTR)
            {

                ADERFillMaterialPresCompMatrixSection(ader_mat_cluster_mem,
                                                      ader_mat_matrix_data,
                                                      ader_mat_pres);

                ader_mat_pres = NextItem(ader_mat_pres);

            }

            /* Calculate the amounts of elements and isotopes that will be    */
            /* removed                                                        */

            ADERGetMaterialRemovalAmounts(ader_mat_cluster_mem, i, t1, t2);

        }

        ader_mat_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) > 0)
        	{

        		stream_counter++;

        	}

        	ader_mat_stream = NextItem(ader_mat_stream);

        }

        ader_mat_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) > 0)
        	{

        		stream_counter++;

        	}

        	ader_mat_stream = NextItem(ader_mat_stream);

        }

        ader_mat_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) > 0)
        	{

        		stream_counter++;

        	}

        	ader_mat_stream = NextItem(ader_mat_stream);

        }

        ader_mat_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

        while(ader_mat_stream > VALID_PTR)
        {

        	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) > 0)
        	{

        		stream_counter++;

        	}

        	ader_mat_stream = NextItem(ader_mat_stream);

        }

        ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

    /* Loop through all the members of the cluster again to handle destination*/
    /* shadow stream isotopic fraction processing as well as row and column   */
    /* bound adjustment accounting for removal tables                         */

    ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

        /* Get the index of the cluster member ( this is like a 'mat' entry   */
        /* elsewhere                                                          */

        ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        if(adj < 1)
        {

            /* If this is not an adjustment cycle ( adj = 1 )...              */

            /* Update the cluster member's destination shadow stream's        */
            /* un-fixed elemental isotopics                                   */

            ADERProcessMaterialShadowStreamEleAndIsoFracs(ader_mat_cluster_mem);

            /* Generate and store the necessary cross sections                */

	        CalculateTransmuXS(ader_mat_cluster_mem, omp_id);

	        ADERMoveCrossSection(ader_mat_cluster_mem, step, i);

        }

        /* Adjust the row bounds of the composition matrix based on amounts of*/
        /* material to be removed and amounts of material present             */

        ADERSetMaterialCompMatrixClusterMemRowBounds(dep, i, ader_mat_cluster_mem,
        		                                     0.0,
													 RDB[DATA_BURN_TIME_INTERVAL]);

        /* Set the reactivity control row entries in the comp matrix          */

        ADERSetMaterialCompMatrixClusterMemRhoRowEntries(dep, ader_mat_cluster_mem,
                                                         0.0,
														 RDB[DATA_BURN_TIME_INTERVAL]);

#ifdef ADER_DIAG

        ADERPrintCrossSections(dep, i, mat, step, t1, t2);

#endif

        ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

#ifdef ADER_TEST

    /* Tests for matrix solution routines                                     */

    if((i == 0) &&
       (step == 0) &&
	   ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP) &&
       (strncmp("FLiBeFuel", GetText(mat + MATERIAL_PTR_NAME), 9) == 0))
    {

    	TESTADERAllocateClpMemory(step);

    	TESTADERBuildClpModel(step);

    	TESTADERSolveClpModel(step);

    	TESTADERGetTargetRemovalAmount();

    	TESTADERMatEleIsoBounds();

    	TESTADERGetEigenBias(dep, mat, t1, t2);

    }

#endif

    /* If it's only table class streams you don't need an opt matrix          */

    if(stream_counter > 0)
    {

        /* Build, solve, and store the solution from the comp matrix. Adjust the  */
        /* material density for all affected material if desired                  */

        ADEROperateMaterialCompMatrix(adj, i, mat, step);

    }

}
