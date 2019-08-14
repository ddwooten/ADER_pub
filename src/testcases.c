/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : printtest.c                                    */
/*                                                                           */
/* Created:       2015/10/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Holds tests. Does not actually run them. runtests.c does.    */
/*                                                                           */
/* Comments:                                                                 */
/*                                                                           */
/*****************************************************************************/

#include "element_data.h"
#include "header.h"
#include "locations.h"
#include "serp_tests.h"

/*****************************************************************************/

int test_num_cases = 172;

int Test_ADERFillMatCompMatrixCmpFutEle();
int Test_ADERFillMatCompMatrixCmpFutIso();
int Test_ADERFillMatCompMatrixCmpSumGrp();
int Test_ADERFillMatCompMatrixEleDelBal();
int Test_ADERFillMatCompMatrixEleDelDel();
int Test_ADERFillMatCompMatrixEleFutBal();
int Test_ADERFillMatCompMatrixEleFutFut();
int Test_ADERFillMatCompMatrixEleIsoFutEle();
int Test_ADERFillMatCompMatrixEleIsoFutIso();
int Test_ADERFillMatCompMatrixIsoDelBal();
int Test_ADERFillMatCompMatrixIsoDelDel();
int Test_ADERFillMatCompMatrixIsoFutBal();
int Test_ADERFillMatCompMatrixIsoFutFut();
int Test_ADERFillMatCompMatrixOxiFutEle();
int Test_ADERFillMatCompMatrixStreamDelEle();
int Test_ADERFillMatCompMatrixStreamDelIso();
int Test_ADERFillMatCompMatrixStreamSumGrp();
int Test_ADERFillMatCompMatrixSumStreamDelEle();
int Test_ADERFillMatCompMatrixSumStreamDelIso();
int Test_ADERGetMatEleIsoFrac();
int Test_ADERProcessAderGrpCmpFrac();
int Test_ADERProcessAderGrpIsoFrac();
int Test_ADERProcessAderMatClusterMems();
int Test_ADERProcessAderMatClusterParent();
int Test_ADERProcessAderMatCmpEleFrac();
int Test_ADERProcessAderMatCmpGrpPtr();
int Test_ADERProcessAderMatCmpIsoEleFrac();
int Test_ADERProcessAderMatCmpIsoFrac();
int Test_ADERProcessAderMatCmpRngMax();
int Test_ADERProcessAderMatCmpRngMin();
int Test_ADERProcessAderMatCmpRto2GrpPtr();
int Test_ADERProcessAderMatCmpRtoMax();
int Test_ADERProcessAderMatCmpRtoMin();
int Test_ADERProcessAderMatCmpSumGrpsPtr();
int Test_ADERProcessAderMatCmpSumGrpWeight();
int Test_ADERProcessAderMatCndPtr();
int Test_ADERProcessAderMatCntTblPtr();
int Test_ADERProcessAderMatIsoPtr();
int Test_ADERProcessAderMatOptDir();
int Test_ADERProcessAderMatOptType();
int Test_ADERProcessAderMatOptTypeTarget();
int Test_ADERProcessAderMatOxiMax();
int Test_ADERProcessAderMatOxiMin();
int Test_ADERProcessAderMatOxiTblPtr();
int Test_ADERProcessAderMatPreserveType();
int Test_ADERProcessAderMatStrmDest();
int Test_ADERProcessAderMatStrmEleFix();
int Test_ADERProcessAderMatStrmEleFrac();
int Test_ADERProcessAderMatStrmFeedType();
int Test_ADERProcessAderMatStrmForm();
int Test_ADERProcessAderMatStrmIsoEleFrac();
int Test_ADERProcessAderMatStrmIsoFrac();
int Test_ADERProcessAderMatStrmMatPtr();
int Test_ADERProcessAderMatStrmPtr();
int Test_ADERProcessAderMatStrmRedoxType();
int Test_ADERProcessAderMatStrmRemvGroup();
int Test_ADERProcessAderMatStrmRemvType();
int Test_ADERProcessAderMatStrmReacType();
int Test_ADERProcessAderMatStrmShadowPtr();
int Test_ADERProcessAderMatStrmShadowSumStrmPtr();
int Test_ADERProcessAderMatStrmSrc();
int Test_ADERProcessAderMatStrmSumGrpsPtr();
int Test_ADERProcessAderMatStrmTypeGroup();
int Test_ADERProcessAderMatStrmTypeRem();
int Test_ADERProcessAderReproElement();
int Test_ADERProcessAderReproIsoEle();
int Test_ADERProcessAderReproIsotope();
int Test_ADERProcessAderStreamSourcesAndDests();
int Test_ADERProcessAderSumGrpPtr();
int Test_ADERProcessMatClusterOpt();
int Test_ADERProcessMatCmpIsoMatAderIsoPtr();
int Test_ADERProcessMatGrpEleIsoPtr();
int Test_ADERProcessMatReproEleIsoRate();
int Test_ADERProcessMatReproIsoRate();
int Test_ADERProcessMatStreamIsoMatAderIsoPtr();
int Test_ADERProcessMatStreamEleUnFixedIsos();
int Test_ADERSetAderClusterMembers();
int Test_ADERSetAderCndCntId();
int Test_ADERSetAderCndId();
int Test_ADERSetAderCndOptDir();
int Test_ADERSetAderCndOptTarget();
int Test_ADERSetAderCndOptType();
int Test_ADERSetAderCndOxiId();
int Test_ADERSetAderCndOxiMax();
int Test_ADERSetAderCndOxiMin();
int Test_ADERSetAderCndOxiVal();
int Test_ADERSetAderCndPreserveType();
int Test_ADERSetAderCndRngGrpId();
int Test_ADERSetAderCndRngMax();
int Test_ADERSetAderCndRngMin();
int Test_ADERSetAderCndRngVal();
int Test_ADERSetAderCndRtoGrpId();
int Test_ADERSetAderCndRtoMax();
int Test_ADERSetAderCndRtoMin();
int Test_ADERSetAderCndRtoVal();
int Test_ADERSetAderControlEntZ();
int Test_ADERSetAderControlEntZai();
int Test_ADERSetAderControlTblId();
int Test_ADERSetAderGrpCompZ();
int Test_ADERSetAderGrpId();
int Test_ADERSetAderGrpIsoZai();
int Test_ADERSetAderGrpSumGroupsPtr();
int Test_ADERSetAderKMax();
int Test_ADERSetAderKMin();
int Test_ADERSetAderNegAdens();
int Test_ADERSetAderOxiEleVal();
int Test_ADERSetAderOxiEleWeight();
int Test_ADERSetAderOxiEleZ();
int Test_ADERSetAderOxiTblId();
int Test_ADERSetAderReproEntVal();
int Test_ADERSetAderReproEntZ();
int Test_ADERSetAderReproEntZai();
int Test_ADERSetAderReproTblId();
int Test_ADERSetAderStrDest();
int Test_ADERSetAderStrForm();
int Test_ADERSetAderStrGrpId();
int Test_ADERSetAderStrGrpType();
int Test_ADERSetAderStrOpt1();
int Test_ADERSetAderStrSrc();
int Test_ADERSetAderStrType();
int Test_ADERSetAderSumGrpWeight();
int Test_ADERSetAderTransIter();
int Test_ADERSetMatAderMem();
int Test_ADERSetMatAderCndMem();
int Test_ADERSetMatCmpColLowerBounds();
int Test_ADERSetMatCmpColId();
int Test_ADERSetMatCmpColUpperBounds();
int Test_ADERSetMatCmpSumRowId();
int Test_ADERSetMatCompMatrixElement();
int Test_ADERSetMatEleBalRowId();
int Test_ADERSetMatEleControl();
int Test_ADERSetMatEleDelColId();
int Test_ADERSetMatEleDelColPtr();
int Test_ADERSetMatEleDelRowId();
int Test_ADERSetMatEleFutColId();
int Test_ADERSetMatEleFutColPtr();
int Test_ADERSetMatEleFutRowId();
int Test_ADERSetMatEleIsoAderMatIsoPtr();
int Test_ADERSetMatEleIsoRowId();
int Test_ADERSetMatIsoBalRowId();
int Test_ADERSetMatIsoControl();
int Test_ADERSetMatIsoDelColId();
int Test_ADERSetMatIsoDelColPtr();
int Test_ADERSetMatIsoDelRowId();
int Test_ADERSetMatIsoFutColId();
int Test_ADERSetMatIsoFutColPtr();
int Test_ADERSetMatIsoFutRowId();
int Test_ADERSetMatKMaxRowBounds();
int Test_ADERSetMatKMaxRowId();
int Test_ADERSetMatKMinRowBounds();
int Test_ADERSetMatKMinRowId();
int Test_ADERSetMatObjGroup();
int Test_ADERSetMatObjFeed();
int Test_ADERSetMatObjFeedAndRemoval();
int Test_ADERSetMatObjReac();
int Test_ADERSetMatObjRedox();
int Test_ADERSetMatObjRemoval();
int Test_ADERSetMatObjStream();
int Test_ADERSetMatObjStreams();
int Test_ADERSetMatObjTransfers();
int Test_ADERSetMatOxiRowBounds();
int Test_ADERSetMatOxiRowId();
int Test_ADERSetMatParentMPINum();
int Test_ADERSetMatPreserveRowBounds();
int Test_ADERSetMatPreserveRowId();
int Test_ADERSetMatStrmColId();
int Test_ADERSetMatStrmShadowColId();
int Test_ADERSetMatStrmShadowSumColId();
int Test_ADERSetMatStrmShadowSumRowId();
int Test_ADERSetMatStrmSumColId();
int Test_ADERSetMatStrmSumRowId();
int Test_RunTests();


int (*test_foo_array[172])() = {&Test_ADERFillMatCompMatrixCmpFutEle,
                              &Test_ADERFillMatCompMatrixCmpFutIso,
                              &Test_ADERFillMatCompMatrixCmpSumGrp,
                              &Test_ADERFillMatCompMatrixEleDelBal,
                              &Test_ADERFillMatCompMatrixEleDelDel,
                              &Test_ADERFillMatCompMatrixEleFutBal,
                              &Test_ADERFillMatCompMatrixEleFutFut,
                              &Test_ADERFillMatCompMatrixEleIsoFutEle,
                              &Test_ADERFillMatCompMatrixEleIsoFutIso,
                              &Test_ADERFillMatCompMatrixIsoDelBal,
                              &Test_ADERFillMatCompMatrixIsoDelDel,
                              &Test_ADERFillMatCompMatrixIsoFutBal,
                              &Test_ADERFillMatCompMatrixIsoFutFut,
                              &Test_ADERFillMatCompMatrixOxiFutEle,
                              &Test_ADERFillMatCompMatrixStreamDelEle,
                              &Test_ADERFillMatCompMatrixStreamDelIso,
                              &Test_ADERFillMatCompMatrixStreamSumGrp,
							  &Test_ADERFillMatCompMatrixSumStreamDelEle,
							  &Test_ADERFillMatCompMatrixSumStreamDelIso,
                              &Test_ADERGetMatEleIsoFrac,
                              &Test_ADERProcessAderGrpCmpFrac,
                              &Test_ADERProcessAderGrpIsoFrac,
                              &Test_ADERProcessAderMatClusterMems,
                              &Test_ADERProcessAderMatClusterParent,
                              &Test_ADERProcessAderMatCmpEleFrac,
                              &Test_ADERProcessAderMatCmpGrpPtr,
                              &Test_ADERProcessAderMatCmpIsoEleFrac,
                              &Test_ADERProcessAderMatCmpIsoFrac,
                              &Test_ADERProcessAderMatCmpRngMax,
                              &Test_ADERProcessAderMatCmpRngMin,
                              &Test_ADERProcessAderMatCmpRto2GrpPtr,
                              &Test_ADERProcessAderMatCmpRtoMax,
                              &Test_ADERProcessAderMatCmpRtoMin,
                              &Test_ADERProcessAderMatCmpSumGrpsPtr,
                              &Test_ADERProcessAderMatCmpSumGrpWeight,
                              &Test_ADERProcessAderMatCndPtr,
                              &Test_ADERProcessAderMatCntTblPtr,
                              &Test_ADERProcessAderMatIsoPtr,
                              &Test_ADERProcessAderMatOptDir,
                              &Test_ADERProcessAderMatOptType,
                              &Test_ADERProcessAderMatOptTypeTarget,
                              &Test_ADERProcessAderMatOxiMax,
                              &Test_ADERProcessAderMatOxiMin,
                              &Test_ADERProcessAderMatOxiTblPtr,
                              &Test_ADERProcessAderMatPreserveType,
                              &Test_ADERProcessAderMatStrmDest,
                              &Test_ADERProcessAderMatStrmEleFix,
                              &Test_ADERProcessAderMatStrmEleFrac,
                              &Test_ADERProcessAderMatStrmFeedType,
                              &Test_ADERProcessAderMatStrmForm,
                              &Test_ADERProcessAderMatStrmIsoEleFrac,
                              &Test_ADERProcessAderMatStrmIsoFrac,
							  &Test_ADERProcessAderMatStrmMatPtr,
                              &Test_ADERProcessAderMatStrmPtr,
                              &Test_ADERProcessAderMatStrmRedoxType,
                              &Test_ADERProcessAderMatStrmRemvGroup,
                              &Test_ADERProcessAderMatStrmRemvType,
                              &Test_ADERProcessAderMatStrmReacType,
                              &Test_ADERProcessAderMatStrmShadowPtr,
                              &Test_ADERProcessAderMatStrmShadowSumStrmPtr,
                              &Test_ADERProcessAderMatStrmSrc,
                              &Test_ADERProcessAderMatStrmSumGrpsPtr,
                              &Test_ADERProcessAderMatStrmTypeGroup,
                              &Test_ADERProcessAderMatStrmTypeRem,
                              &Test_ADERProcessAderReproElement,
							  &Test_ADERProcessAderReproIsoEle,
                              &Test_ADERProcessAderReproIsotope,
                              &Test_ADERProcessAderStreamSourcesAndDests,
                              &Test_ADERProcessAderSumGrpPtr,
                              &Test_ADERProcessMatClusterOpt,
                              &Test_ADERProcessMatCmpIsoMatAderIsoPtr,
                              &Test_ADERProcessMatReproEleIsoRate,
                              &Test_ADERProcessMatReproIsoRate,
                              &Test_ADERProcessMatStreamIsoMatAderIsoPtr,
                              &Test_ADERProcessMatGrpEleIsoPtr,
                              &Test_ADERProcessMatStreamEleUnFixedIsos,
                              &Test_ADERSetAderClusterMembers,
                              &Test_ADERSetAderCndCntId,
                              &Test_ADERSetAderCndId,
                              &Test_ADERSetAderCndOptDir,
                              &Test_ADERSetAderCndOptTarget,
                              &Test_ADERSetAderCndOptType,
                              &Test_ADERSetAderCndOxiId,
                              &Test_ADERSetAderCndOxiMax,
                              &Test_ADERSetAderCndOxiMin,
                              &Test_ADERSetAderCndOxiVal,
                              &Test_ADERSetAderCndPreserveType,
                              &Test_ADERSetAderCndRngGrpId,
                              &Test_ADERSetAderCndRngMax,
                              &Test_ADERSetAderCndRngMin,
                              &Test_ADERSetAderCndRngVal,
                              &Test_ADERSetAderCndRtoGrpId,
                              &Test_ADERSetAderCndRtoMax,
                              &Test_ADERSetAderCndRtoMin,
                              &Test_ADERSetAderCndRtoVal,
                              &Test_ADERSetAderControlEntZ,
                              &Test_ADERSetAderControlEntZai,
                              &Test_ADERSetAderControlTblId,
                              &Test_ADERSetAderGrpCompZ,
                              &Test_ADERSetAderGrpId,
                              &Test_ADERSetAderGrpIsoZai,
                              &Test_ADERSetAderGrpSumGroupsPtr,
                              &Test_ADERSetAderKMax,
                              &Test_ADERSetAderKMin,
							  &Test_ADERSetAderNegAdens,
                              &Test_ADERSetAderOxiEleVal,
                              &Test_ADERSetAderOxiEleWeight,
                              &Test_ADERSetAderOxiEleZ,
                              &Test_ADERSetAderOxiTblId,
                              &Test_ADERSetAderReproEntVal,
                              &Test_ADERSetAderReproEntZ,
                              &Test_ADERSetAderReproEntZai,
                              &Test_ADERSetAderReproTblId,
                              &Test_ADERSetAderStrDest,
                              &Test_ADERSetAderStrForm,
                              &Test_ADERSetAderStrGrpId,
                              &Test_ADERSetAderStrGrpType,
                              &Test_ADERSetAderStrOpt1,
                              &Test_ADERSetAderStrSrc,
                              &Test_ADERSetAderStrType,
                              &Test_ADERSetAderSumGrpWeight,
                              &Test_ADERSetAderTransIter,
                              &Test_ADERSetMatAderMem,
                              &Test_ADERSetMatAderCndMem,
                              &Test_ADERSetMatCmpColLowerBounds,
                              &Test_ADERSetMatCmpColId,
                              &Test_ADERSetMatCmpColLowerBounds,
                              &Test_ADERSetMatCmpSumRowId,
                              &Test_ADERSetMatCompMatrixElement,
                              &Test_ADERSetMatEleBalRowId,
							  &Test_ADERSetMatEleControl,
                              &Test_ADERSetMatEleDelColId,
                              &Test_ADERSetMatEleDelColPtr,
                              &Test_ADERSetMatEleDelRowId,
                              &Test_ADERSetMatEleFutColId,
                              &Test_ADERSetMatEleFutColPtr,
                              &Test_ADERSetMatEleFutRowId,
                              &Test_ADERSetMatEleIsoAderMatIsoPtr,
                              &Test_ADERSetMatEleIsoRowId,
                              &Test_ADERSetMatIsoBalRowId,
							  &Test_ADERSetMatIsoControl,
                              &Test_ADERSetMatIsoDelColId,
                              &Test_ADERSetMatIsoDelColPtr,
                              &Test_ADERSetMatIsoDelRowId,
                              &Test_ADERSetMatIsoFutColId,
                              &Test_ADERSetMatIsoFutColPtr,
                              &Test_ADERSetMatIsoFutRowId,
                              &Test_ADERSetMatKMaxRowBounds,
                              &Test_ADERSetMatKMaxRowId,
                              &Test_ADERSetMatKMinRowBounds,
                              &Test_ADERSetMatKMinRowId,
                              &Test_ADERSetMatObjGroup,
                              &Test_ADERSetMatObjFeed,
                              &Test_ADERSetMatObjFeedAndRemoval,
                              &Test_ADERSetMatObjReac,
                              &Test_ADERSetMatObjRedox,
                              &Test_ADERSetMatObjRemoval,
                              &Test_ADERSetMatObjStream,
                              &Test_ADERSetMatObjStreams,
                              &Test_ADERSetMatObjTransfers,
                              &Test_ADERSetMatOxiRowBounds,
                              &Test_ADERSetMatOxiRowId,
                              &Test_ADERSetMatParentMPINum,
                              &Test_ADERSetMatPreserveRowBounds,
                              &Test_ADERSetMatPreserveRowId,
                              &Test_ADERSetMatStrmColId,
                              &Test_ADERSetMatStrmShadowColId,
                              &Test_ADERSetMatStrmShadowSumColId,
                              &Test_ADERSetMatStrmShadowSumRowId,
                              &Test_ADERSetMatStrmSumColId,
                              &Test_ADERSetMatStrmSumRowId,
                              &Test_RunTests};

