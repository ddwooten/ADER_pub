/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessadergroups.c                        */
/*                                                                           */
/* Created:       2015/12/8 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Call ADERProcessAderGroupFractions to convert group element  */
/*            and isotopic ratios to decimals. Calls ADERProcessAderSumGroup */
/*              to link sum groups with their child groups                   */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderMainData             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderGroups:"

void ADERProcessAderGroups()
{

    long ader_data = 0, grp = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ader_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {

        ADERProcessAderGroupFractions(grp);

        if(RDB[grp + ADER_GRP_SUM_GRPS_PTR] > VALID_PTR)
        {

            ADERProcessAderSumGroup(grp);

        }

        grp = NextItem(grp);

    }

}
