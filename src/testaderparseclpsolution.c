/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderparseclpsolution.c                     */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that the components of the clp solution are properly   */
/*              assinged to composition groups and streams as well as to     */
/*              their respective burn step trackers                          */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERParseClpSolution:"

void TESTADERParseClpSolution(double *solution, long step)
{

    char *const test_name = "ADERParseClpSolution";
    char status[5];
    char print_data[256];
    char *mat_name;
    double argon40_density = 0.0, flibefuel_density = 0.0;
    double pass_value_stream_burn_step = 0.0, pass_value_stream_cur_amt = 0.0;
    double percent_diff_stream_burn_step = 0.0, percent_diff_stream_cur_amt = 0.0;
    double test_value_stream_burn_step = 0.0, test_value_stream_cur_amt = 0.0;
    int append = 0;
    int boolean = 0, boolean_cmp = 0, boolean_cmp_burn = 0, boolean_stream = 0;
    int boolean_stream_burn = 0;
    long ader_data, ader_mat_cmp, ader_mat_cmp_burn_step, ader_mat_cmp_col_id;
    long ader_mat_stream, ader_mat_stream_burn_step, ader_mat_stream_col_id;
    long ader_mat_sum_stream;
    long ader_mat_sum_stream_ent, ader_test_block, argon40, mat, mat_ader_data;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERParseClpSolution.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    argon40 = mat;

    argon40_density = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has feed streams but no ActF stream.\n");

        if(strcmp("ActF", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "Material Argon40 has feed stream ActF but no sum streams.\n");

            ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_sum_stream_ent > VALID_PTR)
            {

                sprintf(print_data, "Material Argon40 feed stream ActF has sum streams but no Uranium sum stream.\n");

                if(strcmp("Uranium", GetText(ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                    sprintf(print_data, "Material FLiBeFuel not found. \n");

                    ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    ader_mat_stream_col_id = (long)RDB[ader_mat_sum_stream + ADER_MAT_STREAM_COL_ID];

                	break;

                }

            	ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);
            }

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no cmp groups.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    flibefuel_density = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    ader_mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(ader_mat_cmp > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has cmp groups but no FLiBe.\n");

        if(strcmp("FLiBe", GetText(ader_mat_cmp + ADER_MAT_CMP_ID)) == 0)
        {

        	ader_mat_cmp_col_id = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID];

        	break;

        }

    	ader_mat_cmp = NextItem(ader_mat_cmp);

    }

    /* Now that we have the column indices we need, modify the solution array */

    solution[ader_mat_cmp_col_id] = 0.3;

    solution[ader_mat_stream_col_id] = 0.1;

    pass_value_stream_cur_amt = 0.1 *
    		                   (RDB[mat + MATERIAL_VOLUME] /
    		                    RDB[argon40 + MATERIAL_VOLUME]);

    pass_value_stream_burn_step = 0.1 * flibefuel_density *
                                  (RDB[mat + MATERIAL_VOLUME] /
                                   RDB[argon40 + MATERIAL_VOLUME]);
;

    /* Now, run the function and test if it assigns new values                */

    ADERParseClpSolution(0, 0, mat, step, solution);

    if(RDB[ader_mat_cmp + ADER_MAT_CMP_CUR_AMT] < 0.300001 &&
       RDB[ader_mat_cmp + ADER_MAT_CMP_CUR_AMT] > 0.299999)
    {

    	boolean_cmp = 1;

    }

    test_value_stream_cur_amt = RDB[ader_mat_sum_stream + ADER_MAT_STREAM_CUR_AMT];

    percent_diff_stream_cur_amt = (test_value_stream_cur_amt -
    		                       pass_value_stream_cur_amt) /
    		                      test_value_stream_cur_amt;

    if(fabs(percent_diff_stream_cur_amt) < 0.001)
    {

    	boolean_stream = 1;

    }

    /* Now retrieve the burn step information, there is only one burn step so */
    /* no looping to the answer is needed                                     */

    ader_mat_cmp_burn_step = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_BURN_STEPS_PTR];

    if(RDB[ader_mat_cmp_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] < 0.300001 &&
       RDB[ader_mat_cmp_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE] > 0.299999)
    {

    	boolean_cmp_burn = 1;

    }

    ader_mat_stream_burn_step = (long)RDB[ader_mat_sum_stream + ADER_MAT_STREAM_BURN_STEPS_PTR];

    test_value_stream_burn_step = RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];

    percent_diff_stream_burn_step = (test_value_stream_burn_step -
    		                         pass_value_stream_burn_step ) /
    		                         pass_value_stream_burn_step;

    if(fabs(percent_diff_stream_burn_step) < 0.001)
    {

    	boolean_stream_burn = 1;

    }

    if(boolean_cmp == 1 &&
       boolean_cmp_burn == 1 &&
       boolean_stream == 1 &&
	   boolean_stream_burn == 1)
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

        if(boolean_cmp == 0)
        {

        	sprintf(print_data, "Test: cmp group: FAIL - Index %ld has as value %f\n \
but ADER_MAT_CMP_CUR_AMT, with value %f, needs value 0.3.\n",
                    ader_mat_cmp_col_id, solution[ader_mat_cmp_col_id],
					RDB[ader_mat_cmp + ADER_MAT_CMP_CUR_AMT]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: cmp group: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_cmp_burn == 0)
        {

        	sprintf(print_data, "Test: cmp group burn step value: FAIL - Index %ld has as value %f\n \
but the burn step value is reported as %f and needs value 0.3.\n",
                    ader_mat_cmp_col_id, solution[ader_mat_cmp_col_id],
					RDB[ader_mat_cmp_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: cmp group burn step value: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream == 0)
        {

        	sprintf(print_data, "Test: stream: FAIL - Index %ld has as value %f\n \
but ADER_MAT_STREAM_CUR_AMT, with value %f, needs value 0.1.\n",
                    ader_mat_stream_col_id, solution[ader_mat_stream_col_id],
					RDB[ader_mat_sum_stream + ADER_MAT_STREAM_CUR_AMT]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: stream group: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream_burn == 0)
        {

        	sprintf(print_data, "Test: stream burn step value: FAIL - Burn step value is reported as %f\n\
  and needs value %f.\n", test_value_stream_burn_step,
                          pass_value_stream_burn_step);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: cmp group burn step value: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

    /* Quickly reset all the streams in this cluster to not complicate testing*/

    solution[ader_mat_cmp_col_id] = 0.0;

    solution[ader_mat_stream_col_id] = 0.0;

    /* Now, run the function and test if it assigns new values                */

    ADERParseClpSolution(0, 0, mat, step, solution);

}
