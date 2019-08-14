/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersolveclpmodel.c                            */
/*                                                                           */
/* Created:       2016/04/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Passes the clp model to the clp simplex solver which returns */
/*              a double array with the solution and the objective value     */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                       TESTADERSolveClpModel               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "Clp_C_Interface.h"
#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSolveClpModel"

void ADERSolveClpModel(double *column_lower_bounds, double *column_upper_bounds,
                       double *index_column_starts, long num_cols, long num_ent,
					   long num_rows, double *objective_row, long opt_dir,
                       double *row_lower_bounds,    double *row_indices,
		               double *row_upper_bounds,    double *solution,
					   double *values, long mat)
{

	/* This is the Clp model "object", yes, this isn't C++ but think of this  */
	/* as an object because it is, it's a port from a C++ code into a C code  */

	Clp_Simplex *clp_model = NULL;

	/* This is for the solution returned by the Clp library. This will be     */
	/* copied into the given solution array                                   */

	double *clp_solution = NULL;

	/* Clp requires that the index_column_starts array and the row_indices    */
	/* array be of type int ( or a custom type but that's irrelevant ),       */
	/* we create arrays for these here                                        */

	int *int_index_column_starts = NULL, *int_row_indices = NULL;

	/* Optimality check, set initial value to failure state                   */

	long optimality = 1;

	long secondary_status = 0;

	/* Loop variable                                                          */

	long i = 0;

	/* Calloc memory for the two int arrays, and the solution                 */

	clp_solution = calloc(num_cols, sizeof(double));

	int_index_column_starts = calloc((num_cols + 1), sizeof(int));

	int_row_indices = calloc(num_ent, sizeof(int));

	/* Now, populate the int versions of the two arrays with their values   */

	for(i = 0; i < (num_cols + 1); i++)
	{

		int_index_column_starts[i] = (int)index_column_starts[i];

	}

	for(i = 0; i < num_ent; i++)
	{

		int_row_indices[i] = (int)row_indices[i];

	}

	/* Instantiate the model                                                  */

	clp_model = Clp_newModel();

	/* Suppress the model output                                              */

	Clp_setLogLevel(clp_model, 0);

	/* Have Clp build the model                                               */

	Clp_loadProblem(clp_model, num_cols, num_rows, int_index_column_starts,
			        int_row_indices, values, column_lower_bounds,
					column_upper_bounds, objective_row, row_lower_bounds,
					row_upper_bounds);

#ifdef ADER_INT_TEST

	if(mat > VALID_PTR)
	{

		TESTADERClpModel(clp_model, mat);

	}

#endif

	/* Set the optimization direction                                         */

	Clp_setObjSense(clp_model, (double)opt_dir);

	/* Solve the matrix                                                       */

	Clp_initialSolve(clp_model);

	/* Check the optimality of the solve                                      */

	optimality = Clp_status(clp_model);

	/* BEGIN ADER TEST MOD */

#ifdef ADER_TEST

    if((long)RDB[DATA_TEST_MODE] == YES)
    {

        optimality = 0;

    }

#endif

    /* END ADER TEST MOD */

	if(optimality > 0)
	{

		/* if the solution was not good, error out and give a consolation     */
		/* message                                                            */

		secondary_status = Clp_secondaryStatus(clp_model);

		Error(0, "Attempted solution of the material composition matrix failed.\n\
Clp status value of %ld. Clp secondary status value of %ld.\n\
No other information is available.\n\
Suggestions:\n \
- Check material constraints. Ensure a possible material composition exists.\n \
- Use smaller time steps for burnup calculation.\n \
\n\
Clp Status Error Codes\n \
0 - ( not an error ) optimal solution\n \
1 - primal infeasible\n \
2 - dual infeasible\n \
3 - stopped on iterations, etc ( literally the error code from Clp )\n \
4 - stopped due to errors ( again, literally the error code from Clp )\n \
\n\
Clp Secondary Status Error Codes\n \
0 - none\n \
1 - primal infeasible because dual limit reached \n \
2 - scaled problem optimal; unscaled has primal infeasibilities\n \
3 - scaled problem optimal; unscaled has dual infeasibilities\n \
4 - scaled problem optimal; unscaled has dual and primal infeasibilities\n \
\n\
Dies Irae: \n \
Day of wrath, and doom impending,\n \
David's word with Sibyl's blending:\n \
Heaven and earth in ashes ending.\n \
What shall I, frail man, be pleading?\n \
Who for me be interceding,\n \
When the just are mercy needing?\n", optimality, secondary_status);

	}

	/* Get the solution vector from the model                                 */

	clp_solution  = Clp_primalColumnSolution(clp_model);

	/* copy the solution to the allocated solution vector                     */

	for(i = 0; i < num_cols; i++)
	{

		solution[i] = clp_solution[i];

	}

	/* Get the objective value and store it to the last entry in the solution */
	/* array                                                                  */

	solution[num_cols] = Clp_objectiveValue(clp_model);

	/* Yes, these arrays are only in this function and would die otherwise    */
	/* but let's be clean and free them manually                              */

	free(clp_solution);

	free(int_index_column_starts);

	free(int_row_indices);

}
