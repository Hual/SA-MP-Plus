#include <Network/RPC.h>

#include "Network.h"
#include "../stdafx.h"
#include "../Game/CHUD.h"
#include "../Game/Hooks/CHooks.h"
#include "../Game/CGame.h"
#include "CRPCCallback.h"

namespace Network
{
	static CRakClient* pRakClient;
	static bool bInitialized = false;
	static bool bConnected = false;

	void Initialize()
	{
		pRakClient = new CRakClient();
		bConnected = false;

		if (pRakClient->Startup() != RakNet::StartupResult::RAKNET_STARTED)
			return;

		bInitialized = true;
	}

	bool IsInitialized()
	{
		return bInitialized;
	}

	void Connect(const std::string& strAddress, unsigned short usPort)
	{
		if (IsInitialized())
			pRakClient->Connect(strAddress.c_str(), usPort, NULL);

	}

	bool IsConnected()
	{
		return bConnected;
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
			case Network::ePacketType::PACKET_PLAYER_REGISTERED:
			{
				bConnected = true;
				CRPCCallback::Initialize();
			}
			case Network::ePacketType::PACKET_RPC:
			{
				unsigned short usRpcId;

				if (bitStream.Read<unsigned short>(usRpcId))
					RPC::Process(usRpcId, bitStream);

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