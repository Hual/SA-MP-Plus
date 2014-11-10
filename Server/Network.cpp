#include <RakNet/SuperFastHash.h>

#include <SAMP+/Utility.h>
#include <SAMP+/CRPC.h>

#include <SAMP+/svr/Network.h>
#include <SAMP+/svr/CRPCCallback.h>
#include <SAMP+/svr/Callback.h>

#include <sampgdk.h>

namespace Network
{
	static CRakServer* pRakServer;
	static bool bInitialized = false;
	static std::list<CClientSocketInfo*> unhandledConnections;
	static std::map<unsigned int, CPlayer*> players;

	void Initialize(const std::string& szHostAddress, t_port usPort, int iConnections)
	{
		if (szHostAddress.length() == 0)
			Initialize(0, usPort, iConnections);
		else
			Initialize(szHostAddress.c_str(), usPort, iConnections);

		return CRPCCallback::Initialize();
	}

	void Initialize(const char* szHostAddress, t_port usPort, int iConnections)
	{
		pRakServer = new CRakServer();
		
		if (pRakServer->Startup(szHostAddress, usPort, iConnections) != RakNet::StartupResult::RAKNET_STARTED)
		{
			Utility::Printf("Couldn't start SA-MP+ plugin");
			exit(EXIT_FAILURE);
		}

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

	std::map<unsigned int, CPlayer*>& GetPlayers()
	{
		return players;
	}

	CPlayer* GetPlayerFromPlayerid(unsigned int uiPlayerid)
	{
		if(!isConnected(uiPlayerid)) return NULL;
		
		return players[uiPlayerid];
	}

	bool isConnected(unsigned int uiPlayerid)
	{
		return !!players.count(uiPlayerid);
	}

	int GetPlayeridFromSystemAddress(const RakNet::SystemAddress& systemAddress)
	{
		// todo: turn address into an int
		//SuperFastHash((const char*)& systemAddress.address.addr4.sin_addr.s_addr, sizeof(systemAddress.address.addr4.sin_addr.s_addr));
		for (std::map<unsigned int, CPlayer*>::iterator it = players.begin(); it != players.end(); ++it)
		{
			if (!strcmp(systemAddress.ToString(false), (*it).second->GetConnectionInfo()->GetSystemAddress().ToString(false)))
				return (*it).first;

		}

		return -1;
	}

	void CloseConnection(unsigned int uiPlayerid)
	{
		pRakServer->CloseConnection(players[uiPlayerid]->GetConnectionInfo()->GetSystemAddress());
		Cleanup(uiPlayerid);
	}

	void CloseUnhandledConnection(const RakNet::SystemAddress& systemAddress)
	{
		pRakServer->CloseConnection(systemAddress);
		CleanupUnhandledConnection(systemAddress);
	}

	void Cleanup(unsigned int uiPlayerid)
	{
		delete players[uiPlayerid];
		players.erase(uiPlayerid);
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
				CPlayer* pPlayer = new CPlayer(*it);
				unhandledConnections.erase(it);
				players[uiPlayerid] = pPlayer;
				pPlayer->GetConnectionInfo()->SetState(eClientConnectionState::CONNECTED);

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
		CPlayer* pPlayer = GetPlayerFromPlayerid(uiPlayerId);
		if (!pPlayer || pPlayer->GetConnectionInfo()->GetState() != eClientConnectionState::CONNECTED)
			return 0;

		return pRakServer->Send(packetType, pPlayer->GetConnectionInfo()->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	unsigned int PlayerSendRPC(unsigned short usRPCId, unsigned int uiPlayerId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		CPlayer* pPlayer = GetPlayerFromPlayerid(uiPlayerId);
		if (!pPlayer || pPlayer->GetConnectionInfo()->GetState() != eClientConnectionState::CONNECTED)
			return 0;

		return pRakServer->SendRPC(usRPCId, pPlayer->GetConnectionInfo()->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	void Broadcast(ePacketType packetType, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		for (std::map<unsigned int, CPlayer*>::iterator it = players.begin(); it != players.end(); ++it)
		{
			CPlayer* pPlayer = it->second;

			if (!pPlayer || pPlayer->GetConnectionInfo()->GetState() != eClientConnectionState::CONNECTED)
				continue;

			pRakServer->Send(packetType, pPlayer->GetConnectionInfo()->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
		}
	}

	void BroadcastRPC(unsigned short usRPCId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		for (std::map<unsigned int, CPlayer*>::iterator it = players.begin(); it != players.end(); ++it)
		{
			CPlayer* pPlayer = it->second;

			if (!pPlayer || pPlayer->GetConnectionInfo()->GetState() != eClientConnectionState::CONNECTED)
				continue;

			pRakServer->SendRPC(usRPCId, pPlayer->GetConnectionInfo()->GetSystemAddress(), pBitStream, priority, reliability, cOrderingChannel);
		}
	}

	void Process()
	{
		if (!IsInitialized())
			return;

		RakNet::Packet* pPacket;

		while ((pPacket = pRakServer->Receive()))
		{
			if (!pPacket->length)
				return;

			int iPlayerId = 0;
			RakNet::BitStream bitStream(&pPacket->data[1], pPacket->length - 1, false);

			if (pPacket->data[0] == ID_NEW_INCOMING_CONNECTION)
			{
				if (Callback::Execute("OnPlayerSAMPPConnect", "is", pPacket->systemAddress.GetPort(), pPacket->systemAddress.ToString(false)))
				{
					CClientSocketInfo* pSockInfo = new CClientSocketInfo(pPacket->systemAddress, pPacket->guid);
					unhandledConnections.push_back(pSockInfo);

					Utility::Printf("Unhandled connection accepted: %s:%i", pPacket->systemAddress.ToString(false), pPacket->systemAddress.GetPort());
				}
				else
				{
					pRakServer->Send(ePacketType::PACKET_CONNECTION_REJECTED, pPacket->systemAddress);
					pRakServer->CloseConnection(pPacket->systemAddress);

					Utility::Printf("Unhandled connection rejected: %s:%i", pPacket->systemAddress.ToString(false), pPacket->systemAddress.GetPort());
				}

				//TODO: read sa-mp's ban list, reject connection if IP is banned
			}
			else
				iPlayerId = GetPlayeridFromSystemAddress(pPacket->systemAddress);

			switch (pPacket->data[0])
			{
			case ID_DISCONNECTION_NOTIFICATION:
			{
				Utility::Printf("Disconnected: %s", pPacket->systemAddress.ToString());
				
				if (iPlayerId != -1)
					Cleanup(iPlayerId);
				else
					CleanupUnhandledConnection(pPacket->systemAddress);
				
#ifdef DEBUG
				Utility::Printf("Connection status: unhandledConnections: %u, players: %u", unhandledConnections.size(), players.size());
#endif

				break;
			}
			case ID_CONNECTION_LOST:
			{
				Utility::Printf("Connection lost: %s", pPacket->systemAddress.ToString());

				if (iPlayerId != -1)
					Cleanup(iPlayerId);
				else
					CleanupUnhandledConnection(pPacket->systemAddress);

#ifdef DEBUG
				Utility::Printf("Connection status: unhandledConnections: %u, players: %u", unhandledConnections.size(), players.size());
#endif

				break;
			}
			case PACKET_RPC:
			{
				if (iPlayerId != -1)
				{
					unsigned short usRpcId;

					if (bitStream.Read<unsigned short>(usRpcId))
						CRPC::Process(usRpcId, bitStream, iPlayerId);

				}

				break;
			}
			default:
				Utility::Printf("Unknown packet received: %u, local: %u", pPacket->data[0], pPacket->wasGeneratedLocally);
				break;
			}

			pRakServer->DeallocatePacket(pPacket);
		}
	}
}
