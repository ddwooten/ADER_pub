/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergettransportinformation.c                  */
/*                                                                           */
/* Created:       2016/04/08 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls various functions to get transmutation cross sections  */
/*              for isotopes as well as the system wide leakage              */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetTransportInformation:"

void ADERGetTransportInformation(long dep, long i, long step)
{

    long mat = 0, omp_id = 0, step_type = 0;

    omp_id = OMP_THREAD_NUM;

    step_type = (long)RDB[dep + DEP_HIS_STEP_TYPE];

    /* Gather the transmutation cross sections ( as well as nu-bar ) for  */
    /* each material that is involved in an ader calculation              */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR) &&
           RDB[(long)RDB[mat + MATERIAL_ADER_DATA] + ADER_MAT_RHO_WEIGHT] > 0.0)
        {

            /* Calculate transmutation cross sections */

            CalculateTransmuXS(mat, omp_id);

            /* Store the xs from above */

            StoreTransmuXS(mat, step, step_type, omp_id, i);

        }

        mat = NextItem(mat);

    }

    /* Get the leakage correction factor                                  */

    ADERGetLeakageCorrectionFactor(dep, i, step);

}
