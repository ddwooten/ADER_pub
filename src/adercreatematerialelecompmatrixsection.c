/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialelecompmatrixsection.c       */
/*                                                                           */
/* Created:       2016/02/27 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates rows and columns for every element in a material's   */
/*              comp matrix. These rows are the "BAL" row, or the balance    */
/*              row which requires that the 'future' amount of the element   */
/*              minus the 'delta' amount that ADER adds or takes away be     */
/*              equal to the amount of element in the material at the time   */
/*              It's an elemental BALance row. The "DEL" row represents the  */
/*              material that the ADER streams will bring in or take away.   */
/*              The DELta in the elemental composition. The "FUT" row        */
/*              represents the criteria that the element must satisfy in the */
/*              FUTure.                                                      */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialEleCompMatrixSection:"

void ADERCreateMaterialEleCompMatrixSection(long ader_mat_matrix_data,
                                            long mat_ader_data)
{

    long ader_cnt = 0, ader_cnt_ent = 0, ader_mat_cnt = 0, ader_mat_ele = 0, ader_mat_ele_col = 0;
    long ader_mat_ele_row = 0;
    long controlled = 0;

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	/* Reset the control flag                                             */

    	controlled = 0;

        /* Create the columns for the element, give it bounds, and return its index */
        /* Please see adercreatematerialisocompmatrixsection.c for an explanation  */
        /* of why this variable transfer occurs                                    */

        /* First the delta column is created                                  */

        ader_mat_ele_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                           -1E+18,
                                                           1E+18);

        WDB[ader_mat_ele + ADER_MAT_ELE_DEL_COL_ID] = (double)ader_mat_ele_col;

        /* The newly created column is the last in its list. We grap it's index */
        /* (in the WDB array, not its index in the comp matrix ) and store this */
        /* to speed later operations                                            */

        WDB[ader_mat_ele + ADER_MAT_ELE_MATRIX_DEL_COL_PTR] = (double)LastItem((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR]);

        /* Now the future column is created                                   */

        ader_mat_ele_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                           0.0,
                                                           1E+18);

        WDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID] = (double)ader_mat_ele_col;

        WDB[ader_mat_ele + ADER_MAT_ELE_MATRIX_FUT_COL_PTR] = (double)LastItem((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR]);

        /* Now we search the materials cnt tables to see if this element is controlled */
        /* and then we set the row bounds based on this information                    */

        ader_mat_cnt = (long)RDB[mat_ader_data + ADER_MAT_CNT_TBLS_PTR];

        while(ader_mat_cnt > VALID_PTR)
        {

            /* The mat cnt simply points to the ader cnt */

            ader_cnt = (long)RDB[ader_mat_cnt + ADER_MAT_CNT_TBL_PTR];

            ader_cnt_ent = (long)RDB[ader_cnt + ADER_CONTROL_ENT_PTR];

            while(ader_cnt_ent > VALID_PTR)
            {

                /* go though the ader cnt's entries, if a Z matches this element */
                /* you have a match, break this loop and exit the next */

                if((long)RDB[ader_mat_ele + ADER_MAT_ELE_Z] == (long)RDB[ader_cnt_ent + ADER_CONTROL_ENT_Z])
                {

                    controlled = 1;

                    /* Set the element's control flag                         */

                    WDB[ader_mat_ele + ADER_MAT_ELE_CONTROL_FLAG] = 1.0;

                    break;

                }

                ader_cnt_ent = NextItem(ader_cnt_ent);

            }

            /* Control was found, break the overall cnt loop */

            if(controlled > 0)
            {

                break;

            }

            ader_mat_cnt = NextItem(ader_mat_cnt);

        }

        /* First, create the balance row, being controlled doesn't matter here*/

        ader_mat_ele_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                           0.0,
                                                           0.0);

        WDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID] = (double)ader_mat_ele_row;

        /* Now create the delta row, being controlled doesn't matter here    */

        ader_mat_ele_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                           0.0,
                                                           0.0);

        WDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID] = (double)ader_mat_ele_row;

        /* Create the element's future row, pass back its index and set the bounds */
        /* If the bounds are controlled than the min and max are the same for the fut row */
        /* If not, there is no upper bound */

        if(controlled > 0)
        {

            ader_mat_ele_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                               0.0,
                                                               0.0);

            WDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID] = (double)ader_mat_ele_row;

        }
        else
        {

             ader_mat_ele_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                                -1E+18,
                                                                 0.0);

             WDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID] = (double)ader_mat_ele_row;

        }

        /* Create a fourth row for each element in which the isotopic balance */
        /* will be represented. The previous rows were for group composition  */
        /* balance                                                            */

        ader_mat_ele_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                           0.0, 0.0);

        WDB[ader_mat_ele + ADER_MAT_ELE_ISO_ROW_ID] = (double)ader_mat_ele_row;

        ader_mat_ele = NextItem(ader_mat_ele);

    }

}
