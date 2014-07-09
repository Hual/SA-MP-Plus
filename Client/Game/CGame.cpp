#include <stdafx.h>
#include "CHUD.h"
#include "CGame.h"
#include "CGraphics.h"
#include "CCmdlineParams.h"
#include "Hooks\Proxy\CJmpProxy.h"
#include "../Network/Network.h"
#include "../Shared/Network/CRPC.h"
#include "Utility/CSystem.h"

bool CGame::m_bGameLoaded;
bool CGame::InPauseMenu;
bool CGame::PauseMenuEnabled;
bool CGame::Frozen;
bool CGame::PedAnims;
int CGame::ClipAmmo[50];

void CGame::OnInitialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice, HWND hWindow)
{
	m_bGameLoaded = false;
	InPauseMenu = false;
	PauseMenuEnabled = true;

	CGraphics::Initialize(pDirect3D, pDevice);
}

void CGame::OnLoad()
{
	if (!CCmdlineParams::ArgumentExists("d") && CCmdlineParams::ArgumentExists("c"))
	{
		CSystem::GetLoadedModules();
		CGame::UnprotectMemory();
		Network::Initialize(CCmdlineParams::GetArgumentValue("h"), atoi(CCmdlineParams::GetArgumentValue("p").c_str()) + 1);
		Network::Connect();
		CHUD::Initialize();

		/*for (int i = 0; i < sizeof(50); ++i) {
			CGame::ClipAmmo[i] = 7;
		}*/
	}
}

void CGame::OnUnload()
{

}

int CGame::OnCursorMove(int iX, int iY)
{
	return false;
}

void CGame::PreDeviceReset()
{
	CGraphics::OnReset();
}

BYTE CGame::OnPauseMenuChange(BYTE bFromMenuID, BYTE bToMenuID)
{
	RakNet::BitStream bitStream;
	bitStream.Write(bFromMenuID);
	bitStream.Write(bToMenuID);

	Network::SendRPC(eRPC::ON_PAUSE_MENU_CHANGE, &bitStream);

	return bToMenuID;
}

void CGame::PostDeviceReset()
{
	
}

void CGame::PreEndScene()
{
	/*if (IsLoaded())
	{
		//TODO: stuff???
	}*/

	CGraphics::PreEndScene();
}

void CGame::PostEndScene()
{
	/*if (!InMainMenu() && !IsLoaded())
	{

	}*/
}

// crash
void CGame::OnWorldCreate()
{
	OnLoad();
	m_bGameLoaded = true;
}

void CGame::OnResolutionChange(int X, int Y)
{
	RakNet::BitStream bitStream;
	bitStream.Write(X);
	bitStream.Write(Y);

	Network::SendRPC(eRPC::ON_RESOLUTION_CHANGE, &bitStream);
}

void CGame::OnPauseMenuToggle(bool toggle)
{
	InPauseMenu = toggle;

	RakNet::BitStream bitStream;
	bitStream.Write(CGame::InPauseMenu);

	Network::SendRPC(eRPC::ON_PAUSE_MENU_TOGGLE, &bitStream);
}

bool CGame::IsLoaded()
{
	return m_bGameLoaded;
}

bool CGame::InMainMenu()
{
	return CMem::Get<bool>(0xBA6831);
}

bool CGame::Paused()
{
	return CMem::Get<bool>(0xB7CB49);
}

bool CGame::InMenu()
{
	return CMem::Get<bool>(0xBA67A4);
}

bool CGame::Playing()
{
	return IsLoaded() && !InMainMenu() && !Paused() && !InMenu();
}

bool CGame::HUDVisible()
{
	return CMem::Get<bool>(0xA444A0);
}

void CGame::SetHUDVisible(bool iVisible)
{
	CMem::PutSingle<bool>(0xA444A0, iVisible);
}

void CGame::SetRadioStation(unsigned long ulStation)
{
	((int(__thiscall*)(int, int, char, int, int))0x4EB3C0)(0x8CB6F8, ulStation, 0, 0, 0);
}

void CGame::SetWaveHeight(float fHeight)
{
	unsigned short ulOpcodes = 0xD8DD;
	CMem::Set(0x0072C667, 0x90, 0x04);
	CMem::Put<unsigned char>(0x72C665, &ulOpcodes, 2);
	CMem::Set(0x0072C659, 0x90, 0x0A);
	CMem::PutSingle<float>(0x00C812E8, fHeight);
}

void CGame::UnprotectMemory()
{
	CMem::Unprotect(0x72C659, 0x12);
	CMem::Unprotect(0xC812E8, sizeof(float));
	//CMem::Unprotect(0x00C7F158, 38 * NUM_CHECKPOINTS);
}

void CGame::SetBlurIntensity(int intensity) 
{
	CMem::PutSingle<BYTE>(0x0704E8A, 0xE8); // call
	CMem::PutSingle<BYTE>(0x0704E8B, 0x11);
	CMem::PutSingle<BYTE>(0x0704E8C, 0xE2);
	CMem::PutSingle<BYTE>(0x0704E8D, 0xFF);
	CMem::PutSingle<BYTE>(0x0704E8E, 0xFF);

	CMem::PutSingle<int>(0x8D5104, intensity);
}

void CGame::SetGameSpeed(float speed) 
{
	CMem::PutSingle<float>(0xB7CB64, speed);
}

void CGame::ToggleDriveOnWater(bool toggle) 
{
	CMem::PutSingle<BYTE>(0x969152, (BYTE)toggle);
}

void CGame::ToggleFrozen(bool toggle) 
{
	Frozen = toggle;
}

void CGame::SetPedAnims(bool toggle)
{
	PedAnims = toggle;
}

unsigned int CGame::IsFrozen() 
{
	return (unsigned int)Frozen;
}

unsigned int CGame::UsePedAnims()
{
	return (unsigned int)PedAnims;
}


void CGame::ToggleSwitchReload(bool toggle) 
{
	if (!toggle) 
	{
		memcpy((void*)0x060B4FA, "\x90\x90\x90\x90\x90\x90", 6);
	}
	else 
	{
		memcpy((void*)0x060B4FA, "\x89\x88\xA8\x05\x00\x00", 6); // mov [eax+000005A8],ecx
	}
}