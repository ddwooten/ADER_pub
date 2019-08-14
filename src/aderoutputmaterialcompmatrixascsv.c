/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoutputmaterialcompmatrixascsv.c            */
/*                                                                           */
/* Created:       2017/02/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Writes a cluster composition matrix out in a csv file format */
/*                                                                           */
/* Comments:This function is called from ADEROutputMaterialCompMatrixData    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROutputMaterialCompMatrixAsCsv:"

void ADEROutputMaterialCompMatrixAsCsv(long ader_mat_matrix_data,
		                               long cluster_num)
{

    char file_out[256];
    long ader_mat_matrix_col = 0, ader_mat_matrix_col_row = 0;
    FILE *fp = NULL;

    /* Go ahead and create the file name                                      */

    sprintf(file_out, "Cluster_%ld_Material_Composition_Matrix.csv", cluster_num);

	if ((fp = fopen(file_out, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open cluster csv file for writing");

	}

	/* Print the warning into the file                                        */

	fprintf(fp, "WARNING!!!: Matrix is TRANSPOSED. Every ROW is ACTUALLY a COLUMN!!!.\n");

	/* Now, loop through the rows and columns of the matrix, but first, do    */
	/* the first column so that the \n trick at the begining of the loop ( to */
	/* avoid trailing new lines and commas ) works                            */

	ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

	ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

	/* Also do the first row so no trailing comma                             */

	fprintf(fp, "%.8f", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

	ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

	while(ader_mat_matrix_col_row > VALID_PTR)
	{

		fprintf(fp, ",%.8f", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

		ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

	}

	/* Now loop the rest of the columns                                       */

	ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

	while(ader_mat_matrix_col > VALID_PTR)
	{

		fprintf(fp, "\n");

		/* Again, do the first row, and then loop the rest                    */

		ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

		fprintf(fp, "%.8f", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

		ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

		while(ader_mat_matrix_col_row > VALID_PTR)
		{

			fprintf(fp, ",%.8f", RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

			ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

		}

		ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

	}

	/* Close the file                                                         */

	fclose(fp);

}
