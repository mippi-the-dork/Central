# Enums & Complex Values — Design

**Central v1.0.0 · Type and graph behavior**

## Using Mode on an enum array

Mode supports **byte-backed native and Blueprint enums**, preserving the enum element type on Value and Modes. Connect an array of supported enum values; it returns the first encountered repeated category and all tied categories.

For example, with AI states [Idle, Patrol, Patrol, Attack, Idle], the results are:
- Value = Idle (the first encountered tied mode)
- Modes = [Idle, Patrol]
- Frequency = 2
- Has Mode = true

You can use Modes to handle a tie instead of taking the scalar Value as the only answer.

## When a type works only with Mode

Boolean, String, Name and Rotator arrays can be counted for repetitions but cannot be meaningfully averaged or sorted by Central's Mean/Median/Weighted Mean nodes. Their unsupported operation pins should not accept those array types.

## Vectors and colors

Mean, Median and Weighted Mean work with Vector2D, Vector, Vector4 and Linear Color by calculating each component independently. A median Vector may combine X from one observation and Y from another, so it may not match any original vector.

Mode counts supported vector/rotator/color values using exact component-based keys. Small floating-point differences can create distinct categories.

## What about arbitrary enums?

Only supported byte-backed enum representations are documented. Unsupported native enum underlying types or arbitrary custom structs are not covered. Check the actual Blueprint connection and compiler diagnostic rather than assuming all enum definitions behave identically.

---

[Technical implementation](TECHNICAL.md) · [Statistics Nodes](../../02-statistics-nodes/README.md)
