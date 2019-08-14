/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderoutputburnmatrixascsv.c                    */
/*                                                                           */
/* Created:       2017/02/04 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Writes a burnup matrix out in a csv file format              */
/*                                                                           */
/* Comments:This function is called from ADERBurnMaterials                   */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADEROutputBurnMatrixAsCsv:"

void ADEROutputBurnMatrixAsCsv(struct ccsMatrix* burn_matrix,
							   long ader_mat_burn_matrix_num_rows,
							   long mat, long step, long sub_step)
{

    char file_out[256];
	long i = 0, j = 0, k = 0;
	long *col = NULL, *row = NULL;
    complex *val = NULL;
    FILE *fp = NULL;

    /* Go ahead and create the file name                                      */

    sprintf(file_out, "Cluster_Parent_%s_Burn_Matrix_Step_%ld_Sub_Step_%ld.csv",
    		GetText(mat + MATERIAL_PTR_NAME), step, sub_step);

	if ((fp = fopen(file_out, "w")) == NULL)
	{

		Die(FUNCTION_NAME, "Unable to open cluster csv file for writing");

	}

	/* Print the warning into the file                                        */

	fprintf(fp, "WARNING!!!: Matrix is TRANSPOSED. Every ROW is ACTUALLY a COLUMN!!!.\n");

	/* Get the matrix storage units                                           */

    val = burn_matrix->values;
    row = burn_matrix->rowind;
    col = burn_matrix->colptr;

	/* Now, loop through the columns and output the matrix                    */

    for(i = 0; i < ader_mat_burn_matrix_num_rows; i++)
    {

    	k = 0;

    	for(j = 0; j < ader_mat_burn_matrix_num_rows; j++)
    	{

    		if(k >= col[i + 1])
    		{

    			if((j + 1) < ader_mat_burn_matrix_num_rows)
    			{

        			fprintf(fp, "0.0,");

    			}
    			else
    			{

        			fprintf(fp, "0.0");

    			}

    		}
    		else if(row[col[i] + k] == j)
    		{

    			if((j + 1) < ader_mat_burn_matrix_num_rows)
    			{

        			fprintf(fp, "%.22f,", val[col[i] + k].re);

    			}
    			else
    			{

        			fprintf(fp, "%.22f", val[col[i] + k].re);

    			}

				k++;

    		}
    		else
    		{

    			if((j + 1) < ader_mat_burn_matrix_num_rows)
    			{

        			fprintf(fp, "0.0,");

    			}
    			else
    			{

        			fprintf(fp, "0.0");

    			}

    		}

    	}

    	fprintf(fp, "\n");

    }

	/* Close the file                                                         */

	fclose(fp);

}
