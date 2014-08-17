#pragma once

#include <list>
#include <amx/amx.h>

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
	cell Execute(const char* szFunction, const char* szFormat, ...);

	cell Process(AMX* pAmx, eCallbackType type, cell* pParams);
	void OnPlayerConnect(unsigned int uiPlayerid);
	void OnPlayerDisconnect(unsigned int uiPlayerid, unsigned int uiReason);

	std::list<AMX*>& GetAMXList();
}