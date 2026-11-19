# Mean Value — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## What it calculates

Mean is the arithmetic average of a supported array:

`Mean = (sum of values) / (number of values)`

For Values **[2, 4, 6, 8]**, Mean returns **5.0**.

## Blueprint pins

| Pin | Direction | Meaning |
| --- | --- | --- |
| Values | Input | Connected supported array |
| Value | Output | Average, or default when invalid |
| Has Value | Output | True only when a valid average was produced |

## Typical workflow

<!-- Media target: Image | central-mean | docs/assets/media/central-mean.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-mean">
  <img src="../../assets/media-placeholder.svg" alt="Mean calculates a valid arithmetic average from supported arrays." loading="lazy">
  <figcaption>Mean calculates a valid arithmetic average from supported arrays.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Mean connected to Integer Make Array [2,4,6,8] and show its Double result 5.0 and Has Value output.</span></figcaption>
</figure>


Use Mean when summarizing sampled quantities, such as several observed damage values or frame-to-frame measurements. Feed the array into Values, branch or select on Has Value, then use Value in the gameplay logic.

## Integer and structure behavior

<!-- Media target: GIF | central-mean-types | docs/assets/media/central-mean-types.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="central-mean-types">
  <img src="../../assets/media-placeholder.svg" alt="Integer Mean retains fractional answers while Vector Mean returns a Vector." loading="lazy">
  <figcaption>Integer Mean retains fractional answers while Vector Mean returns a Vector.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record changing the connected Values type from [1,2] Integers to Vectors; show the Double 1.5 output and later Vector output pin type.</span></figcaption>
</figure>


An Integer, Integer64 or Byte array produces a **Double** answer, preserving fractions. For example, [1, 2] → 1.5. Vector2D, Vector, Vector4 and Linear Color are averaged **per component**, rather than converted to a scalar length or luminance.

## Invalid data

An empty array or a non-finite numeric component (NaN/Infinity) produces Has Value false. A legitimate zero mean, such as [-1, 1], produces Value 0 with Has Value true. Always check validity when an empty collection is possible.

## Choosing Median instead

Mean is affected by outliers. If you need the middle observation rather than the overall arithmetic average, see [Median](../median/DESIGN.md).

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
