/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatelefutcolbounds.c                   */
/*                                                                           */
/* Created:       2017/11/29 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure the elemental column bounds are properly    */
/*              adjusted to account for removal in the ele fut column.       */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatEleFutColBounds:"

void TESTADERMatEleFutColBounds(long step)
{

    char *const test_name = "ADERMatEleFutColBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double argon40_adens = 0.0, flibefuel_adens = 0.0;
    double expected_removal_amount = 0.001219;
    double expected_value_lower = 0.0, expected_value_upper = 1E+18;
    double percent_diff_lower = 0.0, percent_diff_upper = 0.0;
    double test_value_lower = 0.0, test_value_upper = 0.0;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block;
    long i, mat, mat_ader_data;
    long mat_ader_ele, mat_matrix_column, mat_matrix_data;
    long ele_col;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatEleFutColBounds.\n");

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

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    argon40_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ader_ele > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has ader elements but no Li.\n");

        if((long)RDB[mat_ader_ele + ADER_MAT_ELE_Z] == 3)
        {

            sprintf(print_data, "Material FLiBeFuel not found. \n");

            ele_col = (long)RDB[mat_ader_ele + ADER_MAT_ELE_FUT_COL_ID];

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

            sprintf(print_data, "Material FLiBeFuel has no ader elements.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    flibefuel_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_column = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < ele_col; i++)
    {

    	mat_matrix_column = NextItem(mat_matrix_column);

    }

    /* The expected change in the column bounds must be adjusted for removal  */
    /* with density effects factored in                                       */

    expected_removal_amount = expected_removal_amount * (flibefuel_adens /
    		                                             argon40_adens);

    expected_value_lower = expected_value_lower - expected_removal_amount;

    expected_value_upper = expected_value_upper - expected_removal_amount;

    percent_diff_lower = (RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_LOWER_BOUND] - expected_value_lower)/
    		             expected_value_lower;

    percent_diff_upper = (RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_UPPER_BOUND] - expected_value_upper)/
    		             expected_value_upper;

    sprintf(print_data, "Element lithium in material Argon40 has bad future column bounds of\n\
%.8E and %.8E and should have bounds of .8E and .8E.\n",
            RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_LOWER_BOUND],
			RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_UPPER_BOUND],
			expected_value_lower, expected_value_upper);

    if((fabs(percent_diff_lower) <= 0.001) &&
       (fabs(percent_diff_upper) <= 0.001))
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
