/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadercompareburnmatrices.c                  */
/*                                                                           */
/* Created:       2018/03/08 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This test takes in a burn matrix as made by ADER. It then    */
/*              generates a burn matrix for each cluster member and          */
/*              compares the entries for all isotope entries, it ignores     */
/*              stream entries. This function outputs to file.                */
/*                                                                           */
/* Comments: This function is called from ADERBurnMaterials                  */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERCompareBurnMatrices:"

void TESTADERCompareBurnMatrices(struct ccsMatrix *ader_burn_matrix, long mat,
		                         long step, long sub_step)
{
    char file_out[256];
    long isos_index[10000];
    long ader_mat_cluster_ent, ader_mat_cluster_mem;
    long ader_mat_cluster_mem_ader_iso_1, ader_mat_cluster_mem_ader_iso_2;
    long ader_mat_cluster_mem_data;
    long ader_mat_cluster_mem_mat_iso, ader_mat_data, found_1, found_2;
    long i, nuc, serp_index_1, serp_index_2, zai_1, zai_2;
    double ader_matrix_value, percent_diff, serp_matrix_value;
    FILE *fp;
    struct ccsMatrix *serp_burn_matrix;

    /* Go ahead and create the file name                                      */

	if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
	{

	    sprintf(file_out, "Cluster_Parent_%s_Pred_Step_%ld_Sub_Step_%ld_Matrix_Comparison.test",
	    		GetText(mat + MATERIAL_PTR_NAME), step, sub_step);

	}
	else
	{

	    sprintf(file_out, "Cluster_Parent_%s_Corr_Step_%ld_Corr_Sub_Step_%ld_Matrix_Comparison.test",
	    		GetText(mat + MATERIAL_PTR_NAME), step, sub_step);

	}



	if ((fp = fopen(file_out, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open cluster csv file for writing");

	}

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Loop through the cluster members to check the components of each of    */
	/* their burnup matrices                                                  */

	ader_mat_cluster_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_ent > VALID_PTR)
	{

		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

		ader_mat_cluster_mem_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

		fprintf(fp, "Begin cluster member %s burnup matrix comparison:\n",
				GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

		/* Get the serpent created burnup matrix to compare with              */

		serp_burn_matrix = MakeBurnMatrix(ader_mat_cluster_mem, 0);

		/* Loop through the material's serpent isotopes to get their burn     */
		/* indices, this method is taken from MakeBurnMatrix                  */

		i = 0;

		ader_mat_cluster_mem_mat_iso = (long)RDB[ader_mat_cluster_mem + MATERIAL_PTR_COMP];

		while(ader_mat_cluster_mem_mat_iso > VALID_PTR)
		{

			nuc = (long)RDB[ader_mat_cluster_mem_mat_iso + COMPOSITION_PTR_NUCLIDE];

			isos_index[i] = (long)RDB[nuc + NUCLIDE_ZAI];

			i++;

			ader_mat_cluster_mem_mat_iso = NextItem(ader_mat_cluster_mem_mat_iso);

		}

		/* Now, loop through the ader isotopes, and compare the burnup matrix */
		/* information                                                        */

		ader_mat_cluster_mem_ader_iso_1 = (long)RDB[ader_mat_cluster_mem_data + ADER_MAT_ISOS_PTR];

		while(ader_mat_cluster_mem_ader_iso_1 > VALID_PTR)
		{

			ader_mat_cluster_mem_mat_iso = (long)RDB[ader_mat_cluster_mem_ader_iso_1 + ADER_MAT_ISO_PTR];

			nuc = (long)RDB[ader_mat_cluster_mem_mat_iso + COMPOSITION_PTR_NUCLIDE];

			zai_1 = (long)RDB[nuc + NUCLIDE_ZAI];

			found_1 = 0;

			/* Get the isotope index corresponding to this zai                */

			for(i = 0; i < 10000; i++)
			{

				if(isos_index[i] == zai_1)
				{

					serp_index_1 = i;

					found_1 = 1;

					break;

				}

			}

			if(found_1 < 1)
			{

				Die(FUNCTION_NAME, "TESTADERCompareBurnMatrices could not find a matching isotope\n\
	for ADER isotope %ld found at WDB:%ld in the SERPENT isotope index list.\n",
	                zai_1, ader_mat_cluster_mem_ader_iso_1);

			}

			/* Loop through the ader isotopes again, this is how we check the */
			/* information given to each isotope                              */

			ader_mat_cluster_mem_ader_iso_2 = (long)RDB[ader_mat_cluster_mem_data + ADER_MAT_ISOS_PTR];

			while(ader_mat_cluster_mem_ader_iso_2 > VALID_PTR)
			{

				percent_diff = 0.0;

				ader_mat_cluster_mem_mat_iso = (long)RDB[ader_mat_cluster_mem_ader_iso_2 + ADER_MAT_ISO_PTR];

				nuc = (long)RDB[ader_mat_cluster_mem_mat_iso + COMPOSITION_PTR_NUCLIDE];

				zai_2 = (long)RDB[nuc + NUCLIDE_ZAI];

				found_2 = 0;

				/* Get the isotope index corresponding to this zai            */

				for(i = 0; i < 10000; i++)
				{

					if(isos_index[i] == zai_2)
					{

						serp_index_2 = i;

						found_2 = 1;

						break;

					}

				}

				if(found_2 < 1)
				{

					Die(FUNCTION_NAME, "TESTADERCompareBurnMatrices could not find a matching isotope\n\
		for ADER isotope %ld found at WDB:%ld in the SERPENT isotope index list.\n",
		                zai_2, ader_mat_cluster_mem_ader_iso_2);

				}

				/* Now, retreive both values from their respective matrices   */
				/* and compare them.                                          */

				ader_matrix_value = ADERGetBurnMatrixValue((long)RDB[ader_mat_cluster_mem_ader_iso_2 + ADER_MAT_ISO_BURN_INDEX],
						                                   ader_burn_matrix,
														   (long)RDB[ader_mat_cluster_mem_ader_iso_1 + ADER_MAT_ISO_BURN_INDEX]);

				serp_matrix_value = ADERGetBurnMatrixValue(serp_index_2,
						                                   serp_burn_matrix,
														   serp_index_1);

				if(serp_matrix_value == 0.0)
				{

					if(ader_matrix_value == 0.0)
					{

						percent_diff = 0.0;

					}
					else
					{

						percent_diff = 100.00;
					}

				}
				else
				{

					percent_diff = ((ader_matrix_value - serp_matrix_value) / serp_matrix_value) * 100.0;

				}

				if(percent_diff > 1.0)
				{

					fprintf(fp, "    Percent Diff: %.2f\n\
                                         Row Iso:  %ld\n\
                                         Col Iso:  %ld\n\
                                         ADER Ind: [%ld, %ld]\n\
                                         Serp Ind: [%ld, %ld]\n\
                                         ADER Val: %.32f\n\
                                         SERP Val: %.32f\n",
	                       percent_diff, zai_1, zai_2,
						   (long)RDB[ader_mat_cluster_mem_ader_iso_1 + ADER_MAT_ISO_BURN_INDEX],
						   (long)RDB[ader_mat_cluster_mem_ader_iso_2 + ADER_MAT_ISO_BURN_INDEX],
						   serp_index_1, serp_index_2, ader_matrix_value,
						   serp_matrix_value);

				}

				ader_mat_cluster_mem_ader_iso_2 = NextItem(ader_mat_cluster_mem_ader_iso_2);

			}

			ader_mat_cluster_mem_ader_iso_1 = NextItem(ader_mat_cluster_mem_ader_iso_1);

		}

		fprintf(fp, "********************************************************************************\n");

		/* Free the memory for this cluster member's serpent burnup matrix    */

	    ccsMatrixFree(serp_burn_matrix);

		ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

	}

	/* Close the file                                                         */

	fclose(fp);

}
