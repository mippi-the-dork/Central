// Copyright Mippithedork 2026, Inc. All Rights Reserved.

#include "CentralBPLibrary.h"
#include "Algo/Sort.h"
#include <cmath>
#include <type_traits>
#include "UObject/Stack.h"
#include "UObject/UnrealType.h"

namespace CentralPrivate
{
    template<typename T>
    bool Finite(const T& V) { return true; }
    template<> bool Finite<float>(const float& V) { return FMath::IsFinite(V); }
    template<> bool Finite<double>(const double& V) { return FMath::IsFinite(V); }
    template<> bool Finite<FVector>(const FVector& V) { return !V.ContainsNaN() && FMath::IsFinite(V.X) && FMath::IsFinite(V.Y) && FMath::IsFinite(V.Z); }
    template<> bool Finite<FVector2D>(const FVector2D& V) { return FMath::IsFinite(V.X) && FMath::IsFinite(V.Y); }
    template<> bool Finite<FVector4>(const FVector4& V) { return FMath::IsFinite(V.X) && FMath::IsFinite(V.Y) && FMath::IsFinite(V.Z) && FMath::IsFinite(V.W); }
    template<> bool Finite<FLinearColor>(const FLinearColor& V) { return FMath::IsFinite(V.R) && FMath::IsFinite(V.G) && FMath::IsFinite(V.B) && FMath::IsFinite(V.A); }
    template<> bool Finite<FRotator>(const FRotator& V) { return !V.ContainsNaN(); }

    template<typename T> bool OrderedLess(const T& A, const T& B) { return A < B; }

    template<typename T> T ComponentAverage(const T& A, const T& B) { return A + (B - A) / static_cast<T>(2); }
    template<> FVector ComponentAverage(const FVector& A, const FVector& B) { return (A + B) * 0.5; }
    template<> FVector2D ComponentAverage(const FVector2D& A, const FVector2D& B) { return (A + B) * 0.5; }
    template<> FVector4 ComponentAverage(const FVector4& A, const FVector4& B) { return (A + B) * 0.5; }
    template<> FLinearColor ComponentAverage(const FLinearColor& A, const FLinearColor& B) { return (A + B) * 0.5f; }

    template<typename T> T Mean(const TArray<T>& Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return T{};
        T Result{};
        const double Weight = 1.0 / static_cast<double>(Values.Num());
        for (const T& Value : Values)
        {
            if (!Finite(Value)) return T{};
            Result += Value * Weight;
        }
        bValid = Finite(Result);
        return bValid ? Result : T{};
    }
    template<typename T> double NumericMean(const TArray<T>& Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return 0.0;
        double Sum = 0.0;
        for (const T& Value : Values)
        {
            if (!Finite(Value)) return 0.0;
            Sum += static_cast<double>(Value) / static_cast<double>(Values.Num());
        }
        bValid = FMath::IsFinite(Sum);
        return bValid ? Sum : 0.0;
    }

    // Normalize weights before accumulating. This avoids integer overflow and
    // reduces intermediate floating-point overflow for very large weights.
    template<typename T>
    bool ValidateWeights(const TArray<T>& Values, const TArray<double>& Weights, double& TotalWeight)
    {
        TotalWeight = 0.0;
        if (Values.IsEmpty() || Values.Num() != Weights.Num()) return false;
        double MaxWeight = 0.0;
        for (int32 I = 0; I < Weights.Num(); ++I)
        {
            if (!Finite(Values[I]) || !FMath::IsFinite(Weights[I]) || Weights[I] < 0.0) return false;
            MaxWeight = FMath::Max(MaxWeight, Weights[I]);
        }
        if (MaxWeight <= 0.0) return false;
        // TotalWeight stores scaled weights, so summing cannot overflow with
        // ordinary Unreal TArray limits.
        for (double Weight : Weights) TotalWeight += Weight / MaxWeight;
        return FMath::IsFinite(TotalWeight) && TotalWeight > 0.0;
    }

