/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderfillmatcompmatrixpresmolsrow.c     */
/*                                                                           */
/* Created:       2016/13/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that the a "mols" pres row is filled properly with     */
/*              adens weighted streams                                       */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERFillMatCompMatrixPresMolsRow:"

void TESTADERFillMatCompMatrixPresMolsRow(long step)
{

    char *const test_name = "ADERFillMatCompMatrixPresMolsRow";
    char status[5];
    char print_data[256];
    long ader_data, ader_test_block;
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, dest_mat_adens, src_mat_adens, percent_diff;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_preserve_ent, mat_preserve_row, mat_stream, mat_stream_target_col;
    long shadow_stream, src_mat;
    long i;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERFillMatCompMatrixPresMolsRow.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    dest_mat_adens = RDB[mat + MATERIAL_ADENS];

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has redox streams but no Fluorine stream.\n");

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("Fluorine", mat_stream_name, 8) == 0)
        {

            shadow_stream = (long)RDB[mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            src_mat = (long)RDB[shadow_stream + ADER_MAT_STREAM_MAT_PTR];

            src_mat_adens = RDB[src_mat + MATERIAL_ADENS];

            adens_corr_factor = src_mat_adens / dest_mat_adens;

            sprintf(print_data, "FLiBeFuel has Fluorine redox stream but no preserve entries.\n");

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_preserve_ent = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

    while(mat_preserve_ent > VALID_PTR)
    {

        if(strncmp("mols", GetText(mat_preserve_ent + ADER_MAT_PRESERVE_ENT), 4) == 0)
        {

            mat_preserve_row = (long)RDB[mat_preserve_ent + ADER_MAT_PRESERVE_ROW_ID];

            break;

        }

        mat_preserve_ent = NextItem(mat_preserve_ent);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_preserve_row; i++)
    {

        mat_matrix_row = NextItem(mat_matrix_row);

    }

    sprintf(print_data, "FLiBeFuel matrix column %ld preserve row, %ld, has value %f and needs value %f.\n",
            mat_preserve_row, mat_stream_target_col,
            RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
            adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] - adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

    }

}
