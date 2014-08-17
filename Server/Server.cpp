#include <SAMP+/svr/Server.h>

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

	unsigned short getMaxPlayers()
	{
		return atoi(pServerConfig->GetSetting("maxplayers").c_str());
	}

	std::string GetListeningAddress()
	{
		if (pServerConfig->HasSetting("bind"))
			return pServerConfig->GetSetting("bind");
		else
			return "";
	}

	unsigned short GetListeningPort()
	{
		return atoi(pServerConfig->GetSetting("port").c_str());
	}

}