int Test_ADERFillMatCompMatrixCmpFutEle()
{
    char *const test_name = "ADERFillMatCompMatrixCmpFutEle";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_cmp, mat_cmp_col, mat_ele, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixCmpFutEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(mat_cmp > VALID_PTR)
    {

        if(strncmp("FLiBe", GetText(mat_cmp + ADER_MAT_CMP_ID), 5) == 0)
        {

            mat_cmp_col = (long)RDB[mat_cmp + ADER_MAT_CMP_COL_ID];

            sprintf(print_data, "FLiBeFuel has no Li ele in ader data.\n");

            break;

        }

        mat_cmp = NextItem(mat_cmp);

    }

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_cmp_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_row, mat_cmp_col,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 0.374608);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.374607 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 0.374609)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixCmpFutIso()
{
    char *const test_name = "ADERFillMatCompMatrixCmpFutIso";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_cmp, mat_cmp_col, mat_iso, mat_iso_act;
    long mat_iso_row, mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixCmpFutIso.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(mat_cmp > VALID_PTR)
    {

        if(strncmp("FLiBe", GetText(mat_cmp + ADER_MAT_CMP_ID), 5) == 0)
        {

            mat_cmp_col = (long)RDB[mat_cmp + ADER_MAT_CMP_COL_ID];

            sprintf(print_data, "FLiBeFuel has no Li-6 iso in ader data.\n");

            break;

        }

        mat_cmp = NextItem(mat_cmp);

    }

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_FUT_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_cmp_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %1.8e but \n\
needs value %1.8e.\n", mat_iso_row, mat_cmp_col,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 0.0003746);

    if((RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.000373) &&
       (RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 0.000375))
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixCmpSumGrp()
{
    char *const test_name = "ADERFillMatCompMatrixCmpSumGrp";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_cmp, mat_cmp_sum_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;
    long mat_sum_cmp, mat_sum_cmp_col, mat_sum_cmp_grp;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixCmpSumGrp.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no ActF cmp group.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(mat_cmp > VALID_PTR)
    {

        if(strncmp("ActF", GetText(mat_cmp + ADER_MAT_CMP_ID), 4) == 0)
        {

            mat_cmp_sum_row = (long)RDB[mat_cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID];

            sprintf(print_data, "FLiBeFuel has no Uranium cmp.\n");

            break;

        }

        mat_cmp = NextItem(mat_cmp);

    }

    mat_sum_cmp = (long)RDB[mat_cmp + ADER_MAT_CMP_SUM_GRPS_PTR];

    while(mat_sum_cmp > VALID_PTR)
    {

        if(strncmp("Uranium", GetText(mat_sum_cmp + ADER_GRP_SUM_GRP_ID), 7) == 0)
        {

            mat_sum_cmp_grp = (long)RDB[mat_sum_cmp + ADER_GRP_SUM_GRP_PTR];

            mat_sum_cmp_col = (long)RDB[mat_sum_cmp_grp + ADER_MAT_CMP_COL_ID];

            break;

        }

        mat_sum_cmp = NextItem(mat_sum_cmp);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_sum_cmp_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_cmp_sum_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_sum_cmp_col, mat_cmp_sum_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixEleDelBal()
{
    char *const test_name = "ADERFillMatCompMatrixEleDelBal";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleDelBal.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_DEL_COL_ID];

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_BAL_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixEleDelDel()
{
    char *const test_name = "ADERFillMatCompMatrixEleDelDel";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleDelDel.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_DEL_COL_ID];

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_DEL_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixEleFutBal()
{
    char *const test_name = "ADERFillMatCompMatrixEleFutBal";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleFutBal.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_COL_ID];

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_BAL_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.0000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.9999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}


int Test_ADERFillMatCompMatrixEleFutFut()
{
    char *const test_name = "ADERFillMatCompMatrixEleFutFut";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleFutFut.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_COL_ID];

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_row, mat_ele_col,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixEleIsoFutEle()
{
    char *const test_name = "ADERFillMatCompMatrixEleIsoFutEle";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleIsoFutEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_COL_ID];

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_ISO_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.0000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.9999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixEleIsoFutIso()
{
    char *const test_name = "ADERFillMatCompMatrixEleIsoFutIso";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_row, mat_iso, mat_iso_act;
    long mat_iso_col, mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixEleIsoFutIso.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_ISO_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_col = (long)RDB[mat_iso + ADER_MAT_ISO_FUT_COL_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_iso_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.00000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.99999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixIsoDelBal()
{
    char *const test_name = "ADERFillMatCompMatrixIsoDelBal";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_iso, mat_iso_act, mat_iso_col, mat_iso_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixIsoDelBal.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_col = (long)RDB[mat_iso + ADER_MAT_ISO_DEL_COL_ID];

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_BAL_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_iso_col, mat_iso_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixIsoDelDel()
{
    char *const test_name = "ADERFillMatCompMatrixIsoDelDel";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_iso, mat_iso_act, mat_iso_col, mat_iso_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixIsoDelDel.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_col = (long)RDB[mat_iso + ADER_MAT_ISO_DEL_COL_ID];

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_iso_col, mat_iso_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixIsoFutBal()
{
    char *const test_name = "ADERFillMatCompMatrixIsoFutBal";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_iso, mat_iso_act, mat_iso_col, mat_iso_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixIsoFutBal.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_col = (long)RDB[mat_iso + ADER_MAT_ISO_FUT_COL_ID];

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_BAL_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_iso_col, mat_iso_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.0000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.9999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixIsoFutFut()
{
    char *const test_name = "ADERFillMatCompMatrixIsoFutFut";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_iso, mat_iso_act, mat_iso_col, mat_iso_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixIsoFutFut.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no Li ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_col = (long)RDB[mat_iso + ADER_MAT_ISO_FUT_COL_ID];

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_FUT_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_iso_col, mat_iso_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.9999999 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.0000001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixOxiFutEle()
{
    char *const test_name = "ADERFillMatCompMatrixOxiFutEle";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_ele, mat_ele_col;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data, mat_oxi, mat_oxi_row;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixOxiFutEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no B ele data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    mat_oxi_row = (long)RDB[mat_oxi + ADER_MAT_OXI_ROW_ID];

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 5)
        {

            sprintf(print_data, "FLiBeFuel has B ele data but unknown error.\n");

            mat_ele_col = (long)RDB[mat_ele + ADER_MAT_ELE_FUT_COL_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_ele_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_oxi_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_ele_col, mat_oxi_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 2.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 2.0000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 1.9999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixStreamDelEle()
{
    char *const test_name = "ADERFillMatCompMatrixStreamDelEle";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_stream, mat_stream_col, mat_ele, mat_ele_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixStreamDelEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe stream.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no FLiBe feed stream.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        if(strncmp("FLiBe", GetText(mat_stream + ADER_MAT_STREAM_ID), 5) == 0)
        {

            mat_stream_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            sprintf(print_data, "FLiBeFuel has no Li ele in ader data.\n");

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(mat_ele > VALID_PTR)
    {

        if((long)RDB[mat_ele + ADER_MAT_ELE_Z] == 3)
        {

            mat_ele_row = (long)RDB[mat_ele + ADER_MAT_ELE_DEL_ROW_ID];

            break;

        }

        mat_ele = NextItem(mat_ele);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_ele_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_stream_col, mat_ele_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 0.374608);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 0.3746082 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.3746080)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixStreamDelIso()
{
    char *const test_name = "ADERFillMatCompMatrixStreamDelIso";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_stream, mat_stream_col, mat_iso, mat_iso_act;
    long mat_iso_row, mat_matrix_col, mat_matrix_col_row, mat_matrix_data, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixStreamDelIso.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe stream.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no FLiBe feed stream.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        if(strncmp("FLiBe", GetText(mat_stream + ADER_MAT_STREAM_ID), 5) == 0)
        {

            mat_stream_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            sprintf(print_data, "FLiBeFuel has no Li-6 iso in ader data.\n");

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_iso_act = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso_act + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            mat_iso_row = (long)RDB[mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_iso_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_stream_col, mat_iso_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 0.0003746);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 0.0003747 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.0003745)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixStreamSumGrp()
{
    char *const test_name = "ADERFillMatCompMatrixStreamSumGrp";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_stream, mat_stream_sum_row;
    long mat_matrix_col, mat_matrix_col_row, mat_matrix_data;
    long mat_sum_stream, mat_sum_stream_col, mat_sum_stream_grp;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixStreamSumGrp.\n");

    /*Clear the print_data */
    sprintf(print_data, "FLiBeFuel has no FLiBe composition group.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no ActF cmp group.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        if(strncmp("ActF", GetText(mat_stream + ADER_MAT_STREAM_ID), 4) == 0)
        {

            mat_stream_sum_row = (long)RDB[mat_stream + ADER_MAT_STREAM_SUM_GRPS_ROW_ID];

            sprintf(print_data, "FLiBeFuel stream ActF has no Uranium sum stream.\n");

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_sum_stream = (long)RDB[mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    while(mat_sum_stream > VALID_PTR)
    {

        if(strncmp("Uranium", GetText(mat_sum_stream + ADER_GRP_SUM_GRP_ID), 7) == 0)
        {

            mat_sum_stream_grp = (long)RDB[mat_sum_stream + ADER_GRP_SUM_GRP_PTR];

            mat_sum_stream_col = (long)RDB[mat_sum_stream_grp + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_sum_stream = NextItem(mat_sum_stream);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_sum_stream_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < mat_stream_sum_row; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", mat_sum_stream_col, mat_stream_sum_row,
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], -1.0);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.000001 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixSumStreamDelEle()
{
    char *const test_name = "ADERFillMatCompMatrixSumStreamDelEle";
    char status[5];
    char print_data[256];
    char *mat_name;
    double adens_corr_factor, argon40_adens, flibefuel_adens, percent_diff;
    double test_value;
    int append = 0;
    int boolean = 0;
    int i;
    long ader_mat_ele, ader_mat_ele_row, ader_mat_matrix_data;
    long ader_mat_matrix_col, ader_mat_matrix_col_row;
    long ader_mat_stream, ader_mat_stream_col_id, ader_mat_sum_stream;
    long ader_mat_sum_stream_ent, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixSumStreamDelEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Save Argon40s adens                                                    */
    argon40_adens = RDB[mat + MATERIAL_ADENS];

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material Argon40 has feed streams but no ActF stream.\n");

        if(strcmp("ActF", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

            sprintf(print_data, "Material Argon40 has feed stream ActF but no sum streams.\n");

            ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_sum_stream_ent > VALID_PTR)
            {

                sprintf(print_data, "Material Argon40 feed stream ActF has sum streams but no Uranium sum stream.\n");

                if(strcmp("Uranium", GetText(ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                    sprintf(print_data, "Material Argon40 has no ader_mat_elements. \n");

                    ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    ader_mat_stream_col_id = (long)RDB[ader_mat_sum_stream + ADER_MAT_STREAM_COL_ID];

                	break;

                }

            	ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);
            }

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ader_mat_ele > VALID_PTR)
    {

    	sprintf(print_data, "Material Argon40 has elements but no U. \n");

        if((long)RDB[ader_mat_ele + ADER_MAT_ELE_Z] == 92)
        {

        	sprintf(print_data, "Material Argon40 has U but material FLiBeFuel does not exist. \n");

            ader_mat_ele_row = (long)RDB[ader_mat_ele + ADER_MAT_ELE_DEL_ROW_ID];

            break;

        }

        ader_mat_ele = NextItem(ader_mat_ele);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no matrix data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get FLiBeFuel's adens and get the adens corr factor                    */

    flibefuel_adens = RDB[mat + MATERIAL_ADENS];

    /* The 2 is for the volume correction factor                              */

    adens_corr_factor = (flibefuel_adens / argon40_adens) * 2.0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < ader_mat_stream_col_id; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_ele_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    test_value = RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    percent_diff = (test_value - adens_corr_factor) / adens_corr_factor;

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value %f.\n", ader_mat_stream_col_id, ader_mat_ele_row,
            test_value, adens_corr_factor);

    if(fabs(percent_diff) < 0.00001)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERFillMatCompMatrixSumStreamDelIso()
{
    char *const test_name = "ADERFillMatCompMatrixSumStreamDelIso";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long ader_mat_iso, ader_mat_iso_row, ader_mat_matrix_data;
    long ader_mat_matrix_col, ader_mat_matrix_col_row;
    long ader_mat_stream, ader_mat_stream_col_id, ader_mat_sum_stream;
    long ader_mat_sum_stream_ent, mat, mat_ader_data, mat_iso, nuc;

    fprintf(outp, "Begin: Test_ADERFillMatCompMatrixSumStreamDelIso.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel has feed streams but no ActF stream.\n");

        if(strcmp("ActF", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
        {

        	if(strcmp("NULL", GetText(ader_mat_stream + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		ader_mat_stream = NextItem(ader_mat_stream);

        		continue;

        	}

            sprintf(print_data, "Material FLiBeFuel has feed stream ActF but no sum streams.\n");

            ader_mat_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(ader_mat_sum_stream_ent > VALID_PTR)
            {

                sprintf(print_data, "Material FLiBeFuel feed stream ActF has sum streams but no Uranium sum stream.\n");

                if(strcmp("Uranium", GetText(ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_ID)) == 0)
                {

                    sprintf(print_data, "Material FLiBeFuel has no ader_mat_isos. \n");

                    ader_mat_sum_stream = (long)RDB[ader_mat_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    ader_mat_stream_col_id = (long)RDB[ader_mat_sum_stream + ADER_MAT_STREAM_COL_ID];

                	break;

                }

            	ader_mat_sum_stream_ent = NextItem(ader_mat_sum_stream_ent);
            }

        	break;

        }

        ader_mat_stream = NextItem(ader_mat_stream);

    }

    ader_mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	sprintf(print_data, "Material FLiBeFuel has isotopes but no U-233. \n");

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
        {

        	sprintf(print_data, "Material FLiBeFuel has U-233 but no matrix data. \n");

            ader_mat_iso_row = (long)RDB[ader_mat_iso + ADER_MAT_ISO_DEL_ROW_ID];

            break;

        }

        ader_mat_iso = NextItem(ader_mat_iso);

    }

    ader_mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    ader_mat_matrix_col = (long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < ader_mat_stream_col_id; i++)
    {

        ader_mat_matrix_col = NextItem(ader_mat_matrix_col);

    }

    ader_mat_matrix_col_row = (long)RDB[ader_mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < ader_mat_iso_row; i++)
    {

        ader_mat_matrix_col_row = NextItem(ader_mat_matrix_col_row);

    }

    sprintf(print_data, "FLiBeFuel matrix element, (%ld, %ld), has value %f but \n\
needs value 1.\n", ader_mat_iso_row, ader_mat_stream_col_id,
            RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

    if(RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > -1.000001 &&
       RDB[ader_mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < -0.999999)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERGetMatEleIsoFrac()
{
    char *const test_name = "ADERGetMatEleIsoFrac";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_iso, ele_z, mat, mat_ader_data, mat_iso, iso, nuc;

    fprintf(outp, "Begin: Test_ADERGetMatEleIsoFrac.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ADERGetMatEleIsoFrac(mat);

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element Li not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 3)
        {


            ele_iso = (long)RDB[ele + ADER_MAT_ELE_ISOS_PTR];

            sprintf(print_data, "Element Li found but has no isotopes.\n");

            while(ele_iso > VALID_PTR)
            {

                sprintf(print_data, "Element Li found but has no Li-6.\n");

                mat_iso = (long)RDB[ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

                iso = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

                nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

                if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
                {

                    sprintf(print_data, "Li-6 found but has bad fraction of %f and needs fraction of %f.\n",
                            RDB[ele_iso + ADER_MAT_ELE_ISO_FRAC], 0.001);

                    if((RDB[ele_iso + ADER_MAT_ELE_ISO_FRAC] < 0.00101) &&
                       (RDB[ele_iso + ADER_MAT_ELE_ISO_FRAC] > 0.00099))
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                ele_iso = NextItem(ele_iso);

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderGrpCmpFrac()
{
    char *const test_name = "ADERProcessAderGrpCmpFrac";
    char *grp_name;
    char status[5], print_data[256];
    double comp_frac;
    int append = 0;
    int boolean = 0;
    long ADER_data, comp, comp_Z, grp;

    fprintf(outp, "Begin: Test_ADERProcessAderGrpCmpFrac.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];
    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("FLiBe", grp_name, 5) == 0)
        {
            break;
        }

        grp = NextItem(grp);
    }

    comp = (long)RDB[grp + ADER_GRP_COMP_PTR];

    while(comp > VALID_PTR)
    {
        comp_Z = (long)RDB[comp + ADER_GRP_COMP_Z];

        comp_frac = RDB[comp + ADER_GRP_COMP_FRAC];

        if(comp_Z == 4)
        {

            if(comp_frac < 0.083594567 && comp_frac > 0.083594565)
            {

               boolean = 1;

               break;

            }

        }

        comp = NextItem(comp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderGrpIsoFrac()
{
    char *const test_name = "ADERProcessAderGrpIsoFrac";
    char *grp_name;
    char status[5], print_data[256];
    double iso_frac;
    int append = 0;
    int boolean = 0;
    long ADER_data, comp, comp_Z, grp, iso, iso_ZAI;

    fprintf(outp, "Begin: Test_ADERProcessAderGrpIsoFrac.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];
    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("FLiBe", grp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBe group found but has no comp pointer.\n");

            break;

        }

        grp = NextItem(grp);
    }

    comp = (long)RDB[grp + ADER_GRP_COMP_PTR];

    while(comp > VALID_PTR)
    {
        comp_Z = (long)RDB[comp + ADER_GRP_COMP_Z];

        sprintf(print_data, "FLiBe group has comp but no Lithium.\n");

        if(comp_Z == 3)
        {

            sprintf(print_data, "FLiBe group has Lithium but no isos.\n");

            iso = (long)RDB[comp + ADER_GRP_COMP_ISOS_PTR];

            while(iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBe group has Lithium isos but no Li-7.\n");

                iso_ZAI = (long)RDB[iso + ADER_GRP_ISO_ZAI];

                iso_frac = RDB[iso + ADER_GRP_ISO_FRAC];

                if(iso_ZAI == 30070)
                {

                    sprintf(print_data, "FLiBe group has Li-7 but bad frac.\n");

                    if(iso_frac < 0.9990001 && iso_frac > 0.9989999)
                    {

                       boolean = 1;

                       memset(print_data, 0, strlen(print_data));

                       break;

                    }

                }

                iso = NextItem(iso);

            }

            break;

        }

        comp = NextItem(comp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatClusterMems()
{
    char *const test_name = "ADERProcessAderMatClusterMems";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_cluster_ent, mat_cluster_ent_ptr, mat_ader_data;
    long FLiBeFuel_ptr = 0, booleanFLiBeFuel = 0;
    long Fluorine_ptr = 0, booleanFluorine = 0;
    long Uranium_ptr = 0, booleanUranium = 0;

    fprintf(outp, "Begin: Test_ADERProcessAderMatClusterMems.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the pointers of the necessary materials*/

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            FLiBeFuel_ptr = mat;

        }
        else if(strncmp("Fluorine0", mat_name, 9) == 0)
        {

            Fluorine_ptr = mat;

        }
        else if(strncmp("Uranium233", mat_name, 10) == 0)
        {

            Uranium_ptr = mat;

        }

        if((FLiBeFuel_ptr > 0) && (Fluorine_ptr > 0) && (Uranium_ptr > 0))
        {

            sprintf(print_data, "Target material indicies found.\n");

            break;

        }

        mat = NextItem(mat);
    }

    /* We are going to check the pointers inside of Fluorine0, so set it to mat*/

    mat = Fluorine_ptr;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cluster_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    sprintf(print_data, "Material Fluorine0 has no cluster members.\n");

    while(mat_cluster_ent > VALID_PTR)
    {

        mat_cluster_ent_ptr = (long)RDB[mat_cluster_ent + ADER_MAT_CLUSTER_MEM_PTR];

        if(mat_cluster_ent_ptr == FLiBeFuel_ptr)
        {

            booleanFLiBeFuel = 1;

        }
        else if(mat_cluster_ent_ptr == Fluorine_ptr)
        {

            booleanFluorine = 1;

        }
        else if(mat_cluster_ent_ptr == Uranium_ptr)
        {

            booleanUranium = 1;
        }

        if((booleanFLiBeFuel == 1) && (booleanFluorine == 1) && (booleanUranium == 1))
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        mat_cluster_ent = NextItem(mat_cluster_ent);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatClusterParent()
{
    char *const test_name = "ADERProcessAderMatClusterParent";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_cluster_parent, mat_cluster_parent_ptr, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessAderMatClusterParent.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the pointers of the parent materials*/

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            mat_cluster_parent = mat;

            break;

        }

        mat = NextItem(mat);

    }


    /* Get the pointers of the target materials*/

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine0", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    sprintf(print_data, "Material Fluorine0 has bad parent pointer.\n");

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cluster_parent_ptr = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    if(mat_cluster_parent == mat_cluster_parent_ptr)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpEleFrac()
{
    char *const test_name = "ADERProcessAderMatCmpEleFrac";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    double mat_cmp_ele_frac;
    int append = 0;
    int boolean = 0;
    long cmp, ele, ele_Z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessAderMatEleFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but no elements.\n");

            ele = (long)RDB[cmp + ADER_MAT_CMP_ELES_PTR];

            while(ele > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has elements but no F.\n");

                ele_Z = (long)RDB[ele + ADER_MAT_GRP_ELE_Z];

                mat_cmp_ele_frac = RDB[ele +ADER_MAT_GRP_ELE_FRAC];

                if(ele_Z == 9)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe group has F but bad frac.\n");

                    if(mat_cmp_ele_frac < 0.541798 && mat_cmp_ele_frac > 0.541796)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }
                    break;
                }

                ele = NextItem(ele);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpGrpPtr()
{
    char *const test_name = "ADERProcessAderMatCmpGrpPtr";
    char *cmp_name, *grp_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cmp, cmp_grp_ptr, grp, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpGrpPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but no group ID.\n");

            cmp_grp_ptr = (long)RDB[cmp + ADER_MAT_CMP_GRP_PTR];

            /* Get actual instance of group that sum_grp_ptr should point to */
            grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

            while(grp > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel has FLiBe group and ID but broken link.\n");

                grp_name = GetText(grp + ADER_GRP_ID);

                if(strncmp("FLiBe", grp_name, 5) == 0)
                {
                    break;
                }

                grp = NextItem(grp);
            }

            if(grp == cmp_grp_ptr)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpIsoEleFrac()
{
    char *const test_name = "ADERProcessAderMatCmpIsoEleFrac";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    double mat_cmp_iso_frac;
    int append = 0;
    int boolean = 0;
    long cmp, iso, iso_ZAI, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessAderMatIsoEleFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but no isotopes.\n");

            iso = (long)RDB[cmp + ADER_MAT_CMP_ISOS_PTR];

            while(iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has isotopes but no Li-7.\n");

                iso_ZAI = (long)RDB[iso + ADER_MAT_GRP_ISO_ZAI];

                mat_cmp_iso_frac = RDB[iso +ADER_MAT_GRP_ISO_ELE_FRAC];

                if(iso_ZAI == 30070)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe group has Li-7 but bad frac.\n");

                    if(mat_cmp_iso_frac < 0.999001 && mat_cmp_iso_frac > 0.998999)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }
                    break;
                }

                iso = NextItem(iso);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpIsoFrac()
{
    char *const test_name = "ADERProcessAderMatCmpIsoFrac";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    double mat_cmp_iso_frac;
    int append = 0;
    int boolean = 0;
    long cmp, iso, iso_ZAI, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessAderMatIsoFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but no isotopes.\n");

            iso = (long)RDB[cmp + ADER_MAT_CMP_ISOS_PTR];

            while(iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has isotopes but no Li-6.\n");

                iso_ZAI = (long)RDB[iso + ADER_MAT_GRP_ISO_ZAI];

                mat_cmp_iso_frac = RDB[iso + ADER_MAT_GRP_ISO_FRAC];

                if(iso_ZAI == 30060)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe group has Li-6 but bad frac, %f, needs frac %f.\n",
                            mat_cmp_iso_frac, 0.0003746);

                    if(mat_cmp_iso_frac < 0.0003747 && mat_cmp_iso_frac > 0.0003745)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }
                    break;
                }

                iso = NextItem(iso);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpRngMax()
{
    char *const test_name = "ADERProcessAderMatCmpRngMax";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    double mat_rng_max;
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, rng;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpRngMax.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but bad rng max.\n");

            rng = (long)RDB[cmp + ADER_MAT_CMP_RNG_PTR];

            mat_rng_max = RDB[rng + ADER_MAT_CMP_RNG_MAX];

            if(mat_rng_max < 1.000001 && mat_rng_max > 0.9999999 )
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpRngMin()
{
    char *const test_name = "ADERProcessAderMatCmpRngMin";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    double mat_rng_min;
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, rng;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpRngMin.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but bad rng min.\n");

            rng = (long)RDB[cmp + ADER_MAT_CMP_RNG_PTR];

            mat_rng_min = RDB[rng + ADER_MAT_CMP_RNG_MIN];

            if(mat_rng_min < 0.200001 && mat_rng_min > 0.1999999 )
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpRto2GrpPtr()
{
    char *const test_name = "ADERProcessAderMatCmpRto2GrpPtr";
    char *cmp_name, *sec_cmp_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, rto, sec_cmp, sec_cmp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpRto2GrpPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

    sec_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(sec_cmp > VALID_PTR)
    {

        sec_cmp_name = GetText(sec_cmp + ADER_MAT_CMP_ID);

        if(strncmp("ThF4", sec_cmp_name, 4) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ThF4 cmp but no FLiBe cmp.\n");

            break;

        }

        sec_cmp = NextItem(sec_cmp);

    }

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            rto = (long)RDB[cmp + ADER_MAT_CMP_RTOS_PTR];

            sprintf(print_data, "FLiBeFuel has FLiBe cmp but no rtos.\n");

            while(rto > VALID_PTR)
            {

                sprintf(print_data, "ThF4 index not found in FLiBe cmp rtos 2nd grp ptrs in FLiBeFuel.\n");

                sec_cmp_ptr = (long)RDB[rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

                if(sec_cmp == sec_cmp_ptr)
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                    break;

                }

                rto = NextItem(rto);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpRtoMax()
{
    char *const test_name = "ADERProcessAderMatCmpRtoMax";
    char *cmp_name, *sec_cmp_name, *mat_name;
    char status[5], print_data[256];
    double rto_max;
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, rto, sec_cmp, sec_cmp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpRtoMax.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

    sec_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(sec_cmp > VALID_PTR)
    {

        sec_cmp_name = GetText(sec_cmp + ADER_MAT_CMP_ID);

        if(strncmp("ThF4", sec_cmp_name, 4) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ThF4 cmp but no FLiBe cmp.\n");

            break;

        }

        sec_cmp = NextItem(sec_cmp);

    }

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            rto = (long)RDB[cmp + ADER_MAT_CMP_RTOS_PTR];

            sprintf(print_data, "FLiBeFuel has FLiBe cmp but no rtos.\n");

            while(rto > VALID_PTR)
            {

                sprintf(print_data, "ThF4 index not found in FLiBe cmp rtos 2nd grp ptrs in FLiBeFuel.\n");

                sec_cmp_ptr = (long)RDB[rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

                rto_max = RDB[rto + ADER_MAT_CMP_RTO_MAX];

                if(sec_cmp == sec_cmp_ptr)
                {

                    sprintf(print_data, "FLiBe cmp has rto pointing to ThF4 but bad max.\n");

                    if(rto_max < 99.000001 && rto_max > 98.999999)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                        break;

                    }

                }

                rto = NextItem(rto);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpRtoMin()
{
    char *const test_name = "ADERProcessAderMatCmpRtoMin";
    char *cmp_name, *sec_cmp_name, *mat_name;
    char status[5], print_data[256];
    double rto_min;
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, rto, sec_cmp, sec_cmp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpRtoMin.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

    sec_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(sec_cmp > VALID_PTR)
    {

        sec_cmp_name = GetText(sec_cmp + ADER_MAT_CMP_ID);

        if(strncmp("ThF4", sec_cmp_name, 4) == 0)
        {

            sprintf(print_data, "FLiBeFuel has ThF4 cmp but no FLiBe cmp.\n");

            break;

        }

        sec_cmp = NextItem(sec_cmp);

    }

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            rto = (long)RDB[cmp + ADER_MAT_CMP_RTOS_PTR];

            sprintf(print_data, "FLiBeFuel has FLiBe cmp but no rtos.\n");

            while(rto > VALID_PTR)
            {

                sprintf(print_data, "ThF4 index not found in FLiBe cmp rtos 2nd grp ptrs in FLiBeFuel.\n");

                sec_cmp_ptr = (long)RDB[rto + ADER_MAT_CMP_RTO_2ND_GRP_PTR];

                rto_min = RDB[rto + ADER_MAT_CMP_RTO_MIN];

                if(sec_cmp == sec_cmp_ptr)
                {

                    sprintf(print_data, "FLiBe cmp has rto pointing to ThF4 but bad min.\n");

                    if(rto_min < 4.000001 && rto_min > 3.999999)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                        break;

                    }

                }

                rto = NextItem(rto);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpSumGrpsPtr()
{
    char *const test_name = "ADERProcessAderMatCmpSumGrpsPtr";
    char *cmp_name, *sum_cmp_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, sum, sum_cmp, sum_cmp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpSumGrpsPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

    sum_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(sum_cmp > VALID_PTR)
    {

        sum_cmp_name = GetText(sum_cmp + ADER_MAT_CMP_ID);

        if(strncmp("Uranium", sum_cmp_name, 7) == 0)
        {

            sprintf(print_data, "FLiBeFuel has Uraniium cmp but no ActF cmp.\n");

            break;

        }

        sum_cmp = NextItem(sum_cmp);

    }

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("ActF", cmp_name, 4) == 0)
        {

            sum = (long)RDB[cmp + ADER_MAT_CMP_SUM_GRPS_PTR];

            sprintf(print_data, "FLiBeFuel has FLiBe cmp but no sum groups.\n");

            while(sum > VALID_PTR)
            {

                sprintf(print_data, "Uranium index not found in ActF cmp sum grps ptrs in FLiBeFuel.\n");

                sum_cmp_ptr = (long)RDB[sum + ADER_MAT_GRP_SUM_GRP_PTR];

                if(sum_cmp == sum_cmp_ptr)
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                    break;

                }

                sum = NextItem(sum);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCmpSumGrpWeight()
{
    char *const test_name = "ADERProcessAderMatCmpSumGrpWeight";
    char *cmp_name, *sum_cmp_name, *mat_name;
    char status[5], print_data[256];
    double sum_cmp_weight;
    int append = 0;
    int boolean = 0;
    long cmp, mat, mat_ader_data, sum, sum_cmp, sum_cmp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCmpSumGrpWeight.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

    sum_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(sum_cmp > VALID_PTR)
    {

        sum_cmp_name = GetText(sum_cmp + ADER_MAT_CMP_ID);

        if(strncmp("Uranium", sum_cmp_name, 7) == 0)
        {

            sprintf(print_data, "FLiBeFuel has Uranium cmp but no ActF cmp.\n");

            break;

        }

        sum_cmp = NextItem(sum_cmp);

    }

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("ActF", cmp_name, 4) == 0)
        {

            sum = (long)RDB[cmp + ADER_MAT_CMP_SUM_GRPS_PTR];

            sprintf(print_data, "FLiBeFuel has FLiBe cmp but no sum groups.\n");

            while(sum > VALID_PTR)
            {

                sprintf(print_data, "Uranium index not found in ActF cmp sum grps ptrs in FLiBeFuel.\n");

                sum_cmp_ptr = (long)RDB[sum + ADER_MAT_GRP_SUM_GRP_PTR];

                sum_cmp_weight = RDB[sum + ADER_MAT_GRP_SUM_GRP_WEIGHT];

                if(sum_cmp == sum_cmp_ptr)
                {

                    sprintf(print_data, "Uranium sum group in ActF FLiBeFuel cmp group has bad weight.\n");

                    if(sum_cmp_weight < 1.000001 && sum_cmp_weight > 0.9999999)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;

                }

                sum = NextItem(sum);
            }

            break;
        }

        cmp = NextItem(cmp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCndPtr()
{
    char *const test_name = "ADERProcessAderMatCndPtr";
    char *cnd_id, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data, cnd, cnd_ptr, mat, mat_ader_data, mat_cnd;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCndPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "cnd table FLiBeFuel not found. \n");

    ader_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ader_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {

        cnd_id = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_id, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel not found.\n");

            break;

        }

        cnd = NextItem(cnd);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no cnd entries.\n");

            break;

        }

        mat = NextItem(mat);
    }


    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cnd = (long)RDB[mat_ader_data + ADER_MAT_CNDS_PTR];

    while(mat_cnd > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel cnd group 'FLiBeFuel not found.\n");

        cnd_ptr = (long)RDB[mat_cnd + ADER_MAT_CND_PTR];

        cnd_id = GetText(mat_cnd + ADER_MAT_CND_ID);

        if(strncmp("FLiBeFuel", cnd_id, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has cnd FLiBeFuel but bad pointer");

            if(cnd_ptr == cnd)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        mat_cnd = NextItem(mat_cnd);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatCntTblPtr()
{
    char *const test_name = "ADERProcessAderMatCntTblPtr";
    char *cnt_id, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long cnt_ptr, mat, mat_ader_data, mat_cnt;

    fprintf(outp, "Begin: Test_ADERProcessAderMatCntTblPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no CNT tables.\n");

            break;

        }

        mat = NextItem(mat);
    }


    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cnt = (long)RDB[mat_ader_data + ADER_MAT_CNT_TBLS_PTR];

    while(mat_cnt > VALID_PTR)
    {

        sprintf(print_data, "Material FLiBeFuel cnt tables do not have table named '001'.\n");

        cnt_ptr = (long)RDB[mat_cnt + ADER_MAT_CNT_TBL_PTR];

        cnt_id = GetText(cnt_ptr + ADER_CONTROL_TBL_ID);

        if(strncmp("001", cnt_id, 3) == 0)
        {

            memset(print_data, 0, strlen(print_data));

            boolean = 1;

            break;

        }

        mat_cnt = NextItem(mat_cnt);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatIsoPtr()
{
    char *const test_name = "ADERProcessAderMatIsoPtr";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long iso, iso_ptr, mat, mat_ader_data, mat_iso, nuc, zai;

    fprintf(outp, "Begin: Test_ADERProcessAderMatIsoPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no Li-7 isotope.\n");

            break;

        }

        mat = NextItem(mat);
    }

    iso = (long)RDB[mat + MATERIAL_PTR_COMP];

    while(iso > VALID_PTR)
    {

        nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

        zai = (long)RDB[nuc + NUCLIDE_ZAI];

        if(zai == 30070)
        {

            sprintf(print_data, "Material FLiBeFuel has no MAT_ISO_PTR for Li-7.\n");

            break;

        }

        iso = NextItem(iso);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        iso_ptr = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        if(iso_ptr == iso)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOptDir()
{
    char *const test_name = "ADERProcessAderMatOptDir";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_opt, mat_opt_dir;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOptDir.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Lithium7 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    mat_opt_dir = (long)RDB[mat_opt + ADER_MAT_OPT_DIR];

    sprintf(print_data, "Material Lithium7 has bad opt dir of %ld.\n",
            mat_opt_dir);

    if(mat_opt_dir < 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOptType()
{
    char *const test_name = "ADERProcessAderMatOptType";
    char *mat_name, *mat_opt_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_opt;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOptType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Lithium7 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    mat_opt_type = GetText(mat_opt + ADER_MAT_OPT_TYPE);

    sprintf(print_data, "Material Lithium7 has bad opt type of %s.\n",
            mat_opt_type);

    if(strncmp("action", mat_opt_type, 6) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOptTypeTarget()
{
    char *const test_name = "ADERProcessAderMatOptTypeTarget";
    char *mat_name, *mat_opt_target;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_opt;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOptTypeTarget.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Lithium7 not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Lithium7", mat_name, 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    mat_opt_target = GetText(mat_opt + ADER_MAT_OPT_TYPE_TARGET);

    sprintf(print_data, "Material Lithium7 has bad opt type of %s.\n",
            mat_opt_target);

    if(strncmp("feed", mat_opt_target, 4) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOxiMax()
{
    char *const test_name = "ADERProcessAderMatOxiMax";
    char *mat_name;
    char status[5], print_data[256];
    double oxi_max;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_oxi;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOxiMax.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    oxi_max = RDB[mat_oxi + ADER_MAT_OXI_MAX];

    sprintf(print_data, "Material FLiBeFuel has bad oxi max of %f.\n",
            oxi_max);

    if((oxi_max < 0.001000001) && (oxi_max > 0.0009999999))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOxiMin()
{
    char *const test_name = "ADERProcessAderMatOxiMin";
    char *mat_name;
    char status[5], print_data[256];
    double oxi_min;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_oxi;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOxiMin.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    oxi_min = (long)RDB[mat_oxi + ADER_MAT_OXI_MIN];

    sprintf(print_data, "Material FLiBeFuel has bad oxi max of %f.\n",
            oxi_min);

    if((oxi_min < 0.000000001) && (oxi_min > -0.000000001))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatOxiTblPtr()
{
    char *const test_name = "ADERProcessAderMatOxiTblPtr";
    char *ader_oxi_id, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data, ader_oxi, mat, mat_ader_data, mat_oxi, mat_oxi_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatOxiTblPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_oxi = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    mat_oxi_ptr = (long)RDB[mat_oxi + ADER_MAT_OXI_TBL_PTR];

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_oxi = (long)RDB[ader_data + ADER_OXIS_PTR];

    sprintf(print_data, "ADER oxidation table '002' not found. \n");

    while(ader_oxi > VALID_PTR)
    {

        ader_oxi_id = GetText(ader_oxi + ADER_OXI_TBL_ID);

        if(strncmp("002", ader_oxi_id, 3) == 0)
        {

            sprintf(print_data, "Material oxidation ptr does not match ADER oxidation table '002' index. \n");

            if(ader_oxi == mat_oxi_ptr)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        ader_oxi = NextItem(ader_oxi);
    }
    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatPreserveType()
{
    char *const test_name = "ADERProcessAderMatPreserveType";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_preserve_ent;

    fprintf(outp, "Begin: Test_ADERProcessAderMatPreserveType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_preserve_ent = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

    sprintf(print_data, "Material FLiBeFuel has no preserve entries. \n");

    while(mat_preserve_ent > VALID_PTR)
    {

        if(strncmp("mols", GetText(mat_preserve_ent + ADER_MAT_PRESERVE_ENT), 4) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        mat_preserve_ent = NextItem(mat_preserve_ent);

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmDest()
{
    char *const test_name = "ADERProcessAderMatStrmDest";
    char *mat_name, *strm_dest, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmDest.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe stream but bad destination.\n");

            strm_dest = GetText(strm + ADER_MAT_STREAM_DEST);

            if(strncmp("FLiBeFuel", strm_dest, 9) == 0)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmEleFix()
{
    char *const test_name = "ADERProcessAderMatStrmEleFix";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_ele;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmEleFix.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Beryllium redox group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("Beryllium", strm_id, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has Beryllium stream but no elements.\n");

            strm_ele = (long)RDB[strm + ADER_MAT_STREAM_ELES_PTR];

            while(strm_ele > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel has Beryllium stream but no Be element.\n");

                if((long)RDB[strm_ele + ADER_MAT_GRP_ELE_Z] == 4)
                {

                    sprintf(print_data, "FLiBeFuel has Beryllium stream but the Be element has bad fix value.\n");

                    if((long)RDB[strm_ele + ADER_MAT_GRP_ELE_ISO_FIXED] > 0)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_ele = NextItem(strm_ele);

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmEleFrac()
{
    char *const test_name = "ADERProcessAderMatStrmEleFrac";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double mat_strm_ele_frac;
    int append = 0;
    int boolean = 0;
    long ele, ele_Z, mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmEleFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe stream group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if((strncmp("FLiBe", strm_id, 5) == 0))
        {

            sprintf(print_data, "FLiBeFuel has FLiBe feed stream but no elements.\n");

            ele = (long)RDB[strm + ADER_MAT_STREAM_ELES_PTR];

            while(ele > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe stream has elements but no F.\n");

                ele_Z = (long)RDB[ele + ADER_MAT_GRP_ELE_Z];

                mat_strm_ele_frac = RDB[ele + ADER_MAT_GRP_ELE_FRAC];

                if(ele_Z == 9)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe stream has F but bad frac.\n");

                    if(mat_strm_ele_frac < 0.541798 && mat_strm_ele_frac > 0.541796)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;
                }

                ele = NextItem(ele);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmFeedType()
{
    char *const test_name = "ADERProcessAderMatStrmFeedType";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmFeedType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmForm()
{
    char *const test_name = "ADERProcessAderMatStrmForm";
    char *mat_name, *strm_form, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmForm.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            strm_form = GetText(strm + ADER_MAT_STREAM_FORM);

            if(strncmp("disc", strm_form, 4) == 0)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

                break;

            }

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmIsoEleFrac()
{
    char *const test_name = "ADERProcessAderMatStrmIsoEleFrac";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double mat_strm_iso_frac;
    int append = 0;
    int boolean = 0;
    long iso, iso_ZAI, mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderStrmIsoEleFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no stream grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe stream group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if((strncmp("FLiBe", strm_id, 5) == 0))
        {

            sprintf(print_data, "FLiBeFuel has FLiBe removal stream but no isotopes.\n");

            iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe removal stream has isotopes but no Li-7.\n");

                iso_ZAI = (long)RDB[iso + ADER_MAT_GRP_ISO_ZAI];

                mat_strm_iso_frac = RDB[iso +ADER_MAT_GRP_ISO_ELE_FRAC];

                if(iso_ZAI == 30070)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe removal stream has Li-7 but bad frac.\n");

                    if(mat_strm_iso_frac < 0.999001 && mat_strm_iso_frac > 0.998999)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;
                }

                iso = NextItem(iso);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmIsoFrac()
{
    char *const test_name = "ADERProcessAderMatStrmIsoFrac";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double mat_strm_iso_frac;
    int append = 0;
    int boolean = 0;
    long iso, iso_ZAI, mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderStrmIsoFrac.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no stream grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe stream group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if((strncmp("FLiBe", strm_id, 5) == 0))
        {

            sprintf(print_data, "FLiBeFuel has FLiBe removal stream but no isotopes.\n");

            iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe removal stream has isotopes but no Li-6.\n");

                iso_ZAI = (long)RDB[iso + ADER_MAT_GRP_ISO_ZAI];

                mat_strm_iso_frac = RDB[iso + ADER_MAT_GRP_ISO_FRAC];

                if(iso_ZAI == 30060)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe removal stream has Li-6 but bad frac %f, needs frac %f.\n",
                            mat_strm_iso_frac, 0.0003746);

                    if(mat_strm_iso_frac < 0.0003747 && mat_strm_iso_frac > 0.0003745)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;
                }

                iso = NextItem(iso);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmMatPtr()
{
    char *const test_name = "ADERProcessAderMatStrmMatPtr";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmMatPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the target group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            strm_ptr = (long)RDB[strm + ADER_MAT_STREAM_MAT_PTR];

            sprintf(print_data, "FLiBeFuel stream has bad pointer to FLiBeFuel.\n");

            if(strm_ptr == mat)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmPtr()
{
    char *const test_name = "ADERProcessAderMatStrmPtr";
    char *ader_strm_dest, *ader_strm_grp, *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ader_strm, mat, mat_ader_data, strm, strm_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the target group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    ader_strm = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    while(ader_strm > VALID_PTR)
    {

        ader_strm_grp = GetText(ader_strm + ADER_STREAM_GRP_ID);

        ader_strm_dest = GetText(ader_strm + ADER_STREAM_DEST);

        if((strncmp("FLiBe", ader_strm_grp, 5) == 0) &&
           (strncmp("FLiBeFuel", ader_strm_dest, 9) == 0))
        {

            break;

        }

        ader_strm = NextItem(ader_strm);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            strm_ptr = (long)RDB[strm + ADER_MAT_STREAM_PTR];

            sprintf(print_data, "FLiBeFuel stream has bad pointer to group.\n");

            if(strm_ptr == ader_strm)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmRedoxType()
{
    char *const test_name = "ADERProcessAderMatStrmRedoxType";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmRedoxType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Lithium feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("Lithium", strm_id, 7) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmRemvGroup()
{
    char *const test_name = "ADERProcessAderMatStrmRemvGroup";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmRemvGroup.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no reproc stream.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmRemvType()
{
    char *const test_name = "ADERProcessAderMatStrmRemvType";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmRemvType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe removal group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmReacType()
{
    char *const test_name = "ADERProcessAderMatStrmReacType";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmReacType.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Thorium reactivity group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("Thorium", strm_id, 7) == 0)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmShadowPtr()
{
    char *const test_name = "ADERProcessAderMatStrmShadowPtr";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, shadow_ptr, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmShadowPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "Argon40 has no reproc stream.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            shadow_ptr = (long)RDB[strm + ADER_MAT_STREAM_SHADOW_PTR];

            break;

        }

        strm = NextItem(strm);

    }

    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no reproc stream.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "Mismatch between Argon40 shadow ptr, %ld, \n \
and FLiBeFuel reproc ptr of %ld.\n", shadow_ptr, strm);

            if(shadow_ptr == strm)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmShadowSumStrmPtr()
{
    char *const test_name = "ADERProcessAderMatStrmShadowSumStrmPtr";
    char *strm_name, *strm_sum_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, shadow_sum_strm_ptr, strm, strm_sum, strm_sum_ent;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmShadowSumStrmPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "ActF removal stream found but has no sum streams.\n");

            strm_sum_ent = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(strm_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "ActF removal stream sum streams found but has no sum stream 'Uranium'.\n");

                strm_sum_name = GetText(strm_sum_ent + ADER_MAT_GRP_SUM_GRP_ID);

                if(strncmp("Uranium", strm_sum_name, 7) == 0)
                {

                    strm_sum = (long)RDB[strm_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    sprintf(print_data, "Argon40 material not found.\n");

                    shadow_sum_strm_ptr = -(long)RDB[strm_sum + ADER_MAT_STREAM_SHADOW_PTR];

                    break;

                }

                strm_sum_ent = NextItem(strm_sum_ent);

            }

            break;

        }

        strm = NextItem(strm);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material Argon40.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "ActF feed stream found but has no sum streams.\n");

            strm_sum_ent = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(strm_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "ActF feed stream sum streams found but has no sum stream 'Uranium'.\n");

                strm_sum_name = GetText(strm_sum_ent + ADER_MAT_GRP_SUM_GRP_ID);

                if(strncmp("Uranium", strm_sum_name, 7) == 0)
                {

                    strm_sum = (long)RDB[strm_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    sprintf(print_data, "Argon40 ActF feed stream sum group 'Uranium' has index %ld \n\
while ActF removal stream sum group Uranium in FLiBeFuel has index %ld.\n",
                            strm_sum, shadow_sum_strm_ptr);

                    if(strm_sum == shadow_sum_strm_ptr)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;

                }

                strm_sum_ent = NextItem(strm_sum_ent);

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmSrc()
{
    char *const test_name = "ADERProcessAderMatStrmSrc";
    char *mat_name, *strm_id, *strm_src;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmSrc.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe stream but bad source.\n");

            strm_src = GetText(strm + ADER_MAT_STREAM_SRC);

            if(strncmp("FLiBeFuel", strm_src, 9) == 0)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmSumGrpsPtr()
{
    char *const test_name = "ADERProcessAderMatStrmSumGrpsPtr";
    char *mat_name, *strm_id, *sum_strm_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, sum, sum_strm_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmSumGrpsPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_id, 4) == 0)
        {

            sum = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            sprintf(print_data, "FLiBeFuel has ActF stream but no sum groups.\n");

            while(sum > VALID_PTR)
            {

                sprintf(print_data, "Uranium stream not found in ActF stream sum grps ptrs in FLiBeFuel.\n");

                sum_strm_ptr = (long)RDB[sum + ADER_MAT_GRP_SUM_GRP_PTR];

                sum_strm_name = GetText(sum_strm_ptr + ADER_MAT_STREAM_ID);

                if(strncmp("Uranium", sum_strm_name, 7) == 0)
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                    break;

                }

                sum = NextItem(sum);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmTypeGroup()
{
    char *const test_name = "Test_ADERProcessAderMatStrmTypeGroup";
    char *mat_name, *strm_grp_type, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmTypeGroup.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_id, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe stream but bad group type.\n");

            strm_grp_type = GetText(strm + ADER_MAT_STREAM_TYPE);

            if(strncmp("group", strm_grp_type, 3) == 0)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderMatStrmTypeRem()
{
    char *const test_name = "Test_ADERProcessAderMatStrmTypeRem";
    char *mat_name, *strm_grp_type, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERProcessAderMatStrmTypeRem.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no reproc removal group.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "FLiBeFuel has reproc stream but bad group type.\n");

            strm_grp_type = GetText(strm + ADER_MAT_STREAM_TYPE);

            if(strcmp("rem", strm_grp_type) == 0)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderReproElement()
{
    char *const test_name = "ADERProcessAderReproElement";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double strm_ele_val;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_ele, strm_ele_z;

    fprintf(outp, "Begin: Test_ADERProcessAderReproElement.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in FLiBeFuel has no elements.\n");

            strm_ele = (long)RDB[strm + ADER_MAT_STREAM_ELES_PTR];

            while(strm_ele > VALID_PTR)
            {

                strm_ele_z = (long)RDB[strm_ele + ADER_MAT_GRP_ELE_Z];

                if(strm_ele_z == 1)
                {

                    sprintf(print_data, "'reproc' stream in FLiBeFuel has H but bad val.\n");

                    strm_ele_val = RDB[strm_ele + ADER_MAT_GRP_ELE_FRAC];

                    if(strm_ele_val <= 0.400001 && strm_ele_val >= 0.3999999)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_ele = NextItem(strm_ele);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderReproIsoEle()
{
    char *const test_name = "ADERProcessAderReproIsoEle";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_ele, strm_ele_z;

    fprintf(outp, "Begin: Test_ADERProcessAderReproIsoEle.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc2", strm_id, 7) == 0)
        {

            sprintf(print_data, "'reproc2' stream in FLiBeFuel has no elements.\n");

            strm_ele = (long)RDB[strm + ADER_MAT_STREAM_ELES_PTR];

            while(strm_ele > VALID_PTR)
            {

                strm_ele_z = (long)RDB[strm_ele + ADER_MAT_GRP_ELE_Z];

                if(strm_ele_z == 94)
                {

					memset(print_data, 0, strlen(print_data));

					boolean = 1;

                }

                strm_ele = NextItem(strm_ele);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderReproIsotope()
{
    char *const test_name = "ADERProcessAderReproIsotope";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double strm_iso_val;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_iso, strm_iso_zai;

    fprintf(outp, "Begin: Test_ADERProcessAderReproIsotope.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in FLiBeFuel has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                strm_iso_zai = (long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI];

                if(strm_iso_zai == 942390)
                {

                    sprintf(print_data, "'reproc' stream in FLiBeFuel has Pu-239 but bad val of %f.\n",
                            RDB[strm_iso + ADER_MAT_GRP_ISO_FRAC]);

                    strm_iso_val = RDB[strm_iso + ADER_MAT_GRP_ISO_FRAC];

                    if(strm_iso_val <= 0.300001 && strm_iso_val >= 0.2999999)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderStreamSourcesAndDests()
{
    char *const test_name = "ADERProcessAderStreamSourcesAndDests";
    char *strm_id, *strm_src;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ader_data, ader_strm;

    fprintf(outp, "Begin: Test_ADERProcessAderStreamSourcesAndDests.\n");

    /*Clear the print_data */
    sprintf(print_data, "Beryllium stream not found. \n");

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_strm = (long)RDB[ader_data + ADER_STREAMS_PTR];

    while(ader_strm > VALID_PTR)
    {

        strm_id = GetText(ader_strm + ADER_STREAM_GRP_ID);

        if(strncmp(strm_id, "Beryllium", 9) == 0)
        {

            sprintf(print_data, "Beryllium stream found but has no null source.\n");

            strm_src = GetText(ader_strm + ADER_STREAM_SRC);

            if(strncmp(strm_src, "NULL", 4) == 0)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;
        }

        ader_strm = NextItem(ader_strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessAderSumGrpPtr()
{
    char *const test_name = "ADERProcessAderSumGrpPtr";
    char *grp_name, *sgrp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, grp, sgrp, sgrp_ptr;

    fprintf(outp, "Begin: Test_ADERProcessAderSumGrpPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("NestedSum", grp_name, 9) == 0)
        {

            break;

        }

        grp = NextItem(grp);
    }

    sgrp = (long)RDB[grp + ADER_GRP_SUM_GRPS_PTR];

    while(sgrp > VALID_PTR)
    {

        sgrp_name = GetText(sgrp + ADER_GRP_SUM_GRP_ID);

        if(strncmp("ActF", sgrp_name, 4) == 0)
        {

            sgrp_ptr = (long)RDB[sgrp + ADER_GRP_SUM_GRP_PTR];

            /* Get actual instance of group that sum_grp_ptr should point to */
            grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

            while(grp > VALID_PTR)
            {
                grp_name = GetText(grp + ADER_GRP_ID);

                if(strncmp("ActF", grp_name, 4) == 0)
                {

                    break;

                }

                grp = NextItem(grp);
            }

            sprintf(print_data, "ADER_SUM_GRP_PTR for ActF element of \
                                 NestedSum points to %ld while ActF \
                                 has grp ptr of %ld.\n", sgrp_ptr, grp);

            if(grp == sgrp_ptr)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;
        }

        sgrp = NextItem(sgrp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatClusterOpt()
{
    char *const test_name = "ADERProcessMatClusterOpt";
    char *mat_name, *mat_opt_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_opt;

    fprintf(outp, "Begin: Test_ADERProcessMatClusterOpt.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no opt entry. \n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    mat_opt_type = GetText(mat_opt + ADER_MAT_OPT_TYPE);

    sprintf(print_data, "Material FLiBeFuel has bad opt type of %s.\n",
            mat_opt_type);

    if(strncmp("spec_stream", mat_opt_type, 11) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatCmpIsoMatAderIsoPtr()
{
    char *const test_name = "ADERProcessMatCmpIsoMatAderIsoPtr";
    char *cmp_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long cmp, cmp_iso, cmp_iso_mat_ader_iso_ptr, mat, mat_ader_data, mat_iso;
    long iso, iso_ZAI, nuc;

    fprintf(outp, "Begin: Test_ADERProcessMatCmpIsoMatAderIsoPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no composition grps.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe cmp group.\n");

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe group but no isotopes.\n");

            cmp_iso = (long)RDB[cmp + ADER_MAT_CMP_ISOS_PTR];

            while(cmp_iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has isotopes but no Li-6.\n");

                iso_ZAI = (long)RDB[cmp_iso + ADER_MAT_GRP_ISO_ZAI];

                cmp_iso_mat_ader_iso_ptr = RDB[cmp_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

                if(iso_ZAI == 30060)
                {

                    sprintf(print_data, "FLiBeFuel has no mat ader isos.\n");

                    break;

                }

                cmp_iso = NextItem(cmp_iso);
            }

            break;
        }

        cmp = NextItem(cmp);

    }

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has mat ader isos but no Li-6 iso.\n");

        iso = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            sprintf(print_data, "FLiBeFuel has mat ader isos Li-6 but index, %ld, does not match\n \
cmp iso ptr of %ld.\n", mat_iso, cmp_iso_mat_ader_iso_ptr);

            if(mat_iso == cmp_iso_mat_ader_iso_ptr)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatReproEleIsoRate()
{
    char *const test_name = "ADERProcessMatReproEleIsoRate";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double strm_iso_val;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_iso, strm_iso_zai;

    fprintf(outp, "Begin: Test_ADERProcessMatReproEleIsoRate.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in FLiBeFuel has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                sprintf(print_data, "'reproc' stream in FLiBeFuel has no U-235.\n");

                strm_iso_zai = (long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI];

                if(strm_iso_zai == 922350)
                {

                    strm_iso_val = RDB[strm_iso + ADER_MAT_GRP_ISO_ELE_FRAC];

                    sprintf(print_data, "'reproc' stream in FLiBeFuel has U-235 but\n \
bad iso frac of %f and needs iso_frac of 0.0 .\n", strm_iso_val);

                    if(strm_iso_val < 0.000001 && strm_iso_val > -0.000001)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatReproIsoRate()
{
    char *const test_name = "ADERProcessMatReproIsoRate";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    double strm_iso_val;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_iso, strm_iso_zai;

    fprintf(outp, "Begin: Test_ADERProcessMatReproIsoRate.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "'reproc' stream in FLiBeFuel has no isotopes.\n");

            strm_iso = (long)RDB[strm + ADER_MAT_STREAM_ISOS_PTR];

            while(strm_iso > VALID_PTR)
            {

                sprintf(print_data, "'reproc' stream in FLiBeFuel has no U-233.\n");

                strm_iso_zai = (long)RDB[strm_iso + ADER_MAT_GRP_ISO_ZAI];

                if(strm_iso_zai == 922330)
                {

                    strm_iso_val = RDB[strm_iso + ADER_MAT_GRP_ISO_FRAC];

                    sprintf(print_data, "'reproc' stream in FLiBeFuel has U-233 but\n \
bad iso frac of %f and needs iso_frac of 0.4 .\n", strm_iso_val);

                    if(strm_iso_val <= 0.400001 && strm_iso_val >= 0.3999999)
                    {

                        memset(print_data, 0, strlen(print_data));

                        boolean = 1;

                    }

                    break;

                }

                strm_iso = NextItem(strm_iso);
            }

            break;
        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatStreamIsoMatAderIsoPtr()
{
    char *const test_name = "ADERProcessMatStreamIsoMatAderIsoPtr";
    char *stream_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long stream, stream_iso, stream_iso_mat_ader_iso_ptr, mat, mat_ader_data;
    long mat_iso, iso, iso_ZAI, nuc;

    fprintf(outp, "Begin: Test_ADERProcessMatStreamIsoMatAderIsoPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed stream.\n");

        stream_name = GetText(stream + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", stream_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe feed stream but no isotopes.\n");

            stream_iso = (long)RDB[stream + ADER_MAT_STREAM_ISOS_PTR];

            while(stream_iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has isotopes but no Li-6.\n");

                iso_ZAI = (long)RDB[stream_iso + ADER_MAT_GRP_ISO_ZAI];

                stream_iso_mat_ader_iso_ptr = RDB[stream_iso + ADER_MAT_GRP_MAT_ADER_ISO_PTR];

                if(iso_ZAI == 30060)
                {

                    sprintf(print_data, "FLiBeFuel has no mat ader isos.\n");

                    break;

                }

                stream_iso = NextItem(stream_iso);
            }

            break;
        }

        stream = NextItem(stream);

    }

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has mat ader isos but no Li-6 iso.\n");

        iso = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
        {

            sprintf(print_data, "FLiBeFuel has mat ader isos Li-6 but index, %ld, does not match\n \
cmp iso ptr of %ld.\n", mat_iso, stream_iso_mat_ader_iso_ptr);

            if(mat_iso == stream_iso_mat_ader_iso_ptr)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        mat_iso = NextItem(mat_iso);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatGrpEleIsoPtr()
{
    char *const test_name = "ADERProcessMatGrpEleIsoPtr";
    char *stream_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long stream, stream_ele, stream_ele_iso, stream_iso, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERProcessMatGrpEleIsoPtr.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no feed streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no FLiBe feed stream.\n");

        stream_name = GetText(stream + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", stream_name, 5) == 0)
        {

            sprintf(print_data, "FLiBeFuel has FLiBe feed stream but no isotopes.\n");

            stream_iso = (long)RDB[stream + ADER_MAT_STREAM_ISOS_PTR];

            while(stream_iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe group has isotopes but no Li-6.\n");

                if((long)RDB[stream_iso + ADER_MAT_GRP_ISO_ZAI] == 30060)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe stream has no elements.\n");

                    break;

                }

                stream_iso = NextItem(stream_iso);
            }

            stream_ele = (long)RDB[stream + ADER_MAT_STREAM_ELES_PTR];

            while(stream_ele > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel FLiBe stream has elements but no Li.\n");

                if((long)RDB[stream_ele + ADER_MAT_GRP_ELE_Z] == 3)
                {

                    sprintf(print_data, "FLiBeFuel FLiBe stream has Li but no ele isos.\n");

                    stream_ele_iso = (long)RDB[stream_ele + ADER_MAT_GRP_ELE_ISOS_PTR];

                    while(stream_ele_iso > VALID_PTR)
                    {

                        sprintf(print_data, "FLiBeFuel FLiBe stream has Li and its isos but no Li-6 ptr.\n");

                        if((long)RDB[stream_ele_iso + ADER_MAT_GRP_ELE_ISO_PTR] == stream_iso)
                        {

                            boolean = 1;

                            memset(print_data, 0, strlen(print_data));

                            break;

                        }

                        stream_ele_iso = NextItem(stream_ele_iso);

                    }

                    break;

                }

                stream_ele = NextItem(stream_ele);

            }

            break;
        }

        stream = NextItem(stream);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERProcessMatStreamEleUnFixedIsos()
{
    char *const test_name = "ADERProcessMatStreamEleUnFixedIsos";
    char *stream_name, *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, stream, stream_iso, stream_iso_zai ;

    fprintf(outp, "Begin: Test_ADERProcessMatStreamEleUnFixedIsos.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no redox streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(stream > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no Beryllium redox stream.\n");

        stream_name = GetText(stream + ADER_MAT_STREAM_ID);

        if(strncmp("Beryllium", stream_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has Be redox stream but no isotopes.\n");

            stream_iso = (long)RDB[stream + ADER_MAT_STREAM_ISOS_PTR];

            while(stream_iso > VALID_PTR)
            {

                sprintf(print_data, "FLiBeFuel Be stream has isotopes but no Be-9.\n");

                stream_iso_zai = (long)RDB[stream_iso + ADER_MAT_GRP_ISO_ZAI];

                if(stream_iso_zai == 40090)
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                    break;

                }

                stream_iso = NextItem(stream_iso);
            }

            break;
        }

        stream = NextItem(stream);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderClusterMembers()
{
    char *const test_name = "ADERSetAderClusterMembers";
    char *ader_clus_ent_id, *ader_clus_parent_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    int booleanFLiBeFuel = 0;
    int booleanFluorine = 0;
    int booleanUranium = 0;
    long ader_clus, ader_clus_ent, ADER_data;

    fprintf(outp, "Begin: Test_ADERSetAderClusterMembers.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    ader_clus = (long)RDB[ADER_data + ADER_CLUSTERS_PTR];

    sprintf(print_data, "No ADER clusters found.\n");

    while(ader_clus > VALID_PTR)
    {

        sprintf(print_data, "No FLiBeFuel parent cluster found.\n");

        ader_clus_parent_id = GetText(ader_clus + ADER_CLUSTER_PARENT_ID);

        if(strncmp("FLiBeFuel", ader_clus_parent_id, 9) == 0)
        {

            ader_clus_ent = (long)RDB[ader_clus + ADER_CLUSTER_ENT_PTR];

            while(ader_clus_ent > VALID_PTR)
            {

                ader_clus_ent_id = GetText(ader_clus_ent + ADER_CLUSTER_ENT_ID);

                if(strncmp("FLiBeFuel", ader_clus_ent_id, 9) == 0)
                {

                    booleanFLiBeFuel = 1;

                }
                else if(strncmp("Fluorine0", ader_clus_ent_id, 9) == 0)
                {

                    booleanFluorine = 1;

                }
                else if(strncmp("Uranium233", ader_clus_ent_id, 10) == 0)
                {

                    booleanUranium = 1;

                }

                ader_clus_ent = NextItem(ader_clus_ent);

            }

            break;

        }

        ader_clus = NextItem(ader_clus);

    }

    if((booleanFLiBeFuel == 1) && (booleanFluorine == 1) && (booleanUranium == 1))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndCntId()
{
    char *const test_name = "ADERSetAderCndCntId";
    char *cnd_name, *cnt_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, cnt;

    fprintf(outp, "Begin: Test_ADERSetAderCndCntId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];


    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    cnt = (long)RDB[cnd + ADER_CND_CNT_PTR];

    cnt_name = GetText(cnt + ADER_CND_CNT_ID);

    sprintf(print_data, "Ader CND FLiBeFuel cnt group 001 not found. \n");

    if(strncmp("001", cnt_name, 3) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndId()
{
    char *const test_name = "ADERSetAderCndId";
    char *cnd_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd;

    fprintf(outp, "Begin: Test_ADERSetAderCndId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];


    sprintf(print_data, "ADER CND FLiBeFuel not found. \n");

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        cnd = NextItem(cnd);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOptDir()
{
    char *const test_name = "ADERSetAderCndOptDir";
    char *cnd_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, cnd_opt, cnd_opt_dir;

    fprintf(outp, "Begin: Test_ADERSetAderCndOptDir.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];


    sprintf(print_data, "ADER CND LiF not found. \n");

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("LiF", cnd_name, 3) == 0)
        {

            sprintf(print_data, "ADER CND LiF has no optimization entry or bad direction.\n");

            break;
        }

        cnd = NextItem(cnd);
    }

    cnd_opt = (long)RDB[cnd + ADER_CND_OPT_PTR];

    cnd_opt_dir = (long)RDB[cnd_opt + ADER_CND_OPT_DIR];

    if(cnd_opt_dir < 0 )
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOptTarget()
{
    char *const test_name = "ADERSetAderCndOptTarget";
    char *cnd_name, *cnd_opt_target;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, cnd_opt;

    fprintf(outp, "Begin: Test_ADERSetAderCndOptTarget.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];


    sprintf(print_data, "ADER CND LiF not found. \n");

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("LiF", cnd_name, 3) == 0)
        {

            sprintf(print_data, "ADER CND LiF has no optimization entry or bad target.\n");

            break;
        }

        cnd = NextItem(cnd);
    }

    cnd_opt = (long)RDB[cnd + ADER_CND_OPT_PTR];

    cnd_opt_target = GetText(cnd_opt + ADER_CND_OPT_TYPE_TARGET);

    if(strncmp("feed", cnd_opt_target, 4) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOptType()
{
    char *const test_name = "ADERSetAderCndOptType";
    char *cnd_name, *cnd_opt_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, cnd_opt;

    fprintf(outp, "Begin: Test_ADERSetAderCndOptType.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];


    sprintf(print_data, "ADER CND LiF not found. \n");

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("LiF", cnd_name, 3) == 0)
        {

            sprintf(print_data, "ADER CND LiF has no optimization entry or bad type.\n");

            break;
        }

        cnd = NextItem(cnd);
    }

    cnd_opt = (long)RDB[cnd + ADER_CND_OPT_PTR];

    cnd_opt_type = GetText(cnd_opt + ADER_CND_OPT_TYPE);

    if(strncmp("action", cnd_opt_type, 6) == 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOxiId()
{
    char *const test_name = "ADERSetAderCndOxiId";
    char *cnd_name, *oxi_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, oxi;

    fprintf(outp, "Begin: Test_ADERSetAderCndOxiId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    oxi = (long)RDB[cnd + ADER_CND_OXI_PTR];

    oxi_name = GetText(oxi + ADER_CND_OXI_ID);

    sprintf(print_data, "Ader CND FLiBeFuel oxi group 001 not found. \n");

    if(strncmp("002", oxi_name, 3) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOxiMax()
{
    char *const test_name = "ADERSetAderCndOxiMax";
    char *cnd_name, *oxi_name;
    char status[5], print_data[256];
    double cnd_oxi_max;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, oxi;

    fprintf(outp, "Begin: Test_ADERSetAderCndOxiMax.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {

        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {

            break;

        }

        cnd = NextItem(cnd);
    }

    oxi = (long)RDB[cnd + ADER_CND_OXI_PTR];

    oxi_name = GetText(oxi + ADER_CND_OXI_ID);

    sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 not found. \n");

    if(strncmp("002", oxi_name, 3) == 0)
    {

        sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 has bad max. \n");

        cnd_oxi_max = RDB[oxi + ADER_CND_OXI_MAX];

        if(cnd_oxi_max < 0.0010001 && cnd_oxi_max >0.00099999)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

        }

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOxiMin()
{
    char *const test_name = "ADERSetAderCndOxiMin";
    char *cnd_name, *oxi_name;
    char status[5], print_data[256];
    double cnd_oxi_min;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, oxi;

    fprintf(outp, "Begin: Test_ADERSetAderCndOxiMin.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {

        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {

            break;

        }

        cnd = NextItem(cnd);
    }

    oxi = (long)RDB[cnd + ADER_CND_OXI_PTR];

    oxi_name = GetText(oxi + ADER_CND_OXI_ID);

    sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 not found. \n");

    if(strncmp("002", oxi_name, 3) == 0)
    {

        sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 has bad min. \n");

        cnd_oxi_min = RDB[oxi + ADER_CND_OXI_MIN];

        if(cnd_oxi_min < 0.0000001 && cnd_oxi_min > -0.00000001)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

        }

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndOxiVal()
{
    char *const test_name = "ADERSetAderCndOxiVal";
    char *cnd_name, *oxi_name;
    char status[5], print_data[256];
    double cnd_oxi_val;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, oxi;

    fprintf(outp, "Begin: Test_ADERSetAderCndOxiVal.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {

        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("LiF", cnd_name, 3) == 0)
        {

            break;

        }

        cnd = NextItem(cnd);
    }

    oxi = (long)RDB[cnd + ADER_CND_OXI_PTR];

    oxi_name = GetText(oxi + ADER_CND_OXI_ID);

    sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 not found. \n");

    if(strncmp("002", oxi_name, 3) == 0)
    {

        sprintf(print_data, "Ader CND FLiBeFuel oxi group 002 has bad value. \n");

        cnd_oxi_val = RDB[oxi + ADER_CND_OXI_MAX];

        if(cnd_oxi_val < 0.00020001 && cnd_oxi_val > 0.000199999)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

        }

    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndPreserveType()
{
    char *const test_name = "ADERSetAderCndPreserveType";
    char *cnd_name, *pres_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, pres;

    fprintf(outp, "Begin: Test_ADERSetAderCndPreserveType.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    sprintf(print_data, "ADER CND FLiBeFuel not found. \n");

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {

            pres = (long)RDB[cnd + ADER_CND_PRES_PTR];

            while(pres > VALID_PTR)
            {

                pres_type = GetText(pres + ADER_CND_PRES_ENT);

                if(strncmp("mols", pres_type, 4) == 0)
                {

                    memset(print_data, 0, strlen(print_data));

                    boolean = 1;

                    break;

                }

                pres = NextItem(pres);
            }

            break;

        }

        cnd = NextItem(cnd);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRngGrpId()
{
    char *const test_name = "ADERSetAderCndRngGrpId";
    char *cnd_name, *rng_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rng;

    fprintf(outp, "Begin: Test_ADERSetAderCndRngGrpId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rng = (long)RDB[cnd + ADER_CND_RNGS_PTR];

    sprintf(print_data, "Ader RNG FLiBe in CNT FLiBeFuel not found.\n");

    while(rng > VALID_PTR)
    {
        rng_name = GetText(rng + ADER_CND_RNG_GRP_ID);

        if(strncmp("FLiBe", rng_name, 5) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        rng = NextItem(rng);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRngMax()
{
    char *const test_name = "ADERSetAderCndRngMax";
    char *cnd_name, *rng_name;
    char status[5], print_data[256];
    double rng_max;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rng;

    fprintf(outp, "Begin: Test_ADERSetAderCndRngMax.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rng = (long)RDB[cnd + ADER_CND_RNGS_PTR];

    while(rng > VALID_PTR)
    {
        rng_name = GetText(rng + ADER_CND_RNG_GRP_ID);

        if(strncmp("FLiBe", rng_name, 5) == 0)
        {
            rng_max = RDB[rng + ADER_CND_RNG_MAX];
            sprintf(print_data, "Rng max is %f, not 1.0 for \
                                rng FLiBe in CND FliBeFuel.\n",
                    rng_max);
            break;
        }

        rng = NextItem(rng);
    }

    if(rng_max < 1.000001 && rng_max > 0.999999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRngMin()
{
    char *const test_name = "ADERSetAderCndRngMin";
    char *cnd_name, *rng_name;
    char status[5], print_data[256];
    double rng_min;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rng;

    fprintf(outp, "Begin: Test_ADERSetAderCndRngMin.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rng = (long)RDB[cnd + ADER_CND_RNGS_PTR];

    while(rng > VALID_PTR)
    {
        rng_name = GetText(rng + ADER_CND_RNG_GRP_ID);

        if(strncmp("FLiBe", rng_name, 5) == 0)
        {
            rng_min = RDB[rng + ADER_CND_RNG_MIN];
            sprintf(print_data, "Rng min is %f, not 0.2 for \
                                 rng FLiBe in CND FliBeFuel.\n",
                    rng_min);
            break;
        }

        rng = NextItem(rng);
    }

    if(rng_min < 0.200001 && rng_min > 0.1999999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRngVal()
{
    char *const test_name = "ADERSetAderCndRngVal";
    char *cnd_name, *rng_name;
    char status[5], print_data[256];
    double rng_val;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rng;

    fprintf(outp, "Begin: Test_ADERSetAderCndRngVal.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rng = (long)RDB[cnd + ADER_CND_RNGS_PTR];

    while(rng > VALID_PTR)
    {
        rng_name = GetText(rng + ADER_CND_RNG_GRP_ID);

        if(strncmp("ActF", rng_name, 4) == 0)
        {
            rng_val = RDB[rng + ADER_CND_RNG_MIN];
            sprintf(print_data, "Rng val is %f, not 0.4 for \
                                rng FLiBe in CND FliBeFuel.\n",
                    rng_val);
            break;
        }

        rng = NextItem(rng);
    }

    if(rng_val < 0.400001 && rng_val > 0.3999999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRtoGrpId()
{
    char *const test_name = "ADERSetAderCndRtoGrpsId";
    char *cnd_name, *rto1_name, *rto2_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rto;

    fprintf(outp, "Begin: Test_ADERSetAderCndRtoGrpsId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rto = (long)RDB[cnd + ADER_CND_RTOS_PTR];

    sprintf(print_data, "Ader RTO FLiBe/ActF in CNT FLiBeFuel not found.\n");

    while(rto > VALID_PTR)
    {
        rto1_name = GetText(rto + ADER_CND_RTO_GRP1_ID);
        rto2_name = GetText(rto + ADER_CND_RTO_GRP2_ID);

        if((strncmp("FLiBe", rto1_name, 5) == 0) &&
           (strncmp("ActF", rto2_name, 4) == 0))
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        rto = NextItem(rto);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRtoMax()
{
    char *const test_name = "ADERSetAderCndRtoMax";
    char *cnd_name, *rto1_name, *rto2_name;
    char status[5], print_data[256];
    double rto_max;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rto;

    fprintf(outp, "Begin: Test_ADERSetAderCndRtoMax.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rto = (long)RDB[cnd + ADER_CND_RTOS_PTR];

    while(rto > VALID_PTR)
    {

        rto1_name = GetText(rto + ADER_CND_RTO_GRP1_ID);

        rto2_name = GetText(rto + ADER_CND_RTO_GRP2_ID);

        if((strncmp("FLiBe", rto1_name, 5) == 0) &&
           (strncmp("ThF4", rto2_name, 4) == 0))
        {
            rto_max = RDB[rto + ADER_CND_RTO_MAX];

            sprintf(print_data, "Rto max is %f, not 99 for \
                                rto FLiBe/ActF in CND FliBeFuel.\n",
                    rto_max);

            break;

        }

        rto = NextItem(rto);
    }

    if(rto_max < 99.000001 && rto_max > 98.999999)
    {
        boolean = 1;

        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRtoMin()
{
    char *const test_name = "ADERSetAderCndRtoMin";
    char *cnd_name, *rto1_name, *rto2_name;
    char status[5], print_data[256];
    double rto_min;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rto;

    fprintf(outp, "Begin: Test_ADERSetAderCndRtoMin.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rto = (long)RDB[cnd + ADER_CND_RTOS_PTR];

    while(rto > VALID_PTR)
    {
        rto1_name = GetText(rto + ADER_CND_RTO_GRP1_ID);
        rto2_name = GetText(rto + ADER_CND_RTO_GRP2_ID);

        if((strncmp("FLiBe", rto1_name, 5) == 0) &&
           (strncmp("ThF4", rto2_name, 4) == 0))
        {
            rto_min = RDB[rto + ADER_CND_RTO_MIN];
            sprintf(print_data, "Rto min is %f, not 4.0 for \
                                rto FLiBe/ActF in CND FliBeFuel.\n",
                    rto_min);
            break;
        }

        rto = NextItem(rto);
    }

    if(rto_min < 4.000001 && rto_min > 3.999999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderCndRtoVal()
{
    char *const test_name = "ADERSetAderCndRtoVal";
    char *cnd_name, *rto1_name, *rto2_name;
    char status[5], print_data[256];
    double rto_val;
    int append = 0;
    int boolean = 0;
    long ADER_data, cnd, rto;

    fprintf(outp, "Begin: Test_ADERSetAderCndRtoVal.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnd = (long)RDB[ADER_data + ADER_CONDITIONS_PTR];

    while(cnd > VALID_PTR)
    {
        cnd_name = GetText(cnd + ADER_CND_ID);

        if(strncmp("FLiBeFuel", cnd_name, 9) == 0)
        {
            break;
        }

        cnd = NextItem(cnd);
    }

    rto = (long)RDB[cnd + ADER_CND_RTOS_PTR];

    while(rto > VALID_PTR)
    {
        rto1_name = GetText(rto + ADER_CND_RTO_GRP1_ID);
        rto2_name = GetText(rto + ADER_CND_RTO_GRP2_ID);

        if((strncmp("FLiBe", rto1_name, 5) == 0) &&
           (strncmp("ActF", rto2_name, 4) == 0))
        {
            rto_val = RDB[rto + ADER_CND_RTO_MIN];
            sprintf(print_data, "Rto val is %f, not 2.0 for \
                                rto FLiBe/ActF in CND FliBeFuel.\n",
                    rto_val);
            break;
        }

        rto = NextItem(rto);
    }

    if(rto_val < 2.000001 || rto_val > 1.999999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderControlEntZ()
{
    char *const test_name = "ADERSetAderControlEntZ";
    char *cnt_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ent, cnt, Z;

    fprintf(outp, "Begin: Test_ADERSetAderControlEntZ.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnt = (long)RDB[ADER_data + ADER_CONTROL_PTR];

    sprintf(print_data, "ADER Control has no entry data \n");

    while(cnt > VALID_PTR)
    {
        cnt_name = GetText(cnt + ADER_CONTROL_TBL_ID);

        if(strncmp("001", cnt_name, 1) == 0)
        {
            ent = (long)RDB[cnt + ADER_CONTROL_ENT_PTR];

            if(ent > VALID_PTR)
            {
                sprintf(print_data, "ADER control has valid entry data but no Li.\n");
                break;
            }
        }

        cnt = NextItem(cnt);
    }

    while(ent > VALID_PTR)
    {
        Z = (long)RDB[ent + ADER_CONTROL_ENT_Z];

        if(Z == 3)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderControlEntZai()
{
    char *const test_name = "ADERSetAderControlEntZai";
    char *cnt_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ent, cnt, Zai;

    fprintf(outp, "Begin: Test_ADERSetAderControlEntZai.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnt = (long)RDB[ADER_data + ADER_CONTROL_PTR];

    sprintf(print_data, "ADER Control has no entry data \n");

    while(cnt > VALID_PTR)
    {
        cnt_name = GetText(cnt + ADER_CONTROL_TBL_ID);

        if(strncmp("001", cnt_name, 1) == 0)
        {
            ent = (long)RDB[cnt + ADER_CONTROL_ENT_PTR];

            if(ent > VALID_PTR)
            {
                sprintf(print_data, "ADER Control has valid entry data but no Pu-239.\n");
                break;
            }
        }

        cnt = NextItem(cnt);
    }

    while(ent > VALID_PTR)
    {
        Zai = (long)RDB[ent + ADER_CONTROL_ENT_ZAI];

        if(Zai == 942390)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        ent = NextItem(ent);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderControlTblId()
{
    char *const test_name = "ADERSetAderControlTblId";
    char *cnt_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, cnt;

    fprintf(outp, "Begin: Test_ADERSetAderControlTblId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    cnt = (long)RDB[ADER_data + ADER_CONTROL_PTR];

    sprintf(print_data, "ADER Control has no entry data \n");

    while(cnt > VALID_PTR)
    {
        cnt_name = GetText(cnt + ADER_CONTROL_TBL_ID);

        if(strncmp("001", cnt_name, 1) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        cnt = NextItem(cnt);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderGrpCompZ()
{
    char *const test_name = "ADERSetAderGrpCompZ";
    char *grp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    int booleanBe = 0;
    int booleanF = 0;
    int booleanLi = 0;
    int booleanOther = 0;
    long ADER_data, comp, comp_Z, grp;

    fprintf(outp, "Begin: Test_ADERSetAderGrpCompZ.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("FLiBe", grp_name, 5) == 0)
        {
            break;
        }

        grp = NextItem(grp);
    }

    /*Check FLiBe group composition */

    comp = (long)RDB[grp + ADER_GRP_COMP_PTR];

    if(comp < VALID_PTR)
    {
        boolean = 0;
        sprintf(print_data, "Group FLiBe does not have composition. \n");
    }
    else
    {
        while(comp > VALID_PTR)
        {

           comp_Z = (long)RDB[comp + ADER_GRP_COMP_Z];

           if(comp_Z == 3)
           {
               booleanLi = 1;
           }
           else if(comp_Z == 4)
           {
               booleanBe = 1;
           }
           else if(comp_Z == 9)
           {
               booleanF = 1;
           }
           else
           {
               booleanOther = 1;
           }

           comp = NextItem(comp);
        }
    }

    if((booleanLi == 1 && booleanBe == 1 && booleanF == 1)
       && booleanOther == 0 )
    {
        boolean = 1;
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderGrpId()
{
    char *const test_name = "ADERSetAderGrpID";
    char *grp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, grp;

    fprintf(outp, "Begin: Test_ADERSetAderGrpID.\n");

    sprintf(print_data, "FLiBe group not found. \n");

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("FLiBe", grp_name, 5) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        grp = NextItem(grp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderGrpIsoZai()
{
    char *const test_name = "ADERSetAderGrpIsoZai";
    char *grp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    int boolean6 = 0;
    int boolean7 = 0;
    int booleanOther = 0;
    long ADER_data, comp, comp_Z, grp, iso, iso_zai;

    fprintf(outp, "Begin: Test_ADERSetAderGrpIsoZai.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("FLiBe", grp_name, 5) == 0)
        {
            break;
        }

        grp = NextItem(grp);
    }

    comp = (long)RDB[grp + ADER_GRP_COMP_PTR];

    while(comp > VALID_PTR)
    {
        comp_Z = (long)RDB[comp + ADER_GRP_COMP_Z];

        iso = (long)RDB[comp + ADER_GRP_COMP_ISOS_PTR];

        if(comp_Z == 3)
        {
            boolean = 0;
            sprintf(print_data, "Group FLiBe Li has no isos");

            while(iso > VALID_PTR)
            {

               iso_zai = (long)RDB[iso + ADER_GRP_ISO_ZAI];

               if(iso_zai == 30060)
               {
                   boolean6 = 1;
               }
               else if(iso_zai == 30070)
               {
                   boolean7 = 1;
               }
               else
               {
                   booleanOther = 1;
               }

               iso = NextItem(iso);
            }

            if(boolean6 == 1 && boolean7 == 1 && booleanOther == 0)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

                break;

            }
        }
        else if(comp_Z == 4 && iso > VALID_PTR)
        {

            boolean = 0;

            sprintf(print_data, "Group FLiBe Be entry has isos. \n");

            break;

        }
        else if(comp_Z == 9 && iso > VALID_PTR)
        {

            boolean = 0;

            sprintf(print_data, "Group FLiBe F entry has isos. \n");

            break;

        }

        comp = NextItem(comp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }

}

int Test_ADERSetAderGrpSumGroupsPtr()
{
    char *const test_name = "ADERSetAderGrpSumGroupsPtr";
    char *grp_name, *sgrp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    int boolean1 = 0;
    int boolean2 = 0;
    int booleanOther = 0;
    long ADER_data, grp, sgrp;

    fprintf(outp, "Begin: Test_ADERSetAderGrpSumGroupsPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("NestedSum", grp_name, 9) == 0)
        {
            break;
        }

        grp = NextItem(grp);
    }

    /* Check the 'summation' groups */
    if((long)RDB[grp + ADER_GRP_SUM_GRPS_PTR] < VALID_PTR)
    {
        sprintf(print_data, "Group NestedSum has no 'summation' groups.\n");
    }
    else
    {
        sgrp = (long)RDB[grp + ADER_GRP_SUM_GRPS_PTR];
        while(sgrp > VALID_PTR)
        {

            sgrp_name = GetText(sgrp + ADER_GRP_SUM_GRP_ID);

            if(strncmp("ActF", sgrp_name, 4) == 0)
            {

                boolean1 = 1;

            }
            else if(strncmp("Beryllium", sgrp_name, 9) == 0)
            {

                boolean2 = 1;

            }
            else
            {

                booleanOther = 1;

            }

            sgrp = NextItem(sgrp);
        }

        sprintf(print_data, "Group NestedSum doesn't have correct groups. \n");

        if(boolean1 == 1 && boolean2 == 1 && booleanOther == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
        }
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderKMax()
{
    char *const test_name = "ADERSetAderKMax";
    char status[5], print_data[256];
    double ADER_kMax;
    int append = 0;
    int boolean = 0;
    long ADER_data;

    fprintf(outp, "Begin: Test_ADERSetAderKMax.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    ADER_kMax = RDB[ADER_data + ADER_K_MAX];

    sprintf(print_data, "ADER k max criteria is %f but should be 1.00005.\n",
            ADER_kMax);

    if(ADER_kMax < 1.000050001 && ADER_kMax > 1.000049999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderKMin()
{
    char *const test_name = "ADERSetAderKMin";
    char status[5], print_data[256];
    double ADER_kMin;
    int append = 0;
    int boolean = 0;
    long ADER_data;

    fprintf(outp, "Begin: Test_ADERSetAderKMax.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    ADER_kMin = RDB[ADER_data + ADER_K_MIN];

    sprintf(print_data, "ADER k min criteria is %f but should be 0.99995.\n",
            ADER_kMin);

    if(ADER_kMin < 0.999950001 && ADER_kMin > 0.999949999)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderNegAdens()
{
    char *const test_name = "ADERSetAderNegAdens";
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data;

    fprintf(outp, "Begin: Test_ADERSetAderNegAdens.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    sprintf(print_data, "ADER negative adens key is %ld but should be 1.\n",
            (long)RDB[ADER_data + ADER_TRANS_ITER]);

    if((long)RDB[ADER_data + ADER_NEG_ADENS_OPT] > 0)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderOxiEleVal()
{
    char *const test_name = "ADERSetAderOxiEleVal";
    char *oxi_name;
    char status[5], print_data[256];
    double oxi_val;
    int append = 0;
    int boolean = 0;
    long ADER_data, ele, oxi, Z;

    fprintf(outp, "Begin: Test_ADERSetAderOxiEleVal.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    oxi = (long)RDB[ADER_data + ADER_OXIS_PTR];

    sprintf(print_data, "ADER oxi has no entry data \n");

    while(oxi > VALID_PTR)
    {
        oxi_name = GetText(oxi + ADER_OXI_TBL_ID);

        if(strncmp("002", oxi_name, 3) == 0)
        {
            ele = (long)RDB[oxi + ADER_OXI_ELES_PTR];

            if(ele > VALID_PTR)
            {
                sprintf(print_data, "ADER oxi has valid entry data but \
                                     no either no H or incorrect value.\n");
                break;
            }
        }

        oxi = NextItem(oxi);
    }

    while(ele > VALID_PTR)
    {
        Z = (long)RDB[ele + ADER_OXI_ELE_Z];

        oxi_val = RDB[ele + ADER_OXI_ELE_VAL];

        if(Z == 1 && (oxi_val > 0.999999 && oxi_val < 1.000001))
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        ele = NextItem(ele);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderOxiEleWeight()
{
    char *const test_name = "ADERSetAderOxiEleWeight";
    char *oxi_name;
    char status[5], print_data[256];\
    double oxi_weight;
    int append = 0;
    int boolean = 0;
    long ADER_data, ele, oxi, Z;

    fprintf(outp, "Begin: Test_ADERSetAderOxiEleWeight.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    oxi = (long)RDB[ADER_data + ADER_OXIS_PTR];

    sprintf(print_data, "ADER oxi has no entry data \n");

    while(oxi > VALID_PTR)
    {
        oxi_name = GetText(oxi + ADER_OXI_TBL_ID);

        if(strncmp("002", oxi_name, 3) == 0)
        {
            ele = (long)RDB[oxi + ADER_OXI_ELES_PTR];

            if(ele > VALID_PTR)
            {
                sprintf(print_data, "ADER oxi has valid entry data but \
                                     either no H or incorrect weight.\n");
                break;
            }
        }

        oxi = NextItem(oxi);
    }

    while(ele > VALID_PTR)
    {
        Z = (long)RDB[ele + ADER_OXI_ELE_Z];

        oxi_weight = RDB[ele + ADER_OXI_ELE_WEIGHT];

        if(Z == 1)
        {
            sprintf(print_data, "ADER oxi has valid entry data and \
                                 H but incorrect weight for H.\n");
            if(oxi_weight < 2.000001 && oxi_weight > 1.999999)
            {
                boolean = 1;

                memset(print_data, 0, strlen(print_data));

                break;
            }
        }

        ele = NextItem(ele);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderOxiEleZ()
{
    char *const test_name = "ADERSetAderOxiEleZ";
    char *oxi_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ele, oxi, Z;

    fprintf(outp, "Begin: Test_ADERSetAderOxiEleZ.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    oxi = (long)RDB[ADER_data + ADER_OXIS_PTR];

    sprintf(print_data, "ADER oxi has no entry data \n");

    while(oxi > VALID_PTR)
    {
        oxi_name = GetText(oxi + ADER_OXI_TBL_ID);

        if(strncmp("002", oxi_name, 3) == 0)
        {
            ele = (long)RDB[oxi + ADER_OXI_ELES_PTR];

            if(ele > VALID_PTR)
            {
                sprintf(print_data, "ADER oxi has valid entry data but no H.\n");
                break;
            }
        }

        oxi = NextItem(oxi);
    }

    while(ele > VALID_PTR)
    {
        Z = (long)RDB[ele + ADER_OXI_ELE_Z];

        if(Z == 1)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        ele = NextItem(ele);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderOxiTblId()
{
    char *const test_name = "ADERSetAderOxiTblId";
    char *oxi_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, oxi;

    fprintf(outp, "Begin: Test_ADERSetAderOxiTblId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    oxi = (long)RDB[ADER_data + ADER_OXIS_PTR];

    sprintf(print_data, "ADER oxi '002' not found. \n");

    while(oxi > VALID_PTR)
    {
        oxi_name = GetText(oxi + ADER_OXI_TBL_ID);

        if(strncmp("002", oxi_name, 3) == 0)
        {
            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;
        }

        oxi = NextItem(oxi);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderReproEntVal()
{
    char *const test_name = "ADERSetAderReproEntVal";
    char *repro_name;
    char status[5], print_data[256];
    double repro_val;
    int append = 0;
    int boolean = 0;
    long ADER_data, ent, repro, Z;

    fprintf(outp, "Begin: Test_ADERSetAderReproEntVal.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    repro = (long)RDB[ADER_data + ADER_REPROS_PTR];

    sprintf(print_data, "ADER Repro has no entry data \n");

    while(repro > VALID_PTR)
    {
        repro_name = GetText(repro + ADER_REPRO_TBL_ID);

        if(strncmp("reproc", repro_name, 6) == 0)
        {
            ent = (long)RDB[repro + ADER_REPRO_ENT_PTR];

            if(ent > VALID_PTR)
            {
                sprintf(print_data, "ADER Repro has valid entry data but \
                                     either no H or wrong repro val.\n");
                break;
            }
        }

        repro = NextItem(repro);
    }

    while(ent > VALID_PTR)
    {
        Z = (long)RDB[ent + ADER_REPRO_ENT_Z];

        repro_val = RDB[ent + ADER_REPRO_ENT_VAL];

        if(Z == 1 && (repro_val < 0.400001 && repro_val > 0.399999))
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        ent = NextItem(ent);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderReproEntZ()
{
    char *const test_name = "ADERSetAderReproEntZ";
    char *repro_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ent, repro, Z;

    fprintf(outp, "Begin: Test_ADERSetAderReproEntZ.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    repro = (long)RDB[ADER_data + ADER_REPROS_PTR];

    sprintf(print_data, "ADER Repro has no entry data \n");

    while(repro > VALID_PTR)
    {

        repro_name = GetText(repro + ADER_REPRO_TBL_ID);

        if(strncmp("reproc", repro_name, 6) == 0)
        {

            ent = (long)RDB[repro + ADER_REPRO_ENT_PTR];

            if(ent > VALID_PTR)
            {

                sprintf(print_data, "ADER Repro has valid entry data but no H.\n");

                break;

            }

        }

        repro = NextItem(repro);
    }

    while(ent > VALID_PTR)
    {

        Z = (long)RDB[ent + ADER_REPRO_ENT_Z];

        if(Z == 1)
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

            break;

        }

        ent = NextItem(ent);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderReproEntZai()
{
    char *const test_name = "ADERSetAderReproEntZai";
    char *repro_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, ent, repro, ZAI;

    fprintf(outp, "Begin: Test_ADERSetAderReproEntZai.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    repro = (long)RDB[ADER_data + ADER_REPROS_PTR];

    sprintf(print_data, "ADER Repro has no entry data \n");

    while(repro > VALID_PTR)
    {
        repro_name = GetText(repro + ADER_REPRO_TBL_ID);

        if(strncmp("reproc", repro_name, 6) == 0)
        {
            ent = (long)RDB[repro + ADER_REPRO_ENT_PTR];

            if(ent > VALID_PTR)
            {
                sprintf(print_data, "ADER Repro has valid entry data but no U-233.\n");
                break;
            }
        }

        repro = NextItem(repro);
    }

    while(ent > VALID_PTR)
    {
        ZAI = (long)RDB[ent + ADER_REPRO_ENT_ZAI];

        if(ZAI == 922330)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        ent = NextItem(ent);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderReproTblId()
{
    char *const test_name = "ADERSetAderReproTblId";
    char *repro_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, repro;

    fprintf(outp, "Begin: Test_ADERSetAderReproTblId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    repro = (long)RDB[ADER_data + ADER_REPROS_PTR];

    sprintf(print_data, "ADER Repro 'reproc'not found. \n");

    while(repro > VALID_PTR)
    {
        repro_name = GetText(repro + ADER_REPRO_TBL_ID);

        if(strncmp("reproc", repro_name, 6) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        repro = NextItem(repro);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrDest()
{
    char *const test_name = "ADERSetAderStrDest";
    char *str_grp_name, *str_dest_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrDest.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("Beryllium", str_grp_name, 9) == 0)
        {
            break;
        }

        str = NextItem(str);
    }

    str_dest_name = GetText(str + ADER_STREAM_DEST);

    sprintf(print_data, "Destination FLiBeFuel not found in \
                         Beryllium stream.\n");

    if(strncmp("FLiBeFuel", str_dest_name, 9) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrForm()
{
    char *const test_name = "ADERSetAderStrForm";
    char *form, *str_grp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrForm.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("Beryllium", str_grp_name, 9) == 0)
        {
            form = GetText(str + ADER_STREAM_FORM);
            break;
        }

        str = NextItem(str);
    }

    sprintf(print_data, "Form for Beryllium stream not equal to 'cont'.\n");

    if(strncmp("cont", form, 4) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrGrpId()
{
    char *const test_name = "ADERSetAderStrGrpId";
    char *str_grp_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrGrpId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    sprintf(print_data, "ADER Str Beryllium to FLiBeFuel not found. \n");

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("Beryllium", str_grp_name, 9) == 0)
        {
            boolean = 1;
            memset(print_data, 0, strlen(print_data));
            break;
        }

        str = NextItem(str);
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrGrpType()
{
    char *const test_name = "ADERSetAderStrGrpType";
    char *str_grp_name, *str_grp_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrGrpType.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    sprintf(print_data, "ADER Str Beryllium to FLiBeFuel grp type is not grp. \n");

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("Beryllium", str_grp_name, 9) == 0)
        {
            str_grp_type = GetText(str + ADER_STREAM_GRP_TYPE);
            break;
        }

        str = NextItem(str);
    }

    if(strncmp("group", str_grp_type, 3) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrOpt1()
{
    char *const test_name = "ADERSetAderStrOpt1";
    char *str_grp_name;
    char status[5], print_data[256];
    double opt1;
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrOpt1.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("reproc", str_grp_name, 6) == 0)
        {
            opt1 = RDB[str + ADER_STREAM_OPT1];
            break;
        }

        str = NextItem(str);
    }

    sprintf(print_data, "Opt1 for 'reproc' stream is %f, not 0.00001.\n",
            opt1);

    if(opt1 > 0.00000999 && opt1 < 0.00001001)
    {

        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrSrc()
{
    char *const test_name = "ADERSetAderStrSrc";
    char *str_grp_name, *str_src_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrSrc.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("reproc", str_grp_name, 6) == 0)
        {
            break;
        }

        str = NextItem(str);
    }

    str_src_name = GetText(str + ADER_STREAM_SRC);

    sprintf(print_data, "Source FLiBeFuel not found in \
                         'reproc'stream.\n");

    if(strncmp("FLiBeFuel", str_src_name, 9) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderStrType()
{
    char *const test_name = "ADERSetAderStrType";
    char *str_grp_name, *str_type;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data, str;

    fprintf(outp, "Begin: Test_ADERSetAderStrType.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    str = (long)RDB[ADER_data + ADER_STREAMS_PTR];

    sprintf(print_data, "ADER Str Beryllium to FLiBeFuel type is not redox. \n");

    while(str > VALID_PTR)
    {
        str_grp_name = GetText(str + ADER_STREAM_GRP_ID);

        if(strncmp("Beryllium", str_grp_name, 9) == 0)
        {
            str_type = GetText(str + ADER_STREAM_TYPE);
            break;
        }

        str = NextItem(str);
    }

    if(strncmp("redox", str_type, 5) == 0)
    {
        boolean = 1;
        memset(print_data, 0, strlen(print_data));
    }


    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderSumGrpWeight()
{
    char *const test_name = "ADERSetAderSumGrpWeight";
    char *grp_name, *sgrp_name;
    char status[5], print_data[256];
    double sgrp_weight;
    int append = 0;
    int boolean = 0;
    long ADER_data, grp, sgrp;

    fprintf(outp, "Begin: Test_ADERSetAderSumGrpWeight.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    grp = (long)RDB[ADER_data + ADER_GROUPS_PTR];

    while(grp > VALID_PTR)
    {
        grp_name = GetText(grp + ADER_GRP_ID);

        if(strncmp("NestedSum", grp_name, 9) == 0)
        {
            break;
        }

        grp = NextItem(grp);
    }

    sgrp = (long)RDB[grp + ADER_GRP_SUM_GRPS_PTR];

    while(sgrp > VALID_PTR)
    {

        sgrp_name = GetText(sgrp + ADER_GRP_SUM_GRP_ID);

        if(strncmp("ActF", sgrp_name, 4) == 0)
        {

            sprintf(print_data, "Sum grp weight for sum component \
                                 ActF in group NestedSum is %f but \
                                 should be 0.25.\n",sgrp_weight);

            sgrp_weight = RDB[sgrp + ADER_GRP_SUM_GRP_WEIGHT];

            if(sgrp_weight < 0.2500001 && sgrp_weight > 0.24999999)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

        }

        sgrp = NextItem(sgrp);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetAderTransIter()
{
    char *const test_name = "ADERSetAderTransIter";
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long ADER_data;

    fprintf(outp, "Begin: Test_ADERSetAderTransIter.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the first test group */

    ADER_data = (long)RDB[DATA_PTR_ADER];

    sprintf(print_data, "ADER number of transport iterations is %ld but should be 5.\n",
            (long)RDB[ADER_data + ADER_TRANS_ITER]);

    if((long)RDB[ADER_data + ADER_TRANS_ITER] == 5)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatAderMem()
{
    char *const test_name = "ADERSetMatAderMem";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long ADER_data, ele, mat, Z;

    fprintf(outp, "Begin: Test_ADERSetMatAderMem.\n");
    /* This test is unique in that the tested function, ADERSetMatAderMem,
     * does not return a value, rather, it modifies an array. To prevent
     * interference with other tests this test will not call ADERSetMatAderMem
     * to create a new material and what not. Rather, it will check that
     * the test material has the memory.
     */

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {
            break;
        }

        mat = NextItem(mat);
    }

    /* Get material ADER data */
    ADER_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Check that ADER data block exists */
    if(ADER_data < VALID_PTR)
    {
        boolean = 0;
        sprintf(print_data, "ADER material data block does not exist\n");
    }
    /* Check ADER_MAT_ELEMENTS_PTR */
    else if(RDB[ADER_data + ADER_MAT_ELES_PTR] < VALID_PTR)
    {
        boolean = 0;
        sprintf(print_data, "ADER material element block does not exist\n");
    }
    /*Check ADER_MAT_ELEMENTS_PTR array */
    else
    {
        ele = (long)RDB[ADER_data + ADER_MAT_ELES_PTR];
        for(i=0; i < NUMBER_OF_ELEMENTS; i++)
        {
            /* Check that element entry exits */
            if(ele < VALID_PTR)
            {
                boolean = 0;
                sprintf(print_data, "ADER material element, %d, does not exist\n",
                        i);
                break;
            }
            Z = (long)RDB[ele + ADER_MAT_ELE_Z];
            /* Check that element Z set correctly */
            if(Z != (i + 1))
            {
                boolean = 0;
                sprintf(print_data, "ADER material element, %d, does not \
                                     have proper Z value of %d, rather has %ld. \n",
                                        i, i + 1, Z);
                break;
            }
            ele = NextItem(ele);
        }
    }

    /* Check the reactivity weight */
    if(RDB[ADER_data + ADER_MAT_RHO_WEIGHT] < 1.000001 &&
       RDB[ADER_data + ADER_MAT_RHO_WEIGHT] > 0.999999)
    {
        boolean = 1;

        memset(print_data, 0, strlen(print_data));
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatAderCndMem()
{
    char *const test_name = "ADERSetMatAderCndMem";
    char status[5];
    char print_data[256];
    char *mat_name, *ader_mat_cnd_id;
    int append = 0;
    int boolean = 0;
    long mat_ader_data, ader_mat_cnd, mat;

    fprintf(outp, "Begin: Test_ADERSetMatAderCndMem.\n");
    /* This test is unique in that the tested function, ADERSetMatAderMem,
     * does not return a value, rather, it modifies an array. To prevent
     * interference with other tests this test will not call ADERSetMatAderMem
     * to create a new material and what not. Rather, it will check that
     * the test material has the memory.
     */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel has no CNDs attached to it.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_cnd = (long)RDB[mat_ader_data + ADER_MAT_CNDS_PTR];

    while(ader_mat_cnd > VALID_PTR)
    {

        ader_mat_cnd_id = GetText(ader_mat_cnd + ADER_MAT_CND_ID);

        if(strncmp("testCND", ader_mat_cnd_id, 7) == 0)
        {

            memset(print_data, 0, strlen(print_data));

            boolean = 1;

            break;

        }

        ader_mat_cnd = NextItem(ader_mat_cnd);

    }
    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCmpColLowerBounds()
{
    char *const test_name = "ADERSetMatCmpColLowerBounds";
    char *cmp_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    double mat_matrix_col_lower_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long cmp, cmp_col, mat, mat_ader_data, mat_matrix_data, mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatCmpColLowerBounds.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBe cmp not found in material FLiBeFuel.\n");

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBe cmp found but has bad column.\n");

            cmp_col = (long)RDB[cmp + ADER_MAT_CMP_COL_ID];

            if(cmp_col == 0)
            {

                mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

                mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

                for(i = 0; i < cmp_col; i++)
                {

                    mat_matrix_col = NextItem(mat_matrix_col);

                }

                mat_matrix_col_lower_bound = RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_LOWER_BOUND];

                sprintf(print_data, "FLiBe cmp has good column but column \n \
entry has bad lower bound of %f.\n", mat_matrix_col_lower_bound);

                if((mat_matrix_col_lower_bound > 0.19999999) &&
                   (mat_matrix_col_lower_bound < 0.20000001))
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                }

            }

            break;

        }

        cmp = NextItem(cmp);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCmpColId()
{
    char *const test_name = "ADERSetMatCmpColId";
    char *cmp_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long cmp, cmp_col, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatCmpColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF cmp not found in material FLiBeFuel.\n");

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("ActF", cmp_name, 4) == 0)
        {

            sprintf(print_data, "ActF cmp found but has bad column.\n");

            cmp_col = (long)RDB[cmp + ADER_MAT_CMP_COL_ID];

            if(cmp_col == 1)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        cmp = NextItem(cmp);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCmpColUpperBounds()
{
    char *const test_name = "ADERSetMatCmpColUpperBounds";
    char *cmp_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    double mat_matrix_col_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long cmp, cmp_col, mat, mat_ader_data, mat_matrix_data, mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatCmpColUpperBounds.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBe cmp not found in material FLiBeFuel.\n");

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", cmp_name, 5) == 0)
        {

            sprintf(print_data, "FLiBe cmp found but has bad column.\n");

            cmp_col = (long)RDB[cmp + ADER_MAT_CMP_COL_ID];

            if(cmp_col == 0)
            {

                mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

                mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

                for(i = 0; i < cmp_col; i++)
                {

                    mat_matrix_col = NextItem(mat_matrix_col);

                }

                mat_matrix_col_upper_bound = RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_UPPER_BOUND];

                sprintf(print_data, "FLiBe cmp has good column but column \n \
entry has bad upper bound of %f.\n", mat_matrix_col_upper_bound);

                if(mat_matrix_col_upper_bound > 1E+17)
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                }

            }

            break;

        }

        cmp = NextItem(cmp);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCmpSumRowId()
{
    char *const test_name = "ADERSetMatCmpSumRowId";
    char *cmp_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long cmp, cmp_sum_row, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatCmpSumRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF cmp not found in material FLiBeFuel.\n");

    cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(cmp > VALID_PTR)
    {

        cmp_name = GetText(cmp + ADER_MAT_CMP_ID);

        if(strncmp("ActF", cmp_name, 4) == 0)
        {

            cmp_sum_row = (long)RDB[cmp + ADER_MAT_CMP_SUM_GRPS_ROW_ID];

            sprintf(print_data, "ActF cmp found but has bad sum row of %ld.\n",
                    cmp_sum_row);

            if(cmp_sum_row == 4)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        cmp = NextItem(cmp);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCntEleFutRowUpperBound()
{
    char *const test_name = "ADERSetMatCntEleFutRowUpperBound";
    char status[5];
    char print_data[256];
    char *mat_name;
    double mat_matrix_row_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long ele, ele_row, ele_z, mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_row_bound;

    fprintf(outp, "Begin: Test_ADERSetMatCntEleFutRowUpperBound.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element Li not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 3)
        {

            ele_row = (long)RDB[ele + ADER_MAT_ELE_FUT_ROW_ID];

            sprintf(print_data, "Element Li found but has bad row of %ld.\n",
                    ele_row);

            if(ele_row == 19)
            {

                mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

                mat_matrix_row_bound = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

                for(i = 0; i < ele_row; i++)
                {

                    mat_matrix_row_bound = NextItem(mat_matrix_row_bound);

                }

                mat_matrix_row_upper_bound = RDB[mat_matrix_row_bound + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

                sprintf(print_data, "Row has bad upper bound of %f.\n",
                        mat_matrix_row_upper_bound);

                if((mat_matrix_row_upper_bound > -0.0000000001) &&
                   (mat_matrix_row_upper_bound < 0.00000000001))
                {

                    boolean = 1;

                    memset(print_data, 0, strlen(print_data));

                }

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatCompMatrixElement()
{
    char *const test_name = "ADERSetMatCompMatrixElement";
    char status[5];
    char print_data[256];
    char *mat_name;
    double mat_matrix_old_value;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col;
    long mat_matrix_col_row;

    fprintf(outp, "Begin: Test_ADERSetMatCompMatrixElement.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel comp matrix has no columns.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < 3; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_col_row = (long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR];

    for(i = 0; i < 4; i++)
    {

        mat_matrix_col_row = NextItem(mat_matrix_col_row);

    }

    mat_matrix_old_value = RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY];

    /* Go ahead and use the function to set the test value                    */
    ADERSetMaterialCompMatrixElement(3, 4, mat_matrix_data, 54.32);

    sprintf(print_data, "FLiBeFuel comp matrix has value %f at (3, 4) and should have %f.\n",
            RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY], 54.32);

    if(RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 54.31 &&
       RDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 54.33)
    {

        memset(print_data, 0, strlen(print_data));

        boolean = 1;

    }

    /* Reset the value of the matrix so it doesn't mess with future tests     */

    WDB[mat_matrix_col_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = mat_matrix_old_value;

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }

}

int Test_ADERSetMatEleBalRowId()
{
    char *const test_name = "ADERSetMatEleBalRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_row, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleBalRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {

            ele_row = (long)RDB[ele + ADER_MAT_ELE_BAL_ROW_ID];

            sprintf(print_data, "Element H found but has bad row of %ld.\n",
                    ele_row);

            if(ele_row == 9)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleControl()
{
    char *const test_name = "ADERSetMatEleControl";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleControl.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element Li not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 3)
        {

            sprintf(print_data, "Element Li found but has bad control indicator of 0.\n");

            if((long)RDB[ele + ADER_MAT_ELE_CONTROL_FLAG] > 0)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleDelColId()
{
    char *const test_name = "ADERSetMatEleDelColId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_col, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleDelColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {


            ele_col = (long)RDB[ele + ADER_MAT_ELE_DEL_COL_ID];

            sprintf(print_data, "Element H found but has bad column of %ld.\n",
                    ele_col);

            if(ele_col == 18)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleDelColPtr()
{
    char *const test_name = "ADERSetMatEleDelColPtr";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long ele, ele_col, ele_col_ptr, ele_z, mat, mat_ader_data;
    long mat_matrix_data, mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatEleDelColPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {


            ele_col = (long)RDB[ele + ADER_MAT_ELE_DEL_COL_ID];

            sprintf(print_data, "Element H found but has bad column ptr.\n");

            mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

            mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

            for(i = 0; i < ele_col; i++)
            {

                mat_matrix_col = NextItem(mat_matrix_col);

            }

            ele_col_ptr = (long)RDB[ele + ADER_MAT_ELE_MATRIX_DEL_COL_PTR];

            if(ele_col_ptr == mat_matrix_col)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleDelRowId()
{
    char *const test_name = "ADERSetMatEleDelRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_row, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleDelRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {

            ele_row = (long)RDB[ele + ADER_MAT_ELE_DEL_ROW_ID];

            sprintf(print_data, "Element H found but has bad row of %ld.\n",
                    ele_row);

            if(ele_row == 10)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleFutColId()
{
    char *const test_name = "ADERSetMatEleFutColId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_col, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleFutColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {


            ele_col = (long)RDB[ele + ADER_MAT_ELE_FUT_COL_ID];

            sprintf(print_data, "Element H found but has bad column of %ld.\n",
                    ele_col);

            if(ele_col == 19)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleFutColPtr()
{
    char *const test_name = "ADERSetMatEleFutColPtr";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long ele, ele_col, ele_col_ptr, ele_z, mat, mat_ader_data;
    long mat_matrix_data, mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatEleDelColPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {


            ele_col = (long)RDB[ele + ADER_MAT_ELE_FUT_COL_ID];

            sprintf(print_data, "Element H found but has bad column ptr.\n");

            mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

            mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

            for(i = 0; i < ele_col; i++)
            {

                mat_matrix_col = NextItem(mat_matrix_col);

            }

            ele_col_ptr = (long)RDB[ele + ADER_MAT_ELE_MATRIX_FUT_COL_PTR];

            if(ele_col_ptr == mat_matrix_col)
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleFutRowId()
{
    char *const test_name = "ADERSetMatEleFutRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_row, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleFutRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {

            ele_row = (long)RDB[ele + ADER_MAT_ELE_FUT_ROW_ID];

            sprintf(print_data, "Element H found but has bad row of %ld.\n",
                    ele_row);

            if(ele_row == 11)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleIsoAderMatIsoPtr()
{
    char *const test_name = "ADERSetMatEleIsoAderMatIsoPtr";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_iso, ele_z, mat, mat_ader_data, mat_iso, iso, nuc;

    fprintf(outp, "Begin: Test_ADERSetMatEleIsoAderMatIsoPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element Li not found in FLiBeFuel ADER ele list.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 3)
        {


            ele_iso = (long)RDB[ele + ADER_MAT_ELE_ISOS_PTR];

            sprintf(print_data, "Element Li found but has no isotopes.\n");

            while(ele_iso > VALID_PTR)
            {

                sprintf(print_data, "Element Li found but has no Li-6.\n");

                mat_iso = (long)RDB[ele_iso + ADER_MAT_ELE_ISO_ADER_MAT_ISO_PTR];

                iso = (long)RDB[mat_iso + ADER_MAT_ISO_PTR];

                nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

                if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
                {

                    memset(print_data, 0, strlen(print_data));

                    boolean = 1;

                    break;

                }

                ele_iso = NextItem(ele_iso);

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatEleIsoRowId()
{
    char *const test_name = "ADERSetMatEleIsoRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long ele, ele_row, ele_z, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatEleIsoRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Element H not found in material FLiBeFuel.\n");

    ele = (long)RDB[mat_ader_data + ADER_MAT_ELES_PTR];

    while(ele > VALID_PTR)
    {

        ele_z = (long)RDB[ele + ADER_MAT_ELE_Z];

        if(ele_z == 1)
        {

            ele_row = (long)RDB[ele + ADER_MAT_ELE_ISO_ROW_ID];

            sprintf(print_data, "Element H found but has bad row of %ld.\n",
                    ele_row);

            if(ele_row == 12)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        ele = NextItem(ele);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}


int Test_ADERSetMatIsoBalRowId()
{
    char *const test_name = "ADERSetMatIsoBalRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, iso_row, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatIsoBalRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_row = (long)RDB[iso + ADER_MAT_ISO_BAL_ROW_ID];

    sprintf(print_data, "First isotope has bad column of %ld.\n", iso_row);

    if(iso_row == (9 + (NUMBER_OF_ELEMENTS * 4)))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoControl()
{
    char *const test_name = "ADERSetMatEleControl";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, mat, mat_ader_data, mat_iso, nuc;

    fprintf(outp, "Begin: Test_ADERSetMatEleControl.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "Isotope Pu-239 not found in material FLiBeFuel.\n");

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(iso > VALID_PTR)
    {

        mat_iso = (long)RDB[iso + ADER_MAT_ISO_PTR];

        nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

        if((long)RDB[nuc + NUCLIDE_ZAI] == 942390)
        {

            sprintf(print_data, "Isotope Pu-239 found but has bad control indicator of 0.\n");

            if((long)RDB[iso + ADER_MAT_ISO_CONTROL_FLAG] > 0)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        iso = NextItem(iso);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoDelColId()
{
    char *const test_name = "ADERSetMatIsoDelColId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, iso_col, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatIsoDelColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_col = (long)RDB[iso + ADER_MAT_ISO_DEL_COL_ID];

    sprintf(print_data, "First isotope has bad column of %ld.\n", iso_col);

    if(iso_col == (18 + (2 * NUMBER_OF_ELEMENTS)))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoDelColPtr()
{
    char *const test_name = "ADERSetMatIsoDelColPtr";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long iso, iso_col, iso_col_ptr, mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatIsoDelColPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_col = (long)RDB[iso + ADER_MAT_ISO_DEL_COL_ID];

    sprintf(print_data, "First isotope has bad column ptr.\n");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    iso_col_ptr = (long)RDB[iso + ADER_MAT_ISO_MATRIX_DEL_COL_PTR];

    if(iso_col_ptr == mat_matrix_col)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoDelRowId()
{
    char *const test_name = "ADERSetMatIsoDelRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, iso_row, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatIsoDelRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_row = (long)RDB[iso + ADER_MAT_ISO_DEL_ROW_ID];

    sprintf(print_data, "First isotope has bad column of %ld.\n", iso_row);

    if(iso_row == (10 + (NUMBER_OF_ELEMENTS * 4)))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoFutColId()
{
    char *const test_name = "ADERSetMatIsoFutColId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, iso_col, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatIsoFutColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_col = (long)RDB[iso + ADER_MAT_ISO_FUT_COL_ID];

    sprintf(print_data, "First isotope has bad column of %ld.\n", iso_col);

    if(iso_col == (19 + (2 * NUMBER_OF_ELEMENTS)))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoFutColPtr()
{
    char *const test_name = "ADERSetMatIsoFutColPtr";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    int i;
    long iso, iso_col, iso_col_ptr, mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_col;

    fprintf(outp, "Begin: Test_ADERSetMatIsoFutColPtr.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_col = (long)RDB[iso + ADER_MAT_ISO_FUT_COL_ID];

    sprintf(print_data, "First isotope has bad column ptr.\n");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < iso_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    iso_col_ptr = (long)RDB[iso + ADER_MAT_ISO_MATRIX_FUT_COL_PTR];

    if(iso_col_ptr == mat_matrix_col)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatIsoFutRowId()
{
    char *const test_name = "ADERSetMatIsoFutRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long iso, iso_row, mat, mat_ader_data;

    fprintf(outp, "Begin: Test_ADERSetMatIsoFutRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    iso_row = (long)RDB[iso + ADER_MAT_ISO_FUT_ROW_ID];

    sprintf(print_data, "First isotope has bad column of %ld.\n", iso_row);

    if(iso_row == (11 + (NUMBER_OF_ELEMENTS * 4)))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatKMaxRowBounds()
{
    char *const test_name = "ADERSetMatKMaxRowBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double k_max_row_lower_bound, k_max_row_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_rows;
    long mat_matrix_row, mat_rho_max_row;

    fprintf(outp, "Begin: Test_ADERSetMatKMaxRowBounds.\n");

    /*Clear the print_data */
    sprintf(print_data, "No matrix data for material FLiBeFuel.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_rho_max_row = (long)RDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID];

    if(mat_matrix_data > VALID_PTR)
    {

        mat_matrix_rows = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS];

        mat_matrix_row = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

        for(i = 0; i < mat_rho_max_row; i++)
        {

            mat_matrix_row = NextItem(mat_matrix_row);

        }

        k_max_row_lower_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

        k_max_row_upper_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

        sprintf(print_data, "K max row, row %ld, has bad bounds of %f \n \
and %f for lower and upper bounds respectively.\n", (mat_matrix_rows - 3),
                k_max_row_lower_bound, k_max_row_upper_bound);

        if((k_max_row_lower_bound == 0) &&
           (k_max_row_upper_bound > 1E+17))
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));
        }

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatKMaxRowId()
{
    char *const test_name = "ADERSetMatKMaxRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_iso, mat_matrix_data, mat_rho_max_row;
    long mat_num_isos = 0;

    fprintf(outp, "Begin: Test_ADERSetMatKMaxRowId.\n");

    /*Clear the print_data */
    sprintf(print_data, "Rho max row for material FLiBeFuel has bad row id.");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_num_isos++;

        mat_iso = NextItem(mat_iso);

    }

    mat_rho_max_row = (long)RDB[mat_ader_data + ADER_MAT_RHO_MAX_ROW_ID];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    sprintf(print_data, "Rho max row for material FLiBeFuel has bad row of %ld \n\
with expected row of %ld.\n",
            mat_rho_max_row, ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 4));

    if(mat_rho_max_row == ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 4))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatKMinRowBounds()
{
    char *const test_name = "ADERSetMatKMinRowBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double k_min_row_lower_bound, k_min_row_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_rows;
    long mat_matrix_row, mat_rho_min_row;

    fprintf(outp, "Begin: Test_ADERSetMaKMinRowBounds.\n");

    /*Clear the print_data */
    sprintf(print_data, "No matrix data for material FLiBeFuel.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_rho_min_row = (long)RDB[mat_ader_data + ADER_MAT_RHO_MIN_ROW_ID];

    if(mat_matrix_data > VALID_PTR)
    {

        mat_matrix_rows = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS];

        mat_matrix_row = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

        for(i = 0; i < mat_rho_min_row; i++)
        {

            mat_matrix_row = NextItem(mat_matrix_row);

        }

        k_min_row_lower_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

        k_min_row_upper_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

        sprintf(print_data, "K min row, row %ld, has bad lower bound of %f \n \
or bad upper bound of %f.\n",
                (mat_matrix_rows - 2),
                k_min_row_lower_bound,
                k_min_row_upper_bound);

        if((k_min_row_lower_bound < -1E+17) && (k_min_row_upper_bound == 0))
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));
        }

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatKMinRowId()
{
    char *const test_name = "ADERSetMatKMinRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_iso, mat_matrix_data, mat_rho_min_row;
    long mat_num_isos = 0;

    fprintf(outp, "Begin: Test_ADERSetMatKMinRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_num_isos++;

        mat_iso = NextItem(mat_iso);

    }

    mat_rho_min_row = (long)RDB[mat_ader_data + ADER_MAT_RHO_MIN_ROW_ID];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    sprintf(print_data, "Rho min row for material FLiBeFuel has bad row of %ld \n\
with expected row of %ld.\n",
            mat_rho_min_row, ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 3));

    if(mat_rho_min_row == ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 3))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjGroup()
{
    char *const test_name = "ADERSetMatObjGroup";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_cmp_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_cmp, mat_cmp_target_col, mat_matrix_data;
    long mat_matrix_col, mat_matrix_row, mat_opt;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjGroup.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no cmp groups.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_cmp = (long)RDB[mat_ader_data + ADER_MAT_CMPS_PTR];

    while(mat_cmp > VALID_PTR)
    {

        mat_cmp_name = GetText(mat_cmp + ADER_MAT_CMP_ID);

        if(strncmp("FLiBe", mat_cmp_name, 4) == 0)
        {

            mat_cmp_target_col = (long)RDB[mat_cmp + ADER_MAT_CMP_COL_ID];

            break;

        }

        mat_cmp = NextItem(mat_cmp);

    }

    /* Here we modify the optimization settings */

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("group");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("FLiBe");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_cmp_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value 1.0.\n",
            mat_cmp_target_col, RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

    if(RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.99999999 &&
       RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.00000001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjFeed()
{
    char *const test_name = "ADERSetMatObjFeed";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff, src_mat_adens;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjFeed.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Argon40 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", mat_stream_name, 4) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel not found");

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Get the matrix material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 7) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no matrix data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Save FLiBeFuel's adens for later                                       */

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    src_mat_adens = RDB[mat + MATERIAL_ADENS];

    /* Get the target value                                                   */

    adens_corr_factor = parent_mat_adens / src_mat_adens;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("feed");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
            RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
            adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
                    adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjFeedAndRemoval()
{
    char *const test_name = "ADERSetMatObjFeedAndRemoval";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff, src_mat_adens;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjFeedAndRemoval.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Argon40 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", mat_stream_name, 4) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel not found.\n");

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Get the matrix material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 7) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no matrix data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    src_mat_adens = RDB[mat + MATERIAL_ADENS];

    adens_corr_factor = parent_mat_adens / src_mat_adens;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("feed_and_remv");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
			RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
			adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		        adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjReac()
{
    char *const test_name = "ADERSetMatObjReac";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff, src_mat_adens;
    int append = 0;
    int boolean = 0;
    long ader_mat_stream_shadow, ader_mat_stream_src_mat;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjReac.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REAC_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("U233", mat_stream_name, 4) == 0)
        {

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            ader_mat_stream_shadow = (long)RDB[mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

            src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

            adens_corr_factor = src_mat_adens / parent_mat_adens;

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("reac");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
			RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
			adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		        adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjRedox()
{
    char *const test_name = "ADERSetMatObjRedox";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff, src_mat_adens;
    int append = 0;
    int boolean = 0;
    long ader_mat_stream_shadow, ader_mat_stream_src_mat;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjRedox.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    parent_mat_adens = RDB[mat + MATERIAL_ADENS];

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("Fluorine", mat_stream_name, 8) == 0)
        {

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            ader_mat_stream_shadow = (long)RDB[mat_stream + ADER_MAT_STREAM_SHADOW_PTR];

            ader_mat_stream_src_mat = (long)RDB[ader_mat_stream_shadow + ADER_MAT_STREAM_MAT_PTR];

            src_mat_adens = RDB[ader_mat_stream_src_mat + MATERIAL_ADENS];

            adens_corr_factor = src_mat_adens / parent_mat_adens;

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("redox");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
			RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
			adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		        adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjRemoval()
{
    char *const test_name = "ADERSetMatObjRemoval";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col, parent_mat;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjRemoval.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material Fluorine0 not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine0", mat_name, 9) == 0)
        {

            sprintf(print_data, "Fluorine0 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the parent mat adens and get the adens corr factor                 */

    parent_mat = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    parent_mat_adens = RDB[parent_mat + MATERIAL_ADENS];

    adens_corr_factor = RDB[mat + MATERIAL_ADENS] / parent_mat_adens;

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("Fluorine", mat_stream_name, 8) == 0)
        {

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Get FLiBeFuel to get the matrix data                                   */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no matrix data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("remv");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
			RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
			adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		        adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.00001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjStream()
{
    char *const test_name = "ADERSetMatObjStream";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_col, mat_matrix_row, mat_opt, mat_stream;
    long mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjStream.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("Beryllium", mat_stream_name, 9) == 0)
        {

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Here we modify the optimization settings */

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("spec_stream");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("Beryllium");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value 1.0.\n",
            mat_stream_target_col, RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

    if(RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.99999999 &&
       RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.00000001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjStreams()
{
    char *const test_name = "ADERSetMatObjStreams";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_col, mat_matrix_row, mat_opt, mat_stream;
    long mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjStreams.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", mat_stream_name, 5) == 0)
        {

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Here we modify the optimization settings */

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("streams");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value 1.0.\n",
            mat_stream_target_col, RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY]);

    if(RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] > 0.99999999 &&
       RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] < 1.00000001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatObjTransfers()
{
    char *const test_name = "ADERSetMatObjTransfers";
    char status[5];
    char print_data[256];
    char *mat_name, *mat_stream_name;
    double adens_corr_factor, parent_mat_adens, percent_diff, src_mat_adens;
    int append = 0;
    int boolean = 0;
    long ader_mat_parent;
    long mat, mat_ader_data, mat_matrix_data, mat_matrix_col, mat_matrix_row;
    long mat_opt, mat_stream, mat_stream_target_col;
    long i;

    fprintf(outp, "Begin: Test_ADERSetMatObjTransfers.\n");

    /* Execution of the Obj row tests requires manipulation of the WDB array */
    /* directly to avoid an overly complicated input file                    */

    /*Clear the print_data */
    sprintf(print_data, "Material Fluorine0 not found");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Fluorine0", mat_name, 9) == 0)
        {

            sprintf(print_data, "Fluorine0 has no streams.\n");

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Get the parent adens                                                   */

    ader_mat_parent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_PARENT_PTR];

    parent_mat_adens = RDB[ader_mat_parent + MATERIAL_ADENS];

    /* Get the adens_corr_factor                                              */

    src_mat_adens = RDB[mat + MATERIAL_ADENS];

    adens_corr_factor = src_mat_adens / parent_mat_adens;

    /* Get the target stream and retrieve its column index */

    mat_stream = (long)RDB[mat_ader_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(mat_stream > VALID_PTR)
    {

        mat_stream_name = GetText(mat_stream + ADER_MAT_STREAM_ID);

        if(strncmp("Fluorine", mat_stream_name, 8) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel not found");

            mat_stream_target_col = (long)RDB[mat_stream + ADER_MAT_STREAM_COL_ID];

            break;

        }

        mat_stream = NextItem(mat_stream);

    }

    /* Get the matrix material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "FLiBeFuel has no matrix data.\n");

            break;

        }

        mat = NextItem(mat);

    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }


    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("action");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("transfers");

    ADERFillMaterialCompMatrixObjRow(mat);

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    for(i = 0; i < mat_stream_target_col; i++)
    {

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

    sprintf(print_data, "FLiBeFuel matrix column %ld final row has value %f and needs value %f.\n",
            mat_stream_target_col,
			RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY],
			adens_corr_factor);

    percent_diff = (RDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] -
    		        adens_corr_factor) / adens_corr_factor;

    if(fabs(percent_diff) < 0.0001)
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    /* Here we re-reset the objective row so that future tests can rely on the*/
    /* input file                                                             */

    /* Here we modify the optimization settings */

    mat_opt = (long)RDB[mat_ader_data + ADER_MAT_OPT_PTR];

    WDB[mat_opt + ADER_MAT_OPT_TYPE] = (double)PutText("spec_stream");

    WDB[mat_opt + ADER_MAT_OPT_TYPE_TARGET] = (double)PutText("Beryllium");

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    /* Here we wipe the old objective row */

    mat_matrix_col = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_COLS_PTR];

    while(mat_matrix_col > VALID_PTR)
    {

        mat_matrix_row = LastItem((long)RDB[mat_matrix_col + ADER_MAT_MATRIX_COL_ROWS_PTR]);

        WDB[mat_matrix_row + ADER_MAT_MATRIX_COL_ROW_ENTRY] = 0.0;

        mat_matrix_col = NextItem(mat_matrix_col);

    }

    ADERFillMaterialCompMatrixObjRow(mat);

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatOxiRowBounds()
{
    char *const test_name = "ADERSetMatOxiRowBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double oxi_row_lower_bound, oxi_row_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_row, mat_oxi_data, mat_oxi_row;

    fprintf(outp, "Begin: Test_ADERSetMatOxiRowBounds.\n");

    /*Clear the print_data */
    sprintf(print_data, "No matrix data for material FLiBeFuel.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_oxi_data = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    mat_oxi_row = (long)RDB[mat_oxi_data + ADER_MAT_OXI_ROW_ID];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    sprintf(print_data, "Oxi row for material FLiBeFuel has bad row of %ld \n\
with max number of rows %ld.\n",
            mat_oxi_row, (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS]);

    if(mat_matrix_data > VALID_PTR)
    {

        mat_matrix_row = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

        for(i = 0; i < mat_oxi_row; i++)
        {

            mat_matrix_row = NextItem(mat_matrix_row);

        }

        oxi_row_lower_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

        oxi_row_upper_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

        sprintf(print_data, "Oxi row, row %ld, has bad bounds of %f \n \
and %f for lower and upper bounds respectively.\n", mat_oxi_row,
                oxi_row_lower_bound, oxi_row_upper_bound);

        if((oxi_row_lower_bound > -0.00000001) && (oxi_row_lower_bound < 0.00000001) &&
           (oxi_row_upper_bound > 0.00099999) && (oxi_row_upper_bound < 0.00100001))
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));
        }

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatOxiRowId()
{
    char *const test_name = "ADERSetMatOxiRowId";
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_iso, mat_matrix_data, mat_oxi_data, mat_oxi_row;
    long mat_num_isos = 0;

    fprintf(outp, "Begin: Test_ADERSetMatOxiRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_num_isos++;

        mat_iso = NextItem(mat_iso);

    }

    mat_oxi_data = (long)RDB[mat_ader_data + ADER_MAT_OXI_PTR];

    mat_oxi_row = (long)RDB[mat_oxi_data + ADER_MAT_OXI_ROW_ID];

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    sprintf(print_data, "FLiBeFuel Oxi has bad row of %ld.\n", mat_oxi_row);

    if(mat_oxi_row == ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 5))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatParentMPINum()
{
    char *const test_name = "ADERSetMatParentMPINum";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_mpi_num;

    fprintf(outp, "Begin: Test_ADERSetMatParentMPINum.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found.\n");

    /* Get the material*/

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }


    sprintf(print_data, "Material FLiBeFuel has bad MPI number.\n");

    mat_mpi_num = (long)RDB[mat + MATERIAL_MPI_ID];

    if(mat_mpi_num == 0)
    {

        boolean = 1;

        sprintf(print_data, "WARNING!!!: NOT TESTED ON PARALLEL PLATFORM.\n");

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }

}

int Test_ADERSetMatPreserveRowBounds()
{
    char *const test_name = "ADERSetMatPreserveRowBounds";
    char status[5];
    char print_data[256];
    char *mat_name;
    double pres_row_lower_bound, pres_row_upper_bound;
    int append = 0;
    int boolean = 0;
    int i;
    long mat, mat_ader_data, mat_matrix_data;
    long mat_matrix_row, mat_pres_row, mat_preserve_ent;

    fprintf(outp, "Begin: Test_ADERSetMatPreserveRowBounds.\n");

    /*Clear the print_data */
    sprintf(print_data, "No matrix data for material FLiBeFuel.\n");

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_preserve_ent = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

    while(mat_preserve_ent > VALID_PTR)
    {

        if(strncmp("mols", GetText(mat_preserve_ent + ADER_MAT_PRESERVE_ENT), 4) == 0)
        {

            mat_pres_row = (long)RDB[mat_preserve_ent + ADER_MAT_PRESERVE_ROW_ID];

            break;

        }

        mat_preserve_ent = NextItem(mat_preserve_ent);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    sprintf(print_data, "Preserve row for material FLiBeFuel has bad row of %ld \n\
with max number of rows %ld.\n",
            mat_pres_row, (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS]);

    if(mat_matrix_data > VALID_PTR)
    {

        mat_matrix_row = (long)RDB[mat_matrix_data + ADER_MAT_MATRIX_ROW_BOUNDS_PTR];

        for(i = 0; i < mat_pres_row; i++)
        {

            mat_matrix_row = NextItem(mat_matrix_row);

        }

        pres_row_lower_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_LOWER_BOUND];

        pres_row_upper_bound = RDB[mat_matrix_row + ADER_MAT_MATRIX_ROW_UPPER_BOUND];

        sprintf(print_data, "Preserve row, row %ld, has bad bounds of %f \n \
and %f for lower and upper bounds respectively.\n", mat_pres_row,
                pres_row_lower_bound, pres_row_upper_bound);

        if((pres_row_lower_bound > -0.00000001) && (pres_row_lower_bound < 0.00000001) &&
           (pres_row_upper_bound > -0.00000001) && (pres_row_lower_bound < 0.00000001))
        {

            boolean = 1;

            memset(print_data, 0, strlen(print_data));

        }

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatPreserveRowId()
{
    char *const test_name = "ADERSetMatPreserveRowId";
    char *mat_name;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, mat_iso, mat_matrix_data;
    long mat_preserve_ent, mat_preserve_row;
    long mat_num_isos = 0;

    fprintf(outp, "Begin: Test_ADERSetMatPreserveRowId.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material FLiBeFuel not found. \n");

    /* Get the first test group */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_iso = (long)RDB[mat_ader_data + ADER_MAT_ISOS_PTR];

    while(mat_iso > VALID_PTR)
    {

        mat_num_isos++;

        mat_iso = NextItem(mat_iso);

    }

    mat_matrix_data = (long)RDB[mat_ader_data + ADER_MAT_MATRIX_PTR];

    mat_preserve_ent = (long)RDB[mat_ader_data + ADER_MAT_PRESERVES_PTR];

    while(mat_preserve_ent > VALID_PTR)
    {

        if(strncmp("mols", GetText(mat_preserve_ent + ADER_MAT_PRESERVE_ENT), 4) == 0)
        {

            mat_preserve_row = (long)RDB[mat_preserve_ent + ADER_MAT_PRESERVE_ROW_ID];

            break;

        }

        mat_preserve_ent = NextItem(mat_preserve_ent);

    }

    sprintf(print_data, "FLiBeFuel Preserve has bad row of %ld with needed row of %ld.\n",
            mat_preserve_row,
            ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 2));

    if(mat_preserve_row == ((long)RDB[mat_matrix_data + ADER_MAT_MATRIX_NUM_ROWS] - 1 - 12 * NUMBER_OF_ELEMENTS - 9 * mat_num_isos - 2))
    {

        boolean = 1;

        memset(print_data, 0, strlen(print_data));

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmColId()
{
    char *const test_name = "ADERSetMatStrmColId";
    char *strm_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_col;

    fprintf(outp, "Begin: Test_ADERSetMatStrmColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "FLiBe feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("FLiBe", strm_name, 5) == 0)
        {

            strm_col = (long)RDB[strm + ADER_MAT_STREAM_COL_ID];

            sprintf(print_data, "FLiBe feed stream found but has bad column of %ld.\n",
                    strm_col);

            if(strm_col == 5)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmShadowColId()
{
    char *const test_name = "ADERSetMatStrmShadowColId";
    char *mat_name, *strm_id;
    char status[5], print_data[256];
    int append = 0;
    int boolean = 0;
    long col, mat, mat_ader_data, strm;

    fprintf(outp, "Begin: Test_ADERSetMatStrmShadowColId.\n");

    /*Clear the print_data */
    sprintf(print_data, "Material Argon40 not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            sprintf(print_data, "Material Argon40 has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "Argon40 has no reproc stream.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            col = (long)RDB[strm + ADER_MAT_STREAM_COL_ID];

            break;

        }

        strm = NextItem(strm);

    }

    sprintf(print_data, "Material FLiBeFuel not found. \n");

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {
        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            sprintf(print_data, "Material FLiBeFuel has no streams.\n");

            break;

        }

        mat = NextItem(mat);
    }

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    strm = (long)RDB[mat_ader_data + ADER_MAT_REMV_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        sprintf(print_data, "FLiBeFuel has no reproc stream.\n");

        strm_id = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("reproc", strm_id, 6) == 0)
        {

            sprintf(print_data, "Mismatch between Argon40 col, %ld, \n \
and FLiBeFuel reproc col of %ld.\n", col, (long)RDB[strm + ADER_MAT_STREAM_COL_ID]);

            if(col == (long)RDB[strm + ADER_MAT_STREAM_COL_ID])
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);
    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmShadowSumColId()
{
    char *const test_name = "ADERSetMatStrmShadowSumColId";
    char *strm_name, *strm_sum_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, shadow_sum_strm_col, strm, strm_sum, strm_sum_ent;

    fprintf(outp, "Begin: Test_ADERSetMatStrmShadowSumColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "ActF feed stream found but has no sum streams.\n");

            strm_sum_ent = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(strm_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "ActF feed stream sum streams found but has no sum stream 'Uranium'.\n");

                strm_sum_name = GetText(strm_sum_ent + ADER_MAT_GRP_SUM_GRP_ID);

                if(strncmp("Uranium", strm_sum_name, 7) == 0)
                {

                    strm_sum = (long)RDB[strm_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    sprintf(print_data, "Argon40 material not found.\n");

                    shadow_sum_strm_col = (long)RDB[strm_sum + ADER_MAT_STREAM_COL_ID];

                    break;

                }

                strm_sum_ent = NextItem(strm_sum_ent);

            }

            break;

        }

        strm = NextItem(strm);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material Argon40.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "ActF feed stream found but has no sum streams.\n");

            strm_sum_ent = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(strm_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "ActF feed stream sum streams found but has no sum stream 'Uranium'.\n");

                strm_sum_name = GetText(strm_sum_ent + ADER_MAT_GRP_SUM_GRP_ID);

                if(strncmp("Uranium", strm_sum_name, 7) == 0)
                {

                    strm_sum = (long)RDB[strm_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    sprintf(print_data, "Argon40 ActF feed stream sum group 'Uranium' has column %ld \n\
while ActF removal stream sum group Uranium in FLiBeFuel has column %ld.\n",
                            (long)RDB[strm_sum + ADER_MAT_STREAM_COL_ID],
                            shadow_sum_strm_col);

                    if((long)RDB[strm_sum + ADER_MAT_STREAM_COL_ID] == shadow_sum_strm_col)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;

                }

                strm_sum_ent = NextItem(strm_sum_ent);

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmShadowSumRowId()
{
    char *const test_name = "ADERSetMatStrmShadowSumRowId";
    char *strm_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, shadow_sum_row, strm;

    fprintf(outp, "Begin: Test_ADERSetMatStrmShadowSumRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "Argon40 material not found.\n");

            shadow_sum_row = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_ROW_ID];

            break;

        }

        strm = NextItem(strm);

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("Argon40", mat_name, 7) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material Argon40.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

            sprintf(print_data, "Argon40 ActF feed stream found but has sum row of %ld\n \
while FLiBeFuel ActF removal stream has sum row of %ld.\n",
                    (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_ROW_ID],
                    shadow_sum_row);

            if(shadow_sum_row == (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_ROW_ID])
            {

                boolean = 1;

                memset(print_data, 0, strlen(print_data));

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmSumColId()
{
    char *const test_name = "ADERSetMatStrmSumColId";
    char *strm_name, *strm_sum_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_sum, strm_sum_ent;

    fprintf(outp, "Begin: Test_ADERSetMatStrmSumColId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

        	if(strcmp("NULL", GetText(strm + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		strm = NextItem(strm);

        		continue;

        	}

            sprintf(print_data, "ActF feed stream found but has no sum streams.\n");

            strm_sum_ent = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_PTR];

            while(strm_sum_ent > VALID_PTR)
            {

                sprintf(print_data, "ActF feed stream sum streams found but has no sum stream 'Uranium'.\n");

                strm_sum_name = GetText(strm_sum_ent + ADER_MAT_GRP_SUM_GRP_ID);

                if(strncmp("Uranium", strm_sum_name, 7) == 0)
                {

                    strm_sum = (long)RDB[strm_sum_ent + ADER_MAT_GRP_SUM_GRP_PTR];

                    sprintf(print_data, "Uranium sum stream found but has bad column of %ld.\n",
                            (long)RDB[strm_sum + ADER_MAT_STREAM_COL_ID]);

                    if((long)RDB[strm_sum + ADER_MAT_STREAM_COL_ID] == 8254)
                    {

                        boolean = 1;

                        memset(print_data, 0, strlen(print_data));

                    }

                    break;

                }

                strm_sum_ent = NextItem(strm_sum_ent);

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_ADERSetMatStrmSumRowId()
{
    char *const test_name = "ADERSetMatStrmSumRowId";
    char *strm_name;
    char status[5];
    char print_data[256];
    char *mat_name;
    int append = 0;
    int boolean = 0;
    long mat, mat_ader_data, strm, strm_sum_row;

    fprintf(outp, "Begin: Test_ADERSetMatStrmSumRowId.\n");

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* Get the test material */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        mat_name = GetText(mat + MATERIAL_PTR_NAME);

        if(strncmp("FLiBeFuel", mat_name, 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Get material ADER data */
    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    sprintf(print_data, "ActF feed stream not found in material FLiBeFuel.\n");

    strm = (long)RDB[mat_ader_data + ADER_MAT_FEED_STREAMS_PTR];

    while(strm > VALID_PTR)
    {

        strm_name = GetText(strm + ADER_MAT_STREAM_ID);

        if(strncmp("ActF", strm_name, 4) == 0)
        {

        	if(strcmp("NULL", GetText(strm + ADER_MAT_STREAM_SRC)) == 0)
        	{

        		strm = NextItem(strm);

        		continue;

        	}

            strm_sum_row = (long)RDB[strm + ADER_MAT_STREAM_SUM_GRPS_ROW_ID];

            sprintf(print_data, "ActF feed stream found but has bad row of %ld.\n",
                    strm_sum_row);

            if(strm_sum_row == 12694)
            {

                memset(print_data, 0, strlen(print_data));

                boolean = 1;

            }

            break;

        }

        strm = NextItem(strm);

    }

    if (boolean == 1)
    {
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else
    {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}

int Test_RunTests()
{
    char *const test_name = "RunTests";
    const char *const expect = "Hello World!";
    const char *const test_value = "Hello World!";
    char status[5];
    char print_data[256];
    int append = 0;

    fprintf(outp, "Begin: Test_RunTests.\n");

    memset(print_data, 0, strlen(print_data));

    if (strncmp(expect, test_value, 12) == 0){
        strcpy(status, "pass");
        PrintTest(test_name, status, print_data, append);
        return(1);
    }
    else {
        strcpy(status, "fail");
        PrintTest(test_name, status, print_data, append);
        return(-1);
    }
}
