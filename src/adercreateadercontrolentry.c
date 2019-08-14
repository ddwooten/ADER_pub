/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreateadercontrolentry.c                   */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates memory block for ADER listing elements and isotopes  */
/*              to be fully accounted for by a materials group structure.    */
/*                                                                           */
/* Comments:ADERReadAderControlData does all the data processing. This       */
/*          function is called from ReadInput.                               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateAderControlEntry:"

void ADERCreateAderControlEntry(char* fname, long line, char** params,
                                char* pname, long np, char* word)
{
    long ader_data_ptr = 0, control_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Create new control table entry */
    control_ptr = NewItem(ader_data_ptr + ADER_CONTROL_PTR,
                        ADER_CONTROL_TBL_BLOCK_SIZE);

    /* Put name, file name and line number for error reporting later if needed */

    WDB[control_ptr + PARAM_PTR_NAME] = (double)PutText(word);
    WDB[control_ptr + PARAM_PTR_FNAME] = (double)PutText(fname);
    WDB[control_ptr + PARAM_LINE] = (double)line;

    /* Store the control table id */

    WDB[control_ptr + ADER_CONTROL_TBL_ID] = (double)PutText(params[j]);

    j++;

    /* Populate control entry data */

    ADERReadAderControlData(fname, control_ptr, j, line, params, pname, np);
}
