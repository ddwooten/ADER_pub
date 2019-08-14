/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermatremveleamount.c                     */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the calculated amount of elemental     */
/*              removal is correct.                                          */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatRemvEleAmount:"

void TESTADERMatRemvEleAmount(long step)
{

    char *const test_name = "ADERMatRemvEleAmount";
    char status[5];
    char print_data[256];
    char *mat_name, *strm_id;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, mat, mat_ader_data, strm, strm_ele;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERMatRemvEleAmount.\n");

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

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in FLiBeFuel has no elements.\n");

            strm_ele = (long)RDB[strm + ADER_MAT_STREAM_ELES_PTR];

            while(strm_ele > VALID_PTR)
            {

                sprintf(print_data, "'reproc' stream in FLiBeFuel has no Li.\n");

                if((long)RDB[strm_ele + ADER_MAT_GRP_ELE_Z] == 3)
                {

                    sprintf(print_data, "'reproc' stream in FLiBeFuel has Li but\n \
bad ele removal of %f and needs ele rate of 0.00121949 .\n", RDB[strm_ele + ADER_MAT_GRP_ELE_FRAC]);

                    if(RDB[strm_ele + ADER_MAT_GRP_ELE_FRAC] < 0.00121950 &&
                       RDB[strm_ele + ADER_MAT_GRP_ELE_FRAC] > 0.00121948)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_ele = NextItem(strm_ele);
            }

            break;
        }

        strm = NextItem(strm);

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
