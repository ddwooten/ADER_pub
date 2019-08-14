/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadadercndpresdata.c                      */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in 'preservation' tag in the cnd                       */
/*              ADER conditions tables. Returns the index of the next        */
/*              parameter to be checked by ADERReadAderCndData               */
/*                                                                           */
/* Comments: Called by ADERReadAderCndData                                   */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderCndPresData:"

long ADERReadAderCndPresData(char* fname, long cnd_ptr, long j, long line,
                            char** params, char* pname)
{
    char *ader_cnd_id = NULL, *ader_cnd_pres_ent = NULL;
    long ader_cnd_pres = 0;

    /* Catch bad user input */

    if((long)RDB[cnd_ptr + ADER_CND_PRES_PTR] > VALID_PTR)
    {

        ader_cnd_id = GetText(cnd_ptr + ADER_CND_ID);

        ader_cnd_pres = (long)RDB[cnd_ptr + ADER_CND_PRES_PTR];

        ader_cnd_pres_ent = GetText(ader_cnd_pres + ADER_CND_PRES_ENT);

        Error(0, "On line %ld in file %s,\n \
trying to add preservation entry %s to conditions block %s \n \
which already has preservation entry %s. Only one preservation entry per conditions block. \n \
Only one preservation entry per material as well.\n", line, fname, params[j],
              ader_cnd_id, ader_cnd_pres_ent);

    }

    /* Create new preservation entry  for this conditions block               */

    ader_cnd_pres = NewItem(cnd_ptr + ADER_CND_PRES_PTR, ADER_CND_PRES_BLOCK_SIZE);

    /*Store the name */

    WDB[ader_cnd_pres + ADER_CND_PRES_ENT] = (double)PutText(params[j]);

    j++;

    return(j);
}
