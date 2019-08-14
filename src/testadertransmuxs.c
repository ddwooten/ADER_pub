/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadertransmuxs.c                            */
/*                                                                           */
/* Created:       2016/04/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that transmutation cross sections were      */
/*              acquired                                                     */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERTransmuXS:"

void TESTADERTransmuXS(long step)
{

    char *const test_name = "ADERTransmuXS";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, mat, mat_iso, rea, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERTransmuXS.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBEFuel not found.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no U-233.\n");

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

            sprintf(print_data, "FLiBeFuel U-233 has no reactions.\n");

            rea = (long)RDB[nuc + NUCLIDE_PTR_REA];

            while(rea > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel U-233 has reactions but no fission XS.\n");

                if((long)RDB[rea + REACTION_PTR_FISSY] > VALID_PTR)
                {

                    sprintf(print_data, "FLiBeFuel U-233 has fission XS but only decay.\n");

                    if((long)RDB[rea + REACTION_TYPE] != REACTION_TYPE_DECAY)
                    {

                        sprintf(print_data, "FLiBeFuel U-233 has fission XS but 0 value.\n");

                        if((long)RDB[rea + REACTION_PTR_TRANSMUXS] > 0)
                        {

                            boolean = 1;

                            memset(print_data, 0, strlen(print_data));

                            break;

                        }

                    }

                }

                rea = NextItem(rea);

            }

            break;

        }

        mat_iso = NextItem(mat_iso);

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
