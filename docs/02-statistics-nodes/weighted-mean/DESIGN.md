# Weighted Mean Value — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## What it calculates

Weighted Mean calculates an average where each input's contribution is controlled by a corresponding nonnegative weight:

`sum(value × weight) / sum(weight)`

For Values [10, 20] and Weights [1.0, 3.0], Weighted Mean returns **17.5**.

## Inputs and outputs

| Pin | Meaning |
| --- | --- |
| Values | Connected supported numeric, vector or color array |
| Weights | **Double array**, one entry for every Value |
| Value | Weighted average or the output type's default on failure |
| Has Value | True when the weights and values produce a valid result |

## Weight requirements

- Values and Weights must have the **same nonzero length**.
- Every weight must be **finite and nonnegative**.
- At least one weight must be **strictly positive**.
- Zero weights are allowed and contribute nothing.
- A non-finite value is invalid even if its weight is zero.

## Blueprint workflow

Use a Make Array or variable for Values and a separate **Double** Make Array for Weights. Set up two damage scores [10, 20] and relative importance [1, 3], connect both arrays, and check Has Value before consuming 17.5.

To ignore one element, give it weight 0—but keep its numeric value finite. To give an element more influence, increase its weight relative to the others.

## Common failure cases

Lengths [2 values, 1 weight], negative weights, all-zero weights, an empty pair or NaN/Infinity return Has Value false. Integer-family Values produce Double results; supported math structs are calculated component by component.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
