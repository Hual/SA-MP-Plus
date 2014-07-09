#include "Network.h"
#include "../stdafx.h"
#include "../Game/CHUD.h"
#include "../Game/Hooks/CHooks.h"
#include "../Game/CGame.h"
#include "../Shared/Network/CRPC.h"
#include "Network/CRPCCallback.h"
#include "../Shared/RakNet/MessageIdentifiers.h"

namespace Network
{
	static CRakClient* pRakClient;
	static bool bInitialized;
	static bool bConnected;
	static bool bServerHasPlugin;
	static std::string strAddress;
	static unsigned short usPort;

	void Initialize(std::string address, unsigned short port)
	{
		bInitialized = false;

		strAddress = address;
		usPort = port;

		pRakClient = new CRakClient();
		bConnected = false;
		bServerHasPlugin = false;

		if (pRakClient->Startup() != RakNet::StartupResult::RAKNET_STARTED)
			return;

		bInitialized = true;
	}

	bool IsInitialized()
	{
		return bInitialized;
	}

	void Connect()
	{
		if (IsInitialized())
			pRakClient->Connect(strAddress.c_str(), usPort, NULL);

	}

	bool IsConnected()
	{
		return bConnected;
	}

	bool ServerHasPlugin()
	{
		return bServerHasPlugin;
	}

	void Process()
	{
		if (!IsInitialized())
			return;

		RakNet::Packet* pPacket;

		while ((pPacket = pRakClient->Receive()))
		{
			if (!pPacket->length)
				return;

			CLog::Write("Received packet: %i, local: %i", pPacket->data[0], pPacket->wasGeneratedLocally);

			RakNet::BitStream bitStream(&pPacket->data[1], pPacket->length - 1, false);

			switch (pPacket->data[0])
			{
			case ePacketType::PACKET_PLAYER_REGISTERED:
			{
				bConnected = true;
				bServerHasPlugin = true;
				CRPCCallback::Initialize();

				break;
			}
			case ePacketType::PACKET_RPC:
			{
				unsigned short usRpcId;

				if (bitStream.Read<unsigned short>(usRpcId))
					CRPC::Process(usRpcId, bitStream);

				break;
			}
			case ePacketType::PACKET_CONNECTION_REJECTED:
			case ePacketType::PACKET_PLAYER_PROPER_DISCONNECT:
			{
				bServerHasPlugin = false;

				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			case ID_CONNECTION_LOST:
			{
				bConnected = false;

				if (ServerHasPlugin())
					Connect();

				break;
			}
			default:
				break;

			}

			pRakClient->DeallocatePacket(pPacket);
		}
	}

	unsigned int Send(Network::ePacketType packetType, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		if (!IsConnected())
			return 0;

		return pRakClient->Send(packetType, *pRakClient->GetRemoteAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	unsigned int SendRPC(unsigned short usRPCId, RakNet::BitStream* pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel)
	{
		if (!IsConnected())
			return 0;

		return pRakClient->SendRPC(usRPCId, *pRakClient->GetRemoteAddress(), pBitStream, priority, reliability, cOrderingChannel);
	}

	CRakClient* GetRakClient()
	{
		return pRakClient;
	}
}