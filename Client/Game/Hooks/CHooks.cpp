#include <stdafx.h>
#include "CHooks.h"
#include "../Utility/CLog.h"
#include <Detours/detours.h>
#include "Proxy/CJmpProxy.h"

Direct3DCreate9_t  CHooks::m_pfnDirect3DCreate9 = NULL;
DirectInput8Create_t CHooks::m_pfnDirectInput8Create = NULL;
SetCursorPos_t  CHooks::m_pfnSetCursorPos = NULL;

void CHooks::Apply()
{
	ApplyCursorPos();
	ApplyDirect3D();
	ApplyDirectInput();
	InstallJmp();
	InstallPatches();
}

void CHooks::Remove()
{
	RemoveDirectInput();
	RemoveDirect3D();
	RemoveCursorPos();
}

void CHooks::InstallJmp()
{
	CMem::InstallJmp(0x57377D, CJmpProxy::MenuAction1, CJmpProxy::MenuJumpBack1, 6);
	CMem::InstallJmp(0x5736CF, CJmpProxy::MenuAction2, CJmpProxy::MenuJumpBack2, 6);
	CMem::InstallJmp(0x57C2F7, CJmpProxy::MenuAction3, CJmpProxy::MenuJumpBack3, 6);
	CMem::InstallJmp(0x576C27, CJmpProxy::MenuSwitch, CJmpProxy::MenuSwitchJumpBack, 6, 8);
	CMem::InstallJmp(0x52B811, CJmpProxy::WorldCreate, CJmpProxy::WorldCreateJumpBack, 6);
	//TODO: fix checkpoints
	//CMem::InstallJmp(0x722F1A, CJmpProxy::RaceCheckpointUnknown, CJmpProxy::RaceCheckpointUnknownJumpBack, 7, 25);
	CMem::InstallJmp(0x58F4A2, CJmpProxy::PositiveMoneyDraw, CJmpProxy::PositiveMoneyDrawJumpBack, 8);
	//CMem::InstallJmp(0x58EBDA, CJmpProxy::UnknownMoneyDraw1, CJmpProxy::UnknownMoneyDraw1JumpBack, 8);
	CMem::InstallJmp(0x58F4E4, CJmpProxy::NegativeMoneyDraw, CJmpProxy::NegativeMoneyDrawJumpBack, 8);
	CMem::InstallJmp(0x589117, CJmpProxy::ArmourBarDraw, CJmpProxy::ArmourBarDrawJumpBack, 6);
	CMem::InstallJmp(0x589344, CJmpProxy::HealthBarDraw, CJmpProxy::HealthBarDrawJumpBack, 8);
	CMem::InstallJmp(0x589202, CJmpProxy::BreathBarDraw, CJmpProxy::BreathBarDrawJumpBack, 6);
	CMem::InstallJmp(0x589608, CJmpProxy::AmmoDraw, CJmpProxy::AmmoDrawJumpBack, 8);
	CMem::InstallJmp(0x58DDD9, CJmpProxy::WantedLevelDraw, CJmpProxy::WantedLevelDrawJumpBack, 8);
	CMem::InstallJmp(0x4E9FA1, CJmpProxy::ActiveRadioDraw);
	CMem::InstallJmp(0x4E9FB2, CJmpProxy::InactiveRadioDraw, CJmpProxy::InactiveRadioDrawJumpBack, 7);
	//TODO: unknown active draw (71A220)
	CMem::InstallJmp(0x60F583, CJmpProxy::DriveByUnknown, CJmpProxy::DriveByUnknownJumpBack, 6);
	CMem::InstallJmp(0x469941, CJmpProxy::StuntBonus, CJmpProxy::StuntBonusJumpBack, 6);
	CMem::InstallJmp(0x69E360, CJmpProxy::StuntInfo, CJmpProxy::StuntInfoJumpBack, 58);
	CMem::InstallJmp(0x07F6CFD, CJmpProxy::ChangeResolution, CJmpProxy::ChangeResolutionJumpBack, 15);
	CMem::InstallJmp(0x0609560, CJmpProxy::FreezePed, CJmpProxy::FreezePedJumpBack, 6);
	CMem::InstallJmp(0x06B4CC0, CJmpProxy::FreezeVehicle, CJmpProxy::FreezeVehicleJumpBack, 6);
	CMem::InstallJmp(0x0609A1F, CJmpProxy::PedAnims, CJmpProxy::PedAnimsJumpBack, 7);
	//CMem::InstallJmp(0x060B4F4, CJmpProxy::SwitchWeapon, CJmpProxy::SwitchWeaponJumpBack, 6);
}

void CHooks::InstallPatches()
{
	CMem::Cpy((void*)0x0401190, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 every frame
	CMem::Cpy((void*)0x060CD41, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10); // NOP SetGameSpeed to 1.0 on player death
}

void CHooks::ApplyDirectInput()
{
	if (!m_pfnDirectInput8Create)
		m_pfnDirectInput8Create = (DirectInput8Create_t)DetourFunction(DetourFindFunction("dinput8.dll", "DirectInput8Create"), (BYTE*)CHooks::HOOK_DirectInput8Create);
}

void CHooks::RemoveDirectInput()
{
	if (m_pfnDirectInput8Create)
		DetourRemove((BYTE*)m_pfnDirectInput8Create, (BYTE*)HOOK_DirectInput8Create);
}

void CHooks::ApplyDirect3D()
{
	if (!m_pfnDirect3DCreate9)
		m_pfnDirect3DCreate9 = (Direct3DCreate9_t)DetourFunction(DetourFindFunction("d3d9.dll", "Direct3DCreate9"), (BYTE*)HOOK_Direct3DCreate9);
}

void CHooks::RemoveDirect3D()
{
	if (m_pfnDirect3DCreate9)
		DetourRemove((BYTE*)m_pfnDirect3DCreate9, (BYTE*)HOOK_Direct3DCreate9);
}

void CHooks::ApplyCursorPos()
{
	if(!m_pfnSetCursorPos)
		m_pfnSetCursorPos = (SetCursorPos_t)DetourFunction(DetourFindFunction("user32.dll", "SetCursorPos"), (BYTE*)HOOK_SetCursorPos);
}

void CHooks::RemoveCursorPos()
{
	if (m_pfnSetCursorPos)
		DetourRemove((BYTE*)m_pfnSetCursorPos, (BYTE*)HOOK_SetCursorPos);
}

HRESULT CHooks::HOOK_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, void** ppvOut, IUnknown* punkOuter)
{
	HRESULT hr = m_pfnDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	IDirectInput8A* pDInput = (IDirectInput8A*)*ppvOut;
	CDInput8Proxy* pDInputHook = new CDInput8Proxy(pDInput);
	*ppvOut = pDInputHook;
	return hr;
}

IDirect3D9* WINAPI CHooks::HOOK_Direct3DCreate9(UINT SDKVersion)
{
	IDirect3D9* Direct3D = m_pfnDirect3DCreate9(SDKVersion);
	IDirect3D9* Mine_Direct3D = new CD3D9Proxy(Direct3D);
	return Mine_Direct3D;
}

BOOL WINAPI CHooks::HOOK_SetCursorPos(int iX, int iY)
{
	if (CMessageProxy::OnSetCursorPos(iX, iY))
		m_pfnSetCursorPos(iX, iY);
		
	return false;
}
