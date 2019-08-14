/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintmaterialstreamisotopes.c              */
/*                                                                           */
/* Created:       2016/25/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Prints stream isotopes to file                               */
/*                                                                           */
/* Comments:This function is called from ADERPrintListsHierarchy             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintMaterialStreamIsotopes:"

void ADERPrintMaterialStreamIsotopes(long ader_mat_stream, FILE *fp, long mat)
{

	long ader_mat_iso = 0, ader_mat_stream_iso = 0;
    long ader_mat_stream_sum_stream = 0, ader_mat_stream_sum_stream_ent = 0;
    long mat_iso = 0, nuc = 0;

    /* Loop into sum streams                                                  */

    ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    {

    	ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

        /* Process these streams if they exist                               */

    	ADERPrintMaterialStreamIsotopes( ader_mat_stream_sum_stream, fp, mat);

    	ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    }

    ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

    while(ader_mat_stream_iso > VALID_PTR)
    {

    	ader_mat_iso = (long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	fprintf(fp, "%s, %s, %s, %s, %ld\n",
    			GetText(mat + MATERIAL_PTR_NAME),
				GetText(ader_mat_stream + ADER_MAT_STREAM_ID),
				GetText(ader_mat_stream + ADER_MAT_STREAM_SRC),
				GetText(ader_mat_stream + ADER_MAT_STREAM_DEST),
				(long)RDB[nuc + NUCLIDE_ZAI]);

    	fprintf(fp, "    ADER_MAT_STREAM: %ld\n", ader_mat_stream);

    	fprintf(fp, "    ADER_MAT_STREAM_ISOS_PTR: %ld\n", ader_mat_stream_iso);

    	fprintf(fp, "    MATERIAL_COMPOSITION_PTR: %ld\n", mat_iso);

    	fprintf(fp, "    COMPOSITION_PTR_NUCLIDE: %ld\n", nuc);

    	fprintf(fp, "    ADER_MAT_ISOS_PTR: %ld\n", ader_mat_iso);

    	fprintf(fp, "    ADER_MAT_ISO_BURN_INDEX: %ld\n", (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX]);

    	fprintf(fp, "\n");

    	ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

    }

}
