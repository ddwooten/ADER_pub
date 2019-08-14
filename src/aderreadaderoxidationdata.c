/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderreadaderoxidationdata.c                    */
/*                                                                           */
/* Created:       2015/11/30 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Reads in oxidation data items                                */
/*                                                                           */
/* Comments: Called by ADERCreateAderOxidationEntry                          */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERReadAderOxidationData:"

void ADERReadAderOxidationData(char* fname, long oxidation_ptr, long j,
                               long line, char** params, char* pname, long np)
{
    /* Track the processed item number for error reporting */

    long element_counter = 0;
    long oxidation_item = 0;

    while(j < np)
    {

        /* Each entry can have, at most, 4 components */
		/* Create new oxidation table entry */

		oxidation_item = NewItem(oxidation_ptr + ADER_OXI_ELES_PTR,
							   ADER_OXI_ELE_BLOCK_SIZE);

		/*Store the element Z value given from the string by IsotoZAI */

		WDB[oxidation_item + ADER_OXI_ELE_Z] = (double)IsotoZAI(params[j]);

		element_counter++;

		j++;

		/* If it's not an element or its not an input IsotoZAI can handle, die */

		if((long)WDB[oxidation_item + ADER_OXI_ELE_Z] <= 0 ||
		   (long)WDB[oxidation_item + ADER_OXI_ELE_Z] > NUMBER_OF_ELEMENTS)
		{

			Error(0, "Entry %ld in oxidation group %s, \n \
on line %ld in file %s, is not an element, \n \
given by an element symbol.\n", element_counter,
					  GetText(oxidation_ptr + ADER_OXI_TBL_ID),
					  line, fname);

		}

		/* Store the items oxidation value */

		WDB[oxidation_item + ADER_OXI_ELE_VAL] = TestParam(pname, fname,
															   line, params[j],
															   PTYPE_REAL,
															   -(double)NUMBER_OF_ELEMENTS,
															   1E+18);

		j++;

		/* If the item has a weight, store that. Otherwise, break the i */
		/* loop and go to the next entry */

		if(strncmp("weight", params[j], 6) == 0)
		{

			j++;

			WDB[oxidation_item + ADER_OXI_ELE_WEIGHT] = TestParam(pname,
																	  fname,
																	  line,
																	  params[j],
																	  PTYPE_REAL,
																	  -1E+18,
																	   1E+18);

			j++;

		}
		else
		{

			/* Set the weight to 1, because that's what it is             */

			WDB[oxidation_item + ADER_OXI_ELE_WEIGHT] = 1.0;

		}

    }

}
