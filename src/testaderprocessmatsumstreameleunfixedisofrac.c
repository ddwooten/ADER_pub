/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderprocessmatsumstreameleunfixedisofrac.c */
/*                                                                           */
/* Created:       2016/30/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests for correct fraction of isotope in unfixed ele  sum    */
/* sum stream                                                                */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERProcessMatSumStreamEleUnFixedIsoFrac:"

void TESTADERProcessMatSumStreamEleUnFixedIsoFrac(long step)
{

    char *const test_name = "ADERProcessMatSumStreamEleUnFixedIsoFrac";
    char status[5];
    char print_data[256];
    char *mat_name, *stream_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block;
    long mat, mat_ader_data, stream, stream_iso, stream_iso_zai;
    long sum_stream_data, sum_stream;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERProcessMatSumStreamEleUnFixedIsoFrac.\n");

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

            sprintf(print_data, "Material FLiBeFuel has no remv streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no ActF2 remv stream.\n");

        stream_name = GetText(stream + ADER_MAT_STREAM_ID);

        if(strncmp("ActF2", stream_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ActF2 remv stream but no sum streams.\n");

            sum_stream_data = (long)RDB[stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(sum_stream_data > VALID_PTR)
            {


                sprintf(print_data, "FLiBeFuel ActF2 remv stream has sum streams but no Uranium2.\n");

                if(strncmp("Uranium2", GetText(sum_stream_data + ADER_MAT_GRP_SUM_GRP_ID), 8) == 0)
                {

                    sprintf(print_data, "FLiBeFuel ActF2 remv stream has Uranium2 but Uranium2 has no isotopes.\n");

                    sum_stream = (long)RDB[sum_stream_data + ADER_MAT_GRP_SUM_GRP_PTR];

                    stream_iso = (long)RDB[sum_stream + ADER_MAT_STREAM_ISOS_PTR];

                    while(stream_iso > VALID_PTR)
                    {

                        sprintf(print_data, "FLiBeFuel ActF2 remv stream Uranium2 has isotopes but no U-233.\n");

                        stream_iso_zai = (long)RDB[stream_iso + ADER_MAT_GRP_ISO_ZAI];

                        if(stream_iso_zai == 922330)
                        {

                            sprintf(print_data, "FLiBeFuel ActF2 remv stream Uranium2 U-233 has bad frac of %f.\n",
                                    RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC]);

                            if(RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC] < 0.949993 &&
                               RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC] > 0.949991)
                            {

                                boolean = 1;

                                memset(print_data, 0, strlen(print_data));

                            }

                            break;

                        }

                        stream_iso = NextItem(stream_iso);
                    }

                    break;

                }

                sum_stream_data = NextItem(sum_stream_data);

            }

            break;
        }

        stream = NextItem(stream);

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
