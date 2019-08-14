/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialprescompmatrixsection.c      */
/*                                                                           */
/* Created:       2016/03/14 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates a row for a preservation entry in the material       */
/*              comp matrix.                                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialPresCompMatrixSection:"

void ADERCreateMaterialPresCompMatrixSection(long ader_mat_matrix_data,
                                             long ader_mat_pres)
{

    long ader_mat_pres_row = 0;

    ader_mat_pres_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                       0.0,
                                                       0.0);

    WDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID] = (double)ader_mat_pres_row;

}
