/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadergroupisosdata.c                    */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Given the number of isotopes by ADERReadAderGroupItemData    */
/*              loop through the isotope entries storing their information   */
/*              Returns the index of the next parameter to be checked        */
/*                                                                           */
/* Comments: Called by ADERReadAderGroupItemData                             */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderGroupIsosData:"

long ADERReadAderGroupIsosData(long comp_ptr, char* fname, long group_ptr,
                               long j, long line, char** params, char* pname,
                               int num_isos)
{
    long iso_ptr = 0;
    int i = 0;

    for(i = 0; i < num_isos; i++)
    {
        /* Create a new isotope entry in the composition entry for the parent */
        /* group */

        iso_ptr = NewItem(comp_ptr + ADER_GRP_COMP_ISOS_PTR,
                          ADER_GRP_ISO_BLOCK_SIZE);

        WDB[iso_ptr + ADER_GRP_ISO_ZAI] = (double)IsotoZAI(params[j]);

        /*If it's not an isotope ZAI, die */

        if(RDB[iso_ptr + ADER_GRP_ISO_ZAI] < NUMBER_OF_ELEMENTS)
        {
            Error(0, "Iso in group %s, found on line %ld \n \
in file %s, is either not recognizable by \n \
IsotoZai or is not an isotope. \n \
IsotoZai output is %ld.\n",
                  GetText(group_ptr + ADER_GRP_ID), line, fname,
                  RDB[iso_ptr + ADER_GRP_ISO_ZAI]);
        }

        j++;

        /* Store it's fraction of the element who is it's parent */

        WDB[iso_ptr + ADER_GRP_ISO_FRAC] = TestParam(pname, fname, line,
                                                     params[j], PTYPE_REAL,
                                                     0.0, 1E+6);

        j++;
    }

    return(j);
}
