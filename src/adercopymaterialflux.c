/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercopymaterialflux.c                         */
/*                                                                           */
/* Created:       2016/04/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Copies averaging values for various material fluxes for use  */
/*              SIE burnup modes.                                            */
/*                                                                           */
/* Comments:This function is called from StoreTransmuXS                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCopyMaterialFlux:"

void ADERCopyMaterialFlux(double flx, double flx_new_avg, double flx_old_avg,
                          long mat)
{

    long mat_ader_data = 0;

    /* Check to see if material is under ADER control, if not, return         */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if(mat_ader_data < VALID_PTR)
    {

        return;

    }

    WDB[mat_ader_data + ADER_MAT_FLUX] = flx;

    WDB[mat_ader_data + ADER_MAT_FLUX_NEW_AVG] = flx_new_avg;

    WDB[mat_ader_data + ADER_MAT_FLUX_OLD_AVG] = flx_old_avg;

}
