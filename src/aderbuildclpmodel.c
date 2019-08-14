/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderbuildclpmodel.c                            */
/*                                                                           */
/* Created:       2016/04/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Populates the arrays created by ADERAllocateClpMemory with   */
/*              the material comp matrix data as needed by Clp. Additionally */
/*              returns the number of non-zero elements as this is needed by */
/*              ADERSolveClpModel                                            */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                       TESTADERBuildClpModel               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERBuildClpModel"

long ADERBuildClpModel(long ader_mat_matrix_data,   double *column_lower_bounds,
                       double *column_upper_bounds, double *index_column_starts,
		               double *objective_row,       double *row_lower_bounds,
		               double *row_indices,         double *row_upper_bounds,
					   double *values)
{

    long ader_mat_matrix_column  = 0, ader_mat_matrix_column_row = 0;
    long ader_mat_matrix_row_bound = 0, row_num = 0;
    long col_num = 0, num_ent = 0;

    /* First set the first entry of index_coumn_starts to 0. This is because  */
    /* index_column_starts is 1 + the number of columns long                  */

    index_column_starts[0] = 0.0;

    /* Loop through the columns to set column information                     */

    ader_mat_matrix_column = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(ader_mat_matrix_column > VALID_PTR)
    {

    	/* Assign column bounds                                               */

    	column_lower_bounds[col_num] = RDB[ader_mat_matrix_column + ADER_MAT_MATRIX_COL_LOWER_BOUND];

    	column_upper_bounds[col_num] = RDB[ader_mat_matrix_column + ADER_MAT_MATRIX_COL_UPPER_BOUND];

    	/* Set the starting row number for this column                        */

    	row_num = 0;

    	/* Loop through the rows in this column                               */

    	ader_mat_matrix_column_row = (long)RDB[ader_mat_matrix_column + ADER_MAT_MATRIX_COL_ROWS_PTR];

    	/* Do not execute the last row here, that is the objective row and it */
    	/* gets its own array                                                 */

    	while((ader_mat_matrix_column_row > VALID_PTR) &&
    	      (row_num < ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1)))
    	{

    		/* If the value in this matrix position is not 0, process it      */

    		if(fabs(RDB[ader_mat_matrix_column_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]) > 1E-14)
    		{

    			/* Store the row index where this value is found              */

    			row_indices[num_ent] = (double)row_num;

    			/* Store the value found at this matrix position              */

    			values[num_ent] = RDB[ader_mat_matrix_column_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    			/* Increment the number of values stored                      */

    			num_ent++;

    		}

    		/* Increment the number of rows processed                         */

    		row_num++;

    		ader_mat_matrix_column_row = NextItem(ader_mat_matrix_column_row);

    	}

    	/* Populate the objective row. It is the last row in every column     */

    	objective_row[col_num] = RDB[ader_mat_matrix_column_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    	/* Increment the column number                                        */

    	col_num++;

    	/* Store the number of entries ( which also the index in the values   */
    	/* and row indices arrays where the next column's information starts )*/
    	/* in the index_column_starts array                                   */

    	index_column_starts[col_num] = (double)num_ent;

    	ader_mat_matrix_column = NextItem(ader_mat_matrix_column);

        /* Reset the row counter                                                  */

        row_num = 0;

    }

    /* Now, loop through the row bounds information and populate the row      */
    /* bounds, the objective row doens't have bounds so don't bother          */

    ader_mat_matrix_row_bound = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    while((ader_mat_matrix_row_bound > VALID_PTR) &&
    	  (row_num < ((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1)))
    {

    	/* Assign the row bounds                                              */

    	row_lower_bounds[row_num] = RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

    	row_upper_bounds[row_num] = RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

    	/* Increment the row counter                                          */

    	row_num++;

    	ader_mat_matrix_row_bound = NextItem(ader_mat_matrix_row_bound);

    }

    /* return the number of entries, but increment so that it reflects the    */
    /* actual number of entries which is currently one less than the number   */

    num_ent++;

    return(num_ent);

}
