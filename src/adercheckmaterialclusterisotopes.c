/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercheckmaterialclusterisotopes.c             */
/*                                                                           */
/* Created:       2016/2/16 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function checks if a material is part of a cluster and  */
/*           and calls ADERMatchMaterialClusterIsotopes if so                */
/*                                                                           */
/* Comments: This function is called from ProcessMaterials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCheckMaterialClusterIsotopes:"

void ADERCheckMaterialClusterIsotopes(long mat)
{

    long mat_ader_data = 0, mat_cluster_parent = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cluster_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    if(mat_cluster_parent > VALID_PTR)
    {

        ADERMatchMaterialClusterIsotopes(mat);

    }

}
