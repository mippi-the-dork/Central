# Updating & Support — Technical

**Central v1.0.0 · Source-grounded documentation**

## Distribution and modules

`Central.uplugin` specifies version 10000 / `1.0.0`, `Central` Runtime module, and `CentralEditor` Editor module. The source documentation targets UE 5.8.x and platform-specific distributions.

## Compatibility-sensitive surfaces

`UK2Node_Central::AllocateDefaultPins`, `ReallocatePinsDuringReconstruction`, `PostReconstructNode`, `RefreshTypes` and `ExpandNode` control saved Blueprint graph compatibility. Changing public pin names, type-resolution rules or internal function suffixes can break previously authored Blueprints even when runtime calculations remain correct.

## Version verification

Record a specific commit/tag and engine version when testing. Use the source code for that release rather than assuming that main always remains identical to v1.0.0.

## Update checks

After reinstalling, verify Editor module load, action menu node availability, each supported array's pin typing, compilation, Blueprint save/reload, runtime execution and an actual packaged build when the target project requires it.

## Source-based limitation

The repository's current documentation and code do not establish a full backwards-compatibility contract for all future versions. Do not assert binary compatibility, migration support or engine-version support beyond tested evidence.

## Technical support evidence

Attach a minimal reproducer or screenshot with exact graph types and error messages. Include native automation logs, if run, and indicate whether a failure occurs in edit-time graph reconstruction, Blueprint compilation or runtime calculation.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
