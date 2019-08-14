/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : finaltestreport.c                              */
/*                                                                           */
/* Created:       2015/11/3 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.24                                                     */
/*                                                                           */
/* Description: Prints final test output                                     */
/*                                                                           */
/* Comments:                                                                 */
/*                                                                           */
/*****************************************************************************/

#include "header.h"

#define FUNCTION_NAME "FinalTestReport:"

void FinalTestReport(long test_num_passed, long test_num_failed,
                     long test_num_cases)
{

    const char *const test_file_out = "TestResults.test";
    FILE *fp;

    if ((fp = fopen(test_file_out, "a")) == NULL)
    {
        Die(FUNCTION_NAME, "Unable to open test file for writing");
    }
    else
    {
        fprintf(fp, "********************************************************************************\n");
        fprintf(fp, "****************************** Final Test Report *******************************\n");
        fprintf(fp, "Tests passed: %ld \n", test_num_passed);
        fprintf(fp, "Tests failed: %ld \n", test_num_failed);
        fprintf(fp, "Total tests : %ld \n", test_num_cases);
        fprintf(fp, "************************************* End **************************************\n");
    }

    fclose(fp);

    fprintf(outp, "Done running tests.\n \
Tests Passed: %ld \n \
Tests Failed: %ld \n \
Total Tests : %ld \n \
Detailed results in TestResults.test. \n", test_num_passed,
            test_num_failed, test_num_cases);

    /* Because FinalTestReport will now be the exiting function in a test     */
    /* scenario, we call the appropriate finishing functions                  */

    FreeMem();

    FinalizeMPI();

    exit(0);

}
