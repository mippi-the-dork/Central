# Runtime and Editor Architecture — Technical

**Central v1.0.0 · Source-grounded documentation**

## Module descriptor

`Central.uplugin` declares two modules: `Central` of type Runtime with `PreDefault` loading, and `CentralEditor` of type Editor with `Default` loading.

## Editor K2 node

`UK2Node_Central` owns:
- `AllocateDefaultPins` and output construction;
- `GetMenuActions` and Math|Statistics placement;
- `RefreshTypes`, `IsConnectionDisallowed`, and connection notifications;
- pin reconstruction for serialized graphs;
- `ExpandNode` conversion to typed function-call nodes.

## Runtime implementation

`UCentralBPLibrary` is a `UBlueprintFunctionLibrary`. Internal typed `UFUNCTION(BlueprintPure)` methods handle numeric and supported struct arrays. `ModeEnum` uses a reflected custom thunk for enum arrays. The C++ helper implementation lives in `CentralBPLibrary.cpp`.

## Compilation model

`UK2Node_Central::ExpandNode` matches the connected Values type, resolves `OperationName()+Suffix` to a UFunction, spawns `UK2Node_CallFunction`, and transfers connected data pins. The custom user-facing K2 node itself does not run as a distinct runtime Actor/component.

## Dependency boundary

`CentralEditor` depends on editor graph classes; `Central` contains the actual packaged calculation logic. A runtime module should not reference editor-only types. Native tests under `Source/Central/Private/Tests` are guarded by `WITH_DEV_AUTOMATION_TESTS`.

## Stability and future releases

Saved Blueprint graphs depend on node reconstruction and pin names, so changes to type support or output pin naming should be verified with previously saved graph assets. No unannounced future API stability guarantee is inferred here.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
