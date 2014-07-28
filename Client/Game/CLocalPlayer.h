#pragma once

#include "main.h"
#include "../Shared/Game/Definitions.h"

class CLocalPlayer
{
public:
	enum ePlayerAction : unsigned char
	{
		ALL,
		SPRINT,
		ENTER_CAR,
		CROUCH,
		FIRE_WEAPON,
		UNKNOWN,
		SWITCH_WEAPON,
		JUMP,
		COUNT
	};

	static void SetActionEnabled(unsigned char action, bool bEnabled);
	static void OnDriveByShot();
	static void OnStuntBonus(sStuntDetails* pStuntDetails);
	static void SetClipAmmo(BYTE bSlot, int bAmmo);
	static void SetNoReload(bool toggle);
	static void ToggleInfiniteRun(bool toggle);

private:
	static DWORD m_actionMemory[ePlayerAction::COUNT-1];

};