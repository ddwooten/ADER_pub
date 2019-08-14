/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adercomparematerialremovaltables.c             */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Checks that two removal tables have distinct entries         */
/*                                                                           */
/* Comments:This function is called from ADERCheckMaterialRemovalTables      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERCompareMaterialRemovalTables:"

void ADERCompareMaterialRemovalTables(long ader_mat_stream, long mat,
                                      long passed_ader_mat_stream)
{

    long ader_mat_stream_iso = 0, passed_ader_mat_stream_iso = 0;

    /* Loop through the removal table's isotopes                              */

    ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

    while(ader_mat_stream_iso > VALID_PTR)
    {

        /* Now, loop through the passed in removal table's isotopes           */

        passed_ader_mat_stream_iso = (long)RDB[passed_ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

        while(passed_ader_mat_stream_iso > VALID_PTR)
        {

            /* Compare the ZAIs, if they are equal, this is an error, a       */
            /* material may not have multiple removal tables with matching    */
            /* isotopes                                                       */

            if((long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] == (long)RDB[passed_ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI])
            {

                Error(0, "Removal table %s and \n removal table %s both are \
assigned to \n material %s ( via ADER stream entries ) and have at least two \n \
of the same isotope - with ZAI of %ld. This isotope may not have been defined \n \
explicitly for either removal table, rather, it may been added as a member \n \
of an element in both tables. Materials are not allowed to be the source of \n \
multiple removal tables with matching isotopes.\n",
                      GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
                      GetText(passed_ader_mat_stream + ADER_MAT_STREAM_ID),
                      GetText(mat + MATERIAL_PTR_NAME),
                      (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI]);

            }

            passed_ader_mat_stream_iso = NextItem(passed_ader_mat_stream_iso);

        }

        ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

    }

}
