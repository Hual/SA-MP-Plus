#pragma once

#include <DirectX/d3d9.h>

#define NUM_CHECKPOINTS 2

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

	static bool InPauseMenu;
	static bool PauseMenuEnabled;
	static int ClipAmmo[50];
	
private:
	static bool m_bGameLoaded;
	static bool Frozen;
	static bool PedAnims;
	
};