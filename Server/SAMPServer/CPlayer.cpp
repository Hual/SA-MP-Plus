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

int CPlayer::GetResolutionX()
{
	return m_iResolutionX;
}

int CPlayer::GetResolutionY()
{
	return m_iResolutionY;
}

void CPlayer::SetResolution(int X, int Y)
{
	m_iResolutionX = X;
	m_iResolutionY = Y;
}


void CPlayer::SetCurrentMenuId(unsigned char ucMenuId)
{
	m_ucMenuId = ucMenuId;
}

unsigned char CPlayer::GetCurrentMenuId()
{
	return m_ucMenuId;
}