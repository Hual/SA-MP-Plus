#include "Network.h"
#include "../stdafx.h"
#include "../Game/CHUD.h"
#include "../Game/Hooks/CHooks.h"
#include "../Game/CGame.h"
#include "../Shared/Network/CRPC.h"
#include "Network/CRPCCallback.h"

namespace Network
{
	static CRakClient* pRakClient;
	static bool bInitialized = false;

	void Initialize()
	{
		pRakClient = new CRakClient();
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

	void Process()
	{
		if (!IsInitialized())
			return;

		RakNet::Packet* pPacket;

		while ((pPacket = pRakClient->Receive()))
		{
			if (!pPacket->length)
				return;

			CLog::Write("Received packet: %i", pPacket->data[0]);

			RakNet::BitStream bitStream(&pPacket->data[1], pPacket->length - 1, false);
			unsigned char* pData = bitStream.GetData();

			switch (pPacket->data[0])
			{
			case Network::ePacketType::PACKET_PLAYER_REGISTERED:
			{
				CRPCCallback::Initialize();
			}
			case Network::ePacketType::PACKET_RPC:
			{
				unsigned short usRpcId;

				if (bitStream.Read<unsigned short>(usRpcId))
					CRPC::Process(usRpcId, bitStream);

				break;
			}
			default:
				break;

			}

			pRakClient->DeallocatePacket(pPacket);
		}
	}

	CRakClient* GetRakClient()
	{
		return pRakClient;
	}
}