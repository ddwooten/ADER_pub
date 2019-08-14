Author: Daniel Wooten
Date: 06/06/2018

Test Name: 19_Test

Key Concepts/Relationships Being Tested: 
    Streams, group class, discrete, into a mat
    Streams, group class, discrete, between two mats, summation 
    Opt, min, all streams
    Reactivity, targets

Target Result:
Tank1: 
Den:    1.0
1001    0.1
18040   0.8986
90232   0.0
92235   0.0014
92238   0.0

Tank1 ends with:
MATERIAL_ADENS ~.
1001 0.1
18040 0.89
90232 0.0
92235 0.0008
92238 0.0

Tank2 begins with:
MATERIA_ADENS 1.0
1001 0.0
18040 1.0
90232 0.0
92235 0.0
92238 0.0

Tank2 ends with:
MATERIA_ADENS 1.0
1001 0.0
18040 1.0
90232 0.0
92235 0.0
92238 0.0

Stream gU235i should have transfer amount into Tank1 of 0.0
Stream gU235o should have transfer amount from Tank1 of ~0.0042
Stream gU238i should have transfer amount from Tank2 of 0.0
Stream gU238o should have transfer amount from Tank2 of 0.0
Stream gUThi should have transfer amount from Tank2 of 0.0
Stream gUTho should have transfer amount from Tank2 of 0.0

Status: PASS
