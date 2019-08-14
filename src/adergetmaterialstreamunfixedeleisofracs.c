/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetmaterialstreamunfixedeleisofracs.c      */
/*                                                                           */
/* Created:       2016/04/05 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link read in ader data with the           */
/*              appropriate materials                                        */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERProcessMaterialStreamUnFixedEleIsoFracs                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetMaterialStreamUnFixedEleIsoFracs:"

void ADERGetMaterialStreamUnFixedEleIsoFracs(long ader_mat_matrix_data,
		                                     long ader_mat_stream, long mat)
{

    double adens_multiplier = 0, dest_mat_adens = 0, src_mat_adens = 0, total_element = 0;
    long ader_mat_iso = 0, ader_mat_stream_ele = 0, ader_mat_stream_ele_iso = 0;
    long ader_mat_stream_iso = 0, ader_mat_stream_sum_stream_data = 0;
    long ader_mat_stream_sum_stream = 0, mat_ader_data = 0, mat_iso = 0, sign = 0;
    long shadow_stream, src_mat;

    /* first, see if there are sum streams, if so, process those              */

    ader_mat_stream_sum_stream_data = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(ader_mat_stream_sum_stream_data > VALID_PTR)
    {

        ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_data + ADER_MAT_GRP_SUM_GRP_PTR];

        ADERGetMaterialStreamUnFixedEleIsoFracs(ader_mat_matrix_data,
        		                                ader_mat_stream_sum_stream, mat);

        ader_mat_stream_sum_stream_data = NextItem(ader_mat_stream_sum_stream_data);

    }

    /* Go ahead and set the adens_muliplier to 1                              */

    adens_multiplier = 1.0;

    /* If the stream is entering the material it may be the destination   */
    /* end of a shadow stream pair. If so, it will need special           */
    /* processing to account for the source stream's material density     */

    shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    if(shadow_stream > VALID_PTR)
    {

    	dest_mat_adens = RDB[mat + MATERIAL_ADENS];

    	src_mat = (long)RDB[shadow_stream + ADER_MAT_STREAM_MAT_PTR];

    	src_mat_adens = RDB[src_mat + MATERIAL_ADENS];

    	adens_multiplier = src_mat_adens / dest_mat_adens;

    }

    /* Loop through the elements of the stream                                */

    ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

    while(ader_mat_stream_ele > VALID_PTR)
    {

        /* Reset the total_element variable                                   */

        total_element = 0.0;

        /* If the element is fixed, no need to run this function on it        */

        if((long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISO_FIXED] > 0)
        {

            ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

            continue;

        }

        /* This element is not fixed. Loop through it's isotopes to calculate */
        /* the relevant fractions                                             */

        ader_mat_stream_ele_iso = (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR];

        while(ader_mat_stream_ele_iso > VALID_PTR)
        {

            /* Now we navigate to the actual material isotope which knows its */
            /* adens                                                          */

            ader_mat_stream_iso = (long)RDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR];

            ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

            mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

            /* Get the total value for the element                            */

            total_element += RDB[mat_iso + COMPOSITION_ADENS];

            /* Store this number in the ele_frac tag for later processing     */

            WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = RDB[mat_iso + COMPOSITION_ADENS];

            ader_mat_stream_ele_iso = NextItem(ader_mat_stream_ele_iso);

        }

        /* Now, loop through the isotopes again to actually calculate the     */
        /* fractions but only if total element is greater than 0              */

        if(total_element > 0.0)
        {

            ader_mat_stream_ele_iso = (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR];

            while(ader_mat_stream_ele_iso > VALID_PTR)
            {

                ader_mat_stream_iso = (long)RDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR];

                /* Give the isotope its current fraction of the element           */

                WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] / total_element;

                /* Give the isotope its current fraction of the stream            */

                WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] = RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] * RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC];

                ader_mat_stream_ele_iso = NextItem(ader_mat_stream_ele_iso);

            }

        }


        ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

    }

    /* Now that we've updated the elemental and isotopic information, we need */
    /* to update the matrix                                                   */

    /* Get the mat_ader_data                                                  */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Determine the "sign" of the stream. Is it entering or leaving this */
    /* material?                                                          */

    if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
              GetText(mat + MATERIAL_PTR_NAME)) == 0)
    {

        /* Stream is leaving the material                                 */

        sign = -1;

    }
    else
    {

        /* Stream is entering the material                                */

        sign = 1;

    }

    /* Fill in the isotopic fractions ( just do all of them )             */

    ADERFillMaterialCompMatrixIsoData((long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR],
                                      (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
									  ader_mat_matrix_data,
                                      mat_ader_data, adens_multiplier, sign, 0);

}
