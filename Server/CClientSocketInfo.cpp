#include <SAMP+/svr/CClientSocketInfo.h>

CClientSocketInfo::CClientSocketInfo(RakNet::SystemAddress systemAddress, RakNet::RakNetGUID guid)
{
	m_systemAddress = systemAddress;
	m_guid = guid;
	m_state = eClientConnectionState::AWAITING;
	m_creationTime = time(NULL);
}
