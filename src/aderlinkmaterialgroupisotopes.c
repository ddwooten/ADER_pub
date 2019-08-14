/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderlinkmaterialgroupisotopes.c                */
/*                                                                           */
/* Created:       2016/1/4 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Links material ader isotope indices to group isotope data    */
/*                                                                           */
/* Comments:This function is called from ADERLinkMaterialIsotopeIndices      */
/*          and by ADERLinkMaterialStreamIsotopes                            */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERLinkMaterialGroupIsotopes:"

void ADERLinkMaterialGroupIsotopes(long ader_mat_ent_iso, long mat)
{

    long ader_mat_ent_iso_zai = 0, mat_ader_data = 0, mat_ader_iso = 0, mat_iso = 0, nuc = 0;
    long nuc_zai = 0;

    /* get the ader data                                                      */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    while(ader_mat_ent_iso > VALID_PTR)
    {

        /* go through the isotope list */

        ader_mat_ent_iso_zai = (long)RDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_ZAI];

        mat_ader_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

        while(mat_ader_iso > VALID_PTR)
        {

            /* Go through the material's ADER isotopes. If you find a match,  */
            /* store that info                                                */

            mat_iso = (long)RDB[mat_ader_iso + ADER_MAT_ISO_PTR];

            nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

            nuc_zai = (long)RDB[nuc + NUCLIDE_ZAI];

            if(ader_mat_ent_iso_zai == nuc_zai)
            {

                WDB[ader_mat_ent_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR] = mat_ader_iso;

                break;

            }

            mat_ader_iso = NextItem(mat_ader_iso);

        }

        if(WDB[ader_mat_ent_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR] < VALID_PTR)
        {

            Error(0, "No matching material isotope found for group or\n \
stream isotope %ld in material %s. To remedy this error please insert the \n \
isotope in question into the named material's composition definition. This \n \
isotope may be inserted with 0 material fraction. This will preserve simulation\n \
integrity and remedy this error.\n", ader_mat_ent_iso_zai,
                GetText(mat + MATERIAL_PTR_NAME));

        }

        ader_mat_ent_iso = NextItem(ader_mat_ent_iso);

    }

}
