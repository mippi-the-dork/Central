# Testing & Verification — Technical

**Central v1.0.0 · Source-grounded documentation**

## Existing automation test

`Source/Central/Private/Tests/CentralStatisticsTests.cpp` declares:

`IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCentralStatisticsTest, "Central.Runtime.BasicStatistics", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)`

The test is compiled under `WITH_DEV_AUTOMATION_TESTS`.

## What the test asserts

Representative coverage includes:
- Mean of Integer arrays and a valid zero mean;
- Median of even and unsorted arrays, ensuring caller input remains unchanged;
- Mode single/tied/multimodal results, first-encounter order, all-unique and empty frequency;
- Mode signed zero for Float and Vector keys;
- Weighted Mean with valid, zero, mismatched, negative and all-zero weights;
- Invalid infinity behavior for Mean, Mode and Weighted Mean.

## What's not covered by this native test

There is no evidence from this one runtime test of full K2 editor compatibility, saved graph reconstruction, all supported types, split pins, Blueprint compile stability, packaged-game loading or platform-specific benchmarking. These require separate tests.

## Recommended integration matrix

Create minimal reusable Blueprint tests for every supported Values type and operation, reconnect Types, native/Blueprint enum Mode, typed downstream connections, compilation, save/reload, Undo/Redo, duplication, and packaged execution. Keep explicit Expected/Observed/Result columns.

## Evidence status

**Source reviewed, not executed in this documentation session.** Do not mark automation or manual tests Passed until actual output logs or build results confirm them.

## Related source files

- [Central.uplugin](https://github.com/mippi-the-dork/Central/blob/main/Central.uplugin)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design and workflows](DESIGN.md). **QA status:** Code reviewed; this document does not claim passing editor or packaging runs.
