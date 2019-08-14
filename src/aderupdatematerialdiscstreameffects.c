/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderupdatematerialdiscstreameffects.c          */
/*                                                                           */
/* Created:       2016/10/19 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's streams updating it's isotopic    */
/*              composition and density due to changes induced by discreet   */
/*              streams                                                      */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERUpdateMaterialDiscStreamEffects:"

void ADERUpdateMaterialDiscStreamEffects(long adj, long i, long mat)
{

    long ader_mat_stream = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* If this material is not an ader material, exit this function           */

    if(mat_ader_data < VALID_PTR)
    {

    	return;

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    /* These next four while loops are to process the different streams in */
    /* a material */

    while(ader_mat_stream > VALID_PTR)
    {

    	/* If the stream is a disc type, update the material                  */

    	if(strncmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) == 0)
    	{

    		ADERProcessMaterialDiscStreamEffects(ader_mat_stream, adj, i, mat);

    	}

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	/* If the stream is a disc type, update the material                  */

    	if(strncmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) == 0)
    	{

    		ADERProcessMaterialDiscStreamEffects(ader_mat_stream, adj, i, mat);

    	}

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	/* If the stream is a disc type, update the material                  */

    	if(strncmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) == 0)
    	{

    		ADERProcessMaterialDiscStreamEffects(ader_mat_stream, adj, i, mat);

    	}

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	/* If the stream is a disc type, update the material                  */

    	if(strncmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM), 4) == 0)
    	{

    		ADERProcessMaterialDiscStreamEffects(ader_mat_stream, adj, i, mat);

    	}

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(RDB[mat + MATERIAL_ADENS] < 0.0)
    {

    	Error(0,"ADER_ERROR: Application of discrete stream changes to material\n\
density in function ADERUpdateMaterialDiscStreamEffects, following the\n\
solution of the material composition optimization problem, have caused the\n\
material density to be negative. This is most likely the result of a\n\
simulation with mixed discrete and non-discrete streams. The affected\n\
material is %s.\n", GetText(mat + MATERIAL_PTR_NAME));

    }

}
