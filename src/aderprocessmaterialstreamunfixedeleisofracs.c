/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialstreamunfixedeleisofracs.c  */
/*                                                                           */
/* Created:       2016/04/05 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through a material's streams falling functions to fill */
/*              the isotopic fractions for un fixed elements in a stream     */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialStreamUnFixedEleIsoFracs:"

void ADERProcessMaterialStreamUnFixedEleIsoFracs(long mat)
{

    long ader_mat_cluster_parent = 0, ader_mat_matrix_data = 0;
    long ader_mat_stream = 0, cluster_parent_ader_data = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* We need the cluster parent to be able to update the comp matrix info  */

    ader_mat_cluster_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    cluster_parent_ader_data = (long)RDB[ader_mat_cluster_parent + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[cluster_parent_ader_data + ADER_MAT_MATRIX_PTR];

    /* Loop through the material's streams. Pass over rem type streams as     */
    /* these are handled in a special manner, same for dest ends of linked    */
    /* streams                                                                */

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Update the isotopic fractions                                      */

        ADERGetMaterialStreamUnFixedEleIsoFracs(ader_mat_matrix_data,
        		                                ader_mat_stream, mat);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Update the isotopic fractions                                      */

        ADERGetMaterialStreamUnFixedEleIsoFracs(ader_mat_matrix_data,
        		                                ader_mat_stream, mat);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Update the isotopic fractions                                      */

        ADERGetMaterialStreamUnFixedEleIsoFracs(ader_mat_matrix_data,
        		                                ader_mat_stream, mat);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        if((strcmp("rem", GetText(ader_mat_stream + ADER_MAT_STREAM_TYPE)) == 0) ||
           ((long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] > VALID_PTR ))
        {

            ader_mat_stream = NextItem(ader_mat_stream);

            continue;

        }

        /* Update the isotopic fractions                                      */

        ADERGetMaterialStreamUnFixedEleIsoFracs(ader_mat_matrix_data,
        		                                ader_mat_stream, mat);

        ader_mat_stream = NextItem(ader_mat_stream);

    }

}
