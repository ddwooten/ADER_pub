/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermodifyclpsolution.c                    */
/*                                                                           */
/* Created:       2016/04/28 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Overwrites Clp solution vector for testing                   */
/*                                                                           */
/* Comments:This function is called from ADERSolveClpModel                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTAderModifyClpSolution"

void TESTAderModifyClpSolution(double* clp_solution, long num_cols)
{

	long i;

	for(i = 0; i < num_cols; i++)
	{

		clp_solution[i] = 0.0;

	}

}
