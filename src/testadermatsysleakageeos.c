/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatsysleakageeos.c                     */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the value of the system leakage in the eos spot at init*/
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatSysLeakageEos:"

void TESTADERMatSysLeakageEos(long step)
{

    char *const test_name = "ADERMatSysLeakageEos";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, mat, mat_ader_data;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatSysLeakageEos.\n");

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

    if(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS] < -1E+35)
    {

        boolean = 1;

        sprintf(print_data, "Material FLiBeFuel has EOS leakage of %f.\n \
K-imp-inf: %f \n K-imp-eff: %f \n K-imp-leakage: %f \n",
                RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
                RDB[RES_IMP_KINF], RDB[RES_IMP_KEFF],
                (1.0 - RDB[RES_IMP_KEFF] / RDB[RES_IMP_KINF]));

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
