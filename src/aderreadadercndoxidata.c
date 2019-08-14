/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndoxidata.c                       */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in oxidation table id names, tagged by 'oxi' in the cnd*/
/*              ADER conditions tables. Returns the index of the next        */
/*              parameter to be checked by ADERReadAderCndData               */
/*                                                                           */
/* Comments: Called by ADERReadAderCndData                                   */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderCndOxiData:"

long ADERReadAderCndOxiData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    char *ader_cnd_id = NULL, *ader_cnd_oxi_id = NULL;
    long cnd_oxi_entry = 0, start_j = 0;
    long found = 0, found_max = 0, found_min = 0, found_val = 0;

    /* Catch bad user input */

    if((long)RDB[cnd_ptr + ADER_CND_OXI_PTR] > VALID_PTR)
    {

        ader_cnd_id = GetText(cnd_ptr + ADER_CND_ID);

        cnd_oxi_entry = (long)RDB[cnd_ptr + ADER_CND_OXI_PTR];

        ader_cnd_oxi_id = GetText(cnd_oxi_entry + ADER_OXI_TBL_ID);

        Error(0, "On line %ld in file %s,\n \
trying to add oxidation table %s to conditions block %s \n \
which already has oxidation table %s. Only one oxidation table per conditions block. \n \
Only one oxidation table per material as well.\n", line, fname, params[j],
              ader_cnd_id, ader_cnd_oxi_id);

    }

    /* Create new oxidation items table entry entry for this conditions block */

    cnd_oxi_entry = NewItem(cnd_ptr + ADER_CND_OXI_PTR, ADER_CND_OXI_BLOCK_SIZE);

    /*Store the name */

    WDB[cnd_oxi_entry + ADER_CND_OXI_ID] = (double)PutText(params[j]);

    j++;

    /* If it has oxi targets, store them */

    if((strncmp("max", params[j], 3) == 0) ||
       (strncmp("min", params[j], 3) == 0) ||
       (strncmp("val", params[j], 3) == 0))
    {

        start_j = j;

        while((found < 1) && (j < (start_j + 3)))
        {

            if(strncmp("max", params[j], 3) == 0)
            {

                j++;

                WDB[cnd_oxi_entry + ADER_CND_OXI_MAX] = TestParam(pname, fname, line,
                                                                  params[j], PTYPE_REAL,
                                                                  -1E+08, 1E+08);

                j++;

                found_max = 1;

            }
            else if(strncmp("min", params[j], 3) == 0)
            {

                j++;

                WDB[cnd_oxi_entry + ADER_CND_OXI_MIN] = TestParam(pname, fname, line,
                                                                  params[j], PTYPE_REAL,
                                                                  -1E+08, 1E+08);

                j++;

                found_min = 1;

            }
            else if(strncmp("val", params[j], 3) == 0)
            {

                j++;

                WDB[cnd_oxi_entry + ADER_CND_OXI_MAX] = TestParam(pname, fname, line,
                                                                  params[j], PTYPE_REAL,
                                                                  -1E+08, 1E+08);

                WDB[cnd_oxi_entry + ADER_CND_OXI_MIN] = TestParam(pname, fname, line,
                                                                  params[j], PTYPE_REAL,
                                                                  -1E+08, 1E+08);

                j++;

                found_val = 1;

            }
            else
            {

                Error(0, "Input on line %ld in file %s \n \
for cnd group %s has input word, %s, that is not either 'val', 'min', or 'max'.\n",
                      line, fname, GetText(cnd_ptr + ADER_CND_ID), params[j]);

            }

            if((found_val > 0) || ((found_max > 0) && (found_min > 0)))
            {

                found = 1;

            }

        }

        /* It is possible to have looped into another entry in the cnd table */
        /* or even another part of the input. Check to make sure all */
        /* required data items are present for this entry */
        if((found_val < 1) && ((found_max < 1) || (found_min < 1)))
        {

            Error(0, "Either val or min/max pair not given for oxi entry, %s,\n \
in cnd group %s found on line %ld in file %s.\n",
                  GetText(cnd_oxi_entry + ADER_CND_OXI_ID),
                  GetText(cnd_ptr + ADER_CND_ID), line, fname);

        }

    }
    else
    {

        /* Set a default value of 0.0 */

        WDB[cnd_oxi_entry + ADER_CND_OXI_MAX] = 0.0;

        WDB[cnd_oxi_entry + ADER_CND_OXI_MIN] = 0.0;

    }

    return(j);

}
