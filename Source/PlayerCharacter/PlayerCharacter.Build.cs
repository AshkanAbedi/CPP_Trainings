using UnrealBuildTool;

public class PlayerCharacter : ModuleRules
{
    public PlayerCharacter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "Slate",
                "SlateCore"
            }
        );
    }
}