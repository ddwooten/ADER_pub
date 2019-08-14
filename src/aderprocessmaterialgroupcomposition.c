/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialgroupcomposition.c          */
/*                                                                           */
/* Created:       2016/1/1 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles the linking of group composition data to material    */
/*              comp lists and streams.                                      */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialCndGroupData     */
/*          and by ADERProcessMaterialStreamGroupData                        */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialGroupComposition:"

void ADERProcessMaterialGroupComposition(long ader_grp,
                                         long ader_mat_ent_ele_ptr,
                                         long ader_mat_ent_iso_ptr,
                                         long ele_iso_fix_check,
                                         long mat,
                                         long stream_check)
{

    long ader_grp_comp_ent = 0, ader_grp_comp_iso = 0, ader_mat_ent_ele = 0;
    long ader_mat_ent_ele_iso = 0, ader_mat_ent_iso = 0;

    ader_grp_comp_ent = (long)RDB[ader_grp + ADER_GRP_COMP_PTR];

    while(ader_grp_comp_ent > VALID_PTR)
    {

        /* store the ader group's element data in the appropriate list */

        ader_mat_ent_ele = NewItem(ader_mat_ent_ele_ptr,
                                   ADER_MAT_GRP_ELE_BLOCK_SIZE);

        WDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_FRAC] = RDB[ader_grp_comp_ent + ADER_GRP_COMP_FRAC];

        WDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_Z] = RDB[ader_grp_comp_ent + ADER_GRP_COMP_Z];

        ader_grp_comp_iso = (long)RDB[ader_grp_comp_ent + ADER_GRP_COMP_ISOS_PTR];

        /* Here we check for fixed isotopic composition, for all elements, if */
        /* that requirement has been stated in the passed in parameters       */

        if(ele_iso_fix_check > 0 && ader_grp_comp_iso < VALID_PTR)
        {

            Error(0, "ADER group, %s, has no isotopes listed for element with \n\
Z value of %ld. This ADER group has been used to define an ADER stream. ADER \n \
streams with a destination material and no source material MUST have an      \n \
explicit isotopic composition for each element.\n",
                  GetText(ader_grp + ADER_GRP_ID),
                  (long)RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_Z]);

        }
        else if(ader_grp_comp_iso > VALID_PTR)
        {

            /* The element in this group has an isotopic composition. Mark    */
            /* this in the grp ele data block                                 */

            WDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_ISO_FIXED] = 1.0;

        }
        else if(stream_check > 0)
        {

            /* The element in this group has no isotopic composition.         */
            /* Furthermore, this data is for a stream. As such, we must assign*/
            /* every possible isotope, but with no fraction, to this element  */

            ADERProcessMaterialStreamUnFixedEle(ader_mat_ent_ele,
                                                ader_mat_ent_iso_ptr, mat);

        }

        while(ader_grp_comp_iso > VALID_PTR)
        {

            /* If there are isos, store these as well */

            ader_mat_ent_iso = NewItem(ader_mat_ent_iso_ptr,
                                       ADER_MAT_GRP_ISO_BLOCK_SIZE);

            /* Don't forget to give the element a pointer to its isotope */

            ader_mat_ent_ele_iso = NewItem(ader_mat_ent_ele + ADER_MAT_GRP_ELE_ISOS_PTR,
                                           ADER_MAT_GRP_ELE_ISO_BLOCK_SIZE);

            WDB[ader_mat_ent_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] = (double)ader_mat_ent_iso;

            /* now store the iso's information                                */

            WDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = RDB[ader_grp_comp_iso + ADER_GRP_ISO_FRAC];

            WDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_FRAC] = RDB[ader_grp_comp_iso + ADER_GRP_ISO_FRAC] * RDB[ader_grp_comp_ent + ADER_GRP_COMP_FRAC];

            WDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_ZAI] = RDB[ader_grp_comp_iso + ADER_GRP_ISO_ZAI];

            ader_grp_comp_iso = NextItem(ader_grp_comp_iso);

        }

        ader_grp_comp_ent = NextItem(ader_grp_comp_ent);

    }

}

