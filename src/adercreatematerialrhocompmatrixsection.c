/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialrhocompmatrixsection.c       */
/*                                                                           */
/* Created:       2016/02/27 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates a row for the criticality control in the material    */
/*              comp matrix.                                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialRhoCompMatrixSection:"

void ADERCreateMaterialRhoCompMatrixSection(long ader_mat_matrix_data,
                                            long mat_ader_data)
{

    long ader_mat_rho_row = 0;

    /* Create the rows for the reactivity control, give the material ader data the row indices */
    /* variable transfer used to avoid seg-fault                                               */

    ader_mat_rho_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                       0.0,
													   1E+18);

    WDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID] = (double)ader_mat_rho_row;

    ader_mat_rho_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                       -1E+18,
                                                       0.0);

    WDB[mat_ader_data + ADER_MAT_RHO_MIN_ROW_ID] = (double)ader_mat_rho_row;

}
