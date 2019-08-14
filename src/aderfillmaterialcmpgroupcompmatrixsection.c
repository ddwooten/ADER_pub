/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcmpgroupcompmatrixsection.c    */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to fill in elemental and isotopic fraction   */
/*              data from composition groups in to the element and isotope   */
/*              rows of the comp matrix. Additionally calls functions to     */
/*              handle any ratios associated with the comp group as well as  */
/*              any summation entries.                                       */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCmpGroupCompMatrixSection:"

void ADERFillMaterialCmpGroupCompMatrixSection(long ader_mat_cmp,
                                               long ader_mat_matrix_data,
                                               long mat_ader_data)
{

    long ader_mat_cmp_col = 0, ader_mat_cmp_ele = 0, ader_mat_cmp_iso = 0, ader_mat_cmp_rto = 0;

    ader_mat_cmp_col = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID];

    /* We grab the first element in the group's elemental list and pass it to */
    /* the elemental processing function. */

    ader_mat_cmp_ele = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_ELES_PTR];

    ADERFillMaterialCompMatrixEleData(ader_mat_cmp_ele, ader_mat_cmp_col,
                                      ader_mat_matrix_data, mat_ader_data, 1.0, 1, 1);

    /* We grab the first isotope in the group's elemental list and pass it to */
    /* the isotopic processing function. */

    ader_mat_cmp_iso = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_ISOS_PTR];

    ADERFillMaterialCompMatrixIsoData(ader_mat_cmp_iso, ader_mat_cmp_col,
                                      ader_mat_matrix_data, mat_ader_data, 1.0, 1, 1);

    /* If the group has any ratios, deal with those */

    ader_mat_cmp_rto = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RTOS_PTR];

    while(ader_mat_cmp_rto > VALID_PTR)
    {

        ADERFillMaterialCmpRtoCompMatrixSection(ader_mat_cmp_rto,
                                                ader_mat_matrix_data,
                                                ader_mat_cmp_col,
                                                mat_ader_data);

        ader_mat_cmp_rto = NextItem(ader_mat_cmp_rto);

    }

    /* If the group is a summation group, deal with that */

    if((long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR] > VALID_PTR)
    {

        ADERFillMaterialCmpSumCompMatrixSection(ader_mat_cmp,
                                                ader_mat_matrix_data,
                                                mat_ader_data);

    }

}
