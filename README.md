SA-MP+
==========

A client modification that uses SA-MP's plugin SDK to interact with the server and add new features

Download
---------
  * [PAWN include.](Build/sampp.inc?raw=true)
  * [Source code.](https://github.com/v01d-/SA-MP-Plus/archive/master.zip)

####Windows:
  * [Server plugin.](Build/Release/sampp_server.dll?raw=true)
  * [Client addon.](Build/Release/sampp_client.asi?raw=true)

####Linux:
  * [Server plugin.](Build/Release/sampp_server.so?raw=true)

Installation (Client)
---------
  * Download and install an [ASI Loader for GTA San Andreas](http://www.gtagarage.com/mods/show.php?id=8321) if you don't have one,
  * Place the [sampp_client.asi](Build/Release/sampp_client.asi?raw=true) file in your GTA:SA's folder, along with *gta_sa.exe*.

Installation (Server)
---------
  * Download the [Windows](Build/Release/sampp_server.dll?raw=true) or [Linux](Build/Release/sampp_server.so?raw=true) server plugin.
  * Place the file in the *plugins* folder of your server.
  * Add the plugin to your server's *server.cfg*.

Functions
---------
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
  * SetPlayerRaceCheckpointEx(playerid, type, Float:x, Float:y, Float:z, Float:point_x, Float:point_y, Float:point_z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0);
  * SetPlayerCheckpointColour(playerid, colour)
  * SetPlayerRaceCheckpointColour(playerid, colour)

####Callbacks:
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
  * OnDriverDriveByShot(playerid)
  * OnPlayerStunt(playerid, stuntid, money, details[])
  * OnPlayerResolutionChange(playerid, X, Y)

####Experimental/Unstable:
  * SetPlayerCheckpointEx(playerid, Float:x, Float:y, Float:z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0, bool:check_z = true);

Compilation
---------

####Windows:
  * Open the provided solution file (.sln) in Visual Studio.
  * Make sure to change the target to *"Release"* unless you want a build with debug symbols.

####Linux:
  * Open a terminal and use the following commands:
```sh
cd Build
mkdir Temp
cd Temp
cmake ../..
make
```
  * Pass the *-DSAMPP_DEBUG=1* parameter to CMake for generating a build with debug symbols.
