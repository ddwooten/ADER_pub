/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercreatematerialisocompmatrixsection.c       */
/*                                                                           */
/* Created:       2016/02/27 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Creates rows and columns for every isotope in a material's   */
/*              comp matrix. These rows are the "BAL" row, or the balance    */
/*              row which requires that the 'future' amount of the isotope   */
/*              minus the 'delta' amount that ADER adds or takes away be     */
/*              equal to the amount of isotope in the material at the time   */
/*              It's an isotopic BALance row. The "DEL" row represents the   */
/*              material that the ADER streams will bring in or take away.   */
/*              The DELta in the isotopic composition. The "FUT" row         */
/*              represents the criteria that the isotope must satisfy in the */
/*              FUTure.                                                      */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERCreateMaterialClusterMemCompMatrixSection                    */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCreateMaterialIsoCompMatrixSection:"

void ADERCreateMaterialIsoCompMatrixSection(long ader_mat_matrix_data,
                                            long mat_ader_data)
{
    long ader_cnt = 0, ader_cnt_ent = 0, ader_mat_cnt = 0, ader_mat_iso = 0, ader_mat_iso_col = 0;
    long ader_mat_iso_row = 0, mat_iso = 0, nuc = 0;
    long controlled = 0;

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	controlled = 0;

        /* Create the columns for the isotope, give it bounds, and return its index*/
        /* We use a dummy variable for passing, as otherwise, a very exotic        */
        /* seg-fault occurs because the address of the WDB array changes inside    */
        /* the function returning a value but the address of the WDB array         */
        /* in this function is frozen until the return of the value at which       */
        /* point it is going to a bad memory address                               */

        /* First, create the del col                                          */

        ader_mat_iso_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                           -1E+18,
                                                           1E+18);

        WDB[ader_mat_iso + ADER_MAT_ISO_DEL_COL_ID] = (double)ader_mat_iso_col;

        /* The newly created column is the last in its list. We grab it's index */
        /* (in the WDB array, not its index in the comp matrix ) and store this */
        /* to speed later operations                                            */

        WDB[ader_mat_iso + ADER_MAT_ISO_MATRIX_DEL_COL_PTR] = (double)LastItem((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR]);

        /* Next, create the fut col                                           */

        ader_mat_iso_col = ADERCreateMaterialCompMatrixCol(ader_mat_matrix_data,
                                                           0.0,
                                                           1E+18);

        WDB[ader_mat_iso + ADER_MAT_ISO_FUT_COL_ID] = (double)ader_mat_iso_col;

        /* Store the column WDB index                                         */

        WDB[ader_mat_iso + ADER_MAT_ISO_MATRIX_FUT_COL_PTR] = (double)LastItem((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR]);

        /* Now we search the materials cnt tables to see if this isotope is controlled */
        /* and then we set the row bounds based on this information                    */

        mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        ader_mat_cnt = (long)RDB[mat_ader_data + ADER_MAT_CNT_TBLS_PTR];

        while(ader_mat_cnt > VALID_PTR)
        {

            /* The mat cnt simply points to the ader cnt */

            ader_cnt = (long)RDB[ader_mat_cnt + ADER_MAT_CNT_TBL_PTR];

            ader_cnt_ent = (long)RDB[ader_cnt + ADER_CONTROL_ENT_PTR];

            while(ader_cnt_ent > VALID_PTR)
            {

                /* go though the ader cnt's entries, if a ZAI matches this isotope */
                /* you have a match, break this loop and exit the next */

                if((long)RDB[nuc + NUCLIDE_ZAI] == (long)RDB[ader_cnt_ent + ADER_CONTROL_ENT_ZAI])
                {

                    controlled = 1;

                    /* Set the isos's control flag                            */

                    WDB[ader_mat_iso + ADER_MAT_ISO_CONTROL_FLAG] = 1.0;

                    break;

                }

                ader_cnt_ent = NextItem(ader_cnt_ent);

            }

            /* Control was found, break the overall cnt loop */

            if(controlled > 0)
            {

                break;

            }

            ader_mat_cnt = NextItem(ader_mat_cnt);

        }

        /* Now, create the bal row                                            */

        ader_mat_iso_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                           0.0,
                                                           0.0);

        WDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID] = (double)ader_mat_iso_row;

        /* Now, create the del row                                            */

        ader_mat_iso_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                           0.0,
                                                           0.0);

        WDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID] = (double)ader_mat_iso_row;

        /* Create the isotope's fut row, pass back its index and set the      */
        /* bounds. If the bounds are controlled than the min and max are the  */
        /* same If not, there is no upper bound                               */

        if(controlled > 0)
        {

         ader_mat_iso_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                            0.0,
                                                            0.0);

         WDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID] = (double)ader_mat_iso_row;

        }
        else
        {

             ader_mat_iso_row = ADERCreateMaterialCompMatrixRow(ader_mat_matrix_data,
                                                                -1E+18,
                                                                 0.0);

             WDB[ader_mat_iso + ADER_MAT_ISO_FUT_ROW_ID] = (double)ader_mat_iso_row;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

}
