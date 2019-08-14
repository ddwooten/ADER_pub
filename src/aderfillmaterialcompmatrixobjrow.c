/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcompmatrixobjrow.c             */
/*                                                                           */
/* Created:       2016/03/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to incorporate the objective function into   */
/*              into the material comp matrix depending on the objective     */
/*              function parameters given by the user                        */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                       TestCases                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCompMatrixObjRow:"

void ADERFillMaterialCompMatrixObjRow(long mat)
{

    long ader_mat_opt = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    /* Check what opt options the user set, or the default, call appropriate function */

    if(strcmp("action", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE)) == 0)
    {

        if(strcmp("feed", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActFeedCompMatrixSection(mat);

        }
        else if(strcmp("feed_and_remv", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActFeedAndRemvCompMatrixSection(mat);

        }
        else if(strcmp("reac", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActReacCompMatrixSection(mat);

        }
        else if(strcmp("redox", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActRedoxCompMatrixSection(mat);

        }
        else if(strcmp("remv", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActRemvCompMatrixSection(mat);

        }
        else if(strcmp("streams", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActStreamsCompMatrixSection(mat);

        }
        else if(strcmp("transfers", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET)) == 0)
        {

            ADERFillMaterialObjActTransfersCompMatrixSection(mat);

        }
        else
        {

            Error(0, "Opt type and target pair, (%s, %s), for material %s\n \
does not match any acceptable input for these options. Please consult the user's\n \
manual. Currently acceptable input for opt type and target pairs include...\n \
action, feed \n action, feed_and_remv \n action, reac \n action, redox \n \
action, remv \n action, transfers \n \
grp, [name of group assigned to material by 'conditions' block] \n \
spec_stream, [name of stream assigned to material]\n\n",
                  GetText(ader_mat_opt + ADER_MAT_OPT_TYPE),
                  GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET),
                  GetText(mat + MATERIAL_PTR_NAME));

        }

    }
    else if(strcmp("group", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE)) == 0)
    {

        ADERFillMaterialObjGrpCompMatrixSection(GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET), mat);

    }
    else if(strcmp("spec_stream", GetText(ader_mat_opt + ADER_MAT_OPT_TYPE)) == 0)
    {

        ADERFillMaterialObjStreamCompMatrixSection(GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET), mat);

    }
    else
    {

        Error(0, "Opt type and target pair, (%s, %s), for material %s\n \
does not match any acceptable input for these options. Please consult the user's\n \
manual. Currently acceptable input for opt type and target pairs include...\n \
action, feed \n action, feed_and_remv \n action, reac \n action, redox \n \
action, remv \n action, transfers \n \
grp, [name of group assigned to material by 'conditions' block] \n \
spec_stream, [name of stream assigned to material]\n\n",
              GetText(ader_mat_opt + ADER_MAT_OPT_TYPE),
              GetText(ader_mat_opt + ADER_MAT_OPT_TYPE_TARGET),
              GetText(mat + MATERIAL_PTR_NAME));

    }

}
