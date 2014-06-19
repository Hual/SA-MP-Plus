#pragma once

#include "CServerConfig.h"

namespace SAMPServer
{
	void Initialize(const char* szConfigFileName);
	CServerConfig* GetConfig();
	unsigned short GetMaxPlayers();
	unsigned short GetListeningPort();
	std::string& GetListeningAddress();
}