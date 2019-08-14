/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialdiscstreameffects.c         */
/*                                                                           */
/* Created:       2016/10/19 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Actually updates a material's isotopic composition and       */
/*              density based on disc stream effects                         */
/*                                                                           */
/* Comments:This function is called from ADERUpdateMaterialDiscStreamEffects */
/*                                       ADERProcessMaterialDiscStreamEffects*/
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialDiscStreamEffects:"

void ADERProcessMaterialDiscStreamEffects(long ader_mat_stream, long adj,
		                                  long i, long mat)
{

	double src_mat_adens = 0, sign = 0, stream_iso_transfer_amount = 0;
	double stream_transfer_amount = 0;
	long ader_mat_iso = 0;
    long ader_mat_shadow = 0, ader_mat_src_mat = 0, ader_mat_stream_iso = 0;
    long ader_mat_sum_stream = 0, ader_mat_sum_stream_ent = 0, mat_ader_data = 0, mat_iso = 0;
    long src_mat_ader_data = 0;
    long rem_stream = 0;

    /* If this is a rem type stream and this is an adjustment cycle, skip this*/
    /* stream                                                                 */

    if(strncmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE), 3) == 0)
    {

    	rem_stream = 1;

    	if((adj > 0) || (i > 0))
    	{

        	return;

    	}

    }

    /* If this stream has summation streams, they contain the relevant info   */
    /* Ignore the parent stream and deal with the sum streams                 */

    ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    if(ader_mat_sum_stream_ent > VALID_PTR)
    {

    	while(ader_mat_sum_stream_ent > VALID_PTR)
    	{

    		ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

    		ADERProcessMaterialDiscStreamEffects(ader_mat_sum_stream, adj, i, mat);

    		ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);

    	}

    	return;

    }

    /* A material adens is needed to calculate the stream amounts. Get the    */
    /* adens from the source material. If this stream has a positive shadow   */
    /* pointer it has a separate source material. If not, it is the "source"  */
    /* even if it receiving material, it is the source because its atomic     */
    /* density is used for the stream amount calculation                      */

    if(rem_stream > 0)
    {

    	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    	src_mat_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

    }
    else
    {

        ader_mat_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

        if(ader_mat_shadow > VALID_PTR)
        {

        	ader_mat_src_mat = (long)RDB[ader_mat_shadow + ADER_MAT_STREAM_MAT_PTR];

        	src_mat_ader_data = (long)RDB[ader_mat_src_mat + MATERIAL_ADER_DATA];

        	src_mat_adens = RDB[src_mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

        }
        else
        {

        	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

        	src_mat_adens = RDB[mat_ader_data + ADER_MAT_PRE_STEP_ADENS];

        }

    }



    /* We need to know if the stream is brining in or taking out material     */

    /* We need to determine if the stream is leaving or entering the material */
    /* This is most easily done by comparing src and dest names               */

    if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
              GetText(mat + MATERIAL_PTR_NAME)) == 0)
    {

        /* Stream is leaving the material                                     */

        sign = -1.0;

    }
    else
    {

        /* Stream is entering the material                                    */

        sign = 1.0;

    }

    /* Store the stream transfer amount to reduce code complexity             */

    if(rem_stream > 0)
    {

    	stream_transfer_amount = sign *
    			                 RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] *
								 src_mat_adens;

    }
    else
    {

        if(adj > 0)
        {

        	stream_transfer_amount = sign *
        			                 RDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] *
    								 src_mat_adens;

        }
        else
        {

        	stream_transfer_amount = sign *
        			                 RDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] *
    								 src_mat_adens;

        }

    }

    /* Go ahead and update the material density.                              */

	WDB[mat + MATERIAL_ADENS] = RDB[mat + MATERIAL_ADENS] +
			                    stream_transfer_amount;

	/* Now, loop through the stream isotopes and update the material isotopes */
	/* accordingly                                                            */

	ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

	while(ader_mat_stream_iso > VALID_PTR)
	{

		/* Store the amount of the isotope moved                              */

	    if(rem_stream > 0)
	    {

	    	stream_iso_transfer_amount = sign *
	    			                     RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] *
									     src_mat_adens;

	    }
	    else
	    {

			stream_iso_transfer_amount = stream_transfer_amount *
					                     RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC];

	    }

		ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

		mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

		/* Adjust isotopic adens                                              */

		WDB[mat_iso + COMPOSITION_ADENS] = RDB[mat_iso + COMPOSITION_ADENS] +
				                           stream_iso_transfer_amount;

		ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

	}

}
