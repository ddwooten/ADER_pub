/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialcmpgroupcompmatrixsection.c  */
/*                                                                           */
/* Created:       2016/02/26 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Adds a column for a cmp group. If it is a sum group, also    */
/*              adds a row. Stores col and row information on cmp group      */
/*              If the cmp group has a ratio, adds rows for this as well     */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialCmpGroupCompMatrixSection:"

void ADERCreateMaterialCmpGroupCompMatrixSection(long ader_mat_cmp,
                                                 long ader_mat_matrix_data)
{

    double ader_mat_cmp_rto_max = 0;
    long ader_mat_cmp_col = 0, ader_mat_cmp_rng = 0, ader_mat_cmp_row = 0, ader_mat_cmp_rto = 0;

    /* Check to see if this cmp group has restrictions on its fraction of the material */

    ader_mat_cmp_rng = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RNG_PTR];

    if(ader_mat_cmp_rng > VALID_PTR)
    {
        /* If it does.... */
        /* Create the row for the cmp group, give the bounds, and return the index */

         ader_mat_cmp_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                            RDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MIN],
                                                            RDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MAX]);

         WDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID] = (double)ader_mat_cmp_col;

    }
    else
    {

        /* If it doesn't, create a column for it anyway and give it reasonable bounds */

         ader_mat_cmp_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                            0.0,
                                                            1E+18);

         WDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID] = (double)ader_mat_cmp_col;
    }

    ader_mat_cmp_rto = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RTOS_PTR];

    /* Check if this cmp group has ratios with any other cmp group */

    while(ader_mat_cmp_rto > VALID_PTR)
    {

        ader_mat_cmp_rto_max = RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX];

        /* this tests to see if the ratio was input as a single value ratio */
        /* If so, we only need one row, with equal bounds, to handle this ratio */
        /* If not, we need two rows                                         */

        if(ader_mat_cmp_rto_max < 0.0)
        {

             ader_mat_cmp_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                                0.0, 0.0);

             WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN_ROW_ID] = (double)ader_mat_cmp_row;

             /* We mark the row for the max as negative to avoid processing   */
             /* it later                                                      */

             WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID] = -1.0;

        }
        else
        {

             ader_mat_cmp_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                                -1E+18, 0.0);

             WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN_ROW_ID] = (double)ader_mat_cmp_row;

             ader_mat_cmp_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                                0.0, 1E+18);

             WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID] = (double)ader_mat_cmp_row;

        }

        ader_mat_cmp_rto = NextItem(ader_mat_cmp_rto);

    }

    /* Check is the cmp group is a summation group. If so, give it a row as well */

    if((long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR] > VALID_PTR)
    {

         ader_mat_cmp_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data, 0.0, 0.0);

         WDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID] = (double)ader_mat_cmp_row;

    }
    else
    {

        /* Otherwise we mark it negative to avoid processing it later         */

        WDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID] = -1.0;

    }

}
