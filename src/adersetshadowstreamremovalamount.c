/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetshadowstreamremovalamount.c            */
/*                                                                           */
/* Created:       2016/04/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Searches shadow stream's elemental or isotopic lists to store*/
/*              the passed in value                                          */
/*                                                                           */
/* Comments:This function is called from ADERGetStreamRemovalAmounts         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetShadowStreamRemovalAmount:"

void ADERSetShadowStreamRemovalAmount(long ader_mat_stream, long ele_id,
                                      long iso_id, double value)
{

	long ader_mat_stream_ele = 0, ader_mat_stream_iso = 0;

	if(ele_id > 0)
	{

		ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

		while(ader_mat_stream_ele > VALID_PTR)
		{

			if((long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z] == ele_id)
			{

				WDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC] = value;

				break;
			}

			ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

		}

	}
	else
	{

		ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_iso > VALID_PTR)
		{

			if((long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] == iso_id)
			{

				WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = value;

			}

			ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

		}

	}

}
