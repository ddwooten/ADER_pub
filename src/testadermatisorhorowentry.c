/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisorhorowentry.c                    */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that an isotopes reactivity control entry is correct   */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoRhoRowEntry:"

void TESTADERMatIsoRhoRowEntry(long dep, long step)
{

    char *const test_name = "ADERMatIsoRhoRowEntry";
    char status[5];
    char print_data[256];
    char *mat_name;
    double bias = 0, percent_diff, test_value;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, mat, mat_ader_data, mat_ader_iso;
    long mat_ader_iso_fut_col, mat_iso, mat_matrix_data, mat_matrix_col;
    long mat_matrix_col_row, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoRhoRowEntry.\n");

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

    bias = ADERGetEigenBias(dep, mat, 0.0, RDB[DATA_BURN_TIME_INTERVAL]);

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "Material FLiBeFuel has no matrix columns.\n");

            /* This test value should be equal to....                         */
            /* ( ( ( K_max /( ( 1 - p_l) * bias) ) * sigma_abs ) - ( nu_bar * sigma_fis ) ) */

            test_value = (((RDB[ader_data + ADER_K_MAX] /
                           ((1.0 - ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
                        		                    RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
								                    RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
                                                    0.0, RDB[DATA_BURN_TIME_INTERVAL], dep)) *
                             bias)) *
                            ADERAverageValue(RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
                            		         RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
									         RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
                                             0.0, RDB[DATA_BURN_TIME_INTERVAL], dep)) -
                          ADERAverageValue(RDB[mat_ader_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
                        		           RDB[mat_ader_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
								           RDB[mat_ader_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
                                           0.0, RDB[DATA_BURN_TIME_INTERVAL], dep));

            mat_ader_iso_fut_col = (long)RDB[mat_ader_iso + ADER_MAT_ISO_FUT_COL_ID];

            break;

        }

        mat_ader_iso = NextItem(mat_ader_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for( i = 0; i < mat_ader_iso_fut_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < (long)RDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID]; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    percent_diff = fabs((RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
                         test_value) / test_value);

    sprintf(print_data, "Material FLiBeFuel isotope U-233 has reactivity \n \
value %f in matrix element (%ld, %ld) but needs reactivity value %f.\n",
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
            mat_ader_iso_fut_col,
            (long)RDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID], test_value);

    if(percent_diff < 0.001)
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
