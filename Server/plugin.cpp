#include "plugin.h"
#include "../Shared/Utility/Utility.h"
#include "../Shared/RakNet/BitStream.h"
#include "../Shared/Network/CRPC.h"
#include "SDK/sampgdk/core.h"
#include "SDK/sampgdk/a_players.h"
#include "Callback.h"

cell AMX_NATIVE_CALL CallbackProc(AMX* pAmx, cell* pParams)
{	
	return Callback::Process(pAmx, (Callback::eCallbackType)pParams[1], &pParams[2]);
}

cell AMX_NATIVE_CALL ToggleHUDComponentForPlayerProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // component
	bitStream.WriteCasted<unsigned char, cell>(pParams[3]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_HUD_COMPONENT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerHUDComponentColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // colour component
	bitStream.WriteCasted<unsigned int, cell>(pParams[3]); // colour

	return Network::PlayerSendRPC(eRPC::SET_HUD_COMPONENT_COLOUR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetRadioStationForPlayerProc(AMX* pAmx, cell* pParams)
{
	if (IsPlayerInAnyVehicle(pParams[1]))
	{
		RakNet::BitStream bitStream;
		bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // radio station id

		return Network::PlayerSendRPC(eRPC::SET_RADIO_STATION, pParams[1], &bitStream);
	}

	return 1;
}

cell AMX_NATIVE_CALL SetWaveHeightForPlayerProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2])); // wave height

	return Network::PlayerSendRPC(eRPC::SET_WAVE_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePauseMenuAbilityProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_PAUSE_MENU, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL IsPlayerInPauseMenuProc(AMX* pAmx, cell* pParams)
{
	return Network::GetPlayerFromPlayerid(pParams[1])->IsInPauseMenu();
}

cell AMX_NATIVE_CALL SetWaveHeightForAllProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[1])); // wave height

	Network::BroadcastRPC(eRPC::SET_WAVE_HEIGHT, &bitStream);
	return 1;
}

/*cell AMX_NATIVE_CALL SetPlayerCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned long, cell>(pParams[2]); // checkpoint colours
	bitStream.WriteCasted<unsigned long, cell>(pParams[3]);
	bitStream.WriteCasted<unsigned long, cell>(pParams[4]);

	Network::PlayerSendRPC(eRPC::SET_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerRaceCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned long, cell>(pParams[2]); // checkpoint colour

	Network::PlayerSendRPC(eRPC::SET_RACE_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}*/

cell AMX_NATIVE_CALL TogglePlayerActionProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // action
	bitStream.WriteCasted<bool, cell>(pParams[3]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_ACTION, pParams[1], &bitStream);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	Network::Process();
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	Utility::Initialize(ppData);
	Utility::Printf("Loaded");
	SAMPServer::Initialize("server.cfg");
	Network::Initialize(SAMPServer::GetListeningAddress(), SAMPServer::GetListeningPort()+1, SAMPServer::GetMaxPlayers());
	return sampgdk::Load(sampgdk::GetCurrentPluginHandle(), ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	Utility::Printf("Unloaded");
	return sampgdk::Unload(sampgdk::GetCurrentPluginHandle());
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SAMPP_ExecuteCallback", CallbackProc },
	{ "ToggleHUDComponentForPlayer", ToggleHUDComponentForPlayerProc },
	{ "SetRadioStationForPlayer", SetRadioStationForPlayerProc },
	{ "SetWaveHeightForPlayer", SetWaveHeightForPlayerProc },
	{ "SetWaveHeightForAll", SetWaveHeightForAllProc },
	{ "TogglePauseMenuAbility", TogglePauseMenuAbilityProc },
	{ "IsPlayerInPauseMenu", IsPlayerInPauseMenuProc },
	{ "SetPlayerHUDComponentColour", SetPlayerHUDComponentColourProc },
	/*{ "SetPlayerCheckpointColour", SetPlayerCheckpointColourProc },
	{ "SetPlayerRaceCheckpointColour", SetPlayerRaceCheckpointColourProc },*/
	{ "TogglePlayerAction", TogglePlayerActionProc },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *pAmx)
{
	Callback::GetAMXList().push_back(pAmx);
	return amx_Register(pAmx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *pAmx)
{
	Callback::GetAMXList().remove(pAmx);
	return AMX_ERR_NONE;
}