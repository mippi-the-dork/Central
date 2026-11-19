# 03. Types and Blueprint Pins

**Central v1.0.0 · Blueprint statistics for Unreal Engine**

Central's **Values** input starts as a wildcard array. Connecting a supported array determines the result type and whether the node can compile.

## Key type rules

<!-- Media target: Image | central-types-overview | docs/assets/media/central-types-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-types-overview">
  <img src="../assets/media-placeholder.svg" alt="Connected Values arrays determine the output pin types." loading="lazy">
  <figcaption>Connected Values arrays determine the output pin types.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show an Integer Mean outputting Double, a Vector Median outputting Vector, and a String Mode retaining String output; use real pins.</span></figcaption>
</figure>

- Integer, Integer64 and Byte arrays return **Double** for Mean, Median and Weighted Mean.
- Float, Double and supported vectors/colors retain their appropriate supported output type.
- Mode can also work with Booleans, Strings, Names, Rotators, and supported byte-backed native and Blueprint enums.
- **Weights** on Weighted Mean always requires a **Double array**.

## Why checking validity matters
Invalid inputs generally yield the output type's default value. Since zero can be a legitimate statistic, rely on **Has Value** or **Has Mode**, not a comparison against zero.

These pages describe what can be connected, what happens when types change and how numerical edge cases are handled.

## Topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Supported Data Types** | Which Blueprint array types each operation supports | [Design](supported-types/DESIGN.md) | [Technical](supported-types/TECHNICAL.md) |
| **Wildcard Pins & Graph Changes** | Type resolution, connections, reconstruction, split pins and compilation | [Design](wildcard-pins/DESIGN.md) | [Technical](wildcard-pins/TECHNICAL.md) |
| **Validity & Edge Cases** | Empty arrays, zero values, non-finite input and precision limits | [Design](validity-and-edge-cases/DESIGN.md) | [Technical](validity-and-edge-cases/TECHNICAL.md) |
| **Enums & Complex Values** | Enum Mode, vectors, rotators, colors and component-wise operations | [Design](enums-and-complex-types/DESIGN.md) | [Technical](enums-and-complex-types/TECHNICAL.md) |

For practical node usage, start with [Statistics Nodes](../02-statistics-nodes/README.md).
