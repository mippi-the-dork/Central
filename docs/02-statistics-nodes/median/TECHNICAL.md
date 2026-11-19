# Median Value — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Runtime code path

The typed runtime entry points include `MedianInt`, `MedianInt64`, `MedianByte`, `MedianFloat`, `MedianDouble`, `MedianVector2D`, `MedianVector`, `MedianVector4` and `MedianLinearColor`.

`CentralPrivate::Median(TArray<T> Values, ...)` takes an array **by value** and sorts that local working data. Numeric integer-family median also uses a Double result to preserve fractions.

## Even-count calculation

For `n` sorted values, the middle is `n/2`. If `n` is even, the result comes from the entries at `n/2 - 1` and `n/2`; otherwise from `n/2`. `ComponentAverage` handles supported scalar/struct arithmetic.

## Component-wise specializations

Median for Vector2D, Vector, Vector4 and Linear Color constructs per-component ordered results (X/Y/Z/W or R/G/B/A). It does not select one complete input vector as the median or measure distances in vector space.

## Complexity and data integrity

Sorting working values yields **O(n log n)** time for ordinary comparison sorting and requires additional memory. The caller's array is const and unmodified. Engine floating-point behavior and finite checks determine numerical limitations.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
