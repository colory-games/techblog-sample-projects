using UnrealBuildTool;

public class MyCompareInt : ModuleRules
{
    public MyCompareInt(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]{
            "Core",
            "CoreUObject",
            "Engine"
        });

        PrivateDependencyModuleNames.AddRange(new string[]{
            "BlueprintGraph",
            "GraphEditor",
            "KismetCompiler",
            "SlateCore",
            "UnrealEd"
        });
    }
}