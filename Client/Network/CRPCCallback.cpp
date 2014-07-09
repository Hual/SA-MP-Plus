#include "CRPCCallback.h"
#include "Game/CHUD.h"
#include "Game/CGame.h"
#include "Game/Hooks/Proxy/CJmpProxy.h"
#include "Game/CLocalPlayer.h"

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::TOGGLE_HUD_COMPONENT, ToggleHUDComponent);
	CRPC::Add(eRPC::SET_RADIO_STATION, SetRadioStation);
	CRPC::Add(eRPC::SET_WAVE_HEIGHT, SetWaveHeight);
	CRPC::Add(eRPC::TOGGLE_PAUSE_MENU, TogglePauseMenu);
	CRPC::Add(eRPC::SET_HUD_COMPONENT_COLOUR, SetHUDComponentColour);
	//CRPC::Add(eRPC::SET_CHECKPOINT_COLOUR, SetCheckpointColour);
	//CRPC::Add(eRPC::SET_RACE_CHECKPOINT_COLOUR, SetRaceCheckpointColour);
	CRPC::Add(eRPC::TOGGLE_ACTION, ToggleAction);
	CRPC::Add(eRPC::SET_CLIP_AMMO, SetAmmoInClip);
	CRPC::Add(eRPC::SET_NO_RELOAD, SetNoReload);
	CRPC::Add(eRPC::SET_BLUR_INTENSITY, SetBlur);
	CRPC::Add(eRPC::TOGGLE_DRIVE_ON_WATER, DriveOnWater);
	CRPC::Add(eRPC::SET_GAME_SPEED, SetSpeed);
	CRPC::Add(eRPC::TOGGLE_PLAYER_FROZEN, SetFrozen);
	CRPC::Add(eRPC::SET_PLAYER_ANIMS, SetAnims);
	CRPC::Add(eRPC::TOGGLE_SWITCH_RELOAD, ToggleSwitchReload);

	CGame::OnResolutionChange(*(int*)0x0C9C040, *(int*)0x0C9C044);
}

RPC_CALLBACK CRPCCallback::ToggleHUDComponent(RakNet::BitStream& bsData, int iExtra)
{
	unsigned char ucComponent, bToggle;

	if (bsData.Read(ucComponent) && bsData.Read(bToggle))
		CHUD::ToggleComponent(ucComponent, bToggle);

}

RPC_CALLBACK CRPCCallback::SetHUDComponentColour(RakNet::BitStream& bsData, int iExtra)
{
	unsigned char ucComponent;
	DWORD dwColour;

	if (bsData.Read(ucComponent) && bsData.Read(dwColour))
	{
		RakNet::BitStream::ReverseBytesInPlace((unsigned char*)&dwColour, sizeof(DWORD));

		CHUD::SetComponentColour(ucComponent, dwColour);
	}
}

RPC_CALLBACK CRPCCallback::SetRadioStation(RakNet::BitStream& bsData, int iExtra)
{
	unsigned char ucStation;

	if (bsData.Read(ucStation))
		CGame::SetRadioStation(ucStation);
}

RPC_CALLBACK CRPCCallback::SetWaveHeight(RakNet::BitStream& bsData, int iExtra)
{
	float fHeight;

	if (bsData.Read(fHeight))
		CGame::SetWaveHeight(fHeight);

}

RPC_CALLBACK CRPCCallback::TogglePauseMenu(RakNet::BitStream& bsData, int iExtra)
{
	unsigned char ucToggle;

	if (bsData.Read(ucToggle))
		CGame::PauseMenuEnabled = ucToggle;

}

// TODO: fix checkpoint colours
/*RPC_CALLBACK CRPCCallback::SetCheckpointColour(RakNet::BitStream& bsData, int iExtra)
{
	DWORD dwColour[3];

	if (bsData.Read(dwColour[0]) && bsData.Read(dwColour[1]) && bsData.Read(dwColour[2]))
	{
		CMem::PutSingle<DWORD>(0xC7DD58 + 0x58, dwColour[0]);
		CMem::PutSingle<DWORD>(0xC7DD58 + 0xA0 + 0xA0 + 0xA0 + 0x58, dwColour[1]);
		CMem::PutSingle<DWORD>(0xC7DD58 + 0xA0 + 0xA0 + 0xA0 + 0xA0 + 0x58, dwColour[2]);
	}
}

RPC_CALLBACK CRPCCallback::SetRaceCheckpointColour(RakNet::BitStream& bsData, int iExtra)
{
	DWORD dwColour;

	if (bsData.Read(dwColour))
	{
		CJmpProxy::RaceCheckpointByteRed = (BYTE)(dwColour & 0xFF);
		CJmpProxy::RaceCheckpointByteGreen = (BYTE)(dwColour >> 8 & 0xFF);
		CJmpProxy::RaceCheckpointByteBlue = (BYTE)(dwColour >> 16 & 0xFF);

		CMem::PutSingle<DWORD>(0xC7F158 + 0x8, dwColour);
	}
}
*/

RPC_CALLBACK CRPCCallback::ToggleAction(RakNet::BitStream& bsData, int iExtra)
{
	BYTE action;
	bool bToggle;

	if (bsData.Read(action) && bsData.Read(bToggle))
	{
		CLog::Write("ToggleAction %i %i", action, bToggle);
		CLocalPlayer::SetActionEnabled(action, bToggle);
	}

}

RPC_CALLBACK CRPCCallback::SetAmmoInClip(RakNet::BitStream& bsData, int iExtra)
{

	DWORD dwNewAmmo;
	BYTE bSlotId;

	if (bsData.Read(bSlotId) && bsData.Read(dwNewAmmo))
	{
		CLocalPlayer::SetClipAmmo(bSlotId, dwNewAmmo);
	}
}

RPC_CALLBACK CRPCCallback::SetNoReload(RakNet::BitStream& bsData, int iExtra)
{

	bool toggle;

	if (bsData.Read(toggle))
	{
		CLocalPlayer::SetNoReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetSpeed(RakNet::BitStream& bsData, int iExtra)
{

	float speed;

	if (bsData.Read(speed))
	{
		CGame::SetGameSpeed(speed);
	}
}

RPC_CALLBACK CRPCCallback::DriveOnWater(RakNet::BitStream& bsData, int iExtra)
{
	bool toggle;
	if (bsData.Read(toggle)) 
	{
		CGame::ToggleDriveOnWater(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetBlur(RakNet::BitStream& bsData, int iExtra)
{
	int intensity;
	if (bsData.Read(intensity))
	{
		CGame::SetBlurIntensity(intensity);
	}
}

RPC_CALLBACK CRPCCallback::SetFrozen(RakNet::BitStream& bsData, int iExtra)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleFrozen(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAnims(RakNet::BitStream& bsData, int iExtra)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::SetPedAnims(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleSwitchReload(RakNet::BitStream& bsData, int iExtra)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleSwitchReload(toggle);
	}
}