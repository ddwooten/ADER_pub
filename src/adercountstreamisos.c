/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercountstreamisos.c                          */
/*                                                                           */
/* Created:       2016/21/10 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Counts the number of isotopes with fractions greater than 0  */
/*              in a stream and its sum streams                              */
/*                                                                           */
/* Comments:This function is called from ADERGetBurnMatrixSizeData           */
/*                                       ADERCountStreamIsos                 */
/*                                       TESTADERGetBurnMatrixSizeData       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCountStreamIsos:"

long ADERCountStreamIsos(long ader_mat_stream, long num_non_zero_ents)
{

	long ader_mat_stream_iso = 0;
	long ader_mat_stream_sum_ent = 0, ader_mat_stream_sum_stream = 0;

	/* Tunnel into the sum streams of the parent stream if they exist         */

	ader_mat_stream_sum_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	if(ader_mat_stream_sum_ent > VALID_PTR)
	{

		/* If there are sum streams, pass them to this function               */

		while(ader_mat_stream_sum_ent > VALID_PTR)
		{

			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

			num_non_zero_ents = ADERCountStreamIsos(ader_mat_stream_sum_stream, num_non_zero_ents);

			ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

		}

	}
	else
	{

		ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_iso > VALID_PTR)
		{

			if(RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] > 0.0)
			{

				num_non_zero_ents++;

			}

			ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

		}

	}

	return(num_non_zero_ents);

}
