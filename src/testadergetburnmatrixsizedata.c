/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadergetburnmatrixsizedata.c                */
/*                                                                           */
/* Created:       2016/21/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests 7 things:                                              */
/*              Tests that ADERGetBurnMatrixNumRows returns the correct      */
/*              number of rows which is the sum total of all isotopes and    */
/*              streams ( not double counting shadows ) in all materials     */
/*              of a cluster. Also tests total array size allocation and     */
/*              the material boundary breaks. This also tests the            */
/*              ADERAllocateBurnMatrixSizeMemory function. Additionally tests*/
/*              that streams ( not disc ) and sum streams ( not disc ) are   */
/*              given proper vector indices. While testing of the stream     */
/*              index assignment could have gone in the count stream test    */
/*              the necessary row information was already going to be in     */
/*              this test so the testing is done here. Additionally tests    */
/*              that ader isotopes are given the proper index and that the   */
/*              correct number of non-zero burn entries is returned          */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERGetBurnMatrixSizeData:"

void TESTADERGetBurnMatrixSizeData(long mat)
{

    char *const test_name = "ADERGetBurnMatrixSizeData";
    char status[5];
    char print_data[256];
    double **ader_burn_matrix_size_info, *ader_burn_matrix_starts;
    double *ader_burn_matrix_num_ents, *ader_burn_matrix_num_rows;
    double *ader_burn_matrix_N0;
    double *ader_burn_matrix_col_storage;
    int append = 0;
    int boolean = 0, boolean_allocation = 0, boolean_iso_index = 0;
    int boolean_non_zero = 0;
    int boolean_starts = 0, boolean_num_rows = 0, boolean_stream_index = 0;
    int boolean_stream_sum_index = 0;
    long ader_data, ader_mat_cluster_ent, ader_mat_cluster_mem;
    long ader_mat_cluster_mem_ader_data, ader_mat_cluster_mem_stream;
    long ader_mat_stream, ader_mat_stream_index, ader_mat_iso;
    long ader_mat_stream_sum, ader_mat_stream_sum_ent, ader_mat_stream_sum_index;
    long ader_test_block, mat_ader_data, mat_iso, nuc;
    long test_value_iso_index, test_value_num_rows, test_value_starts;
    long test_value_stream_index;
    long test_value_stream_sum_index;
    long expected_non_zero_entries = 0, num_isos = 0, num_rows = 0;
    long num_flibefuel_rows = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERGetBurnMatrixSizeData.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel burn matrix has bad matrix gen. \n");

    /* Count the isotopes in all cluster members and the non-zero burn entries*/

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(ader_mat_cluster_ent > VALID_PTR)
    {

    	ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

    	ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

    	/* Also collect the SERPENT number of non-zero entries in a burn matrix*/

    	expected_non_zero_entries += BurnMatrixSize(ader_mat_cluster_mem);

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	if((strncmp("cont",
    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					4) == 0) ||
    	        (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
    		     (strncmp("prop",
    			   	      GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
    			          4) == 0)))
	    	{

	    		expected_non_zero_entries = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
		    			                                        expected_non_zero_entries);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	if((strncmp("cont",
    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					4) == 0) ||
    	        (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
    		     (strncmp("prop",
    			   	      GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
    			          4) == 0)))
	    	{

	    		expected_non_zero_entries = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
		    			                                        expected_non_zero_entries);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	if((strncmp("cont",
    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					4) == 0) ||
    	        (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
    		     (strncmp("prop",
    			   	      GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
    			          4) == 0)))
	    	{

	    		expected_non_zero_entries = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
		    			                                        expected_non_zero_entries);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	if((strncmp("cont",
    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
					4) == 0) ||
    	        (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
    		     (strncmp("prop",
    			   	      GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
    			          4) == 0)))
	    	{

	    		expected_non_zero_entries = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
		    			                                        expected_non_zero_entries);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

    	if(strncmp("FLiBeFuel", GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME), 9) == 0)
    	{

    		num_flibefuel_rows = num_rows;

    	}

    	mat_iso = (long)RDB[ader_mat_cluster_mem + MATERIAL_PTR_COMP];

    	while(mat_iso > VALID_PTR)
    	{

    		num_rows++;

    		mat_iso = NextItem(mat_iso);

    	}

    	if(strncmp("FLiBeFuel", GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME), 9) == 0)
    	{

    		num_flibefuel_rows = num_rows - num_flibefuel_rows;

    		num_isos = num_flibefuel_rows;

    	}

    	ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

    }

    /* The number of streams, as assigned to all members of the FLiBeFuel     */
    /* cluster, minus discreet streams, is 10 including the components of sum */
    /* streams. We add 1 because of 0 indexing                                */

    num_rows = num_rows + 10;

    /* The number of streams, as assigned to FLiBeFuel, minus                 */
    /* discreet streams is 6 including component sum streams                  */

    num_flibefuel_rows = num_flibefuel_rows + 6;

    /* The target index of the Fluorine stream in FLiBeFuel is equal to the   */
    /* number of isotopes x 2 ( the index is assigned when the stream is read */
    /* at its source, in the Fluorine0 material ) + the number of streams in  */
    /* FLiBeFuel ( 6 ) We do not subtract 1 for zero indexing as the way      */
    /* ADERCountStreams assigns indicies                                      */

    test_value_stream_index = num_isos * 2 + 6;

    /* The target index of the Uranium2 stream in the ActF2 stream is equal to*/
    /* the number of isotopes + 5 as it is the 5th stream in FLiBeFuel.       */
    /* -1 for zero indexing                                                   */

    test_value_stream_sum_index = num_isos + 4;

    /* Run the test function and capture its output                           */

    ader_burn_matrix_size_info = ADERGetBurnMatrixSizeData(mat);

    ader_burn_matrix_num_rows = ader_burn_matrix_size_info[0];

    test_value_num_rows = ader_burn_matrix_num_rows[0];

    ader_burn_matrix_num_ents = ader_burn_matrix_size_info[1];

    ader_burn_matrix_starts = ader_burn_matrix_size_info[2];

    test_value_starts = ader_burn_matrix_starts[1];

    ader_burn_matrix_N0 = ader_burn_matrix_size_info[3];

    ader_burn_matrix_col_storage = ader_burn_matrix_size_info[4];

    /* If this does not cause a seg fault then the vector size boolean passes */
    /* We subtract one beacuse we added one to acount for 0 indexing          */

    ader_burn_matrix_N0[num_rows - 1] = 1.0;

    ader_burn_matrix_col_storage[num_rows - 1] = 1.0;

    boolean_allocation = 1;

    if((long)ader_burn_matrix_num_ents[0] == expected_non_zero_entries)
    {

    	boolean_non_zero = 1;

    }

    if(test_value_starts == num_flibefuel_rows)
    {

    	boolean_starts = 1;

    }


    if(test_value_num_rows == num_rows)
    {

    	boolean_num_rows = 1;

    }

    /* Go ahead and free the burn matrix memory                               */

    ADERDeallocateTarget(ader_burn_matrix_size_info, 5);

    /* Loop through FLiBeFuel's ader isotopes to see if Li-7 got the correct  */
    /* index                                                                  */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
        {

            test_value_iso_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

            if(test_value_iso_index == 8)
            {

                boolean_iso_index = 1;

            }

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    sprintf(print_data, "FLiBeFuel burn matrix has no streams. \n");

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Fluorine redox stream.\n");

        if(strncmp("Fluorine", GetText(ader_mat_stream + ADER_MAT_STREAM_ID), 8) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no ActF2 removal stream.\n");

            ader_mat_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

            if(test_value_stream_index == ader_mat_stream_index)
            {

            	boolean_stream_index = 1;

            	break;

            }

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Test the sum streams                                                   */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no ActF2 remv stream.\n");

        if(strncmp("ActF2", GetText(ader_mat_stream + ADER_MAT_STREAM_ID), 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ActF2 remv stream but no sum streams.\n");

            ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_stream_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel ActF2 remv stream has sum streams but no Uranium2.\n");

                if(strncmp("Uranium2", GetText(ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_ID), 8) == 0)
                {

                	ader_mat_stream_sum = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                	ader_mat_stream_sum_index = (long)RDB[ader_mat_stream_sum + ADER_MAT_STREAM_BURN_INDEX];

                	if(test_value_stream_sum_index == ader_mat_stream_sum_index)
                	{

                		boolean_stream_sum_index = 1;

                	}

                    break;

                }

                ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

            }

            break;
        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(boolean_allocation == 1 &&
       boolean_iso_index == 1 &&
       boolean_num_rows == 1 &&
	   boolean_non_zero == 1 &&
       boolean_starts == 1 &&
	   boolean_stream_index == 1 &&
	   boolean_stream_sum_index == 1)
    {

        boolean = 1;

    }

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        memset(print_data, 0, strlen(print_data));

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

        /* We do not report out the allocation boolean because the program    */
        /* seg fault if that boolean would not pass                           */

        if(boolean_iso_index == 0)
        {

            sprintf(print_data, "Test: Iso index: FAIL:\n \
Li-7 isotope in FLiBeFuel has index %ld and needs index 8.\n",
                    test_value_iso_index);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "Test: Iso index: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_non_zero == 0)
        {

            sprintf(print_data, "Test: Number non-zero entries: FAIL:\n \
There should be %ld non-zero entries and there are %ld non-zero entries.\n",
                    expected_non_zero_entries,
					(long)ader_burn_matrix_num_ents[0]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Number non-zero entries: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_num_rows == 0)
        {

            sprintf(print_data, "Test: Burn matrix num rows: FAIL:\n \
Burnmatrix has rows %ld but should have rows %ld.\n", test_value_num_rows,
                    num_rows);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "Test: Burn matrix num rows: PASS\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_starts == 0)
        {

            sprintf(print_data, "Test: Burn matrix starts: FAIL:\n \
Fluorine0 start is reported as %ld but should be %ld.\n \
Following starts are [ %ld, %ld ].\n", test_value_starts,
                    num_flibefuel_rows, (long)ader_burn_matrix_starts[2],
					(long)ader_burn_matrix_starts[3]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Burn matrix starts: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream_index == 0)
        {

            sprintf(print_data, "Test: Stream index: FAIL:\n \
Redox stream Fluorine in FLiBeFuel has index %ld and needs index %ld.\n",
                    ader_mat_stream_index, test_value_stream_index);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Stream index: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_stream_sum_index == 0)
        {

            sprintf(print_data, "Test: Sum stream index: FAIL:\n \
Removal stream Uranium2 ( sum of ActF2 ) in FLiBeFuel has index %ld \n\
and needs index %ld.\n",
                    ader_mat_stream_sum_index, test_value_stream_sum_index);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Sum stream index: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
