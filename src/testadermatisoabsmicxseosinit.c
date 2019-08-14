/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisoabsmicxseosinit.c                */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that an isotopes miscro fission x nu_bar cross section */
/*              for the end of step is properly initiated to -INFTY at       */
/*              first step                                                   */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoAbsMicXsEosInit:"

void TESTADERMatIsoAbsMicXsEosInit(long step)
{

    char *const test_name = "ADERMatIsoAbsMicXsEosInit";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, mat, mat_ader_data, mat_ader_iso;
    long mat_iso, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoAbsMicXsEosInit.\n");

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

            sprintf(print_data, "Material FLiBeFuel has U-233 but the \n \
ADER_MAT_ISO_ABS_MIC_XS_EOS has bad value of %f. Needs value of -INFTY.\n",
                    RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS]);

            if(RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS] < -1E-36)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        mat_ader_iso = NextItem(mat_ader_iso);

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
