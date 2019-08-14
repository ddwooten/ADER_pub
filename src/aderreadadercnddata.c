/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercnddata.c                          */
/*                                                                           */
/* Created:       2015/11/25 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the entries in an ADER conditions ( tag 'cnd') */
/*              table. Calls auxiliary function to deal with each tag type   */
/*              which themselves return the new parameter to be checked      */
/*                                                                           */
/* Comments: Called by ADERCreateAderCndEntry                                */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderCndData:"

void ADERReadAderCndData(char* fname, long cnd_ptr, long j, long line,
                         char** params, char* pname, long np)
{

    /* track the number of entries for error reporting */

    int entry_counter = 0;

    /* Check the parameter. Call the appropriate function or error out. */

    while(j < np)
    {

        if(strncmp("cnt", params[j], 3) == 0)
        {

            j++;

            j = ADERReadAderCndCntData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;

        }
        else if(strncmp("rng", params[j], 3) == 0)
        {

            j++;

            j = ADERReadAderCndRngData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;

        }
        else if(strncmp("rto", params[j], 3) == 0)
        {

            j++;

            j = ADERReadAderCndRtoData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;

        }
        else if(strncmp("opt", params[j], 3) == 0)
        {

            j++;

            j = ADERReadAderCndOptData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;

        }
        else if(strncmp("oxi", params[j], 3) == 0)
        {

            j++;

            j = ADERReadAderCndOxiData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;

        }
        else if(strncmp("preserve", params[j], 8) == 0)
        {

            j++;

            j = ADERReadAderCndPresData(fname, cnd_ptr, j, line, params, pname);

            entry_counter++;
        }
        else
        {

            Error(0, "Entry %d for cnd table %s, on line %ld in file %s, \n \
does not have valid ID type of, either,\n \
cnt, opt, pres, rng, rto or val.\n",
                  entry_counter, GetText(cnd_ptr + ADER_CND_ID), line, fname);

        }

    }

}
