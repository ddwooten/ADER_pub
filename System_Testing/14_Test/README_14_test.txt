Author: Daniel Wooten
Date: 05/18/2018

Test Name: 14_Test

Key Concepts/Relationships Being Tested: 
    Streams, table-class, discrete, from a material
    Streams, group-class, proportional type, to a material
    Streams, group class, discrete, from a material
    Groups, summation 
    Groups, mixed isotopes
    Elemental control
    Isotopic control
    Preserve mols
    Cnd table, ratios, value 
    Opt,min, reac

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.7
1002 0.2
18040 0.0
92235 0.1

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001 ~0.3
1002 ~0.2
18040 ~0.40
92235 ~0.1

Stream rH1 should have transfer amount ~0.14
Stream gH1 should have transfer amount ~0.26
Stream gAr40 should have transfer amount ~0.4
Stream gH2 should have transfer amount 0.0

Notes: The actual moved value of the rH1 stream is lower, versus the desired,
becuase of the discrete removal of H1 by the other stream. i

Status: PASS
