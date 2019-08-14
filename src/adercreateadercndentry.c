/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateadercndentry.c                       */
/*                                                                           */
/* Created:       2015/11/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles creation of ader "conditions" memory block           */
/*                                                                           */
/* Comments: Cnd is conditions abbreviated. ADERReadAderCndData does all the */
/*           processing. This function is called from ReadInput              */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderCndEntry:"

void ADERCreateAderCndEntry(char* fname, long line, char** params,
                            char* pname, long np, char* word)
{
    long ader_data_ptr = 0, cnd_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new conditions item */

    cnd_ptr = NewItem(ader_data_ptr + ADER_CONDITIONS_PTR, ADER_CND_BLOCK_SIZE);

    /* Put name, file name and line number */

    WDB[cnd_ptr + PARAM_PTR_NAME] = (double)PutText(word);
    WDB[cnd_ptr + PARAM_PTR_FNAME] = (double)PutText(fname);
    WDB[cnd_ptr + PARAM_LINE] = (double)line;

    /* Store the conditions block id name */

    WDB[cnd_ptr + ADER_CND_ID] = (double)PutText(params[j]);

    j++;

    /* Call below function to deal with actual data handling */

    ADERReadAderCndData(fname, cnd_ptr, j, line, params, pname, np);
}
