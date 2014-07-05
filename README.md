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
  
Callbacks:
  
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
  * OnPlayerStunt(playerid, money)

Experimental:

  * SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size, inner_colour = 0xFF0000FF, middle_colour = 0xFF0000FF, outer_colour = 0xFF0000FF)
  * SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, colour = 0xFF0000FF)
  * SetPlayerCheckpointColour(playerid, inner, middle, outer)
  * SetPlayerRaceCheckpointColour(playerid, colour)
