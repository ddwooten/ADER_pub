/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateadergroupentry.c                     */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Handles creation of memory for new ADER groups.              */
/*                                                                           */
/* Comments:ADERReadAderGroupData does all the data processing. This function*/
/*          is called from ReadInput.                                        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderGroupEntry:"

void ADERCreateAderGroupEntry(char* fname, long line, char** params,
                              char* pname, long np, char* word)
{
    long ader_data_ptr = 0, group_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new item */

    group_ptr = NewItem(ader_data_ptr + ADER_GROUPS_PTR, ADER_GRP_BLOCK_SIZE);

    /* Put name, file name and line number */

    WDB[group_ptr + PARAM_PTR_NAME] = (double)PutText(word);
    WDB[group_ptr + PARAM_PTR_FNAME] = (double)PutText(fname);
    WDB[group_ptr + PARAM_LINE] = (double)line;

    /* Store group name */

    WDB[group_ptr + ADER_GRP_ID] = (double)PutText(params[j]);

    j++;

    /* Loop through remaining parameters, putting them in proper places */

    ADERReadAderGroupData(fname, group_ptr, j, line, params, pname, np);
}
