/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcmprtocompmatrixsection.c      */
/*                                                                           */
/* Created:       2016/03/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Sets the passed in group's value to 1 in the matrix for the  */
/*              min, and max if it exists, rto row. Gets column id for second*/
/*              group and sets it's values accordingly.                      */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialCmpGroupCompMatrixSection                        */
/*          For an explanation of how ratios are handled, mathematically, in */
/*          the ADER modification please see the user's manual.              */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCmpRtoCompMatrixSection:"

void ADERFillMaterialCmpRtoCompMatrixSection(long ader_mat_cmp_rto,
                                             long ader_mat_matrix_data,
                                             long ader_mat_matrix_first_col_id,
                                             long mat_ader_data)
{

    long ader_mat_sec_cmp = 0, ader_mat_matrix_sec_col_id = 0;

    /* Go ahead and set the value for the first group, this group's value is  */
    /* always 1                                                               */

    ADERSetMaterialCompMatrixElement(ader_mat_matrix_first_col_id,
                                     (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN_ROW_ID],
                                     ader_mat_matrix_data,
                                     -1.0);

    /* If there is a max row, set the value for the first group               */

    if((long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID] > 0)
    {

        ADERSetMaterialCompMatrixElement(ader_mat_matrix_first_col_id,
                                         (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID],
                                         ader_mat_matrix_data,
                                         -1.0);

    }

    /*Now that the first group is set, deal with the second group in the ratio*/

    ader_mat_sec_cmp = (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

    ader_mat_matrix_sec_col_id = (long)RDB[ader_mat_sec_cmp + ADER_MAT_CMP_COL_ID];

    /* There is always a 'min' rto value, if it's the only one, this is a     */
    /* single value ratio                                                     */

    ADERSetMaterialCompMatrixElement(ader_mat_matrix_sec_col_id,
                                     (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN_ROW_ID],
                                     ader_mat_matrix_data,
                                     RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN]);

    /* If there is a max row, set the value for the first group               */

    if((long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID] > 0)
    {

        ADERSetMaterialCompMatrixElement(ader_mat_matrix_sec_col_id,
                                         (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID],
                                         ader_mat_matrix_data,
                                         RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX]);

    }

}
