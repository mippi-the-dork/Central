# Frequently Asked Questions — Design

**Central v1.0.0 · Source-grounded documentation**

## Basics

**Where do I find the nodes?** In the Blueprint graph action menu under **Math → Statistics**. Search for Mean Value, Median Value, Mode Value or Weighted Mean Value.

**Why are there no execution pins?** Central's statistics nodes are pure calculations. They return values through data pins rather than requiring execution flow.

**Can I use Central in packaged gameplay?** The plugin has a Runtime module for calculations and a separate Editor module for authoring. Packaged behavior should still be verified in your project.

## Values and types

**Why is Values a wildcard?** Connecting a supported array determines the result type. An unconnected Values pin is not a valid input.

**Can I type an array directly into the Values pin?** Use Make Array or an array variable and connect it. The node requires a supported array link.

**Why is my Integer average a Double?** Integer/Integer64/Byte averages are promoted so fractional results are not truncated.

**Does Central support any Blueprint struct?** No. Only the documented math structs are supported.

## Results

<!-- Media target: Image | central-mode-faq | docs/assets/media/central-mode-faq.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-mode-faq">
  <img src="../../assets/media-placeholder.svg" alt="Mode can return Frequency 1 while reporting no repeated mode." loading="lazy">
  <figcaption>Mode can return Frequency 1 while reporting no repeated mode.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Mode input [1,2,3] with Frequency 1, empty Modes and Has Mode false visible together.</span></figcaption>
</figure>


**What does Has Value mean?** The input produced a valid statistic. A Value of zero is not the same as an invalid result.

**Why does Mode say Has Mode false for [1, 2, 3]?** Central requires at least one repeated value for a valid mode.

**Can Mode return several results?** Yes. Modes contains every tied highest-frequency repeated value, in encounter order.

**Does Median sort my input array?** No. It orders a working copy.

**Can Weighted Mean use negative weights?** No. All weights must be finite and nonnegative, with at least one positive weight.

**Do Mode float values use tolerance?** No. Exact/component-key comparison applies, with signed zero grouped together.

For code-level details, open the corresponding Technical reference.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
