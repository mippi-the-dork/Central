# Installation & Compatibility — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Before installing

Central v1.0.0 targets **Unreal Engine 5.8.x**. It includes both Runtime and Editor C++ modules. You can use a compatible precompiled release if available, or build the source in a C++-capable project.

## Project installation from source

1. Close Unreal Editor.
2. Place the complete Central plugin directory in `YourProject/Plugins/Central/`.
3. Verify that `Central.uplugin`, `Source/Central` and `Source/CentralEditor` are inside that same directory.
4. Generate project files if needed and compile the project's **Development Editor** target with your UE 5.8 toolchain.
5. Reopen the project. In **Edit → Plugins**, enable Central if it is disabled, then restart if prompted.
6. Open a Blueprint graph, right-click, and search for **Mean Value**, **Median Value**, **Mode Value**, or **Weighted Mean Value**.

## Precompiled distribution

When using a precompiled package, select the package built for your engine and platform. Replace the old plugin folder *as a complete unit* while Unreal is closed. Do not mix binaries from one release with C++ files from another.

## Engine-wide alternative

You can install into an engine `Engine/Plugins` directory instead of the project. Per-project installation is easier to track with a particular game and source-control branch.

## Common first-launch problems

If the nodes do not appear, check the plugin is enabled, the Editor build succeeded, and the project uses a compatible UE version. Look under **Math → Statistics**, not Central's internal runtime function category. A Blueprint action search may need to run after the editor has finished registering actions.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)
