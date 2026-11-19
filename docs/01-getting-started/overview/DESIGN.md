# What Central Does — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## The problem Central solves

<!-- Media target: Image | central-overview | docs/assets/media/central-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-overview">
  <img src="../../assets/media-placeholder.svg" alt="Central replaces common Blueprint array-math patterns with compact statistics nodes." loading="lazy">
  <figcaption>Central replaces common Blueprint array-math patterns with compact statistics nodes.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture the four statistics nodes in a typical Blueprint graph with sample arrays and key outputs visible.</span></figcaption>
</figure>


Unreal Blueprints provide general-purpose array and math nodes, but combining them into a readable statistical operation takes extra graph space. Central exposes **four pure nodes** in **Math → Statistics**. They take connected arrays and return a result with an explicit validity output.

| Question | Node | Sample result |
| --- | --- | --- |
| What is the arithmetic average? | Mean | [2, 4, 6, 8] → 5 |
| What is the central value after ordering? | Median | [1, 3, 5, 9, 100] → 5 |
| Which value appears most often? | Mode | [2, 2, 3, 3, 4] → two tied modes |
| What if some inputs matter more? | Weighted Mean | [10, 20] with weights [1, 3] → 17.5 |

## When to use each

For a player's recent damage measurements, Mean can summarize the overall average, while Median may better describe a typical hit if a single unusually high hit skews the set. Mode is useful when counting repeated, exact categories such as names or enum states. Weighted Mean supports design scores where individual entries contribute at different rates.

## What is included

Central ships a runtime calculation module and editor K2 nodes. The four graph nodes are **pure**, have **no execution pins**, and their output type follows a supported connected Values array. The plugin does not introduce new Actor types, gameplay components or a separate statistics editor.

## What Central is not

This is not a statistical analysis suite. It does not provide variance, standard deviation, percentiles, arbitrary custom-type handling or a universal aggregation framework in v1.0.0. Mode uses exact value matching rather than a user-defined floating-point tolerance.

Start with [your first graph](../first-graph/DESIGN.md) and [supported data types](../../03-types-and-pins/supported-types/DESIGN.md).

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
