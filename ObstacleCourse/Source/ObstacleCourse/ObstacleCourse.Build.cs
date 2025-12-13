// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ObstacleCourse : ModuleRules
{
	public ObstacleCourse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ObstacleCourse",
			"ObstacleCourse/Variant_Platforming",
			"ObstacleCourse/Variant_Platforming/Animation",
			"ObstacleCourse/Variant_Combat",
			"ObstacleCourse/Variant_Combat/AI",
			"ObstacleCourse/Variant_Combat/Animation",
			"ObstacleCourse/Variant_Combat/Gameplay",
			"ObstacleCourse/Variant_Combat/Interfaces",
			"ObstacleCourse/Variant_Combat/UI",
			"ObstacleCourse/Variant_SideScrolling",
			"ObstacleCourse/Variant_SideScrolling/AI",
			"ObstacleCourse/Variant_SideScrolling/Gameplay",
			"ObstacleCourse/Variant_SideScrolling/Interfaces",
			"ObstacleCourse/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
