/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialcndrngdata.c                */
/*                                                                           */
/* Created:       2016/1/1 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Assigns ader range condition entries to material composition */
/*              groups.                                                      */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialCndData      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialCndRngData:"

void ADERProcessMaterialCndRngData(long ader_cnd_rng, long ader_mat_cmp,
                                   long mat)
{

    char *ader_cnd_rng_grp_id = NULL, *mat_id = NULL;
    long ader_mat_cmp_rng = 0;

    if(RDB[ader_mat_cmp + ADER_MAT_CMP_RNG_PTR] > VALID_PTR)
    {

        ader_cnd_rng_grp_id = GetText(ader_cnd_rng + ADER_CND_RNG_GRP_ID);

        mat_id = GetText(mat + MATERIAL_PTR_NAME);

        Error(0, "More than one range condition entered for group %s \n \
in material %s.\n", ader_cnd_rng_grp_id, mat_id);

    }

    /* Add new range data to a material cmp group */

    ader_mat_cmp_rng = NewItem(ader_mat_cmp + ADER_MAT_CMP_RNG_PTR,
                               ADER_MAT_CMP_RNG_BLOCK_SIZE);

    WDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MAX] = RDB[ader_cnd_rng +
                                                       ADER_CND_RNG_MAX];

    WDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MIN] = RDB[ader_cnd_rng +
                                                           ADER_CND_RNG_MIN];


}

