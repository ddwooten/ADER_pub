/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialisocompmatrixsection.c         */
/*                                                                           */
/* Created:       2016/03/24 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills in isotopic data for each mat isotope.                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialIsoCompMatrixSection:"

void ADERFillMaterialIsoCompMatrixSection(long ader_mat_matrix_data,
                                          long mat_ader_data)
{

    long ader_mat_iso = 0;

    /* Loop through all the elements in the material                          */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

        /* First, place the isotopes delta value in the balance row           */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_COL_ID],
                                         (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        /* Next, place the isotopes delta value in the delta row              */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_COL_ID],
                                         (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        /* Next, place the isotopes future value in the balance row            */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
                                         (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID],
                                         ader_mat_matrix_data, 1.0);

        /* Next, place the isotopes future value in the future row            */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
                                         (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        ader_mat_iso = NextItem(ader_mat_iso);

    }

}
