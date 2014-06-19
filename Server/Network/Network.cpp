#include "Network.h"
#include "../Shared/Utility/Utility.h"
#include "sampgdk/a_players.h"

namespace Network
{
	static CRakServer* pRakServer;
	static bool bInitialized = false;
	static std::list<CClientSocketInfo*> unhandledConnections;
	static std::map<unsigned int, CClientSocketInfo*> clientConnections;

	void Initialize(const std::string& szHostAddress, t_port usPort, int iConnections)
	{
		if (szHostAddress.length() == 0)
			return Initialize(0, usPort, iConnections);
		else
			return Initialize(szHostAddress.c_str(), usPort, iConnections);

	}

	void Initialize(const char* szHostAddress, t_port usPort, int iConnections)
	{
		pRakServer = new CRakServer();
		if (pRakServer->Startup(szHostAddress, usPort, iConnections) != RakNet::StartupResult::RAKNET_STARTED)
			ExitThread(0);

		bInitialized = true;
	}

	CRakServer* GetRakServer()
	{
		return pRakServer;
	}

	bool IsInitialized()
	{
		return bInitialized;
	}

	std::list<CClientSocketInfo*>& GetUnhandledConnections()
	{
		return unhandledConnections;
	}

	std::map<unsigned int, CClientSocketInfo*>& GetClientConnections()
	{
		return clientConnections;
	}

	CClientSocketInfo* GetClientConnectionFromPlayerid(unsigned int uiPlayerid)
	{
		return clientConnections[uiPlayerid];
	}

	bool IsPlayerConnected(unsigned int uiPlayerid)
	{
		return clientConnections.count(uiPlayerid);
	}

	int GetPlayeridFromSystemAddress(const RakNet::SystemAddress& systemAddress)
	{
		for (std::map<unsigned int, CClientSocketInfo*>::iterator it = clientConnections.begin(); it != clientConnections.end(); ++it)
		{
			if (!strcmp(systemAddress.ToString(false), (*it).second->GetSystemAddress().ToString(false)))
				return (*it).first;

		}

		return -1;
	}

	void CloseConnection(unsigned int uiPlayerid)
	{
		pRakServer->CloseConnection(clientConnections[uiPlayerid]->GetSystemAddress());
		CleanupConnection(uiPlayerid);
	}

	void CloseUnhandledConnection(const RakNet::SystemAddress& systemAddress)
	{
		pRakServer->CloseConnection(systemAddress);
		CleanupUnhandledConnection(systemAddress);
	}

	void CleanupConnection(unsigned int uiPlayerid)
	{
		delete clientConnections[uiPlayerid];
		clientConnections.erase(uiPlayerid);
	}

	void CleanupUnhandledConnection(const RakNet::SystemAddress& systemAddress)
	{
		for (std::list<CClientSocketInfo*>::iterator it = unhandledConnections.begin(); it != unhandledConnections.end(); ++it)
		{
			if (!strcmp(systemAddress.ToString(false), (*it)->GetSystemAddress().ToString(false)))
			{
				delete *it;
				unhandledConnections.erase(it);
				return;
			}
		}
	}

	bool HandleConnection(unsigned int uiPlayerid)
	{
		char szIP[16];
		GetPlayerIp(uiPlayerid, szIP, 16);

		for (std::list<CClientSocketInfo*>::iterator it = unhandledConnections.begin(); it != unhandledConnections.end(); ++it)
		{
			if (!strcmp(szIP, (*it)->GetSystemAddress().ToString(false)))
			{
				clientConnections[uiPlayerid] = (*it);
				(*it)->SetState(eClientConnectionState::CONNECTED);
				unhandledConnections.erase(it);

				return true;
			}
		}

		return false;
	}

	bool IsConnectionHandled(const RakNet::SystemAddress& systemAddress)
	{
		return GetPlayeridFromSystemAddress(systemAddress) != -1;
	}

	unsigned int PlayerSend(ePacketType packetType, unsigned int uiPlayerId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		CClientSocketInfo* pSocketInfo = GetClientConnectionFromPlayerid(uiPlayerId);
		if (!pSocketInfo || pSocketInfo->GetState() != eClientConnectionState::CONNECTED)
			return 0;

		return pRakServer->Send(packetType, pSocketInfo->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	unsigned int PlayerSendRPC(unsigned short usRPCId, unsigned int uiPlayerId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		CClientSocketInfo* pSocketInfo = GetClientConnectionFromPlayerid(uiPlayerId);
		if (!pSocketInfo || pSocketInfo->GetState() != eClientConnectionState::CONNECTED)
			return 0;

		return pRakServer->SendRPC(usRPCId, pSocketInfo->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	void Broadcast(ePacketType packetType, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		for (std::map<unsigned int, CClientSocketInfo*>::iterator it = clientConnections.begin(); it != clientConnections.end(); ++it)
		{
			CClientSocketInfo* pSocketInfo = it->second;

			if (!pSocketInfo || pSocketInfo->GetState() != eClientConnectionState::CONNECTED)
				continue;

			pRakServer->Send(packetType, pSocketInfo->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
		}
	}

	void BroadcastRPC(unsigned short usRPCId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		for (std::map<unsigned int, CClientSocketInfo*>::iterator it = clientConnections.begin(); it != clientConnections.end(); ++it)
		{
			CClientSocketInfo* pSocketInfo = it->second;

			if (!pSocketInfo || pSocketInfo->GetState() != eClientConnectionState::CONNECTED)
				continue;

			pRakServer->SendRPC(usRPCId, pSocketInfo->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
		}
	}

	void Process()
	{
		if (!IsInitialized())
			return;

		RakNet::Packet* pPacket;

		while ((pPacket = pRakServer->Receive()))
		{
			switch (pPacket->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
			{
				Utility::Printf("Incoming connection: %s", pPacket->systemAddress.ToString());

				//TODO: read sa-mp's ban list, reject connection if IP is banned

				CClientSocketInfo* pSockInfo = new CClientSocketInfo(pPacket->systemAddress, pPacket->guid);
				unhandledConnections.push_back(pSockInfo);

				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				Utility::Printf("Disconnected: %s", pPacket->systemAddress.ToString());

				break;
			}
			case ID_CONNECTION_LOST:
			{
				Utility::Printf("Connection lost: %s", pPacket->systemAddress.ToString());

				int iPlayerId = GetPlayeridFromSystemAddress(pPacket->systemAddress);
				if (iPlayerId != -1)
					CleanupConnection(iPlayerId);
				else
					CleanupUnhandledConnection(pPacket->systemAddress);

				break;
			}
			default:
				Utility::Printf("Unknown packet received: %u", pPacket->data[0]);
				break;
			}

#ifdef DEBUG
			Utility::Printf("Connection status: unhandledConnections: %u, clientConnections: %u", unhandledConnections.size(), clientConnections.size());
#endif

			pRakServer->DeallocatePacket(pPacket);
		}
	}
}