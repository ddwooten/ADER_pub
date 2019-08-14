/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadaderkmindata.c                         */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Stores minimum k value criteria for ADER mod                 */
/*                                                                           */
/* Comments: Called by ReadInput                                             */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderKMinData:"

void ADERReadAderKMinData(char* fname, long line, char** params,
                          char* pname, long np)
{
    long ader_data_ptr = 0;
    long j = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /* Store the minimum k value */

    WDB[ader_data_ptr + ADER_K_MIN] = TestParam(pname, fname, line,
                                                params[j], PTYPE_REAL,
                                                0.0, 1E+08);
}
