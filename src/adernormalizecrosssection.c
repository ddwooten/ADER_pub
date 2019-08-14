/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adernormalizecrosssection.c                    */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: If a material is under ADER control, and if it has reactivity*/
/*              control, this function will normalize the calculated         */
/*              absorption and fission*nu cross sections                     */
/*                                                                           */
/* Comments:This function is called from CalculateTransmuXS                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERNormalizeCrossSection:"

void ADERNormalizeCrossSection(double flx, long mat)
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

    /* Loop through a mat's ader isos and normalize their calculated xs       */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

        WDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] / flx;

        WDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR] / flx;

        WDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR] / flx;

        ader_mat_iso = NextItem(ader_mat_iso);

    }

}
