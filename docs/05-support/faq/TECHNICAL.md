# Frequently Asked Questions — Technical

**Central v1.0.0 · Source-grounded documentation**

## FAQ routing

- Missing node: `UK2Node_Central::GetMenuActions`, Editor module load, action database.
- Wildcard unresolved: `AllocateDefaultPins`, `RefreshTypes`, `IsConnectionDisallowed`, `ExpandNode`.
- Integer-to-Double promotion: `RefreshTypes` and the typed runtime function signatures.
- Missing Mode result: runtime `Mode<T>` deliberately requires repeat frequency greater than one.
- Enum Mode: `ModeEnum` reflected custom thunk and K2 enum pin expansion.
- Temporary input ordering: `Median` receives array data by value.
- Invalid weight/data: finite validation, matching weights count and positive total weight.

## Avoiding ambiguous bug reports

Include the original values, weights, element type, resulting Value/Modes/Frequency/validity pins, engine and plugin version, and a screenshot of the graph. Without the data type, a reported “wrong output type” is not reproducible.

## API boundary

User-facing nodes compile into internal runtime functions, which are not the same as a public promise that every UFUNCTION name will remain stable in future plugin releases. Source and graph compatibility should be verified when updating.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
