/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoutputmaterialcompmatrixdata.c             */
/*                                                                           */
/* Created:       2017/02/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Writes out all cluster material composition matrix meta data */
/*              to a json formatted text file. Additionally calls supporting */
/*              functions to write out the actual material comp matrix as a  */
/*              csv formatted text file                                      */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterialCompMatrix       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROutputMaterialCompMatrixData:"

void ADEROutputMaterialCompMatrixData()
{

    static char *file_out = "ADER_Cluster_Composition_Matrices.json";
    char print_buffer[256], print_data[256];
    double bias = 0.0;
    double iso_max_dec = 0, iso_max_reac = 0, iso_min_dec = 0, iso_min_reac = 0, k_max_inf = 0, k_min_inf = 0, loss_max = 0, loss_min = 0;
    double production_max = 0, production_min = 0, t1 = 0, t2 = 0;
    FILE *fp = NULL;
    long ader_cnt = 0, ader_cnt_ent = 0, ader_data = 0, ader_mat_cluster_mem = 0;
    long ader_mat_cluster_mem_ader_data = 0;
    long ader_mat_cluster_mem_ent = 0, ader_mat_cluster_mem_oxi = 0, ader_mat_cluster_mem_pres = 0;
    long ader_mat_cluster_mem_stream = 0, ader_mat_cmp = 0, ader_mat_cmp_ele = 0;
    long ader_mat_cmp_iso = 0, ader_mat_cmp_rng = 0, ader_mat_cmp_rto = 0, ader_mat_cmp_rto_grp2 = 0, ader_mat_cmp_sum_grp = 0;
    long ader_mat_cnt = 0;
	long ader_mat_data = 0, ader_mat_ele = 0, ader_mat_ele_iso = 0, ader_mat_iso = 0, ader_mat_matrix_data = 0, ader_mat_matrix_col = 0;
	long ader_mat_matrix_row_bound = 0, ader_mat_search_cmp = 0, ader_oxi = 0, ader_oxi_ele = 0;
	long another_cluster = 0, controlled = 0, dep = 0, i = 0, mat = 0, mat_iso = 0;
	long name_counter = 0, nuc = 0, num_cluster_members = 0, num_col = 0;
	long num_row = 0, search_mat = 0, search_ader_mat_data = 0, tab_length = 0, tab_level = 0;
	long num_clusters = 0;

	/* Here we have tab_level place holders                                   */

	long tab_level_init_dict, tab_level_unique_cluster, tab_level_cluster_data;
	long tab_level_cluster_member_info;

	/* Go ahead and set the tab_lenght and tab_level                          */

	tab_length = 4;

	tab_level = 0;

	if ((fp = fopen(file_out, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open cluster JSON file for writing");

	}

	fprintf(outp, "Beginning cluster data json dump.\n\n");

	/* Print the beginning of the json material clusters list                 */
	/* Don't worry about new-lines for ADERPrintIndentedOutput, it does that  */

	sprintf(print_data, "[");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

	tab_level++;

	/* Create the first dictionary which will hold all the cluster information*/

	sprintf(print_data, "{");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

	tab_level++;

	tab_level_init_dict = tab_level;

	/* Create the clusters dict                                               */

	sprintf(print_data, "\"clusters\" : {");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

	tab_level++;

	tab_level_unique_cluster = tab_level;

	/* Loop through materials to find cluster parents                         */

	mat = (long)RDB[DATA_PTR_M0];

	while(mat > VALID_PTR)
	{

		ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

		if(ader_mat_data > VALID_PTR)
		{

			/* Only be concerned with parent materials                        */

			if((long)RDB[ader_mat_data + ADER_MAT_CLUSTER_PARENT_PTR] == mat)
			{

				tab_level = tab_level_unique_cluster;

				fprintf(outp, "Processing cluster with parent %s.\n\n",
						     GetText(mat + MATERIAL_PTR_NAME));

				/* Create the cluster info dictionary                         */

				sprintf(print_data, "\"cluster_%ld\" : {", num_clusters);

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				tab_level_cluster_data = tab_level;

				/* Increment the number of clusters                           */

				num_clusters++;

				/* Create the parent key and its attribute                    */

				sprintf(print_data, "\"parent\" : \"%s\",",
						            GetText(mat + MATERIAL_PTR_NAME));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				/* Now, create the matrix key                                 */

				sprintf(print_data, "\"composition_matrix_data\" : {");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				/* Get the material composition matrix                        */

				ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

				fprintf(outp, "Processing matrix data for parent %s.\n\n",
						     GetText(mat + MATERIAL_PTR_NAME));

				/* The matrix data is too large to write to the json format   */
				/* As such we call the below function to write out the matrix */
				/* as a separate csv file                                     */

				ADEROutputMaterialCompMatrixAsCsv(ader_mat_matrix_data,
						                          (num_clusters - 1));

				/* Fill in the data for the number of columns and rows        */

				sprintf(print_data, "\"num_cols\" : %ld,",
						            (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]);

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"num_rows\" : %ld,",
						            (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS]);

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				/* Now, create the columns dictionary                         */

				sprintf(print_data, "\"cols\" : {");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				num_col = 0;

				ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

				while(ader_mat_matrix_col > VALID_PTR)
				{

					/* Open the column dictionary                             */

					sprintf(print_data, "\"%ld\" : {", num_col);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Create the column bounds list                          */

					sprintf(print_data, "\"col_bounds\" : [");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Fill the column bounds list                            */

					sprintf(print_data, "%.16f,",
							            RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					sprintf(print_data, "%.16f",
							            RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					/* Close the column bounds list                           */

					sprintf(print_data, "]");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level--;

					/* Close the column dictionary                            */

					if(NextItem(ader_mat_matrix_col) > VALID_PTR)
					{

						sprintf(print_data, "},");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

					}
					else
					{

						/* Final list elements can not have a trailing comma  */

						sprintf(print_data, "}");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

					}

					num_col++;

					ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

				}

				/* Close the columns dictionary                               */

				sprintf(print_data, "},");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level--;

				/* Create the row_bounds dictionary                           */

				sprintf(print_data, "\"row_bounds\" : {");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				num_row = 0;

				/* Now, loop through all the row bounds for this matrix       */

				ader_mat_matrix_row_bound = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

				while(ader_mat_matrix_row_bound > VALID_PTR)
				{

					/* Create the row bound list                              */

					sprintf(print_data, "\"%ld\" : [", num_row);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Fill in the row bound entries                          */

					sprintf(print_data, "%.16f,",
							            RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					sprintf(print_data, "%.16f",
							            RDB[ader_mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					/* Close the row bound list                               */

					if(NextItem(ader_mat_matrix_row_bound) > VALID_PTR)
					{

						sprintf(print_data, "],");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}
					else
					{

						/* The last item in a list can not have a trailing ","*/

						sprintf(print_data, "]");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}

					tab_level--;

					num_row++;

					ader_mat_matrix_row_bound = NextItem(ader_mat_matrix_row_bound);

				}

				/* Close the row_bounds dictionary                            */

				sprintf(print_data, "}");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level--;

				/* Close the composition matrix data dict                     */

				sprintf(print_data, "},");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level--;

				fprintf(outp, "Finished matrix processing for parent %s.\n\n",
						     GetText(mat + MATERIAL_PTR_NAME));

				/* Create the members key and start its list                  */

				sprintf(print_data, "\"members\" : [");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				num_cluster_members = 0;

				/* Fill the members list                                      */

				ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

				while(ader_mat_cluster_mem_ent > VALID_PTR)
				{

					num_cluster_members++;

					ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

					/* Print the cluster member name                          */

					/* The last list entry can not have a trailing comma      */

					if(NextItem(ader_mat_cluster_mem_ent) > VALID_PTR)
					{

						sprintf(print_data, "\"%s\",",
								            GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}
					else
					{

						sprintf(print_data, "\"%s\"",
								            GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}

					ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

				}

				/* Close the cluster members list                             */

				sprintf(print_data, "],");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level--;

				/* Open the cluster members info dict                         */

				sprintf(print_data, "\"members_info\" : {");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				tab_level_cluster_member_info = tab_level;

				/* Now, loop through the cluster members                      */

				ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

				while(ader_mat_cluster_mem_ent > VALID_PTR)
				{

					ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

					ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

					fprintf(outp, "Processing cluster member %s.\n\n",
							     GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

					/* Open the cluster member info dict                      */

					sprintf(print_data, "\"%s\" : {",
							            GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Provide the material density                           */

					sprintf(print_data, "\"density\" : %0.16f,	",
							            RDB[ader_mat_cluster_mem + MATERIAL_ADENS]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					/* Provide the material volume                            */

					sprintf(print_data, "\"volume\" : %0.16f,	",
							            RDB[ader_mat_cluster_mem + MATERIAL_VOLUME]);

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					/* Give the reactivity min and max rows if they exist     */
					/* as well as the criticality targest and leakage         */

					if(RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_RHO_WEIGHT] > 0.0)
					{

						sprintf(print_data, "\"rho_max_row\" : %ld,",
								            (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_RHO_MAX_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						sprintf(print_data, "\"rho_min_row\" : %ld,",
								            (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_RHO_MIN_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						sprintf(print_data, "\"leakage\" : %0.16f,",
								            RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_CUR]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Get the ader data to get the kmax and kmin targets */

						ader_data = (long)RDB[DATA_PTR_ADER];

						sprintf(print_data, "\"k_max\" : %0.8f,",
								            RDB[ader_data + ADER_K_MAX]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						sprintf(print_data, "\"k_min\" : %0.8f,",
								            RDB[ader_data + ADER_K_MIN]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}

					/* Open the cluster member elements dict                  */

					sprintf(print_data, "\"eles\" : {");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Loop through the cluster member's elements             */

					ader_mat_ele = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ELES_PTR];

					while(ader_mat_ele > VALID_PTR)
					{

						/* Open the element dictionary                        */

						sprintf(print_data, "\"%ld\" : {", (long)RDB[ader_mat_ele + ADER_MAT_ELE_Z]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Give the amount of the element in the material     */

						sprintf(print_data, "\"amount\" : %.16f,",
								            RDB[ader_mat_ele + ADER_MAT_ELE_FRAC]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the del col id entry                        */

						sprintf(print_data, "\"del_col_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_COL_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the fut col id entry                        */

						sprintf(print_data, "\"fut_col_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the bal row id entry                        */

						sprintf(print_data, "\"bal_row_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the del row id entry                        */

						sprintf(print_data, "\"del_row_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the fut row id entry                        */

						sprintf(print_data, "\"fut_row_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the iso row id entry                        */

						sprintf(print_data, "\"iso_row_id\" : %ld,",
								            (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISO_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Provide the amount removed by rem tables           */

						sprintf(print_data, "\"amount_removed\" : %0.16f,",
								            ADERGetTargetRemovalAmount(ader_mat_cluster_mem,
								            		                   (long)RDB[ader_mat_ele + ADER_MAT_ELE_Z],
																	   0));

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Open the element's isos dictionary                 */

						sprintf(print_data, "\"isos\" : {");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Now loop through the element's isos                */

						ader_mat_ele_iso = (long)RDB[ader_mat_ele + ADER_MAT_ELE_ISOS_PTR];

						while(ader_mat_ele_iso > VALID_PTR)
						{

							/* Get the ZAI of the isotope                     */

							ader_mat_iso = (long)RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

							mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

							nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

							/* Create the element iso's dict entry            */

							if(NextItem(ader_mat_ele_iso) > VALID_PTR)
							{

								sprintf(print_data, "\"%ld\" : %.16f,",
										            (long)RDB[nuc + NUCLIDE_ZAI],
													RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_FRAC]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							}
							else
							{

								sprintf(print_data, "\"%ld\" : %.16f",
										            (long)RDB[nuc + NUCLIDE_ZAI],
													RDB[ader_mat_ele_iso + ADER_MAT_ELE_ISO_FRAC]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							}

							ader_mat_ele_iso = NextItem(ader_mat_ele_iso);

						}

						/* Close the element's isos dictionary                */

						sprintf(print_data, "},");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

				        /* Now we search the materials cnt tables to see if   */
						/* this element is controlled                         */

						controlled = 0;

				        ader_mat_cnt = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_CNT_TBLS_PTR];

				        while(ader_mat_cnt > VALID_PTR)
				        {

				            /* The mat cnt simply points to the ader cnt      */

				            ader_cnt = (long)RDB[ader_mat_cnt + ADER_MAT_CNT_TBL_PTR];

				            ader_cnt_ent = (long)RDB[ader_cnt + ADER_CONTROL_ENT_PTR];

				            while(ader_cnt_ent > VALID_PTR)
				            {

				                /* go though the ader cnt's entries, if a Z   */
				            	/* matches this element you have a match,     */
				            	/* break this loop and exit the next          */

				                if((long)RDB[ader_mat_ele + ADER_MAT_ELE_Z] == (long)RDB[ader_cnt_ent + ADER_CONTROL_ENT_Z])
				                {

				                    controlled = 1;

				                    break;

				                }

				                ader_cnt_ent = NextItem(ader_cnt_ent);

				            }

				            /* Control was found, break the overall cnt loop */

				            if(controlled > 0)
				            {

				                break;

				            }

				            ader_mat_cnt = NextItem(ader_mat_cnt);

				        }

				        /* Create the elemental control entry                 */

				        if(controlled > 0)
				        {

							sprintf(print_data, "\"control\" : \"yes\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				        }
				        else
				        {

							sprintf(print_data, "\"control\" : \"no\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				        }

						/* Close the element dictionary                       */

						if(NextItem(ader_mat_ele) > VALID_PTR)
						{

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}
						else
						{

							sprintf(print_data, "}");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}

						tab_level--;

						ader_mat_ele = NextItem(ader_mat_ele);

					}

					/* Close the cluster member elements dict                 */

					sprintf(print_data, "},");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level--;

					/* Open the cluster member isos dict                      */

					sprintf(print_data, "\"isos\" : {");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Loop through the cluster member's isotopes             */

					ader_mat_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

					while(ader_mat_iso > VALID_PTR)
					{

						/* Get the ZAI of the isotope in question             */

						mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

						nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

						/* Open the iso dictionary                            */

						sprintf(print_data, "\"%ld\" : {",
								            (long)RDB[nuc + NUCLIDE_ZAI]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Give the amount of the isotope in the material     */

						sprintf(print_data, "\"amount\" : %.16f,",
								            RDB[mat_iso + COMPOSITION_ADENS] /
											RDB[ader_mat_cluster_mem + MATERIAL_ADENS]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the del col id entry                        */

						sprintf(print_data, "\"del_col_id\" : %ld,",
								            (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_COL_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the fut col id entry                        */

						sprintf(print_data, "\"fut_col_id\" : %ld,",
								            (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the bal row id entry                        */

						sprintf(print_data, "\"bal_row_id\" : %ld,",
								            (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the del row id entry                        */

						sprintf(print_data, "\"del_row_id\" : %ld,",
								            (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Create the fut row id entry                        */

						sprintf(print_data, "\"fut_row_id\" : %ld,",
								            (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						if(RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_RHO_WEIGHT] > 0.0)
						{

							/* Provide the isotope reactivity entries as well     */
							/* First, they will have to be calculated. This relies*/
							/* on some support functions and the assumption that  */
							/* the first burnup step is being used                */

							t1 = 0.0;

							t2 = RDB[DATA_BURN_TIME_INTERVAL];

							bias = ADERGetEigenBias(dep, ader_mat_cluster_mem, t1, t2);

							dep = (long)RDB[DATA_BURN_PTR_DEP];

							ader_data = (long)RDB[DATA_PTR_ADER];

							/* The below equation should resemble...              */
							/* ( ( ( K_max / (( 1 - rho_l ) * bias ) ) * Sigma_a ) - ( nu * Sigma_f ) ) */

							k_max_inf = (RDB[ader_data + ADER_K_MAX] /
									     ((1.0 - ADERAverageValue(RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
									        		              RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
															      RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
																  t1, t2, dep)) *
									       bias));

							loss_max = k_max_inf * ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
									                                RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
																	RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
																	t1, t2, dep);

							production_max = ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
									                          RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
															  RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
															  t1, t2, dep);

							iso_max_reac = loss_max - production_max;

							iso_max_dec = production_max - loss_max;

							k_min_inf = (RDB[ader_data + ADER_K_MIN] /
									     ((1.0 - ADERAverageValue(RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_BOS],
									        		              RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_EOS],
															      RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_SYS_LEAKAGE_PS1],
																  t1, t2, dep)) *
									       bias));

							loss_min = k_min_inf * ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_BOS],
									                                RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_EOS],
																	RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_PS1],
																	t1, t2, dep);

							production_min = ADERAverageValue(RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_BOS],
									                          RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_EOS],
															  RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_PS1],
															  t1, t2, dep);

							iso_min_reac = loss_min - production_min;

							iso_min_dec = production_min - loss_min;

							sprintf(print_data, "\"max_reac\" : %0.16f,",
									            iso_max_reac);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"min_reac\" : %0.16f,",
									            iso_min_reac);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"max_dec\" : %0.16f,",
									            iso_max_dec);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"min_dec\" : %0.16f,",
									            iso_min_dec);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}

						/* Provide the amount removed by rem tables           */

						sprintf(print_data, "\"amount_removed\" : %0.16f,",
								            ADERGetTargetRemovalAmount(ader_mat_cluster_mem,
								            		                   0,
																	   (long)RDB[nuc + NUCLIDE_ZAI]));

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				        /* Now we search the materials cnt tables to see if   */
						/* this isotope is controlled                         */

						controlled = 0;

				        ader_mat_cnt = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_CNT_TBLS_PTR];

				        while(ader_mat_cnt > VALID_PTR)
				        {

				            /* The mat cnt simply points to the ader cnt      */

				            ader_cnt = (long)RDB[ader_mat_cnt + ADER_MAT_CNT_TBL_PTR];

				            ader_cnt_ent = (long)RDB[ader_cnt + ADER_CONTROL_ENT_PTR];

				            while(ader_cnt_ent > VALID_PTR)
				            {

				                /* go though the ader cnt's entries, if a ZAI */
				            	/* matches this isotope you have a match,     */
				            	/* break this loop and exit the next          */

				                if((long)RDB[nuc + NUCLIDE_ZAI] == (long)RDB[ader_cnt_ent + ADER_CONTROL_ENT_ZAI])
				                {

				                    controlled = 1;

				                    break;

				                }

				                ader_cnt_ent = NextItem(ader_cnt_ent);

				            }

				            /* Control was found, break the overall cnt loop */

				            if(controlled > 0)
				            {

				                break;

				            }

				            ader_mat_cnt = NextItem(ader_mat_cnt);

				        }

				        /* Create the isotope control entry                   */

				        if(controlled > 0)
				        {

							sprintf(print_data, "\"control\" : \"yes\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				        }
				        else
				        {

							sprintf(print_data, "\"control\" : \"no\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				        }

						/* Close the isotope dictionary                       */

						if(NextItem(ader_mat_iso) > VALID_PTR)
						{

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}
						else
						{

							sprintf(print_data, "}");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}

						tab_level--;

						ader_mat_iso = NextItem(ader_mat_iso);

					}

					/* Close the cluster member isotope dict                  */

					sprintf(print_data, "},");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level--;

					/* Open the CMP groups dict                                */

					sprintf(print_data, "\"cmp_groups\" : {");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Loop through the material's cmp groups                 */

					ader_mat_cmp = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_CMPS_PTR];

					while(ader_mat_cmp > VALID_PTR)
					{

						/* Save the name to print buffer                      */

						strcpy(print_buffer,
							   GetText(ader_mat_cmp + ADER_MAT_CMP_ID));

						/* Now determine if this cmp group has a unique name  */
						/* If not, modify the name for testing                */

						name_counter = 0;

						ader_mat_search_cmp = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_CMPS_PTR];

						while(ader_mat_search_cmp > VALID_PTR)
						{

							if(ader_mat_cmp == ader_mat_search_cmp)
							{

								/* There is no need to count past the cmp     */
								/* group in question                          */

								break;

							}

							if(strcmp(GetText(ader_mat_cmp + ADER_MAT_CMP_ID),
									  GetText(ader_mat_search_cmp + ADER_MAT_CMP_ID)) == 0)
							{

								name_counter++;

							}

							ader_mat_search_cmp = NextItem(ader_mat_search_cmp);

						}

						if(name_counter > 0)
						{

							sprintf(print_data, "_%ld", name_counter);

							strcat(print_buffer, print_data);

						}

						/* Now check to see if the print name needs           */
						/* modification                                       */

						/* Open the cmp group's dict                          */

						sprintf(print_data, "\"%s\" : {", print_buffer);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Provide the WDB address, helps with id             */

						sprintf(print_data, "\"WDB_address\" : %ld,", ader_mat_cmp);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Provide the cmp group's col id                     */

						sprintf(print_data, "\"col_id\" : %ld,",
								            (long)RDB[ader_mat_cmp + ADER_MAT_CMP_COL_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Open the cmp group's bounds list                   */

						sprintf(print_data, "\"col_bounds\" : [");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						ader_mat_cmp_rng = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RNG_PTR];

						if(ader_mat_cmp_rng > VALID_PTR)
						{

							sprintf(print_data, "%.16f,",
									            RDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MIN]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "%.16f",
									            RDB[ader_mat_cmp_rng + ADER_MAT_CMP_RNG_MAX]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}
						else
						{

							sprintf(print_data, "\"NULL\",");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"NULL\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						}

						/* Close the column's bounds list                     */

						sprintf(print_data, "],");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

						/* Provide the cmp group's sum row id if it exists    */

						if((long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR] > VALID_PTR)
						{

							sprintf(print_data, "\"sum_row_id\" : %ld,",
									            (long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							/* Open the sum grps dict                         */

							sprintf(print_data, "\"sum_grps\" : {");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							/* Loop through the sum grps                      */

							ader_mat_cmp_sum_grp = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR];

							while(ader_mat_cmp_sum_grp > VALID_PTR)
							{

								/* Print out the key value pair, i.e., the    */
								/* the sum grp name and weight                */

								if(NextItem(ader_mat_cmp_sum_grp) > VALID_PTR)
								{

									sprintf(print_data, "\"%ld\" : %.16f,",
											            (long)RDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_PTR],
											            RDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_WEIGHT]);

									ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								}
								else
								{

									sprintf(print_data, "\"%ld\" : %.16f",
											            (long)RDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_PTR],
											            RDB[ader_mat_cmp_sum_grp + ADER_MAT_GRP_SUM_GRP_WEIGHT]);

									ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								}

								ader_mat_cmp_sum_grp = NextItem(ader_mat_cmp_sum_grp);

							}

							/* Close the sum grps dict                        */

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}
						else
						{

							sprintf(print_data, "\"sum_row_id\" : \"NULL\",");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							/* Set the sum_grps dict to NULL                  */

							sprintf(print_data, "\"sum_grps\" : {");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							sprintf(print_data, "\"NULL\" : \"NULL\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}

						/* Open the rto list                                  */

						ader_mat_cmp_rto = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RTOS_PTR];

						if(ader_mat_cmp_rto > VALID_PTR)
						{

							sprintf(print_data, "\"cmp_rtos\" : [");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							while(ader_mat_cmp_rto > VALID_PTR)
							{

								/* Open the cmp rto dict                      */

								sprintf(print_data, "{");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level++;

								/* Provide the name and rto group name        */

								ader_mat_cmp_rto_grp2 = (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

								sprintf(print_data, "\"grp2\" : \"%s\",",
										            GetText(ader_mat_cmp_rto_grp2 + ADER_MAT_CMP_ID));

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Provide the id of the rto group            */

								sprintf(print_data, "\"grp2_WDB_address\" : %ld,",
										            ader_mat_cmp_rto_grp2);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Provide the rto max value                  */

								sprintf(print_data, "\"max\" : %.16f,",
										            RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Provide the rto min value                  */

								sprintf(print_data, "\"min\" : %.16f,",
										            RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Provide the rto max row value              */

								sprintf(print_data, "\"max_row\" : %ld,",
										            (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX_ROW_ID]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Provide the rto min row value              */

								sprintf(print_data, "\"min_row\" : %ld",
										            (long)RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN_ROW_ID]);

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								/* Close the cmp rto dict                     */

								if(NextItem(ader_mat_cmp_rto) > VALID_PTR)
								{

									sprintf(print_data, "},");

									ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

									tab_level--;

								}
								else
								{

									sprintf(print_data, "}");

									ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

									tab_level--;

								}

								ader_mat_cmp_rto = NextItem(ader_mat_cmp_rto);

							}

						}
						else
						{

							sprintf(print_data, "\"cmp_rtos\" : [");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							sprintf(print_data, "\"NULL\"");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);


						}

						/* Close the cmp rtos list                            */

						sprintf(print_data, "],");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

						/* Open the cmp eles list                             */

						sprintf(print_data, "\"eles\" : [");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Loop through the cmp eles                          */

						ader_mat_cmp_ele = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_ELES_PTR];

						while(ader_mat_cmp_ele > VALID_PTR)
						{

							/* Open the cmp ele dict                          */

							sprintf(print_data, "{");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							/* Enter the ele information                      */

							sprintf(print_data, "\"%ld\" : %.16f",
									            (long)RDB[ader_mat_cmp_ele + ADER_MAT_GRP_ELE_Z],
												RDB[ader_mat_cmp_ele + ADER_MAT_GRP_ELE_FRAC]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							/* Close the cmp ele dict                         */

							if(NextItem(ader_mat_cmp_ele) > VALID_PTR)
							{

								sprintf(print_data, "},");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}
							else
							{

								sprintf(print_data, "}");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}

							ader_mat_cmp_ele = NextItem(ader_mat_cmp_ele);

						}

						/* Close the cmp's eles list                          */

						sprintf(print_data, "],");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

						/* Open the cmp isos list                             */

						sprintf(print_data, "\"isos\" : [");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Loop through the cmp isos                          */

						ader_mat_cmp_iso = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_ISOS_PTR];

						while(ader_mat_cmp_iso > VALID_PTR)
						{

							/* Open the cmp iso dict                          */

							sprintf(print_data, "{");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							/* Get the ZAI                                    */

							ader_mat_iso = (long)RDB[ader_mat_cmp_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

							mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

							nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

							/* Enter the iso information                      */

							sprintf(print_data, "\"ZAI\" : %ld,",
									            (long)RDB[nuc + NUCLIDE_ZAI]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"ele_frac\" : %0.8f,",
									            RDB[ader_mat_cmp_iso + ADER_MAT_GRP_ISO_ELE_FRAC]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "\"grp_frac\" : %0.8f",
									            RDB[ader_mat_cmp_iso + ADER_MAT_GRP_ISO_FRAC]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							/* Close the cmp iso dict                         */

							if(NextItem(ader_mat_cmp_iso) > VALID_PTR)
							{

								sprintf(print_data, "},");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}
							else
							{

								sprintf(print_data, "}");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}

							ader_mat_cmp_iso = NextItem(ader_mat_cmp_iso);

						}

						/* Close the cmp's isos list                          */

						sprintf(print_data, "]");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

						/* Close the cmp group's dict                         */

						if(NextItem(ader_mat_cmp) > VALID_PTR)
						{

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}
						else
						{

							sprintf(print_data, "}");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}


						ader_mat_cmp = NextItem(ader_mat_cmp);

					}

					/* Close the cmp groups dict                              */

					sprintf(print_data, "},");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level--;

					/* Open the streams dict                                  */

					sprintf(print_data, "\"streams\" : {");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					tab_level++;

					/* Now loop through the material streams but use the      */
					/* ADEROutputMaterialCompMatrixStreamData function to do  */
					/* it so that it can tunnel into summation streams        */

					ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

					ADEROutputMaterialCompMatrixStreamData(ader_mat_cluster_mem,
							                               ader_mat_cluster_mem_stream,
														   0, fp, 0, tab_level,
													       tab_length);

					ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

					ADEROutputMaterialCompMatrixStreamData(ader_mat_cluster_mem,
							                               ader_mat_cluster_mem_stream,
														   0, fp, 1, tab_level,
													       tab_length);

					ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

					ADEROutputMaterialCompMatrixStreamData(ader_mat_cluster_mem,
							                               ader_mat_cluster_mem_stream,
														   0, fp, 2, tab_level,
													       tab_length);

					ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

					ADEROutputMaterialCompMatrixStreamData(ader_mat_cluster_mem,
							                               ader_mat_cluster_mem_stream,
														   0, fp, 3, tab_level,
													       tab_length);

					/* Close the streams dict                                 */

					if((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_OXI_PTR] < VALID_PTR &&
					   (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRESERVES_PTR] < VALID_PTR)
					{

						sprintf(print_data, "}");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

					}
					else
					{

						sprintf(print_data, "},");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

					}

					/* Get the oxidation data                                 */

					ader_mat_cluster_mem_oxi = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_OXI_PTR];

					/* If the oxidation data exists...     					  */

					if(ader_mat_cluster_mem_oxi > VALID_PTR)
					{

						/* Open the oxidation info dict                       */

						sprintf(print_data, "\"oxi\" : {");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Get the oxidation data                             */

						ader_mat_cluster_mem_oxi = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_OXI_PTR];

						/* Provide the oxidation row data                     */

						sprintf(print_data, "\"row_id\" : %ld,", (long)RDB[ader_mat_cluster_mem_oxi + ADER_MAT_OXI_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Give min and max oxi values                        */

						sprintf(print_data, "\"oxi_max\": %0.8f,", RDB[ader_mat_cluster_mem_oxi + ADER_MAT_OXI_MAX]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						sprintf(print_data, "\"oxi_min\": %0.8f,", RDB[ader_mat_cluster_mem_oxi + ADER_MAT_OXI_MIN]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Open the elements oxidation values dictionary      */

						sprintf(print_data, "\"oxi_states\" : {");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Get the ader oxidation table, it has the element   */
						/* values                                             */

						ader_oxi = (long)RDB[ader_mat_cluster_mem_oxi + ADER_MAT_OXI_TBL_PTR];

						ader_oxi_ele = (long)RDB[ader_oxi + ADER_OXI_ELES_PTR];

						while(ader_oxi_ele > VALID_PTR)
						{

							/* Open the elements oxi data list                */

							sprintf(print_data, "\"%ld\" : [", (long)RDB[ader_oxi_ele + ADER_OXI_ELE_Z]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level++;

							/* Populate the list                              */

							sprintf(print_data, "%0.8f,", RDB[ader_oxi_ele + ADER_OXI_ELE_VAL]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							sprintf(print_data, "%0.8f", RDB[ader_oxi_ele + ADER_OXI_ELE_WEIGHT]);

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							/* Close the element oxi data list                */

							if(NextItem(ader_oxi_ele) > VALID_PTR)
							{

								sprintf(print_data, "],");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}
							else
							{

								sprintf(print_data, "]");

								ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

								tab_level--;

							}

							ader_oxi_ele = NextItem(ader_oxi_ele);

						}

						/* Close the elements oxidation values dictionary     */

						sprintf(print_data, "}");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

						/* Close the oxidation info dict                      */

						if((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRESERVES_PTR] < VALID_PTR)
						{

							sprintf(print_data, "}");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}
						else
						{

							sprintf(print_data, "},");

							ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

							tab_level--;

						}

					}

					/* Get the preservation data                              */

					ader_mat_cluster_mem_pres = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRESERVES_PTR];

					/* If there is preservation data                          */

					if(ader_mat_cluster_mem_pres > VALID_PTR)
					{

						/* Open the preservation info dict                    */

						sprintf(print_data, "\"pres\" : {");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level++;

						/* Provide preservation data                          */

						sprintf(print_data, "\"row_id\" : %ld," , (long)RDB[ader_mat_cluster_mem_pres + ADER_MAT_PRESERVE_ROW_ID]);

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						sprintf(print_data, "\"type\" : \"%s\"" , GetText(ader_mat_cluster_mem_pres + ADER_MAT_PRESERVE_ENT));

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						/* Close the preservation info dict                   */

						sprintf(print_data, "}");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

						tab_level--;

					}

					/* Close the member info dict                             */

					if(NextItem(ader_mat_cluster_mem_ent) > VALID_PTR)
					{

						sprintf(print_data, "},");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}
					else
					{

						/* Final list items can not have a trailing ","       */

						sprintf(print_data, "}");

						ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

					}

					tab_level--;

					ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

				}

				/* Close the members info dict                                */

				sprintf(print_data, "}");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level--;

				/* This search is needed to know if a comma is needed or not  */

				another_cluster = 0;

				search_mat = NextItem(mat);

				while(search_mat > VALID_PTR)
				{

					search_ader_mat_data = (long)RDB[search_mat + MATERIAL_ADER_DATA];

					if(search_ader_mat_data > VALID_PTR)
					{

						if((long)RDB[search_ader_mat_data + ADER_MAT_CLUSTER_PARENT_PTR] == search_mat)
						{

							another_cluster = 1;

							break;

						}

					}

					search_mat = NextItem(search_mat);

				}

				if(another_cluster > 0)
				{

					sprintf(print_data, "},");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				}
				else
				{

					sprintf(print_data, "}");

					ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				}

				tab_level--;

			}

		}

		mat = NextItem(mat);

	}

	/* Close the clusters dict                                                */

	sprintf(print_data, "},");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);\

	tab_level--;

	/* Set the number of clusters                                             */

	sprintf(print_data, "\"num_clusters\" : %ld", num_clusters);

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);


	/* Print the dictionary close for the original cluster dictionary         */

	sprintf(print_data, "}");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

	tab_level--;

	/* Print the list close for the json file                                 */

	sprintf(print_data, "]");

	ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

	tab_level--;

	/* Close the file                                                         */

	fclose(fp);

}
