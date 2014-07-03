#ifndef CALLBACK_H
#define CALLBACK_H

#include <list>

#include "SDK/amx/amx.h"

namespace Callback
{
	enum eCallbackType
	{
		ON_PLAYER_CONNECT,
		ON_PLAYER_DISCONNECT
	};

	void Execute(const char* szFunction, const char* szFormat, ...);

	cell Process(AMX* pAmx, eCallbackType type, cell* pParams);
	void OnPlayerConnect(unsigned int uiPlayerid);
	void OnPlayerDisconnect(unsigned int uiPlayerid);

	std::list<AMX*>& GetAMXList();
}

#endif
