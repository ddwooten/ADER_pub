/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetstreamtargetremovalamount.c             */
/*                                                                           */
/* Created:       2016/04/20 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: This function returns the removal amount of the target       */
/*              element or isotope.                                          */
/*                                                                           */
/* Comments:This function is called from ADERGetTargetRemovalAmount          */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetStreamTargetRemovalAmount:"

double ADERGetStreamTargetRemovalAmount(long ader_mat_stream, long ele, long iso)
{

	double amount = 0.0;
    long ader_mat_stream_ele = 0, ader_mat_stream_iso = 0;

    /* Get the element if thats asked for                                     */

    if(ele > 0)
    {

    	/* Loop through the stream's elements                                 */

    	ader_mat_stream_ele = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ELES_PTR];

    	while(ader_mat_stream_ele > VALID_PTR)
    	{

    		/* Find the matching element                                      */

    		if((long)RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_Z] == ele)
    		{

    			amount = RDB[ader_mat_stream_ele + ADER_MAT_GRP_ELE_FRAC];

    		}


    		ader_mat_stream_ele = NextItem(ader_mat_stream_ele);

    	}

    }
    else
    {

    	/* Get the isotope otherwise                                          */

    	/* Loop through the stream's isotopes                                 */

    	ader_mat_stream_iso = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_ISOS_PTR];

    	while(ader_mat_stream_iso > VALID_PTR)
    	{

    		/* Find the matching isotope                                      */

    		if((long)RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ZAI] == iso)
    		{

    			amount = RDB[ader_mat_stream_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

    		}


    		ader_mat_stream_iso = NextItem(ader_mat_stream_iso);

    	}

    }

    return(amount);

}
