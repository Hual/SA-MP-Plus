#pragma once

#include <SAMP+/client/Client.h>
#include <SAMP+/client/CPoint2D.h>
#include <SAMP+/client/CGame.h>

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>

#include "CSprite.h"
#include "Box.h"
#include "resource.h"

class CGraphics
{
public:
	static VOID UpdateScreenResolution();
	static VOID SetScreenResolution(UINT uiWidth, UINT uiHeight);
	static CPoint2D& GetScreenResolution();
	static HRESULT ToggleCursor(bool toggle);
	static bool IsCursorEnabled();
	static void Initialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice);
	static void OnReset();

	//DirectX
	static void PreEndScene();
	static void PostDeviceReset();
	static void BeginScene();
	static void CleanUp();

private:
	static CPoint2D m_pResolution;
	static IDirect3D9* m_pDirect3D;
	static IDirect3DDevice9* m_pDevice;
	static bool m_bCursorEnabled;

	static Sprite* logo;
	static Box* box;

};