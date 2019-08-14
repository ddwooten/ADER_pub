/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercontroldata.c                      */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in controlled elements and isotopes from an ADER       */
/*              control table denoted with the tag 'control'                 */
/*                                                                           */
/* Comments: Called by ADERCreateAderControlEntry                            */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderControlData:"

void ADERReadAderControlData(char* fname, long control_ptr, long j, long line,
                             char** params, char* pname, long np)
{
    long item_counter = 0;
    long id = 0, control_item = 0;

    while(j < np)
    {

        /* Create new control table entry */

        control_item = NewItem(control_ptr + ADER_CONTROL_ENT_PTR,
                               ADER_CONTROL_ENT_BLOCK_SIZE);

        /*Keep track of which entry in the table we are on for error reporting */

        item_counter++;

        /* The first entry in a control table is an element or isotope */
        /* alphanumeric indicator. Convert this string to either a Z or a ZAI */
        /* number with IsotoZAI function which will return -1 if it can't */

        id =  (long)IsotoZAI(params[j]);

        /* Kill if IsotoZAI coulnd't convert the string */

        if(id <= 0)
        {
            Error(0, "Entry %ld in removal group %s, \n \
on line %ld in file %s, is not valid.\n", item_counter,
                      GetText(control_ptr + ADER_CONTROL_TBL_ID),
                      line, fname);
        }
        /* Store in the Z spot if an element */

        else if(id < NUMBER_OF_ELEMENTS)
        {
            WDB[control_item + ADER_CONTROL_ENT_Z] = (double)id;

            j++;
        }
        /* Store in the ZAI spot if an isotope */

        else
        {
            WDB[control_item + ADER_CONTROL_ENT_ZAI] = (double)id;

            j++;

        }

    }

}
