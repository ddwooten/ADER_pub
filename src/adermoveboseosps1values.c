/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermoveboseosps1values.c                      */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Moves the values at the passed in indices according to the   */
/*              current step and step type                                   */
/*                                                                           */
/* Comments:This function is called from ADERMoveCrossSection                */
/*                                       ADERGetLeakageCorrectionFactor      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMoveBosEosPs1Values:"

void ADERMoveBosEosPs1Values(long avg_index, long cur_index, long bos_index,
                             long eos_index, long ps1_index, long mat,
                             long step, long iter)
{

    double flux = 0, flux_new_avg = 0, flux_old_avg = 0, new_avg = 0;
    long mat_ader_data = 0, num_corrector_iter = 0;

    /* This top section modifies the avg value during a corrector iteration   */
    /* when using the SIE method for burnup stepping                          */

    if(((long)RDB[DATA_BURN_SIE] == YES) &&
       ((long)RDB[DATA_BURN_STEP_PC] == CORRECTOR_STEP))
    {

        /* If using BurnMaterialsCI do not average                            */

        if((long)RDB[DATA_BURN_CI_FLAG] == YES)
        {

            num_corrector_iter = 1;

        }
        else
        {

            num_corrector_iter = RDB[DATA_BURN_CI_I] + 1;

        }

        /* Get data                                                           */

        mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

        flux = RDB[mat_ader_data + ADER_MAT_FLUX];

        flux_new_avg = RDB[mat_ader_data + ADER_MAT_FLUX_NEW_AVG];

        flux_old_avg = RDB[mat_ader_data + ADER_MAT_FLUX_OLD_AVG];

        /* If there was flux, get a new average, otherwise, set to 0          */

        if(flux_new_avg > 0.0)
        {

            new_avg = ((num_corrector_iter - 1) * flux_old_avg * RDB[avg_index] +
                        flux * RDB[cur_index]) /
                      (flux_new_avg * num_corrector_iter);

        }
        else
        {

            new_avg = 0.0;

        }

        /* If there was a flux this past iteration, store the value. Otherwise*/
        /* do not update                                                      */

        if(flux > 0.0)
        {

            WDB[eos_index] = new_avg;

        }
        else
        {

            WDB[eos_index] = RDB[avg_index];

        }

        /* If this is not a CI iteration, and if there was a contribution,    */
        /* update the aveage                                                  */

        if(((long)RDB[DATA_BURN_CI_FLAG] == NO) && (flux > 0.0))
        {

           WDB[avg_index] = new_avg;

        }

        /* Clear the accumulation slot                                        */

        WDB[cur_index] = 0.0;

        /* No more action needed                                              */

        return;

    }

    if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
    {

        if(step == 0)
        {

            /* Values are accumulated in cur, move them to where they belong  */

            WDB[bos_index] = RDB[cur_index];

            /* Clean cur for future use                                       */

            WDB[cur_index] = 0.0;

            /* First step of predictor, both PS1 and EOS are set to -INFTY    */

            WDB[eos_index] = -INFTY;

            WDB[ps1_index] = -INFTY;

        }
        else
        {

            if(iter == 0)
            {

                /* This is needed to prevent the ps1 value from being         */
                /* overwritten by multiple calculations of the bos value      */

                WDB[ps1_index] = RDB[bos_index];

            }

            WDB[bos_index] = RDB[cur_index];

            WDB[cur_index] = 0.0;

            WDB[eos_index] = -INFTY;

        }

    }
    else
    {

        /* This is a corrector step, a few changes                            */

        WDB[eos_index] = RDB[cur_index];

        WDB[cur_index] = 0.0;

    }

}
