/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadernormalizematerialstreamdensity.c       */
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that destination stream fractions are normalized to the*/
/*              MATERIAL_ADENS of the material for the source (shadow) stream*/
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERNormalizeMaterialStreamDensity:"

void TESTADERNormalizeMaterialStreamDensity(long step)
{

    char *const test_name = "ADERNormalizeMaterialStreamDensity";
    char status[5];
    char print_data[256];
    char *mat_name;
    double argon40_adens, ele_value, iso_value, percent_diff_ele_value;
    double percent_diff_iso_value, target_iso_value, target_ele_value;
    int i;
    int append = 0;
    int boolean = 0, boolean_ele = 0, boolean_iso = 0;
    long ader_data;
    long ader_mat_ele, ader_mat_ele_row, ader_mat_iso, ader_mat_iso_row;
    long ader_mat_matrix_col;
    long ader_mat_matrix_col_row, ader_mat_matrix_data, ader_mat_stream;
    long ader_mat_stream_col_id, ader_mat_sum_stream;
    long ader_mat_sum_stream_ent, ader_test_block, argon40, mat, mat_iso;
    long mat_ader_data, nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERNormalizeMaterialStreamDensity.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    argon40 = mat;

    argon40_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has feed streams but no ActF stream.\n");

        if(strcmp("ActF", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "Material Argon40 has feed stream ActF but no sum streams.\n");

            ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_sum_stream_ent > VALID_PTR)
            {

                sprintf(print_data, "Material Argon40 feed stream ActF has sum streams but no Uranium sum stream.\n");

                if(strcmp("Uranium", GetText(ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                    sprintf(print_data, "Material Argon40 has no elements. \n");

                    ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    ader_mat_stream_col_id = (long)RDB[ader_mat_sum_stream + ADER_MAT_STREAM_COL_ID];

                	break;

                }

            	ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);
            }

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	sprintf(print_data, "Material Argon40 has elements but no U. \n");

        if((long)RDB[ader_mat_ele + ADER_MAT_ELE_Z] == 92)
        {

        	sprintf(print_data, "Material Argon40 has U but no isotopes. \n");

            ader_mat_ele_row = (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID];

            break;

        }

        ader_mat_ele = NextItem(ader_mat_ele);

    }

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Argon40 has isotopes but no U-233. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

        	sprintf(print_data, "Material Argon40 has U-233 but material FLiBeFuel does not exist. \n");

            ader_mat_iso_row = (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* Get FLiBeFuel where the matrix lives                                   */

    mat = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < ader_mat_stream_col_id; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_ele_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    /* The 2.0 is for a volume correction factor                              */

    target_ele_value = 1.0 * (RDB[mat + MATERIAL_ADENS] / argon40_adens) * 2.0;

    ele_value = RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    percent_diff_ele_value = (RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		                target_ele_value) / target_ele_value;

    if(fabs(percent_diff_ele_value) < 0.00001)
    {

        boolean_ele = 1;

    }

    /* Now check the isotope                                                  */

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_iso_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    /* The 2.0 is for a volume correction factor                              */

    target_iso_value = 1.0 * (RDB[mat + MATERIAL_ADENS] / argon40_adens) * 2.0;

    iso_value = RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    percent_diff_iso_value = (RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		                  target_iso_value) / target_iso_value;

    if(fabs(percent_diff_iso_value) < 0.00001)
    {

        boolean_iso = 1;

    }


    if(boolean_ele == 1 &&
       boolean_iso == 1)
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

        if(boolean_ele == 0)
        {

            sprintf(print_data, "Test: Elemental stream fraction adens: FAIL:\n \
FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", ader_mat_stream_col_id, ader_mat_ele_row, ele_value,
        			target_ele_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Elemental stream fraction adens: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_iso == 0)
        {

            sprintf(print_data, "Test: Isotopic stream fraction adens: FAIL:\n \
FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", ader_mat_stream_col_id, ader_mat_iso_row, iso_value,
        			target_iso_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Isotopic stream fraction adens: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
