# Wildcard Pins & Graph Changes — Technical

**Central v1.0.0 · Type and graph behavior**

## RefreshTypes ownership

`UK2Node_Central::RefreshTypes` initializes Values as an array wildcard and reads `Values->LinkedTo[0]->PinType` as the authoritative type when present. `NotifyPinConnectionListChanged` calls this logic as connections are edited.

## Mode output inference

Mode has a deliberate exception: if Values is unconnected, a typed Value or Modes output link can temporarily help infer the node's type. **It still needs a connected Values array to compile**. When a Values link appears, it takes precedence.

## Reconstruction

`ReallocatePinsDuringReconstruction` and `PostReconstructNode` preserve compatible pin layouts when Blueprints load or change. The current schema can resolve and restore types from previous Values or dependent output pins, then reconcile links with the new type.

## Graph notifications

`RefreshTypes` compares previous and new pin types before calling `GetGraph()->NotifyGraphChanged()`. This avoids repeated graph invalidation when the type does not actually change.

## Compile expansion

`ExpandNode` rejects a disconnected Values input or unsupported array type, then spawns a typed `UK2Node_CallFunction` and moves matching links to it. For enum Mode, intermediate call pins are explicitly aligned to the actual enum type before moving connections.

## Diagnostics

Use the Blueprint compiler messages to distinguish unsupported input arrays, mismatched downstream outputs, missing internal functions or failed pin expansion. The runtime calculations are distinct from editor graph typing and reconstruction.

## Source references

- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design guide](DESIGN.md) · Source-reviewed, not a claim of live editor QA.
