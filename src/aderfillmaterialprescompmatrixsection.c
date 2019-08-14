/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialprescompmatrixsection.c        */
/*                                                                           */
/* Created:       2016/03/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to incorporate different 'preservation'      */
/*              options into the material comp matrix based on pres type     */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADEROperateMaterial                                              */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialPresCompMatrixSection:"

void ADERFillMaterialPresCompMatrixSection(long ader_mat_cluster_ent_mem,
                                           long ader_mat_matrix_data,
                                           long ader_mat_pres)
{

    /* These if statements call the appropriate function depending on the pres*/
    /* type                                                                   */

    if(strncmp("mols", GetText(ader_mat_pres + ADER_MAT_PRESERVE_ENT), 4) == 0)
    {

        ADERFillMaterialPresMolsCompMatrixSection(ader_mat_cluster_ent_mem,
                                                  ader_mat_matrix_data,
                                                  ader_mat_pres);

    }

    /* Put future if statements here to add more 'preserve' options           */

}
