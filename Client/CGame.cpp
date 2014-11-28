#include <SAMP+/CRPC.h>
#include <SAMP+/client/Client.h>
#include <SAMP+/client/CHUD.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/CGraphics.h>
#include <SAMP+/client/CCmdlineParams.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>
#include <SAMP+/client/Network.h>
#include <SAMP+/client/CSystem.h>


bool CGame::m_bGameLoaded;
bool CGame::InPauseMenu;
bool CGame::PauseMenuEnabled;
bool CGame::Frozen;
bool CGame::PedAnims;
bool CGame::RecreateMarkers = false;
bool CGame::VehicleBlips = true;
float CGame::AircraftMaxHeight;
bool CGame::inWater = false;

int CGame::X, CGame::Y;

int CGame::ClipAmmo[50];


void CGame::OnInitialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice, HWND hWindow)
{
	m_bGameLoaded = false;
	InPauseMenu = false;
	PauseMenuEnabled = true;

	X = 5;
	Y = 5;

//	box.Init(pDevice, 100, 60, 1366/2, 768/2, D3DCOLOR_ARGB(25, 255, 255, 255));

	CGraphics::Initialize(pDirect3D, pDevice);
}


void CGame::OnLoad()
{
	if (!CCmdlineParams::ArgumentExists("d") && CCmdlineParams::ArgumentExists("h"))
	{
		//CSystem::GetLoadedModules();
		CLog::Write("OnLoad success");
		CGame::UnprotectMemory();
		Network::Initialize(CCmdlineParams::GetArgumentValue("h"), atoi(CCmdlineParams::GetArgumentValue("p").c_str()) + 1);
		Network::Connect();
		CHUD::Initialize();
		
		CGame::SetAircraftMaxHeight(800.0f);

		/*for (int i = 0; i < sizeof(50); ++i) {
			CGame::ClipAmmo[i] = 7;
		}*/
	}
}

void CGame::OnUnload()
{
	CGraphics::CleanUp();
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
	CGraphics::PostDeviceReset();
}

void CGame::PreEndScene()
{

	if(RecreateMarkers)
	{
		for(int i = 0; i < MAX_RACE_CHECKPOINTS; ++i)
		{
			char *thisCheckpoint = (char*) (RACE_CHECKPOINT_ADDR + (i * RACE_CHECKPOINT_OFFSET));

			if(*((unsigned short*) (thisCheckpoint)) != 257)
				*((bool*) (thisCheckpoint + 2)) = true;
		}

		RecreateMarkers = false;
	}

	CGraphics::PreEndScene();
}

void CGame::PostEndScene()
{

}

void CGame::BeginScene()
{
	CGraphics::BeginScene();
}

void CGame::OnWorldCreate()
{
	if (!IsLoaded())
	{
		OnLoad();
		m_bGameLoaded = true;
	}
}

void CGame::OnResolutionChange(UINT16 X, UINT16 Y)
{
	RakNet::BitStream bitStream;
	bitStream.Write(X);
	bitStream.Write(Y);

	Network::SendRPC(eRPC::ON_RESOLUTION_CHANGE, &bitStream);
}

void CGame::OnMouseClick(BYTE type, UINT16 X, UINT16 Y)
{
	RakNet::BitStream bitStream;
	bitStream.Write(type);
	bitStream.Write(X);
	bitStream.Write(Y);

	Network::SendRPC(eRPC::ON_MOUSE_CLICK, &bitStream);
}

void CGame::OnPauseMenuToggle(bool toggle)
{
	InPauseMenu = toggle;

	RakNet::BitStream bitStream;
	bitStream.Write(CGame::InPauseMenu);

	Network::SendRPC(eRPC::ON_PAUSE_MENU_TOGGLE, &bitStream);
}

void CGame::ToggleVehicleBlips(bool toggle)
{
	VehicleBlips = toggle;
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

BYTE CGame::GetVersion()
{
	unsigned char ucA = CMem::Get<BYTE>(0x748ADD);
	unsigned char ucB = CMem::Get<BYTE>(0x748ADE);
	if (ucA == 0xFF && ucB == 0x53)
		return 1; // usa
	else if (ucA == 0x0F && ucB == 0x84)
		return 2; // eu
	else if (ucA == 0xFE && ucB == 0x10)
		return 3;

	return 0;
}

void CGame::SetAircraftMaxHeight(float height)
{
	AircraftMaxHeight = height;
}

void CGame::SetJetpackMaxHeight(float height)
{
	CMem::PutSingle<float>(0x8703D8, height);
}

void CGame::OnRadioChange(BYTE id)
{
	RakNet::BitStream bitStream;
	
	bitStream.Write(id);

	Network::SendRPC(eRPC::ON_RADIO_CHANGE, &bitStream);
}

void CGame::OnDrinkSprunk()
{
	Network::SendRPC(eRPC::ON_DRINK_SPRUNK);
}

void CGame::ToggleInfiniteOxygen(bool toggle)
{
	CMem::PutSingle<BYTE>(0x96916E, (BYTE)toggle);
}

void CGame::ToggleWaterBuoyancy(bool toggle)
{
	CMem::PutSingle <BYTE>(0x6C3F80, (BYTE) toggle);
	if (toggle)
	{
		memcpy((void*) 0x6C3F80, "\x90\x90\x90\x90\x90\x90\x90", 7); //NOP
	}
	else
	{
		memcpy((void*) 0x6C3F80, "\xC6\x87\x98\x00\x00\x00\x01", 7); //MOV BYTE PTR DS:[EDI+98],1
	}
}

void CGame::OnEnterWater()
{
	inWater = true;

	//Network::SendRPC(eRPC::ON_ENTER_WATER);
}

void CGame::OnLeaveWater()
{
	inWater = false;

	//Network::SendRPC(eRPC::ON_LEAVE_WATER);
}

void CGame::Present()
{
	//CGraphics::DrawString("Running SA-MP+ Pre-Alpha Release", 15, X, Y, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphics::DrawBox(50, 50, 100, 90, D3DCOLOR_ARGB(255, 255, 255, 255));
}