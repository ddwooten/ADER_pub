/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoutputmaterialcompmatrixdata.c             */
/*                                                                           */
/* Created:       2017/08/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Compares the Clp matrix model generated from the material    */
/*              composition optimization matrix with said matrix             */
/*                                                                           */
/* Comments:This function is called from ADERSolveClpModel                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"
#include "Clp_C_Interface.h"

#define FUNCTION_NAME "TESTADERClpModel:"

void TESTADERClpModel(Clp_Simplex* clp_model, long mat)
{

    char print_data[256];
    FILE *fp;
	const CoinBigIndex *clp_col_starts;
	double *clp_col_lower_bounds, *clp_col_upper_bounds;
	const double *clp_matrix_elements;
	double *clp_objective_row, *clp_row_lower_bounds, *clp_row_upper_bounds;
	double percent_diff;
	int clp_num_elements = 0;
	const int *clp_row_indices, *clp_col_lengths;
	long clp_num_cols = 0, clp_num_rows = 0, num_errors = 0;
	long ader_mat_data, ader_mat_matrix_col, ader_mat_matrix_col_row;
	long ader_mat_matrix_data, ader_mat_matrix_row_bound, found;
	int i, j, k;

	/* Create the file name                                                   */

	sprintf(print_data, "ADER_Clp_Model_Material_%s_Conformity.test",
			GetText(mat + MATERIAL_PTR_NAME));

	if ((fp = fopen(print_data, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open file for writing Clp matrix conformity results.\n");

	}

	fprintf(outp, "Beginning Clp matrix conformity check for material %s.\n\n",
			GetText(mat + MATERIAL_PTR_NAME));

	/* Grab the clp data                                                      */

	clp_col_lengths = Clp_getVectorLengths(clp_model);

	clp_col_lower_bounds = Clp_columnLower(clp_model);

	clp_col_starts = Clp_getVectorStarts(clp_model);

	clp_col_upper_bounds = Clp_columnUpper(clp_model);

	clp_matrix_elements = Clp_getElements(clp_model);

	clp_num_cols = Clp_numberColumns(clp_model);

	clp_num_elements = Clp_getNumElements(clp_model);

	clp_num_rows = Clp_numberRows(clp_model);

	clp_objective_row = Clp_objective(clp_model);

	clp_row_indices = Clp_getIndices(clp_model);

	clp_row_lower_bounds = Clp_rowLower(clp_model);

	clp_row_upper_bounds = Clp_rowUpper(clp_model);

	fprintf(fp, "Clp number of matrix elements is %i \n", clp_num_elements);

	/* Grab the material matrix data                                          */

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

	/* Loop through the clp data checking it against the material matrix data */

	for(i = 0; i < clp_num_cols; i++)
	{

		if(clp_col_lengths[i] != (clp_col_starts[i + 1] - clp_col_starts[i]))
		{

			fprintf(fp, "Clp column vector length is %i but Clp column starts difference is %i for\n\
column %i.\n",     clp_col_lengths[i],
(clp_col_starts[i + 1] - clp_col_starts[i]), i);

		}

		/* Retrieve the material matrix column                                */

		ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

		for(j = 0; j < i; j++)
		{

			ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

		}

		/* Check the bounds                                                   */

		percent_diff = (RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND] - clp_col_lower_bounds[i])/
				       clp_col_lower_bounds[i];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Clp column %i has lower bound %1.16E while matrix column has\n\
lower bound of %1.16E.\n\
Material matrix column RDB address: %ld\n", i, clp_col_lower_bounds[i],
	                RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND],
					ader_mat_matrix_col);

			num_errors++;

		}

		percent_diff = (RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND] - clp_col_upper_bounds[i])/
				       clp_col_upper_bounds[i];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Clp column %i has upper bound %1.16E while matrix column has\n\
upper bound of %1.16E.\n\
Material matrix column RDB address: %ld\n", i, clp_col_lower_bounds[i],
	                RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND],
					ader_mat_matrix_col);

			num_errors++;

		}

		/* Check the entries                                                  */

		for(j = clp_col_starts[i]; j < clp_col_starts[i + 1]; j++)
		{

			/* Get the appropriate row from the material matrix               */

			ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

			for(k = 0; k < clp_row_indices[j]; k++)
			{

				ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

			}

			percent_diff = (RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] - clp_matrix_elements[j])/
					       clp_matrix_elements[j];

			if(fabs(percent_diff) > 0.001)
			{

				fprintf(fp, "Clp matrix has value %1.15E at matrix location [ %i , %i ]\n\
while material matrix has value %1.15E.\n\
Material matrix column RDB address: %ld\n\
Material matrix column row RDB address: %ld\n", clp_matrix_elements[j],
						clp_row_indices[j], i,
                        RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
						ader_mat_matrix_col, ader_mat_matrix_col_row);

				num_errors++;

			}

		}

		/* Check the objective row                                            */

		/* Get the objective row from the material matrix                     */

		ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

		for(k = 0; k < clp_num_rows - 1; k++)
		{

			ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

		}

		percent_diff = (RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] - clp_objective_row[i])/
				       clp_objective_row[i];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Clp objective row has value %1.15E while material matrix objective\n\
	has value %1.15E.\n\
	Material matrix column RDB address: %ld\n\
	Material matrix column row RDB address: %ld\n", clp_objective_row[i],
	                RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
					ader_mat_matrix_col, ader_mat_matrix_col_row);

			num_errors++;

		}

	}

	/* Now check the row bounds                                               */

	ader_mat_matrix_row_bound = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

	for(i = 0; i < clp_num_rows; i++)
	{

		percent_diff = (RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] - clp_row_lower_bounds[i])/
                       clp_row_lower_bounds[i];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Clp row %i has lower bound %1.16E while matrix row has\n\
