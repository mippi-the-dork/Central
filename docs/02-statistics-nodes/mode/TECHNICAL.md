# Mode Value — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Typed and reflected implementations

`UCentralBPLibrary` provides typed Mode implementations for numeric types, Vector2D, Vector, Vector4, Linear Color, Rotator, Boolean, String and Name. Supported native/Blueprint enums use a dedicated reflected `ModeEnum` custom thunk.

## Frequency counting

`CentralPrivate::Mode<T>` builds frequency counts using hash maps. The map key for primitive types follows their native semantics, and component-key helpers are defined for supported vectors, colors and rotators. `CanonicalModeKey` normalizes signed floating-point zero before hashing.

## Stable tie output

The algorithm records first-seen order while counting, then returns each value whose count equals the maximum *when that maximum exceeds one*. The first qualifying item in input order is the scalar Value. Tied values remain in Modes.

## Invalid and unique inputs

For an empty array, Frequency is zero. When all values are unique, Frequency is one, Has Mode is false and Modes is empty. Non-finite numeric inputs are rejected to avoid unreliable floating-point hash-key behavior.

## Complexity

Expected counting time is **O(n)** with additional memory proportional to distinct values. Hash behavior is not a formal worst-case timing guarantee. The input array is never re-ordered.

## Pin contract

The public `UK2Node_Central` Mode node resolves its output Value/Modes pins to the input element type, and its compiler expansion forwards Frequency and `bHasMode` to the correct native function.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
