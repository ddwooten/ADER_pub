/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixrowbounds.c           */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Sets a specific row's bounds, either lower or upper as       */
/*              indicated by a bound variable value of 2 or 3 respectively   */
/*              or both bounds if 0 is passed in.                            */
/*              If 'increment' is greater than zero it will add this value to*/
/*              the current bound. If less than zero, the passed in value    */
/*              overwrites the current bound.                                */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds         */
/*          ADERSetMaterialCompMatrixClusterMemRowBounds                     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixRowBounds:"

void ADERSetMaterialCompMatrixRowBounds(long bound,
										long increment,
		                                long mat_matrix_data,
		                                long mat_matrix_row_id,
										double value)
{

	long i = 0, mat_matrix_row_bound = 0;

	/* Get the row bound in question                                          */

	mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

	for(i = 0; i < mat_matrix_row_id; i++)
	{

		mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

	}

	/* If increment is greater than 0, add value to the row bound             */

	if(increment > 0)
	{

		if(bound == 0)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] +
					                                                      value;

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] +
					                                                      value;

		}
		else if(bound == 1)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] +
					                                                      value;

		}
		else if(bound == 2)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] +
					                                                      value;

		}
		else
		{

			Die(FUNCTION_NAME, "Function ADERSetMaterialCompMatrixRowBounds received bad value for variable\n\
'bound' of %ld but should have received a value of 0, 1, or 2.\n", bound);

		}

	}
	else
	{

		if(bound == 0)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] = value;

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] = value;

		}
		else if(bound == 1)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] = value;

		}
		else if(bound == 2)
		{

			WDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] = value;

		}
		else
		{

			Die(FUNCTION_NAME, "Function ADERSetMaterialCompMatrixRowBounds received bad value for variable\n\
'bound' of %ld but should have received a value of 0, 1, or 2.\n", bound);

		}

	}

}
