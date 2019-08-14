/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndrngdata.c                       */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in rng tagged data ( material group composition ranges)*/
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

#define FUNCTION_NAME "ADERReadAderCndRngData:"

long ADERReadAderCndRngData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    long cnd_rng_entry = 0, max_j = 0;
    int found_max = 0, found_min = 0, found_val = 0;

    /* Create new range entry */

    cnd_rng_entry = NewItem(cnd_ptr + ADER_CND_RNGS_PTR, ADER_CND_RNG_BLOCK_SIZE);

    /* Store the id which is the parameter the index is currently on */

    WDB[cnd_rng_entry + ADER_CND_RNG_GRP_ID] = (double)PutText(params[j]);

    j++;

    /* A rng entry may have up to 4 components past the id name */

    max_j = j + 3;

    /* Store data according to its tag. Remember with the found tags */
    /* which data was found. If all necessary data items found, break the loop */

    while(j < max_j)
    {

        if(strncmp("min", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rng_entry + ADER_CND_RNG_MIN] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+18);
            j++;

            found_min = 1;

        }
        else if(strncmp("max", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rng_entry + ADER_CND_RNG_MAX] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+18);

            j++;

            found_max = 1;

        }
        else if(strncmp("val", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rng_entry + ADER_CND_RNG_MIN] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+18);

            WDB[cnd_rng_entry + ADER_CND_RNG_MAX] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+18);

            j++;

            found_val = 1;

        }
        else
        {

            Error(0, "No val or min/max pair given for rng entry, %s,\n \
in cnd group %s found on line %ld in file %s.\n",
                  GetText(cnd_rng_entry + ADER_CND_RNG_GRP_ID),
                  GetText(cnd_ptr + ADER_CND_ID), line, fname);

        }

        if((found_val == 1) || ((found_max == 1) && (found_min ==1)))
        {

            break;

        }
    }

    /* It is possible to have looped into another entry in the cnd table */
    /* or even another part of the input. Check to make sure all */
    /* required data items are present for this entry */
    if((found_val != 1) && ((found_max != 1) || (found_min != 1)))
    {

        Error(0, "Either val or min/max pair not given for rng entry, %s,\n \
in cnd group %s found on line %ld in file %s.\n",
              GetText(cnd_rng_entry + ADER_CND_RNG_GRP_ID),
              GetText(cnd_ptr + ADER_CND_ID), line, fname);

    }

    return(j);

}
