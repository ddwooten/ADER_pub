/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderupdatematerialdiscsumstreameffects.c   */
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests two things: material compositions are updated with     */
/*              disc stream effects and that material density is updated     */
/*              This test is executed on sum streams                         */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERUpdateMaterialDiscSumStreamEffects:"

void TESTADERUpdateMaterialDiscSumStreamEffects(long step)
{

    char *const test_name = "ADERUpdateMaterialDiscSumStreamEffects";
    char status[5];
    char print_data[256];
    char *mat_name;
    double fluorine1_adens;
    double fluorine1_adens_old, percent_diff_fluorine_adens, percent_diff_li6;
    double target_value_fluorine_adens, target_value_li6, lithium7_adens;
    int append = 0;
    int boolean = 0, boolean_den = 0, boolean_li6 = 0;
    long ader_data;
    long ader_mat_iso, ader_mat_stream, ader_mat_sum_stream;
    long ader_mat_sum_stream_ent;
    long ader_test_block, mat, mat_ader_data, mat_iso, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERUpdateMaterialDiscSumStreamEffects.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Lithium7 not found. \n");

    /* Get the first test mat */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            sprintf(print_data, "Material Fluorine1 not found.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    lithium7_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    target_value_li6 = lithium7_adens * 0.1 * 0.45;

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine1", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material Fluorine1 has no ader streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* First grab the old adens before the update                             */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    fluorine1_adens_old = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material Fluorine1 has redox streams but no FreeStreams stream.\n");

        if(strcmp("FreeStreams", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "Material Fluorine1 has FreeStreams stream but no sum streams.\n");

            ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_sum_stream_ent > VALID_PTR)
            {

                sprintf(print_data, "Material Fluorine1 FreeStreams stream has sum streams but no LithiumFree stream.\n");

                if(strcmp("LithiumFree", GetText(ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                    sprintf(print_data, "Material Fluorine1 FreeStreams has LithiumFree stream but has no ader isotopes.\n");

                    ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    WDB[ader_mat_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.1;

                	break;

                }


            	ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);

            }

            break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Call the function to test                                              */

    ADERUpdateMaterialDiscStreamEffects(0, 0, mat);

    fluorine1_adens = RDB[mat + MATERIAL_ADENS];

    target_value_fluorine_adens = fluorine1_adens_old + lithium7_adens * 0.1 -
    		                      (fluorine1_adens_old * 0.5 * 0.00002 * 864000);

    percent_diff_fluorine_adens = (fluorine1_adens - target_value_fluorine_adens) / target_value_fluorine_adens;

    if(fabs(percent_diff_fluorine_adens) < 0.001)
    {

    	boolean_den = 1;

    }

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Fluorine1 has ader isotopes but no Li-6. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

        	sprintf(print_data, "Material Fluorine0 has U-233. \n");

            percent_diff_li6 = (RDB[mat_iso + COMPOSITION_ADENS] - target_value_li6) / target_value_li6;

            if(fabs(percent_diff_li6) < 0.00001)
            {

            	boolean_li6 = 1;

            }

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(boolean_den == 1 &&
       boolean_li6 == 1)
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

        if(boolean_den == 0)
        {

            sprintf(print_data, "Test: Density update: FAIL:\n \
Fluorine1 has density %f and needs density %f.\n", fluorine1_adens,
                    target_value_fluorine_adens);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Density update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_li6 == 0)
        {

            sprintf(print_data, "Test: Li-6 isotopic adens update: FAIL:\n \
Li-6 in Fluorine1 has adens %f and needs adens %f.\n",
                    RDB[mat_iso + COMPOSITION_ADENS], target_value_li6);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Li-6 isotopic adens update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
