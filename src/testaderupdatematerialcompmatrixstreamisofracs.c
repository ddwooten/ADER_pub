/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testaderupdatematerialcompmatrixstreamisofracs.c*/
/*                                                                           */
/* Created:       2016/28/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that destination stream isotope fractions are updated  */
/*              with the source stream isotope fractions. Additionally checks*/
/*              that stream isotopic fractions for unfixed elements are      */
/*              updated                                                      */
/*                                                                           */
/* Comments:This function is called from ADERCorrectTransportCycle           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERUpdateMaterialCompMatrixStreamIsoFracs:"

void TESTADERUpdateMaterialCompMatrixStreamIsoFracs(long step)
{

    char *const test_name = "ADERUpdateMaterialCompMatrixStreamIsoFracs";
    char status[5];
    char print_data[256];
    char *mat_name;
    double Li6_frac, Li7_frac;
    double Lithium7_adens, Fluorine1_adens, percent_diff_Li6_value;
    double percent_diff_Li7_value, target_Li6_value, target_Li7_value;
    int i;
    int append = 0;
    int boolean = 0, boolean_Li6 = 0, boolean_Li7 = 0;
    long ader_data, ader_mat_Li6_row, ader_mat_Li7_row;
    long ader_mat_iso;
    long ader_mat_matrix_col;
    long ader_mat_matrix_col_row, ader_mat_matrix_data, ader_mat_stream;
    long ader_mat_stream_col_id;
    long ader_test_block, mat, mat_iso, mat_ader_data;
    long nuc;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    /* This test only runs if its the first step                              */

    if(step > 0)
    {

        return;

    }

    fprintf(outp, "Begin: TESTADERUpdateMaterialCompMatrixStreamIsoFracs.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material Lithium7 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            sprintf(print_data, "Material Lithium7 has no isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    Lithium7_adens = RDB[mat + MATERIAL_ADENS];

    /* Adjust Lithium isotopic composition to test adjustments                */

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {
        sprintf(print_data, "Material Lithium7 has isotopes but is missing Li-6.\n");

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
    	{

            sprintf(print_data, "Material Lithium7 has Li-6 but is missing Li-7.\n");

    		WDB[mat_iso + COMPOSITION_ADENS] = 0.9 * RDB[mat_iso + COMPOSITION_ADENS];

    		break;

    	}

    	mat_iso = NextItem(mat_iso);

    }

    mat_iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(mat_iso > VALID_PTR)
    {

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

            sprintf(print_data, "Material Lithium7 has Li-7 but is missing ader isotope.\n");

    		WDB[mat_iso + COMPOSITION_ADENS] = 1.1 * RDB[mat_iso + COMPOSITION_ADENS];

    		break;

    	}

    	mat_iso = NextItem(mat_iso);

    }

    target_Li7_value = -0.55;

    /* Rerun the update functions to insert these values                       */

    ADERProcessMaterialStreamUnFixedEleIsoFracs(mat);

    ADERProcessMaterialShadowStreamEleAndIsoFracs(mat);

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Lithium7 has ader isotopes but no Li-7. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
        {

        	sprintf(print_data, "Material Lithium7 has Li-7 but no ader streams. \n");

            ader_mat_Li7_row = (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material Lithium7 has redox streams but no LithiumFree stream.\n");

        if(strcmp("LithiumFree", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "Material Lithium7 has LithiumFree stream but material Fluorine1 does not exist.\n");

			ader_mat_stream_col_id = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_COL_ID];

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine1", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material Fluorine1 has no ader isotopes.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Run the update functions on this material as well                      */

    ADERProcessMaterialStreamUnFixedEleIsoFracs(mat);

    ADERProcessMaterialShadowStreamEleAndIsoFracs(mat);

    Fluorine1_adens = RDB[mat + MATERIAL_ADENS];

    /* The 2.0 is for a volume correction factor                              */

    target_Li6_value = 0.45 * (Lithium7_adens / Fluorine1_adens) * 2.0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material Fluorine1 has ader isotopes but no Li-6. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

        	sprintf(print_data, "Material Fluorine1 has Li-6 but Lithium7 has no matrix data. \n");

            ader_mat_Li6_row = (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            sprintf(print_data, "There is an error in the matrix.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < ader_mat_stream_col_id; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_Li6_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    Li6_frac = RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    percent_diff_Li6_value = (Li6_frac - target_Li6_value) / target_Li6_value;

    if(fabs(percent_diff_Li6_value) < 0.00001)
    {

        boolean_Li6 = 1;

    }

    /* Now check the isotope                                                  */

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_Li7_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    Li7_frac = RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    percent_diff_Li7_value = (Li7_frac - target_Li7_value) / target_Li7_value;

    if(fabs(percent_diff_Li7_value) < 0.00001)
    {

        boolean_Li7 = 1;

    }


    if(boolean_Li6 == 1 &&
       boolean_Li7 == 1)
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

        if(boolean_Li6 == 0)
        {

            sprintf(print_data, "Test: Li-6 update: FAIL:\n \
Lithium7 matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", ader_mat_stream_col_id, ader_mat_Li6_row, Li6_frac,
        			target_Li6_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Li-6 update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

        if(boolean_Li7 == 0)
        {

            sprintf(print_data, "Test: Li-7 update: FAIL:\n \
Lithium7 matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", ader_mat_stream_col_id, ader_mat_Li7_row, Li7_frac,
        			target_Li7_value);

        	PrintTest(test_name, status, print_data, 1);

        }
        else
        {

        	sprintf(print_data, "Test: Li-7 update: PASS\n");

        	PrintTest(test_name, status, print_data, 1);

        }

    }

}
