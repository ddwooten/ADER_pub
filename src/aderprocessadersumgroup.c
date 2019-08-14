/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessadersumgroup.c                      */
/*                                                                           */
/* Created:       2015/12/8 (DDW)                                            */
/* Last modified: 2015/12/8(DDW)                                             */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Links ADER_GRP_SUM_GRP_PTR to the group it should point to   */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderGroups               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderSumGroup:"

void ADERProcessAderSumGroup(long grp)
{

    char *grp_id = NULL;
    long ader_data = 0, search_grp = 0, sum_grp = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    sum_grp = (long)RDB[grp + ADER_GRP_SUM_GRPS_PTR];

    while(sum_grp > VALID_PTR)
    {

        grp_id = GetText(sum_grp + ADER_GRP_SUM_GRP_ID);

        search_grp = (long)RDB[ader_data + ADER_GROUPS_PTR];

        /* We know the group's name we have to find, find it, store its location */
        /* in the ADER_GRP_SUM_GRP_PTR slot. Add this group's density, times  */
        /* it's weight value to the host's density                            */

        while(search_grp > VALID_PTR)
        {

            if(strcmp(GetText(search_grp + ADER_GRP_ID), grp_id) == 0)
            {

                WDB[sum_grp + ADER_GRP_SUM_GRP_PTR] = (double)search_grp;

                break;

            }

            search_grp = NextItem(search_grp);

        }

        sum_grp = NextItem(sum_grp);

    }
}
