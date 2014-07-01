#ifndef SERVER_H
#define SERVER_H

#include "ServerConfig.h"

namespace SAMPServer
{
	void Initialize(const char* szConfigFileName);
	CServerConfig* GetConfig();
	unsigned short GetMaxPlayers();
	unsigned short GetListeningPort();
	std::string& GetListeningAddress();
}

#endif