# Installation & Compatibility — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Declared metadata

`Central.uplugin` specifies v1.0.0 (`Version: 10000`) with a Runtime module (`PreDefault`) and an Editor module (`Default`). The source README targets UE 5.8.x and Win64 distributions. The descriptor itself does not provide a `PlatformAllowList` or an `EngineVersion` field; do not interpret those absent fields as proof of tested compatibility with other targets.

## Build dependencies

`Source/Central/Central.Build.cs` builds the runtime Blueprint function library; `Source/CentralEditor/CentralEditor.Build.cs` builds editor Blueprint graph integration. A source installation requires the Unreal C++ build toolchain and matching engine headers.

## Compile-time registration

`UK2Node_Central::GetMenuActions` registers the custom node action and `GetMenuCategory` supplies `Math|Statistics`. `UCentralBPLibrary` methods are `BlueprintInternalUseOnly`, so authors are expected to use the compact user-facing nodes rather than manually placing dozens of typed internal functions.

## Packaging boundaries

Do not make game-runtime modules depend on `CentralEditor`. A cooked Blueprint compiles the custom node to a call on `UCentralBPLibrary`; this keeps calculation logic available at runtime while excluding editor graph UI.

## Installation diagnostics

A missing action can result from module loading, plugin enablement, build errors or a Blueprint action menu that has not refreshed. Review the actual Output Log rather than claiming that the presence of a directory proves successful registration.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
