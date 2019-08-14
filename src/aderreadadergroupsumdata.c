/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadergroupsumdata.c                     */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Processes data for groups which are summation groups. Stores */
/*              the IDs of all the groups involved. Returns the next params  */
/*              index to be checked                                          */
/*                                                                           */
/* Comments:Called by ADERReadAderGroupData                                  */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderGroupSumData:"

long ADERReadAderGroupSumData(char* fname, long group_ptr, long j, long line,
                              char** params, char* pname, long np)
{
    long sum_group = 0;

    while(j < np )
    {

        /* Create a new sum group entry in the parent group */

        sum_group = NewItem(group_ptr + ADER_GRP_SUM_GRPS_PTR,
                            ADER_GRP_SUM_GRP_BLOCK_SIZE);

        /* Store the group id which is a part of the sum */

        WDB[sum_group + ADER_GRP_SUM_GRP_ID] = (double)PutText(params[j]);

        j++;

        /* Store the weight of this group in the sum */

        WDB[sum_group + ADER_GRP_SUM_GRP_WEIGHT] = TestParam(pname, fname, line,
                                                         params[j], PTYPE_REAL,
                                                         0.0, 1E+6);

        j++;

    }

    return(j);
}
