/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintoutput.c                              */
/*                                                                           */
/* Created:       2017/08/06 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Prints ADER data for burn output for target material given   */
/*              by 'name'                                                    */
/*                                                                           */
/* Comments:This function is called from PrintDepVals                        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintOutput:"

void ADERPrintOutput(long burn_mat, FILE* fp, char* mat_name)
{

	long ader_mat_data = 0, ader_mat_cmp = 0, ader_mat_cmp_burn_step = 0, ader_mat_stream = 0;
	long i = 0, mat = 0;
	long burn_steps = 0;

	/* Go ahead and set burn_steps. If RDB[DATA_BURN_STEP] is 0 and this      */
	/* function has been called, set burnsteps to 1 so that some printing     */
	/* as it is supposed to if we make it here                                */

	if((long)RDB[DATA_BURN_STEP] == 0)
	{

		burn_steps = 1;

	}
	else
	{

		burn_steps = (long)RDB[DATA_BURN_STEP];

	}

	/* First, we need to find the material who's name is given by mat_name    */

	mat = (long)RDB[DATA_PTR_M0];

	while(mat > VALID_PTR)
	{

		if(strcmp(mat_name, GetText(mat + MATERIAL_PTR_NAME)) == 0)
		{

			break;

		}

		mat = NextItem(mat);

	}

	/* Get the ader_mat_data                                                  */

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	if(ader_mat_data < VALID_PTR)
	{

		return;

	}

	/* Set the printed flag, this is needed to avoid double printing when this*/
	/* function is called later to print non-burning ADER materials           */

	if(burn_mat > 0)
	{

		WDB[ader_mat_data + ADER_MAT_PRINTED_FLAG] = 1.0;

	}
	else if((long)RDB[ader_mat_data + ADER_MAT_PRINTED_FLAG] > 0)
	{

		return;

	}

	/* Loop through the cmp groups and print out their data                   */

	ader_mat_cmp = (long)RDB[ader_mat_data + ADER_MAT_CMPS_PTR];

	while(ader_mat_cmp > VALID_PTR)
	{

	    fprintf(fp, "MAT_%s_GRP_%s_FRAC = [ ", mat_name,
	    		GetText(ader_mat_cmp + ADER_MAT_CMP_ID));

	    /* Get the cmp burn data                                              */

	    ader_mat_cmp_burn_step = (long)RDB[ader_mat_cmp + ADER_MAT_CMP_BURN_STEPS_PTR];

	    /* Print the burn data in the .m file vector format                   */

	    for(i = 0; i < burn_steps; i++)
	    {

	    	fprintf(fp, "%1.5E ", RDB[ader_mat_cmp_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE]);

	    	ader_mat_cmp_burn_step = NextItem(ader_mat_cmp_burn_step);

	    }

	    /* Close the vector                                                   */

	    fprintf(fp, "];\n\n");

		ader_mat_cmp = NextItem(ader_mat_cmp);

	}

	/* Now, loop through the material's streams and call a recurssive function*/
	/* to print the data out                                                  */

	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_FEED_STREAMS_PTR];

	while(ader_mat_stream > VALID_PTR)
	{

		ADERPrintOutputStreamData(ader_mat_stream, fp, mat_name);

		ader_mat_stream = NextItem(ader_mat_stream);

	}

	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REAC_STREAMS_PTR];

	while(ader_mat_stream > VALID_PTR)
	{

		ADERPrintOutputStreamData(ader_mat_stream, fp, mat_name);

		ader_mat_stream = NextItem(ader_mat_stream);

	}

	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REDOX_STREAMS_PTR];

	while(ader_mat_stream > VALID_PTR)
	{

		ADERPrintOutputStreamData(ader_mat_stream, fp, mat_name);

		ader_mat_stream = NextItem(ader_mat_stream);

	}

	ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

	while(ader_mat_stream > VALID_PTR)
	{

		ADERPrintOutputStreamData(ader_mat_stream, fp, mat_name);

		ader_mat_stream = NextItem(ader_mat_stream);

	}

}
