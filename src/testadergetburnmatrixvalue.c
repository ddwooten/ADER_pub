/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadergetburnmatrixvalue.c                   */
/*                                                                           */
/* Created:       2016/17/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that proper value is returned                          */
/*                                                                           */
/* Comments: This function is called from ADERBurnMaterials                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERGetBurnMatrixValue:"

void TESTADERGetBurnMatrixValue()
{

    char *const test_name = "ADERGetBurnMatrixValue";
    char status[5];
    char print_data[256];
    double percent_diff, test_value = 0.0;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, i, j, k;
    long *row, *col;
    complex *val;
    struct ccsMatrix *burn_matrix;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERGetBurnMatrixValue.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Generate the matrix                                                    */

    burn_matrix = ccsMatrixNew(10, 10, 99);

    /* Parse out the pieces we need to search through                         */

    val = burn_matrix->values;
    row = burn_matrix->rowind;
    col = burn_matrix->colptr;

    /* Populate the matrix                                                    */

    col[0] = 0;

    k = 0;

    for(i = 0; i < 10; i++)
    {

    	for(j = 0; j < 10; j++)
    	{

    		if(k != 0)
    		{

        	    val[k - 1].re = (double)k;
        	    val[k - 1].im = 0.0;

        	    row[k - 1] = j;

    		}

    		k++;

    	}

	    col[i + 1] = k;

    }

    /* Get the test value                                                     */

    test_value = ADERGetBurnMatrixValue(4, burn_matrix, 8);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    sprintf(print_data, "Value returned is %f but should be 48.0.\n", test_value);

    percent_diff = (test_value - 48.0) / 48.0;

    if(fabs(percent_diff) < 0.001)
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

    }

}
