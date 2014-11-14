#pragma once

#include <SAMP+/CRPC.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK PlayerPauseMenuSwitch(RPC_ARGS);
	static RPC_CALLBACK PlayerPauseMenuBrowse(RPC_ARGS);
	static RPC_CALLBACK PlayerDriveByShot(RPC_ARGS);
	static RPC_CALLBACK StuntBonus(RPC_ARGS);
	static RPC_CALLBACK ResolutionChange(RPC_ARGS);
	static RPC_CALLBACK PlayerClick(RPC_ARGS);
	static RPC_CALLBACK RadioChange(RPC_ARGS);
	static RPC_CALLBACK DrinkSprunk(RPC_ARGS);
};
