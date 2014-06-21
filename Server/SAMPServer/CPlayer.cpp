#include "CPlayer.h"

CPlayer::CPlayer(CClientSocketInfo* socketInfo)
{
	m_pSockInfo = socketInfo;
	m_bInPauseMenu = false;
	m_ucMenuId = 42;
}

CPlayer::~CPlayer()
{
	delete m_pSockInfo;
}

CClientSocketInfo* CPlayer::GetConnectionInfo()
{
	return m_pSockInfo;
}

void CPlayer::SetInPauseMenu(bool bInPauseMenu)
{
	m_bInPauseMenu = bInPauseMenu;
}

bool CPlayer::IsInPauseMenu()
{
	return m_bInPauseMenu;
}

void CPlayer::SetCurrentMenuId(unsigned char ucMenuId)
{
	m_ucMenuId = ucMenuId;
}

unsigned char CPlayer::GetCurrentMenuId()
{
	return m_ucMenuId;
}