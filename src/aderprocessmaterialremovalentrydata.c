/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessmaterialremovalentrydata.c            */
/*                                                                           */
/* Created:       2016/1/20   (DDW)                                          */
/* Last modified: 2016/1/20   (DDW)                                          */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Links removal entries to a material stream's element and iso   */
/*              lists                                                        */
/*                                                                           */
/* Comments:This function is called from ADERProcessMaterialRemovalData        */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessMaterialRemovalEntryData:"

void ADERProcessMaterialRemovalEntryData(long ader_mat_strm, long ader_rem,
                                       long ele_iso_fix_check, long mat)
{

    long ader_mat_strm_ele_ent = 0, ader_mat_strm_iso_ent = 0;
    long ader_rem_entry = 0, ader_rem_entry_z = 0, ader_rem_entry_zai = 0;

    ader_rem_entry = (long)RDB[ader_rem + ADER_REPRO_ENT_PTR];

    while(ader_rem_entry > VALID_PTR)
    {

        ader_rem_entry_z = (long)RDB[ader_rem_entry + ADER_REPRO_ENT_Z];

        ader_rem_entry_zai = (long)RDB[ader_rem_entry + ADER_REPRO_ENT_ZAI];

        if(ader_rem_entry_z > 0)
        {

            /* If the ele_iso_fix_check is enabled, this is an error as all   */
            /* elements in this stream must have an explicit isotopic         */
            /* composition                                                    */

            if(ele_iso_fix_check > 0)
            {

                Error(0, "Element, Z value of %ld, found in removal table %s. \n\
This removal table is part of an ADER stream for which there is a destination \n \
material but no source material. These streams must have an explicit isotopic \n \
composition for every element. In the case of removal tables, this means the \n \
absence of any elemental entries.\n", ader_rem_entry_z,
                      GetText(ader_mat_strm + ADER_MAT_STREAM_ID));

            }

            /* if the removal item is an element, add it to the element list */

            ader_mat_strm_ele_ent = NewItem(ader_mat_strm + ADER_MAT_STREAM_ELES_PTR,
                                            ADER_MAT_GRP_ELE_BLOCK_SIZE);

            WDB[ader_mat_strm_ele_ent + ADER_MAT_GRP_ELE_Z] = RDB[ader_rem_entry + ADER_REPRO_ENT_Z];

            WDB[ader_mat_strm_ele_ent + ADER_MAT_GRP_ELE_FRAC] = RDB[ader_rem_entry + ADER_REPRO_ENT_VAL];

            /* We do not need to set the ADER_MAT_GRP_ELE_ISO_FIXED tag as all*/
            /* elements in a removal table have free isotopic compositions and*/
            /* this is indicated by a value of 0 for this tag which is the    */
            /* default value in the WDB array                                 */

        }
        else if(ader_rem_entry_zai > 0)
        {

			ader_mat_strm_iso_ent = NewItem(ader_mat_strm + ADER_MAT_STREAM_ISOS_PTR,
											ADER_MAT_GRP_ISO_BLOCK_SIZE);

			WDB[ader_mat_strm_iso_ent + ADER_MAT_GRP_ISO_ZAI] = RDB[ader_rem_entry + ADER_REPRO_ENT_ZAI];

			/* We skip assigning to ISO_ELE_FRAC as it has no meaning in the */
			/* removal table scheme. However, this tag will be used to store */
			/* the amount of an isotope removed every time step              */
			/*

			WDB[ader_mat_strm_iso_ent + ADER_MAT_GRP_ISO_ELE_FRAC] = 0.0      */

			WDB[ader_mat_strm_iso_ent + ADER_MAT_GRP_ISO_FRAC] = RDB[ader_rem_entry + ADER_REPRO_ENT_VAL];

        }

        ader_rem_entry = NextItem(ader_rem_entry);

    }

}
