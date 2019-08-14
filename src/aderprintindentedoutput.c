/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintindentedoutput.c                      */
/*                                                                           */
/* Created:       2017/02/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Simple wrapper to reduce instruction set for indented output */
/*                                                                           */
/* Comments:This function is called from ADEROutputMaterialCompMatrixAsJson  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintIndentedOutput:"

void ADERPrintIndentedOutput(FILE* fp, char* print_data,long tab_length,
		                     long tab_level)
{

	fprintf(fp, "%*s%s\n", (int)(tab_level * tab_length), "", print_data);

}