    template<typename T>
    T WeightedMean(const TArray<T>& Values, const TArray<double>& Weights, bool& bValid)
    {
        bValid = false;
        double TotalWeight = 0.0;
        if (!ValidateWeights(Values, Weights, TotalWeight)) return T{};
        double MaxWeight = 0.0;
        for (double Weight : Weights) MaxWeight = FMath::Max(MaxWeight, Weight);
        T Result{};
        for (int32 I = 0; I < Values.Num(); ++I)
        {
            const double Normalized = (Weights[I] / MaxWeight) / TotalWeight;
            Result += Values[I] * Normalized;
        }
        bValid = Finite(Result);
        return bValid ? Result : T{};
    }
    template<typename T>
    double WeightedNumericMean(const TArray<T>& Values, const TArray<double>& Weights, bool& bValid)
    {
        bValid = false;
        double TotalWeight = 0.0;
        if (!ValidateWeights(Values, Weights, TotalWeight)) return 0.0;
        double MaxWeight = 0.0;
        for (double Weight : Weights) MaxWeight = FMath::Max(MaxWeight, Weight);
        double Result = 0.0;
        for (int32 I = 0; I < Values.Num(); ++I)
        {
            Result += static_cast<double>(Values[I]) * ((Weights[I] / MaxWeight) / TotalWeight);
        }
        bValid = FMath::IsFinite(Result);
        return bValid ? Result : 0.0;
    }

    template<typename T> T Median(TArray<T> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return T{};
        for (const T& Value : Values) { if (!Finite(Value)) return T{}; }
        Values.Sort([](const T& A, const T& B){ return OrderedLess(A, B); });
        const int32 Middle = Values.Num() / 2;
        const T Result = Values.Num() % 2 ? Values[Middle] : ComponentAverage(Values[Middle - 1], Values[Middle]);
        bValid = Finite(Result);
        return bValid ? Result : T{};
    }
    template<typename T> double NumericMedian(TArray<T> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return 0.0;
        for (const T& Value : Values) { if (!Finite(Value)) return 0.0; }
        Values.Sort();
        const int32 Middle = Values.Num() / 2;
        bValid = true;
        return Values.Num() % 2 ? static_cast<double>(Values[Middle]) :
            static_cast<double>(Values[Middle - 1]) * 0.5 + static_cast<double>(Values[Middle]) * 0.5;
    }
    // Normalize signed floating-point zero before using values as TMap keys.
    // -0 and +0 compare equal and must map to the same frequency bucket.
    template<typename T> T CanonicalModeKey(const T& Value) { return Value; }
    template<> float CanonicalModeKey<float>(const float& Value) { return Value == 0.0f ? 0.0f : Value; }
    template<> double CanonicalModeKey<double>(const double& Value) { return Value == 0.0 ? 0.0 : Value; }

