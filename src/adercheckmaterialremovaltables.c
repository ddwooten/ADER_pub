/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercheckmaterialremovaltables.c               */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls function to check that no removal tables have the      */
/*              same isotopes.                                               */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                       ADERCheckMaterialRemovalTables      */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCheckMaterialRemovalTables:"

void ADERCheckMaterialRemovalTables(long mat, long passed_ader_mat_stream)
{

    long ader_mat_stream = 0, mat_ader_data = 0;

    /* Get the mat_ader_data                                                  */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Loop through the material's streams                                    */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        /* Only be concerned with removal table streams                       */

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Furthermore, only be concerned if the stream's source is this      */
        /* material                                                           */

        if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Here's the recursive magic. If there is a passed in stream,        */
        /* compare the two. If not, pass in a stream                          */

        if(passed_ader_mat_stream > VALID_PTR)
        {

        	/* Don't want to compare the same removal table...                */

        	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
        			  GetText(passed_ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

                ADERCompareMaterialRemovalTables(ader_mat_stream, mat,
                                                 passed_ader_mat_stream);

        	}

        }
        else
        {

            ADERCheckMaterialRemovalTables(mat, ader_mat_stream);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        /* Only be concerned with removal type streams                        */

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Furthermore, only be concerned if the stream's source is this      */
        /* material                                                           */

        if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Here's the recursive magic. If there is a passed in stream,        */
        /* compare the two. If not, pass in a stream                          */

        if(passed_ader_mat_stream > VALID_PTR)
        {

        	/* Don't want to compare the same removal table...                */

        	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
        			  GetText(passed_ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

                ADERCompareMaterialRemovalTables(ader_mat_stream, mat,
                                                 passed_ader_mat_stream);

        	}

        }
        else
        {

            ADERCheckMaterialRemovalTables(mat, ader_mat_stream);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        /* Only be concerned with removal type streams                        */

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Furthermore, only be concerned if the stream's source is this      */
        /* material                                                           */

        if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Here's the recursive magic. If there is a passed in stream,        */
        /* compare the two. If not, pass in a stream                          */

        if(passed_ader_mat_stream > VALID_PTR)
        {

        	/* Don't want to compare the same removal table...                */

        	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
        			  GetText(passed_ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

                ADERCompareMaterialRemovalTables(ader_mat_stream, mat,
                                                 passed_ader_mat_stream);

        	}

        }
        else
        {

            ADERCheckMaterialRemovalTables(mat, ader_mat_stream);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        /* Only be concerned with removal type streams                        */

        if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Furthermore, only be concerned if the stream's source is this      */
        /* material                                                           */

        if(strcmp(GetText(mat + MATERIAL_PTR_NAME),
                  GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) != 0)
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Here's the recursive magic. If there is a passed in stream,        */
        /* compare the two. If not, pass in a stream                          */

        if(passed_ader_mat_stream > VALID_PTR)
        {

        	/* Don't want to compare the same removal table...                */

        	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
        			  GetText(passed_ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        	{

                ader_mat_stream = NextItem(ader_mat_stream);

                continue;

        	}
        	else
        	{

                ADERCompareMaterialRemovalTables(ader_mat_stream, mat,
                                                 passed_ader_mat_stream);

        	}

        }
        else
        {

            ADERCheckMaterialRemovalTables(mat, ader_mat_stream);

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
