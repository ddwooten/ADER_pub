/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermapdensityvector.c                         */
/*                                                                           */
/* Created:       2016/11/06 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Maps material cluster members isotopic densities and         */
/*              continuous stream feed amounts into the density vector       */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMapDensityVector:"

void ADERMapDensityVector(double* ader_burn_matrix_N,
		                  double* ader_burn_matrix_starts, long adj,
						  long direction, long mat, long predictor,
						  double total_time)
{

	double material_adens = 0;
	long ader_mat_cluster_mem = 0, ader_mat_cluster_mem_ader_data = 0;
	long ader_mat_cluster_mem_ader_iso = 0, ader_mat_cluster_mem_ent = 0;
	long ader_mat_cluster_mem_iso = 0, ader_mat_cluster_mem_stream = 0;
	long ader_mat_data = 0, nuc = 0;

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* This is the function operating in "receive" mode                       */

	if(direction > 0)
	{
		ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

		while(ader_mat_cluster_mem_ent > VALID_PTR)
		{

			/* Reset the material adens variable                              */

			material_adens = 0.0;

			/* Get the actual cluster member                                  */

			ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

			/* Get the cluster member ader data                               */

			ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

			/* Go ahead and find the fake iso to give it its data             */

			ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem + MATERIAL_PTR_COMP];

			while(ader_mat_cluster_mem_iso > VALID_PTR)
			{

				nuc = (long)RDB[ader_mat_cluster_mem_iso + COMPOSITION_PTR_NUCLIDE];

				if((long)RDB[nuc + NUCLIDE_ZAI] == -1)
				{

					WDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS] = ader_burn_matrix_N[(long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FAKE_ISO_BURN_INDEX]];

					break;

				}

				ader_mat_cluster_mem_iso = NextItem(ader_mat_cluster_mem_iso);

			}

			/* Pass the cluster members their isotopics, do this by looping   */
			/* through the ader mat isos                                      */

			ader_mat_cluster_mem_ader_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

			while(ader_mat_cluster_mem_ader_iso > VALID_PTR)
			{

				ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_PTR];

				WDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS] = ader_burn_matrix_N[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]];

				material_adens += RDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS];

				ader_mat_cluster_mem_ader_iso = NextItem(ader_mat_cluster_mem_ader_iso);

			}

			/* Give the material its new adens                                */

			WDB[ader_mat_cluster_mem + MATERIAL_ADENS] = material_adens;

			/* Give prop streams their results                                */

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("prop",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

			ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

		}

	}
	else
	{

		/* This is the function operating in "send" mode. First, loop through */
		/* all cluster members                                                */

		ader_mat_cluster_mem_ent = (long)RDB[ader_mat_data + ADER_MAT_CLUSTER_MEMS_PTR];

		while(ader_mat_cluster_mem_ent > VALID_PTR)
		{

			/* Get the actual cluster member                                  */

			ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

			/* Get the cluster member ader data                               */

			ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

			/* Fill in the cluster member's isotopics                         */

			ader_mat_cluster_mem_ader_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

			while(ader_mat_cluster_mem_ader_iso > VALID_PTR)
			{

				/* Get the material isotope                                   */

				ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_PTR];

				/* On predictor steps it is needed that every isotope's adens */
				/* is copied to the adens_bos position. On corrector steps    */
				/* it is this bos which gets copied to the density vector     */

				if(predictor > 0)
				{

					ader_burn_matrix_N[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]] = RDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS];

					/* On corrector steps this function will be called twice. */
					/* Once it will be called as if it were in a predictor    */
					/* step. This is done so that the ADENS composition can be*/
					/* copied to the N vector for the MaterialBurnUp routine  */
					/* The following if statement ensures the BOS densities   */
					/* are not clobbered                                      */

					if((long)RDB[DATA_BURN_STEP_PC] == PREDICTOR_STEP)
					{

						WDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS_BOS] = RDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS];

					}

				}
				else
				{

					ader_burn_matrix_N[(long)RDB[ader_mat_cluster_mem_ader_iso + ADER_MAT_ISO_BURN_INDEX]] = RDB[ader_mat_cluster_mem_iso + COMPOSITION_ADENS_BOS];

				}

				ader_mat_cluster_mem_ader_iso = NextItem(ader_mat_cluster_mem_ader_iso);

			}

			/* Fill in the cluster members's streams                          */

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

		    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

		    while(ader_mat_cluster_mem_stream > VALID_PTR)
		    {

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) &&
		    	   ((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR))
		    	{

			    	ADERMapDensityVectorStream(ader_burn_matrix_N,
			    			                   ader_mat_cluster_mem_stream,
										       adj, direction, total_time);

		    	}

		    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

		    }

			ader_mat_cluster_mem_ent = NextItem(ader_mat_cluster_mem_ent);

		}

	}

}
