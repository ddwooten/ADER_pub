/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderaveragevalue.c                             */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calculates and returns the weighted average of the three     */
/*              values passed in. Based off of AverageTransmuXS              */
/*                                                                           */
/* Comments:This function is called from                                     */
/*                           ADERSetMaterialCompMatrixClusterMemRhoRowEntries*/
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERAverageValue:"

double ADERAverageValue(double bos_value, double eos_value, double ps1_value,
                        double t1, double t2, long dep)
{

    double average_value = 0, weight_bos = 0, weight_eos = 0, weight_ps1 = 0;

    /* The following comment and next three calculations are taken from       */
    /* AverageTransmuXS                                                       */

    /* average (integrate) general 2nd order polynomial from t1 to t2      */
    /* This works with lower order fits too, the higher order coefficient, */
    /* or rather the weights for them just are 0 */

    weight_bos = RDB[DATA_BURN_FIT_C2W2]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3 +
                 RDB[DATA_BURN_FIT_C1W2]*(t2*t2-t1*t1)/(t2-t1)/2 +
                 RDB[DATA_BURN_FIT_C0W2];

    weight_eos = RDB[DATA_BURN_FIT_C2W3]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3 +
                 RDB[DATA_BURN_FIT_C1W3]*(t2*t2-t1*t1)/(t2-t1)/2 +
                 RDB[DATA_BURN_FIT_C0W3];

    weight_ps1 = RDB[DATA_BURN_FIT_C2W1]*(t2*t2*t2-t1*t1*t1)/(t2-t1)/3 +
                 RDB[DATA_BURN_FIT_C1W1]*(t2*t2-t1*t1)/(t2-t1)/2 +
                 RDB[DATA_BURN_FIT_C0W1];

    average_value = weight_bos * bos_value + weight_eos * eos_value +
                    weight_ps1 * ps1_value;

    /* These are the situations in which an average value should not be       */
    /* calculated, rather it should be overwritten                            */

    if(((long)RDB[DATA_BURN_DECAY_CALC] == YES) ||
       ((long)RDB[dep + DEP_HIS_STEP_TYPE] == DEP_STEP_DEC_STEP) ||
       ((long)RDB[dep + DEP_HIS_STEP_TYPE] == DEP_STEP_DEC_TOT))
    {

        average_value = 0.0;

    }
    else if(average_value < 0.0)
    {

        average_value = bos_value;

    }

    return(average_value);

}
