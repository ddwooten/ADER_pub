/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderallocateclpmemory.c                    */
/*                                                                           */
/* Created:       2016/04/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the allocation of clp memory.                          */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERAllocateClpMemory:"

void TESTADERAllocateClpMemory(long step)
{

    char *const test_name = "ADERAllocateClpMemory";
    char status[5];
    char print_data[256];
    char *mat_name;
    double **clp_arrays;
    double *column_lower_bounds, *column_upper_bounds, *index_column_starts;
    double *objective_row, *row_lower_bounds, *row_indices, *row_upper_bounds;
    double *solution, *values;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_mat_matrix_data, ader_mat_matrix_column;
    long ader_mat_matrix_column_row, ader_test_block;
    long mat, mat_ader_data;
    long counter = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERAllocateClpMemory.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no ader data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Get the number of non-zero elements in the material composition matrix */

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

    /* Test their length by attempting to assign into them                    */

    column_lower_bounds[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] - 1] = 1.0;

    column_upper_bounds[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] - 1] = 1.0;

    /* the ommisison of the -1 for this array is on purpose                   */
    /* clp requires it to be one additional unit long to hold the objective   */
    /* value                                                                  */

    index_column_starts[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]] = 1.0;

    objective_row[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] - 1] = 1.0;

    row_lower_bounds[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1] = 1.0;

    row_indices[counter - 1] = 1.0;

    row_upper_bounds[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1] = 1.0;

    /* the ommisison of the -1 for the solution index is on purpose           */
    /* it is supposed to be one additional unit long to hold the objective    */
    /* value                                                                  */

    solution[(long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]] = 1.0;

    values[counter - 1] = 1.0;

    /* Deallocate the memory, it isn't needed anymore                         */

    ADERDeallocateTarget(clp_arrays, 9);

    boolean = 1;

    memset(print_data, 0, strlen(print_data));

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

    }

}
