#include "K2Node_Central.h"
#include "CentralBPLibrary.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "EdGraph/EdGraphPin.h"

#define LOCTEXT_NAMESPACE "CentralNodes"

namespace CentralEditorPrivate
{
    struct FSupported
    {
        const TCHAR* Suffix;
        FName Category;
        FName SubCategory;
        bool bStructure;
    };
    static const FSupported Types[] = {
        { TEXT("Int"), UEdGraphSchema_K2::PC_Int, NAME_None, false },
        { TEXT("Int64"), UEdGraphSchema_K2::PC_Int64, NAME_None, false },
        { TEXT("Byte"), UEdGraphSchema_K2::PC_Byte, NAME_None, false },
        { TEXT("Float"), UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, false },
        { TEXT("Double"), UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Double, false },
        { TEXT("Vector2D"), UEdGraphSchema_K2::PC_Struct, NAME_None, true },
        { TEXT("Vector"), UEdGraphSchema_K2::PC_Struct, NAME_None, true },
        { TEXT("Vector4"), UEdGraphSchema_K2::PC_Struct, NAME_None, true },
        { TEXT("LinearColor"), UEdGraphSchema_K2::PC_Struct, NAME_None, true },
        { TEXT("Rotator"), UEdGraphSchema_K2::PC_Struct, NAME_None, true },
        { TEXT("Bool"), UEdGraphSchema_K2::PC_Boolean, NAME_None, false },
        { TEXT("String"), UEdGraphSchema_K2::PC_String, NAME_None, false },
        { TEXT("Name"), UEdGraphSchema_K2::PC_Name, NAME_None, false },
    };
    static const FSupported* Match(const FEdGraphPinType& PinType, bool bMode)
    {
        if (PinType.ContainerType != EPinContainerType::Array) return nullptr;
        // Mode accepts native and user-created Blueprint byte-backed enums.
        if (bMode && PinType.PinCategory == UEdGraphSchema_K2::PC_Byte &&
            PinType.PinSubCategoryObject.Get() != nullptr &&
            Cast<UEnum>(PinType.PinSubCategoryObject.Get()))
        {
            static const FSupported EnumType = { TEXT("Enum"), UEdGraphSchema_K2::PC_Byte, NAME_None, false };
            return &EnumType;
        }
        for (const FSupported& Type : Types)
        {
            const FString Suffix(Type.Suffix);
            if (!bMode && (Suffix == TEXT("Bool") || Suffix == TEXT("String") || Suffix == TEXT("Name") || Suffix == TEXT("Rotator"))) continue;
            if (PinType.PinCategory != Type.Category) continue;
            // Byte enums are distinct categorical types, not uint8 arrays.
            // Never dispatch their storage to the Byte runtime function.
            if (Suffix == TEXT("Byte") && PinType.PinSubCategoryObject.Get() != nullptr) continue;
            if (Type.Category == UEdGraphSchema_K2::PC_Real && PinType.PinSubCategory != Type.SubCategory) continue;
            if (Type.bStructure)
            {
                const UObject* Obj = PinType.PinSubCategoryObject.Get();
                const FString StructName = Obj ? Obj->GetName() : FString();
                if (StructName != FString(Type.Suffix))
                {
                    if (!(Suffix == TEXT("Vector") && StructName == TEXT("Vector"))) continue;
                }
            }
            return &Type;
        }
        return nullptr;
    }
    static FEdGraphPinType ScalarOf(const FEdGraphPinType& ArrayType)
    {
        FEdGraphPinType Result = ArrayType;
        Result.ContainerType = EPinContainerType::None;
        return Result;
    }
}

