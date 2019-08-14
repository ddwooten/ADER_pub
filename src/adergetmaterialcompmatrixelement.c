/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetmaterialcompmatrixelement.c             */
/*                                                                           */
/* Created:       2016/03/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: For the passed in material comp matrix, and the column and   */
/*              row index, returns the value at that position                */
/*                                                                           */
/* Comments:This function is called from                                     */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetMaterialCompMatrixElement:"

double ADERGetMaterialCompMatrixElement(long ader_mat_matrix_data,
                                        long col_index, long row_index)
{

    long ader_mat_matrix_col = 0, ader_mat_matrix_col_row = 0, i = 0;

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    /* Cycle through to the desired column                                    */

    for(i = 0; i < col_index; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    /* Cycle through to the desired row                                       */

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < row_index; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    /* Return the value                                                          */

    return(WDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

}
