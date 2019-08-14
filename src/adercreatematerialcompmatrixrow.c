/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialcompmatrixrow.c              */
/*                                                                           */
/* Created:       2016/02/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Adds one row entry to every column in a material comp matrix */
/*              Creates one row bounds entry and populates it as well.       */
/*              Returns the row index of the created row, which is one less  */
/*              than the number of rows in the comp matrix                   */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialCmpGroupCompMatrixSection                      */
/*          ADERCreateMaterialStreamCompMatrixSection                        */
/*          ADERCreateMaterialOxiCompMatrixSection                           */
/*          ADERCreateMaterialRhoCompMatrixSection                           */
/*          ADERCreateMaterialEleCompMatrixSection                           */
/*          ADERCreateMaterialIsoCompMatrixSection                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialCompMatrixRow:"

long ADERCreateMaterialCompMatrixRow(long ader_mat_matrix_data,
                                     double row_lower_bound,
                                     double row_upper_bound)
{

    long ader_mat_matrix_col = 0, ader_mat_matrix_num_rows = 0, ader_mat_matrix_row_bounds = 0;

    ader_mat_matrix_num_rows = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS];

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(ader_mat_matrix_col > VALID_PTR)
    {

        /* Add a new row to every column in the matrix (stored column wise )*/

        NewItem(ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR,
                ADER_MAT_MATRIX_COL_ROW_BLOCK_SIZE);

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    /* Create a new row bounds entry for the matrix ( we only store bounds once rather than for every column*/

    ader_mat_matrix_row_bounds = NewItem(ader_mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR,
                                         ADER_MAT_MATRIX_ROW_BOUNDS_BLOCK_SIZE);

    /* set those bounds */

    WDB[ader_mat_matrix_row_bounds + ADER_MAT_MATRIX_ROW_LOWER_BOUND] = row_lower_bound;

    WDB[ader_mat_matrix_row_bounds + ADER_MAT_MATRIX_ROW_UPPER_BOUND] = row_upper_bound;

    /* increase the number of rows */

    WDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] = (double)(ader_mat_matrix_num_rows + 1);

    /* We return the OLD number of rows as this represents the index of the */
    /* newly created row, which is one less than the number of actual rows */
    /* when using zero-index notation */

    return(ader_mat_matrix_num_rows);

}
