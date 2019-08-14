Author: Daniel Wooten
Date: 04/01/2018

Test Name: 22_Test

Key Concepts/Relationships Being Tested: 
    Shared memory ( OpenMP ) implementation
    Groups, isotopic
    Groups, elemental
    Groups, summation
    Cnd tables, ranges, value
    Cnd tables, ratios, value
    Elemental control
    Isotopic control
    Molar preservation
    Optimization, maximization, transfers
    Optimization, minimization, group
    Multiple cluster operations
    Streams, group class, discrete, into/out-of mat 
    Streams, group class, continuous, between two mats, summation 
    Streams, table class, proportional, out of a mat
    Burnup
    Reactivity control

Target Result:
Tank1 begins with:
MATERIA_ADENS 1.0
1001 0.60
3006 0.10
18040 0.25
92235 0.05

Tank1 ends with:
MATERIAL_ADENS ~1.0
1001  ~0.30
3006  ~0.05
18040 ~0.55 - delta-U
92235 ~0.05 + delta-U

Tank2 begins with:
MATERIA_ADENS 1.0
1001 0.20
3006 0.60
18040 0.20
92235 0.0

Tank2 ends with:
MATERIAL_ADENS ~1.0
1001  ~0.50
3006  ~0.50
18040 ~0.00
92235 ~0.00

Tank3 begins with:
MATERIA_ADENS 0.01
1001  0.0030 
3006  0.0020 
9019  0.0040 
18040 0.0010 

Tank3 ends with:
MATERIA_ADENS ~0.01
1001  ~0.0030 
3006  ~0.0040
9019  ~0.0020
18040 ~0.0010 

Tank4 begins with:
MATERIA_ADENS 0.01
1001  0.0070 
3006  0.0020
9019  0.0010
18040 0.0000

Tank4 ends with:
MATERIA_ADENS ~0.01
1001  ~0.0070
3006  ~0.0000
9019  ~0.0010
18040 ~0.0020

Stream gU235i should have some value less than gU235o - both of these streams
may have a value and gU235o should have a value
Stream 1gLi should have transfer amount from Tank1 to Tank2 of 0.05
Stream gAr should have transfer amount from Tank2 to Tank 1 of 0.20
Stream 1gAr40 should have transfer amount to Tank 1 of 0.15 - delta-U
Stream 2gLi should have transfer amount from Tank2 of 0.15
Stream rH should have transfer amount from Tank1 to Tank2 of 0.3 


Stream 4gLi should have transfer amount from Tank4 to Tank3 of 0.2
Stream gH1F19 should have transfer amount from Tank3 of 0.2
Stream 4gAr40 should have transfer amount to Tank4 of 0.2

In general reactivity convergence should be checked through the run as well.
The best indicator of final reactivity convergence is the k-eff measure from
the corrector cycles as these incorporate the spectrum changes from 
continuous streams and proportional streams. In general a severe offset will
be seen from the reactivity target and the value that ADER produces in its
criticality search. This is because ADER's criticality routine is aware of the
changes to come in the cycle from non-discrete streams.

Status: PASS
