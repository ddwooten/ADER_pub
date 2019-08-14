/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergeteigenbias.c                             */
/*                                                                           */
/* Created:       2016/04/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Determines the bias between ADER k-infinity and SERPENT k-eff*/
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERSetMaterialCompMatrixClusterMemRhoRowEntries                 */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetEigenBias:"

double ADERGetEigenBias(long dep, long mat,
		              double t1, double t2)
{

	double ader_k_inf = 0, bias = 0, neutron_loss = 0, neutron_production = 0;
	double non_leakage = 0;
	long ader_mat_iso = 0, mat_ader_data = 0, mat_iso = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the infinite multiplication factor for this material              */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	neutron_loss += ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
 		                                 RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
			                             RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
									     t1, t2, dep) *
					    RDB[mat_iso + COMPOSITION_ADENS];

    	neutron_production += ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
 		                                       RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
			                                   RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
											   t1, t2, dep) *
							  RDB[mat_iso + COMPOSITION_ADENS];

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    ader_k_inf = neutron_production / neutron_loss;

    non_leakage =  (1.0 - ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
                                           RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
                                           RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
			                               t1, t2, dep));

    bias = Mean((long)RDB[RES_IMP_KEFF], 0) / (ader_k_inf * non_leakage);

    return(bias);

}
