/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintcrosssections.c                       */
/*                                                                           */
/* Created:       2016/04/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Prints relevant cross section and isotopic data to file      */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintCrossSections:"

void ADERPrintCrossSections(long dep, long i, long mat, long step, double t1, double t2)
{

    char file_out[256];
    double ader_k_gain = 0.0, ader_k_loss = 0.0, ader_k_value = 0.0;
    double leakage = 0.0, non_leakage = 0.0;
	long ader_mat_iso = 0, mat_ader_data = 0;
    FILE *fp = NULL;

	/* If this material is not under reactivity control, exit                 */

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	if(mat_ader_data > VALID_PTR)
	{

		if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] <= 0.0)
		{

			return;

		}

	}

    /* Go ahead and create the file name                                      */

    sprintf(file_out, "%s_XS_step_%ld_iter_%ld.txt",
    		GetText(mat + MATERIAL_PTR_NAME), step, i);

	if ((fp = fopen(file_out, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open material cross section output file.\n");

	}

    fprintf(fp, "************************************ Begin *************************************\n");
    fprintf(fp, "\n");
    fprintf(fp, "Material: %s \n", GetText(mat + MATERIAL_PTR_NAME));
    fprintf(fp, "Density: %0.12E \n", RDB[mat + MATERIAL_ADENS]);
    fprintf(fp, "Burnup: %0.12E \n", RDB[mat + MATERIAL_BURNUP]);
    fprintf(fp, "BOS Leakage: %0.12E \n", RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS]);

    /* Get the calculated leakage                                             */

    leakage = ADERAverageValue(RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
                               RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
			                   RDB[mat_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
			                   t1, t2, dep);

    fprintf(fp, "Avg Leakage: %0.12E \n", leakage);

    /* Get the non-leakage                                                    */

    non_leakage = 1.0 - leakage;

    fprintf(fp, "Avg non-leakage: %0.12E \n", non_leakage);

    fprintf(fp, "\n");


	/* loop through the isotopes to get their reacitivty information      +	    */

	ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

	while(ader_mat_iso > VALID_PTR)
	{

		fprintf(fp, "ZAI: %ld \n", (long)RDB[(long)RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_PTR_NUCLIDE] + NUCLIDE_ZAI]);

		fprintf(fp, "    adens:     %0.12E \n", RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS]);

		fprintf(fp, "    adens-bos: %0.12E \n", RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS_BOS]);

		fprintf(fp, "    abs-bos:   %0.12E \n", RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS]);

		fprintf(fp, "    abs-avg:   %0.12E \n", ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
				                                                 t1, t2, dep));

		fprintf(fp, "    fis-avg: %0.12E \n", ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_PS1],
				                                                 t1, t2, dep));

		fprintf(fp, "    nu-avg: %0.12E \n", (ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
                RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
                RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
                t1, t2, dep) / ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_PS1],
				                                                 t1, t2, dep)));

		fprintf(fp, "    nufis-bos: %0.12E \n", RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS]);

		fprintf(fp, "    nufis-avg: %0.12E \n", ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
				                                                 t1, t2, dep));

		fprintf(fp, "    gain-cont: %0.12E \n", ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
				                                                 t1, t2, dep) *
				                                RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS]);

		fprintf(fp, "    loss-cont: %0.12E \n", ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
		                                                         RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
				                                                 t1, t2, dep) *
				                                RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS]);

		fprintf(fp, "\n");

		/* Include the isotopes contribution to k                             */

		ader_k_gain += ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
                                        RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
                                        RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
                                        t1, t2, dep) * RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS];

		ader_k_loss += ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
                                        RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
                                        RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
                                        t1, t2, dep) * RDB[(long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR] + COMPOSITION_ADENS];

		ader_mat_iso = NextItem(ader_mat_iso);

	}

	ader_k_value = (ader_k_gain / ader_k_loss) * non_leakage;

	fprintf(fp, "ader_k_value: %0.12E \n", ader_k_value);

	fprintf(fp, "serpent_k_value: %0.12E \n", Mean((long)RDB[RES_IMP_KEFF], 0));

	fprintf(fp, "percent_diff: %0.3f \n", 100.0 * ((ader_k_value - Mean((long)RDB[RES_IMP_KEFF], 0)) / Mean((long)RDB[RES_IMP_KEFF], 0)));

    fprintf(fp, "********************************************************************************\n");

    fclose(fp);

}
