#pragma once

typedef unsigned short t_port;

namespace Network
{
	enum ePacketType : unsigned char
	{
		PACKET_PLAYER_REGISTERED = 0x87,
		PACKET_PLAYER_PROPER_DISCONNECT,
		PACKET_CONNECTION_REJECTED,
		PACKET_RPC
	};
}
