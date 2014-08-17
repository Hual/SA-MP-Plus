#pragma once

#include <SAMP+/client/CVector.h>

#include <SAMP+/client/Proxy/CD3D9DeviceProxy.h>
#include <SAMP+/client/Proxy/CD3D9Proxy.h>
#include <SAMP+/client/Proxy/CDInput8DeviceProxy.h>
#include <SAMP+/client/Proxy/CDInput8Proxy.h>
#include <SAMP+/client/Proxy/CMessageProxy.h>

typedef IDirect3D9 *(WINAPI* Direct3DCreate9_t)(UINT);
typedef HRESULT(WINAPI* DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
typedef BOOL(WINAPI* SetCursorPos_t)(int, int);

class CHooks
{
public:
	static void Apply();
	static void InstallJmp();
	static void Remove();

private:
	static Direct3DCreate9_t  m_pfnDirect3DCreate9;
	static DirectInput8Create_t m_pfnDirectInput8Create;
	static SetCursorPos_t  m_pfnSetCursorPos;

	static HRESULT HOOK_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
	static IDirect3D9* WINAPI HOOK_Direct3DCreate9(UINT SDKVersion);
	static BOOL WINAPI HOOK_SetCursorPos(int iX, int iY);

	static void ApplyDirectInput();
	static void RemoveDirectInput();
	static void ApplyDirect3D();
	static void RemoveDirect3D();
	static void ApplyCursorPos();
	static void RemoveCursorPos();
	static void InstallPatches();

};
