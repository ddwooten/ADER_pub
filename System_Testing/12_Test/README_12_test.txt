Author: Daniel Wooten
Date: 04/07/2018

Test Name: 12_Test

Key Concepts/Relationships Being Tested: 
    Streams, Table-class, proportional type, between two mats 
    Streams, group class, continuous, between two mats 
    Groups, mixed isos
    Groups, full iso
    Cnd table, ratios, bounds
    Opt, spec group 

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.5
9019 0.25
92235 0.25

Tank1 ends with:
MATERIAL_ADENS ~0.6
1001 ~0.4
9019 ~0.10
92235 ~0.10

Tank2 begins with:
MATERIA_ADENS 0.5
1001 0.5
9019 0.0
92235 0.0

Tank2 ends with:
MATERIAL_ADENS ~0.9
1001 ~0.6
9019 ~0.15
92235 ~0.15

Stream sH1 should have transfer amount ~0.1
Stream sUF should have transfer amount ~0.3

Status: PASS
