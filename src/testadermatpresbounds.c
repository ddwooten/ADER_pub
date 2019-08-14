/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatpresbounds.c                        */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the preservation mols row bounds are   */
/*              properly adjusted to account for removal                     */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatPresBounds:"

void TESTADERMatPresBounds(long step)
{

    char *const test_name = "ADERMatPresBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double expected_value_lower = -2.10536, expected_value_upper = -2.10536;
    double percent_diff_lower = 1.0, percent_diff_upper = 1.0;
    double test_value_lower = 0.0, test_value_upper = 0.0;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, mat, mat_ader_data;
    long mat_matrix_data, mat_matrix_row_bound, mat_pres;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatPresBounds.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no preservation entries.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_pres = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

    while(mat_pres > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has no preservation mols entries.\n");

    	if(strcmp("mols", GetText(mat_pres + ADER_MAT_PRESERVE_ENT)) == 0)
    	{

    		break;

    	}

    	mat_pres = NextItem(mat_pres);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < (long)RDB[mat_pres + ADER_MAT_PRESERVE_ROW_ID]; i++)
    {

        mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

    }

    sprintf(print_data, "Material FLiBeFuel has matrix row %ld should have bounds \n \
of -2.10536 but has lower bound of %f and upper bound of %f.\n",
            (long)RDB[mat_pres + ADER_MAT_PRESERVE_ROW_ID],
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

    test_value_lower = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

    test_value_upper = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

    percent_diff_lower = (test_value_lower - expected_value_lower) /
    		             expected_value_lower;

    percent_diff_upper = (test_value_upper - expected_value_upper) /
    		             expected_value_upper;

    if((fabs(percent_diff_lower) < 0.01) && fabs(percent_diff_upper) < 0.01)
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
