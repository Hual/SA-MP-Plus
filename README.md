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

  Callbacks:
  
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
