Author: Daniel Wooten
Date: 05/21/2018

Test Name: 15_Test

Key Concepts/Relationships Being Tested: 
    Streams, Table-class, continuous type, out of a material
    Streams, group class, discrete, between two mats, summation
    Streams, group class, continuous, out of a mat
    Groups, summation
    Cnd table, ratios, value 
    Opt, min
    Opt, transfers
    Oxi, restrictions, value
    Oxi, table, values
    Oxi, table, weights

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.25
9019 0.0
18040 0.25
92235 0.5

Tank1 ends with:
MATERIAL_ADENS ~0.875
1001 ~0.125
9019 ~0.0
18040 ~0.25
92235 ~0.5

Tank2 begins with:
MATERIA_ADENS 0.5
1001 0.0
9019 0.5
18040 0.0
92235 0.5

Tank2 ends with:
MATERIAL_ADENS ~0.625
1001 ~0.125
9019 ~0.25
18040 ~0.0
92235 ~0.25

Stream gH should have transfer amount from Tank1 of 0.125 
Stream rAr should have transfer amount from Tank1 of ~0.125
Stream gArU should have transfer amount ~0.125 ( 0.125 of Ar and 0.0 of U )
Stream gU should have transfer amount 0.0

Status: PASS