    // Hash based on exact finite numeric components. Signed zero is canonicalized,
    // matching floating-point equality. This avoids hashing struct padding and
    // does not depend on FVector/Color GetTypeHash overload availability.
    struct FComponentKey
    {
        uint64 Bits[4] = { 0, 0, 0, 0 };
        bool operator==(const FComponentKey& Other) const
        {
            for (int32 I = 0; I < 4; ++I)
            {
                if (Bits[I] != Other.Bits[I]) return false;
            }
            return true;
        }
        friend uint32 GetTypeHash(const FComponentKey& Key)
        {
            uint32 Hash = 0;
            for (uint64 Part : Key.Bits) Hash = HashCombine(Hash, ::GetTypeHash(Part));
            return Hash;
        }
    };
    static uint64 ComponentBits(double Component)
    {
        if (Component == 0.0) return 0;
        uint64 Bits = 0;
        FMemory::Memcpy(&Bits, &Component, sizeof(Bits));
        return Bits;
    }
    static FComponentKey MakeComponentKey(const FVector2D& V)
    { FComponentKey K; K.Bits[0] = ComponentBits(V.X); K.Bits[1] = ComponentBits(V.Y); return K; }
    static FComponentKey MakeComponentKey(const FVector& V)
    { FComponentKey K; K.Bits[0] = ComponentBits(V.X); K.Bits[1] = ComponentBits(V.Y); K.Bits[2] = ComponentBits(V.Z); return K; }
    static FComponentKey MakeComponentKey(const FVector4& V)
    { FComponentKey K; K.Bits[0] = ComponentBits(V.X); K.Bits[1] = ComponentBits(V.Y); K.Bits[2] = ComponentBits(V.Z); K.Bits[3] = ComponentBits(V.W); return K; }
    static FComponentKey MakeComponentKey(const FLinearColor& V)
    { FComponentKey K; K.Bits[0] = ComponentBits(V.R); K.Bits[1] = ComponentBits(V.G); K.Bits[2] = ComponentBits(V.B); K.Bits[3] = ComponentBits(V.A); return K; }
    static FComponentKey MakeComponentKey(const FRotator& V)
    { FComponentKey K; K.Bits[0] = ComponentBits(V.Pitch); K.Bits[1] = ComponentBits(V.Yaw); K.Bits[2] = ComponentBits(V.Roll); return K; }

    template<typename T> void Mode(const TArray<T>& Values, T& First, TArray<T>& All, int32& Count, bool& bValid)
    {
        First = T{}; All.Reset(); Count = 0; bValid = false;
        TArray<T> Unique;
        TArray<int32> Frequencies;
        Unique.Reserve(Values.Num());
        Frequencies.Reserve(Values.Num());
        if constexpr (std::is_same_v<T, FVector2D> || std::is_same_v<T, FVector> ||
                      std::is_same_v<T, FVector4> || std::is_same_v<T, FLinearColor> ||
                      std::is_same_v<T, FRotator>)
        {
            TMap<FComponentKey, int32> Indices;
            Indices.Reserve(Values.Num());
            for (const T& Value : Values)
            {
                if (!Finite(Value)) { Count = 0; return; }
                const FComponentKey Key = MakeComponentKey(Value);
                if (const int32* Existing = Indices.Find(Key)) ++Frequencies[*Existing];
                else { const int32 Index = Unique.Add(Value); Indices.Add(Key, Index); Frequencies.Add(1); }
            }
        }
        else
        {
            TMap<T, int32> Indices;
            Indices.Reserve(Values.Num());
            for (const T& Value : Values)
            {
                if (!Finite(Value)) { Count = 0; return; }
                const T Key = CanonicalModeKey(Value);
                if (const int32* Existing = Indices.Find(Key)) ++Frequencies[*Existing];
                else { const int32 Index = Unique.Add(Value); Indices.Add(Key, Index); Frequencies.Add(1); }
            }
        }
        for (int32 Frequency : Frequencies) Count = FMath::Max(Count, Frequency);
        if (Count <= 1) { Count = Values.IsEmpty() ? 0 : 1; return; }
        for (int32 I = 0; I < Unique.Num(); ++I)
            if (Frequencies[I] == Count) All.Add(Unique[I]);
        bValid = !All.IsEmpty();
        if (bValid) First = All[0];
    }

