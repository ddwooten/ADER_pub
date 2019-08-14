/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : testadermakeburnmatrix.c                       */
/*                                                                           */
/* Created:       2016/17/11 (DDW)                                           */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Tests 49 things. boolean variables for each test are given   */
/*                 following the text                                        */
/*              2. That proportional removal table streams in a single       */
/*                 material cluster in a zero flux environment give isotopes */
/*                 the correct lambda value - bl_nf_nc_ps_rt_ti_ro           */
/*              3. That an isotope in a zero flux environment has the correct*/
/*                 decay constant for itself - bl_nf_nc_iso_dy_ti_ro         */
/*              4. That proportional group type source streams in a material */
/*                 cluster in a zero flux environment give isotopes the      */
/*                 correct lambda value - bl_nf_cl_ps_gt_ss_ti_ro            */
/*              5. That proportional group type source streams in a material */
/*                 cluster in a zero flux environment give isotopes the      */
/*                 correct lambda value - bl_nf_cl_ps_gt_sd_ti_ro            */
/*              6. That continuous group type streams do not give themselves */
/*                 any self referential data in a non-cluster material -     */
/*                 bl_fx_nc_cs_gt_ts                                         */
/*              8. That proportional removal table streams do not give       */
/*                 themselves any self referential data in a non-cluster     */
/*                 material - bl_fx_nc_ps_rt_ts                              */
/*              9. That continuous removal table streams do not give         */
/*                 themselves any self referential data in a non-cluster     */
/*                 material - bl_fx_nc_cs_rt_ts                              */
/*             10. That isotopes in a continuous group type stream do not    */
/*                 populate the stream row in a non-cluster material -       */
/*                 bl_fx_nc_iso_ts_cs_gt_ro                                  */
/*             11. That isotopes in a continuous removal table stream do not */
/*                 populate the stream row in a non-cluster material -       */
/*                 bl_fx_nc_iso_ts_cs_rt_ro                                  */
/*             14. That isotopes in a proportional removal table stream do   */
/*                 not receive contributions from the stream column in a     */
/*                 non-cluster material - bl_fx_nc_iso_ts_ps_rt_co           */
/*             15. That isotopes in a proportional removal table stream do   */
/*                 not populate the stream row in a non-cluster material -   */
/*                 bl_fx_nc_iso_ts_ps_rt_ro                                  */
/*             16. That continuous group type streams in a non-cluster       */
/*                 material give their isotopes the proper rate information  */
/*                  - bl_fx_nc_cs_gt_ti_ro                                   */
/*             17. That continuous removal table streams in a non-cluster    */
/*                 material give their isotopes the proper rate information  */
/*                  - bl_fx_nc_cs_rt_ti_ro                                   */
/*             18. That continuous group type summation streams ( stream 1 ) */
/*                  provide the proper rate information to isotopes in a      */
/*                 non-cluster material - bl_fx_nc_cs_gt_sm_s1_ti_ro         */
/*             19. That continuous group type summation streams ( stream 2 ) */
/*                 provide the proper rate information to isotopes in a      */
/*                 non-cluster material - bl_fx_nc_cs_gt_sm_s2_ti_ro         */
/*             20. That isotopes in a non-clustered material do not          */
/*                 populate continuous group type first summation stream     */
/*                 rows - bl_fx_nc_iso_ts_cs_gt_sm_s1_ro                     */
/*             21. That isotopes in a non-clustered material do not          */
/*                 populate continuous group type second summation stream    */
/*                 rows - bl_fx_nc_iso_ts_cs_gt_sm_s2_ro                     */
/*             22. That continuous removal table streams give isotopes in a  */
/*                 cluster material the correct rate data -                  */
/*                 bl_fx_cl_cs_rt_ss_ti_ro                                   */
/*             23. That continuous removal table streams give isotopes in a  */
/*                 cluster material the correct rate data -                  */
/*                 bl_fx_cl_cs_rt_sd_ti_ro                                   */
/*             24. That continuous removal table streams do not give         */
/*                 themselves any self referential data in a clustered       */
/*                 material - bl_fx_cl_cs_rt_ts                              */
/*             25. That isotopes in a continuous removal table source side   */
/*                 stream do not populate the stream row in a clustered      */
/*                 material - bl_fx_cl_iso_ts_cs_rt_ss_ro                    */
/*             26. That isotopes in a continuous removal table destination   */
/*                 side stream do not populate the stream row in a clustered */
/*                 material - bl_fx_cl_iso_ts_cs_rt_sd_ro                    */
/*             27. That isotopes in a proportional group type destination    */
/*                 stream do not receive contributions from the stream column*/
/*                 in a clustered material - bl_fx_cl_iso_ts_ps_gt_sd_co     */
/*             28. That isotopes in a proportional group type source         */
/*                 stream do not receive contributions from the stream column*/
/*                 in a clustered material - bl_fx_cl_iso_ts_ps_gt_ss_co     */
/*             29. That isotopes in a proportional group type destination    */
/*                 side stream do not contribute rate information to the     */
/*                 proportional stream accumulation row in a clustered       */
/*                 material - bl_fx_cl_iso_ts_ps_gt_sd_ro                    */
/*             30. That isotopes in a proportional group type source         */
/*                 side stream do provide contribute rate information to the */
/*                 proportional stream accumulation row in a clustered       */
/*                 material - bl_fx_cl_iso_ts_ps_gt_ss_ro                    */
/*             31. That proportional group type streams do not give          */
/*                 themselves any self referential data in a clustered       */
/*                 material - bl_fx_cl_ps_gt_ts                              */
/*             32. That continuous group type first summation streams in     */
/*                 destination side materials in a material cluster give     */
/*                 isotopes the appropriate rate information -               */
/*                 bl_fx_cl_cs_gt_sm_s1_sd_ti_ro                             */
/*             33. That continuous group type first summation streams in     */
/*                 source side materials in a material cluster give          */
/*                 isotopes the appropriate rate information -               */
/*                 bl_fx_cl_cs_gt_sm_s1_ss_ti_ro                             */
/*             34. That continuous group type second summation streams in    */
/*                 destination side materials in a material cluster give     */
/*                 isotopes the appropriate rate information -               */
/*                 bl_fx_cl_cs_gt_sm_s2_sd_ti_ro                             */
/*             35. That continuous group type second summation streams in    */
/*                 source side materials in a material cluster give          */
/*                 isotopes the appropriate rate information -               */
/*                 bl_fx_cl_cs_gt_sm_s2_ss_ti_ro                             */
/*             36. That isotopes in destination side material in a material  */
/*                 cluster do not give continuous group type first summation */
/*                 streams any rate information -                            */
/*                 bl_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro                         */
/*             37. That isotopes in source side material in a material       */
/*                 cluster do not give continuous group type first summation */
/*                 streams any rate information -                            */
/*                 bl_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro                         */
/*             38. That isotopes in destination side material in a material  */
/*                 cluster do not give continuous group type second summation*/
/*                 streams any rate information -                            */
/*                 bl_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro                         */
/*             39. That isotopes in source side material in a material       */
/*                 cluster do not give continuous group type second summation*/
/*                 streams any rate information -                            */
/*                 bl_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro                         */
/*             40. That continuous group type destination side streams in a  */
/*                 clustered material give their isotopes the proper rate    */
/*                 information - bl_fx_cl_cs_gt_sd_ti_ro                     */
/*             41. That continuous group type source side streams in a       */
/*                 clustered material give their isotopes the proper rate    */
/*                 information - bl_fx_cl_cs_gt_ss_ti_ro                     */
/*             42. That continuous group type streams do not give themselves */
/*                 any self referential data in a clustered material -       */
/*                 bl_fx_cl_cs_gt_ts                                         */
/*             43. That isotopes populate production data for their          */
/*                 decay products - bl_fx_cl_iso_dp_ti_ro                    */
/*             44. That isotopes populate production data for their          */
/*                 fission products - bl_fx_cl_iso_fp_ti_ro                  */
/*             45. That isotopes populate production data for their          */
/*                 transmutation products - bl_fx_cl_iso_nt_ti_ro            */
/*             46. That isotopes in a continuous group type destination side */
/*                 stream do not populate the stream row in a clustered      */
/*                 material - bl_fx_cl_iso_ts_cs_gt_sd_ro                    */
/*             47. That isotopes in a continuous group type source side      */
/*                 stream do not populate the stream row in a clustered      */
/*                 material - bl_fx_cl_iso_ts_cs_gt_ss_ro                    */
/*             48. That isotopes in a proportional removal table destination */
/*                 side stream do not populate the stream column in a        */
/*                 clustered material - bl_fx_cl_iso_ts_ps_rt_sd_co          */
/*             49. That isotopes in a proportional removal table source      */
/*                 side stream do not populate the stream column in a        */
/*                 clustered material - bl_fx_cl_iso_ts_ps_rt_ss_co          */
/*             50. That isotopes in a proportional removal table destination */
/*                 side stream do not populate the stream row in a           */
/*                 clustered material - bl_fx_cl_iso_ts_ps_rt_sd_ro          */
/*             51. That isotopes in a proportional removal table source      */
/*                 side stream populate the stream row with the correct info */
/*                 in a clustered material - bl_fx_cl_iso_ts_ps_rt_ss_ro     */
/*             52. That proportional removal table destination side streams  */
/*                 in a clustered material give isotopes                     */
/*                 the correct lambda value - bl_fx_cl_ps_rt_sd_ti_ro        */
/*             53. That proportional removal table source side streams       */
/*                 in a clustered material give isotopes                     */
/*                 the correct lambda value - bl_fx_cl_ps_rt_ss_ti_ro        */
/*             54. That proportional removal table streams do not give       */
/*                 themselves any self referential data in a clustered       */
/*                 material - bl_fx_cl_ps_rt_ts                              */
/*                                                                           */
/* Comments: This function is called from ADERBurnMaterials                  */
/*           Below is a listing of acronyms used in variable naming          */
/*           bl - boolean                                                    */
/*           cl - part of a cluster                                          */
/*           co - column                                                     */
/*           cs - continuous type stream                                     */
/*           dp - decay product                                              */
/*           ds - discreet type stream                                       */
/*           dy - decay                                                      */
/*           fx - flux in the material                                       */
/*           fp - fission product                                            */
/*           gt - group type stream                                          */
/*           nc - NOT part of a multi-material cluster                       */
/*           nf - no flux in the material                                    */
/*           nt - transmutation reaction                                     */
/*           pd - percent difference                                         */
/*           ps - proportional type stream                                   */
/*           pv - pass value ( value for test to succeed )                   */
/*           ro - row                                                        */
/*           rt - removal table type stream                                  */
/*           s1 - first summation stream in a sum stream                     */
/*           s2 - second summation stream in a sum stream                    */
/*           sd - destination end of a shadow stream                         */
/*           sf - spontaneous fission                                        */
/*           sm - sub componenet of a summation based stream                 */
/*           ss - source end of a shadow stream                              */
/*           ti - to iso                                                     */
/*           ts - to stream                                                  */
/*           tv - test value                                                 */
/*                                                                           */
/*           Most tests will have four key variable associated with them.    */
/*           All tests will have a bl variable that might look something like*/
/*           bl_fx_nc_cs_rt_ti_ro which indicates that it is a boolean       */
/*           variable for a test with material flux for a material that is   */
/*           not part of a multi-material cluster for a continuous removal   */
/*           table based stream sending information to an isotope row. The   */
/*           other three variable will simply change out the bl portion for  */
/*           a tv, pv, and pd. Thus, with the boolean variable names above   */
/*           any of the named tests and their location in this file can be   */
/*           easily searched for.                                            */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "TESTADERMakeBurnMatrix:"

