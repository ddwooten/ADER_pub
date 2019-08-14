/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderclearmaterialcompmatrixclustermempresrowbounds.c */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Clears the existing row bounds of pres rows to prepare for   */
/*              new bound information                                        */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds         */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERClearMaterialCompMatrixClusterMemPresRowBounds:"

void ADERClearMaterialCompMatrixClusterMemPresRowBounds(long ader_mat_matrix_data,
		                                                long mat)
{

	long ader_mat_pres = 0, mat_ader_data  = 0;

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Loop through any preservation entries                                  */

	ader_mat_pres = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

	while(ader_mat_pres > VALID_PTR)
	{

		/* If its a mols preserve, clear the bounds                           */

		if(strcmp("mols", GetText(ader_mat_pres + ADER_MAT_PRESERVE_ENT)) == 0)
		{

	    	ADERSetMaterialCompMatrixRowBounds(0, 0, ader_mat_matrix_data,
	    			                           (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
											   0.0);

		}

		ader_mat_pres = NextItem(ader_mat_pres);

	}

}
