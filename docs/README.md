# Central Documentation

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor modules**

Central brings **Mean, Median, Mode and Weighted Mean** into Unreal Engine Blueprints as four compact, type-aware, pure math nodes. With a supported array connected, you can calculate a useful statistic without constructing the underlying array math, sorting or frequency-counting graph by hand.

![Central Blueprint statistics overview](assets/media-placeholder.svg)

*Central places four statistics operations directly in Blueprint graphs, with outputs that adapt to the connected array type.*

**Capture instructions · Image:** Capture a clean Unreal Blueprint graph showing all four Central nodes—Mean, Median, Mode and Weighted Mean—connected to representative supported arrays, with the node titles and output pins readable. Use this as the site's main product screenshot.

## What can I do with Central?

**Find a typical value.** Use Mean for an average or Median to find the middle of sorted numeric or mathematical values.

**Identify repeated values.** Mode finds the most frequent value and every tied mode, including non-numeric categories such as Strings, Names, Booleans and supported enums.

**Account for importance.** Weighted Mean accepts a Double weight per value, so selected entries contribute more or less to the result.

**Work with Blueprint arrays.** A connected Values array establishes the node's type; integers can return fractional Double averages, and supported vectors and colors are processed component by component.

## Get started in three steps

1. [Install Central](01-getting-started/installation/DESIGN.md) in a supported UE 5.8 project.
2. [Build your first Blueprint statistics graph](01-getting-started/first-graph/DESIGN.md) with an array and a validity output.
3. [Choose the right statistics node](02-statistics-nodes/README.md), then consult the [data type reference](03-types-and-pins/supported-types/DESIGN.md).

## Which documentation should I read?

**Design** explains what to do in the Blueprint Editor, what each output means, and which node to choose for a gameplay task. **Technical** describes type resolution, C++ implementations, numerical behavior, K2 node compilation and integration limitations.

Each feature topic has its own Design and Technical page. The two pages complement rather than duplicate each other.

## Explore the manual

| Category | Topics | What you'll find |
| --- | ---: | --- |
| [01. Getting Started](01-getting-started/README.md) | 3 | How Central works, how to install it, and how to build your first statistics graph |
| [02. Statistics Nodes](02-statistics-nodes/README.md) | 4 | Complete guides for Central's four Blueprint math operations |
| [03. Types and Blueprint Pins](03-types-and-pins/README.md) | 4 | Supported arrays, wildcard pin typing, enums and result validity |
| [04. Implementation & Testing](04-implementation-and-testing/README.md) | 3 | Technical architecture, algorithms and ways to verify real behavior |
| [05. Support](05-support/README.md) | 3 | Answers, troubleshooting steps, updates and support channels |

## Important limitations

Central supports specific array element types, not arbitrary UObject references, user-defined structs, Gameplay Tags, nested arrays or every enum representation. The Values input requires a connected array, and **Has Value / Has Mode** must be used to detect invalid or absent results.

Mode intentionally reports **no mode** when all values appear only once. Median uses a working copy rather than rearranging the original array. Invalid numeric inputs and invalid weight arrays do not produce a valid statistic.

## Future development and resources

The [Roadmap](ROADMAP.md) records Central v1.0.0 as the current release and distinguishes future possibilities from announced plans. The [Media Inventory](MEDIA_INVENTORY.md) lists image/GIF capture instructions for these guides.

[Central on GitHub](https://github.com/mippi-the-dork/Central) · [Releases](https://github.com/mippi-the-dork/Central/releases) · [Report an issue](https://github.com/mippi-the-dork/Central/issues)

**Documentation basis:** Central v1.0.0 repository source and README, reviewed November 2026. Source inspection is not a substitute for live Unreal Editor or packaged-game testing.
