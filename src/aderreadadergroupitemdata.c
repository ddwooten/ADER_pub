/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadergroupitemdata.c                    */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Processes the items in a group. If just an element with no   */
/*              isos, simply stores it's information. Otherwise, call the    */
/*              isotope function to store the isos                           */
/*                                                                           */
/* Comments:Called by ADERReadAderGroupData                                  */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderGroupItemData:"

long ADERReadAderGroupItemData(char* fname, long group_ptr, long j, long line,
                              char** params, char* pname, long np)
{
    long composition = 0;
    int num_isos = 0;

    while(j < np )
    {

        /* Create a new group composition entry */

        composition = NewItem(group_ptr + ADER_GRP_COMP_PTR,
                              ADER_GRP_COMP_BLOCK_SIZE);

        /* Store the element Z for this piece of the composition */

        WDB[composition + ADER_GRP_COMP_Z] = (double)IsotoZAI(params[j]);

        /* If it isn't a Z value, it's an incorrect value */

        if(RDB[composition + ADER_GRP_COMP_Z] < 0 ||
           RDB[composition + ADER_GRP_COMP_Z] > 111)
        {
            Error(0, "Item in group %s, found on line %ld in file \n \
%s is either not recognizable by \n \
IsotoZai or is a non-element without an element parent. \n \
IsotoZai output is %ld.\n",
                  GetText(group_ptr + ADER_GRP_ID), line, fname,
                  RDB[composition + ADER_GRP_COMP_Z]);
        }

        j++;

        /* Store the element's fraction of that group */

        WDB[composition + ADER_GRP_COMP_FRAC] = TestParam(pname, fname, line,
                                                         params[j], PTYPE_REAL,
                                                         0.0, 1E+6);

        j++;

        if(strncmp("isos", params[j], 4) == 0)
        {
            /* If there are isotopes, get the number of isotopes and call the */
            /* isotopes reader routine */

            j++;

            num_isos = atoi(params[j]);

            j++;

            j = ADERReadAderGroupIsosData(composition, fname, group_ptr, j,
                                          line, params, pname, num_isos);
        }

    }

    return(j);
}
