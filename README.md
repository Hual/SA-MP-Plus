SA-MP+
==========

A client modification that uses SA-MP's plugin SDK to interact with the server and add new features

  Functions:
  
  * ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle);
  * SetRadioStationForPlayer(playerid, stationid);
  * SetWaveHeightForPlayer(playerid, Float:height);
  * SetWaveHeightForAll(Float:height);
  * TogglePauseMenuAbility(playerid, bool:toggle);
  * IsPlayerInPauseMenu(playerid);
  * SetPlayerHUDComponentColour(playerid, componentid, colour);
  * TogglePlayerAction(playerid, actionid, bool:toggle);
  * SetPlayerNoReload(playerid, bool:toggle);
  * GetPlayerResolution(playerid, &width, &height);
  * SetPlayerBlurIntensity(playerid, intensity);
  * SetPlayerGameSpeed(playerid, Float:speed);
  * TogglePlayerDriveOnWater(playerid, bool:toggle);
  * TogglePlayerFrozen(playerid, bool:toggle);
  * SetPlayerPedAnims(playerid, bool:toggle);
  * TogglePlayerSwitchReload(playerid, bool:toggle);
  * TogglePlayerInfiniteRun(playerid, bool:toggle);
  * SetPlayerAircraftHeight(playerid, Float:height);
  * Float:GetPlayerAircraftHeight(playerid);
  * SetPlayerJetpackHeight(playerid, Float:height);
  * Float:GetPlayerJetpackHeight(playerid);
  * bool:IsUsingSAMPP(playerid);

Callbacks:
  
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
  * OnDriverDriveByShot(playerid)
  * OnPlayerStunt(playerid, stuntid, money, details[])
  * OnPlayerResolutionChange(playerid, X, Y)

Experimental:

  * SetPlayerCheckpointEx(playerid, Float:x, Float:y, Float:z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0, bool:check_z = true);
  * SetPlayerRaceCheckpointEx(playerid, type, Float:x, Float:y, Float:z, Float:point_x, Float:point_y, Float:point_z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0);
  * SetPlayerCheckpointColour(playerid, colour)
  * SetPlayerRaceCheckpointColour(playerid, colour)
