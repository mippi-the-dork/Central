# Your First Blueprint Graph — Technical

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Initial pins and resolution

`UK2Node_Central::AllocateDefaultPins` creates a wildcard **Values** array pin and the appropriate outputs. Connecting a supported array determines pin types through `NotifyPinConnectionListChanged` and `RefreshTypes`. The node exposes no execution pin.

## Type propagation

`RefreshTypes` reads the Values connection and finds the corresponding `FSupported` entry. Integer, Integer64 and Byte input arrays promote the output to a Double pin for Mean, Median and Weighted Mean. Mode outputs retain the input element type and supplies `Modes` as an array.

## Compiler expansion

At compile time, `ExpandNode` requires a connected supported Values array. It resolves `OperationName + Suffix` to the corresponding `UCentralBPLibrary` function and spawns a `UK2Node_CallFunction`. It transfers Values, Weights if present, results, and validity/frequency pins. An unsupported or unconnected input produces a compiler error instead of silently choosing a type.

## Why test through a full Blueprint

Native runtime calculations can work while graph pin propagation, reconstruction or intermediate compilation fails. Save/reopen, change the array type, duplicate/copy/paste nodes and test split vector output pins when verifying the editor interface. These are additional integration tests beyond the runtime unit test.

## Primary source references

- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralBPLibrary.h](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Public/CentralBPLibrary.h)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)

[Design and usage](DESIGN.md). **Verification:** Implementation reviewed in source; a running UE 5.8 test is a separate check.
