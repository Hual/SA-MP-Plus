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

#define HUD_COMPONENT_ALL 0
#define HUD_COMPONENT_AMMO 1
#define HUD_COMPONENT_WEAPON 2
#define HUD_COMPONENT_HEALTH 3
#define HUD_COMPONENT_BREATH 4
#define HUD_COMPONENT_ARMOUR 5
#define HUD_COMPONENT_MINIMAP 6
#define HUD_COMPONENT_CROSSHAIR 7
#define HUD_COMPONENT_MONEY 8

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

native ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle);
native SetRadioStationForPlayer(playerid, stationid);
native SetWaveHeightForPlayer(playerid, Float:height);
native SetWaveHeightForAll(Float:height);
