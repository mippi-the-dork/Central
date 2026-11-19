# What Central Does — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Plugin descriptor and module division

`Central.uplugin` declares `VersionName: 1.0.0`, a `Central` Runtime module loaded at `PreDefault`, and a `CentralEditor` Editor module loaded at `Default`. `CanContainContent` is false. The descriptor does not declare an engine source modification requirement.

## Source boundaries

- `UCentralBPLibrary` in `Source/Central/` holds the typed runtime `BlueprintPure` functions.
- `UK2Node_Central` in `Source/CentralEditor/` creates user-facing nodes, resolves wildcards and expands into typed function calls.
- `Central.Runtime.BasicStatistics` is an Automation Framework test implemented under `Source/Central/Private/Tests/`.

The editor module is excluded from a normal cooked game; the underlying runtime functions can execute in packaged gameplay.

## Why the nodes are pure

The author-facing nodes inherit from `UK2Node` and allocate **Values**, typed outputs and optional Weights as data pins. They do not present execution pins. During Blueprint compilation, `ExpandNode` replaces the custom graph node with a supported typed `UK2Node_CallFunction`.

## Data ownership and side effects

The runtime methods compute from const arrays. Median receives a working `TArray` copy to sort; input arrays are not re-ordered. The outputs are result values plus validity/frequency fields, not an asset or Actor that stores historical samples.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
