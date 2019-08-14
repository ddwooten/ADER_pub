/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderisosdata.c              */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates ADER_MAT_ISO entry for every iso in a material       */
/*                                                                           */
/* Comments: This function is called from ADERLinkMaterialIsostopeIndicies   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderIsosData:"

void ADERProcessMaterialAderIsosData(long mat)
{

    long i = 0, iso = 0, mat_ader_data = 0, mat_ader_ele = 0, mat_ader_ele_iso = 0, mat_ader_iso = 0;
    long nuc = 0, z = 0, zai = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* loop through all of a materials isotopes */

    iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(iso > VALID_PTR)
    {

        nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

        z = (long)RDB[nuc + NUCLIDE_Z];

        zai = (long)RDB[nuc + NUCLIDE_ZAI];

        /* protect against fake burnup isotope */

        if(zai == -1)
        {

            iso = NextItem(iso);

            continue;

        }

        /* Create an iso list entry for every iso in a material */

        mat_ader_iso = NewItem(mat_ader_data + ADER_MAT_ISOS_PTR,
                               ADER_MAT_ISOS_BLOCK_SIZE);

        WDB[mat_ader_iso + ADER_MAT_ISO_PTR] = (double)iso;

        /* Now, we need to find the element which corresponds to this isotope */
        /* Create an isotope entry for that element, and give it the ptr      */

        mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

        for(i = 0; i < (z - 1); i++)
        {

            mat_ader_ele = NextItem(mat_ader_ele);

        }

        mat_ader_ele_iso = NewItem(mat_ader_ele + ADER_MAT_ELE_ISOS_PTR,
                                   ADER_MAT_ELE_ISO_BLOCK_SIZE);

        WDB[mat_ader_ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR] = (double)mat_ader_iso;

        iso = NextItem(iso);

    }

}
