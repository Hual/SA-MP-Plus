#ifndef RAKSERVER_H
#define RAKSERVER_H

#include <Network/Network.h>

#include "../RakNet/MessageIdentifiers.h"
#include "../RakNet/RakPeer.h"

class CRakServer
{
public:
	CRakServer();
	virtual ~CRakServer();

	RakNet::StartupResult Startup(const char* szHostAddress, t_port usPort, unsigned short iConnections);
	void Shutdown(unsigned int blockDuration, PacketPriority priority);
	unsigned int Send(Network::ePacketType packetType, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F, bool bBroadcast = false);
	unsigned int SendRPC(unsigned short usRPCId, const RakNet::SystemAddress& systemAddress, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F, bool bBroadcast = false);

	RakNet::Packet* Receive();
	void DeallocatePacket(RakNet::Packet* pPacket);
	void CloseConnection(const RakNet::SystemAddress& pSystemAddress);

private:
	RakNet::RakPeer* m_pPeer;
	RakNet::SocketDescriptor* m_pSocketDescriptor;

};

#endif