    template<> FVector2D Median<FVector2D>(TArray<FVector2D> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return FVector2D{};
        for (const auto& Value : Values) { if (!Finite(Value)) return FVector2D{}; }
        FVector2D Result{};
        TArray<double> ComponentsX;
        for (const auto& Value : Values) ComponentsX.Add(Value.X);
        bool bComponentX = false;
        Result.X = NumericMedian(MoveTemp(ComponentsX), bComponentX);
        TArray<double> ComponentsY;
        for (const auto& Value : Values) ComponentsY.Add(Value.Y);
        bool bComponentY = false;
        Result.Y = NumericMedian(MoveTemp(ComponentsY), bComponentY);
        bValid = bComponentX && bComponentY;
        return bValid ? Result : FVector2D{};
    }
    template<> FVector Median<FVector>(TArray<FVector> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return FVector{};
        for (const auto& Value : Values) { if (!Finite(Value)) return FVector{}; }
        FVector Result{};
        TArray<double> ComponentsX;
        for (const auto& Value : Values) ComponentsX.Add(Value.X);
        bool bComponentX = false;
        Result.X = NumericMedian(MoveTemp(ComponentsX), bComponentX);
        TArray<double> ComponentsY;
        for (const auto& Value : Values) ComponentsY.Add(Value.Y);
        bool bComponentY = false;
        Result.Y = NumericMedian(MoveTemp(ComponentsY), bComponentY);
        TArray<double> ComponentsZ;
        for (const auto& Value : Values) ComponentsZ.Add(Value.Z);
        bool bComponentZ = false;
        Result.Z = NumericMedian(MoveTemp(ComponentsZ), bComponentZ);
        bValid = bComponentX && bComponentY && bComponentZ;
        return bValid ? Result : FVector{};
    }
    template<> FVector4 Median<FVector4>(TArray<FVector4> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return FVector4{};
        for (const auto& Value : Values) { if (!Finite(Value)) return FVector4{}; }
        FVector4 Result{};
        TArray<double> ComponentsX;
        for (const auto& Value : Values) ComponentsX.Add(Value.X);
        bool bComponentX = false;
        Result.X = NumericMedian(MoveTemp(ComponentsX), bComponentX);
        TArray<double> ComponentsY;
        for (const auto& Value : Values) ComponentsY.Add(Value.Y);
        bool bComponentY = false;
        Result.Y = NumericMedian(MoveTemp(ComponentsY), bComponentY);
        TArray<double> ComponentsZ;
        for (const auto& Value : Values) ComponentsZ.Add(Value.Z);
        bool bComponentZ = false;
        Result.Z = NumericMedian(MoveTemp(ComponentsZ), bComponentZ);
        TArray<double> ComponentsW;
        for (const auto& Value : Values) ComponentsW.Add(Value.W);
        bool bComponentW = false;
        Result.W = NumericMedian(MoveTemp(ComponentsW), bComponentW);
        bValid = bComponentX && bComponentY && bComponentZ && bComponentW;
        return bValid ? Result : FVector4{};
    }
    template<> FLinearColor Median<FLinearColor>(TArray<FLinearColor> Values, bool& bValid)
    {
        bValid = false;
        if (Values.IsEmpty()) return FLinearColor{};
        for (const auto& Value : Values) { if (!Finite(Value)) return FLinearColor{}; }
        FLinearColor Result{};
        TArray<double> ComponentsR;
        for (const auto& Value : Values) ComponentsR.Add(Value.R);
        bool bComponentR = false;
        Result.R = NumericMedian(MoveTemp(ComponentsR), bComponentR);
        TArray<double> ComponentsG;
        for (const auto& Value : Values) ComponentsG.Add(Value.G);
        bool bComponentG = false;
        Result.G = NumericMedian(MoveTemp(ComponentsG), bComponentG);
        TArray<double> ComponentsB;
        for (const auto& Value : Values) ComponentsB.Add(Value.B);
        bool bComponentB = false;
        Result.B = NumericMedian(MoveTemp(ComponentsB), bComponentB);
        TArray<double> ComponentsA;
        for (const auto& Value : Values) ComponentsA.Add(Value.A);
        bool bComponentA = false;
        Result.A = NumericMedian(MoveTemp(ComponentsA), bComponentA);
        bValid = bComponentR && bComponentG && bComponentB && bComponentA;
        return bValid ? Result : FLinearColor{};
    }
} // namespace CentralPrivate

void UCentralBPLibrary::MeanInt(const TArray<int32>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMean(Values, bHasValue); }

