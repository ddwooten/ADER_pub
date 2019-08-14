/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialadercndoptdata.c            */
/*                                                                           */
/* Created:       2015/1/2 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Copies CND opt data to a material. Checks user input.        */
/*                                                                           */
/* Comments: This function is called from ADERProcessMaterialConditions      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMaterialAderCndOptData:"

void ADERProcessMaterialAderCndOptData(long ader_cnd_opt, long mat)
{

    long ader_mat_opt = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if((long)RDB[mat_ader_data + ADER_MAT_OPT_PTR] > VALID_PTR)
    {

        Error(0, "Attempting to add a SECOND 'opt' entry from a conditions block \n \
to material %s. A material may only have one 'opt' entry from a conditions block \n \
assigned to it. Additionally, an ADER 'cluster'* may only have one material with \n \
an 'opt' entry.\n \n *An ADER 'cluster' is a group of materials which are connected \n \
with ADER 'stream' entries. I.e., materials which are sources and sinks for one another.\n",
             GetText(mat + MATERIAL_PTR_NAME));

    }

    /* copy that optimization data! */

    ader_mat_opt = NewItem(mat_ader_data + ADER_MAT_OPT_PTR,
                           ADER_MAT_OPT_BLOCK_SIZE);

    WDB[ader_mat_opt + ADER_MAT_OPT_DIR] = RDB[ader_cnd_opt + ADER_CND_OPT_DIR];

    WDB[ader_mat_opt + ADER_MAT_OPT_TYPE] = RDB[ader_cnd_opt + ADER_CND_OPT_TYPE];

    WDB[ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET] = RDB[ader_cnd_opt + ADER_CND_OPT_TYPE_TARGET];

}
