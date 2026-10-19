# Central

**Mean, Median, Mode, and Weighted Mean for Unreal Engine Blueprints.**

Central adds four compact, type-aware statistics nodes to Blueprint graphs. Calculate an average, find the middle of a dataset, identify its most common values, or compute an average using individual weights without assembling the underlying array math yourself.

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.8.x-black?logo=unrealengine)
![Platform](https://img.shields.io/badge/Platform-Windows%2064--bit-blue)
![Type](https://img.shields.io/badge/Plugin-Runtime%20%2B%20Editor-green)
![Version](https://img.shields.io/badge/Version-1.0.0-blue)

---

## What is Central?

When working with an array, the question is not always what its total is. Often, you want to know what is typical.

Central brings the four related ways to answer that question into Blueprint:

| Node | Question | Example | Result |
|---|---|---|---|
| **Mean Value** (`MEAN`) | What is the arithmetic average? | `[2, 4, 6, 8]` | `5.0` |
| **Median Value** (`MEDIAN`) | What is the middle of the ordered data? | `[1, 3, 5, 9, 100]` | `5.0` |
| **Mode Value** (`MODE`) | Which value occurs most often? | `[2, 2, 3, 3, 4]` | Modes `[2, 3]` |
| **Weighted Mean Value** (`WEIGHTED MEAN`) | What if some values contribute more? | Values `[10, 20]`, Weights `[1, 3]` | `17.5` |

This is useful for sampled gameplay values, procedural systems, AI state distributions, gameplay telemetry, balancing data, and other Blueprint systems built around collections of values.

Central concentrates on these operations rather than trying to replace Unreal Engine's wider math library.

---

# Features

### Four Focused Statistics Nodes

**Mean, Median, Mode, and Weighted Mean** are available from the Blueprint action menu under **Math > Statistics**.

### Compact Blueprint Presentation

Each operation uses a compact title. The nodes are pure and have no execution pins.

### Type-Aware Array Inputs

The **Values** input takes a supported array. Its connection determines the calculated output type. For Mean, Median, and Weighted Mean, Integer, Integer64, and Byte arrays produce a **Double** value so fractional answers are not truncated.

### Multiple Modes

Mode returns the first encountered modal value and an array of *all* values tied for the highest frequency, in encounter order.

### Native and Blueprint Enum Modes

Mode supports byte-backed native enums and Blueprint enums via an enum-aware reflected implementation. An enum array retains its enum type on the output pins.

### Meaningful Validity Pins

**Has Value** and **Has Mode** distinguish a valid zero-valued answer from a result that could not be computed. A numeric `0` by itself does not indicate success or failure.

### Component-Wise Math

Mean, Median, and Weighted Mean support Vector2D, Vector, Vector4, and Linear Color by operating on each component independently.

### Unmodified Input Arrays

Operations do not rearrange the caller's input arrays. Median creates its own working data when ordering values.

### Hash-Based Frequency Counting

Mode uses map-based frequency counting for supported primitive and mathematical values, including component-based keys for supported vector, color, and rotator types. Expected frequency-counting complexity is linear in the array length; memory use increases with distinct values.

### Editor and Runtime Separation

A **Runtime** module performs calculations; a separate **Editor** module implements the Blueprint nodes and pin typing. The editor module is not required by packaged games.

---

# Using Central

1. Open a Blueprint graph and search for **Mean Value**, **Median Value**, **Mode Value**, or **Weighted Mean Value**.
2. Connect a supported array to **Values**, either from an array variable or a **Make Array** node.
3. For Weighted Mean, also connect a **Double array** to **Weights** with one weight per value.
4. Read the output, checking **Has Value** or **Has Mode** before using a result whose validity matters.

The Values pin requires an array connection; construct inline data through **Make Array** instead of leaving Values disconnected.

---

# Mean Value (`MEAN`)

The arithmetic mean is the sum of the values divided by their count:

```text
Values = [2, 4, 6, 8]
Value  = 5.0
Has Value = true
```

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Supported array to average |
| **Value** | Output | Arithmetic mean, or the output type's default when invalid |
| **Has Value** | Output | Whether a valid average was produced |

Integer-family arrays yield Double answers. For instance, `[1, 2]` produces `1.5` rather than `1`. For Vector2D, Vector, Vector4, and Linear Color, Central averages each coordinate or channel independently.

For an empty array or non-finite numeric input, **Has Value** is false. A valid mean of zero still sets **Has Value** to true.

---

# Median Value (`MEDIAN`)

The median is the middle value after sorting. For even counts it is the average of the two middle values:

```text
Values = [10, 3, 7]
Value = 7.0

Values = [1, 2, 3, 4]
Value = 2.5
```

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Supported array to find the median of |
| **Value** | Output | Middle value or mean of the middle pair |
| **Has Value** | Output | Whether a valid median was produced |

**Median does not sort your original array.** The ordering operation works on temporary data.

For vectors and Linear Color, Median is **component-wise**. This is not the geometric median, and the resulting value may not appear in the original dataset.

---

# Mode Value (`MODE`)

Mode identifies repeated values with the greatest frequency. Unlike Mean and Median, it can also operate on non-numeric categories such as Booleans, Names, Strings, and supported enums.

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Array to count repeated values in |
| **Value** | Output | First encountered qualifying mode; default when none exists |
| **Modes** | Output | All values tied for the highest frequency, in first-seen order |
| **Frequency** | Output | Number of occurrences of each qualifying mode |
| **Has Mode** | Output | True when at least one value occurs more than once |

| Input | Value | Modes | Frequency | Has Mode |
|---|---|---|---:|---|
| `[1, 2, 2, 3]` | `2` | `[2]` | 2 | True |
| `[1, 1, 2, 2, 3]` | `1` | `[1, 2]` | 2 | True |
| `[3, 3, 1, 1, 2, 2]` | `3` | `[3, 1, 2]` | 2 | True |
| `[1, 2, 3]` | Default | `[]` | 1 | False |
| `[]` | Default | `[]` | 0 | False |

## When there is no mode

Central intentionally treats **all-unique** input as having no mode. The input `[1, 2, 3]` therefore reports **Has Mode = false**, even though the greatest frequency is `1`. Empty input reports frequency `0`.

## Bimodal and multimodal values

When several values tie at a frequency greater than one, **Modes** contains all of them. **Value** returns the first one encountered in the original array. Central never silently discards the other modal values; they remain available on **Modes**.

## Mode equality

Mode counts matching values based on its implemented exact/component-key behavior, not an adjustable tolerance. Two values very close to each other are not guaranteed to count as equal. Positive and negative floating-point zero share a frequency group. Non-finite numeric data is rejected rather than treated as a matching category.

For enums, the values are compared as their underlying integral representation while the graph retains the appropriate enum pin type.

---

# Weighted Mean Value (`WEIGHTED MEAN`)

Weighted Mean assigns a contribution weight to each input element.

```text
Values  = [10, 20]
Weights = [1.0, 3.0]
Value   = 17.5
Has Value = true
```

Formula: `sum(value * weight) / sum(weight)`.

| Pin | Direction | Meaning |
|---|---|---|
| **Values** | Input | Numeric, vector, or Linear Color array to average |
| **Weights** | Input | Double array; one weight per element in Values |
| **Value** | Output | Weighted mean, or the type's default when invalid |
| **Has Value** | Output | Whether a valid weighted mean was produced |

### Weight rules

- Values and Weights must have the **same nonzero length**.
- Every weight must be **finite and nonnegative**.
- At least one weight must be **greater than zero**.
- Individual zero weights are allowed and contribute nothing to the result.
- Invalid numeric input is rejected, including entries whose weight is zero.

The Weights array always uses **Double**, regardless of the Values element type. Like ordinary Mean, integer-family Values produce Double results, while supported mathematical structures are averaged component-wise.

---

# Supported Data Types

| Blueprint type | Mean | Median | Mode | Weighted Mean |
|---|:---:|:---:|:---:|:---:|
| Byte | Yes | Yes | Yes | Yes |
| Integer | Yes | Yes | Yes | Yes |
| Integer64 | Yes | Yes | Yes | Yes |
| Float | Yes | Yes | Yes | Yes |
| Double | Yes | Yes | Yes | Yes |
| Vector2D | Yes | Yes | Yes | Yes |
| Vector | Yes | Yes | Yes | Yes |
| Vector4 | Yes | Yes | Yes | Yes |
| Linear Color | Yes | Yes | Yes | Yes |
| Rotator | No | No | Yes | No |
| Boolean | No | No | Yes | No |
| String | No | No | Yes | No |
| Name | No | No | Yes | No |
| Byte-backed native or Blueprint enum | No | No | Yes | No |

**Output types:** All three averaging/ordering operations return Double for Byte, Integer, and Integer64 input. Otherwise, the result follows its supported input type. Mode's **Value** and **Modes** retain their Values array element type.

Arbitrary gameplay tags, object references, custom user structs, nested arrays, and native enums with unsupported underlying representations are not supported.

---

# Edge Cases and Numerical Behavior

| Condition | Behavior |
|---|---|
| Empty Values array | Invalid result; default Value and false validity flag |
| One value for Mean or Median | That value (subject to supported type and validity) |
| All elements unique for Mode | Has Mode false, Modes empty, Frequency 1 |
| Multiple highest-frequency repeated values | All included in Modes; Value uses first encounter |
| Non-finite numeric values | Invalid result rather than NaN-based mode categories |
| Negative or non-finite weight | Weighted Mean invalid |
| Weight lengths differ | Weighted Mean invalid |
| All weights zero | Weighted Mean invalid |
| Large Integer64 values | Possible precision loss when converted to Double |
| Very close floating-point values | May be treated as different Mode values |

When validity is false, do not interpret the returned default as a meaningful statistic.

## Calculation performance

Mean and Weighted Mean ordinarily traverse the input linearly. Median sorts working data, commonly O(n log n). Mode counts frequencies with maps and has expected O(n) counting behavior for supported hashed types. These are algorithmic characteristics, not performance benchmarks from a particular project.

---

# Blueprint Pin Types and Saved Graphs

The **Values** array is initially a wildcard. Connecting a supported array resolves the input and corresponding output type. For integer-family Mean, Median, or Weighted Mean nodes, the scalar output is promoted to Double.

If you change the input array's element type, reconnect dependent pins where necessary and compile the Blueprint. Central uses Unreal Engine's pin reconstruction workflow to preserve compatible connections when a Blueprint is reloaded and rebuilt, including split structure pins.

When changing an array to a different element type, check any dependent connections and compile the Blueprint. Split structure pins and existing connections are handled through Unreal Engine's normal pin reconstruction workflow.

---

# Installation

## Project plugin from source

1. Close Unreal Editor and any active project build.
2. Place the `Central` directory into `YourProject/Plugins/`.
3. Verify the descriptor is at `YourProject/Plugins/Central/Central.uplugin`.
4. Generate Visual Studio project files from the `.uproject` if necessary.
5. Build the project's **Development Editor** target using an Unreal Engine 5.8 C++ environment.
6. Start Unreal Editor and enable **Central** from **Edit > Plugins** if it is not already enabled. Restart if prompted.

```text
YourProject/
├── Config/
├── Content/
├── Plugins/
│   └── Central/
│       ├── Central.uplugin
│       ├── README.md
│       ├── CHANGELOG.md
│       └── Source/
└── YourProject.uproject
```

## Precompiled installation

For precompiled distributions, install the package matching your Unreal Engine version and platform. A source package requires a working C++ build environment and does not include precompiled plugin binaries.

Central can also be installed under your engine's `Engine/Plugins` directory. Per-project installation keeps the plugin alongside the project that uses it.

---

# Technical Architecture

```text
Central/
├── Central.uplugin
├── README.md
├── CHANGELOG.md
└── Source/
    ├── Central/
    │   ├── Central.Build.cs
    │   ├── Public/
    │   │   └── CentralBPLibrary.h
    │   └── Private/
    │       ├── CentralBPLibrary.cpp
    │       ├── CentralModule.cpp
    │       └── Tests/
    │           └── CentralStatisticsTests.cpp
    └── CentralEditor/
        ├── CentralEditor.Build.cs
        ├── Public/
        │   └── K2Node_Central.h
        └── Private/
            ├── CentralEditorModule.cpp
            └── K2Node_Central.cpp
```

Central's `UK2Node` classes supply the graph's compact nodes, wildcard type propagation, and compilation into typed functions. `UCentralBPLibrary` contains the runtime implementations. Mode's enum path uses reflected properties to operate on supported enum arrays without reinterpreting arbitrary array memory as a different `TArray<T>`.

The Runtime module is the part required by gameplay code and cooked content. CentralEditor is compiled for the editor only.

---

# Testing and Troubleshooting

## Automation tests

The plugin includes source-level automation tests under `Source/Central/Private/Tests/`. In a suitable Unreal Editor test environment, run the test named **`Central.Runtime.BasicStatistics`** through the Automation system (for example, Session Frontend). Tests include basic means, medians, single and tied modes, no-mode cases, weighted means, and selected invalid inputs.

Automation tests cover runtime calculations. Blueprint integration and packaged-game behavior can also be checked using the workflows below.

## Checking Blueprint behavior

- Connect every supported array type to the appropriate node and compile.
- Save, close, reopen, and recompile Blueprints containing typed nodes.
- Replace input arrays with different supported types and verify dependent output pins.
- Try unsupported arrays and inspect connection and compiler diagnostics.
- Test split vector/structure output pins, duplication, Undo/Redo, and copy/paste.
- Test native and Blueprint enum arrays with Mode, including tied results.
- Run a packaged build that executes the calculations from a Blueprint.

## Common issues

**The node does not compile:** Connect a supported array to Values, and connect a Double Weights array for Weighted Mean. Review the Blueprint compiler error for invalid types or incompatible connected output pins.

**The node returns zero or an empty array:** Read Has Value or Has Mode. A zero may also be an entirely valid result.

**Mode returns no result for unique elements:** This is intentional. Central requires at least one repeated value for Has Mode to be true.

---

# Compatibility

**Version:** 1.0.0  
**Unreal Engine:** 5.8.x  
**Modules:** Runtime + Editor  
**Distribution:** Source or platform-specific precompiled plugin packages.

Central provides four focused Blueprint statistics operations: Mean, Median, Mode, and Weighted Mean.
