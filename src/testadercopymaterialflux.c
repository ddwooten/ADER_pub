/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadercopymaterialflux.c                     */
/*                                                                           */
/* Created:       2016/04/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that ADERCopyMaterialFlux is working (kind of, this is */
/*              not a rigerous test                                          */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*          It will only pass in the case of not SIE ( single iteration euler*/
/*          set by serpent option 'sie' ) though it designed for SIE. This   */
/*          said, the principle by which it operates, if it operates         */
/*          correctly in PCC mode it will most likely work in SIE            */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERCopyMaterialFlux:"

void TESTADERCopyMaterialFlux(long step)
{

    char *const test_name = "ADERCopyMaterialFlux";
    char status[5];
    char print_data[256];
    char *mat_name;
    double percent_diff;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, mat, mat_ader_data;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the second step and a corrector iteration   */

    if((step != 1) && ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP))
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERCopyMaterialFlux.\n");

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

            sprintf(print_data, "Material FLiBeFuel has no ader data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Compare old and new flux, they should be the same                      */



    sprintf(print_data, "Material FLiBeFuel has new flux of %f\n \
and has old flux of %f.\n", RDB[mat_ader_data + ADER_MAT_FLUX_NEW_AVG],
            RDB[mat_ader_data + ADER_MAT_FLUX_OLD_AVG]);

    percent_diff = fabs((RDB[mat_ader_data + ADER_MAT_FLUX_OLD_AVG] -
                        RDB[mat_ader_data + ADER_MAT_FLUX_NEW_AVG]) /
                        RDB[mat_ader_data + ADER_MAT_FLUX_NEW_AVG]);

    if(percent_diff < 0.0001)
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
