Author: Daniel Wooten
Date: 05/02/2018

Test Name: 13_Test

Key Concepts/Relationships Being Tested: 
    Streams, group-class, proportional type, from a material
    Streams, group class, discrete, to a material
    Groups, summation 
    Cnd table, ratios, bounds
    Opt,max, removal

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.5
9019 0.3
18040 0.0
92235 0.2

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.5
9019 ~0.00
18040 ~0.30
92235 ~0.20

Stream gF19 should have transfer amount ~0.3
Stream gU235 should have transfer amount 0.0
Stream gsAr40 should have transfer amount ~0.3

Status: PASS
