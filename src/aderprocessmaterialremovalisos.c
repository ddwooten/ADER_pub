/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialremovalisos.c                 */
/*                                                                           */
/* Created:       2016/1/20   (DDW)                                          */
/* Last modified: 2016/1/20   (DDW)                                          */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through all rem table isotopes and connects them to    */
/*              parent elements or creates this elements                     */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialRemovalData        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialRemovalIsos:"

void ADERProcessMaterialRemovalIsos(long ader_mat_stream, long mat)
{

	long ader_mat_stream_ele = 0, ader_mat_stream_ele_iso = 0, ader_mat_stream_iso = 0;
	long ader_mat_stream_iso_z = 0, found = 0;

	/* Loop through the stream's isotopes, we need to ensure they have a      */
	/* parent element                                                         */

	ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

	while(ader_mat_stream_iso > VALID_PTR)
	{

		/* Get the Z of the isotope                                           */

		ader_mat_stream_iso_z = (long)floor(RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] / 10000.0);

		found = 0;

		/* Loop through the streams elements to see if a matching one is found*/

		ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

		while(ader_mat_stream_ele > VALID_PTR)
		{

			if((long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z] == ader_mat_stream_iso_z)
			{

				found = 1;

				break;

			}

			ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

		}

		if(found > 0)
		{

			/* If there is an element, provide this element with a pointer to */
			/* the isotope                                                    */

			ader_mat_stream_ele_iso = NewItem(ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR,
					                          ADER_MAT_GRP_ELE_ISO_BLOCK_SIZE);

			WDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] = (double)ader_mat_stream_iso;

		}
		else
		{

			/* There is no element, create it and give it a pointer to the iso*/

			ader_mat_stream_ele = NewItem(ader_mat_stream + ADER_MAT_STREAM_ELES_PTR,
					                      ADER_MAT_GRP_ELE_BLOCK_SIZE);

			WDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z] = (double)ader_mat_stream_iso_z;

			ader_mat_stream_ele_iso = NewItem(ader_mat_stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR,
					                          ADER_MAT_GRP_ELE_ISO_BLOCK_SIZE);

			WDB[ader_mat_stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] = (double)ader_mat_stream_iso;

		}


		ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

	}

}
