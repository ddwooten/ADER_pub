/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergettargetremovalamount.c                   */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function loops through a material's streams, finds rem  */
/*              type streams and calls a function to accumulate the amount   */
/*              of a target, element or isotope, that is removed by rem      */
/*              streams. It accumulates the net amount.                      */
/*                                                                           */
/* Comments:This function is called from ADEROutputMaterialCompMatrixData    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetTargetRemovalAmount:"

double ADERGetTargetRemovalAmount(long mat, long ele, long iso)
{

	double removal_amount = 0.0;
    long ader_mat_stream = 0, mat_ader_data = 0, sign = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Loop through all the material's streams                                */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

        	/* Determine if this stream is removing or adding material        */

        	if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
        			  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		sign = -1;

        	}
        	else
        	{

        		sign = 1;
        	}

        	/* Get the info from this stream                                  */

        	removal_amount = ADERGetStreamTargetRemovalAmount(ader_mat_stream,
        			                                          ele, iso) * sign + removal_amount;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

        	/* Determine if this stream is removing or adding material        */

        	if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
        			  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		sign = -1;

        	}
        	else
        	{

        		sign = 1;
        	}

        	/* Get the info from this stream                                  */

        	removal_amount = ADERGetStreamTargetRemovalAmount(ader_mat_stream,
        			                                          ele, iso) * sign + removal_amount;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

        	/* Determine if this stream is removing or adding material        */

        	if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
        			  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		sign = -1;

        	}
        	else
        	{

        		sign = 1;
        	}

        	/* Get the info from this stream                                  */

        	removal_amount = ADERGetStreamTargetRemovalAmount(ader_mat_stream,
        			                                          ele, iso) * sign + removal_amount;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
        {

        	/* Determine if this stream is removing or adding material        */

        	if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
        			  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		sign = -1;

        	}
        	else
        	{

        		sign = 1;
        	}

        	/* Get the info from this stream                                  */

        	removal_amount = ADERGetStreamTargetRemovalAmount(ader_mat_stream,
        			                                          ele, iso) * sign + removal_amount;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    return(removal_amount);

}
