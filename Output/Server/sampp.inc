native SAMPP_ExecuteCallback(type, {Float,_}:...);

public OnPlayerConnect(playerid)
{
	SAMPP_ExecuteCallback(0, playerid);

#if defined SAMPP_OnPlayerConnect
	return SAMPP_OnPlayerConnect(playerid);
#else
	return 1;
#endif
}

#if defined SAMPP_OnPlayerConnect
	forward SAMPP_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAMPP_OnPlayerConnect

public OnPlayerDisconnect(playerid, reason)
{
	SAMPP_ExecuteCallback(1, playerid);

#if defined SAMPP_OnPlayerDisconnect
	return SAMPP_OnPlayerDisconnect(playerid, reason);
#else
	return 1;
#endif
}

#if defined SAMPP_OnPlayerDisconnect
	forward SAMPP_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SAMPP_OnPlayerDisconnect

/*native SetPlayerCheckpointColour(playerid, inner, middle, outer);
native SetPlayerRaceCheckpointColour(playerid, colour);

stock SAMPP_hook_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size, inner_colour = 0xFF0000FF, middle_colour = 0xFF0000FF, outer_colour = 0xFF0000FF)
{
	return SetPlayerCheckpoint(playerid, x, y, z, size) && SetPlayerCheckpointColour(playerid, inner_colour, middle_colour, outer_colour);
}
#define SetPlayerCheckpoint SAMPP_hook_SetPlayerCheckpoint

stock SAMPP_hook_SetPlayerRaceCP(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, colour = 0xFF0000FF)
{
	return SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size) && SetPlayerRaceCheckpointColour(playerid, colour);
}
#define SetPlayerRaceCheckpoint SAMPP_hook_SetPlayerRaceCP*/

#define HUD_COMPONENT_ALL 0
#define HUD_COMPONENT_AMMO 1
#define HUD_COMPONENT_WEAPON 2
#define HUD_COMPONENT_HEALTH 3
#define HUD_COMPONENT_BREATH 4
#define HUD_COMPONENT_ARMOUR 5
#define HUD_COMPONENT_MINIMAP 6
#define HUD_COMPONENT_CROSSHAIR 7
#define HUD_COMPONENT_MONEY 8

#define HUD_COLOUR_MONEY_POSITIVE 0
#define HUD_COLOUR_MONEY_NEGATIVE 1
#define HUD_COLOUR_ARMOUR 2
#define HUD_COLOUR_HEALTH 3
#define HUD_COLOUR_BREATH 4
#define HUD_COLOUR_AMMO 5
#define HUD_COLOUR_WANTED_LEVEL 6
#define HUD_COLOUR_RADIO_TUNED 7
#define HUD_COLOUR_RADIO_UNTUNED 8

#define RADIO_PLAYBACKFM 1
#define RADIO_KROSE 2
#define RADIO_KDST 3
#define RADIO_BOUNCEFM 4
#define RADIO_SFUR 5
#define RADIO_LOSSANTOS 6
#define RADIO_RADIOX 7
#define RADIO_CSR 8
#define RADIO_KJAHWEST 9
#define RADIO_MASTERSOUNDS 10
#define RADIO_WCTR 11
#define RADIO_UTP 12
#define RADIO_OFF 13

#define PAUSE_ID_STATS 0
#define PAUSE_ID_STARTGAME 1
#define PAUSE_ID_BRIEF 2
#define PAUSE_ID_AUDIOSETTINGS 3
#define PAUSE_ID_DISPLAYSETTINGS 4
#define PAUSE_ID_MAP 5
#define PAUSE_ID_DEFAULTSETTINGS 23
#define PAUSE_ID_AUDIODEFAULTSETTINGS 24
#define PAUSE_ID_CONTROLLERDEFAULTSETTINGS 25
#define PAUSE_ID_USERTRACKOPTIONS 26
#define PAUSE_ID_LANGUAGE 28
#define PAUSE_ID_OPTIONS 33
#define PAUSE_ID_QUITGAME 35
#define PAUSE_ID_CONTROLLERSETUP 36
#define PAUSE_ID_REDEFINECONTROLS 37
#define PAUSE_ID_FOOTVEHICLECONTROLS 38
#define PAUSE_ID_MOUSESETTINGS 39
#define PAUSE_ID_JOYPADSETTINGS 40
#define PAUSE_ID_MAIN 41

native ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle);
native SetRadioStationForPlayer(playerid, stationid);
native SetWaveHeightForPlayer(playerid, Float:height);
native SetWaveHeightForAll(Float:height);
native TogglePauseMenuAbility(playerid, bool:toggle);
native IsPlayerInPauseMenu(playerid);
native SetPlayerHUDComponentColour(playerid, componentid, colour);

forward OnPlayerOpenPauseMenu(playerid);
forward OnPlayerClosePauseMenu(playerid);
forward OnPlayerEnterPauseSubmenu(playerid, from, to);