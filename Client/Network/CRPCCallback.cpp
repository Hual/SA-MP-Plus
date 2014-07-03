#include "CRPCCallback.h"
#include "../Game/CHUD.h"
#include "../Game/CGame.h"
#include "../Game/Hooks/Proxy/CJmpProxy.h"

void CRPCCallback::Initialize()
{
	RPC::Add(eRPC::TOGGLE_HUD_COMPONENT, ToggleHUDComponent);
	RPC::Add(eRPC::SET_RADIO_STATION, SetRadioStation);
	RPC::Add(eRPC::SET_WAVE_HEIGHT, SetWaveHeight);
	RPC::Add(eRPC::TOGGLE_PAUSE_MENU, TogglePauseMenu);
	RPC::Add(eRPC::SET_HUD_COMPONENT_COLOUR, SetHUDComponentColour);
	//RPC::Add(eRPC::SET_CHECKPOINT_COLOUR, SetCheckpointColour);
	//RPC::Add(eRPC::SET_RACE_CHECKPOINT_COLOUR, SetRaceCheckpointColour);
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