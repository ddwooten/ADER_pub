/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderstoreburnmatrixcolumn.c                    */
/*                                                                           */
/* Created:       2016/29/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Actually places generated values in the burnup matrix struct */
/*                                                                           */
/* Comments: This function is called from ADERMakeBurnMatrix                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERStoreBurnMatrixColumn:"

long ADERStoreBurnMatrixColumn(struct ccsMatrix* burn_matrix, long col_index,
		                       double* col_vector, long entry_number,
							   long num_rows)
{

	long i = 0;
	long *row_indices = NULL, *column_starts = NULL;
	complex *values_array = NULL;

	/* Get the pointers to the relevant burn matrix components                */

	column_starts = burn_matrix -> colptr;

	row_indices = burn_matrix -> rowind;

	values_array = burn_matrix -> values;

	/* Now, loop through the col_vector and store its non-zero entries        */

	for(i = 0; i < num_rows; i++)
	{

		/* Do not store 0 entries. This is a dense, column major matrix format*/

		if(col_vector[i] != 0.0)
		{

			/* Store the row this value is found in                           */

			row_indices[entry_number] = i;

			/* Store the value, real part then imaginary part                 */

			values_array[entry_number].re = col_vector[i];

			values_array[entry_number].im = 0.0;

			/* Increment the counter                                          */

			entry_number++;

		}

	}

	/* Store the next column start index                                      */

	column_starts[col_index + 1] = entry_number;

	return(entry_number);

}
