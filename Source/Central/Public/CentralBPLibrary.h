// Copyright Mippithedork 2026, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CentralBPLibrary.generated.h"

UCLASS()
class CENTRAL_API UCentralBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    /** Internal wildcard enum implementation, used by the MODE editor node. */
    UFUNCTION(BlueprintPure, CustomThunk, Category="Central|Internal",
        meta=(BlueprintInternalUseOnly="true", ArrayParm="Values,Modes",
              ArrayTypeDependentParams="Value"))
    static void ModeEnum(const TArray<uint8>& Values, uint8& Value,
        TArray<uint8>& Modes, int32& Frequency, bool& bHasMode);
    DECLARE_FUNCTION(execModeEnum);
    /** Weighted arithmetic mean. Weights must be nonnegative finite Doubles, match Values in length, and have positive total weight. */
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanInt(const TArray<int32>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanInt64(const TArray<int64>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanByte(const TArray<uint8>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanFloat(const TArray<float>& Values, const TArray<double>& Weights, float& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanDouble(const TArray<double>& Values, const TArray<double>& Weights, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanVector2D(const TArray<FVector2D>& Values, const TArray<double>& Weights, FVector2D& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanVector(const TArray<FVector>& Values, const TArray<double>& Weights, FVector& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanVector4(const TArray<FVector4>& Values, const TArray<double>& Weights, FVector4& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void WeightedMeanLinearColor(const TArray<FLinearColor>& Values, const TArray<double>& Weights, FLinearColor& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanInt(const TArray<int32>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanInt64(const TArray<int64>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanByte(const TArray<uint8>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanFloat(const TArray<float>& Values, float& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanDouble(const TArray<double>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanVector2D(const TArray<FVector2D>& Values, FVector2D& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanVector(const TArray<FVector>& Values, FVector& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanVector4(const TArray<FVector4>& Values, FVector4& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MeanLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianInt(const TArray<int32>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianInt64(const TArray<int64>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianByte(const TArray<uint8>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianFloat(const TArray<float>& Values, float& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianDouble(const TArray<double>& Values, double& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianVector2D(const TArray<FVector2D>& Values, FVector2D& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianVector(const TArray<FVector>& Values, FVector& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianVector4(const TArray<FVector4>& Values, FVector4& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void MedianLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, bool& bHasValue);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeInt(const TArray<int32>& Values, int32& Value, TArray<int32>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeInt64(const TArray<int64>& Values, int64& Value, TArray<int64>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeByte(const TArray<uint8>& Values, uint8& Value, TArray<uint8>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeFloat(const TArray<float>& Values, float& Value, TArray<float>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeDouble(const TArray<double>& Values, double& Value, TArray<double>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeVector2D(const TArray<FVector2D>& Values, FVector2D& Value, TArray<FVector2D>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeVector(const TArray<FVector>& Values, FVector& Value, TArray<FVector>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeVector4(const TArray<FVector4>& Values, FVector4& Value, TArray<FVector4>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeLinearColor(const TArray<FLinearColor>& Values, FLinearColor& Value, TArray<FLinearColor>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeRotator(const TArray<FRotator>& Values, FRotator& Value, TArray<FRotator>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeBool(const TArray<bool>& Values, bool& Value, TArray<bool>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeString(const TArray<FString>& Values, FString& Value, TArray<FString>& Modes, int32& Frequency, bool& bHasMode);
    UFUNCTION(BlueprintPure, Category="Central|Internal", meta=(BlueprintInternalUseOnly="true"))
    static void ModeName(const TArray<FName>& Values, FName& Value, TArray<FName>& Modes, int32& Frequency, bool& bHasMode);
};
