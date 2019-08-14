/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetburnmatrixsizedata.c                    */
/*                                                                           */
/* Created:       2016/20/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Returns an array of doubles arrays. The first double array   */
/*              holds the number of rows in the third array which is the     */
/*              burn matrix solution array. The second array holds the number*/
/*              of non zero entries in the burnup matrix to be built. The    */
/*              third array holds the starting index in the burnup vector at */
/*              which each cluster members data begins. The fourth array is  */
/*              a storage array to be used in the make burn matrix routine   */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                       TESTADERGetBurnMatrixSizeData       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERBurnMaterials:"

double** ADERGetBurnMatrixSizeData(long mat)
{

	double **ader_burn_matrix_size_data = NULL, *ader_burn_matrix_num_non_zero_ents = NULL;
	double *ader_burn_matrix_num_rows = NULL, *ader_burn_matrix_starts = NULL;
	long ader_mat_cluster_mem_iso = 0;
	long ader_mat_cluster_ent = 0, ader_mat_cluster_mem = 0;
	long ader_mat_cluster_mem_ader_data = 0;
	long ader_mat_cluster_mem_stream = 0, ader_mat_cluster_mem_stream_count = 0;
	long mat_ader_data = 0;
	long ader_mat_cluster_mem_count = 0;
	long num_cluster_mem_rows = 0, num_non_zero_ents = 0, num_rows = 0;

	/* Allocate space for the return array                                    */

	ader_burn_matrix_size_data = calloc(5, sizeof(double*));

	/* Allocate an array for the num rows                                     */

	ader_burn_matrix_size_data[0] = calloc(1, sizeof(double));

	/* Allocate an array for the number of non zero entries                   */

	ader_burn_matrix_size_data[1] = calloc(1, sizeof(double));

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* First, loop through all cluster member ents to know how many there are */
	/* so the breaks array can be allocated                                   */

	ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_ent > VALID_PTR)
	{

		ader_mat_cluster_mem_count++;

		ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

	}

	/* Increment the counter again to account for it starting at 0            */

	ader_mat_cluster_mem_count++;

	/* Allocate an array for the breaks                                       */

	ader_burn_matrix_size_data[2] = calloc(ader_mat_cluster_mem_count,
			                               sizeof(double));

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	/* Reset the cluster mem count                                            */

	ader_mat_cluster_mem_count = 0;

	/* Loop through the cluster members                                       */

	ader_mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

	while(ader_mat_cluster_ent > VALID_PTR)
	{

		/* Store each cluster member start point. Because num_rows is always  */
		/* incremented after the assignment of a value, assigning it here will*/
		/* always give the index where the next cluster member data starts    */

		ader_burn_matrix_starts[ader_mat_cluster_mem_count] = (double)num_rows;

		num_cluster_mem_rows = 0;

		ader_mat_cluster_mem_stream_count = 0;

		ader_mat_cluster_mem = (long)RDB[ader_mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

		ader_mat_cluster_mem_ader_data = (long)RDB[ader_mat_cluster_mem + MATERIAL_ADER_DATA];

		/* Count the number of non-zero matrix entries provided by this       */
		/* cluster member                                                     */

		num_non_zero_ents += BurnMatrixSize(ader_mat_cluster_mem);

		/* Loop  through the cluster mem's isotopes. We loop through the ader */
		/* isotopes so that they may have their index in the burn matrix.     */
		/* The ader isotopes have a pointer to the material isotopes and all  */
		/* material isotopes are represented in the ader isotope list thanks  */
		/* to earlier linking functions, except the -1 "fictitious" isotope   */
		/* To preserve SERPENT compatibility this isotope is given a row      */
		/* and it's index is stored in the material's ader data               */

		WDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FAKE_ISO_BURN_INDEX] = (double)num_rows;

		num_rows++;

		ader_mat_cluster_mem_iso = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_ISOS_PTR];

		while(ader_mat_cluster_mem_iso > VALID_PTR)
		{

		    /* Give the iso its burn idx                                      */

		    WDB[ader_mat_cluster_mem_iso + ADER_MAT_ISO_BURN_INDEX] = (double)num_rows;

			num_cluster_mem_rows++;

			num_rows++;

			ader_mat_cluster_mem_iso = NextItem(ader_mat_cluster_mem_iso);

		}

		/* Loop through the cluster mem's streams, skip disc form streams     */
		/* Cont form streams get a row because they have a constant they need */
		/* to contribute to an isotopes depletion equation while prop streams */
		/* get a row to actually record how they contributed to an isotope's  */
		/* balance. Skip the destination side of shadow streams unless the    */
		/* number of non zero entries is being counted in which case count all*/
		/* isotopes from all continuous streams, shadow or not because each   */
		/* will contribute an entry                                           */

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_FEED_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* This part counts the number of streams needing matrix rows and */
	    	/* also provides these streams with the index of their row.       */
	    	/* Additionally, the second function counts the number of non-zero*/
	    	/* entries the stream contributes to the burnup matrix.           */

	    	if(strncmp("disc",
	    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
						4) != 0)
	    	{

	    		if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR)
	    		{

	    	    	/* Do not count shadow streams, they will share a row with*/
	    	    	/* with the source side of the stream pair.               */

			    	ader_mat_cluster_mem_stream_count = ADERCountStream(ader_mat_cluster_mem_stream,
			    			                                            ader_mat_cluster_mem_stream_count,
																		num_rows);

	    		}

		    	/* Count the entries if the stream is a cont stream ( shadows */
		    	/* of cont streams get counted as well because both the shadow*/
		    	/* and the actual contribute a matrix entry) or a prop stream */
		    	/* with no shadow or one which is the source side of a shadow */

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) ||
		    	   (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
		    		(strncmp("prop",
		    			   	 GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    			     4) == 0)))

	    		num_non_zero_ents = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
	    				                                num_non_zero_ents);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REAC_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* This part counts the number of streams needing matrix rows and */
	    	/* also provides these streams with the index of their row.       */
	    	/* Additionally, the second function counts the number of non-zero*/
	    	/* entries the stream contributes to the burnup matrix.           */

	    	if(strncmp("disc",
	    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
						4) != 0)
	    	{

	    		if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR)
	    		{

	    	    	/* Do not count shadow streams, they will share a row with*/
	    	    	/* with the source side of the stream pair.               */

			    	ader_mat_cluster_mem_stream_count = ADERCountStream(ader_mat_cluster_mem_stream,
			    			                                            ader_mat_cluster_mem_stream_count,
																		num_rows);

	    		}

		    	/* Count the entries if the stream is a cont stream ( shadows */
		    	/* of cont streams get counted as well because both the shadow*/
		    	/* and the actual contribute a matrix entry) or a prop stream */
		    	/* with no shadow or one which is the source side of a shadow */

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) ||
		    	   (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
		    		(strncmp("prop",
		    			   	 GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    			     4) == 0)))

	    		num_non_zero_ents = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
	    				                                num_non_zero_ents);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* This part counts the number of streams needing matrix rows and */
	    	/* also provides these streams with the index of their row.       */
	    	/* Additionally, the second function counts the number of non-zero*/
	    	/* entries the stream contributes to the burnup matrix.           */

	    	if(strncmp("disc",
	    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
						4) != 0)
	    	{

	    		if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR)
	    		{

	    	    	/* Do not count shadow streams, they will share a row with*/
	    	    	/* with the source side of the stream pair.               */

			    	ader_mat_cluster_mem_stream_count = ADERCountStream(ader_mat_cluster_mem_stream,
			    			                                            ader_mat_cluster_mem_stream_count,
																		num_rows);

	    		}

		    	/* Count the entries if the stream is a cont stream ( shadows */
		    	/* of cont streams get counted as well because both the shadow*/
		    	/* and the actual contribute a matrix entry) or a prop stream */
		    	/* with no shadow or one which is the source side of a shadow */

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) ||
		    	   (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
		    		(strncmp("prop",
		    			   	 GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    			     4) == 0)))

	    		num_non_zero_ents = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
	    				                                num_non_zero_ents);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    ader_mat_cluster_mem_stream = (long)RDB[ader_mat_cluster_mem_ader_data + ADER_MAT_REMV_STREAMS_PTR];

	    while(ader_mat_cluster_mem_stream > VALID_PTR)
	    {

	    	/* This part counts the number of streams needing matrix rows and */
	    	/* also provides these streams with the index of their row.       */
	    	/* Additionally, the second function counts the number of non-zero*/
	    	/* entries the stream contributes to the burnup matrix.           */

	    	if(strncmp("disc",
	    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
						4) != 0)
	    	{

	    		if((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR)
	    		{

	    	    	/* Do not count shadow streams, they will share a row with*/
	    	    	/* with the source side of the stream pair.               */

			    	ader_mat_cluster_mem_stream_count = ADERCountStream(ader_mat_cluster_mem_stream,
			    			                                            ader_mat_cluster_mem_stream_count,
																		num_rows);

	    		}

		    	/* Count the entries if the stream is a cont stream ( shadows */
		    	/* of cont streams get counted as well because both the shadow*/
		    	/* and the actual contribute a matrix entry) or a prop stream */
		    	/* with no shadow or one which is the source side of a shadow */

		    	if((strncmp("cont",
		    			    GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
							4) == 0) ||
		    	   (((long)RDB[ader_mat_cluster_mem_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR) &&
		    		(strncmp("prop",
		    			   	 GetText(ader_mat_cluster_mem_stream + ADER_MAT_STREAM_FORM),
		    			     4) == 0)))

	    		num_non_zero_ents = ADERCountStreamIsos(ader_mat_cluster_mem_stream,
	    				                                num_non_zero_ents);

	    	}

	    	ader_mat_cluster_mem_stream = NextItem(ader_mat_cluster_mem_stream);

	    }

	    /* Add the total stream count to both the num rows and the num cluster*/
	    /* rows                                                               */

		num_cluster_mem_rows = num_cluster_mem_rows + ader_mat_cluster_mem_stream_count;

		num_rows = num_rows + ader_mat_cluster_mem_stream_count;

		/* Increment the cluster mem count                                    */

		ader_mat_cluster_mem_count++;

		ader_mat_cluster_ent = NextItem(ader_mat_cluster_ent);

	}

	/* Allocate an array for the N vector                                     */

	ader_burn_matrix_size_data[3] = calloc(num_rows, sizeof(double));

	/* Allocate an array for the column storage vector                        */

	ader_burn_matrix_size_data[4] = calloc(num_rows, sizeof(double));

	/* Store the number of rows                                               */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_rows[0] = (double)num_rows;

	/* Store the number of non zero entries                                   */

	ader_burn_matrix_num_non_zero_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_num_non_zero_ents[0] = (double)num_non_zero_ents;

	/* And return                                                             */

	return(ader_burn_matrix_size_data);

}