void UK2Node_Central::AllocateDefaultPins()
{
    FEdGraphPinType ArrayType;
    ArrayType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
    ArrayType.ContainerType = EPinContainerType::Array;
    CreatePin(EGPD_Input, ArrayType, TEXT("Values"));
    if (FCString::Strcmp(OperationName(), TEXT("WeightedMean")) == 0)
    {
        FEdGraphPinType WeightsType;
        WeightsType.PinCategory = UEdGraphSchema_K2::PC_Real;
        WeightsType.PinSubCategory = UEdGraphSchema_K2::PC_Double;
        WeightsType.ContainerType = EPinContainerType::Array;
        CreatePin(EGPD_Input, WeightsType, TEXT("Weights"));
    }
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, TEXT("Value"));
    if (FCString::Strcmp(OperationName(), TEXT("Mode")) == 0)
    {
        CreatePin(EGPD_Output, ArrayType, TEXT("Modes"));
        CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, TEXT("Frequency"));
        CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, TEXT("bHasMode"));
    }
    else
    {
        CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, TEXT("bHasValue"));
    }
    Super::AllocateDefaultPins();
    RefreshTypes();
}
void UK2Node_Central::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    // UE 5.8 performs ReallocatePinsDuringReconstruction before reconnecting
    // old pins (UK2Node::ReconstructNode). Recreate the correct pin types now,
    // so the schema can restore existing typed connections without coercion.
    AllocateDefaultPins();

    const bool bMode = FCString::Strcmp(OperationName(), TEXT("Mode")) == 0;
    const UEdGraphPin* OldValues = nullptr;
    const UEdGraphPin* OldValue = nullptr;
    const UEdGraphPin* OldModes = nullptr;
    for (const UEdGraphPin* OldPin : OldPins)
    {
        if (!OldPin) continue;
        if (OldPin->PinName == TEXT("Values")) OldValues = OldPin;
        else if (OldPin->PinName == TEXT("Value")) OldValue = OldPin;
        else if (OldPin->PinName == TEXT("Modes")) OldModes = OldPin;
    }

    FEdGraphPinType RecoveredType;
    RecoveredType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
    RecoveredType.ContainerType = EPinContainerType::Array;
    if (OldValues)
    {
        if (!OldValues->LinkedTo.IsEmpty() && OldValues->LinkedTo[0])
        {
            RecoveredType = OldValues->LinkedTo[0]->PinType;
        }
        else if (CentralEditorPrivate::Match(OldValues->PinType, bMode))
        {
            RecoveredType = OldValues->PinType;
        }
    }
    if (!CentralEditorPrivate::Match(RecoveredType, bMode) && bMode)
    {
        const UEdGraphPin* Source = nullptr;
        if (OldValue && !OldValue->LinkedTo.IsEmpty() && OldValue->LinkedTo[0])
        {
            Source = OldValue->LinkedTo[0];
        }
        else if (OldModes && !OldModes->LinkedTo.IsEmpty() && OldModes->LinkedTo[0])
        {
            Source = OldModes->LinkedTo[0];
        }
        if (Source)
        {
            RecoveredType = Source->PinType;
            RecoveredType.ContainerType = EPinContainerType::Array;
        }
    }

    if (const CentralEditorPrivate::FSupported* Matched = CentralEditorPrivate::Match(RecoveredType, bMode))
    {
        if (UEdGraphPin* Input = FindPin(TEXT("Values"))) Input->PinType = RecoveredType;
        if (UEdGraphPin* Value = FindPin(TEXT("Value")))
        {
            Value->PinType = CentralEditorPrivate::ScalarOf(RecoveredType);
            const FString Suffix(Matched->Suffix);
            if (!bMode && (Suffix == TEXT("Int") || Suffix == TEXT("Int64") || Suffix == TEXT("Byte")))
            {
                Value->PinType.PinCategory = UEdGraphSchema_K2::PC_Real;
                Value->PinType.PinSubCategory = UEdGraphSchema_K2::PC_Double;
                Value->PinType.PinSubCategoryObject = nullptr;
            }
        }
        if (bMode)
        {
            if (UEdGraphPin* Modes = FindPin(TEXT("Modes"))) Modes->PinType = RecoveredType;
        }
    }
    RefreshPinTooltips();
    // Preserve native split-vector restoration and persistent pin data.
    RestoreSplitPins(OldPins);
}

