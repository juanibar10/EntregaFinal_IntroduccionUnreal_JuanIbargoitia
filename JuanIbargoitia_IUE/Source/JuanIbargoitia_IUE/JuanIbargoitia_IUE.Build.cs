// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JuanIbargoitia_IUE : ModuleRules
{
	public JuanIbargoitia_IUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"JuanIbargoitia_IUE",
			"JuanIbargoitia_IUE/Sokoban",
			"JuanIbargoitia_IUE/Variant_Strategy",
			"JuanIbargoitia_IUE/Variant_Strategy/UI",
			"JuanIbargoitia_IUE/Variant_TwinStick",
			"JuanIbargoitia_IUE/Variant_TwinStick/AI",
			"JuanIbargoitia_IUE/Variant_TwinStick/Gameplay",
			"JuanIbargoitia_IUE/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
