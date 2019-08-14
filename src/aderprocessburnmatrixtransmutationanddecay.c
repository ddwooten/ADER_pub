/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessburnmatrixtransmutationanddecay.c   */
/*                                                                           */
/* Created:       2016/29/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills transmutation effects for isotope and its products     */
/*              Also handles decay effects                                   */
/*                                                                           */
/* Comments: This function is called from ADERMakeBurnMatrix                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessBurnMatrixTransmutationAndDecay"

void ADERProcessBurnMatrixTransmutationAndDecay(long ader_mat_iso,
		                                        double* col_vector,
		                                        long mat, double mat_flux,
												long nuc, long omp_id, long rea,
												long reaction_product_nuc,
												long type)
{

	double micro_cross_section = 0, reaction_rate = 0;
	long ader_mat_iso_product_index = 0;

	/* If this reaction is a decay reaction, set the reaction rate            */

	if((type == REACTION_TYPE_DECAY) ||
	   (type == REACTION_TYPE_DEC_BRANCH))
	{

		/* The branching ratio is purposefully left out here because it must  */
		/* be left out below, see below comment for reason. The branching     */
		/* ratio will be included when the vector values are adjusted         */

		reaction_rate = RDB[nuc + NUCLIDE_LAMBDA];

		/* Go ahead and add this removal rate to the isotope's own            */
		/* production/destruction rate, but only if it is not a branch rea    */

		if(type == REACTION_TYPE_DECAY)
		{

			col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] -= reaction_rate *
					                                                         RDB[rea + REACTION_BR];

		}

	}
	else if((type == REACTION_TYPE_PARTIAL) ||
            (type == REACTION_TYPE_TRA_BRANCH))
	{

		/* If this reaction is a transmutation reaction get the rate          */

		micro_cross_section = GetPrivateData(((long)RDB[rea + REACTION_PTR_TRANSMUXS]) + 1,
				                             omp_id);

		/* Make sure a physical answer is provided                           */

		if(micro_cross_section > 0.0)
		{

			/* The branching ratio is purposefully left out here thanks to how*/
			/*the reactions are tabulated                                     */

			reaction_rate = micro_cross_section * mat_flux *
					        BARN;

			/* Go ahead and add this removal rate to the isotope's own            */
			/* production/destruction rate, but only if it is not a branch rea    */

			if(type == REACTION_TYPE_PARTIAL)
			{

				col_vector[(long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]] -= reaction_rate;

			}

		}
		else
		{

			/* The cross section is not real                                  */

			reaction_rate = 0.0;

		}

	}

	/* Get the product ader isotope index IN THIS MATERIAL                    */

	ader_mat_iso_product_index = ADERGetIsoBurnMatrixIndex(FUNCTION_NAME,
			                                               mat,
											               reaction_product_nuc);

	/* Now add the production rate for the product isotope                    */

	col_vector[ader_mat_iso_product_index] += reaction_rate *
			                                  RDB[rea + REACTION_BR];

}
