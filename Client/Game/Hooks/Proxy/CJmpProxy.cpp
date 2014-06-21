#include "CJmpProxy.h"
#include "../../CGame.h"
#include "Network/Network.h"
#include "../Shared/Network/CRPC.h"

DWORD CJmpProxy::MenuJumpBack1;
DWORD CJmpProxy::MenuJumpBack2;
DWORD CJmpProxy::MenuJumpBack3;
DWORD CJmpProxy::MenuSwitchJumpBack;
DWORD CJmpProxy::MenuSwitchEndJumpBack;
DWORD CJmpProxy::WorldCreateJumpBack;

BYTE bMenuID = NULL, bOldMenuID = 41;

__declspec(naked) void CJmpProxy::MenuAction1()
{
	__asm
	{
		mov bMenuID, al
		pushad
	}

	if (bMenuID != 42)
		bOldMenuID = CGame::OnPauseMenuChange(bOldMenuID, bMenuID);

	__asm
	{
		popad
		mov[ESI + 0x15D], al
		jmp[MenuJumpBack1]
	}
}

__declspec(naked) void CJmpProxy::MenuAction2()
{
	__asm
	{
		mov bMenuID, al
		pushad
	}

	bOldMenuID = CGame::OnPauseMenuChange(bOldMenuID, bMenuID);

	__asm
	{
		popad
		mov[ESI + 0x15D], al
		jmp[MenuJumpBack2]
	}
}

__declspec(naked) void CJmpProxy::MenuAction3()
{
	__asm
	{
		mov bMenuID, al
		pushad
	}

	if (!(bMenuID == 41 && bOldMenuID == 41))
		bOldMenuID = CGame::OnPauseMenuChange(bOldMenuID, bMenuID);

	__asm
	{
		popad
		mov[ESI + 0x15D], al
		jmp[MenuJumpBack3]
	}
}

__declspec(naked) void CJmpProxy::MenuSwitch()
{

	__asm pushad

	MenuSwitchEndJumpBack = MenuSwitchJumpBack + 0xD;

	if (CGame::PauseMenuEnabled)
	{
		CGame::OnPauseMenuToggle(!CGame::InPauseMenu);
		// send menu info

		__asm
		{
			popad
			mov cl, [esi + 0x5C]
			mov al, [esi + 0x32]
			cmp cl, bl
			jmp[MenuSwitchJumpBack]
		}
	}
	else // optimise pause menu toggling
	{
		__asm
		{
			popad
			jmp[MenuSwitchEndJumpBack]
		}
	}
}

__declspec(naked) void CJmpProxy::WorldCreate()
{
	__asm pushad;

	CGame::OnWorldCreate();

	__asm
	{
		popad
		mov ecx, 0x76BC90
		jmp[WorldCreateJumpBack]
	}
}