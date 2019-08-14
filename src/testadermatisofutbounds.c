/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisofutbounds.c                      */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the isotopic row bounds are properly   */
/*              set                                                          */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoFutBounds:"

void TESTADERMatIsoFutBounds(long step)
{

    char *const test_name = "ADERMatIsoFutBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0, boolean_iso_controlled = 0, boolean_iso_uncontrolled = 0;
    long ader_data, ader_test_block, controlled_row_bounds, i;
    long iso_controlled_row, iso_uncontrolled_row, mat, mat_ader_data;
    long mat_ader_iso, mat_iso, mat_matrix_data, nuc;
    long uncontrolled_row_bounds;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoFutBounds.\n");

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

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "Material FLiBeFuel not found.\n");

            iso_uncontrolled_row = (long)RDB[mat_ader_iso + ADER_MAT_ISO_FUT_ROW_ID];

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

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "Material FLiBeFuel has bad matrix data.\n");

            iso_controlled_row = (long)RDB[mat_ader_iso + ADER_MAT_ISO_FUT_ROW_ID];

            break;

        }

        mat_ader_iso = NextItem(mat_ader_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    controlled_row_bounds = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < iso_controlled_row; i++)
    {

    	controlled_row_bounds = NextItem(controlled_row_bounds);

    }

    if((RDB[controlled_row_bounds + ADER_MAT_MATRIX_ROW_LOWER_BOUND] == 0.0) &&
       (RDB[controlled_row_bounds + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0))
    {

        boolean_iso_controlled = 1;

    }

    uncontrolled_row_bounds = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < iso_uncontrolled_row; i++)
    {

    	uncontrolled_row_bounds = NextItem(uncontrolled_row_bounds);

    }

    if((RDB[uncontrolled_row_bounds + ADER_MAT_MATRIX_ROW_LOWER_BOUND] < -1E+17) &&
       (RDB[uncontrolled_row_bounds + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0))
    {

        boolean_iso_uncontrolled = 1;

    }

    if(boolean_iso_controlled == 1 &&
       boolean_iso_uncontrolled == 1)
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

        if(boolean_iso_controlled == 0)
        {

            sprintf(print_data, "\nTest: Controlled Isotope Future Row Bounds: FAIL:\n\
Material FLiBeFuel has matrix row %ld should have lower bound\n \
of %f and upper bound of %f but has lower bound of %f and upper bound of %f.\n",
                    iso_controlled_row, 0.0, 0.0,
                    RDB[controlled_row_bounds + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
                    RDB[controlled_row_bounds + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Controlled Isotope Future Row Bounds: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_iso_uncontrolled == 0)
        {

            sprintf(print_data, "\nTest: Uncontrolled Isotope Future Row Bounds: FAIL:\n\
Material FLiBeFuel has matrix row %ld should have lower bound\n \
of %f and upper bound of %f but has lower bound of %f and upper bound of %f.\n",
                    iso_uncontrolled_row, -1E+18, 0.0,
                    RDB[uncontrolled_row_bounds + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
                    RDB[uncontrolled_row_bounds + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Uncontrolled Isotope Future Row Bounds: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

    }

}
