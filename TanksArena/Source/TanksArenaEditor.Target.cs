// This code is property of dannydev. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TanksArenaEditorTarget : TargetRules
{
	public TanksArenaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "TanksArena" } );
	}
}
