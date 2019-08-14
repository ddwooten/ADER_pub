Author: Daniel Wooten
Date: 06/01/2018

Test Name: 18_Test

Key Concepts/Relationships Being Tested: 
    Streams, group class, discrete, into a mat, summation
    Streams, group class, discrete, between two mats, summation 
    Streams, group class, discrete, out of a mat
    Cnd table, range, value 
    Opt, min, all streams

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.3
1002 0.2
18040 0.1
92235 0.4

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.4
1002 ~0.1
18040 ~0.1
92235 ~0.4

Tank2 begins with:
MATERIA_ADENS 1.0
1001 0.25
1002 0.35
18040 0.25
92235 0.15

Tank2 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.25
1002 ~0.25?
18040 ~0.25?
92235 ~0.15

Stream gH1U should have transfer amount from Tank1 of 0.1
Stream gH2Ar should have transfer amount from Tank1 of 0.1
Stream gU should have transfer amount from Tank2 of 0.1

Status: PASS
