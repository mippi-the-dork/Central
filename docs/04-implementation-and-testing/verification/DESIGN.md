# Testing & Verification — Design

**Central v1.0.0 · Source-grounded documentation**

## What has actually been tested in source?

The Central repository contains a native Automation Framework test named **`Central.Runtime.BasicStatistics`**. Its code checks representative means, medians, tied modes, empty arrays, weight rules, signed zero, invalid infinite inputs and the behavior of an unmodified Median input.

That test's existence is **not** evidence that it has been run successfully in your installed Unreal Editor.

## Run the native test

In a suitable Development Editor build, open Unreal's console and execute:

`Automation RunTests Central`

Alternatively, locate `Central.Runtime.BasicStatistics` in the editor's Automation test interface. Capture the full pass/fail result and exact engine/plugin version.

## Manual Blueprint graph checks

- Add all four user-facing statistics nodes in a fresh Blueprint.
- For each supported array type, connect Values and confirm the output type.
- Verify that all integer-family averaging nodes return Double.
- Disconnect/reconnect different supported arrays, including vectors/colors.
- Save, reopen, recompile, duplicate and copy/paste typed nodes.
- Split struct output pins and verify compatible reconstruction.
- Test enum Mode, ties, all-unique input and invalid numeric cases.
- Package a test project and confirm that the compiled runtime calculations still execute.

## Record evidence

Document the exact UE version, Central commit or release, project, input arrays, results, compiler errors, output log and screenshot for a failing graph. A verified build and live Blueprint test are separate from static source review.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
