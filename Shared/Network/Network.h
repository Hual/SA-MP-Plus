#pragma once

typedef unsigned short t_port;

namespace Network
{
	enum ePacketType : unsigned char
	{
		PACKET_PLAYER_REGISTERED = 0x87,
		PACKET_RPC,
		PACKET_TOGGLE_GUI_COMPONENT,
		PACKET_START_RADIO,
		PACKET_SET_WAVE_HEIGHT
	};
}