/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderdeallocatetarget.c                         */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Frees arrays stored in passed in array as well as the passed */
/*              in array                                                     */
/*                                                                           */
/* Comments:This function is called from ADERGetBurnMatrixSizeData           */
/*                                       ADEROperateMaterialCompMatrix       */
/*                                       TESTADERAllocateClpMemory           */
/*                                       TESTADERGetBurnMatrixNumRows        */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERDeallocateTarget:"

void ADERDeallocateTarget(double **target, long target_size)
{

	long i = 0;

	/* Loop through the arrays inside of target ( or rather the pointers )    */
	/* and free them                                                          */

	for(i = 0; i < target_size; i++)
	{

		free(target[i]);

	}

	/*Free the array pointer array                                            */

	free(target);

}
