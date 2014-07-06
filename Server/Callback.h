#pragma once

#include <list>
#include <SDK/amx/amx.h>

struct PAWNArray
{
	cell* address;
	size_t length;
};

namespace Callback
{
	enum eCallbackType
	{
		ON_PLAYER_CONNECT,
		ON_PLAYER_DISCONNECT
	};

	// push arguments in reversed order
	void Execute(const char* szFunction, const char* szFormat, ...);

	cell Process(AMX* pAmx, eCallbackType type, cell* pParams);
	void OnPlayerConnect(unsigned int uiPlayerid);
	void OnPlayerDisconnect(unsigned int uiPlayerid);

	std::list<AMX*>& GetAMXList();
}