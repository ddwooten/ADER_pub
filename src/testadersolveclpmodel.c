/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadersolveclpmodel.c                        */
/*                                                                           */
/* Created:       2016/04/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the solution of the clp model                          */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                       ADEROperateMaterialCompMatrix       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERSolveClpModel:"

void TESTADERSolveClpModel(long step)
{

    char *const test_name = "ADERSolveClpModel";
    char status[5];
    char print_data[256];
    int append = 0;
    int boolean = 0, boolean_column = 0, boolean_objective = 0;
    long ader_data, ader_test_block;

    /* Clp data                                                               */

    long num_col = 5;
    long num_ent = 9;
    long num_row = 3;
    double index_column_starts[6] = {0.0, 1.0, 2.0, 3.0, 6.0, 9.0};
    double row_indices[9] = {0.0, 1.0, 2.0, 0.0, 1.0, 2.0, 0.0, 1.0, 2.0};
    double values[9] = {1.0, 1.0, 1.0, -2.0, 1.0, 3.0, 1.0, 4.0, 2.0};
    double column_lower_bounds[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    double column_upper_bounds[5] = {1000000.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0};
    double objective_row[5] = {2.0, -1.0, 1.0, -5.0, 22.0};
    double row_lower_bounds[3] = {6.0, 3.0, 10.0};
    double row_upper_bounds[3] = {6.0, 3.0, 10.0};
    double solution[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

    /* The matrix these vectors define is given below. The bounds on the rows */
    /* are given as the values to the left ( min ) and right ( max ) of the   */
    /* rows of the matrix. The bounds on the columns are given as the numbers */
    /* above and below the matrix ( min on top, max on bottom ). inf = infinity*/
    /* The letters above the columns are the variables those columns represent.*/
    /* The matrix as a whole represents the constrains that the objective     */
    /* function, p, is subject to. The problem is a minimization problem as   */
    /* seen by the value of 1 as the seventh argument to the ADERSolveClpModel*/
    /* function                                                               */

    /*          a   b   c   d   e
     *          0   0   0   0   0
     *        ___               ___
     *      6 | 1   0   0  -2   1 | 6
     *      3 | 0   1   0   1   4 | 3
     *     10 | 0   0   1   3   2 | 10
     *        ---               ---
     *         inf inf inf inf inf
     *
     * Min P = 2a - 1b + 1c - 5d + 22e
     */

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERSolveClpModel.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    ADERSolveClpModel(column_lower_bounds, column_upper_bounds,
    		          index_column_starts, num_col, num_ent, num_row,
					  objective_row, 1, row_lower_bounds, row_indices,
					  row_upper_bounds, solution, values, 0);

    /* Check both the first column value and the objective value              */

    if(solution[0] < 12.00001 &&
       solution[0] > 11.99999)
    {

    	boolean_column = 1;

    }

    if(solution[5] < 10.00001 &&
       solution[5] > 0.99999)
    {

    	boolean_objective = 1;

    }

    if(boolean_column == 1 &&
       boolean_objective == 1)
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

        if(boolean_column == 0)
        {

        	sprintf(print_data, "Test: column solution: FAIL - First value is %f\n \
but needs value 12.\n", solution[0]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: column solution: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_objective == 0)
        {

        	sprintf(print_data, "Test: objective value: FAIL - Objective value is %f\n \
but needs value 10.\n", solution[5]);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: objective value: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
