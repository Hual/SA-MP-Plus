#include "CRPCCallback.h"
#include "Game/CHUD.h"
#include "Game/CGame.h"

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::TOGGLE_HUD_COMPONENT, TogglePlayerHUDComponent);
	CRPC::Add(eRPC::SET_RADIO_STATION, SetPlayerRadioStation);
	CRPC::Add(eRPC::SET_WAVE_HEIGHT, SetPlayerWaveHeight);
}

RPC_CALLBACK CRPCCallback::TogglePlayerHUDComponent(RakNet::BitStream& bsData)
{
	unsigned char ucComponent, bToggle;

	if (bsData.Read(ucComponent) && bsData.Read(bToggle))
		CHUD::ToggleComponent(ucComponent, bToggle);

}

RPC_CALLBACK CRPCCallback::SetPlayerRadioStation(RakNet::BitStream& bsData)
{
	unsigned char ucStation;

	if (bsData.Read(ucStation))
		CGame::SetRadioStation(ucStation);
}

RPC_CALLBACK CRPCCallback::SetPlayerWaveHeight(RakNet::BitStream& bsData)
{
	float fHeight;

	if (bsData.Read(fHeight))
		CGame::SetWaveHeight(fHeight);

}