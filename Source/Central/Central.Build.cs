// Copyright Mippithedork 2026, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Central : ModuleRules
{
    public Central(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine" });
    }
}
