Tritium
=========

A tritium calculation engine

**_Note: Still in code design. Engine does not build, only design components._**

**_Note: Backwards compatibility will be broken on migration to Protium and Deuterium._**

#Notes On Dimensional Analysis

Tritium Implements a system of meaningful dimensional analysis.

This supports conversion between dimensions using the `*` and `/` operators.

Therefore the folling should compile:
```
TriScalar scaler =TriRate(1.0)*TriTime(1.0);//This works
TriAction act =	TriEnergy(20.0)*TriTime(5.0);//Also works
```
This should not:
```
TriScalar doesntWork = TriTime(0.0)*TriTime(0.0); //This doesn't work
```
This produces the following compile-time error:
```
error: invalid use of incomplete type ‘struct CompileTimeError<0>’
             ERROR_QUANTITIES_NOT_EQUAL_DIMENSIONS() );
```