/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialremovalele.c                  */
/*                                                                           */
/* Created:       2016/04/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates isotope entries for elements in removal tables       */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialRemovalData        */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialRemovalEle:"

void ADERProcessMaterialRemovalEle(long ader_mat_stream, long mat)
{

    long ader_mat_stream_ele = 0, ader_mat_stream_ele_iso = 0, ader_mat_stream_iso = 0;
    long mat_iso = 0, nuc = 0;
    long found = 0;

    /* loop through this material rem table's elements, they need isotopes    */

    ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

    while(ader_mat_stream_ele > VALID_PTR)
    {

        /* loop through the material's isotopes to find all possible isotopes for */
        /* this element                                                           */

        mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

        while(mat_iso > VALID_PTR)
        {

            nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

            /* We must protect against a fictitious nuclide used in burnup routines */

            if((long)RDB[nuc + NUCLIDE_ZAI] == -1)
            {

                mat_iso = NextItem(mat_iso);

                continue;

            }

            /* if this isotope belongs to this element, go ahead and process it   */

            if((long)RDB[nuc + NUCLIDE_Z] == (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z])
            {

                found += 1;

                /* Now we must check to make sure this isotope was not already    */
                /* added independently from this element. If it was, its value is */
                /* meant to overwrite that from this element                      */

                ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

                while(ader_mat_stream_iso > VALID_PTR)
                {

                    if((long)RDB[nuc + NUCLIDE_ZAI] == (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI])
                    {

                        /* This isotope already exists in the list, and the   */
                    	/* ReproIsos processing function already linked it    */
                    	/* to this element, so break                          */

                        break;

                    }

                    ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

                }

                /* If ader_mat_stream_iso is not a valid pointer, it means one of */
                /* two things. One, there are no isotopes in which case there was */
                /* no isotope already in existence for the isotope we found in the*/
                /* material list. Two, we cycled through the entire list and      */
                /* didn't find a match. Either way, create a new stream isotope   */
                /* entry and link it to the element.                              */

                if(ader_mat_stream_iso < VALID_PTR)
                {

                    /* Create the isotope entry                                       */

                    ader_mat_stream_iso = NewItem(ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR,
                                               ADER_MAT_GRP_ISO_BLOCK_SIZE);

                    /* Create the element's isotope entry                             */

                    ader_mat_stream_ele_iso = NewItem(ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR,
                                                   ADER_MAT_GRP_ELE_ISO_BLOCK_SIZE);

                    /* Give the element a pointer to its new isotope                  */

                    WDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] = (double)ader_mat_stream_iso;

                    /* Populate the isotope's data                                    */

                    WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] = RDB[nuc + NUCLIDE_ZAI];

                    /* We store the element's ( and thus the isotope's ) removal */
                    /* rate in the iso_frac slot. We leave the iso_ele_frac open */
                    /* for future calculation data storage                       */

                    WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] = RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC];

                }

            }

            mat_iso = NextItem(mat_iso);

        }

        /* Here we do something interesting. Removal tables are designed to allow */
        /* the user to enter a removal fraction for ALL elements, regardless of   */
        /* Whether or not they are present in the material. Lacking any isotopes  */
        /* at all indicates that the material lacks this element. As such, it     */
        /* should have a 0 removal rate to prevent fictitious removal of it.      */
        /* We avoid warning the user as this could produce copious warnings       */

        if(found < 1)
        {

            WDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] = 0.0;

        }

        ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

    }

}

