#pragma once

#include "../Shared/Network/CRPC.h"


class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK PlayerPauseMenuSwitch(RPC_ARGS);
	static RPC_CALLBACK PlayerPauseMenuBrowse(RPC_ARGS);
	static RPC_CALLBACK PlayerDriveByShot(RPC_ARGS);
};
