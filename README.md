SA-MP+
==========

A client modification that uses SA-MP's plugin SDK to interact with the server and add new features

  Functions:
  
  * ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle)
  * SetRadioStationForPlayer(playerid, stationid)
  * SetWaveHeightForPlayer(playerid, Float:height)
  * SetWaveHeightForAll(Float:height)
  * TogglePauseMenuAbility(playerid, bool:toggle)
  * IsPlayerInPauseMenu(playerid)
  * SetPlayerHUDComponentColour(playerid, componentid, colour)
  * TogglePlayerAction(playerid, actionid, bool:toggle)
  * SetPlayerNoReload(playerid, bool:toggle)
  * GetPlayerResolution(playerid, &width, &height)
  * SetPlayerBlurIntensity(playerid, intensity);
  * SetPlayerGameSpeed(playerid, Float:speed);
  * TogglePlayerDriveOnWater(playerid, bool:toggle);
  * TogglePlayerFrozen(playerid, bool:toggle);
  * SetPlayerPedAnims(playerid, bool:toggle);
  * TogglePlayerSwitchReload(playerid, bool:toggle);
  * TogglePlayerInfiniteRun(playerid, bool:toggle);

Callbacks:
  
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
  * OnDriverDriveByShot(playerid)
  * OnPlayerStunt(playerid, stuntid, money, details[])
  * OnPlayerResolutionChange(playerid, X, Y)

Experimental:

  * SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size, inner_colour = 0xFF0000FF, middle_colour = 0xFF0000FF, outer_colour = 0xFF0000FF)
  * SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, colour = 0xFF0000FF)
  * SetPlayerCheckpointColour(playerid, inner, middle, outer)
  * SetPlayerRaceCheckpointColour(playerid, colour)
