#include <RakNet/BitStream.h>

#include <SAMP+/Utility.h>
#include <SAMP+/CRPC.h>
#include <SAMP+/svr/Plugin.h>
#include <SAMP+/svr/Callback.h>

#include <sampgdk.h>

cell AMX_NATIVE_CALL CallbackProc(AMX* pAmx, cell* pParams)
{	
	return Callback::Process(pAmx, (Callback::eCallbackType)pParams[1], &pParams[2]);
}

cell AMX_NATIVE_CALL ToggleHUDComponentForPlayerProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // component
	bitStream.Write(!!pParams[3]); // toggle

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
	bitStream.Write(!!pParams[2]); // toggle

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

cell AMX_NATIVE_CALL SetPlayerCheckpointExProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write<float>(amx_ctof(pParams[2])); //pos x
	bitStream.Write<float>(amx_ctof(pParams[3])); //pos y
	bitStream.Write<float>(amx_ctof(pParams[4])); //pos z
	bitStream.Write<float>(amx_ctof(pParams[5])); //size
	bitStream.WriteCasted<unsigned int, cell>(pParams[6]); //colour
	bitStream.WriteCasted<unsigned short, cell>(pParams[7]); //period
	bitStream.Write<float>(amx_ctof(pParams[8])); //pulse
	bitStream.WriteCasted<short, cell>(pParams[9]); //rot_rate
	bitStream.Write(!!pParams[10]); //check_z

	DisablePlayerCheckpoint(pParams[1]);

	Network::PlayerSendRPC(eRPC::SET_CHECKPOINT_EX, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerRaceCheckpointExProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); //type
	bitStream.Write<float>(amx_ctof(pParams[3])); //pos x
	bitStream.Write<float>(amx_ctof(pParams[4])); //pos y
	bitStream.Write<float>(amx_ctof(pParams[5])); //pos z
	bitStream.Write<float>(amx_ctof(pParams[6])); //point x
	bitStream.Write<float>(amx_ctof(pParams[7])); //point y
	bitStream.Write<float>(amx_ctof(pParams[8])); //point z
	bitStream.Write<float>(amx_ctof(pParams[9])); //size
	bitStream.WriteCasted<unsigned int, cell>(pParams[10]); //colour
	bitStream.WriteCasted<unsigned short, cell>(pParams[11]); //period
	bitStream.Write<float>(amx_ctof(pParams[12])); //pulse
	bitStream.WriteCasted<short, cell>(pParams[13]); //rot_rate

	DisablePlayerRaceCheckpoint(pParams[1]);

	Network::PlayerSendRPC(eRPC::SET_RACE_CHECKPOINT_EX, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned long, cell>(pParams[2]); // checkpoint colours
	/*bitStream.WriteCasted<unsigned long, cell>(pParams[3]);
	bitStream.WriteCasted<unsigned long, cell>(pParams[4]);*/

	Network::PlayerSendRPC(eRPC::SET_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerRaceCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned int, cell>(pParams[2]); // checkpoint colour

	Network::PlayerSendRPC(eRPC::SET_RACE_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL TogglePlayerActionProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // action
	bitStream.Write(!!pParams[3]); // toggle

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
	bitStream.Write(!!pParams[2]); // bToggle

	return Network::PlayerSendRPC(eRPC::SET_NO_RELOAD, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerBlurIntensityProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_BLUR_INTENSITY, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerDriveOnWaterProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

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
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_PLAYER_FROZEN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPedAnimsProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_PLAYER_ANIMS, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerSwitchReloadProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_SWITCH_RELOAD, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerInfiniteRunProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_INFINITE_RUN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerAircraftHeightProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::GetPlayerFromPlayerid(pParams[1])->SetAircraftHeight(amx_ctof(pParams[2]));
	return Network::PlayerSendRPC(eRPC::SET_AIRCRAFT_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerAircraftHeightProc(AMX* pAmx, cell* pParams)
{
	float f = Network::GetPlayerFromPlayerid(pParams[1])->GetAircraftHeight();
	return amx_ftoc(f);
}

cell AMX_NATIVE_CALL SetPlayerJetpackHeightProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::GetPlayerFromPlayerid(pParams[1])->SetJetpackHeight(amx_ctof(pParams[2]));
	return Network::PlayerSendRPC(eRPC::SET_JETPACK_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerJetpackHeightProc(AMX* pAmx, cell* pParams)
{
	float f = Network::GetPlayerFromPlayerid(pParams[1])->GetJetpackHeight();
	return amx_ftoc(f);
}

cell AMX_NATIVE_CALL TogglePlayerVehicleBlipsProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	Network::GetPlayerFromPlayerid(pParams[1])->ToggleVehicleBlips(!!pParams[2]);
	return Network::PlayerSendRPC(eRPC::TOGGLE_VEHICLE_BLIPS, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerVehicleBlipsProc(AMX* pAmx, cell* pParams)
{
	return Network::GetPlayerFromPlayerid(pParams[1])->GetVehicleBlips();
}

cell AMX_NATIVE_CALL IsUsingSAMPPProc(AMX* pAmx, cell* pParams)
{
	return Network::isConnected(pParams[1]);
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
	Network::Initialize(SAMPServer::GetListeningAddress(), SAMPServer::GetListeningPort()+1, SAMPServer::getMaxPlayers());
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	Utility::Printf("Unloaded");
	return sampgdk::Unload();
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
	{ "SetPlayerCheckpointEx", SetPlayerCheckpointExProc },
	{ "SetPlayerRaceCheckpointEx", SetPlayerRaceCheckpointExProc },
	{ "SetPlayerCheckpointColour", SetPlayerCheckpointColourProc },
	{ "SetPlayerRaceCheckpointColour", SetPlayerRaceCheckpointColourProc },
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
	{ "TogglePlayerSwitchReload", TogglePlayerSwitchReloadProc },
	{ "TogglePlayerInfiniteRun", TogglePlayerInfiniteRunProc },
	{ "SetPlayerAircraftHeight", SetPlayerAircraftHeightProc },
	{ "GetPlayerAircraftHeight", GetPlayerAircraftHeightProc },
	{ "SetPlayerJetpackHeight", SetPlayerJetpackHeightProc },
	{ "GetPlayerJetpackHeight", GetPlayerJetpackHeightProc },
	{ "TogglePlayerVehicleBlips", TogglePlayerVehicleBlipsProc },
	{ "GetPlayerVehicleBlips", GetPlayerVehicleBlipsProc },
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