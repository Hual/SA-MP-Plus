#include <SAMP+/Definitions.h>

#include <SAMP+/svr/CRakServer.h>
#include <SAMP+/svr/Network.h>

CRakServer::CRakServer()
{
	m_pPeer = new RakNet::RakPeer();
}

CRakServer::~CRakServer()
{

}

RakNet::StartupResult CRakServer::Startup(const char* szHostAddress, t_port usPort, unsigned short iConnections)
{
	m_pSocketDescriptor = new RakNet::SocketDescriptor(usPort, szHostAddress);

	RakNet::StartupResult iResult = m_pPeer->Startup(iConnections, m_pSocketDescriptor, 1, SAMPP_DEFAULT_THREAD_PRIORITY);
	
	if (iResult == RakNet::StartupResult::RAKNET_STARTED)
		m_pPeer->SetMaximumIncomingConnections(iConnections+1);

	return iResult;
}

void CRakServer::Shutdown(unsigned int blockDuration, PacketPriority priority)
{
	return m_pPeer->Shutdown(blockDuration, 0, priority);
}

unsigned int CRakServer::Send(Network::ePacketType packetType, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel, bool bBroadcast)
{
	RakNet::BitStream bitStream;
	bitStream.Write((unsigned char)packetType);
	if (pBitStream)
		bitStream.Write((char*)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed());

	return m_pPeer->Send(&bitStream, priority, reliability, cOrderingChannel, systemAddress, bBroadcast);
}

unsigned int CRakServer::SendRPC(unsigned short usRPCId, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel, bool bBroadcast)
{
	RakNet::BitStream bitStream;
	bitStream.Write(usRPCId);
	if (pBitStream)
		bitStream.Write((char*)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed());

	return Send(Network::ePacketType::PACKET_RPC, systemAddress, &bitStream, priority, reliability, cOrderingChannel, bBroadcast);
}

RakNet::Packet* CRakServer::Receive()
{
	return 	m_pPeer->Receive();
}

void CRakServer::DeallocatePacket(RakNet::Packet* pPacket)
{
	return m_pPeer->DeallocatePacket(pPacket);
}

void CRakServer::CloseConnection(const RakNet::SystemAddress& pSystemAddress)
{
	return m_pPeer->CloseConnection(pSystemAddress, true, 0xFF);
}
