# 04. Implementation & Testing

**Central v1.0.0 · Blueprint statistics for Unreal Engine**

The graph nodes visible to authors are implemented in **CentralEditor**, while actual calculations are provided by the separate **Central runtime module**. The runtime functions are used in compiled Blueprint gameplay; the editor module does not need to ship with a packaged game.

## What this section explains

<!-- Media target: Image | central-modules-overview | docs/assets/media/central-modules-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-modules-overview">
  <img src="../assets/media-placeholder.svg" alt="CentralEditor handles graph authoring and Central supplies runtime calculations." loading="lazy">
  <figcaption>CentralEditor handles graph authoring and Central supplies runtime calculations.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw an architecture diagram from UK2Node_Central editor graph to UCentralBPLibrary runtime functions and a packaged Blueprint.</span></figcaption>
</figure>

- How a wildcard K2 node resolves its supported type and expands into a typed function call during compilation.
- How each statistics operation computes results and handles invalid data.
- Which native Unreal Automation test exists, and what still needs hands-on Blueprint and packaging verification.

## Verification status
The repository includes **Central.Runtime.BasicStatistics**, but this site does not claim that the test has been executed in the user's UE 5.8 project. Test instructions and current verification limits are documented explicitly.

## Topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Runtime and Editor Architecture** | Plugin modules, node expansion and native function ownership | [Design](architecture/DESIGN.md) | [Technical](architecture/TECHNICAL.md) |
| **Algorithms & Performance** | Complexity, data handling, numeric strategies and limitations | [Design](algorithms/DESIGN.md) | [Technical](algorithms/TECHNICAL.md) |
| **Testing & Verification** | Existing native test, Blueprint test workflows and packaged-game checks | [Design](verification/DESIGN.md) | [Technical](verification/TECHNICAL.md) |

For day-to-day usage, start with [Getting Started](../01-getting-started/README.md).
