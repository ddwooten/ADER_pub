Author: Daniel Wooten
Date: 06/07/2018

Test Name: 20_Test

Key Concepts/Relationships Being Tested: 
    Streams, group class, continuous, into a mat 
    Streams, group class, continuous, out of a mat 
    Cnd table, range, range
    Opt, max, removal 

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.2
9019 0.3
18040 0.4
92235 0.1

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.1
9019 ~0.3
18040 ~0.5
92235 ~0.1

Stream gH1 should have transfer amount from Tank1 of 0.1
Stream gAr40 should have transfer amount into Tank1 of 0.1

Status: PASS
