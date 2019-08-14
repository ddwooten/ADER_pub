/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetleakagecorrectionfactor.c               */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calculates, averages, and stores the leakage correction      */
/*              factor                                                       */
/*                                                                           */
/* Comments:This function is called from ADERGetTransportInformation         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetLeakageCorrectionFactor:"

void ADERGetLeakageCorrectionFactor(long dep, long i, long step)
{
    double k_eff = 0.0, k_inf = 0.0, leakage = 0;
    long mat = 0, mat_ader_data = 0;

    /* Get the system leakage                                                 */

    k_eff = Mean((long)RDB[RES_IMP_KEFF], 0);

    k_inf = Mean((long)RDB[RES_IMP_KINF], 0);

    if(fabs(((k_eff - k_inf) / k_inf)) < 0.00000001)
    {

    	leakage = 0.0;

    }
    else
    {

        leakage = (1.0 - (Mean((long)RDB[RES_IMP_KEFF], 0) / Mean((long)RDB[RES_IMP_KINF], 0)));

    }

    /* Cycle through the materials, give them this information if they need it*/
    /* If this material isn't under ADER control OR if it isn't involved in   */
    /* reactivity calculations, don't bother with this function               */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

        if(mat_ader_data < VALID_PTR)
        {

            mat = NextItem(mat);

            continue;

        }

        if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] <= 0.0)
        {

            mat = NextItem(mat);

            continue;

        }

        /* Store the calculated leakage                                       */

        WDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_CUR] = leakage;

        /* Move values to their appropriate holders                           */

        ADERMoveBosEosPs1Values(mat_ader_data + ADER_MAT_SYS_LEAKAGE_AVG,
                                mat_ader_data + ADER_MAT_SYS_LEAKAGE_CUR,
                                mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS,
                                mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS,
                                mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1,
                                mat, step, i);

        mat = NextItem(mat);

    }

}
