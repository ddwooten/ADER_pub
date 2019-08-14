/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadaderremovaldata.c                        */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in items in an ADER 'removal' table which has the name */
/*              'repro' table inside the code.                               */
/*                                                                           */
/* Comments: Called by ADERCreateAderRemovalEntry                              */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderRemovalData:"

void ADERReadAderRemovalData(char* fname, long repro_ptr, long j, long line,
                           char** params, char* pname, long np)
{
    /* Count the items processed for error reporting */

    long item_counter = 0;
    long id = 0, repro_item = 0;

    while(j < np)
    {

        /* Create new repro table entry */

        repro_item = NewItem(repro_ptr + ADER_REPRO_ENT_PTR,
                             ADER_REPRO_ENT_BLOCK_SIZE);

        item_counter++;

        /* The first entry in a repro table is an element or isotope */
        /* alphanumeric indicator. Convert this string to either a Z or a ZAI */
        /* number with IsotoZAI function which will return -1 if it can't */

        id =  (long)IsotoZAI(params[j]);

        /* Die if IsotoZAI can't convert the stirng */

        if(id <= 0)
        {
            Error(0, "Entry %ld in removal group %s, \n \
on line %ld in file %s, is not valid.\n", item_counter,
                      GetText(repro_ptr + ADER_REPRO_TBL_ID),
                      line, fname);
        }
        /* If it's an element, store it in the Z spot */

        else if(id <= NUMBER_OF_ELEMENTS)
        {

            WDB[repro_item + ADER_REPRO_ENT_Z] = (double)id;

        }
        /*If it's an isotope store it in the ZAI spot */

        else
        {

            WDB[repro_item + ADER_REPRO_ENT_ZAI] = (double)id;

        }

        j++;

        /* Store it's fractional ( of itself ) removal efficiency */

        WDB[repro_item + ADER_REPRO_ENT_VAL] = TestParam(pname, fname,
                                                         line, params[j],
                                                         PTYPE_REAL,
                                                         0.0, 1E+18);

        j++;

    }

}
