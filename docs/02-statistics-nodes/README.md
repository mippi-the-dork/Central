# 02. Statistics Nodes

**Central v1.0.0 · Blueprint statistics for Unreal Engine**

Every Central statistics operation is a pure Blueprint node. Each provides **Values** as an array input and a result; all but Mode use **Has Value**, while Mode uses **Has Mode** and additionally exposes **Modes** and **Frequency**.

## Choose the right statistic

<!-- Media target: Image | central-four-nodes | docs/assets/media/central-four-nodes.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-four-nodes">
  <img src="../assets/media-placeholder.svg" alt="Central provides four pure nodes under Math → Statistics." loading="lazy">
  <figcaption>Central provides four pure nodes under Math → Statistics.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture all four nodes side-by-side in the Blueprint Editor with Mean, Median, Mode, Weighted Mean titles and validity pins legible.</span></figcaption>
</figure>


| Task | Node | Example |
| --- | --- | --- |
| Typical score across several attempts | Mean | [2, 4, 6, 8] → 5 |
| Middle of values including an outlier | Median | [1, 3, 5, 9, 100] → 5 |
| Most common observed category/value | Mode | [A, B, B, A, C] → A and B tied |
| Weighted score | Weighted Mean | [10, 20] with [1, 3] → 17.5 |

Each node below has a **Design** guide for graph workflows and a **Technical** guide for C++ behavior, pin expansion and edge cases.

## Topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Mean Value** | Arithmetic average, numeric precision and component-wise results | [Design](mean/DESIGN.md) | [Technical](mean/TECHNICAL.md) |
| **Median Value** | Ordered middle values, even counts, and unsorted input arrays | [Design](median/DESIGN.md) | [Technical](median/TECHNICAL.md) |
| **Mode Value** | Repeated values, ties, no-mode behavior and frequency outputs | [Design](mode/DESIGN.md) | [Technical](mode/TECHNICAL.md) |
| **Weighted Mean Value** | Weight arrays, nonnegative weights and weighted averages | [Design](weighted-mean/DESIGN.md) | [Technical](weighted-mean/TECHNICAL.md) |

**All four nodes:** [Mean](mean/DESIGN.md) · [Median](median/DESIGN.md) · [Mode](mode/DESIGN.md) · [Weighted Mean](weighted-mean/DESIGN.md).
