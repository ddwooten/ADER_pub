/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderfillmaterialoxicompmatrixsection.c         */
/*                                                                           */
/* Created:       2016/03/24 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Fills in oxidation data for a material comp matrix           */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERFillMaterialClusterMemCompMatrixSection                      */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERFillMaterialOxiCompMatrixSection:"

void ADERFillMaterialOxiCompMatrixSection(long ader_mat_matrix_data,
                                          long mat_ader_data)
{

    long ader_mat_ele = 0, ader_mat_oxi = 0, ader_oxi = 0, ader_oxi_ele = 0, found = 0;

    /* Grab the material's oxidation data                                     */

    ader_mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    /* Grab the associated ADER Oxidation table                               */

    ader_oxi = (long)RDB[ader_mat_oxi + ADER_MAT_OXI_TBL_PTR];

    /* Now, loop through the ADER oxidation table. For each entry, loop       */
    /* through the mat's elements. Once a matching element for the oxidation  */
    /* entry has been found, the matrix value can be set                      */

    ader_oxi_ele = (long)RDB[ader_oxi + ADER_OXI_ELES_PTR];

    while(ader_oxi_ele > VALID_PTR)
    {

        found = 0;

        ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

        while(ader_mat_ele > VALID_PTR)
        {

            if((long)RDB[ader_oxi_ele + ADER_OXI_ELE_Z] == (long)RDB[ader_mat_ele + ADER_MAT_ELE_Z])
            {

                found = 1;

                break;

            }

            ader_mat_ele = NextItem(ader_mat_ele);

        }

        /* If no matching element was found for an oxidation entry            */
        /* ...something has gone terribly wrong                               */

        if(found < 1)
        {

            Die(FUNCTION_NAME, "No matching element found in material's ADER data \n \
for oxidation table entry having Z value of %ld. This is not a user input error.\n \
Please post on the SERPENT user's group forum as many details regarding the events \n \
leading up to this bug as possible.\n", (long)RDB[ader_oxi_ele + ADER_OXI_ELE_Z]);

        }

        ADERSetMaterialCompMatrixElement((long)RDB[ader_mat_ele + ADER_MAT_ELE_FUT_COL_ID],
                                         (long)RDB[ader_mat_oxi + ADER_MAT_OXI_ROW_ID],
                                         ader_mat_matrix_data,
                                         (RDB[ader_oxi_ele + ADER_OXI_ELE_VAL] * RDB[ader_oxi_ele + ADER_OXI_ELE_WEIGHT]));

        ader_oxi_ele = NextItem(ader_oxi_ele);

    }

}
