/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : aderprocessadermaindata.c                      */
/*                                                                           */
/* Created:       2015/12/8 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Calls various functions to process main ader input not       */
/*              not related to specific materials                            */
/*                                                                           */
/* Comments:This function is called from main.c                              */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERProcessAderMainData:"

void ADERProcessAderMainData()
{

    long ader_data = 0;

    ader_data = (long)RDB[DATA_PTR_ADER];

    /* If no max iteration was set for the transport cycle, set it here       */

    if((long)RDB[ader_data + ADER_TRANS_ITER] < 1)
    {

        WDB[ader_data + ADER_TRANS_ITER] = 5.0;

    }

    /* Set the initial ADER iteration showing that ADER iterations have not   */
    /* yet started                                                            */

    WDB[(long)RDB[DATA_PTR_ADER] + ADER_TRANS_ITER_NUM] = -1.0;

    ADERProcessAderGroups();

    ADERProcessAderStreams();

    ADERProcessAderClusters();

}
