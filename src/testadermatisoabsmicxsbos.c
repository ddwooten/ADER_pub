/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatisoabsmicxsbos.c                    */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that an isotopes micro absorption cross               */
/*              section is calculated correctly                              */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatIsoAbsMicXsBos:"

void TESTADERMatIsoAbsMicXsBos(long step)
{

    char *const test_name = "ADERMatIsoAbsMicXsBos";
    char status[5];
    char print_data[256];
    char *mat_name;
    double percent_diff;
    double total_abs_xs = 0.0;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, id, mat, mat_ader_data, mat_ader_iso;
    long mat_iso, nuc, rea;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatIsoAbsMicXsBos.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get OMP_ID, this will only work on non OMP runs...I think              */

    id = OMP_THREAD_NUM;

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

    /* Calculate transmutation cross sections */

    CalculateTransmuXS(mat, OMP_THREAD_NUM);

    /* Store the xs from above */

    StoreTransmuXS(mat, step, 3, OMP_THREAD_NUM, 0);

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_ader_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader isotopes but no U-233.\n");

        mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

        	/* Get the total abs xs as calcuated by SERPENT                   */

        	rea = (long)RDB[nuc + NUCLIDE_PTR_REA];

        	while(rea > VALID_PTR)
        	{

        		/* This establishes that the reaction is not fission and is   */
        		/* not decay                                                  */

        		if((long)RDB[rea + REACTION_PTR_TRANSMUXS] > VALID_PTR)
        		{

        			total_abs_xs += TestValuePair(rea + REACTION_PTR_TRANSMUXS,
        					                      mat, id);
        		}

        		rea = NextItem(rea);

        	}

        	percent_diff = ((RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS] -
        			         total_abs_xs) / total_abs_xs) * 100.0;

            sprintf(print_data, "Material FLiBeFuel has U-233 but the \n \
ADER_MAT_ISO_ABS_MIC_XS_BOS has bad value of %f.\n \
Has percent difference with possible SERPENT XS of: %f \n \
Needs value of UNKNOWN.\n",
                    RDB[mat_ader_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
					percent_diff);

            if(fabs(percent_diff) < 0.001)
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
