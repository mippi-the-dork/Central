# Updating & Support — Design

**Central v1.0.0 · Source-grounded documentation**

## Update a precompiled plugin

1. Close Unreal Editor and your active build process.
2. Download a package matching your engine version and target platform.
3. Replace the **complete Central plugin folder** under `YourProject/Plugins/Central` rather than mixing files from separate versions.
4. Reopen the project, confirm Central is enabled, and compile one Blueprint containing each node.
5. Reopen a previously saved Blueprint with typed Central nodes and check its connections.

## Update a source checkout

<!-- Media target: Image | central-update | docs/assets/media/central-update.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-update">
  <img src="../../assets/media-placeholder.svg" alt="The Central plugin directory contains its runtime and editor modules." loading="lazy">
  <figcaption>The Central plugin directory contains its runtime and editor modules.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture YourProject/Plugins/Central in File Explorer with Central.uplugin and both Source/Central and Source/CentralEditor folders.</span></figcaption>
</figure>


Pull the release/tag intended for your project, regenerate project files if necessary, rebuild the Development Editor target, and restart the editor. A project installed from source requires a working C++ toolchain.

## Compatibility

Central **v1.0.0** is documented for **Unreal Engine 5.8.x**. It has separate Runtime and Editor modules. The descriptor does not prove additional platforms or engine versions, even if they may compile.

## Getting support

Use [GitHub Issues](https://github.com/mippi-the-dork/Central/issues). Provide exact UE and Central versions, installation source, array element type, sample Values/Weights, observed outputs, compiler errors and relevant Output Log sections.

## Suggesting future features

Describe the gameplay/statistics problem first: why a new statistic or supported type would help, what result should mean for empty/mixed input, and whether it should be usable at runtime. Proposed future features are **not shipped** until documented in a release.

## What about existing Blueprint graphs?

Central reconstructs supported pins using Unreal's graph serialization and reconstruction hooks. Always verify saved graphs when changing plugin versions, especially if input types, split pins or connected outputs change.

---

[Technical implementation](TECHNICAL.md) · [Documentation home](../../README.md)
