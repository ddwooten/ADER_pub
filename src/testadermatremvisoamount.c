/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatremvisoamount.c                     */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the calculated amount of isotopic      */
/*              removal is correct for all three scenarios                   */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatRemvIsoAmount:"

void TESTADERMatRemvIsoAmount(long step)
{

    char *const test_name = "ADERMatRemvIsoAmount";
    char status[5];
    char print_data[256];
    char *mat_name, *strm_id;
    double argon40_adens, f19_target_value, flibefuel_adens, fluorine1_adens;
    double lithium7_adens, percent_diff_cont, percent_diff_disc;
    double percent_diff_prop, test_value_cont, test_value_disc, test_value_prop;
    double u233_target_value;
    int append = 0;
    int boolean = 0, boolean_disc = 0, boolean_cont = 0, boolean_prop = 0;
    long ader_data, ader_test_block, mat, mat_ader_data, strm, strm_iso;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatRemvIsoAmount.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams. \n");

            break;

        }

        mat = NextItem(mat);
    }

    flibefuel_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc2", strm_id, 7) == 0)
        {

            sprintf(print_data, "'reproc2' stream in FLiBeFuel has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                sprintf(print_data, "'reproc2' stream in FLiBeFuel has no F-19.\n");

                if((long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI] == 90190)
                {

                    sprintf(print_data, "'reproc2' stream in FLiBeFuel has F-19 but\n \
material Fluorine1 not found.\n");

                    test_value_cont = RDB[strm_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

                    percent_diff_cont = (test_value_cont - (0.0000030229 * 864000)) / (0.0000030229 * 864000);

                    if(fabs(percent_diff_cont) < 0.001)
                    {

                        boolean_cont = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine1", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material Lithium7 has no streams. \n");

            break;

        }

        mat = NextItem(mat);
    }

    fluorine1_adens = RDB[mat + MATERIAL_ADENS];

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            sprintf(print_data, "Material Lithium7 has no streams. \n");

            break;

        }

        mat = NextItem(mat);
    }

    lithium7_adens = RDB[mat + MATERIAL_ADENS];

    /* The 0.5 is for the volume correction factor                            */

    f19_target_value = (fluorine1_adens / lithium7_adens) * 0.00001 * 864000 * 0.5;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc3", strm_id, 7) == 0)
        {

            sprintf(print_data, "'reproc3' stream in Lithium7 has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                sprintf(print_data, "'reproc3' stream in Lithium7 has no F-19.\n");

                if((long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI] == 90190)
                {

                    sprintf(print_data, "'reproc3' stream in Lithium7 has F-19 but\n \
material Argone40 not found.\n");

                    test_value_disc = RDB[strm_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

                    percent_diff_disc = (test_value_disc -
                    		        f19_target_value) / f19_target_value;

                    if(fabs(percent_diff_disc) < 0.001)
                    {

                        boolean_disc = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);

    }

    /* Get Argon40 */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    argon40_adens = RDB[mat + MATERIAL_ADENS];

    /* The 2.0 is for volume effects                                          */

    u233_target_value = 0.00418358 * (flibefuel_adens / argon40_adens) * 2.0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in Argon40 has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                sprintf(print_data, "'reproc' stream in Argon40 has no U-233.\n");

                if((long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI] == 922330)
                {

                    sprintf(print_data, "'reproc' stream in Argon40 has U-233 but\n \
bad iso removal of %f and needs iso rate of %f.\n",
                            RDB[strm_iso + ADER_MAT_GRP_ISO_ELE_FRAC],
							u233_target_value);

                    test_value_prop = RDB[strm_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

                    percent_diff_prop = (test_value_prop -
                    		        u233_target_value) / u233_target_value;

                    if(fabs(percent_diff_prop) < 0.0001)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean_prop = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);

    }

    if(boolean_cont == 1 &&
       boolean_disc == 1 &&
	   boolean_prop == 1)
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

        if(boolean_cont == 0)
        {

            sprintf(print_data, "Test: Continuous removal: FAIL:\n \
FLiBeFuel remv stream reproc2 F-19 isotope has bad removal amount %f but \n \
needs removal rate %f.\n", test_value_cont, 0.0000030229);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Continuous removal: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_disc == 0)
        {

            sprintf(print_data, "Test: Discreet removal: FAIL:\n \
Fluorine1 remv stream reproc3 F-19 isotope has bad removal amount %f but \n \
needs removal rate %f.\n", test_value_disc, f19_target_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Discreet removal: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_prop == 0)
        {

            sprintf(print_data, "Test: Proportional removal: FAIL:\n \
Argon40 remv stream reproc U-233 isotope has bad removal amount of %f but \n \
needs removal rate of %f.\n", test_value_prop, u233_target_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test:Proportional removal: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }


    }

}
