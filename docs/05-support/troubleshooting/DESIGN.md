# Troubleshooting — Design

**Central v1.0.0 · Source-grounded documentation**

## I can't find the node

Check Central is enabled under **Edit → Plugins**, the project built successfully, and you are editing a Blueprint graph. Search **Mean Value** or **Mode Value**, or navigate **Math → Statistics**. If the module failed to load, check Output Log before assuming the plugin is correctly installed.

## Values pin won't connect or compile

Connect an **array** of a supported type. A scalar value, incompatible element type or disconnected Values pin is not valid. For Weighted Mean, connect a **Double array** to Weights of the same length as Values.

## Output type is unexpected

For Integer/Integer64/Byte input arrays, Mean, Median and Weighted Mean intentionally output **Double**. If you replace a connected array with a different type, review downstream links and recompile.

## Result is zero or empty

Inspect **Has Value** or **Has Mode**. A zero can be a legitimate mean, but also the default returned for an invalid result. All-unique Mode returns an empty Modes array and Frequency 1.

## Mode doesn't match similar-looking numbers

It uses exact/component-key equality. Floating-point values differing below displayed precision may count as different categories. Quantize first if you need bins or approximate grouping.

## Graph worked before saving/reopening

Reopen the Blueprint, inspect disconnected/reconstructed pins, compile and capture the compiler output. In particular, verify split struct pins and enum Mode connections with the actual type. Reconnecting changed-type downstream pins may be necessary.

## Weighted Mean returns invalid

Confirm matching nonzero array lengths, finite nonnegative Double weights, at least one positive weight, and finite Values—even when a corresponding weight is zero.

## Reporting a bug

Include exact version, platform, C++/Blueprint project configuration, graph screenshot, element type, example Values and Weights, compiler/log output and reproducible steps.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
