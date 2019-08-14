/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialelecompmatrixsection.c         */
/*                                                                           */
/* Created:       2016/03/24 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills in element data for each mat element. Also populates   */
/*              element isotopic balance rows with isotopic data             */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialEleCompMatrixSection:"

void ADERFillMaterialEleCompMatrixSection(long ader_mat_matrix_data,
                                          long mat_ader_data)
{

    long ader_mat_ele = 0, ader_mat_ele_iso = 0, ader_mat_iso = 0;

    /* Loop through all the elements in the material                          */

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

        /* First, put the element's delta value in the balance row            */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_COL_ID],
                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        /* Next, put the element's delta value in the delta row               */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_COL_ID],
                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        /* Next, put the element's future value in the balance row            */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID],
                                         ader_mat_matrix_data, 1.0);

        /* Next, put the element's future value in the future composition row*/

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID],
                                         ader_mat_matrix_data, -1.0);

        /* Now place the element's future value in the iso balance row        */

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISO_ROW_ID],
                                         ader_mat_matrix_data, 1.0);

        /* Now, loop through the element's isotopes and set their values in   */
        /* the isotopic balance row                                           */

        ader_mat_ele_iso = (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISOS_PTR];

        while(ader_mat_ele_iso > VALID_PTR)
        {

            ader_mat_iso = (long)RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
                                             (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISO_ROW_ID],
                                             ader_mat_matrix_data, -1.0);

            ader_mat_ele_iso = NextItem(ader_mat_ele_iso);

        }

        ader_mat_ele = NextItem(ader_mat_ele);

    }

}
