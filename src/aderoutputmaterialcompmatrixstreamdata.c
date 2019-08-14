/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoutputmaterialcompmatrixstreamdata.c       */
/*                                                                           */
/* Created:       2017/02/07 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Outputs stream data to the material comp matrix json file    */
/*              Recursively calls itself on sum streams                      */
/*                                                                           */
/* Comments:This function is called from ADEROutputMaterialCompMatrixData    */
/*                                       ADEROutputMaterialCompMatrixStreamData */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROutputMaterialCompMatrixStreamData:"

long ADEROutputMaterialCompMatrixStreamData(long ader_mat_cluster_mem,
											long ader_mat_stream,
											long ader_mat_stream_sum_stream_check,
											FILE* fp, long level, long tab_level,
											long tab_length)
{

	char print_buffer[256], print_data[256];
	long ader_mat_cluster_mem_ader_data = 0, ader_mat_iso = 0, ader_mat_search_stream = 0;
	long ader_mat_stream_ele = 0, ader_mat_stream_iso = 0, ader_mat_stream_shadow_stream = 0;
	long ader_mat_stream_shadow_stream_mat = 0, ader_mat_stream_sum_stream = 0;
	long ader_mat_stream_sum_stream_ent = 0, another_stream = 0, found = 0, mat_iso = 0, name_counter = 0;
	long nuc = 0;

	ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

	while(ader_mat_stream > VALID_PTR)
	{

		/* We only check for name duplicates on primary streams               */

		if(ader_mat_stream_sum_stream_check < 1)
		{

			/* Save the name to print buffer                                  */

			strcpy(print_buffer,
				   GetText(ader_mat_stream + ADER_MAT_STREAM_ID));

			/* Now determine if this stream has a unique name If not, modify  */
			/* the name for testing                                           */

			name_counter = 0;

			found = 0;

			ader_mat_search_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

			while(ader_mat_search_stream > VALID_PTR)
			{

				if(ader_mat_stream == ader_mat_search_stream)
				{

					/* There is no need to count past the stream in question  */

					found = 1;

					break;

				}

				if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
						  GetText(ader_mat_search_stream + ADER_MAT_STREAM_ID)) == 0)
				{

					name_counter++;

				}

				ader_mat_search_stream = NextItem(ader_mat_search_stream);

			}

			ader_mat_search_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

			while((ader_mat_search_stream > VALID_PTR) && (found < 1))
			{

				if(ader_mat_stream == ader_mat_search_stream)
				{

					/* There is no need to count past the stream in question  */

					found = 1;

					break;

				}

				if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
						  GetText(ader_mat_search_stream + ADER_MAT_STREAM_ID)) == 0)
				{

					name_counter++;

				}

				ader_mat_search_stream = NextItem(ader_mat_search_stream);

			}

			ader_mat_search_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

			while((ader_mat_search_stream > VALID_PTR) && (found < 1))
			{

				if(ader_mat_stream == ader_mat_search_stream)
				{

					/* There is no need to count past the stream in question  */

					found = 1;

					break;

				}

				if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
						  GetText(ader_mat_search_stream + ADER_MAT_STREAM_ID)) == 0)
				{

					name_counter++;

				}

				ader_mat_search_stream = NextItem(ader_mat_search_stream);

			}

			ader_mat_search_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

			while((ader_mat_search_stream > VALID_PTR) && (found < 1))
			{

				if(ader_mat_stream == ader_mat_search_stream)
				{

					/* There is no need to count past the stream in question  */

					found = 1;

					break;

				}

				if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
						  GetText(ader_mat_search_stream + ADER_MAT_STREAM_ID)) == 0)
				{

					name_counter++;

				}

				ader_mat_search_stream = NextItem(ader_mat_search_stream);

			}

			if(name_counter > 0)
			{

				sprintf(print_data, "_%ld", name_counter);

				strcat(print_buffer, print_data);

			}

		}
		else
		{

			strcpy(print_buffer, GetText(ader_mat_stream + ADER_MAT_STREAM_ID));

		}

		/* Open the stream's dict                                             */

		sprintf(print_data, "\"%s\" : {", print_buffer);

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level++;

		/* Provide basic stream information                                   */

		sprintf(print_data, "\"burn_idx\" : %ld,",
				            (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX]);

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"col_id\" : %ld,",
				            (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID]);

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"dest\" : \"%s\",",
				            GetText(ader_mat_stream + ADER_MAT_STREAM_DEST));

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"form\" : \"%s\",",
				            GetText(ader_mat_stream + ADER_MAT_STREAM_FORM));

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"src\" : \"%s\",",
				            GetText(ader_mat_stream + ADER_MAT_STREAM_SRC));

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"type\" : \"%s\",",
				            GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE));

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		sprintf(print_data, "\"sum_row_id\" : %ld,",
				            (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID]);

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		/* Open the shadow stream dict                                        */

		sprintf(print_data, "\"shadow\" : {");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level++;

		/* Get the shadow stream                                              */

		ader_mat_stream_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

		if(ader_mat_stream_shadow_stream != 0)
		{

			/* Source side streams, those leaving a material                  */
			/* have negative pointers to the destination                      */
			/* stream                                                         */

			if(ader_mat_stream_shadow_stream < 0)
			{

				ader_mat_stream_shadow_stream = ader_mat_stream_shadow_stream * -1;

				/* Provide the shadow information                             */

				sprintf(print_data, "\"dest_stream\" : \"%s\",",
						            GetText(ader_mat_stream_shadow_stream + ADER_MAT_STREAM_ID));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				ader_mat_stream_shadow_stream_mat = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

				sprintf(print_data, "\"dest_mat\" : \"%s\",",
						            GetText(ader_mat_stream_shadow_stream_mat + MATERIAL_PTR_NAME));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"src_stream\" : \"%s\",",
						            GetText(ader_mat_stream + ADER_MAT_STREAM_ID));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"src_mat\" : \"%s\"",
						            GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			}
			else
			{

				/* Provide the shadow information                             */

				sprintf(print_data, "\"src_stream\" : \"%s\",",
						            GetText(ader_mat_stream_shadow_stream + ADER_MAT_STREAM_ID));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				ader_mat_stream_shadow_stream_mat = (long)RDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_MAT_PTR];

				sprintf(print_data, "\"src_mat\" : \"%s\",",
						            GetText(ader_mat_stream_shadow_stream_mat + MATERIAL_PTR_NAME));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"dest_stream\" : \"%s\",",
						            GetText(ader_mat_stream + ADER_MAT_STREAM_ID));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"dest_mat\" : \"%s\"",
						            GetText(ader_mat_cluster_mem + MATERIAL_PTR_NAME));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			}

		}
		else
		{

			/* There is no shadow stream, set a null dict                     */

			sprintf(print_data, "\"NULL\" : \"NULL\"");

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		}

		/* Close the shadow stream dict                                       */

		sprintf(print_data, "},");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level--;

		/* Deal with summation streams                                        */

		/* Open the sum streams list                                          */

		sprintf(print_data, "\"sum_streams\" : [");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level++;

		ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

		if(ader_mat_stream_sum_stream_ent > VALID_PTR)
		{

			while(ader_mat_stream_sum_stream_ent > VALID_PTR)
			{

				/* Open the sum stream dict                                   */

				sprintf(print_data, "{");

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				tab_level++;

				/* Provide basic sum stream information                       */

				sprintf(print_data, "\"name\": \"%s\",",
						            GetText(ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID));

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				sprintf(print_data, "\"weight\": %.16f,",
						            RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_WEIGHT]);

				ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

				/* Now, pass the actual sum stream to this function so that   */
				/* all of its info may be input                               */

				ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

				ADEROutputMaterialCompMatrixStreamData(ader_mat_cluster_mem,
						                               ader_mat_stream_sum_stream,
													   1, fp, level, tab_level,
												       tab_length);

				/* Close the sum stream dict                                  */

				if(NextItem(ader_mat_stream_sum_stream_ent) > VALID_PTR)
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

				ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

			}

		}
		else
		{

			/* Provide a null list entry for no sum streams                   */

			sprintf(print_data, "\"NULL\"");

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		}

		/* Close the sum streams list                                         */

		sprintf(print_data, "],");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level--;

		/* Open the stream eles list                                          */

		sprintf(print_data, "\"eles\" : [");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level++;

		/* Loop through the stream eles                                       */

		ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

		while(ader_mat_stream_ele > VALID_PTR)
		{

			/* Open the stream ele dict                                      */

			sprintf(print_data, "{");

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			tab_level++;

			/* Enter the ele information                                      */

			sprintf(print_data, "\"%ld\" : %.16f",
					            (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z],
								RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC]);

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			/* Close the stream ele dict                                      */

			if(NextItem(ader_mat_stream_ele) > VALID_PTR)
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

			ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

		}

		/* Close the streams's eles list                                      */

		sprintf(print_data, "],");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level--;

		/* Open the stream's isos list                                        */

		sprintf(print_data, "\"isos\" : [");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level++;

		/* Loop through the stream isos                                       */

		ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_iso > VALID_PTR)
		{

			/* Open the cmp iso dict                                          */

			sprintf(print_data, "{");

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			tab_level++;

			/* Get the ZAI                                                    */

			ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

			mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

			nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

			/* Enter the iso information                                      */

			sprintf(print_data, "\"ZAI\" : %ld,",
					            (long)RDB[nuc + NUCLIDE_ZAI]);

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			sprintf(print_data, "\"ele_frac\" : %0.8f,",
					            RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC]);

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			sprintf(print_data, "\"grp_frac\" : %0.8f",
					            RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC]);

			ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

			/* Close the stream iso dict                                      */

			if(NextItem(ader_mat_stream_iso) > VALID_PTR)
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

			ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

		}

		/* Close the stream's isos list                                       */

		sprintf(print_data, "]");

		ADERPrintIndentedOutput(fp, print_data, tab_length, tab_level);

		tab_level--;

		/* To close the stream dict we need to know if there are any more of  */
		/* this type of stream or of the streams to be processed. Because feed*/
		/* streams are the first to be processed they do not hae a stream     */
		/* check they only need the "current stream type" check               */
		/* Additionally we need to know if there are any more sum streams if  */
		/* this function was called for sum streams, as such, it is the first */
		/* check                                                              */

		another_stream = 0;

		if(ader_mat_stream_sum_stream_check > 0)
		{

			another_stream = 0;

		}
		else if(NextItem(ader_mat_stream) > VALID_PTR)
		{

			another_stream = 1;

		}
		else if(((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR] > VALID_PTR) &&
				level < 1)
		{

			another_stream = 1;

		}
		else if(((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR] > VALID_PTR) &&
				level < 2)
		{

			another_stream = 1;

		}
		else if(((long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR] > VALID_PTR) &&
				level < 3)
		{

			another_stream = 1;

		}

		if(another_stream > 0)
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

		ader_mat_stream = NextItem(ader_mat_stream);

	}

    /* Return the value                                                       */

    return(tab_level);

}
