/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderprocessmatstreameleunfixedisofrac.c    */
/*                                                                           */
/* Created:       2016/30/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests for correct fraction of isotope in unfixed ele stream  */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERProcessMatStreamEleUnFixedIsoFrac:"

void TESTADERProcessMatStreamEleUnFixedIsoFrac(long step)
{

    char *const test_name = "ADERProcessMatStreamEleUnFixedIsoFrac";
    char status[5];
    char print_data[256];
    char *mat_name, *stream_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block;
    long mat, mat_ader_data, stream, stream_iso, stream_iso_zai ;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERProcessMatStreamEleUnFixedIsoFrac.\n");

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

            sprintf(print_data, "Material FLiBeFuel has no redox streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Fluorine redox stream.\n");

        stream_name = GetText(stream + ADER_MAT_STREAM_ID);

        if(strncmp("Fluorine", stream_name, 8) == 0)
        {

            sprintf(print_data, "FLiBeFuel has Fluorine redox stream but no isotopes.\n");

            stream_iso = (long)RDB[stream + ADER_MAT_STREAM_ISOS_PTR];

            while(stream_iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel Fluorine stream has isotopes but no F-19.\n");

                stream_iso_zai = (long)RDB[stream_iso + ADER_MAT_GRP_ISO_ZAI];

                if(stream_iso_zai == 90190)
                {

                    sprintf(print_data, "FLiBeFuel Fluorine stream has F-19 but bad frac of %f.\n",
                            RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC]);

                    if(RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC] < 1.0000001 &&
                       RDB[stream_iso + ADER_MAT_GRP_ISO_FRAC] > 0.9999999)
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
