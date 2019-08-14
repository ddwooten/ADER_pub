/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercorrecttransportcycle.c                    */
/*                                                                           */
/* Created:       2016/04/08 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls various functions to correct material composition      */
/*              according to the ADER solution. Calls additional transport   */
/*              cycles to account for changes in material composition.       */
/*                                                                           */
/* Comments:This function is called from BurnupCycle                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCorrectTransportCycle:"

void ADERCorrectTransportCycle(long dep, long step)
{

    long ader_data = 0, i = 0, mat = 0, omp_id = 0;

    omp_id = OMP_THREAD_NUM;

    ader_data = (long)RDB[DATA_PTR_ADER];

    /* The following two function are called here, rather than having been    */
    /* moved in BunrnupCycle, to avoid developer confusion. Their results     */
    /* should not change between calls within the same step, so it simply     */
    /* incurs the computational cost of an unneeded call                      */

    /* Calculate coefficients for the fit to xs/flux/power */

    DepletionPolyFit(dep, step);

    /* Set depletion step size */

    SetDepStepSize(dep, step);

    for(i = 0; i < (long)RDB[ader_data + ADER_TRANS_ITER]; i++)
    {

    	/* Set the ADER trans iter num                                        */

    	WDB[ader_data + ADER_TRANS_ITER_NUM] = (double)i;

        /* This function gets all transport information ( leakage and XS ) for*/
        /* all ader mats                                                      */

        ADERGetTransportInformation(dep, i, step);

        /* Now, loop through mats and apply the ADEROperateMaterial function  */
        /* to all of them. The function will reject those mats not under ADER */
        /* control                                                            */

        /* If OpenMP is enabled this block will spawn off OMP_NUM_THREADS     */
        /* which will all loop through materials but each thread will only    */
        /* process a material who's thread ID number matches the actual thread*/
        /* id number.                                                         */

#ifdef OPEN_MP
#pragma omp parallel private (mat)
#endif
        {

			mat = (long)RDB[DATA_PTR_M0];

			while(mat > VALID_PTR)
			{

				/* This checks if a thread should process this material. If   */
				/* not the material is skipped over and a new one checked     */

				if(MyParallelMat(mat, NO) == NO)
				{

					mat = NextItem(mat);

					continue;

				}

#ifdef ADER_INT_TEST
#ifdef OPEN_MP

				fprintf(outp, "ADER Thread %d reporting in!\n", OMP_THREAD_NUM);

#endif
#endif

				ADEROperateMaterial(0, dep, i, mat, step, 0.0,
						            RDB[DATA_BURN_TIME_INTERVAL]);

				mat = NextItem(mat);

			}

#ifdef OPEN_MP
#pragma omp barrier
#endif

        }

        /* Finish building the matrix                                         */

#ifdef ADER_TEST

		if((i == 0) && (step == 0) &&
		   ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP))
		{

			TESTADERAverageValue(dep, step);

			TESTADERCopyMaterialFlux(step);

			TESTADERFillMatCompMatrixPresMolsRow(step);

			TESTADERMatEleBalBounds(step);

			TESTADERMatEleFutBounds(step);

			TESTADERMatIsoAbsMicXsBos(step);

			TESTADERMatIsoAbsMicXsEosInit(step);

			TESTADERMatIsoAbsMicXsPs1Init(step);

			TESTADERMatIsoBalBounds(step);

			TESTADERMatIsoFutBounds(step);

			TESTADERMatIsoNuBarFisMicXsBos(step);

			TESTADERMatIsoNuBarFisMicXsEosInit(step);

			TESTADERMatIsoNuBarFisMicXsPs1Init(step);

			TESTADERMatIsoRhoRowEntry(dep, step);

			TESTADERMatPresBounds(step);

			TESTADERProcessMatStreamEleUnFixedIsoEleFrac(step);

			TESTADERProcessMatStreamEleUnFixedIsoFrac(step);

			TESTADERProcessMatSumStreamEleUnFixedIsoFrac(step);

			TESTADERMatRemvEleAmount(step);

			TESTADERMatRemvIsoAmount(step);

			TESTADERMatSysLeakageBos(step);

			TESTADERMatSysLeakageEos(step);

			TESTADERMatSysLeakagePs1Init(step);

			TESTADERNormalizeMaterialStreamDensity(step);

			TESTADERTransmuXS(step);

			TESTADERUpdateMaterialCompMatrixStreamIsoFracs(step);

			TESTADERUpdateMaterialCompMatrixSumStreamIsoFracs(step);

			TESTADERUpdateMaterialDiscStreamEffects(step);

			TESTADERUpdateMaterialDiscSumStreamEffects(step);

		}

#endif

		mat = (long)RDB[DATA_PTR_M0];

		while(mat > VALID_PTR)
		{

			ADERUpdateMaterialDiscStreamEffects(0, i, mat);

			mat = NextItem(mat);

		}

#ifdef ADER_TEST

		if((i == 0) && (step == 0) &&
		   ((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP))
		{

			TESTADERFixComposition();

		}

#endif

		/* Adjust material compositions and density according to impacts made */
		/* by streams which are discreet in nature                            */

        /* Now that the ADER adjustments have been made, re-run the transport */

		PrepareTransportCycle();

        TransportCycle();

#ifdef ADER_TEST

        /* We skip loop checking for the tests environment to save time       */

        return;
#endif

        /* The eigenvalue predicted, given this material composition, is      */
        /* within bounds, so exit                                             */

        if(Mean((long)RDB[RES_IMP_KEFF], 0) <= RDB[ader_data + ADER_K_MAX] &&
           Mean((long)RDB[RES_IMP_KEFF], 0) >= RDB[ader_data + ADER_K_MIN])
        {

            break;

        }

    }

#ifdef ADER_DIAG

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

    	if((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR)
    	{

	        CalculateTransmuXS(mat, omp_id);

	        ADERMoveCrossSection(mat, step, i);

    	    ADERPrintFinalStepCrossSections(dep, mat, step, 0.0,
    	    		                        RDB[DATA_BURN_TIME_INTERVAL]);

    	}

    	mat = NextItem(mat);

    }

#endif

	/* Set the ADER trans iter num                                        */

	WDB[ader_data + ADER_TRANS_ITER_NUM] = 0.0;

}
