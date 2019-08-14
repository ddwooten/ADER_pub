/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprintsumstreams.c                          */
/*                                                                           */
/* Created:       2016/25/09 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Provides information regarding ADER summation streams for the*/
/*              ADERPrintListsHierarchy function                             */
/*                                                                           */
/* Comments:This function is called from ADERPrintListsHierarchy             */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERPrintSumStreams:"

void ADERPrintSumStreams(long ader_mat_stream_sum_ent, FILE* fp, int sum_level)
{

    char print_data[256];
    long ader_mat_stream_sum_stream = 0;

    while(ader_mat_stream_sum_ent > VALID_PTR)
    {

        /* Get the actual sum stream pointed to by the stream_sum_ent             */

        ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

        /* Print the data                                                         */

    	sprintf(print_data, "        %i: %s, %ld\n", sum_level,
    			GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID),
    			ader_mat_stream_sum_stream);

    	fprintf(fp, "%s", print_data);

    	ADERPrintSumStreams((long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_SUM_GRPS_PTR],
    			            fp, sum_level + 1);

    	ader_mat_stream_sum_ent = NextItem(ader_mat_stream_sum_ent);

    }

}
