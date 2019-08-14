/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessaderstreams.c                       */
/*                                                                           */
/* Created:       2015/12/8 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to condition ADER stream data                */
/*                                                                           */
/* Comments:This function is called from ADERProcessAderMainData             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderStreams:"

void ADERProcessAderStreams()
{

    long ader_data = 0, ader_strm = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_strm = (long)RDB[ader_data + ADER_STREAMS_PTR];

    while(ader_strm > VALID_PTR)
    {

        ADERProcessAderStreamSourcesAndDests(ader_strm);

        ader_strm = NextItem(ader_strm);

    }

}
