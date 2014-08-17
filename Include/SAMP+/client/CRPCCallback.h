#pragma once

#include <SAMP+/CRPC.h>
#include <SAMP+/client/Client.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK ToggleHUDComponent(RPC_ARGS);
	static RPC_CALLBACK SetRadioStation(RPC_ARGS);
	static RPC_CALLBACK SetWaveHeight(RPC_ARGS);
	static RPC_CALLBACK TogglePauseMenu(RPC_ARGS);
	static RPC_CALLBACK SetHUDComponentColour(RPC_ARGS);
	static RPC_CALLBACK SetPlayerCheckpointEx(RPC_ARGS);
	static RPC_CALLBACK SetPlayerRaceCheckpointEx(RPC_ARGS);
	static RPC_CALLBACK SetCheckpointColour(RPC_ARGS);
	static RPC_CALLBACK SetRaceCheckpointColour(RPC_ARGS);
	static RPC_CALLBACK ToggleAction(RPC_ARGS);
	static RPC_CALLBACK SetAmmoInClip(RPC_ARGS);
	static RPC_CALLBACK SetNoReload(RPC_ARGS);
	static RPC_CALLBACK ToggleInfiniteRun(RPC_ARGS);
	static RPC_CALLBACK DriveOnWater(RPC_ARGS);
	static RPC_CALLBACK SetBlur(RPC_ARGS);
	static RPC_CALLBACK SetSpeed(RPC_ARGS);
	static RPC_CALLBACK SetFrozen(RPC_ARGS);
	static RPC_CALLBACK SetAnims(RPC_ARGS);
	static RPC_CALLBACK ToggleSwitchReload(RPC_ARGS);
	static RPC_CALLBACK SetJetpackHeight(RPC_ARGS);
	static RPC_CALLBACK SetAircraftHeight(RPC_ARGS);

private:

};