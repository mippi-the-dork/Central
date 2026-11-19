# Validity & Edge Cases — Technical

**Central v1.0.0 · Type and graph behavior**

## Runtime validity flags

The typed methods compute the return value and set `bHasValue` or `bHasMode`. They return defaults on invalid input, deliberately separating output payload from output validity.

## Finite checks

`CentralPrivate::Finite<T>` specializes for float/double and the supported mathematical struct types. The Mode implementation rejects non-finite numeric categories rather than attempting to use NaN as a hash key.

## Weighted constraints

`ValidateWeights` requires nonempty matching lengths, nonnegative finite weights, and a positive total contribution. A zero-weight item does not exempt its Values entry from finite-value validation.

## Mode's no-mode rule

`Mode<T>` counts frequencies, retains the maximum even if it is 1, then only fills Modes/Value as a valid result when an item repeats. The empty array has maximum frequency 0.

## Precision boundaries

The Integer64-to-Double conversion can round sufficiently large integers. Floating-point accumulation follows the native arithmetic of the typed helper. Signed floating-point zero is canonicalized as a Mode key. This is not a statistical error-estimation library.

## Testing evidence

The source includes explicit automation assertions for an empty mean/median, a valid zero mean, all-unique Mode, empty Mode frequency, signed-zero Mode, invalid infinity inputs, mismatched and negative weight arrays, zero weights and tied modes. The presence of these assertions is not proof of a successful test run in a particular editor build.

## Source references

- [K2Node_Central.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/CentralEditor/Private/K2Node_Central.cpp)
- [CentralBPLibrary.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/CentralBPLibrary.cpp)
- [CentralStatisticsTests.cpp](https://github.com/mippi-the-dork/Central/blob/main/Source/Central/Private/Tests/CentralStatisticsTests.cpp)

[Design guide](DESIGN.md) · Source-reviewed, not a claim of live editor QA.
