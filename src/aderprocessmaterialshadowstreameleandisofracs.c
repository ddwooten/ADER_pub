/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialshadowstreameleandisofracs.c*/
/*                                                                           */
/* Created:       2016/04/05 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's shadow streams which are the      */
/*              destination end and populates their isotopic fractions for   */
/*              each element with those from the source side as these are the*/
/*              the ratios which will be coming in                           */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialShadowStreamEleAndIsoFracs:"

void ADERProcessMaterialShadowStreamEleAndIsoFracs(long mat)
{

    long ader_mat_cluster_parent = 0, ader_mat_matrix_data = 0;
    long ader_mat_stream = 0, cluster_parent_ader_data = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* We need the cluster parent to be able to update the comp matrix info  */

    ader_mat_cluster_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    cluster_parent_ader_data = (long)RDB[ader_mat_cluster_parent + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[cluster_parent_ader_data + ADER_MAT_MATRIX_PTR];

    /* Loop through the material's streams. Only process those streams which  */
    /* have a postive shadow stream pointer indicating they have a source     */
    /* stream, skip rem type streams as they have already been processed      */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
    	           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Copy isotopics from the source stream                              */

        ADERGetMaterialShadowStreamIsoFracs(ader_mat_stream);

        /* Re-do the streams element and isotopic fractions in the matrix. Not*/
        /* only does this update the isotopics but it updates the material    */
        /* density correction factor for teh elements and isotopes            */

        ADERFillMaterialStreamCompMatrixSection(mat,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
    	           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Copy isotopics from the source stream                              */

        ADERGetMaterialShadowStreamIsoFracs(ader_mat_stream);

        /* Re-do the streams element and isotopic fractions in the matrix. Not*/
        /* only does this update the isotopics but it updates the material    */
        /* density correction factor for teh elements and isotopes            */

        ADERFillMaterialStreamCompMatrixSection(mat,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
    	           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Copy isotopics from the source stream                              */

        ADERGetMaterialShadowStreamIsoFracs(ader_mat_stream);

        /* Re-do the streams element and isotopic fractions in the matrix. Not*/
        /* only does this update the isotopics but it updates the material    */
        /* density correction factor for teh elements and isotopes            */

        ADERFillMaterialStreamCompMatrixSection(mat,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
    	           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] < VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Copy isotopics from the source stream                              */

        ADERGetMaterialShadowStreamIsoFracs(ader_mat_stream);

        /* Re-do the streams element and isotopic fractions in the matrix. Not*/
        /* only does this update the isotopics but it updates the material    */
        /* density correction factor for teh elements and isotopes            */

        ADERFillMaterialStreamCompMatrixSection(mat,
                                                ader_mat_matrix_data,
                                                ader_mat_stream);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
