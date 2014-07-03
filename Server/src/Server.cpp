#include "Server.h"

namespace SAMPServer
{
	static ServerConfig *config;

	void Initialize(const char* szConfigFileName)
	{
		config = new ServerConfig(szConfigFileName);
	}

	ServerConfig *GetConfig()
	{
		return config;
	}

	unsigned short GetMaxPlayers()
	{
		return config->GetInt("maxplayers");
	}

	std::string GetListeningAddress()
	{
		std::string address = config->GetString("bind");

		if(address.empty())
			address = "127.0.0.1";
			
		return address;
	}

	unsigned short GetListeningPort()
	{
		return config->GetInt("port");
	}
}
