/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadergeteigenbias.c                         */
/*                                                                           */
/* Created:       2016/04/17 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests the value of the eigen bias                            */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERGetEigenBias:"

void TESTADERGetEigenBias(long dep, long mat, double t1, double t2)
{

    char *const test_name = "ADERGetEigenBias";
    char status[5];
    char print_data[256];
    char *mat_name;
    double ader_k_inf = 0;
    double expected_bias = 0, neutron_production = 0, neutron_loss = 0;
    double non_leakage = 0, old_serp_imp_k_eff = 0, percent_diff = 0, test_value = 0;
    int append = 0;
    int boolean = 0;
    long ader_data = 0, ader_mat_iso = 0, ader_test_block = 0;
    long mat_iso = 0, mat_ader_data = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERGetEigenBias.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

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

    /* Now set the new, and fake, serpent implicit non-infinite multiplication*/
    /* factor                                                                 */

    ader_k_inf = neutron_production / neutron_loss;

    non_leakage = (Mean((long)RDB[RES_IMP_KEFF], 0) / Mean((long)RDB[RES_IMP_KINF], 0));

    expected_bias = 0.13;

    old_serp_imp_k_eff = RES1[(long)RDB[(long)RDB[RES_IMP_KEFF] + SCORE_PTR_DATA] + STAT_X];

    RES1[(long)RDB[(long)RDB[RES_IMP_KEFF] + SCORE_PTR_DATA] + STAT_X] = expected_bias *
    		                                                             non_leakage *
																		 ader_k_inf *
																		 RES1[(long)RDB[(long)RDB[RES_IMP_KEFF] + SCORE_PTR_DATA] + STAT_N];

    test_value = ADERGetEigenBias(dep, mat, t1, t2);

    sprintf(print_data, "Material FLiBeFuel has a bias of %0.8E.\n \
Needs bias of %0.8E.\n", test_value,
            expected_bias);

    percent_diff = fabs((test_value - expected_bias) / expected_bias);

    /* Reset serp imp k                                                       */

    RES1[(long)RDB[(long)RDB[RES_IMP_KEFF] + SCORE_PTR_DATA] + STAT_X] = old_serp_imp_k_eff;

    if(percent_diff < 0.0001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

    }

}
