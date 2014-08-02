#pragma once

#include <map>
#include <list>

#include <SAMP+/Network.h>
#include <SAMP+/svr/CRakServer.h>
#include <SAMP+/svr/CClientSocketInfo.h>
#include <SAMP+/svr/CPlayer.h>

namespace Network
{
	void Initialize(const char* szHostAddress, t_port usPort, int iConnections);
	void Initialize(const std::string& szHostAddress, t_port usPort, int iConnections);
	CRakServer* GetRakServer();
	bool IsInitialized();

	std::list<CClientSocketInfo*>& GetUnhandledConnections();
	std::map<unsigned int, CPlayer*>& GetPlayers();
	CPlayer* GetPlayerFromPlayerid(unsigned int uiPlayerid);
	int GetPlayeridFromSystemAddress(const RakNet::SystemAddress& systemAddress);
	bool isConnected(unsigned int uiPlayerid);

	void CloseConnection(unsigned int uiPlayerid);
	void CloseUnhandledConnection(const RakNet::SystemAddress& systemAddress);
	void Cleanup(unsigned int uiPlayerid);
	void CleanupUnhandledConnection(const RakNet::SystemAddress& systemAddress);

	bool HandleConnection(unsigned int uiPlayerid);
	bool IsConnectionHandled(const RakNet::SystemAddress& systemAddress);

	unsigned int PlayerSend(ePacketType packetType, unsigned int uiPlayerId, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	unsigned int PlayerSendRPC(unsigned short usRPCId, unsigned int uiPlayerId, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	void Broadcast(ePacketType packetType, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);
	void BroadcastRPC(unsigned short usRPCId, RakNet::BitStream* pBitStream = NULL, PacketPriority priority = PacketPriority::HIGH_PRIORITY, PacketReliability reliability = PacketReliability::RELIABLE_ORDERED, char cOrderingChannel = 0x7F);

	void Process();
}
