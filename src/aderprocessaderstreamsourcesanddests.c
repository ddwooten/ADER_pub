/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessaderstreamsourcesanddests.c         */
/*                                                                           */
/* Created:       2015/12/8 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Sets a streams source or dest to null if there is no data.   */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderStreams              */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderStreamSourcesAndDests:"

void ADERProcessAderStreamSourcesAndDests(long ader_strm)
{

    if(RDB[ader_strm + ADER_STREAM_DEST] < VALID_PTR)
    {

        WDB[ader_strm + ADER_STREAM_DEST] = (double)PutText("NULL");

    }

    if(RDB[ader_strm + ADER_STREAM_SRC] < VALID_PTR)
    {

        WDB[ader_strm + ADER_STREAM_SRC] = (double)PutText("NULL");

    }

}
