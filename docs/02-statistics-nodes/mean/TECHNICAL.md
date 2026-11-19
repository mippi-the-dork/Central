# Mean Value — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Implementations

`UCentralBPLibrary::MeanInt`, `MeanInt64`, `MeanByte`, `MeanFloat`, `MeanDouble`, `MeanVector2D`, `MeanVector`, `MeanVector4` and `MeanLinearColor` provide the typed runtime endpoints.

The generic `CentralPrivate::Mean<T>` and `NumericMean<T>` helpers implement the operation. The integer-family entry points use Double outputs to retain fractional values.

## Finite-value validation

The helper `Finite<T>` is specialized for floating-point scalars and supported math structures. Invalid numeric components invalidate the result. Output defaults are used on failure, and `bHasValue` distinguishes valid zero from failure.

## Component-wise treatment

For FVector2D/FVector/FVector4/FLinearColor, the generic math adds and divides the corresponding components; it is not geometric mean or a calculation based on vector magnitudes.

## Complexity and precision

Mean traverses the array in expected **O(n)** time and does not sort or modify it. Floating-point rounding remains possible, especially with large magnitudes and Integer64 values converted to Double. The implementation makes no promise of exact arbitrary-precision arithmetic.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
