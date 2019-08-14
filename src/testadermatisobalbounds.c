/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisobalbounds.c                      */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the isotopic row bounds are properly   */
/*              adjusted to account for removal and mateiral abundance in the*/
/*              isos bal row                                                 */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoBalBounds:"

void TESTADERMatIsoBalBounds(long step)
{

    char *const test_name = "ADERMatIsoBalBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, mat, mat_ader_data, mat_ader_iso;
    long mat_ader_iso_row, mat_iso, mat_matrix_data, mat_matrix_row_bound, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoBalBounds.\n");

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

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "Material FLiBeFuel not has no matrix rows.\n");

            mat_ader_iso_row = (long)RDB[mat_ader_iso + ADER_MAT_ISO_BAL_ROW_ID];

            break;

        }

        mat_ader_iso = NextItem(mat_ader_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < mat_ader_iso_row; i++)
    {

        mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

    }

    sprintf(print_data, "Material FLiBeFuel has matrix row %ld should have bounds \n \
of 0.008503482 but has lower bound of %f and upper bound of %f.\n",
            mat_ader_iso_row,
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
            RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

    if((RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] > 0.000135 &&
        RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] < 0.000137) &&
       (RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] > 0.000135 &&
        RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] < 0.000137))
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
