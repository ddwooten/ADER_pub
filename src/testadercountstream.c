/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadercountstream.c                          */
/*                                                                           */
/* Created:       2016/21/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that ADERCountStream returns an appropriate value.     */
/*              WARNING!!! Tests for stream index assignment are done in the */
/*              TESTADERGetBurnMatrixData test for simplicity                */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERCountStream:"

void TESTADERCountStream(long mat)
{

    char *const test_name = "ADERCountStream";
    char status[5];
    char print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data;
    long ader_mat_stream;
    long ader_test_block, mat_ader_data, test_value;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERCountStream.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel has no streams. \n");

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has feed streams but no ActF stream.\n");

        /* Even though this stream would not be processed by count streams    */
        /* we still use it here because it is otherwise equiavlent to a sum   */
        /* stream that would be fed into the function                         */

        if(strcmp("ActF", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* We pass 0 for "num_rows" because it doesn't matter for this test       */

    test_value = ADERCountStream(ader_mat_stream, 0, 0);

    sprintf(print_data, "Material FLiBeFuel feed stream ActF has \n \
bad stream count of %ld and needs 2.\n", test_value);

    if(test_value == 2)
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

    }

}
