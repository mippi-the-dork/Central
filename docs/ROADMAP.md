# Central Roadmap

**Current release:** Central v1.0.0 · Unreal Engine 5.8.x · Runtime and Editor modules  
**Status:** First public documentation baseline · November 2026

## At a glance

<!-- Media target: Image | central-roadmap | docs/assets/media/central-roadmap.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-roadmap">
  <img src="assets/media-placeholder.svg" alt="Central v1.0.0 is released; no future version or feature set has been announced." loading="lazy">
  <figcaption>Central v1.0.0 is released; no future version or feature set has been announced.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a milestone graphic with v1.0.0 Released listing Mean, Median, Mode and Weighted Mean, plus a separate Future Unannounced region; do not invent planned features.</span></figcaption>
</figure>


| Milestone | Status | Scope |
| --- | --- | --- |
| **v1.0.0 — Four Statistics Nodes** | Released | Mean, Median, Mode and Weighted Mean as type-aware, pure Blueprint nodes |
| **Future major/minor updates** | **Not announced** | No specific next-version number, delivery date, new supported type, node or feature is committed |

## v1.0.0 — Current capabilities

The initial release supplies four user-facing nodes under **Math → Statistics**.

- **Mean** computes an arithmetic average.
- **Median** returns the ordered middle, averaging the two central items for even counts.
- **Mode** finds repeated values and all qualifying ties, including supported categorical and enum arrays.
- **Weighted Mean** uses a corresponding Double weight array to control each value's contribution.

Central also provides runtime/editor module separation, wildcard Values array typing, integer-to-Double average promotion, validity outputs, and a native runtime automation test.

## What comes next?

Specific changes beyond v1.0.0 have **not been committed by the plugin author**. The roadmap deliberately does not label imagined statistics nodes, a new public API, or expanded types as planned features.

Possible requests can be discussed through [Central Issues](https://github.com/mippi-the-dork/Central/issues), with decisions made according to usefulness, Blueprint clarity, runtime performance, type safety and maintenance cost. Such requests do not become roadmap commitments until a release plan is approved.

## How future releases should be documented

When an update is planned, distinguish **Planned** from **Implemented**, **Released**, and **Verified**. Each shipped node or type should have:
- Design and Technical documentation;
- examples of valid and invalid input;
- explicit pin types and numeric behavior;
- a native runtime test and Blueprint compile/reconstruction checks;
- genuine editor screenshots and GIFs where they materially help.

[Current Statistics Nodes](02-statistics-nodes/README.md) · [Verification](04-implementation-and-testing/verification/DESIGN.md) · [GitHub](https://github.com/mippi-the-dork/Central)
