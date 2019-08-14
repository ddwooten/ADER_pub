 /*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adersetmaterialcompmatrixclustermemremovaltablerowbounds.c */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Adjusts row bounds in the comp matrix to account for material*/
/*              removal due to removal tables                                */
/*                                                                           */
/* Comments:This function is called from                                     */
/*          ADERSetMaterialCompMatrixClusterMemRowBounds                     */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds:"

void ADERSetMaterialCompMatrixClusterMemRemovalTableRowBounds(long ader_mat_matrix_data,
		                                                      long ader_mat_stream,
															  long dep,
															  long mat,
															  double t1,
															  double t2)
{

	double sign = 0;
	long ader_mat_ele = 0, ader_mat_iso = 0, ader_mat_stream_ele = 0;
	long ader_mat_stream_iso = 0, mat_ader_data = 0, mat_iso = 0, nuc = 0;

	mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	/* Determine if this material is the stream's source or sink, set sign    */

	if(strcmp(GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
			  GetText(mat + MATERIAL_PTR_NAME)) == 0)
	{

		sign = -1.0;

	}
	else
	{

		sign = 1.0;

	}

	/* Loop through the stream's elements                                     */

	ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

	while(ader_mat_stream_ele > VALID_PTR)
	{

		/* Loop through the material elements to get the row information      */

		ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

		while(ader_mat_ele > VALID_PTR)
		{

			if((long)RDB[ader_mat_ele + ADER_MAT_ELE_Z] ==
		       (long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z])
			{

				break;

			}

			ader_mat_ele = NextItem(ader_mat_ele);

		}

		/* Add the calculated removal amount, stored in ADER_MAT_GRP_ELE_FRAC */
		/* to the appropriate rows                                            */

    	ADERSetMaterialCompMatrixRowBounds(0, 1, ader_mat_matrix_data,
    			                           (long)RDB[ader_mat_ele + ADER_MAT_ELE_BAL_ROW_ID],
										   (sign *
										    RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC]));

		ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

	}

	/* Loop through the stream's isotopes                                     */

	ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

	while(ader_mat_stream_iso > VALID_PTR)
	{

		ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

		/* Add the calculated removal amount, stored in                       */
		/* ADER_GRP_ISO_ELE_FRAC to the appropriate rows                      */

    	ADERSetMaterialCompMatrixRowBounds(0, 1, ader_mat_matrix_data,
    			                           (long)RDB[ader_mat_iso + ADER_MAT_ISO_BAL_ROW_ID],
										   (sign *
										    RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC]));

    	/* Deal with any pres row                                             */

    	ADERSetMaterialCompMatrixClusterMemPresRowBounds(ader_mat_matrix_data, mat,
    			                                         (sign *
    			                                          RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC]));

		ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

	}

}
