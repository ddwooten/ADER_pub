/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialstreamunfixedele.c          */
/*                                                                           */
/* Created:       2016/04/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates isotope entries for unfixed elements                 */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialGroupComposition */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialStreamUnFixedEle:"

void ADERProcessMaterialStreamUnFixedEle(long ader_mat_stream_ele,
                                         long ader_mat_stream_iso_ptr,
                                         long mat)
{

    long ader_mat_stream_ele_iso = 0, ader_mat_stream_iso = 0, mat_iso = 0, nuc = 0;
    long found = 0;

    /* loop through the material's isotopes to find all possible isotopes for */
    /* this element                                                           */

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        /* if this isotope belongs to this element, go ahead and process it   */

        if((long)RDB[nuc + NUCLIDE_Z] == (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z])
        {

            found += 1;

            /* Create the isotope entry                                       */

            ader_mat_stream_iso = NewItem(ader_mat_stream_iso_ptr,
                                       ADER_MAT_GRP_ISO_BLOCK_SIZE);

            /* Create the element's isotope entry                             */

            ader_mat_stream_ele_iso = NewItem(ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR,
                                           ADER_MAT_GRP_ELE_ISO_BLOCK_SIZE);

            /* Give the element a pointer to its new isotope                  */

            WDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] = (double)ader_mat_stream_iso;

            /* Populate the isotope's data                                    */

            WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] = RDB[nuc + NUCLIDE_ZAI];

        }

        mat_iso = NextItem(mat_iso);

    }

    if(found < 1)
    {

        Error(0, "No isotopes were found for element with Z value of %ld in \n \
material %s. This error originated from ADERProcessMaterialStreamUnFixedEle \n \
which indicates that an element in a stream assigned to the named material has \n \
no isotopes in this material. Please place at least one isotope belonging to \n \
this element into the named material's composition at, at least, 0 material \n \
fraction. This will fix the error and preserve the simulation integrity.\n",
              (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z],
              GetText(mat + MATERIAL_PTR_NAME));
    }

}

