/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateaderstreamentry.c                    */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles creation of streams entry memory.                    */
/*                                                                           */
/* Comments:ADERReadAderStreamData does all the data processing. This        */
/*          function is called from ReadInput                                */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderStreamEntry:"

void ADERCreateAderStreamEntry(char* fname, long line, char** params,
                              char* pname, long np)
{
    long ader_data_ptr = 0, stream_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new stream entry */

    stream_ptr = NewItem(ader_data_ptr + ADER_STREAMS_PTR, ADER_STREAM_BLOCK_SIZE);

    /* Populate stream entry data */

    ADERReadAderStreamData(fname, stream_ptr, j, line, params, pname, np);
}
