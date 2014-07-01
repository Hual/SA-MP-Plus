#include <sampgdk/a_players.h>

#include "RPCCallback.h"
#include "../Utility.h"
#include "../Callback.h"

void RPCCallback::Initialize()
{
	RPC::Add(eRPC::ON_PAUSE_MENU_TOGGLE, RPCCallback::PlayerPauseMenuSwitch);
	RPC::Add(eRPC::ON_PAUSE_MENU_CHANGE, RPCCallback::PlayerPauseMenuBrowse);
}

RPC_CALLBACK RPCCallback::PlayerPauseMenuSwitch(RPC_ARGS)
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

RPC_CALLBACK RPCCallback::PlayerPauseMenuBrowse(RPC_ARGS)
{
	unsigned char ucFrom, ucTo;

	if (bsData.Read(ucFrom) && bsData.Read(ucTo))
		Callback::Execute("OnPlayerEnterPauseSubmenu", "iii", ucTo, ucFrom, iExtra);

}
