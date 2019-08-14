/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetmateleisofrac.c                         */
/*                                                                           */
/* Created:       2016/03/14 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calculates fraction of each isotope belonging to an elemental*/
/*              group as well as the element's fraction of the material      */
/*                                                                           */
/* Comments: This function is called from ADEROperateMaterial                */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetMatEleIsoFrac:"

void ADERGetMatEleIsoFrac(long mat)
{

    double sum = 0;
    long ader_mat_ele = 0, ader_mat_ele_iso = 0, ader_mat_iso = 0, mat_ader_data = 0, iso = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* loop through all of a materials elements */

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

        /* reset the sum for this element                                     */

        sum = 0.0;

        ader_mat_ele_iso = (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISOS_PTR];

        /* get the total adens for all isotopes of this elemental type */

        while(ader_mat_ele_iso > VALID_PTR)
        {

            ader_mat_iso = (long)RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

            iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

            sum += RDB[iso + COMPOSITION_ADENS];

            ader_mat_ele_iso = NextItem(ader_mat_ele_iso);

        }

        /* store the total sum as the fraction of the material for this element*/

        WDB[ader_mat_ele + ADER_MAT_ELE_FRAC] = sum / RDB[mat + MATERIAL_ADENS];

        ader_mat_ele_iso = (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISOS_PTR];

        /* get the relative fraction of each isotope in this element. This    */
        /* if protects against NaNs appearing in the code                     */

        if(sum != 0.0)
        {

            while(ader_mat_ele_iso > VALID_PTR)
            {

                ader_mat_iso = (long)RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

                iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

                WDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_FRAC] = RDB[iso + COMPOSITION_ADENS] / sum;

                ader_mat_ele_iso = NextItem(ader_mat_ele_iso);

            }

        }

        ader_mat_ele = NextItem(ader_mat_ele);

    }

}
