# Maintaining Central Documentation

## Scope and source of truth

This manual describes Central v1.0.0 as implemented in the public C++ source. The README is a useful overview, but the K2 node source and runtime implementations determine the exact supported pin types, behavior, and limitations.

The site follows the established Mippi documentation layout while using Central-specific terminology. **Do not copy Focus feature categories into Central.**

## Pair responsibilities

Each feature has two independently useful pages:
- **Design:** What the node/feature does, where to find it, user steps, pin examples, expected results, errors, and limitations.
- **Technical:** `UK2Node_Central` behavior, native UFUNCTIONs, input validation, array handling, complexity, implementation details and editor/runtime contracts.

Avoid filling both pages with the same explanatory material. Update the relevant pair when behavior changes.

## Visuals and capture instructions

The [Media Inventory](MEDIA_INVENTORY.md) and `assets/media-slots.json` assign static or animated capture needs, exact asset filenames, captions and detailed capture instructions. The second caption line is intentionally visible during authoring; it should be removed when all genuine assets replace placeholders if a public-facing instruction line is no longer desired.

Never invent a screenshot of a running Unreal Editor. The current site uses a neutral placeholder where genuine artwork/recordings have not been supplied. Keep the user-facing caption accurate when replacing an asset.

## Updating a release

1. Inspect the source revision and all changes to runtime types/K2 pin rules.
2. Update the Design/Technical topics, supported type matrix and examples.
3. Update `site-manifest.json` and the homepage version baseline.
4. Update the [Roadmap](ROADMAP.md) with confirmed historical and planned features, without inventing feature promises.
5. Test local Markdown links, search, media, desktop/mobile and browser history.
6. Run the native automation and appropriate Blueprint/package tests; record **actual** results in [Verification Matrix](VERIFICATION_MATRIX.md).

## GitHub Pages

Publish from **main → /docs** in repository Settings → Pages. The intended URL is https://mippi-the-dork.github.io/Central/ . The repository merge and live Pages deployment are separate conditions.
