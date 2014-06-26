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
DWORD CJmpProxy::RaceCheckpointUnknownJumpBack;
DWORD CJmpProxy::PositiveMoneyDrawJumpBack;
//DWORD CJmpProxy::UnknownMoneyDraw1JumpBack;
DWORD CJmpProxy::NegativeMoneyDrawJumpBack;
DWORD CJmpProxy::ArmourBarDrawJumpBack;
DWORD CJmpProxy::HealthBarDrawJumpBack;
DWORD CJmpProxy::AmmoDrawJumpBack;
DWORD CJmpProxy::WantedLevelDrawJumpBack;
DWORD CJmpProxy::BreathBarDrawJumpBack;
DWORD CJmpProxy::InactiveRadioDrawJumpBack;

/*BYTE CJmpProxy::RaceCheckpointByteRed = NULL;
BYTE CJmpProxy::RaceCheckpointByteGreen = NULL;
BYTE CJmpProxy::RaceCheckpointByteBlue = NULL;*/

BYTE bMenuID = NULL, bOldMenuID = 41;

DWORD FUNC_SetColour = 0x719430;

DWORD CJmpProxy::HUDColourList[] =
{
	0xFF2C6836,     // positive money
	//0xFF0000FF,   // unknown money
	0xFF1D19B4,     // negative money
	0xFFE1E1E1,     // armour bar
	0xFF1D19B4,     // health bar
	0xFFF1CBAC,     // breath bar
	0xFFF1CBAC,     // ammo
	0xFF106290,     // wanted level
	0xFF106290,     // tuned radio
	0xFF969696      // untuned radio
};

JMP_CAVE CJmpProxy::MenuAction1()
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

JMP_CAVE CJmpProxy::MenuAction2()
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

JMP_CAVE CJmpProxy::MenuAction3()
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

JMP_CAVE CJmpProxy::MenuSwitch()
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

JMP_CAVE CJmpProxy::WorldCreate()
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

/*JMP_CAVE CJmpProxy::RaceCheckpointUnknown()
{
	__asm
	{
		//mov	dl, RaceCheckpointByteRed
		mov[esi + 0x08], dl
		mov dl, [esp + 0x70]
		mov[esi + 0x2C], ecx
		mov cl, [esp + 0x6C]
		//mov al, RaceCheckpointByteGreen
		mov[esi + 0x09], al
		mov ax, [esp+0x7C]
		mov[esi+0x0B], dl
		//mov cl, RaceCheckpointByteBlue
		mov[esi+0x0A], cl
		jmp[RaceCheckpointUnknownJumpBack]
	}
}*/

JMP_CAVE CJmpProxy::PositiveMoneyDraw()
{
	__asm
	{
		mov edx, [HUDColourList]
		push edx
		call FUNC_SetColour
		jmp[PositiveMoneyDrawJumpBack]
	}
}

/*JMP_CAVE CJmpProxy::UnknownMoneyDraw1()
{
	__asm
	{
		mov eax, dwPositiveMoneyColour
		//mov edx, [dwTest + 0x04]
		push eax
		call FUNC_SetColour
		jmp[UnknownMoneyDraw1JumpBack]
	}
}*/

JMP_CAVE CJmpProxy::NegativeMoneyDraw()
{
	__asm
	{
		mov eax, [HUDColourList + 0x04]
		push eax
		call FUNC_SetColour
		jmp[NegativeMoneyDrawJumpBack]
	}
}

JMP_CAVE CJmpProxy::ArmourBarDraw()
{
	__asm
	{
		mov[esp+0x0C], edx
		mov eax, [HUDColourList + 0x08]
		jmp[ArmourBarDrawJumpBack]
	}
}


JMP_CAVE CJmpProxy::HealthBarDraw()
{
	__asm
	{
		mov eax, 0x859524
		fmul dword ptr[eax]
		mov eax, [HUDColourList + 0x0C]
		jmp[HealthBarDrawJumpBack]
	}
}

JMP_CAVE CJmpProxy::BreathBarDraw()
{
	__asm
	{
		mov edx, [HUDColourList + 0x10]
		push ecx
		push edx
		push 0x01
		jmp[BreathBarDrawJumpBack]
	}
}

JMP_CAVE CJmpProxy::AmmoDraw()
{
	__asm
	{
		mov ecx, [HUDColourList + 0x14]
		push ecx
		call FUNC_SetColour
		jmp[AmmoDrawJumpBack]
	}
}

JMP_CAVE CJmpProxy::WantedLevelDraw()
{
	__asm
	{
		mov eax, [HUDColourList + 0x18]
		push eax
		call FUNC_SetColour
		jmp[WantedLevelDrawJumpBack]
	}
}

JMP_CAVE CJmpProxy::ActiveRadioDraw()
{
	__asm
	{
		mov ecx, [HUDColourList + 0x1C]
		push ecx
		mov ecx, 0x4E9FBA
		jmp ecx
	}
}

JMP_CAVE CJmpProxy::InactiveRadioDraw()
{
	__asm
	{
		mov edx, 0x58FEA0
		call edx
		mov eax, [HUDColourList + 0x20]
		jmp[InactiveRadioDrawJumpBack]
	}
}
