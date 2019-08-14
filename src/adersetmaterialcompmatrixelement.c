/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixelement.c             */
/*                                                                           */
/* Created:       2016/03/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: For the passed in material comp matrix, sets the value       */
/*              specified by the function arguments at the given indices     */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialCmpRtoCompMatrixSection                          */
/*          ADERFillMAterialCmpSumCompMatrixSection                          */
/*          ADERFillMaterialCompMatrixEleData                                */
/*          ADERFillMaterialCompMatrixIsoData                                */
/*          ADERFillMaterialEleCompMatrixSection                             */
/*          ADERFillMaterialIsoCompMatrixSection                             */
/*          ADERFillMaterialObjActFeedAndRemvCompMatrix                      */
/*          ADERFillMaterialObjActFeedCompMatrix                             */
/*          ADERFillMaterialObjActReacCompMatrix                             */
/*          ADERFillMaterialObjActRedoxCompMatrix                            */
/*          ADERFillMaterialObjActRemvCompMatrix                             */
/*          ADERFillMaterialObjActStreamsCompMatrix                          */
/*          ADERFillMaterialObjActTransfersCompMatrix                        */
/*          ADERFillMaterialObjActStreamCompMatrix                           */
/*          ADERFillMaterialObjActGrpCompMatrix                              */
/*          ADERFillMaterialOxiCompMatrixSection                             */
/*          ADERFillMaterialPresMolsCompMatrixSection                        */
/*          ADERFillMaterialStreamCompMatrixSection                          */
/*          ADERSetMaterialCompMatrixClusterMemRhoRowEntries                 */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixElement:"

void ADERSetMaterialCompMatrixElement(long index_col,
                                      long index_row,
                                      long ader_mat_matrix_data,
                                      double value)
{

    long ader_mat_matrix_col = 0, ader_mat_matrix_col_row = 0, i = 0;

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    /* Cycle through to the desired column                                    */

    for(i = 0; i < index_col; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    /* Cycle through to the desired row                                       */

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < index_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    /* Set the value                                                          */

    WDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = value;

}
