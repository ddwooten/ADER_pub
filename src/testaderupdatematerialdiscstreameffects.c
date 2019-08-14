/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderupdatematerialdiscstreameffects.c      */
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests four things: material compositions are updated with    */
/*              disc stream effects and that material density is updated     */
/*              The same is tested for rem table disc type streams           */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERUpdateMaterialDiscStreamEffects:"

void TESTADERUpdateMaterialDiscStreamEffects(long step)
{

    char *const test_name = "ADERUpdateMaterialDiscStreamEffects";
    char status[5];
    char print_data[256];
    char *mat_name;
    double f19_adens, fluorine0_adens;
    double fluorine0_adens_old, fluorine1_adens, lithium7_adens;
    double lithium7_adens_old, percent_diff_f19;
    double percent_diff_fluorine_adens, percent_diff_lithium7_adens;
    double percent_diff_u233, target_value_f19, target_value_fluorine0_adens;
    double target_value_lithium7_adens, target_value_u233, uranium233_adens;
    double u233_adens;
    int append = 0;
    int boolean = 0, boolean_den_lithium7 = 0, boolean_f19 = 0;
    int boolean_den_fluorine0 = 0, boolean_u233 = 0;
    long ader_data;
    long ader_mat_iso, ader_mat_stream;
    long ader_test_block, mat, mat_ader_data, mat_iso, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERUpdateMaterialDiscStreamEffects.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Uranium233 not found. \n");

    /* Get the first test mat */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Uranium233", mat_name, 10) == 0)
        {

            sprintf(print_data, "Material Fluorine0 not found.\n");

            break;

        }

        mat = NextItem(mat);

    }

    uranium233_adens = RDB[mat + MATERIAL_ADENS];

    target_value_u233 = uranium233_adens * 0.1;

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine0", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material Fluorine0 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* First grab the old adens before the update                             */

    fluorine0_adens_old = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	sprintf(print_data, "Material Fluorine0 has redox streams but no U233 stream. \n");

        if(strncmp("U233", GetText(ader_mat_stream + ADER_MAT_STREAM_ID), 4) == 0)
        {

        	sprintf(print_data, "Material Fluorine0 has no ader isotopes. \n");

        	WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.1;

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Call the function to test                                              */

    ADERUpdateMaterialDiscStreamEffects(0, 0, mat);

    fluorine0_adens = RDB[mat + MATERIAL_ADENS];

    target_value_fluorine0_adens = fluorine0_adens_old + uranium233_adens * 0.1;

    percent_diff_fluorine_adens = (fluorine0_adens - target_value_fluorine0_adens) / target_value_fluorine0_adens;

    if(fabs(percent_diff_fluorine_adens) < 0.00001)
    {

    	boolean_den_fluorine0 = 1;

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Fluorine0 has ader isotopes but no U-233. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

        	sprintf(print_data, "Material Fluorine1 not found. \n");

        	u233_adens = RDB[mat_iso + COMPOSITION_ADENS];

            percent_diff_u233 = (u233_adens - target_value_u233) / target_value_u233;

            if(fabs(percent_diff_u233) < 0.00001)
            {

            	boolean_u233 = 1;

            }

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* Now test that removal table streams which are disc in form are handeld */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine1", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material Lithium7 not found.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    fluorine1_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    /* The 0.5 is a volume correction factor                                  */

    target_value_f19 = fluorine1_adens * 0.00001 * 864000 * 0.5;

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            sprintf(print_data, "Material Lithium7 has no isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    lithium7_adens_old = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    /* Call the function to test                                              */

    ADERUpdateMaterialDiscStreamEffects(0, 0, mat);

    lithium7_adens = RDB[mat + MATERIAL_ADENS];

    target_value_lithium7_adens = lithium7_adens_old + target_value_f19;

    percent_diff_lithium7_adens = (lithium7_adens - target_value_lithium7_adens) / target_value_lithium7_adens;

    if(fabs(percent_diff_lithium7_adens) < 0.001)
    {

    	boolean_den_lithium7 = 1;

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Lithium7 has ader isotopes but no F-19. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 90190)
        {

        	sprintf(print_data, "Material Lithium7 has F-19. \n");

        	f19_adens = RDB[mat_iso + COMPOSITION_ADENS];

            percent_diff_f19 = (f19_adens - target_value_f19) / target_value_f19;

            if(fabs(percent_diff_f19) < 0.001)
            {

            	boolean_f19 = 1;

            }

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(boolean_den_fluorine0 == 1 &&
       boolean_u233 == 1 &&
	   boolean_den_lithium7 == 1 &&
	   boolean_f19 == 1)
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

        if(boolean_f19 == 0)
        {

            sprintf(print_data, "Test: F-19 isotopic adens update: FAIL:\n \
F-19 in Lithium7 has adens %f and needs adens %f.\n",
                    f19_adens, target_value_f19);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: F-19 isotopic adens update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_den_fluorine0 == 0)
        {

            sprintf(print_data, "Test: Density group type update: FAIL:\n \
Fluorine0 has density %f and needs density %f.\n", fluorine0_adens,
                    target_value_fluorine0_adens);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Density group type update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_den_lithium7 == 0)
        {

            sprintf(print_data, "Test: Density rem type update: FAIL:\n \
Lithium7 has density %f and needs density %f.\n", lithium7_adens,
                    target_value_lithium7_adens);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Density rem type update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_u233 == 0)
        {

            sprintf(print_data, "Test: U-233 isotopic adens update: FAIL:\n \
U-233 in Fluorine0 has adens %f and needs adens %f.\n",
                    u233_adens, target_value_u233);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: U-233 isotopic adens update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
