# Enums & Complex Values — Technical

**Central v1.0.0 · Type and graph behavior**

## Reflected enum execution

`UCentralBPLibrary::ModeEnum` declares a `BlueprintPure` `CustomThunk` using `ArrayParm="Values,Modes"` and `ArrayTypeDependentParams="Value"`. `execModeEnum` inspects reflected input array and element properties at runtime, validates supported integral enum representation and copies properly typed results.

This avoids reinterpreting arbitrary `TArray<Enum>` memory as `TArray<uint8>` without reflection, while keeping the author-visible enum type on graph pins.

## Special compiler handling

When `UK2Node_Central::ExpandNode` identifies enum Mode, it aligns intermediate Values, Modes and Value pin types to the actual connected enum before transferring graph links to the reflected thunk.

## Complex-mode hashing

`FComponentKey` and `MakeComponentKey` provide component-based keys for Vector2D, Vector, Vector4, Linear Color and Rotator. `ComponentBits` and signed-zero normalization support consistent grouping for zero-valued components.

## Component-wise calculation

The runtime's Median specializations treat Vector2D, Vector, Vector4 and Linear Color as independent coordinate/channel samples. Ordinary Mean and Weighted Mean use corresponding component arithmetic. Rotator is only eligible for Mode.

## Unsupported representations

Native enums with incompatible underlying storage, object references and arbitrary struct arrays are not promised. Enum support is tied to the actual reflected type, not a generic conversion of any Blueprint value to an integer.

## Source references

- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design guide](DESIGN.md) · Source-reviewed, not a claim of live editor QA.
