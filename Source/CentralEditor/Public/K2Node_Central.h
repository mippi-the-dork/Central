// Copyright Mippithedork 2026, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_Central.generated.h"

UCLASS(Abstract)
class CENTRALEDITOR_API UK2Node_Central : public UK2Node
{
    GENERATED_BODY()
public:
    virtual void AllocateDefaultPins() override;
    virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
    virtual void PostReconstructNode() override;
    virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
    virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetTooltipText() const override;
    virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    virtual bool IsNodePure() const override { return true; }
    virtual bool ShouldShowNodeProperties() const override { return false; }
protected:
    virtual const TCHAR* OperationName() const PURE_VIRTUAL(UK2Node_Central::OperationName, return TEXT(""););
    void RefreshTypes();
    void RefreshPinTooltips();
};

UCLASS()
class CENTRALEDITOR_API UK2Node_CentralWeightedMean : public UK2Node_Central
{
    GENERATED_BODY()
protected:
    virtual const TCHAR* OperationName() const override { return TEXT("WeightedMean"); }
};

UCLASS()
class CENTRALEDITOR_API UK2Node_CentralMean : public UK2Node_Central
{
    GENERATED_BODY()
protected:
    virtual const TCHAR* OperationName() const override { return TEXT("Mean"); }
};
UCLASS()
class CENTRALEDITOR_API UK2Node_CentralMedian : public UK2Node_Central
{
    GENERATED_BODY()
protected:
    virtual const TCHAR* OperationName() const override { return TEXT("Median"); }
};
UCLASS()
class CENTRALEDITOR_API UK2Node_CentralMode : public UK2Node_Central
{
    GENERATED_BODY()
protected:
    virtual const TCHAR* OperationName() const override { return TEXT("Mode"); }
};
