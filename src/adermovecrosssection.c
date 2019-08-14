/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermovecrosssection.c                         */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Moves ADER cross section data from where it is stored to     */
/*              where it belongs                                             */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMoveCrossSection:"

void ADERMoveCrossSection(long mat, long step, long iter)
{

    long ader_mat_iso = 0, mat_ader_data = 0;

    /* If this material isn't under ADER control OR if it isn't involved in   */
    /* reactivity calculations, don't bother with this function               */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if(mat_ader_data < VALID_PTR)
    {

        return;

    }

    if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] <= 0.0)
    {

        return;

    }

    /* Loop through a mat's ader isos and move their calculated xs            */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

        ADERMoveBosEosPs1Values(ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_AVG,
                                ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR,
                                ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS,
                                ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS,
                                ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1,
                                mat, step, iter);

        ADERMoveBosEosPs1Values(ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_AVG,
                                ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR,
                                ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS,
                                ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS,
                                ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1,
                                mat, step, iter);

        ADERMoveBosEosPs1Values(ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_AVG,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_BOS,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_EOS,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_PS1,
                                mat, step, iter);

        ADERMoveBosEosPs1Values(ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_AVG,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_BOS,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_EOS,
                                ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_PS1,
                                mat, step, iter);

        ader_mat_iso = NextItem(ader_mat_iso);

    }

}
