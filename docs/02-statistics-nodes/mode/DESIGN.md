# Mode Value — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## What it calculates

Mode finds the value or values appearing most frequently. Unlike the averaging operations, Mode also works on supported categorical arrays such as Boolean, String, Name and enum values.

## Blueprint pins

| Pin | Meaning |
| --- | --- |
| Values | Connected supported array |
| Value | First qualifying mode encountered in original input order |
| Modes | Every tied mode, preserving first-encounter order |
| Frequency | Count shared by each most-frequent value |
| Has Mode | True only when a value repeats (frequency greater than 1) |

## Tie behavior

<!-- Media target: Image | central-mode | docs/assets/media/central-mode.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-mode">
  <img src="../../assets/media-placeholder.svg" alt="Mode returns all tied repeated values and preserves first-encounter order." loading="lazy">
  <figcaption>Mode returns all tied repeated values and preserves first-encounter order.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture input [2,2,3,3,4] and outputs Value 2, Modes [2,3], Frequency 2 and Has Mode true.</span></figcaption>
</figure>


For **[2, 2, 3, 3, 4]**, Value is 2, Modes is [2, 3], Frequency is 2, and Has Mode is true. For **[3, 3, 1, 1, 2, 2]**, Modes is [3, 1, 2]: the first-seen order is preserved.

## When every value is unique

<!-- Media target: GIF | central-mode-unique | docs/assets/media/central-mode-unique.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="central-mode-unique">
  <img src="../../assets/media-placeholder.svg" alt="All-unique Mode has Frequency 1 but Has Mode false." loading="lazy">
  <figcaption>All-unique Mode has Frequency 1 but Has Mode false.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record switching from [1,2,3] (no mode, Frequency 1) to [2,2,3] (repeated mode, Frequency 2); clearly show both validity states.</span></figcaption>
</figure>


Central intentionally reports **no mode** for [1, 2, 3]. Has Mode false, Modes empty and Frequency **1**. For an empty array, Frequency is **0**. No repeated value means no meaningful modal result by Central's chosen definition.

## Comparison rules

Mode uses exact/component-key matching, not an adjustable near-equality tolerance. Two floating-point values that look alike after rounding may count separately. Positive and negative zero share a frequency group. A non-finite numeric value invalidates the result.

## How to use it

For a collection of recent AI state enum values, connect the enum array and use Modes to understand ties. Use Has Mode before reading Value, so a default enum value is not mistaken for a real repeated state.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
