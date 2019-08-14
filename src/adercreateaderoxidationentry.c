/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateaderoxidationentry.c                 */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles creation of oxidation entry memory and data pop      */
/*                                                                           */
/* Comments:ADERReadAderOxidationData does all the data processing. This     */
/*          function is called from ReadInput.                               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderOxidationEntry:"

void ADERCreateAderOxidationEntry(char* fname, long line, char** params,
                                  char* pname, long np, char* word)
{
    long ader_data_ptr = 0, oxidation_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new oxidation table entry */
    oxidation_ptr = NewItem(ader_data_ptr + ADER_OXIS_PTR,
                            ADER_OXI_TBL_BLOCK_SIZE);

    /* Put name, file name and line number */

    WDB[oxidation_ptr + PARAM_PTR_NAME] = (double)PutText(word);
    WDB[oxidation_ptr + PARAM_PTR_FNAME] = (double)PutText(fname);
    WDB[oxidation_ptr + PARAM_LINE] = (double)line;

    /* Store oxidation table name */

    WDB[oxidation_ptr + ADER_OXI_TBL_ID] = (double)PutText(params[j]);

    j++;

    /* Populate oxidation entry data */

    ADERReadAderOxidationData(fname, oxidation_ptr, j, line, params, pname, np);
}
