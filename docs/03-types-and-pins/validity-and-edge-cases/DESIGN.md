# Validity & Edge Cases — Design

**Central v1.0.0 · Type and graph behavior**

## Never assume default output means success

<!-- Media target: Image | central-validity | docs/assets/media/central-validity.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-validity">
  <img src="../../assets/media-placeholder.svg" alt="Two outputs may both equal zero even when only one represents a valid result." loading="lazy">
  <figcaption>Two outputs may both equal zero even when only one represents a valid result.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show Mean([-1,1]) producing zero with Has Value true beside empty Mean producing default zero with Has Value false.</span></figcaption>
</figure>


Central reports **Has Value** for Mean, Median and Weighted Mean, and **Has Mode** for Mode. A valid average may be zero, so comparing `Value != 0` is not a reliable validity check.

| Input or condition | Result behavior |
| --- | --- |
| Empty Mean/Median/Weighted Mean array | Has Value false; Value default |
| Mean([-1, 1]) | Has Value true; Value 0 |
| All-unique Mode([1, 2, 3]) | Has Mode false; Modes empty; Frequency 1 |
| Empty Mode array | Has Mode false; Modes empty; Frequency 0 |
| Invalid numeric NaN/Infinity | Invalid result; don't consume default Value |
| Weighted Mean mismatched lengths | Has Value false |
| Weighted Mean with negative/non-finite weight | Has Value false |
| Weighted Mean with all zero weights | Has Value false |
| Weighted Mean with some zero, some positive weights | Valid if all values and weights are otherwise valid |

## Safe Blueprint consumption

Feed Has Value/Has Mode into a Branch or Select-style decision before using the calculated result. Provide a meaningful fallback for empty samples or missing repeated values, rather than treating a default zero or empty array as actual telemetry.

## Mode frequency is not validity

All-unique Mode has **Frequency 1** but Has Mode false. Frequency describes the highest count observed; Central's definition of a mode requires a repeat.

## Precision and equality

Large Integer64 inputs can lose precision when converted to Double. Floating-point values close together may remain different Mode categories, and signed zero is grouped as equal. Mode does not have an epsilon/rounding setting. If grouping approximate values is required, deliberately quantize the input before using Mode.

## What if I need an empty array to mean zero?

That is an application-level policy. Central reports the statistic as invalid and leaves your Blueprint to decide whether to use zero, a default state or skip an update.

---

[Technical implementation](TECHNICAL.md) · [Statistics Nodes](../../02-statistics-nodes/README.md)
