# Algorithms & Performance — Technical

**Central v1.0.0 · Source-grounded documentation**

## Mean and Weighted Mean

`NumericMean<T>` and the generic `Mean<T>` traverse supported numeric/struct arrays. Weighted Mean validates weights and normalizes by the maximum finite weight before accumulating a weighted result, mitigating some intermediate overflow patterns.

## Median

`Median(TArray<T> Values,...)` takes a copy by value, sorts that copy and returns the middle item or middle-pair average. Component-specific overloads sort coordinate arrays for vectors and colors. For comparison sorting this is typically O(n log n), plus copy/working-data memory.

## Mode

`Mode<T>` uses frequency maps, with per-component keys for complex structs and normalized signed zero for floating-point keys. Expected hashing/counting work is linear in n; worst-case hash behavior and memory overhead depend on key distribution and implementation. Retaining first-encounter order is part of the return contract.

## Finite and precision handling

Non-finite inputs invalidate numeric operations, and invalid weights invalidate weighted means. Double answers for integer-family means/medians can round large Integer64 values. No custom arbitrary-precision or approximate-match algorithm is supplied.

## Performance verification recommendations

Benchmark actual project workloads rather than extrapolating from complexity notation: vary array size, number of unique Mode categories, float vs struct element type, frequency of Blueprint evaluation and platform. Separate runtime calculation cost from Blueprint VM graph overhead and any upstream array-generation cost.

## No unverified claims

The repository has runtime functional assertions but no source evidence here of a completed cross-platform performance benchmark. Avoid claiming specific frame costs or throughput until measured.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
