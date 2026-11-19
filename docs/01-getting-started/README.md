# 01. Getting Started

**Central v1.0.0 · Blueprint statistics for Unreal Engine**

Central adds four pure Blueprint nodes under **Math → Statistics**. It lets you calculate typical values from arrays directly in graphs, without manually implementing sorting, frequency counting or accumulation.

## Start with the question

<!-- Media target: Image | central-start-overview | docs/assets/media/central-start-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-start-overview">
  <img src="../assets/media-placeholder.svg" alt="Four statistics operations answer different questions about a collection." loading="lazy">
  <figcaption>Four statistics operations answer different questions about a collection.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show four small labeled Blueprint examples using a shared simple dataset, each displaying a different applicable result.</span></figcaption>
</figure>

Use **Mean** for an ordinary average, **Median** when outliers could distort an average, **Mode** for repeated values and categories, and **Weighted Mean** when values deserve different contributions.

## Five-minute setup
1. Install Central v1.0.0 into an Unreal Engine 5.8 project and enable the plugin.
2. Open a Blueprint graph and right-click to find a Central statistics node.
3. Connect a supported **Values** array (use **Make Array** for inline test data).
4. Check **Has Value** or **Has Mode** to distinguish a valid zero from an invalid/default output.

The nodes have no execution pins. The array connection determines the output type. An unconnected Values array is **not** a usable default input.

## Topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **What Central Does** | Purpose, examples, feature scope and when to use each node | [Design](overview/DESIGN.md) | [Technical](overview/TECHNICAL.md) |
| **Installation & Compatibility** | Installing the plugin, version requirements and project structure | [Design](installation/DESIGN.md) | [Technical](installation/TECHNICAL.md) |
| **Your First Blueprint Graph** | Finding the nodes, connecting Values arrays and using validity outputs | [Design](first-graph/DESIGN.md) | [Technical](first-graph/TECHNICAL.md) |

For detailed implementation, use the companion Technical page for each topic.
