/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercountstream.c                              */
/*                                                                           */
/* Created:       2016/21/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Counts the number of sum streams in parent streams. Returns  */
/*              the total number of streams in a parent stream. Also provides*/
/*              stream's with their index and their isotopes with their's    */
/*                                                                           */
/* Comments:This function is called from ADERGetBurnMatrixSizeData           */
/*                                       ADERCountStream                     */
/*                                       TESTADERCountStream                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCountStream:"

long ADERCountStream(long ader_mat_stream, long ader_mat_stream_count,
		             long num_rows)
{

	long ader_mat_stream_shadow_stream = 0;
	long ader_mat_stream_sum_ent = 0, ader_mat_stream_sum_stream = 0;

	/* Tunnel into the sum streams of the parent stream if they exist         */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	if(ader_mat_stream_sum_ent > VALID_PTR)
	{

		/* If there are sum streams, pass them to this function               */

		while(ader_mat_stream_sum_ent > VALID_PTR)
		{

			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

			ader_mat_stream_count = ADERCountStream(ader_mat_stream_sum_stream, ader_mat_stream_count, num_rows);

			ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

		}

	}
	else
	{

		/* Once the function finds a stream with no sum components, it will   */
		/* increment the counter and return, also give the stream its index   */
		/* Which should happen before increment                               */

		WDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX] = (double)(ader_mat_stream_count + num_rows);

		/* Give the shadow its index if it exists and if it does, by the way  */
		/* this function is called, it will be a destination stream           */

		ader_mat_stream_shadow_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR] * -1;

		if(ader_mat_stream_shadow_stream > VALID_PTR)
		{

			WDB[ader_mat_stream_shadow_stream + ADER_MAT_STREAM_BURN_INDEX] = (double)(ader_mat_stream_count + num_rows);

		}

		ader_mat_stream_count++;

	}

	return(ader_mat_stream_count);

}