lower bound of %1.16E.\n\
Material matrix row bound RDB address: %ld\n", i, clp_row_lower_bounds[i],
	                RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
					ader_mat_matrix_row_bound);

			num_errors++;

		}

		percent_diff = (RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] - clp_row_upper_bounds[i])/
                       clp_row_upper_bounds[i];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Clp row %i has upper bound %1.16E while matrix row has\n\
upper bound of %1.16E.\n\
Material matrix row bound RDB address: %ld\n", i, clp_row_upper_bounds[i],
	                RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND],
					ader_mat_matrix_row_bound);

			num_errors++;

		}

		ader_mat_matrix_row_bound = NextItem(ader_mat_matrix_row_bound);

	}

	/* Now do the reverse check. Loop through the material matrix data and    */
	/* check it against the clp data                                          */

	ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

	for(i = 0; i < (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]; i++)
	{

		/* Check the column bounds                                            */

		percent_diff = (clp_col_lower_bounds[i] - RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND])/
				       RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Matrix column %i has lower bound %1.16E while clp column has\n\
lower bound of %1.16E.\n\
Material matrix column RDB address: %ld\n", i, RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND],
                    clp_col_lower_bounds[i],
					ader_mat_matrix_col);

			num_errors++;

		}

		percent_diff = (clp_col_upper_bounds[i] - RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND])/
				       RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Matrix column %i has upper bound %1.16E while clp column has\n\
upper bound of %1.16E.\n\
Material matrix column RDB address: %ld\n", i, RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND],
                    clp_col_upper_bounds[i],
					ader_mat_matrix_col);

			num_errors++;

		}

		/* Now check the matrix entries                                       */

		ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

		for(j = 0; j < (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1; j++)
		{

			if(RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] != 0.0)
			{

				found = 0;

				for(k = clp_col_starts[i]; k < clp_col_starts[i + 1]; k++)
				{

					if(clp_row_indices[k] == j)
					{

						found = 1;

						break;

					}

				}

				if(found < 1)
				{

					fprintf(fp, "No matching clp matrix entry was found for material matrix entry located at\n\
[ %i , %i ].\n\
Material matrix column RDB address: %ld\n\
MAterial matrix column row address: %ld\n", j, i, ader_mat_matrix_col,
                            ader_mat_matrix_col_row);

					num_errors++;

				}
				else
				{

					percent_diff = (clp_matrix_elements[k] - RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY])/
							       RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

					if(fabs(percent_diff) > 0.001)
					{

						fprintf(fp, "Material matrix has value %1.15E at matrix location [ %i , %i ]\n\
while clp matrix has value %1.15E.\n\
Material matrix column RDB address: %ld\n\
Material matrix column row RDB address: %ld\n", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
								j , i,
		                        clp_matrix_elements[k],
								ader_mat_matrix_col, ader_mat_matrix_col_row);

						num_errors++;

					}

				}

			}

			ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

		}

		/* Now check the objective row                                        */

		percent_diff = (clp_objective_row[i] - RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY])/
				       RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Material objective row has value %1.15E while clp matrix objective\n\
has value %1.15E.\n\
Material matrix column RDB address: %ld\n\
Material matrix column row RDB address: %ld\n", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
					clp_objective_row[i],
					ader_mat_matrix_col, ader_mat_matrix_col_row);

			num_errors++;

		}

		ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

	}

	/* Now check the row bounds                                               */

	ader_mat_matrix_row_bound = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

	for(i = 0; i < (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1; i++)
	{

		percent_diff = (clp_row_lower_bounds[i] - RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND])/
				       RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Material matrix row %i has lower bound %1.16E while clp row has\n\
lower bound of %1.16E.\n\
Material matrix row bound RDB address: %ld\n", i,
                    RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
                    clp_row_lower_bounds[i],
					ader_mat_matrix_row_bound);

			num_errors++;

		}

		percent_diff = (clp_row_upper_bounds[i] - RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND])/
				       RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

		if(fabs(percent_diff) > 0.001)
		{

			fprintf(fp, "Material matrix row %i has upper bound %1.16E while clp row has\n\
upper bound of %1.16E.\n\
Material matrix row bound RDB address: %ld\n", i,
	                RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND],
					clp_row_upper_bounds[i],
					ader_mat_matrix_row_bound);

			num_errors++;

		}

		ader_mat_matrix_row_bound = NextItem(ader_mat_matrix_row_bound);

	}

	if(num_errors == 0)
	{

		fprintf(fp, "No discrepancies were found between the Clp matrix and the material composition\n\
matrix.\n");

	}
	else
	{

		fprintf(fp, "%ld total discrepancies were found between the Clp matrix\n\
and the material composition matrix.\n", num_errors);

	}

	/* Close the file                                                         */

	fclose(fp);

}
