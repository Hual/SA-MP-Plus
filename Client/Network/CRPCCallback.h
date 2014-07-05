#pragma once

#include "../Shared/Network/CRPC.h"
#include <stdafx.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK ToggleHUDComponent(RPC_ARGS);
	static RPC_CALLBACK SetRadioStation(RPC_ARGS);
	static RPC_CALLBACK SetWaveHeight(RPC_ARGS);
	static RPC_CALLBACK TogglePauseMenu(RPC_ARGS);
	static RPC_CALLBACK SetHUDComponentColour(RPC_ARGS);
	//static RPC_CALLBACK SetCheckpointColour(RPC_ARGS);
	//static RPC_CALLBACK SetRaceCheckpointColour(RPC_ARGS);
	static RPC_CALLBACK ToggleAction(RPC_ARGS);

private:

};