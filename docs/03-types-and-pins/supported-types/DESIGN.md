# Supported Data Types — Design

**Central v1.0.0 · Type and graph behavior**

## Type compatibility

<!-- Media target: Image | central-supported-types | docs/assets/media/central-supported-types.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-supported-types">
  <img src="../../assets/media-placeholder.svg" alt="A defined set of numeric and math-struct arrays is supported, with more categories for Mode." loading="lazy">
  <figcaption>A defined set of numeric and math-struct arrays is supported, with more categories for Mode.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show a numeric Mean, Vector Median and enum or String Mode, each with real typed array connections.</span></figcaption>
</figure>


Central accepts **arrays of supported types**, not arbitrary values or nested arrays. The connection to Values determines which native implementation and output type are used.

| Blueprint type | Mean | Median | Mode | Weighted Mean |
| --- | :---: | :---: | :---: | :---: |
| Byte | Yes | Yes | Yes | Yes |
| Integer | Yes | Yes | Yes | Yes |
| Integer64 | Yes | Yes | Yes | Yes |
| Float / Double | Yes | Yes | Yes | Yes |
| Vector2D / Vector / Vector4 | Yes | Yes | Yes | Yes |
| Linear Color | Yes | Yes | Yes | Yes |
| Rotator | No | No | Yes | No |
| Boolean | No | No | Yes | No |
| String / Name | No | No | Yes | No |
| Supported byte-backed enum | No | No | Yes | No |

## Result type

Mean, Median and Weighted Mean return **Double** for Byte/Integer/Integer64 arrays. Other supported scalar and math-struct inputs retain their appropriate result type. Mode returns a **Value** and **Modes** array of the original element type.

## Why an unsupported array fails

Object references, Gameplay Tags, arbitrary user structs, nested arrays and enums with unsupported underlying representations are not supported by these custom nodes. The graph connection should be rejected or compilation should report an incompatible array rather than assuming a numerical interpretation.

## Example: choosing a type

For measured frame time samples with fractional milliseconds, use Float or Double arrays. For repeated named states, use Mode on a Name or supported enum array. For several positions, a Vector mean returns a component-wise average, not an average distance.

## When to consult Technical

If a type's connection appears available but then fails to compile, the Technical reference explains the exact K2 supported-type matching logic and runtime entry points.

---

[Technical implementation](TECHNICAL.md) · [Statistics Nodes](../../02-statistics-nodes/README.md)
