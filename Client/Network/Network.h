#pragma once

#include "CRakClient.h"
#include "../../Shared/Network/Network.h"

namespace Network
{
	void Initialize();
	bool IsInitialized();
	void Connect(const std::string& strAddress, unsigned short usPort);
	void Process();
	CRakClient* GetRakClient();
}