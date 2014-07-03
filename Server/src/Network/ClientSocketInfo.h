#ifndef CLIENTSOCKETINFO_H
#define CLIENTSOCKETINFO_H

#include <RakNet/RakNetTypes.h>

enum eClientConnectionState
{
	AWAITING,
	CONNECTED
};

class CClientSocketInfo
{
public:
	CClientSocketInfo(RakNet::SystemAddress systemAddress, RakNet::RakNetGUID guid);
	virtual inline ~CClientSocketInfo() {};

	inline void SetState(eClientConnectionState state) { m_state = state; };

	inline RakNet::SystemAddress& GetSystemAddress() { return m_systemAddress; };
	inline RakNet::RakNetGUID& GetGUID() { return m_guid; };
	inline eClientConnectionState GetState() { return m_state; };

private:
	RakNet::SystemAddress m_systemAddress;
	RakNet::RakNetGUID m_guid;
	eClientConnectionState m_state;

};

#endif
