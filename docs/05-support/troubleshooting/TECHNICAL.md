# Troubleshooting — Technical

**Central v1.0.0 · Source-grounded documentation**

## Diagnostic categories

**Action not found:** Check `CentralEditor` module loading and K2 action registration.

**Unsupported link:** `CentralEditorPrivate::Match` enforces array category, struct/enum subtype and supported operations. `IsConnectionDisallowed` rejects unsupported combinations.

**Compile error:** `ExpandNode` checks connected Values and a matching typed UFunction. It emits separate messages for missing Values, unsupported type, internal function lookup failure and pin-expansion failure.

**Unexpected output type:** `RefreshTypes` promotes Integer-family averaging operations to Double and keeps Mode output aligned with the Values element type. Dependent connections may need to change.

**Unexpected invalid result:** See finite checks in `CentralBPLibrary.cpp`, `ValidateWeights` and the Mode no-repeat definition.

## Reproduction strategy

Start in a clean Blueprint with a small Make Array; verify one operation at a time. Record the exact Values element type and result pins. Add saved graph reload, copy/paste or split structure pins only after a minimal graph succeeds.

## Regression classification

Separate runtime math errors (reproducible through `Central.Runtime.BasicStatistics`) from K2 authoring/compilation errors and packaged-game integration issues. These often require different source owners.

## Tests not claimed passed

The documentation can describe the source test and how to run it, but cannot infer that the user's project passes compilation, graph reconstruction or packaging until those outputs are collected.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
