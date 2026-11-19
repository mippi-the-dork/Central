# Central v1.0.0 Verification Matrix

**Source review completed; the following tests are not reported as passing.** Execute them in a compatible UE 5.8 Editor project and record the exact version/build, Central commit or release, date, log and observations.

| ID | Test | Expected result | Status |
| --- | --- | --- | --- |
| CEN-01 | Enable Central in a fresh UE 5.8 project | Both Runtime and Editor modules load | Not run |
| CEN-02 | Search Blueprint action menu | Four nodes appear under Math → Statistics | Not run |
| CEN-03 | Connect Int/Int64/Byte Values to Mean/Median/Weighted Mean | Outputs resolve to Double | Not run |
| CEN-04 | Connect Float, Double, Vector2D, Vector, Vector4 and Linear Color arrays | Eligible results resolve and compile | Not run |
| CEN-05 | Connect unsupported Values types | Clear connection/compiler rejection | Not run |
| CEN-06 | Use [1,2,3,4] with Mean/Median | Results 2.5; Has Value true | Not run |
| CEN-07 | Verify Median input order after evaluation | Original Values order unchanged | Not run |
| CEN-08 | Mode on [2,2,3,3,4] | Modes [2,3], Value 2, Frequency 2 | Not run |
| CEN-09 | Mode on [1,2,3] and [] | Has Mode false, Frequency 1 and 0 respectively | Not run |
| CEN-10 | Mode on native and Blueprint byte-backed enums | Output Value/Modes preserve correct enum pin type | Not run |
| CEN-11 | Mode on String, Name, Boolean and Rotator arrays | Correct eligible typed outputs and frequency behavior | Not run |
| CEN-12 | Weighted Mean [10,20] / [1,3] | Result 17.5, Has Value true | Not run |
| CEN-13 | Invalid/mismatched/zero-only/negative/non-finite weights | Has Value false | Not run |
| CEN-14 | Empty or non-finite input data | Invalid result and safe default output | Not run |
| CEN-15 | Change array type, reconstruct pins, split struct outputs | Graph updates compatible links and reports incompatibilities | Not run |
| CEN-16 | Save/reopen/duplicate/copy-paste typed nodes | Pin types and compiled behavior remain correct | Not run |
| CEN-17 | Execute `Automation RunTests Central` | `Central.Runtime.BasicStatistics` succeeds | Not run |
| CEN-18 | Package project with Central nodes | Runtime calculations execute without CentralEditor | Not run |
| DOC-01 | Load GitHub Pages homepage and all five overviews | Site and links load correctly | Not run |
| DOC-02 | Open all 34 topic pages; toggle Design/Technical | Navigation and pairing are correct | Static link audit only |
| DOC-03 | Search title and body-only term | Full-text search returns relevant excerpt | Not run |
| DOC-04 | Check desktop, tablet, 320–400px mobile | Navigation, figures, tables and TOC remain usable | Not run |
| DOC-05 | Check screenshots/GIF placeholders and media captions | Assets fit article and show clear instructions | Static asset audit only |
| DOC-06 | Test keyboard nav, focus indicators and browser history | No keyboard or history regressions | Not run |

## Reporting

Use **Passed**, **Failed**, **Blocked** or **Not applicable** only after execution; attach evidence. “Static audit” or “source reviewed” must not be promoted to passed editor/browser testing.

The native runtime test is declared in [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp). It does not itself verify all K2 connection, reload, copying or packaging scenarios.

[Testing guide](04-implementation-and-testing/verification/DESIGN.md) · [Roadmap](ROADMAP.md)
