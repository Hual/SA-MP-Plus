#pragma once

#include <map>
#include "../Shared/RakNet/BitStream.h"

#define RPC_CALLBACK void
#define RPC_ARGS RakNet::BitStream& bsData

typedef RPC_CALLBACK (*RPCFunct_t)(RPC_ARGS);

enum eRPC : unsigned short
{
	TOGGLE_HUD_COMPONENT,
	SET_RADIO_STATION,
	SET_WAVE_HEIGHT
};

class CRPC
{
public:
	static void Add(unsigned short usRPCId, RPCFunct_t func);
	static void Process(unsigned short usRPCId, RakNet::BitStream& bsData);

private:
	static std::map<unsigned short, RPCFunct_t> m_functions;

};
