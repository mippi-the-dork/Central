# Wildcard Pins & Graph Changes — Design

**Central v1.0.0 · Type and graph behavior**

## Why Values starts as a wildcard

Central uses one compact node per operation, instead of exposing separate graph nodes for integers, floats, vectors and every other supported type. Its Values pin starts as a **wildcard array**; the connected array tells Central which typed calculation to use.

## Connecting an array

1. Add a Central node using the Blueprint action menu.
2. Create or find an array variable or Make Array node with a supported element type.
3. Connect the array to **Values**.
4. Watch the node's Value output update to the compatible scalar/struct type.
5. For Mode, the Modes output becomes an array of the same element type.
6. Recompile after changing array types.

## Changing the type later

Disconnect an Integer array and connect a Vector array. Existing downstream nodes expecting Double may no longer be compatible with the Vector result, so review and reconnect those downstream pins.

Saved Blueprints preserve their graph pins through Unreal's reconstruction system. Central attempts to restore compatible links, but incompatible replacements require author intervention.

## Split structure pins

If you split a Vector result into X/Y/Z, change an upstream type and recompile, inspect the reconstructed pins. A split output from one struct cannot automatically remain connected to an incompatible struct.

## What is not supported

The Values input is **not** a free editable default array; connect a Make Array or array variable. It does not infer type from arbitrary unrelated numeric scalar pins. For Mean/Median/Weighted Mean, an incompatible output connection cannot make an otherwise unsupported Values array valid.

---

[Technical implementation](TECHNICAL.md) · [Statistics Nodes](../../02-statistics-nodes/README.md)
