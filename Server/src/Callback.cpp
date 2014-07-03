#include "Callback.h"
#include "Network/Network.h"
#include "Utility.h"

namespace Callback
{
	static AMX* amx_allowed = NULL;
	static std::list<AMX*> amxPointers;

	std::list<AMX*>& GetAMXList()
	{
		return amxPointers;
	}

	void Execute(const char* szFunction, const char* szFormat, ...)
	{
		va_list argPtr;

		for (std::list<AMX*>::iterator it = amxPointers.begin(); it != amxPointers.end(); ++it)
		{
			AMX* pAmx = *it;
			int iFuncIdx;

			if (amx_FindPublic(pAmx, szFunction, &iFuncIdx) != 0)
				continue;

			cell iReturn;

			cell addresses[16];
			unsigned int addr_idx = 0;

			va_start(argPtr, szFormat);

			for (unsigned int i = 0; i < strlen(szFormat); ++i)
			{
				switch (szFormat[i])
				{
				case 'i':
				{
					amx_Push(pAmx, va_arg(argPtr, int));

					break;
				}
				case 's':
				{
					amx_PushString(pAmx, &addresses[addr_idx++], NULL, va_arg(argPtr, char*), false, false);

					break;
				}
				case 'a':
				{
					cell iAmxAddr, *pPhysAddr;

					cell* pArray = va_arg(argPtr, cell*);
					amx_Allot(pAmx, sizeof(pArray) / sizeof(cell), &iAmxAddr, &pPhysAddr);
					memcpy(pPhysAddr, pArray, sizeof(pArray));
					amx_Push(pAmx, iAmxAddr);

					break;
				}
				}
			}

			va_end(argPtr);

			amx_Exec(pAmx, &iReturn, iFuncIdx);

			for (unsigned int i = 0; i < addr_idx; ++i)
			{
				amx_Release(pAmx, addresses[i]);
			}
		}
	}

	cell Process(AMX* pAmx, eCallbackType type, cell* pParams)
	{
		// limit callbacks
		if (!amx_allowed)
			amx_allowed = pAmx;
		else if (amx_allowed != pAmx)
			return 0;

		switch (type)
		{
		case eCallbackType::ON_PLAYER_CONNECT:
		{
			cell *pPlayerId = NULL;
			amx_GetAddr(pAmx, pParams[0], &pPlayerId);
			OnPlayerConnect(*pPlayerId);
			break;
		}
		case eCallbackType::ON_PLAYER_DISCONNECT:
		{
			cell *pPlayerId = NULL;
			amx_GetAddr(pAmx, pParams[0], &pPlayerId);
			OnPlayerDisconnect(*pPlayerId);
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
		if (Network::GetPlayers().count(uiPlayerid))
			Network::CloseConnection(uiPlayerid);

	}
}
