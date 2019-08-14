/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetmaterialshadowstreamisofracs.c          */
/*                                                                           */
/* Created:       2016/04/05 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the isotopes in a source stream copying their  */
/*              fractions to the isotopes of the destination stream          */
/*              Does the same for all sum streams                            */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERProcessMaterialShadowStreamEleAndIsoFracs                    */
/*          ADERGetMaterialShadowStreamIsoFracs                              */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetMaterialShadowStreamIsoFracs:"

void ADERGetMaterialShadowStreamIsoFracs(long ader_mat_stream)
{

	long ader_dest_mat = 0;
	long ader_mat_stream_iso = 0, ader_mat_stream_source_stream = 0;
	long ader_mat_stream_source_stream_iso = 0;
	long ader_mat_sum_stream = 0, ader_mat_sum_stream_ent = 0;
	long ader_src_mat = 0;
	long found = 0;

	/* Get the source stream                                                  */

	ader_mat_stream_source_stream = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

	/* Loop through the destination stream's isotopes                         */

	ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

	while(ader_mat_stream_iso > VALID_PTR)
	{

		found = 0;

		/* Now loop through the source stream's isotopes                      */

		ader_mat_stream_source_stream_iso = (long)RDB[ader_mat_stream_source_stream + ADER_MAT_STREAM_ISOS_PTR];

		while(ader_mat_stream_source_stream_iso > VALID_PTR)
		{

			/* If there is a match, copy the isotope's fraction of the stream */
			/* from the source end to the destination end isotope             */

			if((long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] == (long)RDB[ader_mat_stream_source_stream_iso + ADER_MAT_GRP_ISO_ZAI])
			{

				WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_FRAC] = RDB[ader_mat_stream_source_stream_iso + ADER_MAT_GRP_ISO_FRAC];

				WDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC] = RDB[ader_mat_stream_source_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

				found = 1;

				break;

			}

			ader_mat_stream_source_stream_iso = NextItem(ader_mat_stream_source_stream_iso);

		}

		/* Error out if no match was found                                    */

		if(found < 1)
		{

			ader_dest_mat = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_MAT_PTR];

			ader_src_mat = (long)RDB[ader_mat_stream_source_stream + ADER_MAT_STREAM_MAT_PTR];

			Error(0, "Isotope %ld in stream %s in material %s does not have a companion isotope\n \
in stream %s in material %s.\n", (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI],
                  GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
				  GetText(ader_dest_mat + MATERIAL_PTR_NAME),
				  GetText(ader_mat_stream_source_stream + ADER_MAT_STREAM_ID),
				  GetText(ader_src_mat + MATERIAL_PTR_NAME));

		}

		ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

	}

	/* Loop through all sum streams and do the same for them                  */

	ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

	while(ader_mat_sum_stream_ent > VALID_PTR)
	{

		ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

		ADERGetMaterialShadowStreamIsoFracs(ader_mat_sum_stream);

		ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);

	}

}
