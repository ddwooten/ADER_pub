/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateaderremovalentry.c                     */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles creation of repro table memory. This table is tagged */
/*              as 'removal' in the actual input.                            */
/* Comments:ADERReadAderRemovalData does all the actual processing. This       */
/*          function is called from ReadInput.                               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderRemovalEntry:"

void ADERCreateAderRemovalEntry(char* fname, long line, char** params,
                              char* pname, long np, char* word)
{
    long ader_data_ptr = 0, repro_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new repro table entry */
    repro_ptr = NewItem(ader_data_ptr + ADER_REPROS_PTR,
                        ADER_REPRO_TBL_BLOCK_SIZE);

    /* Put name, file name and line number */

    WDB[repro_ptr + PARAM_PTR_NAME] = (double)PutText(word);
    WDB[repro_ptr + PARAM_PTR_FNAME] = (double)PutText(fname);
    WDB[repro_ptr + PARAM_LINE] = (double)line;

    /* Store repro table name */

    WDB[repro_ptr + ADER_REPRO_TBL_ID] = (double)PutText(params[j]);

    j++;

    /* Populate repro entry data */

    ADERReadAderRemovalData(fname, repro_ptr, j, line, params, pname, np);
}
