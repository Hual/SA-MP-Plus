#include"CRakClient.h"

CRakClient::CRakClient()
{
	m_pPeer = new RakNet::RakPeer();
	m_pSocketDescriptor = new RakNet::SocketDescriptor();
	m_bConnected = false;
}

CRakClient::~CRakClient()
{

}

RakNet::StartupResult CRakClient::Startup()
{
	return m_pPeer->Startup(1, m_pSocketDescriptor, 1, THREAD_PRIORITY_NORMAL);
}

void CRakClient::Shutdown(int iBlockDuration)
{
	Disconnect();

	return m_pPeer->Shutdown(iBlockDuration);
}

RakNet::ConnectionAttemptResult CRakClient::Connect(const char* szAddress, unsigned short usPort, const char* szPassword)
{
	Disconnect();

	m_pSystemAddress = new RakNet::SystemAddress(szAddress, usPort);

	return m_pPeer->Connect(szAddress, usPort, szPassword, szPassword ? strlen(szPassword) : NULL);
}

void CRakClient::Disconnect()
{
	if (IsConnected())
	{
		m_pPeer->CloseConnection(*m_pSystemAddress, true);
		m_bConnected = false;
	}
}

RakNet::Packet* CRakClient::Receive()
{
	return 	m_pPeer->Receive();
}

void CRakClient::DeallocatePacket(RakNet::Packet* pPacket)
{
	return m_pPeer->DeallocatePacket(pPacket);
}

//TODO: cancel connection attempt

bool CRakClient::IsConnected()
{
	return m_bConnected;
}