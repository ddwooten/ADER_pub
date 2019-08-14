/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderaveragevalue.c                         */
/*                                                                           */
/* Created:       2016/04/17 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the value of the system leakage in the avg spot to     */
/*              test the efficacy of ADERAveageValue                         */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERAverageValue:"

void TESTADERAverageValue(long dep, long step)
{

    char *const test_name = "ADERAverageValue";
    char status[5];
    char print_data[256];
    char *mat_name;
    double expected_leakage, percent_diff, t1, t2, test_value, wBOS, wEOS, wPS1;
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

    fprintf(outp, "Begin: TESTADERAverageValue.\n");

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

    /* Calculate the average leakage. Compare to the provided value           */

    t1 = 0.0;

    t2 = 10.0 * 24.0 * 60.0 * 60.0;

    wPS1 = RDB[DATA_BURN_FIT_C2W1]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3
      + RDB[DATA_BURN_FIT_C1W1]*(t2*t2-t1*t1)/(t2-t1)/2
      + RDB[DATA_BURN_FIT_C0W1];

    wBOS = RDB[DATA_BURN_FIT_C2W2]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3
      + RDB[DATA_BURN_FIT_C1W2]*(t2*t2-t1*t1)/(t2-t1)/2
      + RDB[DATA_BURN_FIT_C0W2];

    wEOS = RDB[DATA_BURN_FIT_C2W3]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3
      + RDB[DATA_BURN_FIT_C1W3]*(t2*t2-t1*t1)/(t2-t1)/2
      + RDB[DATA_BURN_FIT_C0W3];

    expected_leakage = wBOS * RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS] +
                       wEOS * RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS] +
                       wPS1 * RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1];

    test_value = ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
							      RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
								  RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
								  t1, t2, dep);

    sprintf(print_data, "Material FLiBeFuel has AVG leakage of %f.\n \
Needs AVG leakage of %f.\n", test_value,
            expected_leakage);

    percent_diff = fabs((test_value - expected_leakage) / expected_leakage);

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
