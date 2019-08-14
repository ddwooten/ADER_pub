/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetmaterialremovalamounts.c                */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function loops through a material's streams, finds rem  */
/*              type streams and calls a function to calculate and store the */
/*              estimated amount to be removed. Ignores dest end of shadow   */
/*              streams, the source end will pass this information to them   */
/*                                                                           */
/* Comments:This function is called from ADEROpeateMaterial                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetMaterialRemovalAmounts:"

void ADERGetMaterialRemovalAmounts(long mat, long i, double t1, double t2)
{

    long ader_mat_stream = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Loop through all the material's streams                                */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

        	/* Ignore the destination end of linked streams, they don't have  */
        	/* the material composition data to calculate the numbers right   */
        	/* source ends have negative pointers to the destination stream   */

        	if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] <= 0)
        	{

                ADERGetStreamRemovalAmounts(ader_mat_stream, mat, mat_ader_data, t1,
                                            t2);

        	}

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

        	/* Ignore the destination end of linked streams, they don't have  */
        	/* the material composition data to calculate the numbers right   */
        	/* source ends have negative pointers to the destination stream   */

        	if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] <= 0)
        	{

                ADERGetStreamRemovalAmounts(ader_mat_stream, mat, mat_ader_data, t1,
                                            t2);

        	}

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

        	/* Ignore the destination end of linked streams, they don't have  */
        	/* the material composition data to calculate the numbers right   */
        	/* source ends have negative pointers to the destination stream   */

        	if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] <= 0)
        	{

                ADERGetStreamRemovalAmounts(ader_mat_stream, mat, mat_ader_data, t1,
                                            t2);

        	}

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) &&
           ((i == 0) || (strcmp("disc", GetText(ader_mat_stream + ADER_MAT_STREAM_FORM)) != 0)))
        {

        	/* Ignore the destination end of linked streams, they don't have  */
        	/* the material composition data to calculate the numbers right   */
        	/* source ends have negative pointers to the destination stream   */

        	if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] <= 0)
        	{

                ADERGetStreamRemovalAmounts(ader_mat_stream, mat, mat_ader_data, t1,
                                            t2);

        	}

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
