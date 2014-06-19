#pragma once

#include "../Shared/Network/CRPC.h"
#include <stdafx.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK TogglePlayerHUDComponent(RPC_ARGS);
	static RPC_CALLBACK SetPlayerRadioStation(RPC_ARGS);
	static RPC_CALLBACK SetPlayerWaveHeight(RPC_ARGS);

private:

};