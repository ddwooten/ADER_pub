/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : setmatadermem                                  */
/*                                                                           */
/* Created:       2015/10/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Called from readinput if keyword "ader" is found in a "mat"  */
/*              definition. Creates ADER data blocks and populates an ADER   */
/*              element list with the Z values of all elements.              */
/*                                                                           */
/* Comments:Called by ReadInput in the 'mat' section                         */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"

/*****************************************************************************/

void ADERSetMatAderMem(long loc0, char** params, long np, char* pname,
                       char* fname, long line)
{
    int i = 0;
    int k = 0;
    long mat_ader_data_ptr = 0, mat_ader_ele = 0, ader_mat_cnd = 0;

    /* Create ADER memory for the mat*/

    mat_ader_data_ptr = NewItem(loc0 + MATERIAL_ADER_DATA, ADER_MAT_BLOCK_SIZE);

    /*Loop to create element in Z_LIST for each element for current mat */

    for(i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {

        mat_ader_ele = NewItem(mat_ader_data_ptr + ADER_MAT_ELES_PTR,
                               ADER_MAT_ELE_BLOCK_SIZE);

        WDB[mat_ader_ele + ADER_MAT_ELE_Z] = (double)(i + 1);

    }

    /*Loop over parameters to see if material has a reactivity weight */

    while(k < np)
    {

        if (strncmp(params[k], "rhow", 4) == 0)
        {

            k++;

            WDB[mat_ader_data_ptr + ADER_MAT_RHO_WEIGHT] = TestParam(pname,
                                                                     fname, line,
                                                                     params[k],
                                                                     PTYPE_REAL,
                                                                     0.0, 1.0);

        }

        /* check for cnd entry flags and if so add a tag to the material */

        if (strncmp(params[k], "cnd", 3) == 0)
        {

            k++;

            ader_mat_cnd = NewItem(mat_ader_data_ptr + ADER_MAT_CNDS_PTR,
                                   ADER_MAT_CND_ENT_BLOCK_SIZE);

            WDB[ader_mat_cnd + ADER_MAT_CND_ID] = (double)PutText(params[k]);

        }

        k++;

    }

}
