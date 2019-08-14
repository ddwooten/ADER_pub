/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetisoburnmatrixindex.c                    */
/*                                                                           */
/* Created:       2016/22/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Retrieves the index of the isotope which belongs to nuc      */
/*                                                                           */
/* Comments:This function is called from ADERMakeBurnMatrix                  */
/*                                       MaterialBurnup                      */
/*                                       PrintDepMatrix                      */
/*                                       UpdateCIStop                        */
/*                                       TESTADERGetIsoBurnMatrixIndex       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetIsoBurnMatrixIndex:"

long ADERGetIsoBurnMatrixIndex(char* func, long mat, long nuc)
{

	long ader_mat_data = 0, ader_mat_iso = 0, mat_iso = 0, mat_iso_nuc = 0;
	long found = 0, iso_index = -1;

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	if(ader_mat_data < VALID_PTR)
	{

		Die(FUNCTION_NAME, "Material %s passed to ADERGetIsoBurnMatrixIndex by \n\
function %s is not an ADER material.\n", GetText(mat + MATERIAL_PTR_NAME),
            func);

	}

	/* If this function is attempting to retreive the index for the -1 "fake" */
	/* isotope, this index is stored in the material's ader data              */

	if((long)RDB[nuc + NUCLIDE_ZAI] == -1)
	{

		iso_index = (long)RDB[ader_mat_data + ADER_MAT_FAKE_ISO_BURN_INDEX];

	}
	else
	{

		/* Loop through the ader material isotopes, find the one who's ZAI    */
		/* matches the ZAI of nuc. Return the index                           */

		ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

		while(ader_mat_iso > VALID_PTR)
		{

			mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

			mat_iso_nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

			if((long)RDB[mat_iso_nuc + NUCLIDE_ZAI] == (long)RDB[nuc + NUCLIDE_ZAI])
			{

				iso_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

				break;

			}

			ader_mat_iso = NextItem(ader_mat_iso);

		}

	}



	if(iso_index < 0)
	{

		if(found > 0)
		{

			Die(FUNCTION_NAME, "Isotope, with ZAI of %ld, passed to ADERGetIsoBurnMatrixIndex \n\
	by function %s for material %s does not have a valid burn matrix index.\n",
	            (long)RDB[nuc + NUCLIDE_ZAI], func,
				GetText(mat + MATERIAL_PTR_NAME));

		}
		else
		{

			Die(FUNCTION_NAME, "Isotope, with ZAI of %ld, passed to ADERGetIsoBurnMatrixIndex \n\
	by function %s for material %s was not found in said material.\n",
	            (long)RDB[nuc + NUCLIDE_ZAI], func,
				GetText(mat + MATERIAL_PTR_NAME));

		}

	}

	return(iso_index);

}
