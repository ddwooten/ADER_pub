/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermapdensityvector.c                     */
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests 5 things: 1) That the composition vector is given the  */
/*              correct isotopic densities in the "send" mode. 2) That the   */
/*              material receives the correct isotopic density from the      */
/*              composition vector in "receive" mode. 3) That a continuous   */
/*              ( cont ) stream sends the proper amount                      */
/*              into the composition vector. 4) That a prop type stream      */
/*              receives the correct amount in receive mode.                 */
/*              mode. 5) that 3 happens for sum streams                      */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMapDensityVector:"

void TESTADERMapDensityVector()
{

    char *const test_name = "ADERMapDensityVector";
    char status[5];
    char print_data[256];
    char *mat_name;
    double percent_diff_cont_rem_table_send;
    double percent_diff_li7_receive, percent_diff_li7_send;
    double percent_diff_prop_receive, percent_diff_stream_send;
    double percent_diff_stream_sum_send;
    double test_value_prop_receive = 0.0;
    double target_value_cont_rem_table_send;
    double target_value_li7_receive, target_value_li7_send;
    double target_value_prop_receive, target_value_stream_send;
    double target_value_stream_sum_send, total_time;
    double value_cont_rem_table_send, value_li7_receive;
    double value_li7_send, value_stream_send, value_stream_sum_send;
    int append = 0;
    int boolean = 0;
    int boolean_cont_rem_table_send = 0;
    int boolean_li7_receive = 0, boolean_li7_send = 0;
    int boolean_prop_receive = 0, boolean_stream_send = 0;
    int boolean_stream_sum_send = 0;
	double **ader_burn_matrix_size_data;
	double *ader_burn_matrix_N0, *ader_burn_matrix_N_EOS;
	double *ader_burn_matrix_num_rows, *ader_burn_matrix_starts;
	double *initial_state_storage;
    long ader_data;
    long ader_test_block, ader_mat_stream, ader_mat_stream_burn_step;
    long ader_mat_stream_cont_rem, ader_mat_stream_prop;
    long ader_mat_stream_shadow, ader_mat_stream_src_mat;
    long ader_mat_stream_src_mat_ader_data;
    long  ader_mat_stream_sum, ader_mat_stream_sum_ent, cont_stream;
    long cont_stream_sum, mat, mat_ader_data, mat_iso, nuc;
    long li7_index = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERMapDensityVector.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the total burn time                                                */

    total_time = RDB[DATA_BURN_TIME_INTERVAL];

    /* Get the first test mat */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Get the burn matrix size data                                          */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_N_EOS = ader_burn_matrix_size_data[4];

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	/* Create a storage vector to save the current state of the material      */
	/* atomic densities and stream values which will be returned to the       */
	/* material at the end of the test                                        */

	initial_state_storage = calloc(*ader_burn_matrix_num_rows, sizeof(double));

	/* Assuming that the map function works, go ahead and graba that data     */

    ADERMapDensityVector(initial_state_storage, ader_burn_matrix_starts, 0, 0,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

	/* Get the Li-7 isotope in FLiBeFuel and store its value for testing      */

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has isotopes but is missing Li-7.\n");

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

    		target_value_li7_send = RDB[mat_iso + COMPOSITION_ADENS];

    		break;

    	}

    	li7_index++;

    	mat_iso = NextItem(mat_iso);

    }

    /* Set the "CUR_AMT" for the Fluorine stream in the Fluorine material     */
    /* which can be accesed from the FLiBeFuel stream                         */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Fluorine redox stream.\n");

        if(strncmp("Fluorine", GetText(ader_mat_stream + ADER_MAT_STREAM_ID), 8) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no ActF2 removal stream.\n");

            cont_stream = ader_mat_stream;

            ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

            /* REMEMBER ADERMapDensityVector uses pre-step adens              */

            ader_mat_stream_src_mat_ader_data = (long)RDB[ader_mat_stream_src_mat + MATERIAL_ADER_DATA];

            target_value_stream_send = 0.3 * RDB[ader_mat_stream_src_mat_ader_data + ADER_MAT_PRE_STEP_ADENS] / total_time;

            WDB[ader_mat_stream_shadow + ADER_MAT_STREAM_CUR_AMT] = 0.3;

            break;
        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Set the "CUR_AMT" for the Uranium2 sum stream in the ActF2 stream in   */
    /* FLiBeFuel, also grab the rem type prop form stream reproc              */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no ActF2 or reproc remv stream.\n");

        if(strcmp("reproc", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

        	ader_mat_stream_prop = ader_mat_stream;

            sprintf(print_data, "FLiBeFuel has no ActF2 stream.\n");

        }

        if(strcmp("ActF2", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ActF2 remv stream but no sum streams.\n");

            ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_stream_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel ActF2 remv stream has sum streams but no Uranium2.\n");

                if(strcmp("Uranium2", GetText(ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                	ader_mat_stream_sum = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                	cont_stream_sum = ader_mat_stream_sum;

                	target_value_stream_sum_send = 0.5 * RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS] / total_time;

                	WDB[ader_mat_stream_sum + ADER_MAT_STREAM_CUR_AMT] = 0.5;

                    break;

                }

                ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

            }

            break;
        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Now call the map function in the send mode                             */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

    /* Test the N0 received the correct Li7 value                             */

    value_li7_send = ader_burn_matrix_N0[li7_index];

    percent_diff_li7_send = (value_li7_send -
    		                 target_value_li7_send) / target_value_li7_send;

    if(fabs(percent_diff_li7_send) < 0.0001)
    {

    	boolean_li7_send = 1;

    }

    /* Test to see if the  stream sent the correct amount                     */

    value_stream_send = ader_burn_matrix_N0[(long)RDB[cont_stream + ADER_MAT_STREAM_BURN_INDEX]];

    percent_diff_stream_send = (value_stream_send -
    		                    target_value_stream_send) / target_value_stream_send;

    if(fabs(percent_diff_stream_send) < 0.001)
    {

    	boolean_stream_send = 1;

    }

    /* Now test to see if the sum stream sent the correct amount              */

    value_stream_sum_send = ader_burn_matrix_N0[(long)RDB[cont_stream_sum + ADER_MAT_STREAM_BURN_INDEX]];

    percent_diff_stream_sum_send = (value_stream_sum_send -
    		                    target_value_stream_sum_send) / target_value_stream_sum_send;

    if(fabs(percent_diff_stream_sum_send) < 0.001)
    {

    	boolean_stream_sum_send = 1;

    }


    /* Assign a value in the burn vector for Li-7 and the prop stream         */

    target_value_prop_receive = 0.7;

    target_value_li7_receive = 0.17;

    ader_burn_matrix_N_EOS[(long)RDB[ader_mat_stream_prop + ADER_MAT_STREAM_BURN_INDEX]] = 0.7;

    ader_burn_matrix_N_EOS[li7_index] = target_value_li7_receive;

    /* Now call the map function in the receive mode                          */

    ADERMapDensityVector(ader_burn_matrix_N_EOS, ader_burn_matrix_starts, 0, 1,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

    /*Now, check that the prop stream received the correct amount             */
    /* We will need to retrieve its burn step value to do so                  */

    ader_mat_stream_burn_step = (long)RDB[ader_mat_stream_prop + ADER_MAT_STREAM_BURN_STEPS_PTR];

    test_value_prop_receive = RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE];

    percent_diff_prop_receive = (test_value_prop_receive -
    		                     target_value_prop_receive) /
    		                     target_value_prop_receive;

    if(fabs(percent_diff_prop_receive) < 0.0001)
    {

    	boolean_prop_receive = 1;

    }

    /* Now, cycle through to Li-7 in FLiBeFuel and check its value. Also,     */
    /* reset the old value                                                    */

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has isotopes but is missing Li-7.\n");

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

            sprintf(print_data, "This test failed. See details below.\n");

            value_li7_receive = RDB[mat_iso + COMPOSITION_ADENS];

            percent_diff_li7_receive = (value_li7_receive -
            		                   target_value_li7_receive) /
            		                  target_value_li7_receive;

            WDB[mat_iso + COMPOSITION_ADENS] = target_value_li7_send;

    		break;

    	}

    	mat_iso = NextItem(mat_iso);

    }

    if(fabs(percent_diff_li7_receive) < 0.0001)
    {

    	boolean_li7_receive = 1;

    }

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

	/* reset the mat's data                                                   */

    ADERMapDensityVector(initial_state_storage, ader_burn_matrix_starts, 0, 1,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

	/* Now, repeat the send procedure for the Lithium7 material cluster so    */
	/* that we an test a continuous removal based table                       */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strcmp("Lithium7", mat_name) == 0)
        {

            sprintf(print_data, "Material Lithium7 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Get the burn matrix size data                                          */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_N_EOS = ader_burn_matrix_size_data[4];

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	/* Get the rLi7 removal stream                                            */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Lithium7 has no rLi7 remv stream.\n");

        if(strcmp("rLi7", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

        	ader_mat_stream_cont_rem = ader_mat_stream;

            sprintf(print_data, "FLiBeFuel has no ActF2 stream.\n");

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    target_value_cont_rem_table_send = 0.1;

    /* Now call the map function in the send mode                            */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

    /* Now test that the value was sent                                       */

    value_cont_rem_table_send = ader_burn_matrix_N0[(long)RDB[ader_mat_stream_cont_rem + ADER_MAT_STREAM_BURN_INDEX]];

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

	percent_diff_cont_rem_table_send = (value_cont_rem_table_send - target_value_cont_rem_table_send) /
			                           target_value_cont_rem_table_send;

    if(fabs(percent_diff_cont_rem_table_send) < 0.001)
    {

    	boolean_cont_rem_table_send = 1;

    }

    if(boolean_li7_receive == 1 &&
       boolean_li7_send == 1 &&
	   boolean_prop_receive == 1 &&
	   boolean_stream_send == 1 &&
	   boolean_stream_sum_send == 1 &&
	   boolean_cont_rem_table_send == 1)
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

        if(boolean_li7_receive == 0)
        {

            sprintf(print_data, "Test: Isotope fraction send: FAIL:\n \
Li-7 isotope in FLiBeFuel has value %f but N0 vector, at index %ld has \n\
value %f.\n", target_value_li7_send, li7_index, value_li7_send);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Isotope fraction send: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_li7_send == 0)
        {

            sprintf(print_data, "Test: Isotope fraction receive: FAIL:\n \
Li-7 isotope in FLiBeFuel received value %f but needed value %f.\n",
                    value_li7_receive, target_value_li7_receive);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Isotope fraction receive: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_prop_receive == 0)
        {

            sprintf(print_data, "Test: Prop stream receive: FAIL:\n \
Removal stream reproc in FLiBeFuel received value %f but needed value %f.\n",
                   test_value_prop_receive,
				   target_value_prop_receive);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Prop stream receive: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream_send == 0)
        {

            sprintf(print_data, "Test: Cont stream send: FAIL:\n \
Redox stream Fluorine in Fluorine0 sent value\n\
%1.16E but N0 vector has value\n\
%1.16E.\n",
                   target_value_stream_send, value_stream_send);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Cont stream send: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream_sum_send == 0)
        {

            sprintf(print_data, "Test: Cont sum stream send: FAIL:\n \
Removal sum stream Uranium2 in stream ActF2 in FLiBeFuel sent value\n\
%1.16E but N0 vector has value\n\
%1.16E.\n",
                   target_value_stream_sum_send, value_stream_sum_send);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Cont sum stream send: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_cont_rem_table_send == 0)
        {

            sprintf(print_data, "Test: Continuous removal table value send: FAIL:\n \
rLi7 stream in material Lithium7 sent value %1.8E to the burn vector\n\
at index %ld but should have sent %1.8E.\n", value_cont_rem_table_send,
                    (long)RDB[ader_mat_stream_cont_rem + ADER_MAT_STREAM_BURN_INDEX],
					target_value_cont_rem_table_send);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Continuous removal table value send: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

    /* Now reset the material's state                                         */

    ADERMapDensityVector(initial_state_storage, ader_burn_matrix_starts, 0, 1,
    		             mat, 1, RDB[DATA_BURN_TIME_INTERVAL]);

    /* Now free the storage vector                                            */

    free(initial_state_storage);

}