void TESTADERMakeBurnMatrix()
{

    char *const test_name = "ADERMakeBurnMatrix";
    char status[5];
    char print_data[1000];
    double **ader_burn_matrix_size_data;
    double *ader_burn_matrix_col_storage;
    double *ader_burn_matrix_num_ents, *ader_burn_matrix_num_rows;
    double *ader_burn_matrix_N0, *ader_burn_matrix_starts;
    double *ader_optimization_solution_array;
    double t1, t2, total_time;
    double fluorine1_flux, lithium7_flux, testtank_flux;
    long ader_data, ader_mat_data;
	long ader_mat_iso, ader_mat_matrix_data;
	long ader_mat_stream, ader_mat_stream_sum_stream;
	long ader_mat_stream_sum_stream_ent, ader_test_block, li6_lithium7_mat_iso;
	long mat, mat_iso, nuc;
    struct ccsMatrix *burn_matrix;
    double pd_fx_cl_cs_gt_sd_ti_ro = 0.0;
    double pd_fx_cl_cs_gt_sm_s1_sd_ti_ro = 0.0;
    double pd_fx_cl_cs_gt_sm_s1_ss_ti_ro = 0.0;
    double pd_fx_cl_cs_gt_sm_s2_sd_ti_ro = 0.0;
    double pd_fx_cl_cs_gt_sm_s2_ss_ti_ro = 0.0;
    double pd_fx_cl_cs_gt_ss_ti_ro = 0.0;
    double pd_fx_cl_cs_rt_sd_ti_ro = 0.0;
    double pd_fx_cl_cs_rt_ss_ti_ro = 0.0;
    double pd_fx_cl_iso_ts_ps_gt_ss_ro = 0.0;
    double pd_fx_cl_iso_ts_ps_rt_ss_ro = 0.0;
    double pd_fx_cl_ps_rt_sd_ti_ro = 0.0;
    double pd_fx_cl_ps_rt_ss_ti_ro = 0.0;
    double pd_fx_nc_cs_gt_sm_s1_ti_ro = 0.0;
    double pd_fx_nc_cs_gt_sm_s2_ti_ro = 0.0;
    double pd_fx_nc_cs_gt_ti_ro = 0.0, pd_fx_nc_cs_rt_ti_ro = 0.0;
    double pd_fx_nc_iso_ts_ps_rt_ro = 0.0;
    double pd_nf_cl_ps_gt_sd_ti_ro = 0.0, pd_nf_cl_ps_gt_ss_ti_ro = 0.0;
    double pd_nf_nc_iso_dy_ti_ro = 0.0;
    double pd_nf_nc_ps_rt_ti_ro = 0.0;
    double pv_fx_cl_cs_gt_sd_ti_ro = 1.0;
    double pv_fx_cl_cs_gt_sm_s1_sd_ti_ro = 2.0;
    double pv_fx_cl_cs_gt_sm_s1_ss_ti_ro = -1.0;
    double pv_fx_cl_cs_gt_sm_s2_sd_ti_ro = 2.0;
    double pv_fx_cl_cs_gt_sm_s2_ss_ti_ro = -1.0;
    double pv_fx_cl_cs_gt_ss_ti_ro = -1.0;
    double pv_fx_cl_cs_gt_ts = 0.0;
    double pv_fx_cl_cs_rt_sd_ti_ro = (6.4058073E-03 * 2.0);
    double pv_fx_cl_cs_rt_ss_ti_ro = -6.4058073E-03;
    double pv_fx_cl_cs_rt_ts = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_gt_ss_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_rt_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_cs_rt_ss_ro = 0.0;
    double pv_fx_cl_iso_ts_ps_gt_sd_co = 0.0;
    double pv_fx_cl_iso_ts_ps_gt_ss_co = 0.0;
    double pv_fx_cl_iso_ts_ps_gt_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_ps_gt_ss_ro = 0.0000008023;
    double pv_fx_cl_iso_ts_ps_rt_sd_co = 0.0;
    double pv_fx_cl_iso_ts_ps_rt_ss_co = 0.0;
    double pv_fx_cl_iso_ts_ps_rt_sd_ro = 0.0;
    double pv_fx_cl_iso_ts_ps_rt_ss_ro = 1.0E-08;
    double pv_fx_cl_ps_gt_ts = 0.0;
    double pv_fx_cl_ps_rt_sd_ti_ro = 0.000009 * 2.0;
    double pv_fx_cl_ps_rt_ss_ti_ro = -0.000009;
    double pv_fx_cl_ps_rt_ts = 0.0;
    double pv_fx_nc_cs_gt_sm_s1_ti_ro = 1.0;
    double pv_fx_nc_cs_gt_sm_s2_ti_ro = 1.0;
    double pv_fx_nc_cs_gt_ti_ro = 1.0;
    double pv_fx_nc_cs_rt_ti_ro = -0.05;
    double pv_fx_nc_cs_gt_ts = 0.0, pv_fx_nc_cs_rt_ts = 0.0;
    double pv_fx_nc_iso_ts_cs_gt_ro = 0.0;
    double pv_fx_nc_iso_ts_cs_gt_sm_s1_ro = 0.0;
    double pv_fx_nc_iso_ts_cs_gt_sm_s2_ro = 0.0;
    double pv_fx_nc_iso_ts_cs_rt_ro = 0.0;
    double pv_fx_nc_iso_ts_ps_rt_co = 0.0;
    double pv_fx_nc_iso_ts_ps_rt_ro = 0.05;
    double pv_fx_nc_ps_rt_ts = 0.0;
    double pv_nf_cl_ps_gt_sd_ti_ro =  0.0000008023 * 2.0;
    double pv_nf_cl_ps_gt_ss_ti_ro = -0.0000008023;
    double pv_nf_nc_iso_dy_ti_ro = -1.380625E-13;
    double pv_nf_nc_ps_rt_ti_ro = -0.05;
    double tv_fx_cl_cs_gt_sd_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_sm_s1_sd_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_sm_s1_ss_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_sm_s2_sd_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_sm_s2_ss_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_ss_ti_ro = 0.0;
    double tv_fx_cl_cs_gt_ts = 1.0;
    double tv_fx_cl_cs_rt_sd_ti_ro = 0.0;
    double tv_fx_cl_cs_rt_ss_ti_ro = 0.0;
    double tv_fx_cl_cs_rt_ts = 1.0;
    double tv_fx_cl_iso_ts_cs_gt_sd_ro = 1.0;
    double tv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro = 0.0;
    double tv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro = 0.0;
    double tv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro = 0.0;
    double tv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro = 0.0;
    double tv_fx_cl_iso_ts_cs_gt_ss_ro = 1.0;
    double tv_fx_cl_iso_ts_cs_rt_sd_ro = 1.0;
    double tv_fx_cl_iso_ts_cs_rt_ss_ro = 1.0;
    double tv_fx_cl_iso_ts_ps_gt_sd_co = 1.0;
    double tv_fx_cl_iso_ts_ps_gt_ss_co = 1.0;
    double tv_fx_cl_iso_ts_ps_gt_sd_ro = 1.0;
    double tv_fx_cl_iso_ts_ps_gt_ss_ro = 0.0;
    double tv_fx_cl_iso_ts_ps_rt_sd_co = 1.0;
    double tv_fx_cl_iso_ts_ps_rt_ss_co = 1.0;
    double tv_fx_cl_iso_ts_ps_rt_sd_ro = 1.0;
    double tv_fx_cl_iso_ts_ps_rt_ss_ro = 0.0;
    double tv_fx_cl_ps_gt_ts = 1.0;
    double tv_fx_cl_ps_rt_sd_ti_ro = 0.0;
    double tv_fx_cl_ps_rt_ss_ti_ro = 0.0;
    double tv_fx_cl_iso_dp_ti_ro = 0.0;
    double tv_fx_cl_iso_fp_ti_ro = 0.0;
    double tv_fx_cl_iso_nt_ti_ro = 0.0;
    double tv_fx_cl_ps_rt_ts = 1.0;
    double tv_fx_nc_cs_gt_sm_s1_ti_ro = 0.0;
    double tv_fx_nc_cs_gt_sm_s2_ti_ro = 0.0;
    double tv_fx_nc_cs_gt_ti_ro = 0.0, tv_fx_nc_cs_rt_ti_ro = 0.0;
    double tv_fx_nc_cs_gt_ts = 1.0, tv_fx_nc_cs_rt_ts = 1.0;
    double tv_fx_nc_iso_ts_cs_gt_ro = 1.0;
    double tv_fx_nc_iso_ts_cs_gt_sm_s1_ro = 0.0;
    double tv_fx_nc_iso_ts_cs_gt_sm_s2_ro = 0.0;
    double tv_fx_nc_iso_ts_cs_rt_ro = 1.0;
    double tv_fx_nc_iso_ts_ps_rt_co = 1.0, tv_fx_nc_iso_ts_ps_rt_ro = 1.0;
    double tv_fx_nc_ps_rt_ts = 1.0, tv_nf_cl_ps_gt_sd_ti_ro = 0.0;
    double tv_nf_cl_ps_gt_ss_ti_ro = 0.0;
    double tv_nf_nc_iso_dy_ti_ro = 0.0;
    double tv_nf_nc_ps_rt_ti_ro = 0.0;
    double li6_lithium7_hold = 0.0;
    int append = 0;
    int bl_fx_cl_cs_gt_sd_ti_ro = 0;
    int bl_fx_cl_cs_gt_sm_s1_sd_ti_ro = 0;
    int bl_fx_cl_cs_gt_sm_s1_ss_ti_ro = 0;
    int bl_fx_cl_cs_gt_sm_s2_sd_ti_ro = 0;
    int bl_fx_cl_cs_gt_sm_s2_ss_ti_ro = 0;
    int bl_fx_cl_cs_gt_ss_ti_ro = 0;
    int bl_fx_cl_cs_rt_sd_ti_ro = 0;
    int bl_fx_cl_cs_rt_ss_ti_ro = 0;
    int bl_fx_cl_cs_gt_ts = 0;
    int bl_fx_cl_cs_rt_ts = 0;
    int bl_fx_cl_iso_ts_cs_gt_sd_ro = 0;
    int bl_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro = 0;
    int bl_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro = 0;
    int bl_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro = 0;
    int bl_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro = 0;
    int bl_fx_cl_iso_ts_cs_gt_ss_ro = 0;
    int bl_fx_cl_iso_ts_cs_rt_sd_ro = 0;
    int bl_fx_cl_iso_ts_cs_rt_ss_ro = 0;
    int bl_fx_cl_iso_ts_ps_gt_sd_co = 0;
    int bl_fx_cl_iso_ts_ps_gt_ss_co = 0;
    int bl_fx_cl_iso_ts_ps_gt_sd_ro = 0;
    int bl_fx_cl_iso_ts_ps_gt_ss_ro = 0;
    int bl_fx_cl_iso_ts_ps_rt_sd_co = 0;
    int bl_fx_cl_iso_ts_ps_rt_ss_co = 0;
    int bl_fx_cl_iso_ts_ps_rt_sd_ro = 0;
    int bl_fx_cl_iso_ts_ps_rt_ss_ro = 0;
    int bl_fx_cl_iso_dp_ti_ro = 0;
    int bl_fx_cl_iso_fp_ti_ro = 0;
    int bl_fx_cl_iso_nt_ti_ro = 0;
    int bl_fx_cl_ps_gt_ts = 0;
    int bl_fx_cl_ps_rt_sd_ti_ro = 0;
    int bl_fx_cl_ps_rt_ss_ti_ro = 0;
    int bl_fx_cl_ps_rt_ts = 0.0;
    int bl_fx_nc_cs_gt_sm_s1_ti_ro = 0;
    int bl_fx_nc_cs_gt_sm_s2_ti_ro = 0;
    int bl_fx_nc_cs_gt_ti_ro = 0, bl_fx_nc_cs_rt_ti_ro = 0;
    int bl_fx_nc_cs_gt_ts = 0,  bl_fx_nc_cs_rt_ts = 0;
    int bl_fx_nc_iso_ts_cs_gt_ro = 0;
    int bl_fx_nc_iso_ts_cs_gt_sm_s1_ro = 0.0;
    int bl_fx_nc_iso_ts_cs_gt_sm_s2_ro = 0.0;
    int bl_fx_nc_iso_ts_cs_rt_ro = 0;
    int bl_fx_nc_iso_ts_ps_rt_co = 0;
    int bl_fx_nc_iso_ts_ps_rt_ro = 0;
    int bl_fx_nc_ps_rt_ts = 0;
    int bl_nf_cl_ps_gt_sd_ti_ro = 0, bl_nf_cl_ps_gt_ss_ti_ro = 0;
    int bl_nf_nc_iso_dy_ti_ro = 0;
    int bl_nf_nc_ps_rt_ti_ro = 0;
    int boolean = 0;
    long be9_flibefuel_index = -1, beryllium_flibefuel_redox_stream_index = -1;
    long f19_fluorine0_index = -1, f19_uranium233_index = -1;
    long fluorine_fluorine0_redox_stream_index = -1;
    long fluorine_uranium233_redox_stream_index = -1;
    long li6li7_fluorine1_remv_stream_found = -1;
    long li6li7_lithium7_remv_stream_found = -1;
    long li6_flibefuel_index = -1;
    long li6_fluorine1_remv_stream_index = -1;
    long li6_fluorine1_remv_sum_stream_index = -1;
    long li6_fluorine1_index = -1;
    long li6_lithium7_index = -1;
    long li6_lithium7_remv_stream_index = -1;
    long li6_lithium7_remv_sum_stream_index = -1;
    long li7_argon40_index = -1;
    long li7_flibefuel_index = -1;
    long li7_fluorine1_index = -1;
    long li7_fluorine1_remv_sum_stream_index = -1;
    long li7_lithium7_index = -1;
    long li7_lithium7_remv_sum_stream_index = -1;
    long h1_testtank_feed_stream_index = -1;
    long h1_testtank_index = -1, h3_flibefuel_index = -1;
    long he4_argon40_index = -1;
    long he4_flibefuel_index = -1;
    long np239_flibefuel_index = -1;
    long reproc_argon40_remv_stream_index = -1;
    long reproc_flibefuel_remv_stream_index = -1;
    long rli7_fluorine1_remv_stream_index = -1, rli7_lithium7_remv_stream_index = -1;
    long rv51_testtank_remv_stream_index = -1, rw186_testtank_remv_stream_index = -1;
    long step = 0;
    long ta181_testtank_index = -1;
    long ta181_testtank_feed_sum_stream_index = -1;
    long tests_passing = 0, type = 1, u233_flibefuel_index = -1;
    long u239_flibefuel_index = -1;
    long u233_testtank_index = -1, v51_testtank_index = -1;
    long v51ta181_testtank_feed_stream_found = -1;
    long v51_testtank_feed_sum_stream_index = -1, w186_testtank_index = -1;
    long xe135_flibefuel_index = -1;

    ader_data = (long)RDB[DATA_PTR_ADER];

    ader_test_block = (long)RDB[ader_data + ADER_TEST_INFO_PTR];

    fprintf(outp, "Begin: TESTADERMakeBurnMatrix.\n");

    WDB[ader_test_block + ADER_TEST_NUM_CASES] += 1.0;

    /*Clear the print_data */
    memset(print_data, 0, strlen(print_data));

    /* FIRST: We do the zero flux tests                                       */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("TestTank", GetText(mat + MATERIAL_PTR_NAME), 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* These following steps are to clear stream CUR_AMT data so as to not    */
    /* Interfere with testing the "+1" seen in the allocation is for the CLP  */
    /* return value and while that does not matter here we stick with         */
    /* convention for clarity                                                 */

    ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

    ader_optimization_solution_array = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] + 1, sizeof(double));

    /* ADERParseClpSolution is called as it is the easiest way to reset all   */
    /* streams                                                                */

    ADERParseClpSolution(0, 0, mat, 0, ader_optimization_solution_array);

    /* Go ahead and free the optimization array                               */

    free(ader_optimization_solution_array);

    /* Gen the data to gen the matrix                                         */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

    /* Set the time interval for data processing                              */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

	/* Map appropriate data                                                   */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 0, total_time);

	/* Get sub step start and end times                                       */

    t1 = 0.0;
    t2 = total_time * 0.50;

    /* Set the material flux to 0, this is for testing                        */

    testtank_flux = RDB[mat + MATERIAL_BURN_FLUX_SSA];

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = 0.0;

    /* Now, get the indices of the matrix that need to be checked             */

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 10010)
    	{

    		h1_testtank_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 230510)
    	{

    		v51_testtank_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 731810)
    	{

    		ta181_testtank_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 741860)
    	{

    		w186_testtank_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
    	{

    		u233_testtank_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(h1_testtank_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for H-1 was not found.\n");

    }

    if(v51_testtank_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for Va-51 was not found.\n");

    }

    if(ta181_testtank_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for Ta-181 was not found.\n");

    }

    if(w186_testtank_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for W-186 was not found.\n");

    }

    if(u233_testtank_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for U-233 was not found.\n");

    }

    /* Collect the stream indices that are needed                             */

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_FEED_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("H1", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		h1_testtank_feed_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    	}

    	if(strcmp("V51Ta181", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		v51ta181_testtank_feed_stream_found = 1;

    		ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    		while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    		{

    			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

    			if(strcmp("Ta181", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				ta181_testtank_feed_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			if(strcmp("V51", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				v51_testtank_feed_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    		}

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(h1_testtank_feed_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for the H1 feed stream\n\
was not found.\n");

    }

    if(v51ta181_testtank_feed_stream_found < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for the V51Ta181 feed stream\n\
was not found.\n");

    }
    else
    {

    	if(ta181_testtank_feed_sum_stream_index < 0 &&
    	   v51_testtank_feed_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the indices for the Ta181 and V51\n\
summation streams were not found though the parent stream, V51Ta181, was found.\n");

    	}
    	else if(ta181_testtank_feed_sum_stream_index > 0 &&
    	        v51_testtank_feed_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material TestTank the index for the V51 summation\n\
stream in parent stream V51Ta181 was not found though the index for the\n\
Ta181 summation stream was found.\n");

    	}
    	else if(ta181_testtank_feed_sum_stream_index < 0 &&
    	        v51_testtank_feed_sum_stream_index > 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material TestTank the index for the Ta181 summation\n\
stream in parent stream V51Ta181 was not found though the index for the\n\
V51 summation stream was found.\n");

    	}

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("rV51", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		rv51_testtank_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}


    	if(strcmp("rW186", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		rw186_testtank_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(rv51_testtank_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for the rV51 remv stream\n\
was not found.\n");

    }

    if(rw186_testtank_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material TestTank the index for the rW186 remv stream\n\
was not found.\n");

    }

    /* Gen the burnup matrix                                                  */

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

    ADERMakeBurnMatrix(burn_matrix,
    		           ader_burn_matrix_col_storage, mat,
					   (long)ader_burn_matrix_num_ents[0],
					   (long)ader_burn_matrix_num_rows[0], step, type, t1, t2);

    /* Now get the values from the burn matrix and compare to the expected    */

    tv_nf_nc_ps_rt_ti_ro = ADERGetBurnMatrixValue(v51_testtank_index,
    		                                      burn_matrix,
												  v51_testtank_index);

    pd_nf_nc_ps_rt_ti_ro = (tv_nf_nc_ps_rt_ti_ro - pv_nf_nc_ps_rt_ti_ro) /
    		                                       pv_nf_nc_ps_rt_ti_ro;

    if(fabs(pd_nf_nc_ps_rt_ti_ro) < 0.001)
    {

    	bl_nf_nc_ps_rt_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_nf_nc_iso_dy_ti_ro = ADERGetBurnMatrixValue(u233_testtank_index,
    		                                       burn_matrix,
												   u233_testtank_index);

    pd_nf_nc_iso_dy_ti_ro = (tv_nf_nc_iso_dy_ti_ro - pv_nf_nc_iso_dy_ti_ro) /
    		                                        pv_nf_nc_iso_dy_ti_ro;

    if(fabs(pd_nf_nc_iso_dy_ti_ro) < 0.01)
    {

    	bl_nf_nc_iso_dy_ti_ro = 1;

    	tests_passing += 1;

    }

    /* Clear the memory associated with the zero flux TestTank burn matrix    */

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    /* Reset the TestTank flux                                                */

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = testtank_flux;

    /* Get the Lithium7 cluster and generate its zero flux burnup matrix      */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Lithium7", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* These following steps are to clear stream CUR_AMT data so as to not    */
    /* Interfere with testing the "+1" seen in the allocation is for the CLP  */
    /* return value and while that does not matter here we stick with         */
    /* convention for clarity                                                 */

    ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

    ader_optimization_solution_array = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] + 1, sizeof(double));

    /* ADERParseClpSolution is called as it is the easiest way to reset all   */
    /* streams                                                                */

    ADERParseClpSolution(0, 0, mat, 0, ader_optimization_solution_array);

    /* Go ahead and free the optimization array                               */

    free(ader_optimization_solution_array);

    /* Gen the data to gen the matrix                                         */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

    /* Set the time interval for data processing                              */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

	/* Map appropriate data                                                   */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 0, total_time);

    /* Set the material flux to 0, this is for testing                        */

    lithium7_flux = RDB[mat + MATERIAL_BURN_FLUX_SSA];

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = 0.0;

    /* Next get the Fluorine1 material to set its flux level                  */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Fluorine1", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Set the material flux to 0, this is for testing                        */

    fluorine1_flux = RDB[mat + MATERIAL_BURN_FLUX_SSA];

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = 0.0;

    /* Now, get the indices of the matrix that need to be checked             */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Lithium7", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
    	{

    		li6_lithium7_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    		li6_lithium7_hold = RDB[mat_iso + COMPOSITION_ADENS];

    		li6_lithium7_mat_iso = mat_iso;

    		WDB[mat_iso + COMPOSITION_ADENS] = RDB[ader_mat_data + ADER_MAT_PRE_STEP_ADENS] / 2.0;

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

    		li7_lithium7_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(li6_lithium7_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the index for Li-6 was not found.\n");

    }

    if(li7_lithium7_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the index for Li-7 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Li6", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		li6_lithium7_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.25;

    	}


    	if(strcmp("rLi7", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		rli7_lithium7_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	if(strcmp("Li6Li7", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		li6li7_lithium7_remv_stream_found = 1;

    		ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    		while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    		{

    			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

    			if(strcmp("Li6", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				li6_lithium7_remv_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			if(strcmp("Li7", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				li7_lithium7_remv_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    		}

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(li6_lithium7_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the index for the Li6 remv stream\n\
was not found.\n");

    }

    if(rli7_lithium7_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the index for the rLi7 remv stream\n\
was not found.\n");

    }

    if(li6li7_lithium7_remv_stream_found < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the index for the Li6Li7 remv stream\n\
was not found.\n");

    }
    else
    {

    	if(li6_lithium7_remv_sum_stream_index < 0 &&
    	   li7_lithium7_remv_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
"In burnup matrix for material Lithium7 the indices for the Li6 and Li7\n\
summation streams were not found though the parent stream, Li6Li7, was found.\n");

    	}
    	else if(li6_lithium7_remv_sum_stream_index > 0 &&
    	    	li7_lithium7_remv_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material Lithium7 the index for the Li7 summation\n\
stream in parent stream Li6Li7 was not found though the index for the\n\
Li6 summation stream was found.\n");

    	}
    	else if(li6_lithium7_remv_sum_stream_index < 0 &&
    	    	li7_lithium7_remv_sum_stream_index > 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material Lithium7 the index for the Li6 summation\n\
stream in parent stream Li6Li7 was not found though the index for the\n\
Li7 summation stream was found.\n");

    	}

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Fluorine1", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
    	{

    		li6_fluorine1_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

    		li7_fluorine1_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(li6_fluorine1_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the index for Li-6 was not found.\n");

    }

    if(li7_fluorine1_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the index for Li-7 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Li6Li7", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		li6li7_fluorine1_remv_stream_found = 1;

    		ader_mat_stream_sum_stream_ent = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_SUM_GRPS_PTR];

    		while(ader_mat_stream_sum_stream_ent > VALID_PTR)
    		{

    			ader_mat_stream_sum_stream = (long)RDB[ader_mat_stream_sum_stream_ent + ADER_MAT_GRP_SUM_GRP_PTR];

    			if(strcmp("Li6", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				li6_fluorine1_remv_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			if(strcmp("Li7", GetText(ader_mat_stream_sum_stream + ADER_MAT_STREAM_ID)) == 0)
    			{

    				li7_fluorine1_remv_sum_stream_index = (long)RDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_BURN_INDEX];

    				WDB[ader_mat_stream_sum_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    			}

    			ader_mat_stream_sum_stream_ent = NextItem(ader_mat_stream_sum_stream_ent);

    		}

    	}

    	if(strcmp("Li6", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		li6_fluorine1_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.25;

    	}

    	if(strcmp("rLi7", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		rli7_fluorine1_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(li6_fluorine1_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the index for the Li6 remv stream\n\
was not found.\n");

    }

    if(rli7_fluorine1_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the index for the rLi7 remv stream\n\
was not found.\n");

    }

    if(li6li7_fluorine1_remv_stream_found < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the index for the Li6Li7 feed stream\n\
was not found.\n");

    }
    else
    {

    	if(li6_fluorine1_remv_sum_stream_index < 0 &&
    	   li7_fluorine1_remv_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine1 the indices for the Li6 and Li7\n\
summation streams were not found though the parent stream, Li6Li7, was found.\n");

    	}
    	else if(li6_fluorine1_remv_sum_stream_index > 0 &&
    	    	li7_fluorine1_remv_sum_stream_index < 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material Fluorine1 the index for the Li7 summation\n\
stream in parent stream Li6Li7 was not found though the index for the\n\
Li6 summation stream was found.\n");

    	}
    	else if(li6_fluorine1_remv_sum_stream_index < 0 &&
    	    	li7_fluorine1_remv_sum_stream_index > 0)
    	{

        	Die(FUNCTION_NAME,\
    "In burnup matrix for material Fluorine1 the index for the Li6 summation\n\
stream in parent stream Li6Li7 was not found though the index for the\n\
Li7 summation stream was found.\n");

    	}

    }

    /* Gen the burnup matrix                                                  */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Lithium7", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

    ADERMakeBurnMatrix(burn_matrix,
    		           ader_burn_matrix_col_storage, mat,
					   (long)ader_burn_matrix_num_ents[0],
					   (long)ader_burn_matrix_num_rows[0], step, type, t1, t2);

    /* Now get the values from the burn matrix and compare to the expected    */

    tv_nf_cl_ps_gt_ss_ti_ro = ADERGetBurnMatrixValue(li6_lithium7_index,
    		                                         burn_matrix,
												     li6_lithium7_index);

    pd_nf_cl_ps_gt_ss_ti_ro = (tv_nf_cl_ps_gt_ss_ti_ro - pv_nf_cl_ps_gt_ss_ti_ro) /
    		                                             pv_nf_cl_ps_gt_ss_ti_ro;

    if(fabs(pd_nf_cl_ps_gt_ss_ti_ro) < 0.001)
    {

    	bl_nf_cl_ps_gt_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_nf_cl_ps_gt_sd_ti_ro = ADERGetBurnMatrixValue(li6_lithium7_index,
    		                                         burn_matrix,
												     li6_fluorine1_index);

    pd_nf_cl_ps_gt_sd_ti_ro = (tv_nf_cl_ps_gt_sd_ti_ro - pv_nf_cl_ps_gt_sd_ti_ro) /
    		                                             pv_nf_cl_ps_gt_sd_ti_ro;

    if(fabs(pd_nf_cl_ps_gt_sd_ti_ro) < 0.001)
    {

    	bl_nf_cl_ps_gt_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    /* Clear the memory associated with the zero flux TestTank burn matrix    */

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    /* Reset the Fluorine1 flux                                               */

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = fluorine1_flux;

    /* Reset the Lithium7 flux                                                */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strcmp("Lithium7", GetText(mat + MATERIAL_PTR_NAME)) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    /* Reset the Lithium7 flux                                                */

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = lithium7_flux;

    /* SECOND: We do the tests with flux                                      */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("TestTank", GetText(mat + MATERIAL_PTR_NAME), 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Gen the data to gen the matrix                                         */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

    /* Set the time interval for data processing                              */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

	/* Map appropriate data                                                   */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 0, total_time);

    /* Here we set the TestTank flux to a fixed value for testing             */

    WDB[mat + MATERIAL_BURN_FLUX_SSA] = 12.0;

    /* Gen the burnup matrix                                                  */

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

    ADERMakeBurnMatrix(burn_matrix,
    		           ader_burn_matrix_col_storage, mat,
					   (long)ader_burn_matrix_num_ents[0],
					   (long)ader_burn_matrix_num_rows[0], step, type, t1, t2);

    /* Now get the values from the burn matrix and compare to the expected    */

    tv_fx_nc_cs_gt_ts = ADERGetBurnMatrixValue(h1_testtank_feed_stream_index,
    		                                   burn_matrix,
											   h1_testtank_feed_stream_index);

    if(tv_fx_nc_cs_gt_ts == 0.0)
    {

    	bl_fx_nc_cs_gt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_ps_rt_ts = ADERGetBurnMatrixValue(rv51_testtank_remv_stream_index,
    		                                   burn_matrix,
											   rv51_testtank_remv_stream_index);

    if(tv_fx_nc_ps_rt_ts == 0.0)
    {

    	bl_fx_nc_ps_rt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_cs_rt_ts = ADERGetBurnMatrixValue(rw186_testtank_remv_stream_index,
    		                                   burn_matrix,
											   rw186_testtank_remv_stream_index);

    if(tv_fx_nc_cs_rt_ts == 0.0)
    {

    	bl_fx_nc_cs_rt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_cs_gt_ro = ADERGetBurnMatrixValue(h1_testtank_index,
    		                                          burn_matrix,
											          h1_testtank_feed_stream_index);

    if(tv_fx_nc_iso_ts_cs_gt_ro == 0.0)
    {

    	bl_fx_nc_iso_ts_cs_gt_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_cs_rt_ro = ADERGetBurnMatrixValue(w186_testtank_index,
    		                                         burn_matrix,
											         rw186_testtank_remv_stream_index);

    if(tv_fx_nc_iso_ts_cs_rt_ro == 0.0)
    {

    	bl_fx_nc_iso_ts_cs_rt_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_ps_rt_co = ADERGetBurnMatrixValue(rv51_testtank_remv_stream_index,
    		                                          burn_matrix,
													  v51_testtank_index);

    if(tv_fx_nc_iso_ts_ps_rt_co == 0.0)
    {

    	bl_fx_nc_iso_ts_ps_rt_co = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_ps_rt_ro = ADERGetBurnMatrixValue(v51_testtank_index,
    		                                          burn_matrix,
											          rv51_testtank_remv_stream_index);

    pd_fx_nc_iso_ts_ps_rt_ro = (tv_fx_nc_iso_ts_ps_rt_ro - pv_fx_nc_iso_ts_ps_rt_ro) /
    		                                               pv_fx_nc_iso_ts_ps_rt_ro;

    if(fabs(pd_fx_nc_iso_ts_ps_rt_ro) < 0.001)
    {
    	bl_fx_nc_iso_ts_ps_rt_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_cs_gt_ti_ro = ADERGetBurnMatrixValue(h1_testtank_feed_stream_index,
    		                                      burn_matrix,
												  h1_testtank_index);

    pd_fx_nc_cs_gt_ti_ro = (tv_fx_nc_cs_gt_ti_ro - pv_fx_nc_cs_gt_ti_ro) /
    		                                       pv_fx_nc_cs_gt_ti_ro;

    if(fabs(pd_fx_nc_cs_gt_ti_ro) < 0.001)
    {

    	bl_fx_nc_cs_gt_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_cs_rt_ti_ro = ADERGetBurnMatrixValue(rw186_testtank_remv_stream_index,
    		                                      burn_matrix,
												  w186_testtank_index);

    pd_fx_nc_cs_rt_ti_ro = (tv_fx_nc_cs_rt_ti_ro - pv_fx_nc_cs_rt_ti_ro) /
    		                                       pv_fx_nc_cs_rt_ti_ro;

    if(fabs(pd_fx_nc_cs_rt_ti_ro) < 0.001)
    {

    	bl_fx_nc_cs_rt_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_cs_gt_sm_s1_ti_ro = ADERGetBurnMatrixValue(ta181_testtank_feed_sum_stream_index,
    		                                            burn_matrix,
												        ta181_testtank_index);

    pd_fx_nc_cs_gt_sm_s1_ti_ro = (tv_fx_nc_cs_gt_sm_s1_ti_ro - pv_fx_nc_cs_gt_sm_s1_ti_ro) /
    		                                                   pv_fx_nc_cs_gt_sm_s1_ti_ro;

    if(fabs(pd_fx_nc_cs_gt_sm_s1_ti_ro) < 0.001)
    {

    	bl_fx_nc_cs_gt_sm_s1_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_cs_gt_sm_s2_ti_ro = ADERGetBurnMatrixValue(v51_testtank_feed_sum_stream_index,
    		                                            burn_matrix,
												        v51_testtank_index);

    pd_fx_nc_cs_gt_sm_s2_ti_ro = (tv_fx_nc_cs_gt_sm_s2_ti_ro - pv_fx_nc_cs_gt_sm_s2_ti_ro) /
    		                                                   pv_fx_nc_cs_gt_sm_s2_ti_ro;

    if(fabs(pd_fx_nc_cs_gt_sm_s2_ti_ro) < 0.001)
    {

    	bl_fx_nc_cs_gt_sm_s2_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_cs_gt_sm_s1_ro = ADERGetBurnMatrixValue(ta181_testtank_index,
    		                                             burn_matrix,
												         ta181_testtank_feed_sum_stream_index);

    if(tv_fx_nc_iso_ts_cs_gt_sm_s1_ro == 0.0)
    {

    	bl_fx_nc_iso_ts_cs_gt_sm_s1_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_nc_iso_ts_cs_gt_sm_s2_ro = ADERGetBurnMatrixValue(v51_testtank_index,
    		                                             burn_matrix,
												         v51_testtank_feed_sum_stream_index);

    if(tv_fx_nc_iso_ts_cs_gt_sm_s2_ro == 0.0)
    {

    	bl_fx_nc_iso_ts_cs_gt_sm_s2_ro = 1;

    	tests_passing += 1;

    }

    /* Clear the memory associated with the zero flux TestTank burn matrix    */

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    /* Now begin the tests with the Lithium7 cluster                          */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("Lithium7", GetText(mat + MATERIAL_PTR_NAME), 8) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* Gen the data to gen the matrix                                         */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

    /* Set the time interval for data processing                              */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

	/* Map appropriate data                                                   */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 0, total_time);

    /* Gen the burnup matrix                                                  */

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

    ADERMakeBurnMatrix(burn_matrix,
    		           ader_burn_matrix_col_storage, mat,
					   (long)ader_burn_matrix_num_ents[0],
					   (long)ader_burn_matrix_num_rows[0], step, type, t1, t2);

    /* Begin gathering the test information                                   */

    tv_fx_cl_cs_rt_ss_ti_ro = ADERGetBurnMatrixValue(rli7_lithium7_remv_stream_index,
    		                                         burn_matrix,
												     li7_lithium7_index);

    pd_fx_cl_cs_rt_ss_ti_ro = (tv_fx_cl_cs_rt_ss_ti_ro - pv_fx_cl_cs_rt_ss_ti_ro) /
    		                                             pv_fx_cl_cs_rt_ss_ti_ro;

    if(fabs(pd_fx_cl_cs_rt_ss_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_rt_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_rt_sd_ti_ro = ADERGetBurnMatrixValue(rli7_fluorine1_remv_stream_index,
    		                                         burn_matrix,
												     li7_fluorine1_index);

    pd_fx_cl_cs_rt_sd_ti_ro = (tv_fx_cl_cs_rt_sd_ti_ro - pv_fx_cl_cs_rt_sd_ti_ro) /
    		                                             pv_fx_cl_cs_rt_sd_ti_ro;

    if(fabs(pd_fx_cl_cs_rt_sd_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_rt_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_rt_ts = ADERGetBurnMatrixValue(rli7_lithium7_remv_stream_index,
    		                                   burn_matrix,
											   rli7_lithium7_remv_stream_index);

    if(tv_fx_cl_cs_rt_ts == 0.0)
    {

    	bl_fx_cl_cs_rt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_rt_ss_ro = ADERGetBurnMatrixValue(li7_lithium7_index,
    		                                             burn_matrix,
												         rli7_lithium7_remv_stream_index);

    if(tv_fx_cl_iso_ts_cs_rt_ss_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_rt_ss_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_rt_sd_ro = ADERGetBurnMatrixValue(li7_fluorine1_index,
    		                                             burn_matrix,
												         rli7_fluorine1_remv_stream_index);

    if(tv_fx_cl_iso_ts_cs_rt_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_rt_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_gt_sd_co = ADERGetBurnMatrixValue(li6_fluorine1_remv_stream_index,
    		                                             burn_matrix,
												         li6_fluorine1_index);

    if(tv_fx_cl_iso_ts_ps_gt_sd_co == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_gt_sd_co = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_gt_ss_co = ADERGetBurnMatrixValue(li6_lithium7_remv_stream_index,
    		                                             burn_matrix,
												         li6_lithium7_index);

    if(tv_fx_cl_iso_ts_ps_gt_ss_co == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_gt_ss_co = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_gt_sd_ro = ADERGetBurnMatrixValue(li6_fluorine1_index,
    		                                             burn_matrix,
														 li6_fluorine1_remv_stream_index);

    if(tv_fx_cl_iso_ts_ps_gt_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_gt_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_gt_ss_ro = ADERGetBurnMatrixValue(li6_lithium7_index,
    		                                             burn_matrix,
														 li6_lithium7_remv_stream_index);

    pd_fx_cl_iso_ts_ps_gt_ss_ro = (tv_fx_cl_iso_ts_ps_gt_ss_ro - pv_fx_cl_iso_ts_ps_gt_ss_ro) /
    		                                                     pv_fx_cl_iso_ts_ps_gt_ss_ro;

    if(fabs(pd_fx_cl_iso_ts_ps_gt_ss_ro) < 0.001)
    {

    	bl_fx_cl_iso_ts_ps_gt_ss_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_ps_gt_ts = ADERGetBurnMatrixValue(li6_lithium7_remv_stream_index,
    		                                   burn_matrix,
											   li6_lithium7_remv_stream_index);

    if(tv_fx_cl_ps_gt_ts == 0.0)
    {

    	bl_fx_cl_ps_gt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_sm_s1_sd_ti_ro = ADERGetBurnMatrixValue(li6_fluorine1_remv_sum_stream_index,
    		                                               burn_matrix,
												           li6_fluorine1_index);

    pd_fx_cl_cs_gt_sm_s1_sd_ti_ro = (tv_fx_cl_cs_gt_sm_s1_sd_ti_ro - pv_fx_cl_cs_gt_sm_s1_sd_ti_ro) /
    		                                                         pv_fx_cl_cs_gt_sm_s1_sd_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_sm_s1_sd_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_sm_s1_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_sm_s1_ss_ti_ro = ADERGetBurnMatrixValue(li6_lithium7_remv_sum_stream_index,
    		                                               burn_matrix,
												           li6_lithium7_index);

    pd_fx_cl_cs_gt_sm_s1_ss_ti_ro = (tv_fx_cl_cs_gt_sm_s1_ss_ti_ro - pv_fx_cl_cs_gt_sm_s1_ss_ti_ro) /
    		                                                         pv_fx_cl_cs_gt_sm_s1_ss_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_sm_s1_ss_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_sm_s1_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_sm_s2_sd_ti_ro = ADERGetBurnMatrixValue(li7_fluorine1_remv_sum_stream_index,
    		                                               burn_matrix,
												           li7_fluorine1_index);

    pd_fx_cl_cs_gt_sm_s2_sd_ti_ro = (tv_fx_cl_cs_gt_sm_s2_sd_ti_ro - pv_fx_cl_cs_gt_sm_s2_sd_ti_ro) /
    		                                                         pv_fx_cl_cs_gt_sm_s2_sd_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_sm_s2_sd_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_sm_s2_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_sm_s2_ss_ti_ro = ADERGetBurnMatrixValue(li7_lithium7_remv_sum_stream_index,
    		                                               burn_matrix,
												           li7_lithium7_index);

    pd_fx_cl_cs_gt_sm_s2_ss_ti_ro = (tv_fx_cl_cs_gt_sm_s2_ss_ti_ro - pv_fx_cl_cs_gt_sm_s2_ss_ti_ro) /
    		                                                         pv_fx_cl_cs_gt_sm_s2_ss_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_sm_s2_ss_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_sm_s2_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro = ADERGetBurnMatrixValue(li6_fluorine1_index,
    		                                                   burn_matrix,
															   li6_fluorine1_remv_sum_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro = ADERGetBurnMatrixValue(li6_lithium7_index,
    		                                                   burn_matrix,
															   li6_lithium7_remv_sum_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro = ADERGetBurnMatrixValue(li7_fluorine1_index,
    		                                                   burn_matrix,
															   li7_fluorine1_remv_sum_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro = ADERGetBurnMatrixValue(li7_lithium7_index,
    		                                                   burn_matrix,
															   li7_lithium7_remv_sum_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro = 1;

    	tests_passing += 1;

    }

    /* Clear the memory associated with the zero flux TestTank burn matrix    */

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    /* Now begin the tests with the FLiBeFuel cluster                          */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("FLiBeFuel", GetText(mat + MATERIAL_PTR_NAME), 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    /* These following steps are to clear stream CUR_AMT data so as to not    */
    /* Interfere with testing the "+1" seen in the allocation is for the CLP  */
    /* return value and while that does not matter here we stick with         */
    /* convention for clarity                                                 */

    ader_mat_matrix_data = (long)RDB[ader_mat_data + ADER_MAT_MATRIX_PTR];

    ader_optimization_solution_array = calloc((long)RDB[ader_mat_matrix_data + ADER_MAT_MATRIX_NUM_COLS] + 1, sizeof(double));

    /* ADERParseClpSolution is called as it is the easiest way to reset all   */
    /* streams                                                                */

    ADERParseClpSolution(0, 0, mat, 0, ader_optimization_solution_array);

    /* Go ahead and free the optimization array                               */

    free(ader_optimization_solution_array);

    /* Gen the data to gen the matrix                                         */

	ader_burn_matrix_size_data = ADERGetBurnMatrixSizeData(mat);

	/* Parse that data out                                                    */

	ader_burn_matrix_num_rows = ader_burn_matrix_size_data[0];

	ader_burn_matrix_num_ents = ader_burn_matrix_size_data[1];

	ader_burn_matrix_starts = ader_burn_matrix_size_data[2];

	ader_burn_matrix_N0 = ader_burn_matrix_size_data[3];

	ader_burn_matrix_col_storage = ader_burn_matrix_size_data[4];

    /* Set the time interval for data processing                              */

	total_time = RDB[DATA_BURN_TIME_INTERVAL];

	/* Map appropriate data                                                   */

    ADERMapDensityVector(ader_burn_matrix_N0, ader_burn_matrix_starts, 0, 0,
    		             mat, 0, total_time);

    /* Now gather the index information that is needed                        */

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 10030)
    	{

    		h3_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 20040)
    	{

    		he4_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30060)
    	{

    		li6_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}


    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

    		li7_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 40090)
    	{

    		be9_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 541350)
    	{

    		xe135_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 922330)
    	{

    		u233_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 922390)
    	{

    		u239_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 932390)
    	{

    		np239_flibefuel_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(h3_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for H-3 was not found.\n");

    }

    if(he4_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for He-4 was not found.\n");

    }

    if(li6_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for Li-6 was not found.\n");

    }

    if(li7_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for Li-7 was not found.\n");

    }

    if(be9_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for Be-9 was not found.\n");

    }

    if(xe135_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for Xe-135 was not found.\n");

    }

    if(u233_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for U-233 was not found.\n");

    }

    if(u239_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for U-239 was not found.\n");

    }

    if(np239_flibefuel_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for Np-239 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Beryllium", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		beryllium_flibefuel_redox_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(beryllium_flibefuel_redox_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for the Beryllium redox\n\
stream was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("reproc", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		reproc_flibefuel_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(reproc_flibefuel_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material FLiBeFuel the index for the reproc removal\n\
stream was not found.\n");

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("Argon40", GetText(mat + MATERIAL_PTR_NAME), 7) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 20040)
    	{

    		he4_argon40_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 30070)
    	{

    		li7_argon40_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(he4_argon40_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Argon40 the index for He-4 was not found.\n");

    }

    if(li7_argon40_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Argon40 the index for Li-7 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REMV_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("reproc", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		reproc_argon40_remv_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(reproc_argon40_remv_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Argon40 the index for the reproc feed\n\
stream was not found.\n");

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("Fluorine0", GetText(mat + MATERIAL_PTR_NAME), 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 90190)
    	{

    		f19_fluorine0_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(f19_fluorine0_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine0 the index for F-19 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Fluorine", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		fluorine_fluorine0_redox_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    		WDB[ader_mat_stream + ADER_MAT_STREAM_CUR_AMT] = 0.5;

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(fluorine_fluorine0_redox_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Fluorine0 the index for the Fluorine redox\n\
stream was not found.\n");

    }

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("Uranium233", GetText(mat + MATERIAL_PTR_NAME), 10) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    ader_mat_iso = (long)RDB[ader_mat_data + ADER_MAT_ISOS_PTR];

    while(ader_mat_iso > VALID_PTR)
    {

    	mat_iso = (long)RDB[ader_mat_iso + ADER_MAT_ISO_PTR];

    	nuc = (long)RDB[mat_iso + COMPOSITION_PTR_NUCLIDE];

    	if((long)RDB[nuc + NUCLIDE_ZAI] == 90190)
    	{

    		f19_uranium233_index = (long)RDB[ader_mat_iso + ADER_MAT_ISO_BURN_INDEX];

    	}

    	ader_mat_iso = NextItem(ader_mat_iso);

    }

    if(f19_uranium233_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Uranium233 the index for F-19 was not found.\n");

    }

    ader_mat_stream = (long)RDB[ader_mat_data + ADER_MAT_REDOX_STREAMS_PTR];

    while(ader_mat_stream > VALID_PTR)
    {

    	if(strcmp("Fluorine", GetText(ader_mat_stream + ADER_MAT_STREAM_ID)) == 0)
    	{

    		fluorine_uranium233_redox_stream_index = (long)RDB[ader_mat_stream + ADER_MAT_STREAM_BURN_INDEX];

    	}

    	ader_mat_stream = NextItem(ader_mat_stream);

    }

    if(fluorine_uranium233_redox_stream_index < 0)
    {

    	Die(FUNCTION_NAME,\
"In burnup matrix for material Uranium233 the index for the Fluorine redox\n\
stream was not found.\n");

    }

    /* Gen the burnup matrix                                                  */

    mat = (long)RDB[DATA_PTR_M0];

    while(mat > VALID_PTR)
    {

        if(strncmp("FLiBeFuel", GetText(mat + MATERIAL_PTR_NAME), 9) == 0)
        {

            break;

        }

        mat = NextItem(mat);

    }

    ader_mat_data = (long)RDB[mat + MATERIAL_ADER_DATA];

	burn_matrix = ccsMatrixNew((long)ader_burn_matrix_num_rows[0],
			                   (long)ader_burn_matrix_num_rows[0],
							   (long)ader_burn_matrix_num_ents[0]);

    ADERMakeBurnMatrix(burn_matrix,
    		           ader_burn_matrix_col_storage, mat,
					   (long)ader_burn_matrix_num_ents[0],
					   (long)ader_burn_matrix_num_rows[0], step, type, t1, t2);

    /* Begin gathering the test information                                   */

    tv_fx_cl_cs_gt_sd_ti_ro = ADERGetBurnMatrixValue(fluorine_uranium233_redox_stream_index,
    		                                         burn_matrix,
												     f19_uranium233_index);

    pd_fx_cl_cs_gt_sd_ti_ro = (tv_fx_cl_cs_gt_sd_ti_ro - pv_fx_cl_cs_gt_sd_ti_ro) /
    		                                             pv_fx_cl_cs_gt_sd_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_sd_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_ss_ti_ro = ADERGetBurnMatrixValue(fluorine_fluorine0_redox_stream_index,
    		                                         burn_matrix,
												     f19_fluorine0_index);

    pd_fx_cl_cs_gt_ss_ti_ro = (tv_fx_cl_cs_gt_ss_ti_ro - pv_fx_cl_cs_gt_ss_ti_ro) /
    		                                             pv_fx_cl_cs_gt_ss_ti_ro;

    if(fabs(pd_fx_cl_cs_gt_ss_ti_ro) < 0.001)
    {

    	bl_fx_cl_cs_gt_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_cs_gt_ts = ADERGetBurnMatrixValue(fluorine_fluorine0_redox_stream_index,
    		                                   burn_matrix,
											   fluorine_fluorine0_redox_stream_index);

    if(tv_fx_cl_cs_gt_ts == 0.0)
    {

    	bl_fx_cl_cs_gt_ts = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_dp_ti_ro = ADERGetBurnMatrixValue(u239_flibefuel_index,
    		                                       burn_matrix,
												   np239_flibefuel_index);

    if(tv_fx_cl_iso_dp_ti_ro > 0.0)
    {

    	bl_fx_cl_iso_dp_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_fp_ti_ro = ADERGetBurnMatrixValue(u233_flibefuel_index,
    		                                       burn_matrix,
												   xe135_flibefuel_index);

    if(tv_fx_cl_iso_fp_ti_ro > 0.0)
    {

    	bl_fx_cl_iso_fp_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_nt_ti_ro = ADERGetBurnMatrixValue(li6_flibefuel_index,
    		                                       burn_matrix,
												   h3_flibefuel_index);

    if(tv_fx_cl_iso_nt_ti_ro > 0.0)
    {

    	bl_fx_cl_iso_nt_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_sd_ro = ADERGetBurnMatrixValue(f19_uranium233_index,
    		                                             burn_matrix,
												         fluorine_uranium233_redox_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_cs_gt_ss_ro = ADERGetBurnMatrixValue(f19_fluorine0_index,
    		                                             burn_matrix,
												         fluorine_fluorine0_redox_stream_index);

    if(tv_fx_cl_iso_ts_cs_gt_ss_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_cs_gt_ss_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_rt_sd_co = ADERGetBurnMatrixValue(reproc_argon40_remv_stream_index,
    		                                             burn_matrix,
												         li7_argon40_index);

    if(tv_fx_cl_iso_ts_ps_rt_sd_co == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_rt_sd_co = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_rt_ss_co = ADERGetBurnMatrixValue(reproc_flibefuel_remv_stream_index,
    		                                             burn_matrix,
												         li7_flibefuel_index);

    if(tv_fx_cl_iso_ts_ps_rt_ss_co == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_rt_ss_co = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_rt_sd_ro = ADERGetBurnMatrixValue(li7_argon40_index,
    		                                             burn_matrix,
														 reproc_argon40_remv_stream_index);

    if(tv_fx_cl_iso_ts_ps_rt_sd_ro == 0.0)
    {

    	bl_fx_cl_iso_ts_ps_rt_sd_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_iso_ts_ps_rt_ss_ro = ADERGetBurnMatrixValue(li7_flibefuel_index,
    		                                             burn_matrix,
														 reproc_argon40_remv_stream_index);

    pd_fx_cl_iso_ts_ps_rt_ss_ro = (tv_fx_cl_iso_ts_ps_rt_ss_ro - pv_fx_cl_iso_ts_ps_rt_ss_ro) /
    		                                                     pv_fx_cl_iso_ts_ps_rt_ss_ro;

    if(fabs(pd_fx_cl_iso_ts_ps_rt_ss_ro) < 0.001)
    {

    	bl_fx_cl_iso_ts_ps_rt_ss_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_ps_rt_sd_ti_ro = ADERGetBurnMatrixValue(he4_flibefuel_index,
    		                                         burn_matrix,
													 he4_argon40_index);

    pd_fx_cl_ps_rt_sd_ti_ro = (tv_fx_cl_ps_rt_sd_ti_ro - pv_fx_cl_ps_rt_sd_ti_ro) /
    		                                             pv_fx_cl_ps_rt_sd_ti_ro;

    if(fabs(pd_fx_cl_ps_rt_sd_ti_ro) < 0.001)
    {

    	bl_fx_cl_ps_rt_sd_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_ps_rt_ss_ti_ro = ADERGetBurnMatrixValue(he4_flibefuel_index,
    		                                         burn_matrix,
													 he4_flibefuel_index);

    pd_fx_cl_ps_rt_ss_ti_ro = (tv_fx_cl_ps_rt_ss_ti_ro - pv_fx_cl_ps_rt_ss_ti_ro) /
    		                                             pv_fx_cl_ps_rt_ss_ti_ro;

    if(fabs(pd_fx_cl_ps_rt_ss_ti_ro) < 0.001)
    {

    	bl_fx_cl_ps_rt_ss_ti_ro = 1;

    	tests_passing += 1;

    }

    tv_fx_cl_ps_rt_ts = ADERGetBurnMatrixValue(reproc_flibefuel_remv_stream_index,
    		                                   burn_matrix,
										       reproc_flibefuel_remv_stream_index);

    if(tv_fx_cl_ps_rt_ts == 0.0)
    {

    	bl_fx_cl_ps_rt_ts = 1;

    	tests_passing += 1;

    }

	/* Deallocate the burn matrix size data                                   */

	ADERDeallocateTarget(ader_burn_matrix_size_data, 5);

    /* Free the memory                                                        */

    ccsMatrixFree(burn_matrix);

    /* Reset the Lithium7 Li-6 value and density                              */

	WDB[li6_lithium7_mat_iso + COMPOSITION_ADENS] = li6_lithium7_hold;

    if(bl_nf_nc_ps_rt_ti_ro == 1 &&
       bl_nf_nc_iso_dy_ti_ro == 1 &&
	   bl_nf_cl_ps_gt_ss_ti_ro == 1 &&
	   bl_nf_cl_ps_gt_sd_ti_ro == 1 &&
	   bl_fx_nc_cs_gt_ts == 1 &&
	   bl_fx_nc_ps_rt_ts == 1 &&
	   bl_fx_nc_cs_rt_ts == 1 &&
	   bl_fx_nc_iso_ts_cs_gt_ro == 1 &&
	   bl_fx_nc_iso_ts_cs_rt_ro == 1 &&
	   bl_fx_nc_iso_ts_ps_rt_co == 1 &&
	   bl_fx_nc_iso_ts_ps_rt_ro == 1 &&
	   bl_fx_nc_cs_gt_ti_ro == 1 &&
	   bl_fx_nc_cs_rt_ti_ro == 1 &&
	   bl_fx_nc_cs_gt_sm_s1_ti_ro == 1 &&
	   bl_fx_nc_cs_gt_sm_s2_ti_ro == 1 &&
	   bl_fx_nc_iso_ts_cs_gt_sm_s1_ro == 1 &&
	   bl_fx_nc_iso_ts_cs_gt_sm_s2_ro == 1 &&
	   bl_fx_cl_cs_rt_ss_ti_ro == 1 &&
	   bl_fx_cl_cs_rt_sd_ti_ro == 1 &&
	   bl_fx_cl_cs_rt_ts == 1 &&
	   bl_fx_cl_iso_ts_cs_rt_ss_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_rt_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_ps_gt_sd_co == 1 &&
	   bl_fx_cl_iso_ts_ps_gt_ss_co == 1 &&
	   bl_fx_cl_iso_ts_ps_gt_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_ps_gt_ss_ro == 1 &&
	   bl_fx_cl_ps_gt_ts == 1 &&
	   bl_fx_cl_cs_gt_sm_s1_sd_ti_ro == 1 &&
	   bl_fx_cl_cs_gt_sm_s1_ss_ti_ro == 1 &&
	   bl_fx_cl_cs_gt_sm_s2_sd_ti_ro == 1 &&
	   bl_fx_cl_cs_gt_sm_s2_ss_ti_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro == 1 &&
	   bl_fx_cl_cs_gt_sd_ti_ro == 1 &&
	   bl_fx_cl_cs_gt_ss_ti_ro  == 1 &&
	   bl_fx_cl_cs_gt_ts == 1 &&
	   bl_fx_cl_iso_dp_ti_ro == 1 &&
	   bl_fx_cl_iso_fp_ti_ro == 1 &&
	   bl_fx_cl_iso_nt_ti_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_cs_gt_ss_ro == 1 &&
	   bl_fx_cl_iso_ts_ps_rt_sd_co == 1 &&
	   bl_fx_cl_iso_ts_ps_rt_ss_co == 1 &&
	   bl_fx_cl_iso_ts_ps_rt_sd_ro == 1 &&
	   bl_fx_cl_iso_ts_ps_rt_ss_ro == 1 &&
	   bl_fx_cl_ps_rt_sd_ti_ro == 1 &&
	   bl_fx_cl_ps_rt_ss_ti_ro == 1 &&
	   bl_fx_cl_ps_rt_ts == 1)
    {

        boolean = 1;

    }

    if (boolean == 1)
    {

        WDB[ader_test_block + ADER_TEST_NUM_PASSED] += 1.0;

        strcpy(status, "pass");

        memset(print_data, 0, strlen(print_data));

        PrintTest(test_name, status, print_data, append);

    }
    else
    {

        WDB[ader_test_block + ADER_TEST_NUM_FAILED] += 1.0;

        strcpy(status, "fail");

        PrintTest(test_name, status, print_data, append);

        sprintf(print_data, "\nSub-tests passing: %ld / 50:", tests_passing);

        PrintTest(test_name, status, print_data, 1);

        /* We do not report out the allocation boolean because the program    */
        /* seg fault if that boolean would not pass                           */

        if(bl_nf_nc_ps_rt_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Zero flux non-cluster proportional removal table stream to iso row: FAIL:\n\
  Isotope V-51 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from proportional removal table removal stream rV51 in material TestTank.\n\
  Variable family in test - nf_nc_ps_rt_ti_ro\n",
                    tv_nf_nc_ps_rt_ti_ro, v51_testtank_index,
					v51_testtank_index, pv_nf_nc_ps_rt_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Zero flux non-cluster proportional removal table stream to iso row: PASS\n\
  Variable family in test - nf_nc_ps_rt_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_nf_nc_iso_dy_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Zero flux non-cluster isotope decay rate: FAIL:\n\
  Isotope U-233 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  Variable family in test - nf_nc_iso_dy_ti_ro\n",
                    tv_nf_nc_iso_dy_ti_ro, u233_testtank_index,
					u233_testtank_index, pv_nf_nc_iso_dy_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Zero flux non-cluster isotope decay rate: PASS\n\
  Variable family in test - nf_nc_iso_dy_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_nf_cl_ps_gt_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Zero flux cluster proportional group type source stream to iso row: FAIL:\n\
  Isotope Li-6 in material Lithium7 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from proportional group type feed stream Li6 in material Lithium7.\n\
  Variable family in test - nf_cl_ps_gt_ss_ti_ro\n",
                    tv_nf_cl_ps_gt_ss_ti_ro, li6_lithium7_index,
					li6_lithium7_index, pv_nf_cl_ps_gt_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Zero flux cluster proportional group type source stream to iso row: PASS\n\
  Variable family in test - nf_cl_ps_gt_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_nf_cl_ps_gt_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Zero flux cluster proportional group type destination stream to iso row:\n\
  FAIL:\n\
  Isotope Li-6 in material Fluorine1 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from proportional group type feed stream Li6 in material Fluorine1.\n\
  Variable family in test - nf_cl_ps_gt_sd_ti_ro\n",
                    tv_nf_cl_ps_gt_sd_ti_ro, li6_fluorine1_index,
					li6_lithium7_index, pv_nf_cl_ps_gt_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Zero flux cluster proportional group type destination stream to iso row:\n\
  PASS\n\
  Variable family in test - nf_cl_ps_gt_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_gt_ts == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type stream self value: FAIL:\n\
  Continuous group type stream H1 in material TestTank\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_cs_gt_ts\n",
                    tv_fx_nc_cs_gt_ts, h1_testtank_feed_stream_index,
					h1_testtank_feed_stream_index, pv_fx_nc_cs_gt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type stream self value: PASS\n\
  Variable family in test - fx_nc_cs_gt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_ps_rt_ts == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster proportional removal table stream self value: FAIL:\n\
  Proportional removal table stream rV51 in material TestTank\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_ps_rt_ts\n",
                    tv_fx_nc_ps_rt_ts, rv51_testtank_remv_stream_index,
					rv51_testtank_remv_stream_index, pv_fx_nc_ps_rt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster proportional removal table stream self value: PASS\n\
  Variable family in test - fx_nc_ps_rt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_rt_ts == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous removal table stream self value: FAIL:\n\
  Continuous removal table stream rW186 in material TestTank\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_cs_rt_ts\n",
                    tv_fx_nc_cs_rt_ts, rw186_testtank_remv_stream_index,
					rw186_testtank_remv_stream_index, pv_fx_nc_cs_rt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous removal table stream self value: PASS\n\
  Variable family in test - fx_nc_cs_rt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_cs_gt_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type stream row: FAIL:\n\
  H-1 in material TestTank has given H1 continuous group type feed stream\n\
  a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_ro\n",
                    tv_fx_nc_iso_ts_cs_gt_ro, h1_testtank_feed_stream_index,
					h1_testtank_index, pv_fx_nc_iso_ts_cs_gt_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type stream row: PASS\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_cs_rt_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous removal table stream row: FAIL:\n\
  W-186 in material TestTank has given rW186 continuous removal table removal\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_iso_ts_cs_rt_ro\n",
                    tv_fx_nc_iso_ts_cs_rt_ro, rw186_testtank_remv_stream_index,
					w186_testtank_index, pv_fx_nc_iso_ts_cs_rt_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous removal table stream row: PASS\n\
  Variable family in test - fx_nc_iso_ts_cs_rt_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_ps_rt_co == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to proportional removal table stream column: FAIL:\n\
  V-51 in material TestTank has value of %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E in the\n\
  column corresponding to the rV51 removal table removal stream in TestTank.\n\
  Variable family in test - fx_nc_iso_ts_ps_rt_co\n",
                    tv_fx_nc_iso_ts_ps_rt_co, v51_testtank_index,
					rv51_testtank_remv_stream_index, pv_fx_nc_iso_ts_ps_rt_co);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to proportional removal table stream column: PASS\n\
  Variable family in test - fx_nc_iso_ts_ps_rt_co\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_ps_rt_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to proportional removal table stream row: FAIL:\n\
  V-51 in material TestTank has given rV51 proportional removal table removal\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_nc_iso_ts_ps_rt_ro\n",
                    tv_fx_nc_iso_ts_ps_rt_ro, rv51_testtank_remv_stream_index,
					v51_testtank_index, pv_fx_nc_iso_ts_ps_rt_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to proportional removal table stream row: PASS\n\
  Variable family in test - fx_nc_iso_ts_ps_rt_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_gt_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type stream to iso row: FAIL:\n\
  Isotope H-1 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous group type feed stream H1 in material TestTank.\n\
  Variable family in test - fx_nc_cs_gt_ti_ro\n",
                    tv_fx_nc_cs_gt_ti_ro, h1_testtank_index,
					h1_testtank_feed_stream_index, pv_fx_nc_cs_gt_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type stream to iso row: PASS\n\
  Variable family in test - fx_nc_cs_gt_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_rt_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous removal table stream to iso row: FAIL:\n\
  Isotope W-186 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous removal table removal stream rW186 in material TestTank.\n\
  Variable family in test - fx_nc_cs_rt_ti_ro\n",
                    tv_fx_nc_cs_rt_ti_ro, w186_testtank_index,
					rw186_testtank_remv_stream_index, pv_fx_nc_cs_rt_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous removal table stream to iso row: PASS\n\
  Variable family in test - fx_nc_cs_rt_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_gt_sm_s1_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type first summation stream to iso row: FAIL\n\
  Ta-181 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  Ta181 in feed sum stream V51Ta181 in material TestTank.\n\
  Variable family in test - fx_nc_cs_gt_sm_s1_ti_ro\n",
                    tv_fx_nc_cs_gt_sm_s1_ti_ro, ta181_testtank_index,
					ta181_testtank_feed_sum_stream_index,
					pv_fx_nc_cs_gt_sm_s1_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type first summation stream to iso row: PASS\n\
  Variable family in test - fx_nc_cs_gt_sm_s1_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_cs_gt_sm_s2_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type second summation stream to iso row: FAIL\n\
  V-51 in material TestTank has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  V51 in feed sum stream V51Ta181 in material TestTank.\n\
  Variable family in test - fx_nc_cs_gt_sm_s2_ti_ro\n",
                    tv_fx_nc_cs_gt_sm_s2_ti_ro, v51_testtank_index,
					v51_testtank_feed_sum_stream_index,
					pv_fx_nc_cs_gt_sm_s2_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster continuous group type first summation stream to iso row: PASS\n\
  Variable family in test - fx_nc_cs_gt_sm_s2_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_cs_gt_sm_s1_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type first summation stream row: FAIL\n\
  Ta181 summation stream in parent feed stream V51Ta181 in material TestTank\n\
  has value %1.15E at matrix location [ %ld , %ld ]\n\
  but should have value %1.15E from Ta181 iso in material TestTank.\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_sm_s1\n",
                    tv_fx_nc_iso_ts_cs_gt_sm_s1_ro,
					ta181_testtank_feed_sum_stream_index,
					ta181_testtank_index,
					pv_fx_nc_iso_ts_cs_gt_sm_s1_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type first summation stream row: PASS\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_sm_s1\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_nc_iso_ts_cs_gt_sm_s2_ro == 0)
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type first summation stream row: FAIL\n\
  V51 summation stream in parent feed stream V51Ta181 in material TestTank\n\
  has value %1.15E at matrix location [ %ld , %ld ]\n\
  but should have value %1.15E from V51 iso in material TestTank.\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_sm_s2\n",
                    tv_fx_nc_iso_ts_cs_gt_sm_s2_ro,
					v51_testtank_feed_sum_stream_index,
					v51_testtank_index,
					pv_fx_nc_iso_ts_cs_gt_sm_s2_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Non-cluster iso to continuous group type first summation stream row: PASS\n\
  Variable family in test - fx_nc_iso_ts_cs_gt_sm_s2\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_rt_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous removal table source side stream to iso row: FAIL:\n\
  Isotope Li-7 in material Lithium7 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous removal table removal stream rLi7 in material Lithium7.\n\
  Variable family in test - fx_cl_cs_rt_ss_ti_ro\n",
                    tv_fx_cl_cs_rt_ss_ti_ro, li7_lithium7_index,
					rli7_lithium7_remv_stream_index, pv_fx_cl_cs_rt_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous removal table source side stream to iso row: PASS\n\
  Variable family in test - fx_cl_cs_rt_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_rt_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous removal table destination side stream to iso row: FAIL:\n\
  Isotope Li-7 in material Fluorine1 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous removal table feed stream rLi7 in material Fluorine1.\n\
  Variable family in test - fx_cl_cs_rt_sd_ti_ro\n",
                    tv_fx_cl_cs_rt_sd_ti_ro, li7_fluorine1_index,
					rli7_fluorine1_remv_stream_index, pv_fx_cl_cs_rt_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous removal table destination side stream to iso row: PASS\n\
  Variable family in test - fx_cl_cs_rt_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_rt_ts == 0)
        {

            sprintf(print_data, "\nTest: Continuous removal table stream self value: FAIL:\n\
  Continuous removal table stream rLi7 in material Lithium7\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_cs_rt_ts\n",
                    tv_fx_cl_cs_rt_ts, rli7_lithium7_remv_stream_index,
					rli7_lithium7_remv_stream_index, pv_fx_cl_cs_rt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous removal table stream self value: PASS\n\
  Variable family in test - fx_cl_cs_rt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_rt_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous removal table source side stream row: FAIL:\n\
  Li-7 in material Lithium7 has given rLi7 continuous removal table removal\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_iso_ts_cs_rt_ss_ro\n",
                    tv_fx_cl_iso_ts_cs_rt_ss_ro, rli7_lithium7_remv_stream_index,
					li7_lithium7_index, pv_fx_cl_iso_ts_cs_rt_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous removal table source side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_rt_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_rt_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous removal table destination side stream row: FAIL:\n\
  Li-7 in material Fluorine1 has given rLi7 continuous removal table feed\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_iso_ts_cs_rt_sd_ro\n",
                    tv_fx_cl_iso_ts_cs_rt_sd_ro, rli7_fluorine1_remv_stream_index,
					li7_fluorine1_index, pv_fx_cl_iso_ts_cs_rt_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous removal table destination side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_rt_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_gt_sd_co == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional group type destination side stream column: FAIL:\n\
  Li-6 in material Fluorine1 has value of %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E in the\n\
  column corresponding to the Li6 group type feed stream in Fluorine1.\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_sd_co\n",
                    tv_fx_cl_iso_ts_ps_gt_sd_co, li6_fluorine1_index,
					li6_fluorine1_remv_stream_index, pv_fx_cl_iso_ts_ps_gt_sd_co);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional group type destination side stream column: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_sd_co\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_gt_ss_co == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional group type source side stream column: FAIL:\n\
  Li-6 in material Lithium7 has value of %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E in the\n\
  column corresponding to the Li6 group type remv stream in Lithium7.\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_ss_co\n",
                    tv_fx_cl_iso_ts_ps_gt_ss_co, li6_lithium7_index,
					li6_lithium7_remv_stream_index, pv_fx_cl_iso_ts_ps_gt_ss_co);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional group type source side stream column: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_ss_co\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_gt_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional group type destination side stream row: FAIL:\n\
  The Li6 proportional group type feed stream in material Fluorine1 has\n\
  value of %1.15E at matrix location [ %ld , %ld ] but should have\n\
  value of %1.15E in the column corresponding to the Li6\n\
  isotope in material Fluorine1.\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_sd_ro\n",
                    tv_fx_cl_iso_ts_ps_gt_sd_ro, li6_fluorine1_remv_stream_index,
					li6_fluorine1_index, pv_fx_cl_iso_ts_ps_gt_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional group type destination side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_gt_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional group type source side stream row: FAIL:\n\
  The Li6 proportional group type remv stream in material Lithium7 has\n\
  value of %1.15E at matrix location [ %ld , %ld ] but should have\n\
  value of %1.15E in the column corresponding to the Li6\n\
  isotope in material Lithium7.\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_ss_ro\n",
                    tv_fx_cl_iso_ts_ps_gt_ss_ro, li6_lithium7_remv_stream_index,
					li6_lithium7_index, pv_fx_cl_iso_ts_ps_gt_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional group type source side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_gt_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_ps_gt_ts == 0)
        {

            sprintf(print_data, "\nTest: Proportional group type stream self value: FAIL:\n\
  Proportional group type stream Li6 in material Lithium7\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_ps_gt_ts\n",
                    tv_fx_cl_ps_gt_ts, li6_lithium7_remv_stream_index,
					li6_lithium7_remv_stream_index, pv_fx_cl_ps_gt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Proportional group type stream self value: PASS\n\
  Variable family in test - fx_cl_ps_gt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_sm_s1_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type first summation destination side stream\n\
to iso row: FAIL:\n\
  Li-6 in material Fluorine1 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  Li6 in feed sum stream Li6Li7 in material Fluorine1.\n\
  Variable family in test - fx_cl_cs_gt_sm_s1_sd_ti_ro\n",
                    tv_fx_cl_cs_gt_sm_s1_sd_ti_ro, li6_fluorine1_index,
					li6_fluorine1_remv_sum_stream_index,
					pv_fx_cl_cs_gt_sm_s1_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type first summation destination side stream\n\
to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_sm_s1_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_sm_s1_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type first summation source side stream\n\
to iso row: FAIL:\n\
  Li-6 in material Lithium7 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  Li6 in removal sum stream Li6Li7 in material Lithium7.\n\
  Variable family in test - fx_cl_cs_gt_sm_s1_ss_ti_ro\n",
                    tv_fx_cl_cs_gt_sm_s1_ss_ti_ro, li6_lithium7_index,
					li6_lithium7_remv_sum_stream_index,
					pv_fx_cl_cs_gt_sm_s1_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type first summation source side stream\n\
to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_sm_s1_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_sm_s2_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type second summation destination side stream\n\
to iso row: FAIL:\n\
  Li-7 in material Fluorine1 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  Li7 in feed sum stream Li6Li7 in material Fluorine1.\n\
  Variable family in test - fx_cl_cs_gt_sm_s2_sd_ti_ro\n",
                    tv_fx_cl_cs_gt_sm_s2_sd_ti_ro, li6_fluorine1_index,
					li6_fluorine1_remv_sum_stream_index,
					pv_fx_cl_cs_gt_sm_s2_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type second summation destination side stream\n\
to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_sm_s2_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_sm_s2_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type second summation source side stream\n\
to iso row: FAIL:\n\
  Li-7 in material Lithium7 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value %1.15E from summation stream\n\
  Li7 in removal sum stream Li6Li7 in material Lithium7.\n\
  Variable family in test - fx_cl_cs_gt_sm_s2_ss_ti_ro\n",
                    tv_fx_cl_cs_gt_sm_s2_ss_ti_ro, li7_lithium7_index,
					li7_lithium7_remv_sum_stream_index,
					pv_fx_cl_cs_gt_sm_s2_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type second summation source side stream\n\
to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_sm_s2_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type first summation destination side stream\n\
row: FAIL:\n\
  Li6 summation stream in parent feed stream Li6Li7 in material Fluorine1\n\
  has value %1.15E at matrix location [ %ld , %ld ] but should\n\
  have value %1.15E from Li-6 iso in material Fluorine1.\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s1_sd_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro,
					li6_fluorine1_remv_sum_stream_index,
					li6_fluorine1_index,
					pv_fx_cl_iso_ts_cs_gt_sm_s1_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type first summation destination side stream\n\
row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s1_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type first summation source side stream\n\
row: FAIL:\n\
  Li6 summation stream in parent remv stream Li6Li7 in material Lithium7\n\
  has value %1.15E at matrix location [ %ld , %ld ] but should\n\
  have value %1.15E from Li-6 iso in material Lithium7.\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s1_ss_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro,
					li6_lithium7_remv_sum_stream_index,
					li6_lithium7_index,
					pv_fx_cl_iso_ts_cs_gt_sm_s1_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type first summation source side stream\n\
row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s1_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type second summation destination side stream\n\
row: FAIL:\n\
  Li7 summation stream in parent feed stream Li6Li7 in material Fluorine1\n\
  has value %1.15E at matrix location [ %ld , %ld ] but should\n\
  have value %1.15E from Li-7 iso in material Fluorine1.\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s2_sd_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro,
					li7_fluorine1_remv_sum_stream_index,
					li7_fluorine1_index,
					pv_fx_cl_iso_ts_cs_gt_sm_s2_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type second summation destination side stream\n\
row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s2_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type second summation source side stream\n\
row: FAIL:\n\
  Li7 summation stream in parent remv stream Li6Li7 in material Lithium7\n\
  has value %1.15E at matrix location [ %ld , %ld ] but should\n\
  have value %1.15E from Li-7 iso in material Lithium7.\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s2_ss_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro,
					li7_lithium7_remv_sum_stream_index,
					li7_lithium7_index,
					pv_fx_cl_iso_ts_cs_gt_sm_s2_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type second summation source side stream\n\
row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sm_s2_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type destination side stream to iso row: FAIL:\n\
  Isotope F-19 in material Uranium233 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous group type redox stream Fluorine in material Uranium233.\n\
  Variable family in test - fx_cl_cs_gt_sd_ti_ro\n",
                    tv_fx_cl_cs_gt_sd_ti_ro, f19_uranium233_index,
					fluorine_uranium233_redox_stream_index, pv_fx_cl_cs_gt_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type destination side stream to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type source side stream to iso row: FAIL:\n\
  Isotope F-19 in material Fluorine0 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from continuous group type redox stream Fluorine in material Fluorine0.\n\
  Variable family in test - fx_cl_cs_gt_ss_ti_ro\n",
                    tv_fx_cl_cs_gt_ss_ti_ro, f19_fluorine0_index,
					fluorine_fluorine0_redox_stream_index, pv_fx_cl_cs_gt_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type source side stream to iso row: PASS\n\
  Variable family in test - fx_cl_cs_gt_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_cs_gt_ts == 0)
        {

            sprintf(print_data, "\nTest: Continuous group type stream self value: FAIL:\n\
  Continuous group type stream Fluorine in material Fluorine0\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_cs_gt_ts\n",
                    tv_fx_cl_cs_gt_ts, fluorine_fluorine0_redox_stream_index,
					fluorine_fluorine0_redox_stream_index, pv_fx_cl_cs_gt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Continuous group type stream self value: PASS\n\
  Variable family in test - fx_cl_cs_gt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_dp_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Isotope decay product production: FAIL:\n\
  Np-239 in material FLiBeFuel has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have a value greater than 0 from the\n\
  decay of U-239 in FLiBeFuel\n\
  Variable family in test - fx_cl_iso_dp_ti_ro\n",
                    tv_fx_cl_iso_dp_ti_ro, np239_flibefuel_index,
					u239_flibefuel_index);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Isotope decay product production: PASS\n\
  Variable family in test - fx_cl_iso_dp_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_fp_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Isotope fission product production: FAIL:\n\
  Xe-135 in material FLiBeFuel has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have a value greater than 0 from the\n\
  fission of U-233 in FLiBeFuel\n\
  Variable family in test - fx_cl_iso_fp_ti_ro\n",
                    tv_fx_cl_iso_fp_ti_ro, xe135_flibefuel_index,
					u233_flibefuel_index);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Isotope fission product production: PASS\n\
  Variable family in test - fx_cl_iso_fp_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_nt_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Isotope transmutation product production: FAIL:\n\
  H-3 in material FLiBeFuel has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have a value greater than 0 from the\n\
  transmutation of Li-6 in FLiBeFuel\n\
  Variable family in test - fx_cl_iso_nt_ti_ro\n",
                    tv_fx_cl_iso_nt_ti_ro, h3_flibefuel_index,
					li6_flibefuel_index);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Isotope transmutation product production: PASS\n\
  Variable family in test - fx_cl_iso_nt_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type destination side stream row: FAIL:\n\
  F-19 in material Uranium233 has given Fluorine continuous group type feed\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sd_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_sd_ro, fluorine_uranium233_redox_stream_index,
					f19_uranium233_index, pv_fx_cl_iso_ts_cs_gt_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type destination side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_cs_gt_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to continuous group type source side stream row: FAIL:\n\
  F-19 in material Fluorine0 has given Fluorine continuous group type feed\n\
  stream a value of %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_ss_ro\n",
                    tv_fx_cl_iso_ts_cs_gt_ss_ro, fluorine_fluorine0_redox_stream_index,
					f19_fluorine0_index, pv_fx_cl_iso_ts_cs_gt_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to continuous group type source side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_cs_gt_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_rt_sd_co == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table destination side stream column: FAIL:\n\
  Li-7 in material Argon40 has value of %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E in the\n\
  column corresponding to the reproc removal table feed stream in Argon40.\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_sd_co\n",
                    tv_fx_cl_iso_ts_ps_rt_sd_co, li7_argon40_index,
					reproc_argon40_remv_stream_index, pv_fx_cl_iso_ts_ps_rt_sd_co);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table destination side stream column: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_sd_co\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_rt_sd_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table destination side stream row: FAIL:\n\
  reproc proportional removal table feed stream in material Argon40 has value\n\
  of %1.15E at matrix location [ %ld , %ld ] but should have value\n\
  of %1.15E in the column corresponding to Li-7 in Argon40.\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_sd_ro\n",
                    tv_fx_cl_iso_ts_ps_rt_sd_ro, reproc_argon40_remv_stream_index,
					li7_argon40_index, pv_fx_cl_iso_ts_ps_rt_sd_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table destination side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_sd_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_rt_ss_co == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table source side stream column: FAIL:\n\
  Li-7 in material FLiBeFuel has value of %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E in the\n\
  column corresponding to the reproc removal table remv stream in FLiBeFuel.\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_ss_co\n",
                    tv_fx_cl_iso_ts_ps_rt_ss_co, li7_flibefuel_index,
					reproc_flibefuel_remv_stream_index, pv_fx_cl_iso_ts_ps_rt_ss_co);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table source side stream column: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_ss_co\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_iso_ts_ps_rt_ss_ro == 0)
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table source side stream row: FAIL:\n\
  reproc proportional removal table feed stream in material Argon40 has value\n\
  of %1.15E at matrix location [ %ld , %ld ] but should have value\n\
  of %1.15E in the column corresponding to Li-7 in Argon40.\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_ss_ro\n",
                    tv_fx_cl_iso_ts_ps_rt_ss_ro, reproc_flibefuel_remv_stream_index,
					li7_flibefuel_index, pv_fx_cl_iso_ts_ps_rt_ss_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Iso to proportional removal table source side stream row: PASS\n\
  Variable family in test - fx_cl_iso_ts_ps_rt_ss_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_ps_rt_sd_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Proportional removal table destination stream to iso row: FAIL:\n\
  Isotope He-4 in material Argon40 has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from proportional removal table feed stream reproc in material Argon40.\n\
  Variable family in test - fx_cl_ps_rt_sd_ti_ro\n",
                    tv_fx_cl_ps_rt_sd_ti_ro, he4_argon40_index,
					he4_flibefuel_index, pv_fx_cl_ps_rt_sd_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Proportional removal table destination stream to iso row: PASS\n\
  Variable family in test - fx_cl_ps_rt_sd_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_ps_rt_ss_ti_ro == 0)
        {

            sprintf(print_data, "\nTest: Proportional removal table source stream to iso row: FAIL:\n\
  Isotope He-4 in material FLiBeFuel has value %1.15E at matrix\n\
  location [ %ld , %ld ] but should have value of %1.15E\n\
  from proportional removal table removal stream reproc in material FLiBeFuel.\n\
  Variable family in test - fx_cl_ps_rt_ss_ti_ro\n",
                    tv_fx_cl_ps_rt_ss_ti_ro, he4_flibefuel_index,
					he4_flibefuel_index, pv_fx_cl_ps_rt_ss_ti_ro);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Proportional removal table source stream to iso row: PASS\n\
  Variable family in test - fx_cl_ps_rt_ss_ti_ro\n");

            PrintTest(test_name, status, print_data, 1);

        }

        if(bl_fx_cl_ps_rt_ts == 0)
        {

            sprintf(print_data, "\nTest: Proportional removal table stream self value: FAIL:\n\
  Proportional removal table stream reproc in material FLiBeFuel\n\
  has value %1.15E at matrix location [ %ld , %ld ] but\n\
  should have value of %1.15E\n\
  Variable family in test - fx_cl_ps_rt_ts\n",
                    tv_fx_cl_ps_rt_ts, reproc_flibefuel_remv_stream_index,
					reproc_flibefuel_remv_stream_index, pv_fx_cl_ps_rt_ts);

            PrintTest(test_name, status, print_data, 1);

        }
        else
        {

            sprintf(print_data, "\nTest: Proportional removal table stream self value: PASS\n\
  Variable family in test - fx_cl_ps_rt_ts\n");

            PrintTest(test_name, status, print_data, 1);

        }

    }

}
