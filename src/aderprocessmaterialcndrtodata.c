/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialcndrtodata.c                */
/*                                                                           */
/* Created:       2016/1/2 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Assigns ader ratio condition entries to material composition */
/*              groups.                                                      */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialCndCmpData      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialCndRtoData:"

void ADERProcessMaterialCndRtoData(long ader_cnd_rto, long ader_mat_cmp,
                                   long mat)
{

    char *ader_cnd_rto_grp2_id = NULL;
    long ader_mat_cmp_rto = 0;

    /* Add an rto entry to a material composition control group */

    ader_mat_cmp_rto = NewItem(ader_mat_cmp + ADER_MAT_CMP_RTOS_PTR,
                               ADER_MAT_CMP_RTO_BLOCK_SIZE);

    WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX] = RDB[ader_cnd_rto +
                                                       ADER_CND_RTO_MAX];

    WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN] = RDB[ader_cnd_rto +
                                                           ADER_CND_RTO_MIN];

    ader_cnd_rto_grp2_id = GetText(ader_cnd_rto + ADER_CND_RTO_GRP2_ID);

    /* Provide index of the other group involved in this ratio */

    WDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR] = (double)ADERProcessMaterialCndGroupData(ader_cnd_rto_grp2_id, mat);

}

