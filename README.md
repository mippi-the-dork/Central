# Central

**Blueprint Statistics for Unreal Engine**

**Spend less time building math graphs. Spend more time using the answers.**

Central brings **Mean, Median, Mode and Weighted Mean** into Unreal Engine Blueprints as four compact, type-aware nodes. Connect a supported array to get the average, find its middle value, identify repeated values or account for the relative importance of individual entries—without rebuilding the same sorting, counting and averaging logic.

[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.8.x-black?logo=unrealengine)](https://www.unrealengine.com/) ![Platform](https://img.shields.io/badge/Platform-Win64-blue) ![Runtime + Editor](https://img.shields.io/badge/Plugin-Runtime%20%2B%20Editor-217346) ![Version](https://img.shields.io/badge/Central-v1.0.0-blue) [![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

<p align="center">
  <img src="Resources/Icon128.png" alt="Central plugin icon" width="128">
</p>

---

## Your Blueprint graph should answer the question

You have a collection of values and want to know what they tell you. A straightforward statistic shouldn't require another loop, sorting setup, collection of counters or several branches. Those extra nodes make the graph harder to read and add more logic to maintain.

**Central gives those common calculations a home.**

- **Get a useful average.** Find the arithmetic mean of your numeric, vector or color samples.
- **See past the outliers.** Use Median to find the middle of a dataset rather than letting one unusual value dominate.
- **Find what's most common.** Mode reports repeated values—including tied results and supported enum categories.
- **Account for importance.** Weighted Mean lets some samples contribute more than others.
- **Keep results meaningful.** Validity pins tell you whether a calculation actually produced an answer, even when that answer is zero.

## Explore the documentation

> ### [**Central Documentation — Full User Guide and Technical Reference**](https://mippi-the-dork.github.io/Central/)
>
> **Everything you need to learn and use Central, in one place.** Browse each statistics node, build your first Blueprint graph, check supported array types and validity rules, or explore the implementation and troubleshooting guides.
>
> **[Get Started](https://mippi-the-dork.github.io/Central/?page=01-getting-started%2FREADME.md)** · **[All Statistics Nodes](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2FREADME.md)** · **[Types & Blueprint Pins](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2FREADME.md)** · **[Troubleshooting](https://mippi-the-dork.github.io/Central/?page=05-support%2Ftroubleshooting%2FDESIGN.md)**

The README introduces what Central offers. **The [documentation website](https://mippi-the-dork.github.io/Central/) is the maintained reference for exact pin behavior, installation, examples and technical details.**

## Four statistics. One clean approach.

All four nodes are available from the Blueprint action menu under **Math → Statistics**.

| Statistics node | What you can do |
| --- | --- |
| **[Mean Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fmean%2FDESIGN.md)** | Calculate the arithmetic average. For example, `[2, 4, 6, 8]` returns **5**. |
| **[Median Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fmedian%2FDESIGN.md)** | Find the middle of the ordered values, even with outliers. `[1, 3, 5, 9, 100]` returns **5**. |
| **[Mode Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fmode%2FDESIGN.md)** | Find the most frequent values, including ties. `[2, 2, 3, 3, 4]` returns **2 and 3** as modes. |
| **[Weighted Mean Value](https://mippi-the-dork.github.io/Central/?page=02-statistics-nodes%2Fweighted-mean%2FDESIGN.md)** | Give inputs different contributions. Values `[10, 20]` with weights `[1, 3]` return **17.5**. |

These are **pure Blueprint nodes**, with no execution pins. Central calculates from the arrays you provide; it doesn't require special Actors, components or an additional editor.

## Useful in real production workflows

### Make sense of gameplay samples

Average recent damage, response times or scores without adding another arithmetic subgraph. If a few extreme samples distort the result, use Median to describe the middle instead.

### Find patterns in AI and procedural systems

Use Mode to identify the most frequently observed AI state, selected category or generated value. Mode can work with supported non-numeric data, including **Booleans, Strings, Names and byte-backed enums**. When several values tie for the highest repeated frequency, **Modes** returns all of them.

### Combine scores with different priorities

Weighted Mean makes it straightforward to combine sampled values with explicit importance. Provide a **Double** weight array alongside your Values array; zero weights are allowed, and at least one weight must be positive.

### Work naturally with Blueprint types

The **Values** array connection determines the compatible output type. Integer, Integer64 and Byte inputs return **Double** results for Mean, Median and Weighted Mean, preserving fractional averages. Supported Vector2D, Vector, Vector4 and Linear Color calculations operate component by component.

### Know whether the result is usable

**Has Value** or **Has Mode** distinguishes a legitimate result of `0` from a calculation with no usable result. Median does not rearrange your input array; it orders a working copy instead.

[**Learn about supported types, validity, and numerical edge cases →**](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fvalidity-and-edge-cases%2FDESIGN.md)

## Get Central

**Central v1.0.0** targets **Unreal Engine 5.8.x on Windows 64-bit**, with separate **Runtime** and **Editor** modules.

Choose a compatible prebuilt release when available, or install the full source from this repository in a project with a working Unreal Engine C++ toolchain. The calculations are in the Runtime module; the authoring nodes are provided by the Editor module.

**[Download GitHub Releases](https://github.com/mippi-the-dork/Central/releases)** · **[Installation Guide](https://mippi-the-dork.github.io/Central/?page=01-getting-started%2Finstallation%2FDESIGN.md)** · **[Your First Blueprint Graph](https://mippi-the-dork.github.io/Central/?page=01-getting-started%2Ffirst-graph%2FDESIGN.md)**

## Important limitations

Central is a **focused Blueprint statistics plugin**, not a full statistical analysis, telemetry or data-collection system.

- **Four operations, not an analytics suite.** It doesn't provide standard deviation, variance, percentiles, charting or automatic sample collection.
- **Supported arrays only.** Arbitrary custom structs, Gameplay Tags, UObject references, nested arrays and unsupported native enum representations are outside the current type set.
- **A connected Values array is required.** Use a supported array variable or **Make Array**; don't leave the wildcard input unconnected.
- **Mode requires repetition.** When every value appears only once, Central intentionally reports **Has Mode = false**; ties among repeated values are supported.
- **Weighted Mean validates its inputs.** Weights must be a same-length **Double** array of finite, nonnegative values with at least one positive weight.
- **Floating-point rules still apply.** Very close numeric values may count as distinct modes, and sufficiently large Integer64 inputs can lose precision when converted to Double.
- **Invalid isn't the same as zero.** Empty or invalid numeric inputs can produce a default output; check **Has Value** or **Has Mode** before relying on it.

For exact details, see [Supported Data Types](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fsupported-types%2FDESIGN.md), [Validity & Edge Cases](https://mippi-the-dork.github.io/Central/?page=03-types-and-pins%2Fvalidity-and-edge-cases%2FDESIGN.md) and [Troubleshooting](https://mippi-the-dork.github.io/Central/?page=05-support%2Ftroubleshooting%2FDESIGN.md).

## What's next?

Central v1.0.0 established the four core statistics nodes, type-aware Blueprint inputs, validity outputs and separation between editor authoring and runtime calculations.

**No future version or specific feature set has been announced.** Suggestions for additional operations or supported types can be discussed through GitHub Issues; they aren't included in v1.0.0 unless shipped in a later release.

[**View the Central Roadmap →**](https://mippi-the-dork.github.io/Central/?page=ROADMAP.md)

## Issues, feature requests and contributions

Found a bug? Please [open an issue](https://github.com/mippi-the-dork/Central/issues) with your Central/Unreal versions, input array type, sample values or weights, expected result, and Blueprint compiler messages or screenshots where helpful.

Have an idea? [Submit a feature request](https://github.com/mippi-the-dork/Central/issues) describing the gameplay or authoring problem, the operation or type that would help, and what should happen with empty or invalid input.

**Pull requests are welcome.** For major changes, open an issue first so the intended scope can be discussed. Central aims to remain compact, type-safe and natural to Unreal's Blueprint workflow.

## License

Central is distributed under the **MIT License**. See [LICENSE](LICENSE) for the full terms.

---

**Central is created by Mippi the Dork.**

**[Explore the Documentation](https://mippi-the-dork.github.io/Central/)** · **[Get Central](https://github.com/mippi-the-dork/Central/releases)** · **[Report an Issue](https://github.com/mippi-the-dork/Central/issues)**
