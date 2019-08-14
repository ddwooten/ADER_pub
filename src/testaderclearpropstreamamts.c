/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderclearpropstreamamts.c                  */
/*                                                                           */
/* Created:       2017/01/13 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that ADERClearPropStreamAmts does indeed set the       */
/*              CUR_AMT and ADJ_AMT to 0 for all prop streams                */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERClearPropStreamAmts:"

void TESTADERClearPropStreamAmts(long mat)
{

    char *const test_name = "ADERClearPropStreamAmts";
    char status[5];
    char print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data;
    long ader_mat_stream;
    long ader_test_block, mat_ader_data, test_value;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERClearPropStreamAmts.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel has no remv streams. \n");

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has remv streams but no reproc stream.\n");

        if(strcmp("reproc", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Set the cur_amt and adj_amt to some number                             */

    WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 5.0;

    WDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] = 3.0;

    ADERClearPropStreamAmts(0, mat);

    sprintf(print_data, "Material FLiBeFuel has reproc stream with CUR_AMT of \n \
%f and ADJ_AMT of %f.\n", RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT],
            RDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT]);

    if((RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] == 0.0) &&
       (RDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] == 0.0))
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
