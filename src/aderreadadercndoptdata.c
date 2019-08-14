/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndoptdata.c                       */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in opt tagged data ( linear solver optimization params)*/
/*              from ADER conditions tables. Returns the index of the next   */
/*              parameter to be checked by ADERReadAderCndData               */
/*                                                                           */
/* Comments: Called by ADERReadAderCndData                                   */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderCndOptData:"

long ADERReadAderCndOptData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    long cnd_opt_entry = 0, max_j = 0;
    int found_dir = 0, found_type = 0;

    if((long)RDB[cnd_ptr + ADER_CND_OPT_PTR] > VALID_PTR)
    {

        Error(0, "Attempting to attach an 'opt' entry to cnd table \n \
%s. Cnd table %s already has an 'opt' entry. Only one 'opt' entry is allowed \n \
per cnd table and only one opt entry per material as well. Found on line %ld of \n \
file %s.\n", GetText(cnd_ptr + ADER_CND_ID), GetText(cnd_ptr + ADER_CND_ID),
              line, fname);

    }

    /* Create new optimization entry */

    cnd_opt_entry = NewItem(cnd_ptr + ADER_CND_OPT_PTR, ADER_CND_OPT_BLOCK_SIZE);

    /* An optimization entry may have up to 5 components past the id */

    max_j = j + 5;

    /* Store data according to its tag. Remember with the found tags */
    /* which data was found. If all necessary data items found, break the loop */

    while(j < max_j)
    {

        if(strncmp("dir", params[j], 3) == 0)
        {

            j++;

            if(strncmp("max", params[j], 3) == 0)
            {

                j++;

                /* We store an optimization direction of "maximize" as a number */
                /* less than zero and a direction of "minimize" as greater than 0 */

                WDB[cnd_opt_entry + ADER_CND_OPT_DIR] = -1.0;

            }
            else if(strncmp("min", params[j], 3) == 0)
            {

                j++;

                WDB[cnd_opt_entry + ADER_CND_OPT_DIR] = 1.0;

            }
            else
            {

                Error(0, "Keyword 'max' or 'min' not found after 'dir' entry\n \
for opt entry in cnd group %s found on line %ld in file %s.\n",
                      GetText(cnd_ptr + ADER_CND_ID), line, fname);
            }

            found_dir = 1;

        }
        else if(strncmp("type", params[j], 4) == 0)
        {

            j++;

            WDB[cnd_opt_entry + ADER_CND_OPT_TYPE] = (double)PutText(params[j]);

            j++;

            WDB[cnd_opt_entry + ADER_CND_OPT_TYPE_TARGET] = (double)PutText(params[j]);

            j++;

            found_type = 1;

        }
        else
        {

            Error(0, "Bad entry, '%s', for opt entry \n \
in cnd group %s on line %ld in file %s.\n \
This is not of type 'dir' or 'type'.\n \
These keywords may have insufficient data in your input or may be missing.\n",
                  params[j], GetText(cnd_ptr + ADER_CND_ID), line, fname);

        }

        if((found_dir == 1) && (found_type == 1))
        {

            break;

        }

    }

    /* It is possible to have looped into another entry in the cnd table */
    /* or even another part of the input. Check to make sure all */
    /* required data items are present for this entry */

    if((found_dir != 1) && (found_type != 1))
    {

        Error(0, "Either 'dir' or 'type', or both, entry(ies) not given for opt entry,\n \
in cnd group %s found on line %ld in file %s.\n",
              GetText(cnd_ptr + ADER_CND_ID), line, fname);

    }

    return(j);
}