void UK2Node_Central::PostReconstructNode()
{
    Super::PostReconstructNode();
    RefreshTypes();
}
void UK2Node_Central::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
    RefreshTypes();
}
bool UK2Node_Central::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    if (!MyPin || !OtherPin)
    {
        return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
    }

    const bool bMode = FCString::Strcmp(OperationName(), TEXT("Mode")) == 0;
    if (MyPin->PinName == TEXT("Values") && MyPin->Direction == EGPD_Input)
    {
        if (OtherPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard &&
            !CentralEditorPrivate::Match(OtherPin->PinType, bMode))
        {
            OutReason = TEXT("Central requires an array of a supported element type. Unsupported structs or element types cannot connect to this node.");
            return true;
        }
    }
    if (bMode && (MyPin->PinName == TEXT("Value") || MyPin->PinName == TEXT("Modes")))
    {
        // If the input is typed, Mode outputs must preserve the same element type.
        const UEdGraphPin* ValuesPin = FindPin(TEXT("Values"));
        if (ValuesPin && ValuesPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard &&
            OtherPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
        {
            const FEdGraphPinType Expected = MyPin->PinType;
            if (Expected.PinCategory != OtherPin->PinType.PinCategory ||
                Expected.PinSubCategory != OtherPin->PinType.PinSubCategory ||
                Expected.PinSubCategoryObject != OtherPin->PinType.PinSubCategoryObject ||
                Expected.ContainerType != OtherPin->PinType.ContainerType)
            {
                OutReason = TEXT("Mode output must match the connected Values array element type.");
                return true;
            }
        }
    }
    // All four operations have strongly typed outputs after Values is connected.
    // Prevent a stale consumer (for example after replacing an Integer array
    // with a Vector array) from silently retaining an incompatible connection.
    if (MyPin->Direction == EGPD_Output &&
        (MyPin->PinName == TEXT("Value") || MyPin->PinName == TEXT("Modes")) &&
        MyPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard &&
        OtherPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
    {
        const FEdGraphPinType& Expected = MyPin->PinType;
        const FEdGraphPinType& Actual = OtherPin->PinType;
        if (Expected.PinCategory != Actual.PinCategory ||
            Expected.PinSubCategory != Actual.PinSubCategory ||
            Expected.PinSubCategoryObject != Actual.PinSubCategoryObject ||
            Expected.ContainerType != Actual.ContainerType)
        {
            OutReason = TEXT("Central output type is determined by the Values array. Connect a compatible consumer or change the input array type.");
            return true;
        }
    }
    return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

void UK2Node_Central::RefreshTypes()
{
    UEdGraphPin* Input = FindPin(TEXT("Values"));
    UEdGraphPin* Value = FindPin(TEXT("Value"));
    if (!Input || !Value) return;
    const bool bMode = FCString::Strcmp(OperationName(), TEXT("Mode")) == 0;
    FEdGraphPinType InputType;
    InputType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
    InputType.ContainerType = EPinContainerType::Array;
    // Input array determines the type; other output pins are not authoritative.
    if (Input->LinkedTo.Num() > 0 && Input->LinkedTo[0])
    {
        InputType = Input->LinkedTo[0]->PinType;
    }
    else if (bMode)
    {
        // Either dependent output can establish the input type when the
        // array has not yet been connected. A new array link takes priority.
        const UEdGraphPin* Modes = FindPin(TEXT("Modes"));
        const UEdGraphPin* Source = nullptr;
        if (!Value->LinkedTo.IsEmpty()) Source = Value->LinkedTo[0];
        else if (Modes && !Modes->LinkedTo.IsEmpty()) Source = Modes->LinkedTo[0];
        if (Source)
        {
            InputType = Source->PinType;
            InputType.ContainerType = EPinContainerType::Array;
        }
    }
    const auto* Matched = CentralEditorPrivate::Match(InputType, bMode);
    const FEdGraphPinType PreviousInputType = Input->PinType;
    const FEdGraphPinType PreviousValueType = Value->PinType;
    const UEdGraphPin* PreviousModesPin = bMode ? FindPin(TEXT("Modes")) : nullptr;
    const FEdGraphPinType PreviousModesType = PreviousModesPin ? PreviousModesPin->PinType : FEdGraphPinType();
    Input->PinType = InputType;
    Value->PinType = CentralEditorPrivate::ScalarOf(InputType);
    if (Matched && !bMode && (FString(Matched->Suffix) == TEXT("Int") || FString(Matched->Suffix) == TEXT("Int64") || FString(Matched->Suffix) == TEXT("Byte")))
    {
        Value->PinType.PinCategory = UEdGraphSchema_K2::PC_Real;
        Value->PinType.PinSubCategory = UEdGraphSchema_K2::PC_Double;
        Value->PinType.PinSubCategoryObject = nullptr;
    }
    if (bMode)
    {
        if (UEdGraphPin* Modes = FindPin(TEXT("Modes"))) Modes->PinType = InputType;
    }
    RefreshPinTooltips();
    // Avoid recursively invalidating graph rendering when no type changed.
    // This can be called repeatedly during reconstruction and connection edits.
    const UEdGraphPin* CurrentModesPin = bMode ? FindPin(TEXT("Modes")) : nullptr;
    const bool bTypeChanged = !(PreviousInputType == Input->PinType) ||
        !(PreviousValueType == Value->PinType) ||
        (CurrentModesPin && !(PreviousModesType == CurrentModesPin->PinType));
    if (bTypeChanged && GetGraph()) GetGraph()->NotifyGraphChanged();
}
void UK2Node_Central::GetMenuActions(FBlueprintActionDatabaseRegistrar& Registrar) const
{
    UClass* ActionKey = GetClass();
    if (Registrar.IsOpenForRegistration(ActionKey))
    {
        Registrar.AddBlueprintAction(ActionKey, UBlueprintNodeSpawner::Create(ActionKey));
    }
}
FText UK2Node_Central::GetMenuCategory() const { return LOCTEXT("Category", "Math|Statistics"); }
FText UK2Node_Central::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    if (FString(OperationName()) == TEXT("WeightedMean"))
        return TitleType == ENodeTitleType::FullTitle ? LOCTEXT("WeightedMeanFullTitle", "Weighted Mean Value") : LOCTEXT("WeightedMeanCompact", "WEIGHTED MEAN");
    if (TitleType == ENodeTitleType::FullTitle) return FText::FromString(FString(OperationName()) + TEXT(" Value"));
    return FText::FromString(FString(OperationName()).ToUpper());
}
FText UK2Node_Central::GetTooltipText() const
{
    const FString Operation(OperationName());
    if (Operation == TEXT("WeightedMean"))
    {
        return LOCTEXT("WeightedMeanNodeTooltip", "Calculates a weighted arithmetic mean of Values using corresponding Weights.\n"
            "Weights must be a Double array with the same number of elements as Values. Each weight must be finite and nonnegative, and at least one must be positive. "
            "A zero weight excludes its value. Integer inputs return Double. Vector and color inputs are averaged component-wise. "
            "Has Value is false for invalid arrays or non-finite input; the input arrays are not modified.");
    }
    if (Operation == TEXT("Mean"))
    {
        return LOCTEXT("MeanNodeTooltip", "Calculates the arithmetic mean (average) of an array.\n"
            "Integer and Byte arrays produce a Double result, so fractions are preserved. "
            "Vector and Linear Color components are averaged independently.\n"
            "Has Value is false when the array is empty or contains non-finite numeric data. "
            "The input array is not modified.");
    }
    if (Operation == TEXT("Median"))
    {
        return LOCTEXT("MedianNodeTooltip", "Finds the median of an array, the middle value after sorting.\n"
            "For an even number of values, averages the two middle values. "
            "Integer and Byte arrays return Double. Vectors and Linear Colors use a component-wise median.\n"
            "Has Value is false for empty arrays or non-finite numeric data. The input array is not reordered.");
    }
    return LOCTEXT("ModeNodeTooltip", "Finds the most frequently occurring value or values in an array.\n"
        "Value is the first mode encountered; Modes contains all tied modes in first-seen order. "
        "Frequency is the number of occurrences of each mode.\n"
        "Has Mode is false when no item repeats, the array is empty, or numeric data is non-finite. "
        "Matching uses the value type's equality rules. The input array is not modified.");
}
void UK2Node_Central::RefreshPinTooltips()
{
    const FString Operation(OperationName());
    const bool bMode = Operation == TEXT("Mode");
    const UEdGraphPin* Input = FindPin(TEXT("Values"));
    const bool bTyped = Input && Input->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard;
    const FString TypeNote = bTyped ? TEXT(" The array connection sets this node's output type.") : TEXT(" Connect a supported array to determine its type.");
    if (UEdGraphPin* Pin = FindPin(TEXT("Values")))
    {
        Pin->PinToolTip = FString(bMode
            ? TEXT("Input array to search for repeated values. Supports numeric types, native and Blueprint Enums, vectors, Linear Color, Rotator, Boolean, String, and Name. Exact behavior follows each type's equality operator.")
            : TEXT("Input array to calculate the statistical result. Supports Byte, Integer, Integer64, Float, Double, Vector2D, Vector, Vector4, and Linear Color. Unconnected arrays are not supported; connect Make Array.")) + TypeNote;
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("Weights")))
    {
        Pin->PinToolTip = TEXT("Double array of nonnegative weights, one per input value. The two arrays must have the same length; at least one weight must be positive. Zero-weight entries do not contribute.");
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("Value")))
    {
        Pin->PinToolTip = Operation == TEXT("WeightedMean") ? TEXT("Weighted arithmetic average of the input values. Integer input produces Double, vectors and colors use component-wise averages. Returns a default value when Has Value is false.") : Operation == TEXT("Mean")
            ? TEXT("Arithmetic average. Integer and Byte input arrays output Double; vectors and colors are averaged component-wise. Returns the default value when Has Value is false.")
            : Operation == TEXT("Median")
                ? TEXT("Middle value of the sorted data, or average of the two middle values for even-sized arrays. For vectors and colors, this is component-wise. Returns the default when Has Value is false.")
                : TEXT("First most-frequent value in the input's original encounter order. For ties, see Modes. Returns the type's default when Has Mode is false.");
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("bHasValue")))
    {
        Pin->PinToolTip = TEXT("True if a non-empty array produces a finite, valid result. False for empty arrays or non-finite numerical values. Check before using Value.");
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("Modes")))
    {
        Pin->PinToolTip = TEXT("All values tied for the highest frequency, in first-encountered order. Empty when Has Mode is false. Each listed mode occurs Frequency times.");
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("Frequency")))
    {
        Pin->PinToolTip = TEXT("How many times each most-frequent value occurs. Returns 0 for an empty array, 1 when all items are unique, or a larger count when a mode exists.");
    }
    if (UEdGraphPin* Pin = FindPin(TEXT("bHasMode")))
    {
        Pin->PinToolTip = TEXT("True if at least one value occurs more than once. False when all input values are unique, the array is empty, or numeric data is invalid. Check before using Value or Modes.");
    }
}
void UK2Node_Central::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);
    UEdGraphPin* Input = FindPin(TEXT("Values"));
    const bool bMode = FCString::Strcmp(OperationName(), TEXT("Mode")) == 0;
    if (!Input || Input->LinkedTo.IsEmpty())
    {
        CompilerContext.MessageLog.Error(TEXT("Central: connect a supported array to @@"), this);
        BreakAllNodeLinks();
        return;
    }
    const CentralEditorPrivate::FSupported* Type = CentralEditorPrivate::Match(Input->LinkedTo[0]->PinType, bMode);
    if (!Type)
    {
        CompilerContext.MessageLog.Error(TEXT("Central: unsupported array element type on @@"), this);
        BreakAllNodeLinks();
        return;
    }
    const FName FunctionName(*(FString(OperationName()) + FString(Type->Suffix)));
    UFunction* Function = UCentralBPLibrary::StaticClass()->FindFunctionByName(FunctionName);
    if (!Function)
    {
        CompilerContext.MessageLog.Error(TEXT("Central: internal function not found on @@"), this);
        BreakAllNodeLinks();
        return;
    }
    UK2Node_CallFunction* Call = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    Call->SetFromFunction(Function);
    Call->AllocateDefaultPins();
    // UHT declares byte placeholders; the enum thunk reads the reflected types.
    // Match every dependent intermediate pin to the source enum before moving links.
    if (bMode && FString(Type->Suffix) == TEXT("Enum"))
    {
        const FEdGraphPinType ActualArray = Input->LinkedTo[0]->PinType;
        if (UEdGraphPin* P = Call->FindPin(TEXT("Values"))) P->PinType = ActualArray;
        if (UEdGraphPin* P = Call->FindPin(TEXT("Modes"))) P->PinType = ActualArray;
        if (UEdGraphPin* P = Call->FindPin(TEXT("Value"))) P->PinType = CentralEditorPrivate::ScalarOf(ActualArray);
    }
    auto Transfer = [&](const TCHAR* Source, const TCHAR* Destination)
    {
        UEdGraphPin* From = FindPin(Source);
        UEdGraphPin* To = Call->FindPin(Destination);
        if (!From || !To || !CompilerContext.MovePinLinksToIntermediate(*From, *To).CanSafeConnect())
            CompilerContext.MessageLog.Error(TEXT("Central: pin expansion failure on @@"), this);
    };
    Transfer(TEXT("Values"), TEXT("Values"));
    if (FString(OperationName()) == TEXT("WeightedMean")) Transfer(TEXT("Weights"), TEXT("Weights"));
    Transfer(TEXT("Value"), TEXT("Value"));
    if (bMode)
    {
        Transfer(TEXT("Modes"), TEXT("Modes"));
        Transfer(TEXT("Frequency"), TEXT("Frequency"));
        Transfer(TEXT("bHasMode"), TEXT("bHasMode"));
    }
    else Transfer(TEXT("bHasValue"), TEXT("bHasValue"));
    BreakAllNodeLinks();
}
#undef LOCTEXT_NAMESPACE
