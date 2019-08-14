/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadergetisoburnmatrixindex.c                */
/*                                                                           */
/* Created:       2016/22/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests that ADERGetIsoBurnMatrixIndex returns the correct val */
/*                                                                           */
/* Comments:This function is called from ADERBurnMatreials                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERGetIsoBurnMatrixIndex:"

void TESTADERGetIsoBurnMatrixIndex(long mat)
{

    char *const test_name = "ADERGetIsoBurnMatrixIndex";
    char status[5];
    char print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data;
    long ader_mat_iso;
    long ader_test_block, mat_ader_data, mat_iso, nuc, test_value;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERGetIsoBurnMatrixIndex.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel has no ader isotopes. \n");

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has ader isotopes but no Li-7. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

    		test_value = ADERGetIsoBurnMatrixIndex(FUNCTION_NAME, mat, nuc);

            sprintf(print_data, "Material FLiBeFuel has ader isotopes Li-7 \n\
but bad index of %ld and needs index of 8. \n", test_value);

    		if(test_value == 8)
    		{

    			boolean = 1;

    	        memset(print_data, 0, strlen(print_data));

    		}

    		break;

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

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
