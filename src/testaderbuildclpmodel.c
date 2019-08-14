/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderbuildclpmodel.c                        */
/*                                                                           */
/* Created:       2016/04/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the creation of the clp model, stored in arrays        */
/*              provided by ADERAllocateClpMemory                            */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERBuildClpModel:"

void TESTADERBuildClpModel(long step)
{

    char *const test_name = "ADERBuildClpModel";
    char status[5];
    char print_data[256];
    char *mat_name;
    double **clp_arrays;
    double *column_lower_bounds, *column_upper_bounds, *index_column_starts;
    double *objective_row, *row_lower_bounds, *row_indices, *row_upper_bounds;
    double *values;
    int append = 0;
    int boolean = 0, boolean_clb = 0, boolean_cub = 0, boolean_ics = 0;
    int boolean_or = 0, boolean_rlb = 0, boolean_ri = 0, boolean_rub = 0;
    int boolean_v = 0;
    long ader_data, ader_mat_iso, ader_mat_matrix_data, ader_mat_stream;
	long ader_test_block;
    long beryllium_stream_col_id, flibefuel_u233_row_id, mat, mat_ader_data;
    long mat_iso, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERBuildClpModel.\n");

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

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    clp_arrays = ADERAllocateClpMemory(ader_mat_matrix_data);

    /* Get the array pointers given by ADERAllocateClpMemory                  */

    column_lower_bounds = clp_arrays[0];

    column_upper_bounds = clp_arrays[1];

    index_column_starts = clp_arrays[2];

    objective_row = clp_arrays[3];

    row_lower_bounds = clp_arrays[4];

    row_indices = clp_arrays[5];

    row_upper_bounds = clp_arrays[6];

    /* the solution array isn't needed so don't get it                        */

    values = clp_arrays[8];

    /* Pass these arrays to build for value filling                           */

    ADERBuildClpModel(ader_mat_matrix_data, column_lower_bounds,
    		          column_upper_bounds, index_column_starts,
					  objective_row, row_lower_bounds,
					  row_indices, row_upper_bounds, values);

    /* Fist test the column_lower_bounds                                      */

    if(column_lower_bounds[0] < 0.2000001 &&
       column_lower_bounds[0] > 0.1999999)
    {

    	boolean_clb = 1;

    }

    /* Fist test the column_upper_bounds                                      */

    if(column_upper_bounds[0] < 1.0000001 &&
       column_upper_bounds[0] > 0.9999999)
    {

    	boolean_cub = 1;

    }

    /* Test index_column_starts                                               */

    if((long)index_column_starts[1] == 11)
    {

    	boolean_ics = 1;

    }

    /* Test objective row                                                     */

    /* Get Beryllium redox stream column id                                   */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Beryllium", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		beryllium_stream_col_id = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID];

    		break;

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if((long)objective_row[beryllium_stream_col_id] == 1)
    {

    	boolean_or = 1;

    }

    /* Test row_lower_bound                                                   */

    /* Get U-233 iso bal row                                                  */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
    	{

    		flibefuel_u233_row_id = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID];

    		break;

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* This number coming from the amount of U233 in FLiBeFuel should decrease*/

    if(row_lower_bounds[flibefuel_u233_row_id] < 0.000137 &&
       row_lower_bounds[flibefuel_u233_row_id] > 0.000135)
    {

    	boolean_rlb = 1;

    }

    /* Test row_indices, first value should be zero for ActF rto row with     */
    /* FLiBe group in FLiBeFuel                                               */

    if((long)row_indices[0] == 0)
    {

    	boolean_ri = 1;

    }

    /* Test row_upper_bounds                                                  */

    if(row_upper_bounds[flibefuel_u233_row_id] < 0.000137 &&
       row_upper_bounds[flibefuel_u233_row_id] > 0.000135)
    {

    	boolean_rub = 1;

    }

    /* Test values                                                            */

    if(values[0] < -0.999999 &&
       values[0] > -1.000001)
    {

    	boolean_v = 1;

    }

    /* Deallocate the memory, it isn't needed anymore                         */

    ADERDeallocateTarget(clp_arrays, 9);

    if(boolean_clb == 1 &&
       boolean_cub == 1 &&
	   boolean_ics == 1 &&
       boolean_or ==  1 &&
	   boolean_rlb == 1 &&
	   boolean_ri ==  1 &&
	   boolean_rub == 1 &&
	   boolean_v ==   1)
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

        sprintf(print_data, "See following data for a breakdown of sub unit tests.\n");

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

        if(boolean_clb == 0)
        {

        	sprintf(print_data, "Test: column_lower_bound: FAIL - First value has as value %f\n \
but needs value 0.2.\n",
        			column_lower_bounds[0]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: column_lower_bound: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_cub == 0)
        {

        	sprintf(print_data, "Test: column_upper_bound: FAIL - First value has value %f\n \
but needs value 1.0.\n",
        			column_upper_bounds[0]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: column_upper_bound: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    	if(boolean_ics == 0)
    	{

        	sprintf(print_data, "Test: index_column_starts: FAIL - Second value has value %f\n \
but needs value 11.\n",
        			index_column_starts[1]);

        	PrintTest(test_name, status, print_data, 1);

    	}
        else
        {

        	sprintf(print_data, "Test: index_column_starts: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_or == 0)
        {

        	sprintf(print_data, "Test: objective_row : FAIL - Index %ld has value %f but needs value 1.\n",
        			beryllium_stream_col_id, objective_row[beryllium_stream_col_id]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: objective_row: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    	if(boolean_rlb == 0)
    	{

        	sprintf(print_data, "Test: row_lower_bounds : FAIL - Index %ld has value %f\n \
but needs value 0.0085033.\n",
        			flibefuel_u233_row_id,
					row_lower_bounds[flibefuel_u233_row_id]);

        	PrintTest(test_name, status, print_data, 1);

    	}
        else
        {

        	sprintf(print_data, "Test: row_lower_bounds: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    	if(boolean_ri == 0)
    	{

        	sprintf(print_data, "Test: row_indices: FAIL - First value has value %f but needs value 0.\n",
        			row_indices[0]);

        	PrintTest(test_name, status, print_data, 1);

    	}
        else
        {

        	sprintf(print_data, "Test: row_indices: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    	if(boolean_rub == 0)
    	{

        	sprintf(print_data, "Test: row_upper_bounds : FAIL - Index %ld has value %f\n \
but needs value 0.0085033.\n",
        			flibefuel_u233_row_id,
					row_upper_bounds[flibefuel_u233_row_id]);

        	PrintTest(test_name, status, print_data, 1);

    	}
        else
        {

        	sprintf(print_data, "Test: row_upper_bounds: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_v == 0)
        {

        	sprintf(print_data, "Test: values : FAIL - First entry has value %f\n \
but needs value 1.\n",
        			values[0]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: values: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
