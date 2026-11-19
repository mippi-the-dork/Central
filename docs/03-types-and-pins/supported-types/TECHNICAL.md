# Supported Data Types — Technical

**Central v1.0.0 · Type and graph behavior**

## Static supported-type lookup

`CentralEditorPrivate::Types` lists the supported schema categories and the runtime function suffix for each type. `CentralEditorPrivate::Match` checks the input `FEdGraphPinType`, including the container type, scalar pin category, struct subtype and enum metadata.

## Integer promotion

`RefreshTypes` uses `CentralEditorPrivate::ScalarOf` to remove the array container, then overrides the output to a `PC_Real` / `PC_Double` pin when the operation is Mean, Median or Weighted Mean and the resolved input suffix is Int, Int64 or Byte.

## Struct types

Struct matching uses the reflected struct information and supported Vector2D, Vector, Vector4 or Linear Color implementation rather than treating any `PC_Struct` as valid. Mode additionally supports Rotator.

## Category-only Mode types

String, Name, Boolean and supported enums only resolve when the operation is Mode. Averaging nonnumeric categories would not have a defined mathematical meaning in the current API.

## Runtime target consistency

Every supported graph type must resolve to a `UCentralBPLibrary` function named from the operation and type suffix, or `ExpandNode` reports an internal function lookup error. Type availability is therefore a contract between `K2Node_Central.cpp` and `CentralBPLibrary.h/.cpp`.

## Compatibility boundary

The table describes v1.0.0 source. Do not assume that a newer UE struct type, an unsupported native enum representation, or an arbitrary user struct inherits eligibility from a related type.

## Source references

- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design guide](DESIGN.md) · Source-reviewed, not a claim of live editor QA.
