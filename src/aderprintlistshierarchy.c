/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintlistshierarchy.c                      */
/*                                                                           */
/* Created:       2016/03/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Provides information regarding ADER memory lists for debug   */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintListsHierarchy:"

void ADERPrintListsHierarchy()
{

    static char *test_file_out = "ADER_Memory_Lists.test";
    char print_data[256], file_out[256];
    char *mat_name = NULL;
    FILE *fp = NULL, *fp1 = NULL;
    double filled_entries = 0, percent_empty = 0, total_entries = 0;
    double **dump_vector = NULL;
    long ader_cluster = 0, ader_cluster_ent = 0, ader_data = 0, ader_mat_cluster_mem = 0;
    long ader_mat_cluster_mem_ader_data = 0, ader_mat_cluster_mem_cmp = 0;
    long ader_mat_cluster_mem_cmp_rto = 0, ader_mat_cluster_mem_ele = 0;
    long ader_mat_cluster_mem_ent = 0, ader_mat_cluster_mem_iso = 0;
    long ader_mat_cluster_mem_pres = 0;
    long ader_mat_cluster_mem_stream = 0, ader_mat_cmp = 0, ader_mat_cmp_rto = 0, ader_mat_cmp_rto_grp2 = 0;
	long ader_mat_data = 0, ader_mat_ele = 0, ader_mat_matrix_data = 0, ader_mat_matrix_col = 0;
	long ader_mat_matrix_col_row = 0, ader_mat_iso = 0, ader_mat_pres = 0, ader_mat_stream = 0;
	long ader_mat_stream_shadow = 0, ader_mat_stream_sum_ent = 0, found = 0, mat = 0, mat_iso = 0;
	long nuc, num_cmp_rows = 0, num_eles = 0, num_ents = 0, num_isos = 0, num_oxi = 0, num_pres = 0;
	long num_reac = 0, num_stream_cols = 0, num_stream_rows = 0;

    if(1 < 2)
    {

        if ((fp = fopen(test_file_out, "w")) == NULL)
        {
            Die(FUNCTION_NAME, "Unable to open ADER memory file for writing");
        }

        fprintf(fp, "************************************ Begin *************************************\n");
        fprintf(fp, "\n");
        fprintf(fp, "ADER Memory Lists\n");
        fprintf(fp, "\n");
        fprintf(fp, "********************************************************************************\n");
        fprintf(fp, "Begin Materials:\n\n");

        /* Loop through materials, print their name and RDB index             */

        mat = (long)RDB[DATA_PTR_M0];

        while(mat > VALID_PTR)
        {

        	sprintf(print_data, ", %ld\n\n", mat);

        	fprintf(fp, "%s", GetText(mat + MATERIAL_PTR_NAME));

        	fprintf(fp, "%s", print_data);

        	mat = NextItem(mat);

        }

        fprintf(fp, "End materials:\n\n");

        /* Loop through ADER clusters, print the parent & all cluster members */

        ader_data = (long)RDB[DATA_PTR_ADER];

        ader_cluster = (long)RDB[ader_data + ADER_CLUSTERS_PTR];

        fprintf(fp, "Begin ADER Clusters:\n\n");

        while(ader_cluster > VALID_PTR)
        {

        	sprintf(print_data, "Cluster parent: %s\n",
        			GetText(ader_cluster + ADER_CLUSTER_PARENT_ID));

        	fprintf(fp, "%s", print_data);

        	sprintf(print_data, "    Cluster members:\n");

        	fprintf(fp, "%s", print_data);

        	ader_cluster_ent = (long)RDB[ader_cluster + ADER_CLUSTER_ENT_PTR];

        	while(ader_cluster_ent > VALID_PTR)
        	{

            	sprintf(print_data, "    %s\n",
            			GetText(ader_cluster_ent + ADER_CLUSTER_ENT_ID));

            	fprintf(fp, "%s", print_data);

        		ader_cluster_ent = NextItem(ader_cluster_ent);

        	}

        	sprintf(print_data, "\n");

        	fprintf(fp, "%s", print_data);

        	ader_cluster = NextItem(ader_cluster);

        }

        fprintf(fp, "End ADER Clusters:\n\n");

        /* Print out the material ader clusters, parents and members          */

        fprintf(fp, "Begin Material Clusters:\n\n");

        mat = (long)RDB[DATA_PTR_M0];

        while(mat > VALID_PTR)
        {

        	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

        	if(ader_mat_data > VALID_PTR)
        	{

            	fprintf(fp, "%s\n", GetText(mat + MATERIAL_PTR_NAME));

            	sprintf(print_data, "Cluster parent: %ld\n",
            			(long)RDB[ader_mat_data + ADER_MAT_CLUSTER_PARENT_PTR]);

            	fprintf(fp, "%s", print_data);

            	fprintf(fp, "    Cluster Members:\n");

            	ader_mat_cluster_mem = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

            	while(ader_mat_cluster_mem > VALID_PTR)
            	{

                	sprintf(print_data, "    %s, %ld, cluster_mem: %ld\n",
                			GetText((long)RDB[ader_mat_cluster_mem + ADER_MAT_CLUSTER_MEM_PTR] + MATERIAL_PTR_NAME),
                			(long)RDB[ader_mat_cluster_mem + ADER_MAT_CLUSTER_MEM_PTR],
							ader_mat_cluster_mem);

                	fprintf(fp, "%s", print_data);

            		ader_mat_cluster_mem = NextItem(ader_mat_cluster_mem);

            	}

            	fprintf(fp, "\n");

        	}

        	mat = NextItem(mat);

        }

        fprintf(fp, "End Materials Clusters:\n\n");

        /* Print out material ader information                                */

        fprintf(fp, "Begin Materials:\n\n");

        mat = (long)RDB[DATA_PTR_M0];

        while(mat > VALID_PTR)
        {

        	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

        	if(ader_mat_data < VALID_PTR)
        	{

        		mat = NextItem(mat);

        		continue;

        	}

        	mat_name = GetText(mat + MATERIAL_PTR_NAME);

        	/* Go ahead and output the isotope data lists for this material   */

            sprintf(file_out, "%s_Isotopes_WDB_Address_List.test",
            		mat_name);

        	if ((fp1 = fopen(file_out, "w")) == NULL)
        	{

        		Die(FUNCTION_NAME, "Unable to open material isotope list file for writing");

        	}

        	fprintf(fp1, "Material %s Isotopes WDB Address List Key:\n\n", mat_name);

        	fprintf(fp1, "Material name, Isotope Zai\n");

        	fprintf(fp1, "    MATERIAL_COMPOSITION_PTR: WDB address for isotope\n");

        	fprintf(fp1, "    COMPOSITION_PTR_NUCLIDE: WDB address for nuclide\n");

        	fprintf(fp1, "    ADER_MAT_ISOS_PTR: WDB address for ader isotope\n");

        	fprintf(fp1, "    ADER_MAT_ISO_BURN_INDEX: Burnup matrix index\n");

        	fprintf(fp1, "    ADER_MAT_ISO_DEL_COL_ID: Optimization matrix del column index\n");

        	fprintf(fp1, "    ADER_MAT_ISO_FUT_COL_ID: Optimization matrix fut column index\n");

        	fprintf(fp1, "    ADER_MAT_ISO_BAL_ROW_ID: Optimization matrix bal row index\n");

        	fprintf(fp1, "    ADER_MAT_ISO_DEL_ROW_ID: Optimization matrix del row index\n");

        	fprintf(fp1, "    ADER_MAT_ISO_FUT_ROW_ID: Optimization matrix fut row index\n");

        	fprintf(fp1,"********************************************************************************\n");

        	/* Count the isos                                                 */

        	num_cmp_rows = 0;

        	num_stream_cols = 0;

        	num_stream_rows = 0;

        	num_isos = 0;

        	mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

        	while(mat_iso > VALID_PTR)
        	{

        		nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        		found = (long)RDB[nuc + NUCLIDE_ZAI];

        		ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

        		while(ader_mat_iso > VALID_PTR)
        		{

        			if(mat_iso == (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR])
        			{

        				found = -10000;

        				break;

        			}

        			ader_mat_iso = NextItem(ader_mat_iso);

        		}

            	fprintf(fp1, "%s, %ld\n", mat_name, (long)RDB[nuc + NUCLIDE_ZAI]);

            	fprintf(fp1, "    MATERIAL_COMPOSITION_PTR: %ld\n", mat_iso);

            	fprintf(fp1, "    COMPOSITION_PTR_NUCLIDE: %ld\n", nuc);

            	if(found == -10000)
            	{

                	fprintf(fp1, "    ADER_MAT_ISOS_PTR: %ld\n", ader_mat_iso);

                	fprintf(fp1, "    ADER_MAT_ISO_BURN_INDEX: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]);

                	fprintf(fp1, "    ADER_MAT_ISO_DEL_COL_ID: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_COL_ID]);

                	fprintf(fp1, "    ADER_MAT_ISO_FUT_COL_ID: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID]);

                	fprintf(fp1, "    ADER_MAT_ISO_BAL_ROW_ID: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID]);

                	fprintf(fp1, "    ADER_MAT_ISO_DEL_ROW_ID: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID]);

                	fprintf(fp1, "    ADER_MAT_ISO_FUT_ROW_ID: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID]);

            	}
            	else if( found == -1)
            	{

                	fprintf(fp1, "    ADER_MAT_ISOS_PTR: N/A\n");

                	fprintf(fp1, "    ADER_MAT_ISO_BURN_INDEX: %ld\n", (long)RDB[ader_mat_data + ADER_MAT_FAKE_ISO_BURN_INDEX]);

            	}
            	else
            	{

                	fprintf(fp1, "    ADER_MAT_ISOS_PTR: ERROR: NO ADER ISOTOPE\n");

            	}

            	fprintf(fp1, "\n");

        		num_isos++;

        		mat_iso = NextItem(mat_iso);

        	}

        	fclose(fp1);

        	if(ader_mat_data > VALID_PTR)
        	{

            	sprintf(print_data, ", %ld\n\n", mat);

            	fprintf(fp, "%s", GetText(mat + MATERIAL_PTR_NAME));

            	fprintf(fp, "%s", print_data);

            	fprintf(fp, "Isos: %ld\n\n", num_isos);

            	/* Loop through any cmp groups                                */

                fprintf(fp, "    Material cmp groups:\n\n");

            	ader_mat_cmp = (long)RDB[ader_mat_data + ADER_MAT_CMPS_PTR];

            	while(ader_mat_cmp > VALID_PTR)
            	{

            		num_cmp_rows++;

                	fprintf(fp, "    %s : %ld\n",
                			GetText(ader_mat_cmp + ADER_MAT_CMP_ID),
							ader_mat_cmp);

                    fprintf(fp, "        Cmp rtos:\n\n");

                    /* Loop through any rtos attached to this group           */

                    ader_mat_cmp_rto = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_RTOS_PTR];

                    while(ader_mat_cmp_rto > VALID_PTR)
                    {

                    	num_cmp_rows++;

                        fprintf(fp, "        Rto_WDB_Address: %ld\n",
                        		ader_mat_cmp_rto);

                    	ader_mat_cmp_rto_grp2 = (long)RDB[ ader_mat_cmp_rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

                        fprintf(fp, "        2nd_Cmp_Group: %s\n",
                        		GetText(ader_mat_cmp_rto_grp2 + ADER_MAT_CMP_ID));

                        fprintf(fp, "        2nd_WDB_Address: %ld\n",
                        		ader_mat_cmp_rto_grp2);

                        fprintf(fp, "        Max: %f\n",
                        		RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX]);

                        if(RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MAX] > 0.0)
                        {

                        	num_cmp_rows++;

                        }

                        fprintf(fp, "        Min: %f\n",
                        		RDB[ader_mat_cmp_rto + ADER_MAT_CMP_RTO_MIN]);

                        fprintf(fp, "\n");

                    	ader_mat_cmp_rto = NextItem(ader_mat_cmp_rto);

                    }

                    /* Report if group is a summation group                   */

                    if((long)RDB[ader_mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR] > VALID_PTR)
                    {

                    	num_cmp_rows++;

                        fprintf(fp, "        Sum Grp\n");

                    }

            		ader_mat_cmp = NextItem(ader_mat_cmp);

            	}

            	/* Loop through material streams                              */

            	/* Open the stream isotopes file                              */

                sprintf(file_out, "%s_Stream_Isotopes_WDB_Address_List.test",
                		mat_name);

            	if ((fp1 = fopen(file_out, "w")) == NULL)
            	{

            		Die(FUNCTION_NAME, "Unable to open material isotope list file for writing");

            	}

            	fprintf(fp1, "Material %s Stream Isotopes WDB Address List Key:\n\n", mat_name);

            	fprintf(fp1, "Material name, Stream name, Stream source, stream destination, Isotope Zai\n");

            	fprintf(fp1, "    ADER_MAT_STREAM: WDB address for stream\n");

            	fprintf(fp1, "    ADER_MAT_STREAM_ISOS_PTR: WDB address for stream isotope\n");

            	fprintf(fp1, "    MATERIAL_COMPOSITION_PTR: WDB address for isotope\n");

            	fprintf(fp1, "    COMPOSITION_PTR_NUCLIDE: WDB address for nuclide\n");

            	fprintf(fp1, "    ADER_MAT_ISOS_PTR: WDB address for ader isotope\n");

            	fprintf(fp1, "    ADER_MAT_ISO_BURN_INDEX: Burnup matrix index\n");

            	fprintf(fp1,"********************************************************************************\n\n");

                fprintf(fp, "    Material streams:\n\n");

            	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_FEED_STREAMS_PTR];

            	while(ader_mat_stream > VALID_PTR)
            	{

            		ADERPrintMaterialStreamIsotopes(ader_mat_stream, fp1, mat);

            		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_stream, 0, 0);

					fprintf(fp, "    %s, %ld",
							GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
							ader_mat_stream);

            	    if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0))
            	    {

            	    	fprintf(fp, ", removal table");

            	    }

            	    if(((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] != 0))
            	    {

            	    	ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            	    	if(ader_mat_stream_shadow < 0)
            	    	{

            	    		ader_mat_stream_shadow = ader_mat_stream_shadow * -1;

            	    	}

            	    	fprintf(fp, ", shadow [ %s, %ld ]",
            	    			GetText(ader_mat_stream_shadow + ADER_MAT_STREAM_ID),
								ader_mat_stream_shadow);

            	    }

            	    fprintf(fp, "\n");

            	    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
            	    {

            	    	num_stream_rows++;

                	    fprintf(fp, "        Summation stream\n");

            	    }


            	    ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            	    ADERPrintSumStreams(ader_mat_stream_sum_ent, fp, 1);

            		ader_mat_stream = NextItem(ader_mat_stream);

            	}

            	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REAC_STREAMS_PTR];

            	while(ader_mat_stream > VALID_PTR)
            	{

            		ADERPrintMaterialStreamIsotopes(ader_mat_stream, fp1, mat);

            		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_stream, 0, 0);

					fprintf(fp, "    %s, %ld",
							GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
							ader_mat_stream);

            	    if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0))
            	    {

            	    	fprintf(fp, ", removal table");

            	    }

            	    if(((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] != 0))
            	    {

            	    	ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            	    	if(ader_mat_stream_shadow < 0)
            	    	{

            	    		ader_mat_stream_shadow = ader_mat_stream_shadow * -1;

            	    	}

            	    	fprintf(fp, ", shadow [ %s, %ld ]",
            	    			GetText(ader_mat_stream_shadow + ADER_MAT_STREAM_ID),
								ader_mat_stream_shadow);

            	    }

            	    fprintf(fp, "\n");

            	    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
            	    {

            	    	num_stream_rows++;

                	    fprintf(fp, "        Summation stream\n");

            	    }


            	    ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            	    ADERPrintSumStreams(ader_mat_stream_sum_ent, fp, 1);

            		ader_mat_stream = NextItem(ader_mat_stream);

            	}

            	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REDOX_STREAMS_PTR];

            	while(ader_mat_stream > VALID_PTR)
            	{

            		ADERPrintMaterialStreamIsotopes(ader_mat_stream, fp1, mat);

            		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_stream, 0, 0);

					fprintf(fp, "    %s, %ld",
							GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
							ader_mat_stream);

            	    if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0))
            	    {

            	    	fprintf(fp, ", removal table");

            	    }

            	    if(((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] != 0))
            	    {

            	    	ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            	    	if(ader_mat_stream_shadow < 0)
            	    	{

            	    		ader_mat_stream_shadow = ader_mat_stream_shadow * -1;

            	    	}

            	    	fprintf(fp, ", shadow [ %s, %ld ]",
            	    			GetText(ader_mat_stream_shadow + ADER_MAT_STREAM_ID),
								ader_mat_stream_shadow);

            	    }

            	    fprintf(fp, "\n");

            	    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
            	    {

            	    	num_stream_rows++;

                	    fprintf(fp, "        Summation stream\n");

            	    }


            	    ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            	    ADERPrintSumStreams(ader_mat_stream_sum_ent, fp, 1);

            		ader_mat_stream = NextItem(ader_mat_stream);

            	}

            	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

            	while(ader_mat_stream > VALID_PTR)
            	{

            		ADERPrintMaterialStreamIsotopes(ader_mat_stream, fp1, mat);

            		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_stream, 0, 0);

					fprintf(fp, "    %s, %ld",
							GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
							ader_mat_stream);

            	    if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0))
            	    {

            	    	fprintf(fp, ", removal table");

            	    }

            	    if(((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] != 0))
            	    {

            	    	ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            	    	if(ader_mat_stream_shadow < 0)
            	    	{

            	    		ader_mat_stream_shadow = ader_mat_stream_shadow * -1;

            	    	}

            	    	fprintf(fp, ", shadow [ %s, %ld ]",
            	    			GetText(ader_mat_stream_shadow + ADER_MAT_STREAM_ID),
								ader_mat_stream_shadow);

            	    }

            	    fprintf(fp, "\n");

            	    if((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
            	    {

            	    	num_stream_rows++;

                	    fprintf(fp, "        Summation stream\n");

            	    }


            	    ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            	    ADERPrintSumStreams(ader_mat_stream_sum_ent, fp, 1);

            		ader_mat_stream = NextItem(ader_mat_stream);

            	}

            	fclose(fp1);

            	fprintf(fp, "    Number of total streams: %ld.\n\n", num_stream_cols);

            	if((long)RDB[ader_mat_data + ADER_MAT_CLUSTER_PARENT_PTR] == mat)
            	{

            		num_ents = 0;

            		num_eles = 0;

            		num_pres = 0;

            		num_oxi = 0;

            		num_reac = 0;

                	ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

            		fprintf(fp, "    \nMatrix Data Summary\n\n");

            		fprintf(fp, "      The row and column count will be a few off as\n \
      shadow streams are double counted in cluster materials.\n");

            		fprintf(fp, "        Rows: %ld\n", (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS]);

            		fprintf(fp, "        Cols: %ld\n", (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS]);

            		/* Get num non-zero entries                               */

            		ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

            		while(ader_mat_matrix_col > VALID_PTR)
            		{

            			ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

            			while(ader_mat_matrix_col_row > VALID_PTR)
            			{

            				if(fabs(RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]) > 1E-12)
            				{

            					num_ents++;

            				}

            				ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

            			}

            			ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

            		}

            		fprintf(fp, "        Ents: %ld\n", num_ents);

            		filled_entries = (double)num_ents;

            		total_entries = RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] * RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS];

            		percent_empty = 1.0 - (filled_entries / total_entries);

            		fprintf(fp, "        %% Empty: %f\n", (100.0 * percent_empty));

            		/* Now, loop through cluster members, skipping the first  */
            		/* because it is the parent, and count their streams and  */
            		/* what not                                               */

            		ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

            		ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

            		while(ader_mat_cluster_mem_ent > VALID_PTR)
            		{

            			ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

            			ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem + MATERIAL_PTR_COMP];

            			while(ader_mat_cluster_mem_iso > VALID_PTR)
            			{

            				num_isos++;

            				ader_mat_cluster_mem_iso = NextItem(ader_mat_cluster_mem_iso);

            			}

            			ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

            			ader_mat_cluster_mem_ele = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ELES_PTR];

            			while(ader_mat_cluster_mem_ele > VALID_PTR)
            			{

            				num_eles++;

            				ader_mat_cluster_mem_ele = NextItem(ader_mat_cluster_mem_ele);

            			}

            			ader_mat_cluster_mem_cmp = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_CMPS_PTR];

                    	while(ader_mat_cluster_mem_cmp > VALID_PTR)
                    	{

                    		num_cmp_rows++;

                            /* Loop through any rtos attached to this group           */

                    		ader_mat_cluster_mem_cmp_rto = (long)RDB[ader_mat_cluster_mem_cmp + ADER_MAT_CMP_RTOS_PTR];

                            while(ader_mat_cluster_mem_cmp_rto > VALID_PTR)
                            {

                            	num_cmp_rows++;

                                if(RDB[ader_mat_cluster_mem_cmp_rto + ADER_MAT_CMP_RTO_MAX] > 0.0)
                                {

                                	num_cmp_rows++;

                                }

                                ader_mat_cluster_mem_cmp_rto = NextItem(ader_mat_cluster_mem_cmp_rto);

                            }

                            /* Report if group is a summation group                   */

                            if((long)RDB[ader_mat_cluster_mem_cmp + ADER_MAT_CMP_SUM_GRPS_PTR] > VALID_PTR)
                            {

                            	num_cmp_rows++;

                            }

                            ader_mat_cluster_mem_cmp = NextItem(ader_mat_cluster_mem_cmp);

                    	}

                    	/*Now loop through streams                            */

                    	ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

                    	while(ader_mat_cluster_mem_stream > VALID_PTR)
                    	{

                    		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_cluster_mem_stream, 0, 0);

                    	    if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
                    	    {

                    	    	num_stream_rows++;

                    	    }

                    	    ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

                    	}

                    	ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

                    	while(ader_mat_cluster_mem_stream > VALID_PTR)
                    	{

                    		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_cluster_mem_stream, 0, 0);

                    	    if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
                    	    {

                    	    	num_stream_rows++;

                    	    }

                    	    ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

                    	}

                    	ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

                    	while(ader_mat_cluster_mem_stream > VALID_PTR)
                    	{

                    		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_cluster_mem_stream, 0, 0);

                    	    if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
                    	    {

                    	    	num_stream_rows++;

                    	    }

                    	    ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

                    	}

                    	ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

                    	while(ader_mat_cluster_mem_stream > VALID_PTR)
                    	{

                    		num_stream_cols = num_stream_cols + ADERCountStream(ader_mat_cluster_mem_stream, 0, 0);

                    	    if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SUM_GRPS_PTR] > VALID_PTR)
                    	    {

                    	    	num_stream_rows++;

                    	    }

                    	    ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

                    	}

                    	if((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_OXI_PTR] > VALID_PTR)
                    	{

                    		num_oxi++;

                    	}

                    	if((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_RHO_WEIGHT] > 0.0)
                    	{

                    		num_reac = num_reac + 2;

                    	}

                    	ader_mat_cluster_mem_pres = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_PRESERVES_PTR];

						while(ader_mat_cluster_mem_pres > VALID_PTR)
						{

							num_pres++;

							ader_mat_cluster_mem_pres = NextItem(ader_mat_cluster_mem_pres);

						}

                    	ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

            		}

            		/* Count the elements in the parent                       */

            		ader_mat_ele = (long)RDB[ader_mat_data + ADER_MAT_ELES_PTR];

            		while(ader_mat_ele > VALID_PTR)
            		{

            			num_eles++;

            			ader_mat_ele = NextItem(ader_mat_ele);

            		}

            		/* Count the pres entries, in the parent                  */

            		ader_mat_pres = (long)RDB[ader_mat_data + ADER_MAT_PRESERVES_PTR];

            		while(ader_mat_pres > VALID_PTR)
            		{

            			num_pres++;

            			ader_mat_pres = NextItem(ader_mat_pres);

            		}

            		fprintf(fp, "        Ele Cols:    %ld\n", (num_eles * 2));

            		fprintf(fp, "        Iso Cols:    %ld\n", (num_isos * 2));

            		fprintf(fp, "        Stream Cols: %ld\n", num_stream_cols);

            		fprintf(fp, "        Total Cols:  %ld\n", ((num_eles * 2) +
            				                                   (num_isos * 2) +
															   num_stream_cols));

            		fprintf(fp, "        Cmp Rows:    %ld\n", num_cmp_rows);

            		fprintf(fp, "        Ele Rows:    %ld\n", (num_eles * 4));

            		fprintf(fp, "        Iso Rows:    %ld\n", (num_isos * 3));

            		fprintf(fp, "        Opt Rows:    %d\n", 1);

            		if((long)RDB[ader_mat_data + ADER_MAT_OXI_PTR] > VALID_PTR)
            		{

            			num_oxi++;

            			fprintf(fp, "        Oxi Rows:    %d\n", 1);

            		}

            		fprintf(fp, "        Pres Rows:   %ld\n", num_pres);

            	    if(RDB[ader_mat_data + ADER_MAT_RHO_WEIGHT] > 0.0)
            		{

            			num_reac = num_reac + 2;

            			fprintf(fp, "        Oxi Rows:    %d\n", 1);

            		}

            		fprintf(fp, "        Stream Rows: %ld\n", num_stream_rows);

            		fprintf(fp, "        Total Rows:  %ld\n\n", (num_cmp_rows + (num_eles * 4) +
            				                                   (num_isos * 3) +
															   num_oxi +
															   num_pres +
															   num_reac +
															   num_stream_rows) + 1);

            	}

        	}

        	/* Rebuild the stream indices                                     */

        	dump_vector = ADERGetBurnMatrixSizeData(mat);

        	ADERDeallocateTarget(dump_vector, 5);

        	mat = NextItem(mat);

        }

        fprintf(fp, "\nEnd materials:\n\n");


        fprintf(fp, "********************************************************************************\n");

        fclose(fp);

    }

}
