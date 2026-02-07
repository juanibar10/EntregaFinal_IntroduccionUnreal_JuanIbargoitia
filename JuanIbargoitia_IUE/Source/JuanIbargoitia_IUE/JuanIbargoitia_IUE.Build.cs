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
			"JuanIbargoitia_IUE/Sokoban"
		});
	}
}
