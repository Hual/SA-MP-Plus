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

cell AMX_NATIVE_CALL GetPlayerResolutionProc(AMX* pAmx, cell* pParams)
{	
	cell *cellptr;
	amx_GetAddr(pAmx, pParams[2], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetResolutionX(); 

	amx_GetAddr(pAmx, pParams[3], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetResolutionY();

	return 1;
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

cell AMX_NATIVE_CALL SetPlayerClipAmmoProc(AMX* pAmx, cell* pParams) // tips off SA-MP's anti-cheat, wouldn't recomend using... yet...
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // bSlotId
	bitStream.WriteCasted<DWORD, cell>(pParams[3]); // dwNewAmmo

	return Network::PlayerSendRPC(eRPC::SET_CLIP_AMMO, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerNoReloadProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<bool, cell>(pParams[2]); // bToggle

	return Network::PlayerSendRPC(eRPC::SET_NO_RELOAD, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerBlurIntensityProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<int, cell>(pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_BLUR_INTENSITY, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerDriveOnWaterProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<bool, cell>(pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_DRIVE_ON_WATER, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerGameSpeedProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	return Network::PlayerSendRPC(eRPC::SET_GAME_SPEED, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerFrozenProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<bool, cell>(pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_PLAYER_FROZEN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPedAnimsProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<bool, cell>(pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_PLAYER_ANIMS, pParams[1], &bitStream);
}


cell AMX_NATIVE_CALL IsUsingSAMPPProc(AMX* pAmx, cell* pParams)
{
	return Network::IsPlayerConnected(pParams[1]);
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
	//{ "SetPlayerAmmoInClip", SetPlayerClipAmmoProc }, // tips off SA-MP's anti-cheat, wouldn't recomend using... yet...
	{ "SetPlayerNoReload", SetPlayerNoReloadProc },
	{ "GetPlayerResolution", GetPlayerResolutionProc },
	{ "IsUsingSAMPP", IsUsingSAMPPProc },
	{ "SetPlayerBlurIntensity", SetPlayerBlurIntensityProc },
	{ "TogglePlayerDriveOnWater", TogglePlayerDriveOnWaterProc },
	{ "SetPlayerGameSpeed", SetPlayerGameSpeedProc },
	{ "TogglePlayerFrozen", TogglePlayerFrozenProc },
	{ "SetPlayerPedAnims", SetPedAnimsProc },

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