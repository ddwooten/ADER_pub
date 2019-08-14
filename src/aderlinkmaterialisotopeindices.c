/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderlinkmaterialisotopeindices.c               */
/*                                                                           */
/* Created:       2016/1/4 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls functions to link material isotope indices to group    */
/*              isotope data                                                 */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialAderData         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERLinkMaterialIsotopeIndices:"

void ADERLinkMaterialIsotopeIndices(long mat)
{

    long ader_mat_ent = 0, ader_mat_ent_iso = 0, mat_ader_data = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* First, call the Process function to create the material isos list */

    ADERProcessMaterialAderIsosData(mat);

    /* Go through the comp groups */

    ader_mat_ent = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(ader_mat_ent > VALID_PTR)
    {

        ader_mat_ent_iso = (long)RDB[ader_mat_ent + ADER_MAT_CMP_ISOS_PTR];

        ADERLinkMaterialGroupIsotopes(ader_mat_ent_iso, mat);

        ader_mat_ent = NextItem(ader_mat_ent);

    }

    /*Go through the streams */

    ader_mat_ent = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_ent > VALID_PTR)
    {

        ADERLinkMaterialStreamIsotopes(ader_mat_ent, mat);

        ader_mat_ent = NextItem(ader_mat_ent);

    }

    ader_mat_ent = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(ader_mat_ent > VALID_PTR)
    {

        ADERLinkMaterialStreamIsotopes(ader_mat_ent, mat);

        ader_mat_ent = NextItem(ader_mat_ent);

    }

    ader_mat_ent = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_ent > VALID_PTR)
    {

        ADERLinkMaterialStreamIsotopes(ader_mat_ent, mat);

        ader_mat_ent = NextItem(ader_mat_ent);

    }

    ader_mat_ent = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_ent > VALID_PTR)
    {

        ADERLinkMaterialStreamIsotopes(ader_mat_ent, mat);

        ader_mat_ent = NextItem(ader_mat_ent);

    }

}
