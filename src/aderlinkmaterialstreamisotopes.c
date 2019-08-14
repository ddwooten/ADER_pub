/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderlinkmaterialstreamisotopes.c               */
/*                                                                           */
/* Created:       2016/1/4 (DDW)                                             */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Links material isotope indices to group isotope data         */
/*                                                                           */
/* Comments:This function is called from ADERLinkMaterialIsotopeIndices      */
/*          and by itself                                                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERLinkMaterialStreamIsotopes:"

void ADERLinkMaterialStreamIsotopes(long ader_mat_strm, long mat)
{

    long ader_mat_strm_iso = 0, ader_mat_strm_sum_grp = 0, ader_mat_strm_sum_grp_data = 0;

    ader_mat_strm_iso = (long)RDB[ader_mat_strm + ADER_MAT_STREAM_ISOS_PTR];

    /* Pass the first member of the iso list to the following function */
    /* It will go through the rest matching them up to isotopes in the  */
    /* material */

    ADERLinkMaterialGroupIsotopes(ader_mat_strm_iso, mat);

    ader_mat_strm_sum_grp_data = (long)RDB[ader_mat_strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(ader_mat_strm_sum_grp_data > VALID_PTR)
    {

        /* If the stream has summation streams, go through these as well */

        ader_mat_strm_sum_grp = (long)RDB[ader_mat_strm_sum_grp_data + ADER_MAT_GRP_SUM_GRP_PTR];

        ADERLinkMaterialStreamIsotopes(ader_mat_strm_sum_grp, mat);

        ader_mat_strm_sum_grp_data = NextItem(ader_mat_strm_sum_grp_data);

    }

}
