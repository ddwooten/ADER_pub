/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialoxicompmatrixsection.c       */
/*                                                                           */
/* Created:       2016/02/27 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates a row for the oxidation control in the material      */
/*              comp matrix.                                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialOxiCompMatrixSection:"

void ADERCreateMaterialOxiCompMatrixSection(long ader_mat_matrix_data,
                                            long ader_mat_oxi)
{

    long ader_mat_oxi_row = 0;

    /* Create the row for the oxi control, give the oxi data its row index */
    /* variable transfer is done to avoid seg-fault. Explained in iso matrix section */

     ader_mat_oxi_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                        RDB[ader_mat_oxi + ADER_MAT_OXI_MIN],
                                                        RDB[ader_mat_oxi + ADER_MAT_OXI_MAX]);

     WDB[ader_mat_oxi + ADER_MAT_OXI_ROW_ID] = (double)ader_mat_oxi_row;

}
