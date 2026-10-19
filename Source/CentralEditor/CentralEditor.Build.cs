using UnrealBuildTool;

public class CentralEditor : ModuleRules
{
    public CentralEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "BlueprintGraph", "UnrealEd", "KismetCompiler", "GraphEditor", "Central"
        });
    }
}
