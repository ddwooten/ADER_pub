/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadergroupdata.c                        */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Called by ADERCreateAderGroupEntry to process group data     */
/*              Calls auxiliary functions to either store a groups density   */
/*              and then process it's contents. If the group is a sum group  */
/*              a special routine is called                                  */
/*                                                                           */
/* Comments: Called by ADERCreateAderGroupEntry. The auxiliary functions     */
/*           should return the next index to be checked                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderGroupData:"

void ADERReadAderGroupData(char* fname, long group_ptr, long j, long line,
                           char** params, char* pname, long np)
{
    /* Loop through the group entry's contents */

    while(j < np)
    {

        if(strncmp("sum", params[j], 3) == 0)
        {

            /* If the group type is sum, call the routine to deal with those */
            /* group types */

            j++;

            j = ADERReadAderGroupSumData(fname, group_ptr, j, line, params, pname,
                                         np);

        }
        else
        {
            /* Otherwise, it's a normal group, read in a normal group */

            j = ADERReadAderGroupItemData(fname, group_ptr, j, line, params, pname,
                                          np);
        }

    }

}
