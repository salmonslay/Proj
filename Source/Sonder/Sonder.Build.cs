// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sonder : ModuleRules
{
	public Sonder(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"AdvancedSessions", "UINavigation"});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Sockets", 
			"CableComponent",
			"Niagara", 
			"LevelSequence", 
			"MovieScene", 
			"UMG", 
			"GeometryCollectionEngine", 
			"NavigationSystem"
		});
		
	}
}
