Author: Daniel Wooten
Date: 03/29/2019

Test Name: 21_Test

Key Concepts/Relationships Being Tested: 
    Shared memory parallelized collection of cross sections

Pass Criteria: Run the file h1_pu239_bare.txt with the source code
compiled with the -DADER_DIAG flag. Compare the absoprtion and fission
neutron production cross sections for the applicable isotopes (H-1
and Pu-239 primarily) as well as the non-leakage probability and
calculated criticality eigenvalue - all found in the file
fuel_XS_End_of_step_0.txt - against the values as reported by SERPENT2.
The non-leakage probabilities should show some degree of difference, less
than 5%. This is due to ADER using non-leakage probabilities from the n-1
composition of the material, not the most recent. This is a reporting
shortcoming and not an actual code problem. The remainder of differences
should be less than 1% this should be performed as a two part test, part
A with a single thread running the program and part B with multiple threads.

Status: Pass
