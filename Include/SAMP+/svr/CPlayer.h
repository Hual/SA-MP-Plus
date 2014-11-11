#pragma once

#include <SAMP+/svr/CClientSocketInfo.h>

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
	int GetResolutionX();
	int GetResolutionY();
	void SetResolution(int X, int Y);
	float GetAircraftHeight();
	float GetJetpackHeight();
	void SetAircraftHeight(float height);
	void SetJetpackHeight(float height);
	void ToggleVehicleBlips(bool toggle);
	bool GetVehicleBlips();

private:
	CClientSocketInfo* m_pSockInfo;
	bool m_bInPauseMenu;
	unsigned char m_ucMenuId;
	int m_iResolutionX;
	int m_iResolutionY;
	float m_fAircraftHeight;
	float m_fJetpackHeight;
	bool m_bVehicleBlips;

};