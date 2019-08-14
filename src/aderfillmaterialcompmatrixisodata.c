/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcompmatrixisodata.c            */
/*                                                                           */
/* Created:       2016/03/23 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the composition, or stream, isotopes passed in */
/*              and find their matching ader_mat_iso which has the correct   */
/*              row to put the fraction in. Column is given by the calling   */
/*              function. The input type is to specify whether the           */
/*              came from a composition group ( type 1 ) or a stream         */
/*              ( type 0 ). These designate either FUT or DEL rows           */
/*              respectively                                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialCmpGroupCompMatrixSection                        */
/*          ADERFillMaterialStreamCompMatrixSection                          */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCompMatrixIsoData:"

void ADERFillMaterialCompMatrixIsoData(long ader_mat_ent_iso,
                                       long ader_mat_matrix_col_id,
                                       long ader_mat_matrix_data,
                                       long mat_ader_data,
									   double mult,
                                       long sign, long type)
{

    long ader_mat_iso = 0;

    /* Loop through the isotope list passed in ( the first isotope is given   */
    /* by ader_mat_ent_iso ) and grab the ader_mat_iso that corresponds to it */
    /* to get the row to place the fraction ( times the multiplier ) in       */

    while(ader_mat_ent_iso > VALID_PTR)
    {

        ader_mat_iso = (long)RDB[ader_mat_ent_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

        if(sign > 0)
        {

            /* Sign indicates a positive number, so put a positive number     */

            if(type == 0)
            {

                ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                 (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID],
                                                 ader_mat_matrix_data,
                                                 RDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_FRAC] * mult);

            }
            else if(type == 1)
            {

                ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                 (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID],
                                                 ader_mat_matrix_data,
                                                 RDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_FRAC] * mult);

            }
            else
            {

                Die(FUNCTION_NAME, "Improper 'type' variable passed to ADERFillMaterialCompMatrixEleData \n \
Type must have value of 0 or 1, has value of %ld.\n. Please post this issue, \n \
with all available supporting documentation ( run scripts, etc ) to the \n \
SERPENT users forums.\n", type);

            }

        }
        else
        {

            /* Sign indicates a negative number, so put a negative number     */

            if(type == 0)
            {

                ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                 (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID],
                                                 ader_mat_matrix_data,
                                                 -RDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_FRAC] * mult);

            }
            else if(type == 1)
            {

                ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                 (long)RDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID],
                                                 ader_mat_matrix_data,
                                                 -RDB[ader_mat_ent_iso + ADER_MAT_GRP_ISO_FRAC] * mult);

            }
            else
            {

                Die(FUNCTION_NAME, "Improper 'type' variable passed to ADERFillMaterialCompMatrixEleData \n \
Type must have value of 0 or 1, has value of %ld.\n. Please post this issue, \n \
with all available supporting documentation ( run scripts, etc ) to the \n \
SERPENT users forums.\n", type);

            }

        }

        ader_mat_ent_iso = NextItem(ader_mat_ent_iso);

    }

}
