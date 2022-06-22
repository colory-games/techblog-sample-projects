using UnrealBuildTool;

public class MyDivide : ModuleRules
{
    public MyDivide(ReadOnlyTargetRules Target) : base(Target)
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