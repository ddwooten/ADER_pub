/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatminrhomaxrowbound.c                 */
/*                                                                           */
/* Created:       2018/02/03 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that the reactivity minimum row maximum bound has been */
/*              set properly                                                 */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatMinRhoMaxRowBound:"

void TESTADERMatMinRhoMaxRowBound()
{

    char *const test_name = "ADERMatMinRhoMaxRowBound";
    char status[5];
    char print_data[256];
    char *mat_name;
    double percent_diff, test_value;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, mat, mat_ader_data, mat_ader_iso;
    long mat_ader_iso_fut_col, mat_iso, mat_matrix_data, mat_matrix_col;
    long mat_matrix_row_bound, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERMatMinRhoMaxRowBound.\n");

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

            sprintf(print_data, "Material FLiBeFuel has no ader isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for( i = 0; i < (long)RDB[mat_ader_data + ADER_MAT_RHO_MIN_ROW_ID]; i++)
    {

    	mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

    }

    sprintf(print_data, "Material FLiBeFuel minimum reactivity row has upper \n \
bound of %.12f and should have an upper bound of 0.0.\n",
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

    if(RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0)
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
