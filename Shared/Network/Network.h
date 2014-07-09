#pragma once

typedef unsigned short t_port;

namespace Network
{
	enum ePacketType : unsigned char
	{
		PACKET_PLAYER_REGISTERED = 0x87,
		PACKET_PLAYER_KICKED,
		PACKET_RPC
	};
}
