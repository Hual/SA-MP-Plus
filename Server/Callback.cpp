#include "Callback.h"
#include "../Shared/Utility/Utility.h"
#include "Network/Network.h"

namespace Callback
{
	cell Process(AMX* pAmx, eCallbackType type, cell* pParams)
	{
		switch (type)
		{
		case eCallbackType::ON_PLAYER_CONNECT:
		{
			cell* pPlayerId = nullptr;
			amx_GetAddr(pAmx, pParams[0], &pPlayerId);
			OnPlayerConnect(*pPlayerId);
			delete pPlayerId;

			break;
		}
		case eCallbackType::ON_PLAYER_DISCONNECT:
		{
			cell* pPlayerId = nullptr;
			amx_GetAddr(pAmx, pParams[0], &pPlayerId);
			OnPlayerDisconnect(*pPlayerId);
			delete pPlayerId;

			break;
		}
		default:
			break;

		}
		return 1;
	}

	void OnPlayerConnect(unsigned int uiPlayerid)
	{
		if (Network::HandleConnection(uiPlayerid))
			Network::PlayerSend(Network::ePacketType::PACKET_PLAYER_REGISTERED, uiPlayerid);

		Utility::Printf("Player connecting, has the SA-MP+ plugin: %i", Network::IsPlayerConnected(uiPlayerid));
	}

	void OnPlayerDisconnect(unsigned int uiPlayerid)
	{
		if (Network::GetClientConnectionFromPlayerid(uiPlayerid))
			Network::CloseConnection(uiPlayerid);

	}
}