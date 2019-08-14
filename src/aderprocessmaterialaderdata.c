/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialaderdata.c                  */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link read in ader data with the           */
/*              appropriate materials                                        */
/*                                                                           */
/* Comments:This function is called from ProcessMaterials                    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialAderData:"

void ADERProcessMaterialAderData()
{

    long mat = 0;

    fprintf(outp, "Processing ADER data and allocating memory.\n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR)
        {

        	if((long)RDB[DATA_BURN_BUMODE] == BUMODE_TTA)
        	{

        		Warn(FUNCTION_NAME, "ADER material burnup simulations may only \n\
be completed using the CRAM burn matrix solution methodology.\n\
TTA was set by the user but has been overridden by ADER to CRAM.\n");


        		WDB[DATA_BURN_BUMODE] = (double)BUMODE_CRAM;

        	}

            if(((long)RDB[mat + MATERIAL_BURN_RINGS] > VALID_PTR) ||
               ((long)RDB[mat + MATERIAL_BURN_RINGS] > 0) ||
               ((long)RDB[mat + MATERIAL_PTR_DIV] > VALID_PTR))
            {

                /* ADER is not compatible with divided materials */

                Error(0, "Use of the ADER components of SERPENT is not \n \
compatible with 'divided'* materials in SERPENT. \n \
Material %s is both an ADER material and a divided material. \n \
*['divided' materials are those which have been given an integer number \n \
, greater than 0, following the 'burn' entry in the material definition card, \n \
or those materials which were created from parent materials defined with the \n \
'burn' card followed by an integer.\n", GetText(mat + MATERIAL_PTR_NAME));

            }

            ADERProcessMaterialAderClusters(mat);

            ADERCheckMaterialClusterIsotopes(mat);

            ADERProcessMaterialConditions(mat);

            ADERProcessMaterialStreams(mat);

            ADERLinkMaterialIsotopeIndices(mat);

        }

        mat = NextItem(mat);

    }

    /* Now we loop through the materials again as these next set of processing*/
    /* functions requires that all ADER materials already have been processed */
    /* with the above functions.                                              */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR)
        {

            ADERProcessMaterialShadowStreams(mat);

            ADERProcessMaterialClusterOptEntry(mat);

        }

        mat = NextItem(mat);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR)
        {

            ADERCheckMaterialRemovalTables(mat, 0);

            ADERCreateMaterialCompMatrix(mat);

        }

        mat = NextItem(mat);

    }

    /* Send out the below while loop to differing threads. If a material      */
    /* doesn't belong to a thread it will get skipped                         */

#ifdef OPEN_MP
#pragma omp parallel private(mat)
#endif
    {

		mat = (long)RDB[DATA_PTR_M0];

		while(mat > VALID_PTR)
		{

			if(MyParallelMat(mat, NO) == NO)
			{

				mat = NextItem(mat);

				continue;

			}

			if((long)RDB[mat + MATERIAL_ADER_DATA] > VALID_PTR)
			{

				if((long)RDB[(long)RDB[mat + MATERIAL_ADER_DATA] + ADER_MAT_MATRIX_PTR] > VALID_PTR)
				{

#ifdef ADER_INT_TEST
#ifdef OPEN_MP

				fprintf(outp, "ADER Thread %d reporting in!\n", OMP_THREAD_NUM);

#endif
#endif

					ADERFillMaterialCompMatrix(mat);

				}

			}

			mat = NextItem(mat);

		}

#ifdef OPEN_MP
#pragma omp barrier
#endif


    }

    fprintf(outp, "OK.\n\n");

}
