/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercleartargetpropstreamamts.c                */
/*                                                                           */
/* Created:       2017/01/13 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Clears the CUR_AMT and ADJ_AMT for a given prop stream and   */
/*              its sum streams if it has any                                */
/*                                                                           */
/* Comments:This function is called from ADERClearPropStreamAmts             */
/*                                       ADERClearTargetPropStreamAmts       */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERClearTargetPropStreamAmts:"

void ADERClearTargetPropStreamAmts(long ader_mat_stream, long adj)
{

	long ader_mat_stream_sum = 0, ader_mat_stream_sum_ent = 0;

	if(adj == 0)
	{

		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.0;

		WDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] = 0.0;

	}
	else
	{

		WDB[ader_mat_stream + ADER_MAT_STREAM_ADJ_AMT] = 0.0;

	}

	/* If the stream has summation streams, loop through those        */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	while(ader_mat_stream_sum_ent > VALID_PTR)
	{

		ader_mat_stream_sum = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

		ADERClearTargetPropStreamAmts(ader_mat_stream_sum, adj);

		ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

	}

}
