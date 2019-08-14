/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialclustermemcompmatrixsection.c  */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the composition groups and streams of a        */
/*              material calling functions to incorporate their existence    */
/*              into the material comp matrix. Also calls functions to       */
/*              handle valence and reactivity entries                        */
/*                                                                           */
/* Comments:This function is called from ADERFillMaterialCompMatrix          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialClusterMemCompMatrixSection:"

void ADERFillMaterialClusterMemCompMatrixSection(long ader_mat_cluster_ent_mem,
                                                 long ader_mat_matrix_data)
{

    long ader_mat_cmp = 0, ader_mat_stream = 0;
    long ader_mat_oxi = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[ader_mat_cluster_ent_mem + MATERIAL_ADER_DATA];

    ader_mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(ader_mat_cmp > VALID_PTR)
    {

        /* Process the cmp groups for this cluster mem */

        ADERFillMaterialCmpGroupCompMatrixSection(ader_mat_cmp,
                                                  ader_mat_matrix_data,
                                                  mat_ader_data);

        ader_mat_cmp = NextItem(ader_mat_cmp);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    /* These next four while loops are to process the different streams in */
    /* a material */

    while(ader_mat_stream > VALID_PTR)
    {

        ADERFillMaterialStreamCompMatrixSection(ader_mat_cluster_ent_mem,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ADERFillMaterialStreamCompMatrixSection(ader_mat_cluster_ent_mem,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ADERFillMaterialStreamCompMatrixSection(ader_mat_cluster_ent_mem,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        ADERFillMaterialStreamCompMatrixSection(ader_mat_cluster_ent_mem,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    /* Deal with elements and isotopes */

    ADERFillMaterialEleCompMatrixSection(ader_mat_matrix_data, mat_ader_data);

    ADERFillMaterialIsoCompMatrixSection(ader_mat_matrix_data, mat_ader_data);

    ader_mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    /* If oxidation control is on, deal with that too */

    if(ader_mat_oxi > VALID_PTR)
    {

        ADERFillMaterialOxiCompMatrixSection(ader_mat_matrix_data,
                                             mat_ader_data);

    }

}
