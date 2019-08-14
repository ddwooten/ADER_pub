Author: Daniel Wooten
Date: 05/31/2018

Test Name: 17_Test

Key Concepts/Relationships Being Tested: 
    Streams, group class, continuous, into a mat, summation
    Streams, group class, discrete, between two mats 
    Streams, group class, discrete, out of a mat, summation
    Cnd table, range, value, summation 
    Opt, max, feed and removal

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.2
1002 0.2
18040 0.5
92235 0.1

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.4
1002 ~0.2
18040 ~0.3
92235 ~0.1

Tank2 begins with:
MATERIA_ADENS 0.5
1001 0.1
1002 0.15
18040 0.1
92235 0.15

Tank2 ends with:
MATERIAL_ADENS ~0.5
1001 ~0.1
1002 ~0.1
18040 ~0.3
92235 ~0.0

Stream gH1H2 should have transfer amount to Tank1 of 0.2
Stream gH2U should have transfer amount from Tank2 of 0.2
Stream gAr should have transfer amount from Tank1 of 0.2
Stream gH1H2x should have transfer amount to Tank1 of 0.0
Stream gH2Ux should have transfer amount from Tank2 of 0.0
Stream gAr40 should have transfer amount from Tank1 of 0.0

Status: PASS
