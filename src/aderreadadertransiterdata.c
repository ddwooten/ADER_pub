/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadertransiterdata.c                    */
/*                                                                           */
/* Created:       2016/04/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Stores maximum transport calculation iterations              */
/*                                                                           */
/* Comments: Called by ReadInput                                             */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderTransIterData:"

long ADERReadAderTransIterData(char* fname, long line, char** params,
                               char* pname, long np, long k)
{
    long ader_data_ptr = 0;

    /*Get ADER data block address */

    ader_data_ptr = (long)RDB[DATA_PTR_ADER];

    /*Store the maximum transport calculation iteration */

    WDB[ader_data_ptr + ADER_TRANS_ITER] = TestParam(pname, fname, line,
                                                    params[k], PTYPE_INT,
                                                    0, 100000);

    /* Increment k to indicate successful assignment */

    k = k + 1;

    return k;

}
