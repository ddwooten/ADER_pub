/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermateleisobounds.c                      */
/*                                                                           */
/* Created:       2016/04/12 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests to be sure that the elemental row bounds are properly  */
/*              set                                                          */
/*                                                                           */
/* Comments:This function is called from ADEROperateMaterial                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMatEleIsoBounds:"

void TESTADERMatEleIsoBounds()
{

    char *const test_name = "ADERMatEleIsoBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ader_data, ader_test_block, ele_iso_row, ele_iso_row_bound;
    long i, mat, mat_ader_data;
    long mat_ader_ele, mat_matrix_data;


    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERMatEleIsoBounds.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no ader elements.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ader_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ader_ele > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader elements but no Li.\n");

        if((long)RDB[mat_ader_ele + ADER_MAT_ELE_Z] == 3)
        {

            sprintf(print_data, "Material FLiBeFuel has no matrix row bounds.\n");

            ele_iso_row = (long)RDB[mat_ader_ele + ADER_MAT_ELE_ISO_ROW_ID];

            break;

        }

        mat_ader_ele = NextItem(mat_ader_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ele_iso_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

    for(i = 0; i < ele_iso_row; i++)
    {

    	ele_iso_row_bound = NextItem(ele_iso_row_bound);

    }

    if((RDB[ele_iso_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND] == 0.0) &&
       (RDB[ele_iso_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND] == 0.0))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if(boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

		sprintf(print_data, "\nTest: Elememt Isotope Balance Row Bounds: FAIL:\n\
Material FLiBeFuel has matrix row %ld should\n\
have lower bound of %f and upper bound of %f\n\
but has lower bound of %f and upper bound of %f.\n",
				ele_iso_row, 0.0, 0.0,
				RDB[ele_iso_row_bound + ADER_MAT_MATRIX_ROW_LOWER_BOUND],
				RDB[ele_iso_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND]);

		PrintTest(test_name, status, print_data, append);

	}

}
