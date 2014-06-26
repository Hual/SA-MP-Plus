#include "CRPCCallback.h"
#include "../Shared/Utility/Utility.h"
#include "../Callback.h"
#include "sampgdk/a_players.h"

void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::ON_PAUSE_MENU_TOGGLE, CRPCCallback::PlayerPauseMenuSwitch);
	CRPC::Add(eRPC::ON_PAUSE_MENU_CHANGE, CRPCCallback::PlayerPauseMenuBrowse);
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
