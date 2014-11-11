#include <SAMP+/svr/CPlayer.h>

CPlayer::CPlayer(CClientSocketInfo* socketInfo)
{
	m_pSockInfo = socketInfo;
	m_bInPauseMenu = false;
	m_ucMenuId = 42;
	m_fAircraftHeight = 800.0f;
	m_fJetpackHeight = 100.0f;
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

float CPlayer::GetAircraftHeight()
{
	return m_fAircraftHeight;
}

float CPlayer::GetJetpackHeight()
{
	return m_fJetpackHeight;
}

void CPlayer::SetAircraftHeight(float height)
{
	m_fAircraftHeight = height;
}

void CPlayer::SetJetpackHeight(float height)
{
	m_fJetpackHeight = height;
}

void CPlayer::SetCurrentMenuId(unsigned char ucMenuId)
{
	m_ucMenuId = ucMenuId;
}

void CPlayer::ToggleVehicleBlips(bool toggle)
{
	m_bVehicleBlips = toggle;
}

bool CPlayer::GetVehicleBlips()
{
	return m_bVehicleBlips;
}

unsigned char CPlayer::GetCurrentMenuId()
{
	return m_ucMenuId;
}