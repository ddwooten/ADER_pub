/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessadergroupfractions.c                */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Converts elemental and isotopic ratios to fractions          */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderGroups               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderGroupFractions:"

void ADERProcessAderGroupFractions(long grp)
{

    double ele_sum = 0.0;
    double iso_sum = 0.0;
    long ele = 0, iso = 0;

    ele = (long)RDB[grp + ADER_GRP_COMP_PTR];

    /* Get the total */
    while(ele > VALID_PTR)
    {

        ele_sum += RDB[ele + ADER_GRP_COMP_FRAC];

        ele = NextItem(ele);

    }

    /* Turn that total into decimals. Also, do the same for isos */
    ele = (long)RDB[grp + ADER_GRP_COMP_PTR];

    while(ele > VALID_PTR)
    {

        WDB[ele + ADER_GRP_COMP_FRAC] = RDB[ele + ADER_GRP_COMP_FRAC] / ele_sum;

        iso_sum = 0.0;

        /* Get the iso sum if it exists, if no isos, both of these next while */
        /* loops will not run */

        iso = (long)RDB[ele + ADER_GRP_COMP_ISOS_PTR];

        while(iso > VALID_PTR)
        {

            iso_sum += RDB[iso + ADER_GRP_ISO_FRAC];

            iso = NextItem(iso);

        }

        iso = (long)RDB[ele + ADER_GRP_COMP_ISOS_PTR];

        while(iso > VALID_PTR)
        {

            WDB[iso + ADER_GRP_ISO_FRAC] = RDB[iso + ADER_GRP_ISO_FRAC] / iso_sum;

            iso = NextItem(iso);

        }

        ele = NextItem(ele);

    }
}
