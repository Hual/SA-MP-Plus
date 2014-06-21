#pragma once

#include "CRakClient.h"
#include "../../Shared/Network/Network.h"

namespace Network
{
	void Initialize();
	bool IsInitialized();
	void Connect(const std::string& strAddress, unsigned short usPort);
	bool IsConnected();
	void Process();
	unsigned int Send(Network::ePacketType packetType, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	unsigned int SendRPC(unsigned short usRPCId, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	CRakClient* GetRakClient();
}
