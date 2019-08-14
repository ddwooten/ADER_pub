/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixclustermempresrowbounds.c */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to adjust row bounds in the comp matrix to   */
/*              account for material removal due to removal tables if        */
/*              preservation rows are in use                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds         */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixClusterMemPresRowBounds:"

void ADERSetMaterialCompMatrixClusterMemPresRowBounds(long ader_mat_matrix_data,
		                                              long mat, double value)
{

	long ader_mat_pres = 0, mat_ader_data = 0;

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Loop through any preservation entries                                  */

	ader_mat_pres = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

	while(ader_mat_pres > VALID_PTR)
	{

		/* If its a mols preserve, adjust the value                           */

		if(strcmp("mols", GetText(ader_mat_pres + ADER_MAT_PRESERVE_ENT)) == 0)
		{

			/* We multiply by -1 so that the "preserve mols" row is aware that*/
			/*, if material is leaving say, it needs to have a positive value */
			/* to balance out that material that has left. The inverse is true*/
			/* for material coming into the system                            */

	    	ADERSetMaterialCompMatrixRowBounds(0, 1, ader_mat_matrix_data,
	    			                           (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
											   -1.0 * value);

		}

		ader_mat_pres = NextItem(ader_mat_pres);

	}

}
