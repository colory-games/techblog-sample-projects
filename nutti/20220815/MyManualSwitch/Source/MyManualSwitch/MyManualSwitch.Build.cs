using UnrealBuildTool;

public class MyManualSwitch : ModuleRules
{
    public MyManualSwitch(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]{
            "Core",
            "CoreUObject",
            "Engine"
        });

        PrivateDependencyModuleNames.AddRange(new string[]{
            "BlueprintGraph",
            "EditorStyle",
            "GraphEditor",
            "KismetCompiler",
            "Slate",
            "SlateCore",
            "ToolMenus",
            "UnrealEd"
        });
    }
}