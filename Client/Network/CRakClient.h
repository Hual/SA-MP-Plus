#pragma once

#include "../../Shared/RakNet/RakPeer.h"

class CRakClient
{
public:
	CRakClient();
	virtual ~CRakClient();

	RakNet::StartupResult Startup();
	void Shutdown(int iBlockDuration);
	RakNet::ConnectionAttemptResult Connect(const char* szAddress, unsigned short usPort, const char* szPassword);
	RakNet::Packet* Receive();
	void DeallocatePacket(RakNet::Packet* pPacket);
	void Disconnect();
	bool IsConnected();

private:
	RakNet::RakPeer* m_pPeer;
	RakNet::SocketDescriptor* m_pSocketDescriptor;
	RakNet::SystemAddress* m_pSystemAddress;
	bool m_bConnected;

};