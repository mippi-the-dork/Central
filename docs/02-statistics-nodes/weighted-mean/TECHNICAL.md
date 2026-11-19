# Weighted Mean Value — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Typed entry points

`WeightedMeanInt`, `WeightedMeanInt64`, `WeightedMeanByte`, `WeightedMeanFloat`, `WeightedMeanDouble`, `WeightedMeanVector2D`, `WeightedMeanVector`, `WeightedMeanVector4` and `WeightedMeanLinearColor` are available in `UCentralBPLibrary`. Every implementation receives `TArray<double> Weights`.

## Validation

`ValidateWeights` rejects empty input, mismatched lengths, negative weights, non-finite weights and a zero total weight. Numeric Values are also checked for finite data, including entries with zero weight.

## Normalized accumulation

The implementation uses a **maximum-weight normalization** path before accumulating contributions, reducing the risk of some intermediate overflow scenarios when large finite weights would otherwise be multiplied or summed directly. This improves robustness without promising exact arbitrary-precision arithmetic.

## Output typing

Integer, Integer64 and Byte inputs produce Double output. Float, Double and supported vector/color inputs use their corresponding supported output types. Mathematical structures are multiplied/added per coordinate or channel.

## Complexity

Weighted Mean processes each input a bounded number of times, so it is **O(n)** in input count with no sorting of the caller's arrays. Large values and floating-point rounding remain meaningful limitations.

## Blueprint compilation

`UK2Node_Central::ExpandNode` transfers Values, Weights, Value and `bHasValue` to the matching `UCentralBPLibrary` function. A missing or incompatible Weights link cannot be treated as valid input.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
