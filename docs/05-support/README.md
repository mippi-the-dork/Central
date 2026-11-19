# 05. Support

**Central v1.0.0 · Blueprint statistics for Unreal Engine**

Central's most common support questions involve **unconnected wildcard arrays**, unsupported type connections, a default output that looks like a valid result, or Mode correctly reporting **no mode** when every input occurs only once.

## Start here
If a graph fails to compile, confirm that **Values** is connected to a compatible array, that **Weights** is a Double array for Weighted Mean and that downstream output connections still match the input element type.

If the node returns zero or an empty Modes array, inspect the validity output before deciding the calculation failed. For saved graphs, reconnect changed-type pins and recompile.

## Contact and diagnostics
Use [Central Issues](https://github.com/mippi-the-dork/Central/issues). Include exact Unreal and Central versions, a screenshot of the Blueprint graph, input array element type, sample data, the compiler message and whether the problem survives reopening the Blueprint.

## Topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Frequently Asked Questions** | Common questions about modes, types, validity and editor behavior | [Design](faq/DESIGN.md) | [Technical](faq/TECHNICAL.md) |
| **Troubleshooting** | Compile errors, unavailable pins, unexpected values and invalid results | [Design](troubleshooting/DESIGN.md) | [Technical](troubleshooting/TECHNICAL.md) |
| **Updating & Support** | Source and precompiled updates, compatibility and reporting issues | [Design](updating/DESIGN.md) | [Technical](updating/TECHNICAL.md) |

For detailed implementation, use the companion Technical page for each topic.
