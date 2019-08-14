/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialpresmolscompmatrixsection.c    */
/*                                                                           */
/* Created:       2016/03/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's stream entries filling in the     */
/*              given preservation row with -1s for src streams and 1s for   */
/*              dest streams. This ensures that 'mols' input and removed by  */
/*              streams are equal. Additionally streams are normalized by    */
/*              material density                                             */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialPresCompMatrixSection                            */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialPresMolsCompMatrixSection:"

void ADERFillMaterialPresMolsCompMatrixSection(long ader_mat_cluster_ent_mem,
                                               long ader_mat_matrix_data,
                                               long ader_mat_pres)
{

	double adens_corr_factor = 0, dest_mat_adens = 0, src_mat_adens = 0;
    long ader_mat_stream = 0, ader_mat_stream_shadow = 0, ader_mat_stream_src_mat = 0;
    long mat_ader_data = 0;

    mat_ader_data = (long)RDB[ader_mat_cluster_ent_mem + MATERIAL_ADER_DATA];

    /* Go through the material's streams and set their matrix entries for     */
    /* this preserve row to reflect that feed amounts must equal removal      */
    /* amounts, skip rem type streams                                         */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
		{

    		ader_mat_stream = NextItem(ader_mat_stream);

    		continue;

		}
    	else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
                       GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

    		/* If this stream has a shadow, which would be a source material  */
    		/* based stream, we must correct for differing atomic densities   */

    		ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    		if(ader_mat_stream_shadow > 0)
    		{

    			ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

    			dest_mat_adens = RDB[ader_mat_cluster_ent_mem + MATERIAL_ADENS];

    			src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

    			adens_corr_factor = (src_mat_adens / dest_mat_adens) *
 			                        (RDB[ader_mat_stream_src_mat + MATERIAL_VOLUME] /
						             RDB[ader_mat_cluster_ent_mem + MATERIAL_VOLUME]);

    		}
    		else
    		{

    			adens_corr_factor = 1.0;

    		}

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, adens_corr_factor);

        }
        else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, -1.0);

        }
        else
        {

            Die(FUNCTION_NAME, "Stream %s in material %s does not have the material\n \
as either a source or a destination. This is not a user input error.\n \
Please post on the SERPENT user's group forum as many details regarding the events \n \
leading up to this bug as possible.\n", GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME));

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
		{

    		ader_mat_stream = NextItem(ader_mat_stream);

    		continue;

		}
    	else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
                       GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

    		/* If this stream has a shadow, which would be a source material  */
    		/* based stream, we must correct for differing atomic densities   */

    		ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    		if(ader_mat_stream_shadow > 0)
    		{

    			ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

    			dest_mat_adens = RDB[ader_mat_cluster_ent_mem + MATERIAL_ADENS];

    			src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

    			adens_corr_factor = (src_mat_adens / dest_mat_adens) *
 			                        (RDB[ader_mat_stream_src_mat + MATERIAL_VOLUME] /
						             RDB[ader_mat_cluster_ent_mem + MATERIAL_VOLUME]);

    		}
    		else
    		{

    			adens_corr_factor = 1.0;

    		}

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, adens_corr_factor);

        }
        else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, -1.0);

        }
        else
        {

            Die(FUNCTION_NAME, "Stream %s in material %s does not have the material\n \
as either a source or a destination. This is not a user input error.\n \
Please post on the SERPENT user's group forum as many details regarding the events \n \
leading up to this bug as possible.\n", GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME));

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
		{

    		ader_mat_stream = NextItem(ader_mat_stream);

    		continue;

		}
    	else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
                       GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

    		/* If this stream has a shadow, which would be a source material  */
    		/* based stream, we must correct for differing atomic densities   */

    		ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    		if(ader_mat_stream_shadow > 0)
    		{

    			ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

    			dest_mat_adens = RDB[ader_mat_cluster_ent_mem + MATERIAL_ADENS];

    			src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

    			adens_corr_factor = (src_mat_adens / dest_mat_adens) *
 			                        (RDB[ader_mat_stream_src_mat + MATERIAL_VOLUME] /
						             RDB[ader_mat_cluster_ent_mem + MATERIAL_VOLUME]);

    		}
    		else
    		{

    			adens_corr_factor = 1.0;

    		}

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, adens_corr_factor);

        }
        else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, -1.0);

        }
        else
        {

            Die(FUNCTION_NAME, "Stream %s in material %s does not have the material\n \
as either a source or a destination. This is not a user input error.\n \
Please post on the SERPENT user's group forum as many details regarding the events \n \
leading up to this bug as possible.\n", GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME));

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0)
		{

    		ader_mat_stream = NextItem(ader_mat_stream);

    		continue;

		}
    	else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
                       GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

    		/* If this stream has a shadow, which would be a source material  */
    		/* based stream, we must correct for differing atomic densities   */

    		ader_mat_stream_shadow = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

    		if(ader_mat_stream_shadow > 0)
    		{

    			ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

    			dest_mat_adens = RDB[ader_mat_cluster_ent_mem + MATERIAL_ADENS];

    			src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

    			adens_corr_factor = (src_mat_adens / dest_mat_adens) *
 			                        (RDB[ader_mat_stream_src_mat + MATERIAL_VOLUME] /
						             RDB[ader_mat_cluster_ent_mem + MATERIAL_VOLUME]);

    		}
    		else
    		{

    			adens_corr_factor = 1.0;

    		}

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, adens_corr_factor);

        }
        else if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME)) == 0)
        {

            ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID],
                                             (long)RDB[ader_mat_pres + ADER_MAT_PRESERVE_ROW_ID],
                                             ader_mat_matrix_data, -1.0);

        }
        else
        {

            Die(FUNCTION_NAME, "Stream %s in material %s does not have the material\n \
as either a source or a destination. This is not a user input error.\n \
Please post on the SERPENT user's group forum as many details regarding the events \n \
leading up to this bug as possible.\n", GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                GetText(ader_mat_cluster_ent_mem + MATERIAL_PTR_NAME));

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
