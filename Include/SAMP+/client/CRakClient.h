#pragma once

#include <RakNet/RakPeer.h>
#include <SAMP+/Network.h>

class CRakClient
{
public:
	CRakClient();
	virtual ~CRakClient();

	RakNet::StartupResult Startup();
	void Shutdown(int iBlockDuration);
	RakNet::ConnectionAttemptResult Connect(const char* szAddress, unsigned short usPort, const char* szPassword);
	unsigned int Send(Network::ePacketType packetType, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	unsigned int SendRPC(unsigned short usRPCId, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	RakNet::Packet* Receive();
	void DeallocatePacket(RakNet::Packet* pPacket);
	void Disconnect();
	bool IsConnected();
	RakNet::SystemAddress* GetRemoteAddress();

private:
	RakNet::RakPeer* m_pPeer;
	RakNet::SocketDescriptor* m_pSocketDescriptor;
	RakNet::SystemAddress* m_pSystemAddress;
	bool m_bConnected;

};