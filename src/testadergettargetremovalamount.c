/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadergettargetremovalamount.c               */
/*                                                                           */
/* Created:       2017/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the returned removal amount is correct */
/*                                                                           */
/* Comments:This function is called from ADEROpperateMaterial                */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERGetTargetRemovalAmount:"

void TESTADERGetTargetRemovalAmount()
{

    char *const test_name = "ADERMatGetRemovalAmount";
    char status[5];
    char print_data[256];
    char *mat_name;
    double ele_rem_amount, iso_rem_amount, percent_diff_ele, percent_diff_iso;
    int append = 0;
    int boolean = 0, boolean_ele = 0, boolean_iso = 0;
    long ader_data, ader_test_block, mat;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERMatGetRemovalAmount.\n");

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

            break;

        }

        mat = NextItem(mat);

    }

    ele_rem_amount = ADERGetTargetRemovalAmount(mat, 3, 0);

    percent_diff_ele = (ele_rem_amount - 0.00121949) / 0.00121949;

    iso_rem_amount = ADERGetTargetRemovalAmount(mat, 0, 30070);

    percent_diff_iso = (iso_rem_amount - 0.00121827) / 0.00121827;

    if(percent_diff_ele < 0.001)
    {

    	boolean_ele = 1;

    }

    if(percent_diff_iso < 0.001)
    {

    	boolean_iso = 1;

    }

    if(boolean_ele == 1 &&
       boolean_iso == 1)
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

        if(boolean_ele == 0)
        {

            sprintf(print_data, "\nTest: Elemental removal amount: FAIL:\n \
Removal amount for Li is given as %f but should be 0.00121949.\n",
                    ele_rem_amount);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Elemental removal amount: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_iso == 0)
        {

            sprintf(print_data, "\nTest: Isotope removal amount: FAIL:\n \
Removal amount for Li-7 is given as %f but should be 0.00121827.\n",
                    iso_rem_amount);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Isotope removal amount: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

    }

}
