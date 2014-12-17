#pragma once

#include <DirectX/d3d9.h>
#include <SAMP+/client/CVector.h>

#define CHECKPOINT_ADDR 0xC7DD58
#define CHECKPOINT_PLACE 0x725120
#define CHECKPOINT_OFFSET 0xA0
#define MAX_CHECKPOINTS 32

#define RACE_CHECKPOINT_ADDR 0xC7F158
#define RACE_CHECKPOINT_OFFSET 0x38
#define MAX_RACE_CHECKPOINTS 32

typedef void* (*PlaceCheckpoint_t)(unsigned int, unsigned short, CVector*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short, float, short, float, float, float, bool);


class CGame
{
public:

	static void OnInitialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice, HWND hWindow);
	static void OnLoad();
	static void OnUnload();
	
	//DirectX
	static void PreDeviceReset();
	static void PostDeviceReset();
	static void PreEndScene();
	static void PostEndScene();
	static void BeginScene();

	static bool IsLoaded();
	static bool InMainMenu();
	static bool HUDVisible();
	static bool InMenu();
	static bool Paused();
	static bool Playing();
	static unsigned int IsFrozen();
	static unsigned int UsePedAnims();
	static BYTE GetVersion();

	static int OnCursorMove(int iX, int iY);
	static BYTE OnPauseMenuChange(BYTE bFromMenuID, BYTE bToMenuID);
	static void OnWorldCreate();
	static void OnPauseMenuToggle(bool toggle);
	static void OnResolutionChange(UINT16 X, UINT16 Y);
	static void OnRadioChange(BYTE id);
	static void OnMouseClick(BYTE type, UINT16 X, UINT16 Y);
	static void OnDrinkSprunk();
	static void OnEnterWater();
	static void OnLeaveWater();

	static void UnprotectMemory();
	static void SetRadioStation(unsigned long ulStation);
	static void SetWaveHeight(float fLength);
	static void SetHUDVisible(bool bVisible);
	static void ToggleDriveOnWater(bool toggle);
	static void SetGameSpeed(float speed);
	static void SetBlurIntensity(int intensity);
	static void ToggleFrozen(bool toggle);
	static void SetPedAnims(bool toggle);
	static void ToggleSwitchReload(bool toggle);
	static void SetAircraftMaxHeight(float height);
	static void SetJetpackMaxHeight(float height);
	static void ToggleVehicleBlips(bool toggle);
	static void ToggleInfiniteOxygen(bool toggle);
	static void ToggleWaterBuoyancy(bool toggle);

	static bool VehicleBlips;
	static bool InPauseMenu;
	static bool PauseMenuEnabled;
	static bool RecreateMarkers;
	static int ClipAmmo[50];
	static float AircraftMaxHeight;
	static bool inWater;

	static void Present();
	static int X, Y;


private:
	static bool m_bGameLoaded;
	static bool Frozen;
	static bool PedAnims;

	
};
