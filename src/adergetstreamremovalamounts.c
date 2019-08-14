/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetstreamremovalamounts.c                  */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function calculates and stores the estimated amount of  */
/*              elements and isotopes to be removed                          */
/*                                                                           */
/* Comments:This function is called from ADERGetMaterialRemovalAmounts       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetStreamRemovalAmounts:"

void ADERGetStreamRemovalAmounts(long ader_mat_stream, long mat,
                                 long mat_ader_data, double t1, double t2)
{

    double adens_corr_factor = 0, dest_mat_adens = 0, mat_remv_frac = 0, sign = 0;
    double ader_mat_stream_total_moved = 0.0;
    long ader_mat_iso = 0, ader_mat_shadow_stream = 0;
    long ader_mat_stream_ele = 0, ader_mat_stream_ele_iso = 0;
    long ader_mat_stream_iso = 0, ader_stream = 0, dest_mat = 0, mat_iso = 0;

    /* If this stream has a shadow stream ( which by the way this function    */
    /* is called any shadow stream will be a destination stream and its       */
    /* index will be stored as a negative value in the source stream which    */
    /* the ader_mat_stream would be if this stream has a shadow ) get the     */
    /* shadow stream                                                          */

    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < 0)
    {

    	ader_mat_shadow_stream = -(long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    	/* Get the shadow stream's material                                   */

    	dest_mat = (long)RDB[ader_mat_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

    	dest_mat_adens = RDB[dest_mat + MATERIAL_ADENS];

    	/* Calculate the adens correction factor                              */

    	adens_corr_factor = (RDB[mat + MATERIAL_ADENS] / dest_mat_adens) *
    			            (RDB[mat + MATERIAL_VOLUME] /
    			             RDB[dest_mat + MATERIAL_VOLUME]);

    }
    else
    {

    	ader_mat_shadow_stream = 0;

    }

	/* Determine if this material is the stream's source or sink, set sign    */

	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
			  GetText(mat + MATERIAL_PTR_NAME)) == 0)
	{

		sign = -1.0;

	}
	else
	{

		sign = 1.0;

	}

    /* Get the original ader stream the material stream was based of off      */

    ader_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_PTR];

    /* Store the fraction of the total material that is to processed every    */
    /* second                                                                 */

    mat_remv_frac = RDB[ader_stream + ADER_STREAM_OPT1];

    /* Loop through the stream's elements                                     */

    ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

    while(ader_mat_stream_ele > VALID_PTR)
    {

        /* Clear the element's previous amount that was removed. For removal  */
        /* streams this is stored in the ELE_FRAC slot as it is not used here */

        WDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] = 0.0;

        /* If there is a shadow stream, set its elemental amount              */

        if(ader_mat_shadow_stream > VALID_PTR)
        {

            ADERSetShadowStreamRemovalAmount(ader_mat_shadow_stream,
            		                         (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z],
    										 0, 0.0);

        }

        /* Loop through the element's isotopes                                */

        ader_mat_stream_ele_iso = (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR];

        while(ader_mat_stream_ele_iso > VALID_PTR)
        {

            /* Get the actual stream isotope                                  */
            ader_mat_stream_iso = (long)RDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR];

            /* Get the ader_mat_iso ( needed to get mat_iso )                 */

            ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

            /* Get the mat_iso ( needed for composition ADENS )               */

            mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

            /* Calculate the expected amount of the isotope to be removed     */
            /* this is stored in the ISO_ELE_FRAC slot as it is not used here */

            /* The removal amount must be calculated based on the stream form */

            if(strcmp("prop", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) == 0)
            {

                WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = fabs((RDB[mat_iso + COMPOSITION_ADENS] /
                                                                        RDB[mat + MATERIAL_ADENS]) *
                                                                       (1.0 -
                                                                        exp((t2 - t1) *
                                                                            mat_remv_frac *
																			sign *
                                                                            RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC])));

            }
            else
            {

            	/* Disc and cont form removal tables will remove the same     */
            	/* amount of material, it just happens differently in time    */
            	/* NOTE!!: Disc and Cont removal tables have units in terms   */
            	/* of fraction per second.                                    */

                WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = mat_remv_frac *
                                                                        (t2 - t1) *
                                                                        RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC]*
																		(RDB[mat_iso + COMPOSITION_ADENS] / RDB[mat + MATERIAL_ADENS]);

            }

            /* If there is a shadow stream, set the iso amount                */

            if(ader_mat_shadow_stream > VALID_PTR)
            {

                ADERSetShadowStreamRemovalAmount(ader_mat_shadow_stream,
                		                         0,
        										 (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI],
												 RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] * adens_corr_factor);

            }

            /* Increment the element's expected removal amount                */

            WDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] = RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] +
                                                               RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

            ader_mat_stream_ele_iso = NextItem(ader_mat_stream_ele_iso);

        }

        /* If there is a shadow stream, set the new elemental amount          */

        if(ader_mat_shadow_stream > VALID_PTR)
        {

            ADERSetShadowStreamRemovalAmount(ader_mat_shadow_stream,
            		                         (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z],
    										 0,
											 RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] * adens_corr_factor);

        }

        /* Increment the total amount of material moved                       */

        ader_mat_stream_total_moved += RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC];

        ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

    }

    /* Store the total amount of material moved in both the host and shadow   */
    /* streams                                                                */

    WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = ader_mat_stream_total_moved;

    if(ader_mat_shadow_stream > VALID_PTR)
    {

    	WDB[ader_mat_shadow_stream + ADER_MAT_STREAM_CUR_AMT] = ader_mat_stream_total_moved * adens_corr_factor;

    }

}
