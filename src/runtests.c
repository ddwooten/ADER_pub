/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : runtests.c                                     */
/*                                                                           */
/* Created:       2015/10/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Executes test cases found in testcases.c                     */
/*                                                                           */
/* Comments:                                                                 */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"
#include "serp_tests.h"

#define FUNCTION_NAME "RunTests:"
/*****************************************************************************/

void RunTests()
{
    int foo = 0;
    int (*test)();
    int test_num_passed = 0;
    int test_num_failed = 0;
    long ader_data, ader_test_block;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    WDB[ader_test_block + ADER_TEST_NUM_CASES] = (double)test_num_cases;

    fprintf(outp, "Running tests. \n");

    for (foo = 0; foo < test_num_cases; foo++)
    {
        test = test_foo_array[foo];
        if (test() > 0)
        {
            test_num_passed += 1;
        }
        else
        {
            test_num_failed += 1;
        }
    }

    if ((test_num_passed + test_num_failed) != test_num_cases)
    {
        Die(FUNCTION_NAME, "Tests passed and failed not equal to number of tests");
    }

    WDB[ader_test_block + ADER_TEST_NUM_PASSED] = (double)test_num_passed;

    WDB[ader_test_block + ADER_TEST_NUM_FAILED] = (double)test_num_failed;

}
