/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialcompmatrixeledata.c            */
/*                                                                           */
/* Created:       2016/03/18 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the composition, or stream, elements passed in */
/*              and find their matching ader_mat_ele which has the correct   */
/*              row to put the fraction in. Column is given by the calling   */
/*              function. The input type is to specify whether the           */
/*              came from a composition group ( type 1 ) or a stream         */
/*              ( type 0 ). These designate either FUT or DEL rows           */
/*              respectively                                                 */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*          ADERFillMaterialStreamCompMatrixSection                          */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialCompMatrixEleData:"

void ADERFillMaterialCompMatrixEleData(long ader_mat_ent_ele,
                                       long ader_mat_matrix_col_id,
                                       long ader_mat_matrix_data,
                                       long mat_ader_data,
									   double mult,
                                       long sign, long type)
{

	/* They type variable indicates whether the passed in element or isotope  */
	/* should be put in a future, or a del row                                */

    long ader_mat_ele = 0;

    /* Loop through the elemental list passed in ( the first element is given */
    /* by ader_mat_ent_ele ) and search the mat_ader_data's elemental list for*/
    /* the matching element.                                                  */

    while(ader_mat_ent_ele > VALID_PTR)
    {

        ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

        while(ader_mat_ele > VALID_PTR)
        {

            /* If we found the matching element, place the group fraction for */
            /* that element into the appropriate matrix position              */

            if((long)RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_Z] == (long)RDB[ader_mat_ele + ADER_MAT_ELE_Z])
            {

                if(sign > 0)
                {

                    /* Sign indicates a positive number, so put a positive num*/

                    if(type == 0)
                    {

                        ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID],
                                                         ader_mat_matrix_data,
                                                         RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_FRAC] * mult);

                    }
                    else if(type == 1)
                    {

                        ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID],
                                                         ader_mat_matrix_data,
                                                         RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_FRAC] * mult);

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

                    /* Sign indicates a negative number, so put a neg number  */

                    if(type == 0)
                    {

                        ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID],
                                                         ader_mat_matrix_data,
                                                         -RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_FRAC] * mult);

                    }
                    else if(type == 1)
                    {

                        ADERSetMaterialCompMatrixElement(ader_mat_matrix_col_id,
                                                         (long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_ROW_ID],
                                                         ader_mat_matrix_data,
                                                         -RDB[ader_mat_ent_ele + ADER_MAT_GRP_ELE_FRAC] * mult);

                    }
                    else
                    {

                        Die(FUNCTION_NAME, "Improper 'type' variable passed to ADERFillMaterialCompMatrixEleData \n \
Type must have value of 0 or 1, has value of %ld.\n. Please post this issue, \n \
with all available supporting documentation ( run scripts, etc ) to the \n \
SERPENT users forums.\n", type);

                    }

                }

                break;

            }

            ader_mat_ele = NextItem(ader_mat_ele);

        }

        ader_mat_ent_ele = NextItem(ader_mat_ent_ele);

    }

}
