/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisofutcolbounds.c                   */
/*                                                                           */
/* Created:       2017/11/29 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the isotopic future column bounds are  */
/*              adjusted to account for removal in the isotope's future col  */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoFutColBounds:"

void TESTADERMatIsoFutColBounds(long step)
{

    char *const test_name = "ADERMatIsoFutColBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double expected_value_lower = 0.0;
    double expected_value_upper = 1E+18;
    double expected_removal_amount = 0.004183572012;
    double percent_diff_lower = 0.0, percent_diff_upper = 0.0;
    double test_value_lower = 0.0, test_value_upper = 0.0;
    double argon40_adens, flibefuel_adens;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, controlled_row_bounds, i;
    long iso_col, mat, mat_ader_data;
    long mat_ader_iso, mat_iso, mat_matrix_column, mat_matrix_data, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoFutColBounds.\n");

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

            sprintf(print_data, "Material Argon40 has no ader isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    argon40_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "Material FLiBeFuel not found.\n");

            iso_col = (long)RDB[mat_ader_iso + ADER_MAT_ISO_FUT_ROW_ID];

            break;

        }

        mat_ader_iso = NextItem(mat_ader_iso);

    }

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

    flibefuel_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* The expected values for the  isotope future column bounds must be      */
    /* adjusted for the density difference between the two materials          */

    expected_removal_amount = expected_removal_amount * (flibefuel_adens /
    		                                             argon40_adens);

    /* We add the expected removal amount because it is negative for the mat  */

    expected_value_lower = expected_value_lower - expected_removal_amount;

    expected_value_upper = expected_value_upper - expected_removal_amount;

    mat_matrix_column = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < iso_col; i++)
    {

    	mat_matrix_column = NextItem(mat_matrix_column);

    }

    percent_diff_lower = (RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_LOWER_BOUND] -
    		             expected_value_lower) / expected_value_lower;

    percent_diff_upper = (RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_UPPER_BOUND] -
    		             expected_value_upper) / expected_value_upper;

    sprintf(print_data, "Isotope U-233 in material Argon40 has bad future column bounds of\n\
%.8E and %.8E and should have bounds of .8E and .8E.\n",
            RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_LOWER_BOUND],
			RDB[mat_matrix_column + ADER_MAT_MATRIX_COL_UPPER_BOUND],
			expected_value_lower, expected_value_upper);

    if((fabs(percent_diff_lower) < 0.001) &&
       (fabs(percent_diff_upper) < 0.001))
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
