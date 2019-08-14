/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderscorecrosssection.c                        */
/*                                                                           */
/* Created:       2016/04/16 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: If a material is under ADER control, and if it has reactivity*/
/*              control, this function will gather the cross section data    */
/*              from CalculateTransmuXS                                      */
/*                                                                           */
/* Comments:This function is called from CalculateTransmuXS                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERScoreCrossSection:"

void ADERScoreCrossSection(long abs, double E, long id, long mat, long nuc,
		                   long rea, double value)
{

    long ader_mat_iso = 0, mat_ader_data = 0, mat_iso = 0, mat_nuc = 0;

    /* If this material isn't under ADER control OR if it isn't involved in   */
    /* reactivity calculations, don't bother with this function               */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    if(mat_ader_data < VALID_PTR)
    {

        return;

    }

    if(RDB[mat_ader_data + ADER_MAT_RHO_WEIGHT] <= 0.0)
    {

        return;

    }

    /* Find the ader mat isotope that matches the nuclide                     */

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

        mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

        mat_nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[mat_nuc + NUCLIDE_ZAI] == (long)RDB[nuc + NUCLIDE_ZAI])
        {

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    /* If we didn't find a matching isotope, error out                        */

    if((long)RDB[mat_nuc + NUCLIDE_ZAI] != (long)RDB[nuc + NUCLIDE_ZAI])
    {

        Die(FUNCTION_NAME, "Error in function ADERScoreCrossSection. \n \
Please report this error to the SERPENT dev team. The easiest way is most \n \
likely the SERPENT users forums. Please include as much information about your\n \
simulation as possible. The following information will be most helpful. \n\n \
Material Name: %s \n\n \
ZAI of nuclide not found in ADER_MAT_ISO_PTR list: %ld \n\n \
OMP THREAD NUM: %ld \n\n", GetText(mat + MATERIAL_PTR_NAME),
            (long)RDB[nuc + NUCLIDE_ZAI], id);

    }

    /* Now, determine if the reaction should be scored and if so how          */
    /* Here the reaction is scored as fission because it has a fission yield  */
    /* and is not spontaneous fission                                         */

    if(abs == 0)
    {

        WDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_NUBAR_FIS_MIC_XS_CUR] +
        		                                                value;

    }
    else if(abs > 0)
		{

        	if(((long)RDB[rea + REACTION_MT] == 18)||
        	   ((long)RDB[rea + REACTION_MT] == 19)||
        	   ((long)RDB[rea + REACTION_MT] == 20)||
        	   ((long)RDB[rea + REACTION_MT] == 21)||
        	   ((long)RDB[rea + REACTION_MT] == 38))
			{

				WDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] +
																  value;

				WDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_FIS_MIC_XS_CUR] +
																		value;

			}
			else
			{

				WDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] = RDB[ader_mat_iso + ADER_MAT_ISO_ABS_MIC_XS_CUR] +
																  value;

			}

		}
    else
    {

    	return;

    }

}
