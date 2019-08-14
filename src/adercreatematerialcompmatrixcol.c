/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialcompmatrixcol.c              */
/*                                                                           */
/* Created:       2016/02/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates a comp matrix column entry, assinging it bounds and  */
/*              populating it's row items with empty rows equal to the       */
/*              current number of rows in the matrix                         */
/*              Returns the index of the created column, one less than the   */
/*              total number of columns                                      */
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

#define FUNCTION_NAME "ADERCreateMaterialCompMatrixCol:"

long ADERCreateMaterialCompMatrixCol(long ader_mat_matrix_data,
                                     double col_lower_bound,
                                     double col_upper_bound)
{

    long ader_mat_matrix_col = 0, ader_mat_matrix_num_cols = 0;
    long i = 0;

    ader_mat_matrix_num_cols = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS];

    ader_mat_matrix_col = NewItem(ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR,
                                  ADER_MAT_MATRIX_COL_BLOCK_SIZE);

    /* set those bounds */

    WDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND] = col_lower_bound;

    WDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND] = col_upper_bound;

    /* Create the column's rows */

    for(i = 0; i < (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS]; i++)
    {

        NewItem(ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR,
                ADER_MAT_MATRIX_COL_ROW_BLOCK_SIZE);

    }

    /* increase the number of columns */

    WDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] = (double)(ader_mat_matrix_num_cols + 1);

    /* We return the OLD number of cols as this represents the index of the */
    /* newly created col, which is one less than the number of actual cols */
    /* when using zero-index notation */

    return(ader_mat_matrix_num_cols);

}
