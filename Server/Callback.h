#pragma once

#include <SDK/amx/amx.h>

namespace Callback
{
	enum eCallbackType
	{
		ON_PLAYER_CONNECT,
		ON_PLAYER_DISCONNECT
	};

	cell Process(AMX* pAmx, eCallbackType type, cell* pParams);
	void OnPlayerConnect(unsigned int uiPlayerid);
	void OnPlayerDisconnect(unsigned int uiPlayerid);

}