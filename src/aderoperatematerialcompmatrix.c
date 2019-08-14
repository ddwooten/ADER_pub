/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoperatematerialcompmatrix.c                */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to build the clp model of the material comp  */
/*              matrix and then solves this matrix. Assigns the solution     */
/*              components through ADERParseClpSolution                      */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROperateMaterialCompMatrix:"

void ADEROperateMaterialCompMatrix(long adj, long i, long mat, long step)
{

    double **clp_arrays = NULL;
    double *column_lower_bounds = NULL, *column_upper_bounds = NULL, *index_column_starts = NULL;
    double *objective_row = NULL, *row_lower_bounds = NULL, *row_indices = NULL, *row_upper_bounds = NULL;
    double *solution = NULL, *values = NULL;
    long ader_mat_matrix_data = 0, ader_mat_opt = 0, mat_ader_data = 0, num_ent = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the material optimization data, this will be needed in solve        */

    ader_mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    /* No opt entries were found. At least one is required                    */

    if(ader_mat_opt < VALID_PTR)
    {

        Error(0, "Parent material, %s, has no opt entry and is under ADER control.\n\
At least one member of an ADER cluster* must have opt data in a conditions block\n \
attached to said material. Any material in a cluster, but ONLY ONE material,\n \
may have an opt entry; ADER will copy this entry over to the parent material.\n\n\
* An ADER 'cluster' is a group of materials which are connected \n \
with ADER 'stream' entries.\n\
I.e., materials which are sources and sinks for one another.\n",
                      GetText(mat + MATERIAL_PTR_NAME));

    }

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Call ADERAllocateClpMemory to allocate memory for the clp components   */

    clp_arrays = ADERAllocateClpMemory(ader_mat_matrix_data);

    /* Get the array pointers given by ADERAllocateClpMemory                  */

    column_lower_bounds = clp_arrays[0];

    column_upper_bounds = clp_arrays[1];

    index_column_starts = clp_arrays[2];

    objective_row = clp_arrays[3];

    row_lower_bounds = clp_arrays[4];

    row_indices = clp_arrays[5];

    row_upper_bounds = clp_arrays[6];

    solution = clp_arrays[7];

    values = clp_arrays[8];

#ifdef ADER_DIAG

    ADEROutputMaterialCompMatrixData();

#endif


    /* Pass these array pointers and the requisite information to Build       */

    num_ent = ADERBuildClpModel(ader_mat_matrix_data, column_lower_bounds,
    		                    column_upper_bounds, index_column_starts,
					            objective_row, row_lower_bounds,
					            row_indices, row_upper_bounds, values);

    /* Now that the matrix is built, pass this to solve                       */

    ADERSolveClpModel(column_lower_bounds, column_upper_bounds,
    		          index_column_starts,
					  (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS],
					  num_ent,
					  (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS],
					  objective_row, (long)RDB[ader_mat_opt + ADER_MAT_OPT_DIR],
	                  row_lower_bounds, row_indices,
					  row_upper_bounds, solution, values, mat);

    /* If tests are being used, 0 out the solution vector to ease testing     */

#ifdef ADER_TEST

    TESTAderModifyClpSolution(solution, (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]);

#endif

    /* And now that the solution is known, pass this to Parse                 */

    ADERParseClpSolution(adj, i, mat, step, solution);

#ifdef ADER_TEST

	if((i == 0) && (step == 0) &&
	   ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP) &&
	   (strcmp("FLiBeFuel", GetText(mat + MATERIAL_PTR_NAME)) == 0))
	{

		TESTADERParseClpSolution(solution, step);

	}

#endif

	/* Call ADERDeallocateTarget to free all memory allocated by              */
    /* ADERAllocateClpMemory                                                  */

    ADERDeallocateTarget(clp_arrays, 9);

}
