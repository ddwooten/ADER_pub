/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcmpsumcompmatrixsection.c      */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a composition groups summation groups and fills*/
/*              the given ader_mat_matrix with the necessary data for        */
/*              handling summation groups in the linear optimization scheme  */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialCmpGroupCompMatrixSection                        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCmpSumCompMatrixSection:"

void ADERFillMaterialCmpSumCompMatrixSection(long ader_mat_cmp,
                                             long ader_mat_matrix_data,
                                             long mat_ader_data)
{

    long ader_mat_cmp_sum_ent = 0, ader_mat_cmp_sum_grp = 0;

    /* Go ahead and set the parent group's ( the one passed in ) value to 1   */
    /* in the matrix                                                          */

    ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID],
                                     (long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID],
                                     ader_mat_matrix_data,
                                     1.0);

    /* Now, loop through the comp group's sum groups, setting their matrix    */
    /* matrix values                                                          */

    ader_mat_cmp_sum_ent = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR];

    while(ader_mat_cmp_sum_ent > VALID_PTR)
    {

        ader_mat_cmp_sum_grp = (long)RDB[ader_mat_cmp_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_cmp_sum_grp + ADER_MAT_CMP_COL_ID],
                                         (long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID],
                                         ader_mat_matrix_data,
                                         -RDB[ader_mat_cmp_sum_ent + ADER_MAT_GRP_SUM_GRP_WEIGHT]);

        ader_mat_cmp_sum_ent = NextItem(ader_mat_cmp_sum_ent);

    }

}
