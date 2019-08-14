/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadernegadens.c                         */
/*                                                                           */
/* Created:       2016/09/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Sets negative isotopic density handling flag*/
/*                                                                           */
/* Comments: Called by ReadInput                                             */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderNegAdens:"

void ADERReadAderNegAdens(char* fname, long line, char** params,
                               char* pname, long np)
{
    long ader_data_ptr = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /*Store the maximum transport calculation iteration */

    WDB[ader_data_ptr + ADER_NEG_ADENS_OPT] = 1.0;

    return;

}
