#include "CRPCCallback.h"
#include "Game/CHUD.h"
#include "Game/CGame.h"

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::TOGGLE_HUD_COMPONENT, ToggleHUDComponent);
	CRPC::Add(eRPC::SET_RADIO_STATION, SetRadioStation);
	CRPC::Add(eRPC::SET_WAVE_HEIGHT, SetWaveHeight);
	CRPC::Add(eRPC::TOGGLE_PAUSE_MENU, TogglePauseMenu);
}

RPC_CALLBACK CRPCCallback::ToggleHUDComponent(RakNet::BitStream& bsData, int iExtra)
{
	unsigned char ucComponent, bToggle;

	if (bsData.Read(ucComponent) && bsData.Read(bToggle))
		CHUD::ToggleComponent(ucComponent, bToggle);

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