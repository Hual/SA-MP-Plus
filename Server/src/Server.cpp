#include "Server.h"

namespace SAMPServer
{
	static CServerConfig* pServerConfig;

	void Initialize(const char* szConfigFileName)
	{
		pServerConfig = new CServerConfig(szConfigFileName);
	}

	CServerConfig* GetConfig()
	{
		return pServerConfig;
	}

	unsigned short GetMaxPlayers()
	{
		return atoi(pServerConfig->GetSetting("maxplayers").c_str());
	}

	std::string& GetListeningAddress()
	{
		return pServerConfig->GetSetting("bind");
	}

	unsigned short GetListeningPort()
	{
		return atoi(pServerConfig->GetSetting("port").c_str());
	}
}
