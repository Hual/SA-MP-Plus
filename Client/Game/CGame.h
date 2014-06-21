#pragma once

#include <DirectX/d3d9.h>

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

	static int OnCursorMove(int iX, int iY);
	static BYTE OnPauseMenuChange(BYTE bFromMenuID, BYTE bToMenuID);
	static void OnWorldCreate();
	static void OnPauseMenuToggle(bool toggle);

	static void UnprotectMemory();
	static void SetRadioStation(unsigned long ulStation);
	static void SetWaveHeight(float fLength);
	static void SetHUDVisible(bool bVisible);

	static bool InPauseMenu;
	static bool PauseMenuEnabled;

private:
	static bool m_bGameLoaded;

};