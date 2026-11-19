# Runtime and Editor Architecture — Design

**Central v1.0.0 · Source-grounded documentation**

## How Central fits into an Unreal project

Central has two separate modules: **Central** provides calculation functions usable at runtime; **CentralEditor** provides the graph nodes, wildcard pin handling, and compilation into those functions.

As a Blueprint author, you use the four compact statistics nodes. You don't need to call the internal typed functions or create a special statistics Actor.

## From graph to game

<!-- Media target: Image | central-compile-flow | docs/assets/media/central-compile-flow.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-compile-flow">
  <img src="../../assets/media-placeholder.svg" alt="Central's graph nodes compile into typed runtime function calls." loading="lazy">
  <figcaption>Central's graph nodes compile into typed runtime function calls.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Diagram Blueprint wildcard node → supported-type resolution → UK2Node_CallFunction → Central Runtime execution in packaged gameplay.</span></figcaption>
</figure>


1. Place Mean, Median, Mode or Weighted Mean in a Blueprint.
2. Connect a supported array to Values.
3. Central's editor node determines the output type.
4. During Blueprint compilation, the custom node becomes a call to a typed runtime function.
5. The packaged game runs the result calculation without requiring the editor UI module.

## Why this separation matters

Editor-only graph classes are not intended to ship as gameplay runtime dependencies. Keeping the calculations in the Runtime module also allows packaged Blueprints to execute the statistic that was authored in the editor.

## For technical users

Use the Technical page to trace the module descriptor, K2 graph nodes and runtime functions. The [Algorithms](../algorithms/TECHNICAL.md) page explains how Mean, Median, Mode and Weighted Mean handle their data.

## Integration boundaries

Central does not implement background sampling, statistics recording, network synchronization, persistent storage or gameplay telemetry collection. You provide arrays from your own gameplay system; Central calculates on those inputs.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
