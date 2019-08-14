/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessburnmatrixfissionyield.c            */
/*                                                                           */
/* Created:       2016/29/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills fission yield effects for isotope and its products     */
/*                                                                           */
/* Comments: This function is called from ADERMakeBurnMatrix                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessBurnMatrixFissionYield"

void ADERProcessBurnMatrixFissionYield(long ader_mat_iso, double* col_vector,
		                               long fission_yield_data, long mat,
									   double mat_flux, long nuc, long omp_id,
									   long rea, long type)
{

	double micro_cross_section = 0, reaction_rate = 0;
	long ader_mat_iso_product_index = 0, fission_yield = 0, fission_yield_nuc = 0;

	/* If this is spontaneous fission, the reaction rate is the decay constant*/

	if(type == REACTION_TYPE_DECAY)
	{

		reaction_rate = RDB[nuc + NUCLIDE_LAMBDA] *
				        RDB[rea + REACTION_BR];

	}
	else
	{

		/* This is a particle induced fission, to get the rate GetPrivateData is */
		/* used as opposed to TestValuePair ( the function used in the normal */
		/* SERPENT version as, at the time of development, there were         */
		/* unresolved bug concerns with TestValuePair. When used properly     */
		/* GetPrivateData is equivalent to a correct implementation of        */
		/* TestValuePair. It is important to know that TestValuePair takes    */
		/* the RDB LOCATION of the data, and not the data itself while        */
		/* GetPrivateData DOES take the actual data ICREMENTED BY 1           */

		micro_cross_section = GetPrivateData(((long)RDB[rea + REACTION_PTR_TRANSMUXS]) + 1,
				                             omp_id);

		/* Make sure a physical answer is provided                            */

		if(micro_cross_section > 0.0)
		{

			reaction_rate = micro_cross_section * mat_flux *
					        BARN * RDB[rea + REACTION_BR];

		}
		else
		{

			/* The cross section is not real                                  */

			reaction_rate = 0.0;

		}

	}

	/* Go ahead and add this removal rate to the isotope's own                */
	/* production/destruction rate                                            */

	col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] -= reaction_rate;

	/* Now, loop through the fission yield products and fill in their         */
	/* production data from this isotope                                      */

	fission_yield = (long)RDB[fission_yield_data + FISSION_YIELD_PTR_DISTR];

	while(fission_yield > VALID_PTR)
	{

		/* Get the product "nuc" data                                         */

		fission_yield_nuc = (long)RDB[fission_yield + FY_PTR_TGT];

		/* Get the matching ader isotope IN THIS MATERIAL                     */

		ader_mat_iso_product_index = ADERGetIsoBurnMatrixIndex(FUNCTION_NAME,
				                                               mat,
														       fission_yield_nuc);

		/* Now, add the fractional reaction rate to the production of the     */
		/*target isotope from the isotope undergoing fission                  */

		col_vector[ader_mat_iso_product_index] += reaction_rate *
				                                  RDB[fission_yield + FY_INDEPENDENT_FRAC] *
                                                  RDB[rea + REACTION_BR];

		fission_yield = NextItem(fission_yield);

	}

}
