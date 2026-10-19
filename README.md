# Central

**Mean, median, mode, and weighted mean calculations for Unreal Engine Blueprint arrays.**

Central brings four statistical operations into Blueprint graphs through compact, type-aware nodes. Connect a supported array to calculate its average, find its middle value, or identify its most frequently occurring items without building separate counting and sorting logic.

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.8.x-black?logo=unrealengine)
![Platform](https://img.shields.io/badge/Platform-Windows%2064--bit-blue)
![Type](https://img.shields.io/badge/Plugin-Runtime%20%2B%20Editor-green)
![Version](https://img.shields.io/badge/Version-0.7.0-blue)

> **Development status:** Central 0.7.0 is a source development build. The code has not yet been confirmed by a successful Unreal Engine 5.8 build and full Blueprint test pass. Compatibility, packaging, and runtime behavior must be validated before public release.

---

# What is Central?

Mean, median, and mode answer different questions about a collection of values:

| Operation | Question | Example | Result |
|---|---|---|---|
| **Mean** | What is the arithmetic average? | `[2, 4, 6, 8]` | `5.0` |
| **Median** | What is the middle of the sorted values? | `[1, 3, 5, 9, 100]` | `5` |
| **Mode** | Which value appears most often? | `[2, 2, 3, 3, 4]` | `2` and `3` |
| **Weighted Mean** | What is the average when some values matter more? | Values `[10, 20]`, Weights `[1, 3]` | `17.5` |

These calculations are useful in gameplay balancing, procedural generation, telemetry, AI decision logic, sampled positions, and other systems that work with arrays of values.

Central keeps the operations in one **Math > Statistics** Blueprint category. Its custom nodes determine their types from the connected array, and compile into typed runtime functions.

---

# Features

### Mean Value (`MEAN`)

Calculates an arithmetic average. Integer, Integer64, and Byte inputs produce Double results to preserve fractional answers. Vector and Linear Color arrays are averaged component-wise.

### Weighted Mean Value (`WEIGHTED MEAN`)

Computes a weighted arithmetic average using a Double Weights array. Values and Weights must have matching lengths. Weights must be finite and nonnegative, with at least one positive weight. Zero-weight entries do not contribute. Integer-family inputs produce Double; math structures are averaged component-wise.

### Median Value (`MEDIAN`)

Finds the middle element after sorting. Even-length arrays average the two middle values. Vector and Linear Color medians are component-wise, not geometric medians.

### Mode Value (`MODE`)

Finds the most frequently occurring item or items. Reports one convenient first-encountered result, all tied highest-frequency values, their occurrence count, and whether a mode exists.

### Type-Aware Pins

Connect a supported array and Central changes the result pins to appropriate types. Mean and Median promote integer-family results to Double rather than silently truncating fractions.

### Multiple Modes

Bimodal and multimodal arrays return every tied mode through the **Modes** array, preserving first-encountered order.

### Explicit Validity Outputs

**Has Value** and **Has Mode** distinguish useful results from empty datasets and other unsupported results. A default output value alone should not be used as a success indicator.

### Read-Only Input

Central does not modify or sort the original array. Median sorts a local copy.

### Runtime Calculation, Editor Integration

A Runtime module implements the calculations, while an Editor module provides the Blueprint graph nodes. The editor UI is not required in packaged games.

---

# Using Central

1. Open a Blueprint graph.
2. Right-click and search for **Mean Value**, **Median Value**, or **Mode Value** under **Math > Statistics**.
3. Connect a supported array to **Values**. You can use an array variable or a **Make Array** node.
4. Read the calculated outputs, checking **Has Value** or **Has Mode** before relying on the result.

Central's input pin currently requires a connected array. An unconnected input cannot be used as an inline array literal; use **Make Array** instead.

## Mean Value

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Array of numeric, vector, or Linear Color values to average |
| **Value** | Output | Arithmetic average; defaults when no valid result exists |
| **Has Value** | Output | True when the input produces a valid finite average |

For example, `[1, 2]` produces `1.5`, not `1`. For vectors, each component is averaged independently. The same applies to Linear Color RGBA channels.

## Median Value

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Array to find the median of |
| **Value** | Output | Middle sorted value, or average of the two middle values |
| **Has Value** | Output | True when a valid median exists |

For example, `[10, 3, 7]` produces `7`. `[1, 2, 3, 4]` produces `2.5`.

**Vectors and Linear Color:** Components are treated independently. The final result may not be one of the original array elements. This is not a geometric median.

## Mode Value

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Array to count repeated values in |
| **Value** | Output | First encountered value among all qualifying modes |
| **Modes** | Output | All values tied for the greatest frequency, in encounter order |
| **Frequency** | Output | Occurrence count of each most-frequent value |
| **Has Mode** | Output | True only when at least one value occurs more than once |

| Input | Value | Modes | Frequency | Has Mode |
|---|---|---|---:|---|
| `[1, 2, 2, 3]` | `2` | `[2]` | 2 | True |
| `[1, 1, 2, 2, 3]` | `1` | `[1, 2]` | 2 | True |
| `[3, 3, 1, 1, 2, 2]` | `3` | `[3, 1, 2]` | 2 | True |
| `[1, 2, 3]` | Default | `[]` | 1 | False |
| `[]` | Default | `[]` | 0 | False |

Central deliberately defines **no mode** when every element occurs only once. For these arrays, **Has Mode** is false even though **Frequency** is 1. A Boolean array also follows this rule: `[true, false]` has no mode, while `[true, true, false]` does.

---

# Supported Types

| Blueprint data type | Mean | Median | Mode |
|---|:---:|:---:|:---:|
| Byte | Yes | Yes | Yes |
| Integer | Yes | Yes | Yes |
| Integer64 | Yes | Yes | Yes |
| Float | Yes | Yes | Yes |
| Double | Yes | Yes | Yes |
| Vector2D | Yes | Yes | Yes |
| Vector | Yes | Yes | Yes |
| Vector4 | Yes | Yes | Yes |
| Linear Color | Yes | Yes | Yes |
| Rotator | No | No | Yes |
| Boolean | No | No | Yes |
| String | No | No | Yes |
| Name | No | No | Yes |

**Type rules:** Integer, Integer64, and Byte return Double for Mean and Median. All other supported outputs preserve their corresponding scalar or structure type. Mode returns the input element type and an array of that same type.

Arbitrary enums, Gameplay Tags, user-defined structures, and object references are not implemented in this development version.

---

# Calculation Rules and Edge Cases

### Empty Arrays

Mean and Median return the type's default and **Has Value = false**. Mode returns default **Value**, an empty **Modes** array, **Frequency = 0**, and **Has Mode = false**.

### Non-Finite Values

NaN or infinite numeric input invalidates the calculation. For Mean and Median, **Has Value** becomes false. For Mode, **Has Mode** becomes false and mode outputs are cleared. Check the Boolean output before using any result.

### Equality for Mode

Mode uses the value type's equality semantics. Numeric -0 and +0 share a frequency bucket, while a first-encountered input value remains the displayed result. Numeric floating-point values and math structures should not be assumed to have a configurable tolerance. Particularly for computed floating-point values, nearly identical results can count as distinct. For complex math types, equality may be governed by Unreal's overloaded operators.

### Tie Resolution

When two or more values share the highest frequency, **Modes** reports all of them in the order they first occur in the input. **Value** returns the first of those tied modes.

### Precision

Mean and Median return a Double for integer-family arrays. Very large Integer64 values may still lose some integer precision when represented as a Double. Float-based results are subject to ordinary floating-point rounding.

### Performance

Mean processes the array linearly. Median sorts a local copy, ordinarily taking O(n log n). Mode uses a `TMap` for integral, floating-point, String, and Name types, providing expected linear frequency counting; supported math structures use an equality scan that can take O(n²) in the worst case.

---

# Installation

## Source Installation

1. Close Unreal Editor.
2. Copy the **Central** folder into your project's `Plugins` directory, creating it if needed.
3. The resulting path should be `YourProject/Plugins/Central/Central.uplugin`.
4. Right-click your `.uproject` and select **Generate Visual Studio project files** if needed.
5. Build the project's Editor target with a compatible Unreal Engine 5.8 C++ toolchain.
6. Start Unreal Editor. Under **Edit > Plugins**, find **Central**, enable it if necessary, and restart when prompted.

Do not remove the earlier **ModeValue** plugin until any Blueprints that reference its original node have been migrated and saved. Central does not automatically migrate legacy ModeValue nodes.

## Plugin Structure

```text
Central/
├── Central.uplugin
├── README.md
└── Source/
    ├── Central/
    │   ├── Central.Build.cs
    │   ├── Public/CentralBPLibrary.h
    │   └── Private/
    │       ├── CentralBPLibrary.cpp
    │       └── CentralModule.cpp
    └── CentralEditor/
        ├── CentralEditor.Build.cs
        ├── Public/K2Node_Central.h
        └── Private/
            ├── K2Node_Central.cpp
            └── CentralEditorModule.cpp
```

---

# Technical Notes

Central's visible nodes use custom `UK2Node` implementations for typed pins. During Blueprint compilation, those nodes expand to the corresponding typed functions in `UCentralBPLibrary`.

The Runtime module supplies the calculations. The Editor module supplies graph integration. The internal typed functions are deliberately hidden from the ordinary Blueprint action menu.

Currently, type support is validated during Blueprint compilation. Certain unsupported connections might be permitted visually before generating a compiler diagnostic. Connected array inputs are required.

---

# Troubleshooting

### The node will not compile

Make sure **Values** is connected to a supported array and the project is using the supported Unreal Engine version. Unsupported types produce Blueprint compilation errors.

### The output is zero or empty

Check **Has Value** or **Has Mode**. A zero result can be mathematically valid, but it is also the default result when a calculation cannot produce a value.

### Mode returns no result for a nonempty array

If every item is unique, Central treats the data as having no mode. Check **Frequency**: it will read 1 for a nonempty all-unique dataset.

### An old ModeValue node is missing

Central does not redirect or automatically replace nodes from the earlier ModeValue plugin. Restore the previous plugin temporarily if needed and migrate the nodes manually.

---

# Development Validation

Before a public 1.0.0 release, verify successful compilation and cooking for Unreal Engine 5.8, automatic pin type reconstruction, Undo/Redo, Blueprint serialization and reopening, type restrictions, all supported data types, empty and non-finite arrays, integer precision, bimodal and multimodal results, and packaged-runtime execution.

**Central 0.7.0 is a development build, not a public release.**

---

# Weighted Mean

Connect an array to **Values** and a Double array to **Weights**. The matching element indices determine which weight applies to which value.

```text
Values  = [10, 20]
Weights = [1, 3]
Result  = 17.5
```

Weighted Mean calculates `sum(value * weight) / sum(weight)` after normalizing weights. It returns **Has Value = false** when the arrays are empty, lengths differ, any weight is negative or non-finite, all weights are zero, or a value is non-finite. A failed calculation returns the type's default value. A zero weight excludes its corresponding value from the result, but invalid numeric values are still rejected during input validation.

The Weights pin currently uses a **Double array**, including when the Values array is Float, Integer, or Vector. This is deliberate and preserves consistent precision for weights.

# Development Validation

This source version includes a developer automation test covering basic means, fractional integer medians, single/multiple/no modes, weighted means, and invalid weights. Run it using the Unreal Automation Test framework with the filter `Central.`. Run Blueprint graph compilation, pin reconstruction, copy/paste, game packaging, and runtime regression tests separately before a public release.

**Known limitations:** Mode does not yet accept user-defined Blueprint enum arrays. Non-hashable math structs use a linear equality search and may be expensive on large arrays. The graph compiler reports unsupported array types, but connection-time rejection is not yet comprehensive. Floating-point mode uses the type's exact equality rules. This package has not been built inside UE 5.8 in this environment.


## Development pass 0.7.0

- Added graph connection-time rejection for unsupported Values array element types. A connected array must use one of Central's supported types. Enum arrays are intentionally not supported yet.
- Added Mode output connection checks when the input array has already determined its type.
- Expanded runtime automation coverage for empty arrays, three-way mode ties, odd-sized medians, and weighted zero-input edge cases.

### Validation status

This is a source-only development package. Compilation, Blueprint graph reconstruction, and automated tests must be run in Unreal Engine 5.8 before a public release. Tests can be launched in Unreal's Session Frontend with the `Central.Runtime.BasicStatistics` automation test.

## Development pass 0.7.0

- Canonicalizes the hash key for signed floating-point zero so negative and positive zero share a Mode frequency bucket.
- Reduces redundant Blueprint graph refresh notifications when wildcard-derived pin types have not changed.
- Adds signed-zero, zero-mean and string-tie automation coverage.
- Keeps existing serialized node names and pins unchanged.
- Unreal Engine 5.8 compilation and in-editor validation are still required.


## Development validation notes (0.7.0)

Mode requires at least one repeated value. When every item is unique, `Has Mode` is false, `Modes` is empty, and `Frequency` is 1. Invalid floating-point input also fails rather than treating non-finite values as categories.

Blueprint output connections are checked against the currently resolved output type for all four nodes. This check is not a substitute for testing reconstruction, graph reload, pin relinking, and compilation in an installed UE 5.8 editor.

The source in this package has not been built in UE 5.8. Blueprint enum arrays remain unsupported.


## Saved Blueprint node reconstruction (development validation)

Central recreates wildcard pin types from existing connected pins before Unreal restores graph connections during node reconstruction. This is intended to keep the `Values`, `Value`, and (for Mode) `Modes` pins consistent across save, reload, and Blueprint regeneration. Native split-pin restoration is retained. This behavior has been reviewed against the user-supplied Unreal Engine 5.8 `UK2Node` source but has **not** yet been verified by saving/reloading a Blueprint in an Unreal Editor build.

Recommended validation: connect each supported input type, compile and save the Blueprint, restart the editor, reopen and compile again; then disconnect and replace the array with a different supported type, and test split vector pins and Undo/Redo.

## Version 0.7.0 development changes

- Mode supports byte-backed native and Blueprint enum arrays through a reflected runtime thunk. Enum values are counted without converting the original array to ordinary bytes.
- Vector2D, Vector, Vector4, Linear Color, and Rotator modes use component-key hashing, preserving encounter order and recognizing signed zero consistently.
- Integer-valued enums with non-byte Blueprint representations require additional editor validation before release.
- Automated tests now cover signed-zero vector frequency grouping.

> Development status: compilation and visual Blueprint testing on Unreal Engine 5.8 are still required.
