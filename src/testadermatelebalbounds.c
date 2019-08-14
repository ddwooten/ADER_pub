/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatelebalbounds.c                      */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the elemental row bounds are properly  */
/*              adjusted to account for removal and material abundance in the*/
/*              ele bal row                                                  */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatEleBalBounds:"

void TESTADERMatEleBalBounds(long step)
{

    char *const test_name = "ADERMatEleBalBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double argon40_adens, flibefuel_adens, percent_lower_diff;
    double percent_upper_diff, target_lower_value, target_upper_value;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, mat, mat_ader_data, mat_ader_ele;
    long mat_ader_ele_row, mat_matrix_data, mat_matrix_row_bound;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatEleBalBounds.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no ader elements.\n");

            break;

        }

        mat = NextItem(mat);

    }

    argon40_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ader_ele > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has ader elements but no Li.\n");

        if((long)RDB[mat_ader_ele + ADER_MAT_ELE_Z] == 3)
        {

            sprintf(print_data, "Material FLiBeFuel not found.\n");

            mat_ader_ele_row = (long)RDB[mat_ader_ele + ADER_MAT_ELE_BAL_ROW_ID];

            break;

        }

        mat_ader_ele = NextItem(mat_ader_ele);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no matrix bounds.\n");

            break;

        }

        mat = NextItem(mat);

    }

    flibefuel_adens = RDB[mat + MATERIAL_ADENS];

    /* The 2.0 is for volume effects                                          */

    target_lower_value = 0.00121949 * (flibefuel_adens / argon40_adens) * 2.0;

    target_upper_value = 0.00121949 * (flibefuel_adens / argon40_adens) * 2.0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < mat_ader_ele_row; i++)
    {

        mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

    }

    sprintf(print_data, "Material FLiBeFuel has matrix row %ld should have bounds \n \
of %f but has lower bound of %f and upper bound of %f.\n",
            mat_ader_ele_row, target_lower_value,
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

    percent_lower_diff = (RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] -
    		              target_lower_value ) / target_lower_value;

    percent_upper_diff = (RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] -
                           target_upper_value ) / target_upper_value;

    if(fabs(percent_lower_diff) < 0.00001 && fabs(percent_upper_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

    }

}
