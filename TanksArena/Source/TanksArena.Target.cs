// This code is property of dannydev. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TanksArenaTarget : TargetRules
{
	public TanksArenaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TanksArena" } );
	}
}
