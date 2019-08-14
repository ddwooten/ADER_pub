/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintoutputstreamdata.c                    */
/*                                                                           */
/* Created:       2017/08/06 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Prints ADER data for burn output for target stream and       */
/*              tunnels into sumstreams                                      */
/*                                                                           */
/* Comments:This function is called from ADERPrintOutput                     */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintOutputStreamData:"

void ADERPrintOutputStreamData(long ader_mat_stream, FILE* fp, char* mat_name)
{

	long ader_mat_data = 0, ader_mat_stream_burn_step = 0, ader_mat_stream_sum_stream = 0;
	long ader_mat_stream_sum_stream_ent = 0, i = 0, mat = 0;
	long burn_steps = 0;

	/* Get the ader mat data, we will need it.                                */

	mat = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_MAT_PTR];

	ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

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

	fprintf(fp, "MAT_%s_STREAM_%s_STEP_AMT = [ ", mat_name,
			GetText(ader_mat_stream + ADER_MAT_STREAM_ID));

	/* Get the stream burn data                                                  */

	ader_mat_stream_burn_step = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_STEPS_PTR];

	/* Print the burn data in the .m file vector format                       */

	for(i = 0; i < burn_steps; i++)
	{

		fprintf(fp, "%1.5E ", RDB[ader_mat_stream_burn_step + ADER_MAT_GRP_BURN_STEP_VALUE]);

		ader_mat_stream_burn_step = NextItem(ader_mat_stream_burn_step);

	}

	/* Close the vector                                                       */

	fprintf(fp, "];\n\n");

	/* Now, loop through the sum streams if there are any                     */

	ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	while(ader_mat_stream_sum_stream_ent > VALID_PTR)
	{

		ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

		ADERPrintOutputStreamData(ader_mat_stream_sum_stream, fp, mat_name);

		ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

	}

}
