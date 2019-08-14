/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixclustermemrhorowentries.c*/
/*                                                                           */
/* Created:       2016/04/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's isotopes filling in reactivity    */
/*              information if it is needed                                  */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixClusterMemRhoRowEntries:"

void ADERSetMaterialCompMatrixClusterMemRhoRowEntries(long dep, long mat,
													  double t1, double t2)
{

	double ader_mat_iso_k_max_value = 0, ader_mat_iso_k_min_value = 0, bias = 0;
	long ader_data = 0, ader_mat_iso = 0;
	long ader_parent_mat = 0, ader_parent_mat_ader_data = 0;
	long ader_parent_mat_matrix_data = 0, mat_ader_data = 0;

	/* If this material is not under reactivity control, exit                 */

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	if(mat_ader_data > VALID_PTR)
	{

		if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] > 0.0)
		{

			/* Get the parent material here for matrix data */

			ader_parent_mat = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

			ader_parent_mat_ader_data = (long)RDB[ader_parent_mat + MATERIAL_ADER_DATA];

			ader_parent_mat_matrix_data = (long)RDB[ader_parent_mat_ader_data + ADER_MAT_MATRIX_PTR];

		}
		else
		{

			return;

		}

	}

	/* First we need the ader data for k_max and k_min values                 */

	ader_data = (long)RDB[DATA_PTR_ADER];

	/* Get the biasing factor between ADER and SERPENT                        */

	bias = ADERGetEigenBias(dep, mat, t1, t2);

	/* loop through the isotopes to fill their reacitivty information         */

	ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

	while(ader_mat_iso > VALID_PTR)
	{

		/* Get the value to put in the k max row and iso fut col              */
        /* This value should be equal to....                         */
        /* ( ( ( K_max / ( ( 1 - p_l ) * bias ) * sigma_abs ) - ( nu_bar * sigma_fis ) ) */

		ader_mat_iso_k_max_value = (((RDB[ader_data + ADER_K_MAX] /
				                      ((1.0 - ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
				                    		                   RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
															   RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
															   t1, t2, dep)) *
				                         bias)) *
				                      ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
				                    		           RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
											           RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
													   t1, t2, dep)) -
				                    ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
				                    		         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
											         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
													 t1, t2, dep));

		/* Get the value to put in the k min row and iso fut col              */
        /* This value should be equal to....                                  */
        /* ( ( ( K_min / ( 1 - p_l ) ) * sigma_abs ) - ( nu_bar * sigma_fis ) ) */

		ader_mat_iso_k_min_value = (((RDB[ader_data + ADER_K_MIN] /
				                      ((1.0 - ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
				                    		                   RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
											                   RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
															   t1, t2, dep)) *
				                        bias)) *
				                      ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
				                    		           RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
											           RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
													   t1, t2, dep)) -
				                    ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
				                    		         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
											         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
													 t1, t2, dep));

		ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
				                         (long)RDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID],
										 ader_parent_mat_matrix_data,
										 ader_mat_iso_k_max_value);

		ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID],
				                         (long)RDB[mat_ader_data + ADER_MAT_RHO_MIN_ROW_ID],
										 ader_parent_mat_matrix_data,
										 ader_mat_iso_k_min_value);

		ader_mat_iso = NextItem(ader_mat_iso);

	}

}
