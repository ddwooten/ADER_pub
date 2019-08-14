/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadaderstreamdata.c                       */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Process the various parts of an ADER stream input.           */
/*                                                                           */
/* Comments: Called by ADERCreateAderStreamEntry                             */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderStreamData:"

void ADERReadAderStreamData(char* fname, long stream_ptr, long j, long line,
                            char** params, char* pname, long np)
{
    /* Track the inputs found for error checking */

    int found_form = 0, found_from = 0, found_frac = 0, found_group = 0;
    int found_rem = 0, found_to = 0, found_type = 0;

    /* Loop through all the inputs of the stream, store them appropriately */
    /* according to their tag */

    while(j < np)
    {

        if(strncmp("form", params[j], 4) == 0)
        {

            j++;

            WDB[stream_ptr + ADER_STREAM_FORM] = (double)PutText(params[j]);

            if(strncmp("cont", GetText(stream_ptr + ADER_STREAM_FORM), 4) != 0 &&
               strncmp("disc", GetText(stream_ptr + ADER_STREAM_FORM), 4) != 0 &&
			   strncmp("prop", GetText(stream_ptr + ADER_STREAM_FORM), 4) != 0)
            {

                Error(0, "Invalid entry for 'form' field in ADER stream on line %ld \n \
in file %s. Acceptable entries are 'cont', 'disc', and 'prop'.\n",
                      line, fname);

            }

            found_form = 1;

            j++;

        }
        else if(strncmp("frac", params[j], 4) == 0)
        {

            j++;

            WDB[stream_ptr + ADER_STREAM_OPT1] = TestParam(pname, fname, line,
                                                        params[j], PTYPE_REAL,
                                                        0.0, 1E+18);

            found_frac = 1;

            j++;

        }
        else if(strncmp("from", params[j], 4) == 0)
        {

            j++;

            WDB[stream_ptr + ADER_STREAM_SRC] = (double)PutText(params[j]);

            found_from = 1;

            j++;

        }
        else if(strncmp("group", params[j], 3) == 0)
        {

            WDB[stream_ptr + ADER_STREAM_GRP_TYPE] = (double)PutText(params[j]);

            j++;

            WDB[stream_ptr + ADER_STREAM_GRP_ID] = (double)PutText(params[j]);

            found_group = 1;

            j++;

        }
        else if(strncmp("rem", params[j], 3) == 0)
        {

            WDB[stream_ptr + ADER_STREAM_GRP_TYPE] = (double)PutText(params[j]);

            j++;

            WDB[stream_ptr + ADER_STREAM_GRP_ID] = (double)PutText(params[j]);

            found_rem = 1;

            j++;

        }
        else if(strncmp("to", params[j], 2) == 0)
        {

            j++;

            WDB[stream_ptr + ADER_STREAM_DEST] = (double)PutText(params[j]);

            found_to = 1;

            j++;

        }
        else if(strncmp("type", params[j], 4) == 0)
        {

            j++;

            WDB[stream_ptr + ADER_STREAM_TYPE] = (double)PutText(params[j]);

            j++;

            found_type = 1;

        }
        else
        {

            Error(0, "Invalid entry tag in ADER stream on line %ld in file %s.\n",
                  line, fname);

        }

    }

    /* If the correct combinations of pieces are not in the input, error out */

    if((!found_group && !found_rem) ||
       (!found_from && !found_to) ||
       (found_rem && !found_frac) ||
       (!found_type) ||
       (!found_form))
    {

        Error(0, "Incomplete entry for ADER stream on line %ld in file %s.\n",
              line, fname);

    }

    /* Group-class streams of proportional type with no source are not        */
    /* permitted. Edge cases are too numerous.                                */

    if((strcmp("prop", GetText(stream_ptr + ADER_STREAM_FORM)) == 0) &&
       found_group &&
	   !found_from)
    {

        Error(0, "Group-class streams of proportional type with no source material are not\n\
permitted. Found on line %ld in file %s.\n",
              line, fname);

    }

}
