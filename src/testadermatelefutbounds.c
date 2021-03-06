/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatelefutbounds.c                      */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the elemental row bounds are properly  */
/*              set                                                          */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatEleFutBounds:"

void TESTADERMatEleFutBounds(long step)
{

    char *const test_name = "ADERMatEleFutBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0, boolean_ele_controlled = 0, boolean_ele_uncontrolled = 0;
    long ader_data, ader_test_block, controlled_ele_row, controlled_row_bound;
    long i, mat, mat_ader_data;
    long mat_ader_ele, mat_matrix_data;
    long uncontrolled_ele_row, uncontrolled_row_bound;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatEleFutBounds.\n");

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

    mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ader_ele > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has ader elements but no Li.\n");

        if((long)RDB[mat_ader_ele + ADER_MAT_ELE_Z] == 3)
        {

            sprintf(print_data, "Material FLiBeFuel not found. \n");

            uncontrolled_ele_row = (long)RDB[mat_ader_ele + ADER_MAT_ELE_FUT_ROW_ID];

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

    mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ader_ele > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader elements but no Li.\n");

        if((long)RDB[mat_ader_ele + ADER_MAT_ELE_Z] == 3)
        {

            sprintf(print_data, "Material FLiBeFuel has no matrix row bounds.\n");

            controlled_ele_row = (long)RDB[mat_ader_ele + ADER_MAT_ELE_FUT_ROW_ID];

            break;

        }

        mat_ader_ele = NextItem(mat_ader_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    controlled_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < controlled_ele_row; i++)
    {

    	controlled_row_bound = NextItem(controlled_row_bound);

    }

    if((RDB[controlled_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] == 0.0) &&
       (RDB[controlled_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0))
    {

        boolean_ele_controlled = 1;

    }

    uncontrolled_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < uncontrolled_ele_row; i++)
    {

    	uncontrolled_row_bound = NextItem(uncontrolled_row_bound);

    }


    if((RDB[uncontrolled_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] < -1E17) &&
       (RDB[uncontrolled_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0))
    {

        boolean_ele_uncontrolled = 1;

    }

    if(boolean_ele_controlled == 1 &&
       boolean_ele_uncontrolled == 1)
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

        if(boolean_ele_controlled == 0)
        {

            sprintf(print_data, "\nTest: Controlled Element Future Row Bounds: FAIL:\n\
Material FLiBeFuel has matrix row %ld should\n\
have lower bound of %f and upper bound of %f\n\
but has lower bound of %f and upper bound of %f.\n",
                    controlled_ele_row, 0.0, 0.0,
                    RDB[controlled_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
                    RDB[controlled_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Controlled Element Future Row Bounds: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_ele_uncontrolled == 0)
        {

            sprintf(print_data, "\nTest: Uncontrolled Element Future Row Bounds: FAIL:\n\
Material FLiBeFuel has matrix row %ld should\n\
have lower bound of %f and upper bound of %f\n\
but has lower bound of %f and upper bound of %f.\n",
                    uncontrolled_ele_row, -1E+18, 0.0,
                    RDB[uncontrolled_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
                    RDB[uncontrolled_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Uncontrolled Element Future Row Bounds: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

    }

}
