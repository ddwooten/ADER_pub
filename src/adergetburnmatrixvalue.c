/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adergetburnmatrixvalue.c                       */
/*                                                                           */
/* Created:       2016/22/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Returns the real component of a value found at the passed in */
/*              indices of a burn matrix                                     */
/*                                                                           */
/* Comments:This function is called from TESTADERGetBurnMatrixValue          */
/*                                       TESTADERMakeBurnMatrix              */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERGetBurnMatrixValue:"

double ADERGetBurnMatrixValue(long col_index, struct ccsMatrix* burn_matrix,
		                      long row_index)
{

	double value = 0.0;
	long i = 0;
	long *col = NULL, *row = NULL;
    complex *val = NULL;

    /* Get pointers to matrix components                                      */

    val = burn_matrix->values;
    row = burn_matrix->rowind;
    col = burn_matrix->colptr;

    /* Col[column_index] stores the row index at which the values in the      */
    /* column represented by column_index start in the row and val vectors.   */
    /* From that index forward, until the index given by Col[column_index + 1]*/
    /* , search row for the passed in row index. The vector index at which the*/
    /* target index is found is the vector index in val which holds the value */
    /* which belongs at the passed in indices                                 */

    for(i = col[col_index]; i < (col[col_index + 1]); i++)
    {

    	if(row[i] == row_index)
    	{

    		value = val[i].re;

    		break;

    	}

    }

	return(value);

}
