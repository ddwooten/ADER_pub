/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderfixcomposition.c                       */
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fixed negative material composition adens due to non-physical*/
/*              ADER operations executed for testing.                        */
/*                              THIS IS NOT TESTING AN ACTUAL FUNCTION       */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERFixComposition:"

void TESTADERFixComposition(long step)
{

	long mat, mat_iso;

	/* loop through the mats                                                  */

	mat = (long)RDB[DATA_PTR_M0];

	while(mat > VALID_PTR)
	{

		mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

		while(mat_iso > VALID_PTR)
		{

			if(RDB[mat_iso + COMPOSITION_ADENS] < 0.0)
			{

				WDB[mat_iso + COMPOSITION_ADENS] = 0.0;

			}

			mat_iso = NextItem(mat_iso);

		}

		mat= NextItem(mat);

	}

}
