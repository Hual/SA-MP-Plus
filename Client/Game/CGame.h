#pragma once

#include <DirectX/d3d9.h>
#include "CVector.h"

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
	static void PreDeviceReset();
	static void PostDeviceReset();
	static void PreEndScene();
	static void PostEndScene();
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
	static void OnResolutionChange(int X, int Y);

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

	static bool InPauseMenu;
	static bool PauseMenuEnabled;
	static bool RecreateMarkers;
	static int ClipAmmo[50];
	static float AircraftMaxHeight;
	
private:
	static bool m_bGameLoaded;
	static bool Frozen;
	static bool PedAnims;
};
