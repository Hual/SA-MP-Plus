#pragma once

#include <SAMP+/svr/CServerConfig.h>

namespace SAMPServer
{
	void Initialize(const char* szConfigFileName);
	CServerConfig* GetConfig();
	unsigned short getMaxPlayers();
	unsigned short GetListeningPort();
	std::string GetListeningAddress();
}