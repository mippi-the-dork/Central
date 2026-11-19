# Central Documentation Media Inventory

The site contains **32 planned media placements** across **28 pages**: **26 images/diagrams** and **6 GIF demonstrations**. They use a neutral placeholder until real Blueprint captures or source-grounded technical diagrams replace them.

Every placement has an intended public caption and a distinct **Capture instructions · Image/GIF** line explaining exactly what to show. The same requirements appear in [media-slots.json](assets/media-slots.json).

| Page | Media | Final file |
| --- | --- | --- |
| [README.md](README.md) | Image | `central-hero.png` |
| [01-getting-started/README.md](01-getting-started/README.md) | Image | `central-start-overview.png` |
| [02-statistics-nodes/README.md](02-statistics-nodes/README.md) | Image | `central-four-nodes.png` |
| [03-types-and-pins/README.md](03-types-and-pins/README.md) | Image | `central-types-overview.png` |
| [04-implementation-and-testing/README.md](04-implementation-and-testing/README.md) | Image | `central-modules-overview.png` |
| [05-support/README.md](05-support/README.md) | Image | `central-support-triage.png` |
| [01-getting-started/overview/DESIGN.md](01-getting-started/overview/DESIGN.md) | Image | `central-overview.png` |
| [01-getting-started/overview/TECHNICAL.md](01-getting-started/overview/TECHNICAL.md) | Image | `central-source-ownership.png` |
| [01-getting-started/installation/DESIGN.md](01-getting-started/installation/DESIGN.md) | Image | `central-install.png` |
| [01-getting-started/first-graph/DESIGN.md](01-getting-started/first-graph/DESIGN.md) | GIF | `central-first-graph.gif` |
| [02-statistics-nodes/mean/DESIGN.md](02-statistics-nodes/mean/DESIGN.md) | Image | `central-mean.png` |
| [02-statistics-nodes/mean/DESIGN.md](02-statistics-nodes/mean/DESIGN.md) | GIF | `central-mean-types.gif` |
| [02-statistics-nodes/median/DESIGN.md](02-statistics-nodes/median/DESIGN.md) | Image | `central-median.png` |
| [02-statistics-nodes/median/DESIGN.md](02-statistics-nodes/median/DESIGN.md) | GIF | `central-median-even.gif` |
| [02-statistics-nodes/mode/DESIGN.md](02-statistics-nodes/mode/DESIGN.md) | Image | `central-mode.png` |
| [02-statistics-nodes/mode/DESIGN.md](02-statistics-nodes/mode/DESIGN.md) | GIF | `central-mode-unique.gif` |
| [02-statistics-nodes/weighted-mean/DESIGN.md](02-statistics-nodes/weighted-mean/DESIGN.md) | Image | `central-weighted-mean.png` |
| [02-statistics-nodes/weighted-mean/DESIGN.md](02-statistics-nodes/weighted-mean/DESIGN.md) | GIF | `central-weighted-invalid.gif` |
| [03-types-and-pins/supported-types/DESIGN.md](03-types-and-pins/supported-types/DESIGN.md) | Image | `central-supported-types.png` |
| [03-types-and-pins/wildcard-pins/DESIGN.md](03-types-and-pins/wildcard-pins/DESIGN.md) | GIF | `central-wildcard.gif` |
| [03-types-and-pins/validity-and-edge-cases/DESIGN.md](03-types-and-pins/validity-and-edge-cases/DESIGN.md) | Image | `central-validity.png` |
| [03-types-and-pins/enums-and-complex-types/DESIGN.md](03-types-and-pins/enums-and-complex-types/DESIGN.md) | Image | `central-enum.png` |
| [03-types-and-pins/wildcard-pins/TECHNICAL.md](03-types-and-pins/wildcard-pins/TECHNICAL.md) | Image | `central-pin-reconstruction.png` |
| [03-types-and-pins/enums-and-complex-types/TECHNICAL.md](03-types-and-pins/enums-and-complex-types/TECHNICAL.md) | Image | `central-enum-thunk.png` |
| [04-implementation-and-testing/architecture/DESIGN.md](04-implementation-and-testing/architecture/DESIGN.md) | Image | `central-compile-flow.png` |
| [04-implementation-and-testing/architecture/TECHNICAL.md](04-implementation-and-testing/architecture/TECHNICAL.md) | Image | `central-architecture.png` |
| [04-implementation-and-testing/algorithms/DESIGN.md](04-implementation-and-testing/algorithms/DESIGN.md) | Image | `central-complexity.png` |
| [04-implementation-and-testing/verification/DESIGN.md](04-implementation-and-testing/verification/DESIGN.md) | Image | `central-automation.png` |
| [05-support/faq/DESIGN.md](05-support/faq/DESIGN.md) | Image | `central-mode-faq.png` |
| [05-support/troubleshooting/DESIGN.md](05-support/troubleshooting/DESIGN.md) | Image | `central-compile-error.png` |
| [05-support/updating/DESIGN.md](05-support/updating/DESIGN.md) | Image | `central-update.png` |
| [ROADMAP.md](ROADMAP.md) | Image | `central-roadmap.png` |

## Replacing the placeholders

Capture the actual Unreal Blueprint behavior or create an accurate diagram from Central's C++ source. Save under `docs/assets/media/` using the listed filename, change the figure's relative `src`, and retain or refine the reader caption. Check that the image/GIF stays within the article width on desktop and mobile.

Central's existing `Resources/Icon128.png` is used for the header and favicon, not substituted for a real Blueprint screenshot.
