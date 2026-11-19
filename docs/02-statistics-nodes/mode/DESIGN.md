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

For **[2, 2, 3, 3, 4]**, Value is 2, Modes is [2, 3], Frequency is 2, and Has Mode is true. For **[3, 3, 1, 1, 2, 2]**, Modes is [3, 1, 2]: the first-seen order is preserved.

## When every value is unique

Central intentionally reports **no mode** for [1, 2, 3]. Has Mode false, Modes empty and Frequency **1**. For an empty array, Frequency is **0**. No repeated value means no meaningful modal result by Central's chosen definition.

## Comparison rules

Mode uses exact/component-key matching, not an adjustable near-equality tolerance. Two floating-point values that look alike after rounding may count separately. Positive and negative zero share a frequency group. A non-finite numeric value invalidates the result.

## How to use it

For a collection of recent AI state enum values, connect the enum array and use Modes to understand ties. Use Has Mode before reading Value, so a default enum value is not mistaken for a real repeated state.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
