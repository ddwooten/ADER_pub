/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndrtodata.c                       */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in rto tagged data ( material group composition ratios)*/
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

#define FUNCTION_NAME "ADERReadAderCndRtoData:"

long ADERReadAderCndRtoData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    long cnd_rto_entry = 0, max_j = 0;
    int found_grp2 = 0, found_max = 0, found_min = 0, found_val = 0;

    /* A ratio may have at most 6 more data items past the first group */

    max_j = j + 6;

    /* Create new conditions controlled items entry */

    cnd_rto_entry = NewItem(cnd_ptr + ADER_CND_RTOS_PTR, ADER_CND_RTO_BLOCK_SIZE);

    WDB[cnd_rto_entry + ADER_CND_RTO_GRP1_ID] = (double)PutText(params[j]);

    j++;

    /*Go ahead and set the rto values to negative 1. This will be used as a */
    /* as a check later                                                     */

    WDB[cnd_rto_entry + ADER_CND_RTO_MAX] = -1.0;

    WDB[cnd_rto_entry + ADER_CND_RTO_MIN] = -1.0;

    /* loops through the entry storing items according to their tag */
    /* Exit the loop if you've grabbed all items or hit the max item count */

    while(j < max_j)
    {

        if(strncmp("min", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rto_entry + ADER_CND_RTO_MIN] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+08);
            j++;

            found_min = 1;

        }
        else if(strncmp("max", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rto_entry + ADER_CND_RTO_MAX] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+08);

            j++;

            found_max = 1;

        }
        else if(strncmp("val", params[j], 3) == 0)
        {

            j++;

            WDB[cnd_rto_entry + ADER_CND_RTO_MIN] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+08);

            WDB[cnd_rto_entry + ADER_CND_RTO_MAX] = TestParam(pname, fname, line,
                                                              params[j], PTYPE_REAL,
                                                              0.0, 1E+08);

            /* We make the max entry negative for checks later on             */

            WDB[cnd_rto_entry + ADER_CND_RTO_MAX] = -RDB[cnd_rto_entry + ADER_CND_RTO_MAX];

            j++;

            found_val = 1;
        }
        else if(strncmp("grp2", params[j], 4) == 0)
        {

            j++;

            WDB[cnd_rto_entry + ADER_CND_RTO_GRP2_ID] = (double)PutText(params[j]);

            j++;

            found_grp2 = 1;
        }
        else
        {

            Error(0, "No val, min/max pair or grp2 given for rto entry %s \n \
in cnd group %s found on line %ld in file %s.\n",
                  GetText(cnd_rto_entry + ADER_CND_RTO_GRP1_ID),
                  GetText(cnd_ptr + ADER_CND_ID), line, fname);

        }

        if((found_grp2 == 1) && ((found_val == 1) || ((found_max == 1) && found_min == 1)))
        {

            break;

        }

    }

    /* Check to make sure all required input is present */

    if((found_grp2 != 1) || !((found_val == 1) || ((found_max == 1) && found_min == 1)))
        {

            Error(0, "Either no grp2 or no val or no min/max pair found for \n \
rto group %s in cnd group %s,\n \
found on line %ld in file %s.\n",
                  GetText(cnd_rto_entry + ADER_CND_RTO_GRP1_ID),
                  GetText(cnd_ptr + ADER_CND_RNG_GRP_ID), line, fname);
        }

    /* Check to make sure max is not smaller than min, but MAX must not be    */
    /* negative as this is a purposeful action by the code                    */

    if((WDB[cnd_rto_entry + ADER_CND_RTO_MAX] > 0.0) &&
       (WDB[cnd_rto_entry + ADER_CND_RTO_MAX] < ( WDB[cnd_rto_entry + ADER_CND_RTO_MIN] - 0.000000001)))
    {

        Error(0, "Max ratio value of, %f, not greater than min ratio value of %f \n \
for rto group %s in cnd group %s,\n \
found on line %ld in file %s.\n",
              WDB[cnd_rto_entry + ADER_CND_RTO_MAX],
              WDB[cnd_rto_entry + ADER_CND_RTO_MIN],
              GetText(cnd_rto_entry + ADER_CND_RTO_GRP1_ID),
              GetText(cnd_ptr + ADER_CND_RNG_GRP_ID), line, fname);

    }

    return(j);
}
