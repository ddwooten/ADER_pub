Author: Daniel Wooten
Date: 05/29/2018

Test Name: 16_Test

Key Concepts/Relationships Being Tested: 
    Streams, group class, proportional, between two mats 
    Streams, group class, continuous, out of a mat, summation
    Cnd table, range, summation
    Opt, max, feed

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.3
1002 0.2
18040 0.4
92235 0.1

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.125
1002 ~0.20
18040 ~0.4
92235 ~0.275

Tank2 begins with:
MATERIA_ADENS 0.5
1001 0.1
1002 0.1
18040 0.125
92235 0.175

Tank2 ends with:
MATERIAL_ADENS ~0.5
1001 ~0.275
1002 ~0.1
18040 ~0.125
92235 ~0.0

Stream gH1H2 should have transfer amount from Tank1 of 0.175
Stream gU should have transfer amount from Tank2 of ~0.175

Status: PASS
