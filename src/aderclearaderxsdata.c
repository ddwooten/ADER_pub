/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderclearaderxsdata.c                          */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Clears ADER XS data to be inline with CalculateTransmuXS and */
/*              ScoreTransmuXS                                               */
/*                                                                           */
/* Comments:This function is called from ClearPrivateData and ClearPrivateRes*/
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERClearAderXSData:"

void ADERClearAderXSData()
{

	long ader_mat_iso = 0, mat = 0, mat_ader_data = 0;

	/* loop through all the mats ( this may need to change for parallel proc  */

	mat = (long)RDB[DATA_PTR_M0];

	while(mat > VALID_PTR)
	{

		mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

		/* Check to see if material is under ADER control                     */

		if(mat_ader_data > VALID_PTR)
		{

			/* Check to see if material has reactivity data                   */

			if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] > 0.0)
			{

				/* Loop through the material isotopes                         */

				ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

				while(ader_mat_iso > VALID_PTR)
				{

					/* Clear the current XS data                              */

					WDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] = 0.0;

					WDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR] = 0.0;

					WDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR] = 0.0;

					ader_mat_iso = NextItem(ader_mat_iso);

				}

			}

		}

		mat = NextItem(mat);

	}

}
