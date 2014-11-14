#include <SAMP+/Utility.h>
#include <SAMP+/Definitions.h>

#include <SAMP+/svr/CRPCCallback.h>
#include <SAMP+/svr/Callback.h>
#include <SAMP+/svr/Network.h>

#include <sampgdk.h>

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::ON_PAUSE_MENU_TOGGLE, CRPCCallback::PlayerPauseMenuSwitch);
	CRPC::Add(eRPC::ON_PAUSE_MENU_CHANGE, CRPCCallback::PlayerPauseMenuBrowse);
	CRPC::Add(eRPC::ON_DRIVE_BY_SHOT, CRPCCallback::PlayerDriveByShot);
	CRPC::Add(eRPC::ON_STUNT_BONUS, CRPCCallback::StuntBonus);
	CRPC::Add(eRPC::ON_RESOLUTION_CHANGE, CRPCCallback::ResolutionChange);
	CRPC::Add(eRPC::ON_MOUSE_CLICK, CRPCCallback::PlayerClick);
	CRPC::Add(eRPC::ON_RADIO_CHANGE, CRPCCallback::RadioChange);
	CRPC::Add(eRPC::ON_DRINK_SPRUNK, CRPCCallback::DrinkSprunk);
}

RPC_CALLBACK CRPCCallback::PlayerPauseMenuSwitch(RPC_ARGS)
{
	bool bOpened;

	if (bsData.Read(bOpened))
	{
		if (bOpened)
			Callback::Execute("OnPlayerOpenPauseMenu", "i", iExtra);
		else
			Callback::Execute("OnPlayerClosePauseMenu", "i", iExtra);
			
	}
}

RPC_CALLBACK CRPCCallback::PlayerPauseMenuBrowse(RPC_ARGS)
{
	unsigned char ucFrom, ucTo;

	if (bsData.Read(ucFrom) && bsData.Read(ucTo))
		Callback::Execute("OnPlayerEnterPauseSubmenu", "iii", ucTo, ucFrom, iExtra);

}

RPC_CALLBACK CRPCCallback::PlayerDriveByShot(RPC_ARGS)
{
	Callback::Execute("OnDriverDriveByShot", "i", iExtra);
}

RPC_CALLBACK CRPCCallback::StuntBonus(RPC_ARGS)
{
	sStuntDetails stuntDetails;

	if (bsData.Read(stuntDetails))
			Callback::Execute("OnPlayerStunt", "aiii", PAWNArray{ stuntDetails.iInfo, 6 }, stuntDetails.dwMoney, stuntDetails.ucType, iExtra);

}

RPC_CALLBACK CRPCCallback::ResolutionChange(RPC_ARGS)
{

	int X, Y;

	if (bsData.Read(X) && bsData.Read(Y))
		Callback::Execute("OnPlayerResolutionChange", "iii", Y, X, iExtra);

	Network::GetPlayerFromPlayerid(iExtra)->SetResolution(X, Y);

}

RPC_CALLBACK CRPCCallback::PlayerClick(RPC_ARGS)
{
	int type;
	int X, Y;

	if (bsData.Read(type) && bsData.Read(X) && bsData.Read(Y))
		Callback::Execute("OnPlayerClick", "iiii", Y, X, type, iExtra);
}

RPC_CALLBACK CRPCCallback::RadioChange(RPC_ARGS)
{
	int id;

	if (bsData.Read(id))
	{
		Network::GetPlayerFromPlayerid(iExtra)->SetRadio(id);
		if (IsPlayerInAnyVehicle(iExtra))
			Callback::Execute("OnPlayerChangeRadioStation", "iii", GetPlayerVehicleID(iExtra), id, iExtra);
	}
}

RPC_CALLBACK CRPCCallback::DrinkSprunk(RPC_ARGS)
{
	Callback::Execute("OnPlayerDrinkSprunk", "i", iExtra);
}