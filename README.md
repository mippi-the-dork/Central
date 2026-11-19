<div align="center">

<img src="Resources/Icon128.png" alt="Central plugin icon" width="96">

# Central

### Statistics belong in your Blueprint graph. Not in a maze of math nodes.

**Mean · Median · Mode · Weighted Mean** for Unreal Engine Blueprints.

Four compact, type-aware nodes. Clear results. Less graph clutter.

[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.8.x-black?logo=unrealengine)](https://www.unrealengine.com/)
![Platform](https://img.shields.io/badge/Platform-Win64-blue)
![Modules](https://img.shields.io/badge/Runtime%20%2B%20Editor-Modules-2c9f79)
![Version](https://img.shields.io/badge/Version-1.0.0-327cc8)
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

**[Explore the Documentation](https://mippi-the-dork.github.io/Central/)** · **[Get Central](https://github.com/mippi-the-dork/Central/releases)** · **[View the Source](https://github.com/mippi-the-dork/Central)**

</div>

---

## Your data has a story. Find the useful number.

Blueprints are great at manipulating values. But answering a basic question about an array can quickly mean building another set of loops, branches, counters, sorting logic, and temporary variables.

**Central gives those everyday questions their own nodes.** Connect a supported array, read the result, and get back to the system you're actually designing.

| The question | Use | Example result |
| --- | --- | --- |
| **What's the average?** | **Mean** | `[2, 4, 6, 8]` → **5** |
| **What's the middle value?** | **Median** | `[1, 3, 5, 9, 100]` → **5** |
| **What occurs most often?** | **Mode** | `[2, 2, 3, 3, 4]` → **2 and 3** |
| **What if some values matter more?** | **Weighted Mean** | `[10, 20]` with weights `[1, 3]` → **17.5** |

You'll find all four under **Math → Statistics** in the Blueprint action menu.

**[See all four nodes, their pins, and practical examples →](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2FREADME.md)**

## Built for real Blueprint work

**Compact, pure nodes.** No execution pins or custom workflow to manage. Central fits directly into graphs where you're already using arrays.

**Types that adapt to your data.** Connect a supported array to **Values** and the output pins resolve accordingly. Integer, Integer64, and Byte averages produce **Double** results, so an average like `1.5` isn't silently truncated.

**More than just numbers.** Mean, Median, and Weighted Mean support component-wise calculations for Vector2D, Vector, Vector4, and Linear Color. Mode also supports repeated Booleans, Strings, Names, Rotators, and supported byte-backed native/Blueprint enums.

**Ties aren't thrown away.** Mode exposes the first encountered qualifying value, **every tied mode**, their **Frequency**, and **Has Mode**.

**Know whether a result is valid.** **Has Value** and **Has Mode** distinguish a real zero from an invalid or absent statistic—important when game logic depends on the answer.

**Your input stays yours.** Central does not reorder the original array just to calculate a median.

**Useful in packaged games.** Blueprint authoring lives in an Editor module; the calculations live in a separate Runtime module.

## Where would you use it?

- **Gameplay balancing:** Compare recent damage, movement, or scoring samples.
- **AI and procedural systems:** Find commonly selected states or summarize generated values.
- **Telemetry and playtesting:** Distinguish typical behavior from unusual outliers.
- **Weighted decisions:** Combine several scores using explicit, nonnegative contribution weights.
- **Vectors and colors:** Calculate component-wise typical values without building separate calculations for each channel.

Central doesn't collect these samples for you. **You supply the arrays; Central answers the statistical question.**

## See Central in action

The [full documentation website](https://mippi-the-dork.github.io/Central/) contains focused user guides and separate implementation references, including:

| Want to… | Go here |
| --- | --- |
| Set up Central and create your first graph | [Getting Started](https://mippi-the-dork.github.io/Central/?page=01-getting-started%2FREADME.md) |
| Find the right node for your problem | [Statistics Nodes](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2FREADME.md) |
| Understand tied modes and categorical values | [Mode Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fmode%2FDESIGN.md) |
| Build a weighted average correctly | [Weighted Mean Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fweighted-mean%2FDESIGN.md) |
| Check whether your array type is supported | [Supported Data Types](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fsupported-types%2FDESIGN.md) |
| Understand wildcard pins and changing types | [Wildcard Pins & Graph Changes](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fwildcard-pins%2FDESIGN.md) |
| Handle empty data, invalid results, and precision | [Validity & Edge Cases](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fvalidity-and-edge-cases%2FDESIGN.md) |
| Explore the C++ implementation | [Runtime and Editor Architecture](https://mippi-the-dork.github.io/Central/?page=04-implementation-and-testing%2Farchitecture%2FTECHNICAL.md) |
| Find fixes or report a problem | [Troubleshooting](https://mippi-the-dork.github.io/Central/?page=05-support%2Ftroubleshooting%2FDESIGN.md) |

**[OPEN THE CENTRAL DOCUMENTATION WEBSITE →](https://mippi-the-dork.github.io/Central/)**

## A focused tool, not an entire statistics suite

Central is deliberately small in scope. It provides **four** statistics operations—not variance, standard deviation, percentiles, data visualization, automatic analytics collection, or a replacement for Unreal's math libraries.

A few boundaries matter:

- **Supported arrays only.** Arbitrary custom structs, Gameplay Tags, UObject references, nested arrays, and every possible enum representation are not supported.
- **Connect Values.** The wildcard input requires a connected supported array; use **Make Array** for inline values.
- **Mode requires repetition.** All-unique inputs deliberately return **Has Mode = false**, even though the highest observed frequency is one.
- **Weights have rules.** Weighted Mean requires one finite, nonnegative **Double** weight per value and at least one positive weight.
- **Numerical precision still applies.** Very close floating-point values can count as distinct Mode values; large Integer64 values can lose precision when converted to Double.
- **Check validity outputs.** Empty or invalid numerical inputs return an invalid result; a default value alone does not tell you whether the calculation succeeded.

For the exact behavior, supported types, and examples, see [Limitations and Edge Cases](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fvalidity-and-edge-cases%2FDESIGN.md).

## Compatibility and installation

**Current release:** Central **v1.0.0** · **Unreal Engine 5.8.x** · **Win64** · **Runtime + Editor**

Download an available matching package from [Releases](https://github.com/mippi-the-dork/Central/releases), or use the source in this repository with an Unreal Engine C++ build environment. Complete installation and updating instructions live in the [Installation Guide](https://mippi-the-dork.github.io/Central/?page=01-getting-started%2Finstallation%2FDESIGN.md).

## Contributing, issues, and feature requests

**Found a bug?** [Open an issue](https://github.com/mippi-the-dork/Central/issues/new) with your Unreal version, Central version, array type, example data, expected/actual results, and any relevant Blueprint compiler messages or screenshots. Check [Troubleshooting](https://mippi-the-dork.github.io/Central/?page=05-support%2Ftroubleshooting%2FDESIGN.md) first.

**Have a feature idea?** [Start a feature request](https://github.com/mippi-the-dork/Central/issues/new) explaining the gameplay or graph-authoring problem, why the proposed statistic or type helps, and what the results should mean for empty or invalid inputs. The [Roadmap](https://mippi-the-dork.github.io/Central/?page=ROADMAP.md) distinguishes shipped functionality from unannounced future work.

**Want to contribute code or documentation?** Issues and pull requests are welcome. For a substantial change, discuss the scope in an issue first. Keep contributions focused, document new behavior, and include relevant tests where appropriate.

## License

Central is provided under the **MIT License**. See [LICENSE](LICENSE) for the complete terms and copyright notice.

---

<div align="center">

**Four nodes. Better answers. Cleaner Blueprints.**

**[Read the Docs](https://mippi-the-dork.github.io/Central/)** · [Releases](https://github.com/mippi-the-dork/Central/releases) · [Report an Issue](https://github.com/mippi-the-dork/Central/issues)

</div>
