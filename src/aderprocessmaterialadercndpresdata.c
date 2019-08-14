/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialadercndpresdata.c           */
/*                                                                           */
/* Created:       2016/3/20 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Copies CND pres data to a material. Checks user input.       */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialConditions      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderCndPresData:"

void ADERProcessMaterialAderCndPresData(long ader_cnd_pres, long mat)
{

    long ader_mat_preserve = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* copy that preserve data! */

    ader_mat_preserve = NewItem(mat_ader_data + ADER_MAT_PRESERVES_PTR,
                               ADER_MAT_PRESERVE_BLOCK_SIZE);

    WDB[ader_mat_preserve + ADER_MAT_PRESERVE_ENT] = RDB[ader_cnd_pres + ADER_CND_PRES_ENT];

}
