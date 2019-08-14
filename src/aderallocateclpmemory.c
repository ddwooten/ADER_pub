/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderallocateclpmemory.c                        */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Allocates arrays of doubles according to the size needed by  */
/*              the material comp matrix. Stores these in a an array of      */
/*              double pointers                                              */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                       TESTADERAllocateClpMemory           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERAllocateClpMemory"

double** ADERAllocateClpMemory(long ader_mat_matrix_data)
{

    double **clp_arrays = NULL;
    long ader_mat_matrix_column = 0, ader_mat_matrix_column_row = 0;
    long counter = 0;

    /* First, allocate space for the return value                             */

    clp_arrays = calloc(9, sizeof(double*));

    /* Get the number of non-zero elements in the material comp matrix        */

    ader_mat_matrix_column = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(ader_mat_matrix_column > VALID_PTR)
    {

    	ader_mat_matrix_column_row = (long)RDB[ader_mat_matrix_column + ADER_MAT_MATRIX_COL_ROWS_PTR];

    	while(ader_mat_matrix_column_row > VALID_PTR)
    	{

    		if(fabs(RDB[ader_mat_matrix_column_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]) > 1E-33)
    		{

    			counter++;

    		}

    		ader_mat_matrix_column_row = NextItem(ader_mat_matrix_column_row);

    	}

    	ader_mat_matrix_column = NextItem(ader_mat_matrix_column);

    }

    /* Allocate space for the column lower bounds array, store to clp_arrays  */

    clp_arrays[0] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS],
    		               sizeof(double));

    /* Allocate space for the column upper bounds array, store to clp_arrays  */

    clp_arrays[1] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS],
    		               sizeof(double));

    /* Allocate space for the index column starts array, store to clp_arrays  */

    clp_arrays[2] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] + 1,
    		               sizeof(double));

    /* Allocate space for the objective row, store to clp_arrays              */

    clp_arrays[3] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS],
    		               sizeof(double));

    /* Allocate space for the row lower bounds array, store to clp_arrays     */

    clp_arrays[4] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS],
    		               sizeof(double));

    /* Allocate space for the row indices array, store to clp_arrays    */

    clp_arrays[5] = calloc(counter, sizeof(double));

    /* Allocate space for the row upper bounds array, store to clp_arrays     */

    clp_arrays[6] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS],
    		               sizeof(double));

    /* Allocate space for the solution array, store to clp_arrays, increase by*/
    /* 1 to store the objective value                                         */

    clp_arrays[7] = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] + 1,
    		               sizeof(double));

    /* Allocate space for the values array, store to clp_arrays               */

    clp_arrays[8] = calloc(counter, sizeof(double));

    return(clp_arrays);

}
