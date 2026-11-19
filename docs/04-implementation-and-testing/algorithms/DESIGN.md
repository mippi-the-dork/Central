# Algorithms & Performance — Design

**Central v1.0.0 · Source-grounded documentation**

## What each node does internally

| Node | General approach | Expected complexity |
| --- | --- | --- |
| Mean | Accumulate and average | O(n) |
| Median | Sort a working copy and select the middle | O(n log n) |
| Mode | Count occurrences using maps | O(n) expected |
| Weighted Mean | Validate weights and accumulate weighted contributions | O(n) |

These are **algorithmic estimates**, not UE performance benchmarks on a particular platform or dataset.

## Choosing with cost in mind

For a modest array of recent gameplay samples, any node may be appropriate. For large arrays evaluated frequently, Median's sorting and Mode's temporary frequency storage deserve additional attention. Because these are pure Blueprint nodes, avoid requesting expensive calculations many times per frame unless necessary.

## Memory behavior

Median uses a working copy while sorting; Mode uses additional counting structures as unique values accumulate. Mean and Weighted Mean do not sort the original input arrays.

## Mathematical expectations

Weighted Mean rejects negative weights and zero total contribution, unlike systems that might interpret signed weights as coefficients. Mode matches values exactly, rather than clustering close floating-point values.

## When to optimize

If arrays are large and change infrequently, compute once when data changes and cache the result in your gameplay logic. Don't assume a pure output is cached for you by the plugin.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