void UCentralBPLibrary::MeanInt64(const TArray<int64>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMean(Values, bHasValue); }

void UCentralBPLibrary::MeanByte(const TArray<uint8>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMean(Values, bHasValue); }

void UCentralBPLibrary::MeanFloat(const TArray<float>& Values, float& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MeanDouble(const TArray<double>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MeanVector2D(const TArray<FVector2D>& Values, FVector2D& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MeanVector(const TArray<FVector>& Values, FVector& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MeanVector4(const TArray<FVector4>& Values, FVector4& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MeanLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, bool& bHasValue)
{ Value = CentralPrivate::Mean(Values, bHasValue); }

void UCentralBPLibrary::MedianInt(const TArray<int32>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMedian(Values, bHasValue); }

void UCentralBPLibrary::MedianInt64(const TArray<int64>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMedian(Values, bHasValue); }

void UCentralBPLibrary::MedianByte(const TArray<uint8>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::NumericMedian(Values, bHasValue); }

void UCentralBPLibrary::MedianFloat(const TArray<float>& Values, float& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::MedianDouble(const TArray<double>& Values, double& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::MedianVector2D(const TArray<FVector2D>& Values, FVector2D& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::MedianVector(const TArray<FVector>& Values, FVector& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::MedianVector4(const TArray<FVector4>& Values, FVector4& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::MedianLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, bool& bHasValue)
{ Value = CentralPrivate::Median(Values, bHasValue); }

void UCentralBPLibrary::ModeInt(const TArray<int32>& Values, int32& Value, TArray<int32>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeInt64(const TArray<int64>& Values, int64& Value, TArray<int64>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeByte(const TArray<uint8>& Values, uint8& Value, TArray<uint8>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeFloat(const TArray<float>& Values, float& Value, TArray<float>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeDouble(const TArray<double>& Values, double& Value, TArray<double>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeVector2D(const TArray<FVector2D>& Values, FVector2D& Value, TArray<FVector2D>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeVector(const TArray<FVector>& Values, FVector& Value, TArray<FVector>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeVector4(const TArray<FVector4>& Values, FVector4& Value, TArray<FVector4>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, TArray<FLinearColor>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeRotator(const TArray<FRotator>& Values, FRotator& Value, TArray<FRotator>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeBool(const TArray<bool>& Values, bool& Value, TArray<bool>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeString(const TArray<FString>& Values, FString& Value, TArray<FString>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::ModeName(const TArray<FName>& Values, FName& Value, TArray<FName>& Modes, int32& Frequency, bool& bHasMode)
{ CentralPrivate::Mode(Values, Value, Modes, Frequency, bHasMode); }

void UCentralBPLibrary::WeightedMeanInt(const TArray<int32>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedNumericMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanInt64(const TArray<int64>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedNumericMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanByte(const TArray<uint8>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedNumericMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanFloat(const TArray<float>& Values, const TArray<double>& Weights, float& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanDouble(const TArray<double>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanVector2D(const TArray<FVector2D>& Values, const TArray<double>& Weights, FVector2D& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanVector(const TArray<FVector>& Values, const TArray<double>& Weights, FVector& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanVector4(const TArray<FVector4>& Values, const TArray<double>& Weights, FVector4& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

void UCentralBPLibrary::WeightedMeanLinearColor(const TArray<FLinearColor>& Values, const TArray<double>& Weights, FLinearColor& Value, bool& bHasValue)
{ Value = CentralPrivate::WeightedMean(Values, Weights, bHasValue); }

// The editor node sets enum-specific pin types on this internal wildcard thunk.
// The Blueprint VM supplies the real element property, which may be a byte enum
// or an FEnumProperty with a different underlying integer width.
void UCentralBPLibrary::ModeEnum(const TArray<uint8>& Values, uint8& Value,
    TArray<uint8>& Modes, int32& Frequency, bool& bHasMode)
{
    Value = 0;
    Modes.Reset();
    Frequency = 0;
    bHasMode = false;
}

DEFINE_FUNCTION(UCentralBPLibrary::execModeEnum)
{
    Stack.MostRecentProperty = nullptr;
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.StepCompiledIn<FArrayProperty>(nullptr);
    const FArrayProperty* InputProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
    void* InputAddress = Stack.MostRecentPropertyAddress;

    Stack.MostRecentProperty = nullptr;
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.StepCompiledIn<FProperty>(nullptr);
    const FProperty* ScalarProperty = Stack.MostRecentProperty;
    void* ScalarAddress = Stack.MostRecentPropertyAddress;

    Stack.MostRecentProperty = nullptr;
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.StepCompiledIn<FArrayProperty>(nullptr);
    const FArrayProperty* ModesProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
    void* ModesAddress = Stack.MostRecentPropertyAddress;

    P_GET_PROPERTY(FIntProperty, Frequency);
    P_GET_UBOOL(bHasMode);
    P_FINISH;
    P_NATIVE_BEGIN;

    Frequency = 0;
    bHasMode = false;
    if (ScalarProperty && ScalarAddress) ScalarProperty->ClearValue(ScalarAddress);
    if (ModesProperty && ModesAddress)
    {
        FScriptArrayHelper ModesHelper(ModesProperty, ModesAddress);
        ModesHelper.EmptyValues();
    }
    if (InputProperty && InputAddress && ScalarProperty && ScalarAddress &&
        ModesProperty && ModesAddress && InputProperty->Inner &&
        InputProperty->Inner->SameType(ScalarProperty) &&
        ModesProperty->Inner && InputProperty->Inner->SameType(ModesProperty->Inner))
    {
        const FProperty* Inner = InputProperty->Inner;
        const bool bEnumType = CastField<FEnumProperty>(Inner) ||
            (CastField<FByteProperty>(Inner) && CastField<FByteProperty>(Inner)->Enum);
        if (bEnumType)
        {
            FScriptArrayHelper Array(InputProperty, InputAddress);
            FScriptArrayHelper Result(ModesProperty, ModesAddress);
            TArray<int32> UniqueIndices;
            TArray<int32> Counts;
            TMap<int64, int32> Seen;
            Seen.Reserve(Array.Num());
            const FNumericProperty* Numeric = CastField<FNumericProperty>(Inner);
            const FNumericProperty* NumericInner = CastField<FEnumProperty>(Inner)
                ? CastField<FEnumProperty>(Inner)->GetUnderlyingProperty() : Numeric;
            if (NumericInner)
            {
                for (int32 Index = 0; Index < Array.Num(); ++Index)
                {
                    const void* Raw = Array.GetRawPtr(Index);
                    const int64 Key = CastField<FByteProperty>(NumericInner)
                        ? static_cast<int64>(NumericInner->GetUnsignedIntPropertyValue(Raw))
                        : NumericInner->GetSignedIntPropertyValue(Raw);
                    if (const int32* Existing = Seen.Find(Key)) ++Counts[*Existing];
                    else { int32 NewIndex = UniqueIndices.Add(Index); Seen.Add(Key, NewIndex); Counts.Add(1); }
                }
                for (int32 Count : Counts) Frequency = FMath::Max(Frequency, Count);
                if (Frequency > 1)
                {
                    for (int32 Index = 0; Index < UniqueIndices.Num(); ++Index)
                    {
                        if (Counts[Index] != Frequency) continue;
                        const void* Source = Array.GetRawPtr(UniqueIndices[Index]);
                        const int32 Destination = Result.AddValue();
                        Inner->CopyCompleteValue(Result.GetRawPtr(Destination), Source);
                        if (!bHasMode)
                        {
                            ScalarProperty->CopyCompleteValue(ScalarAddress, Source);
                            bHasMode = true;
                        }
                    }
                }
            }
        }
    }
    P_NATIVE_END;
}
