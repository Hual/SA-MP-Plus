#ifndef PLAYER_H
#define PLAYER_H

#include "Network/ClientSocketInfo.h"

class CPlayer
{
public:
	CPlayer(CClientSocketInfo* socketInfo);
	~CPlayer();

	CClientSocketInfo* GetConnectionInfo();
	void SetInPauseMenu(bool bInPauseMenu);
	bool IsInPauseMenu();
	void SetCurrentMenuId(unsigned char ucMenuId);
	unsigned char GetCurrentMenuId();

private:
	CClientSocketInfo* m_pSockInfo;
	bool m_bInPauseMenu;
	unsigned char m_ucMenuId;

};

#endif
