// Copyright Mippithedork 2026, Inc. All Rights Reserved.

#include "CentralBPLibrary.h"

#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include <limits>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCentralStatisticsTest,
    "Central.Runtime.BasicStatistics",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCentralStatisticsTest::RunTest(const FString& Parameters)
{
    bool bHasValue = false;
    double NumericValue = 0.0;
    UCentralBPLibrary::MeanInt(TArray<int32>{ 1, 2, 3, 4 }, NumericValue, bHasValue);
    TestTrue(TEXT("Mean produces a value"), bHasValue);
    TestEqual(TEXT("Mean of [1,2,3,4]"), NumericValue, 2.5);

    UCentralBPLibrary::MedianInt(TArray<int32>{ 1, 2, 3, 4 }, NumericValue, bHasValue);
    TestTrue(TEXT("Even median produces a value"), bHasValue);
    TestEqual(TEXT("Even integer median retains fractions"), NumericValue, 2.5);

    int32 ModeValue = 0;
    int32 Frequency = 0;
    TArray<int32> Modes;
    bool bHasMode = false;
    UCentralBPLibrary::ModeInt(TArray<int32>{ 2, 2, 3, 3, 4 }, ModeValue, Modes, Frequency, bHasMode);
    TestTrue(TEXT("Bimodal mode exists"), bHasMode);
    TestEqual(TEXT("First tied mode"), ModeValue, 2);
    TestEqual(TEXT("Two modes"), Modes.Num(), 2);
    TestEqual(TEXT("Mode frequency"), Frequency, 2);

    UCentralBPLibrary::ModeInt(TArray<int32>{ 1, 2, 3 }, ModeValue, Modes, Frequency, bHasMode);
    TestFalse(TEXT("All unique means no mode"), bHasMode);
    TestTrue(TEXT("No modes returned"), Modes.IsEmpty());

    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ 1.0, 3.0 }, NumericValue, bHasValue);
    TestTrue(TEXT("Valid weighted mean"), bHasValue);
    TestEqual(TEXT("Weighted mean result"), NumericValue, 17.5);

    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ 1.0 }, NumericValue, bHasValue);
    TestFalse(TEXT("Mismatched array lengths"), bHasValue);
    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ -1.0, 2.0 }, NumericValue, bHasValue);
    TestFalse(TEXT("Negative weight"), bHasValue);
    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ 0.0, 0.0 }, NumericValue, bHasValue);
    TestFalse(TEXT("Zero total weight"), bHasValue);

    // Empty arrays must never claim they produced a statistic.
    UCentralBPLibrary::MeanInt(TArray<int32>{}, NumericValue, bHasValue);
    TestFalse(TEXT("Empty mean has no value"), bHasValue);
    UCentralBPLibrary::MedianInt(TArray<int32>{}, NumericValue, bHasValue);
    TestFalse(TEXT("Empty median has no value"), bHasValue);

    UCentralBPLibrary::ModeInt(TArray<int32>{}, ModeValue, Modes, Frequency, bHasMode);
    TestFalse(TEXT("Empty mode has no value"), bHasMode);
    TestEqual(TEXT("Empty mode frequency is zero"), Frequency, 0);
    TestTrue(TEXT("Empty mode list"), Modes.IsEmpty());

    UCentralBPLibrary::ModeInt(TArray<int32>{ 7, 7, 8, 8, 9, 9 }, ModeValue, Modes, Frequency, bHasMode);
    TestTrue(TEXT("Three-way mode exists"), bHasMode);
    TestEqual(TEXT("Three-way mode count"), Modes.Num(), 3);
    TestEqual(TEXT("First encounter determines primary mode"), ModeValue, 7);
    TestEqual(TEXT("Three-way mode frequency"), Frequency, 2);

    UCentralBPLibrary::MedianInt(TArray<int32>{ 7, 1, 3 }, NumericValue, bHasValue);
    TestTrue(TEXT("Odd median valid"), bHasValue);
    TestEqual(TEXT("Odd median sorts a copy"), NumericValue, 3.0);

    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ 0.0, 5.0 }, NumericValue, bHasValue);
    TestTrue(TEXT("Zero individual weight permitted"), bHasValue);
    TestEqual(TEXT("Zero-weight value excluded"), NumericValue, 20.0);

    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{}, TArray<double>{}, NumericValue, bHasValue);
    TestFalse(TEXT("Empty weighted mean invalid"), bHasValue);

    // Hash maps must treat positive and negative floating-point zero as the same key.
    float FloatMode = 1.0f;
    TArray<float> FloatModes;
    UCentralBPLibrary::ModeFloat(TArray<float>{ -0.0f, 0.0f, 9.0f }, FloatMode, FloatModes, Frequency, bHasMode);
    TestTrue(TEXT("Signed zero forms a repeated floating-point mode"), bHasMode);
    TestEqual(TEXT("Signed zero frequency"), Frequency, 2);
    TestEqual(TEXT("Signed zero single modal value"), FloatModes.Num(), 1);

    // Two different statistical outcomes may share the same numerical default.
    UCentralBPLibrary::MeanInt(TArray<int32>{ -1, 1 }, NumericValue, bHasValue);
    TestTrue(TEXT("A valid zero mean is distinguishable from invalid input"), bHasValue);
    TestEqual(TEXT("Valid zero mean"), NumericValue, 0.0);

    FString StringMode;
    TArray<FString> StringModes;
    UCentralBPLibrary::ModeString(TArray<FString>{ TEXT("B"), TEXT("A"), TEXT("A"), TEXT("B") },
        StringMode, StringModes, Frequency, bHasMode);
    TestTrue(TEXT("String ties are valid"), bHasMode);
    TestEqual(TEXT("String tie first-seen result"), StringMode, FString(TEXT("B")));
    TestEqual(TEXT("String tie count"), StringModes.Num(), 2);

    // Complex structures use component-based hashing with canonical signed zeros.
    FVector VectorMode;
    TArray<FVector> VectorModes;
    UCentralBPLibrary::ModeVector(TArray<FVector>{ FVector(-0.0, 2.0, 3.0),
        FVector(0.0, 2.0, 3.0), FVector(4.0, 5.0, 6.0) },
        VectorMode, VectorModes, Frequency, bHasMode);
    TestTrue(TEXT("Vector mode hashes signed zero consistently"), bHasMode);
    TestEqual(TEXT("Vector mode frequency"), Frequency, 2);
    TestEqual(TEXT("Vector mode list length"), VectorModes.Num(), 1);

    // Reordered inputs must not be mutated by median calculations.
    TArray<int32> Unsorted{ 9, 1, 5, 3 };
    UCentralBPLibrary::MedianInt(Unsorted, NumericValue, bHasValue);
    TestTrue(TEXT("Median of reordered data valid"), bHasValue);
    TestEqual(TEXT("Median of reordered data"), NumericValue, 4.0);
    TestEqual(TEXT("Median does not alter source array"), Unsorted[0], 9);

    UCentralBPLibrary::ModeInt(TArray<int32>{ 12, 13, 14, 15 }, ModeValue, Modes, Frequency, bHasMode);
    TestFalse(TEXT("Single occurrences do not constitute a mode"), bHasMode);
    TestEqual(TEXT("No mode still exposes maximum frequency"), Frequency, 1);
    TestEqual(TEXT("No mode returns zero default"), ModeValue, 0);

    // Invalid floating-point input must be rejected, not silently ignored.
    float MeanFloatResult = 0.0f;
    const float Infinity = std::numeric_limits<float>::infinity();
    UCentralBPLibrary::MeanFloat(TArray<float>{ 1.0f, Infinity }, MeanFloatResult, bHasValue);
    TestFalse(TEXT("Infinite mean input invalid"), bHasValue);
    UCentralBPLibrary::ModeFloat(TArray<float>{ 1.0f, 1.0f, Infinity }, FloatMode, FloatModes, Frequency, bHasMode);
    TestFalse(TEXT("Infinite mode input invalid"), bHasMode);
    TestTrue(TEXT("Invalid mode has no modes"), FloatModes.IsEmpty());
    TestEqual(TEXT("Invalid mode frequency zero"), Frequency, 0);

    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 10, 20 }, TArray<double>{ Infinity, 1.0 }, NumericValue, bHasValue);
    TestFalse(TEXT("Infinite weight invalid"), bHasValue);
    UCentralBPLibrary::WeightedMeanInt(TArray<int32>{ 5, 10, 15 }, TArray<double>{ 0.0, 0.0, 1.0 }, NumericValue, bHasValue);
    TestTrue(TEXT("Single contributing positive weight valid"), bHasValue);
    TestEqual(TEXT("Weighted mean ignores zero weights"), NumericValue, 15.0);

    return true;
}
#endif
