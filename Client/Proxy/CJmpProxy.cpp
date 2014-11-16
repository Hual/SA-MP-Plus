#include <SAMP+/CRPC.h>
#include <SAMP+/client/CHooks.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/Network.h>
#include <SAMP+/client/CLocalPlayer.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>

DWORD CJmpProxy::MenuJumpBack1;
DWORD CJmpProxy::MenuJumpBack2;
DWORD CJmpProxy::MenuJumpBack3;
DWORD CJmpProxy::MenuSwitchJumpBack;
DWORD CJmpProxy::MenuSwitchEndJumpBack;
DWORD CJmpProxy::WorldCreateJumpBack;
//DWORD CJmpProxy::RaceCheckpointUnknownJumpBack;
DWORD CJmpProxy::PositiveMoneyDrawJumpBack;
//DWORD CJmpProxy::UnknownMoneyDraw1JumpBack;
DWORD CJmpProxy::NegativeMoneyDrawJumpBack;
DWORD CJmpProxy::ArmourBarDrawJumpBack;
DWORD CJmpProxy::HealthBarDrawJumpBack;
DWORD CJmpProxy::AmmoDrawJumpBack;
DWORD CJmpProxy::WantedLevelDrawJumpBack;
DWORD CJmpProxy::BreathBarDrawJumpBack;
DWORD CJmpProxy::InactiveRadioDrawJumpBack;
DWORD CJmpProxy::DriveByUnknownJumpBack;
DWORD CJmpProxy::StuntBonusJumpBack;
DWORD CJmpProxy::StuntInfoJumpBack;
DWORD CJmpProxy::ChangeResolutionJumpBack;
DWORD CJmpProxy::FreezePedJumpBack;
DWORD CJmpProxy::FreezeVehicleJumpBack;
DWORD CJmpProxy::PedAnimsJumpBack;
DWORD CJmpProxy::SwitchWeaponJumpBack;
DWORD CJmpProxy::AircraftMaxHeight1JumpBack;
DWORD CJmpProxy::AircraftMaxHeight2JumpBack;
DWORD CJmpProxy::MarkersHookJmpBack;
DWORD CJmpProxy::RadioHookJmpBack;
DWORD CJmpProxy::DrinkSprunkJmpBack;

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

sStuntDetails CJmpProxy::StuntDetails;

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

DWORD gtasa_markers_jmp_pointer = 0x584A79;
JMP_CAVE CJmpProxy::MarkersHook()
{
	__asm pushad

	if (CGame::VehicleBlips == false)
	{
		__asm
		{
			popad
				mov eax, [esp + 04h]
				cmp eax, 000003ECh
				je return_hook
				mov eax, gtasa_markers_jmp_pointer
				jmp dword ptr[eax]


			return_hook:
				mov eax, 0h
					ret
		}
	}
	else
	{
		__asm
		{
			popad
				mov eax, gtasa_markers_jmp_pointer
				jmp dword ptr[eax]
		}
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
	__asm
	{
		pushad
		call CGame::OnWorldCreate
		popad
		mov[eax], edx
		movzx eax, byte ptr[esi + 0x59]
		jmp[WorldCreateJumpBack]
	}
}

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

JMP_CAVE CJmpProxy::DriveByUnknown()
{
	__asm pushad;
	
	CLocalPlayer::OnDriveByShot();

	__asm
	{
		popad
		mov ecx, [esi + 0x480]
		jmp[DriveByUnknownJumpBack]
	}
}

JMP_CAVE CJmpProxy::StuntBonus()
{
	__asm
	{
		add dword ptr ds : [eax + 0xB8], edx		// inc money

		pushad

		lea eax, StuntDetails
		mov [eax].dwMoney, edx

		popad

		jmp[StuntBonusJumpBack]						// jmp to regular func
	}

}

JMP_CAVE CJmpProxy::StuntInfo()
{
	__asm
	{
		mov ecx, [esp + 0x14]
		mov[StuntDetails + 0x04] + 0x00, ecx
		mov edx, [esp + 0x10]
		mov[StuntDetails + 0x04] + 0x04, edx
		sub esp, 0x320
		push ebx
		mov ebx, [esp + 0x340]
		mov[StuntDetails + 0x04] + 0x08, ebx
		push ebp
		mov ebp, [esp + 0x340]
		mov[StuntDetails + 0x04] + 0x0C, ebp
		push esi
		mov esi, [esp + 0x350]
		mov[StuntDetails + 0x04] + 0x10, esi
		push edi
		mov edi, [esp + 0x350]
		mov[StuntDetails + 0x04] + 0x14, edi
		lea eax, [esp + 0x10]
		push eax
		mov eax, [esp + 0x338]
		pushad
		lea ebx, StuntDetails
		mov[ebx].ucType, al
	}

	if (StuntDetails.ucType != 55)
		CLocalPlayer::OnStuntBonus(&StuntDetails);
	
	__asm
	{
		popad
		jmp[StuntInfoJumpBack]
	}

}

JMP_CAVE CJmpProxy::ChangeResolution() 
{
	__asm
	{
		push ebx
		mov ebx, 0x0C9C040
		mov [ebx], ecx
		mov edx, [eax + 04]
		mov ebx, 0x0C9C044
		mov [ebx], edx
		pop ebx

		pushad
		push edx
		push ecx
		call CGame::OnResolutionChange
		popad

		jmp[ChangeResolutionJumpBack]
	}
}

JMP_CAVE CJmpProxy::FreezePed()
{
	__asm
	{
		call CGame::IsFrozen // modify eax, which is all we need to do
		jmp[FreezePedJumpBack]
	}
}

JMP_CAVE CJmpProxy::FreezeVehicle() // freeze vehicle that PED is driving
{
	__asm
	{
		call CGame::IsFrozen // modify eax, which is all we need to do
		jmp[FreezeVehicleJumpBack]
	}
}

JMP_CAVE CJmpProxy::PedAnims() 
{
	__asm
	{
		call CGame::UsePedAnims
		cmp eax,1
		jmp[PedAnimsJumpBack]
	}
}

JMP_CAVE CJmpProxy::AircraftMaxHeight1()
{
	__asm
	{
		fcomp dword ptr[CGame::AircraftMaxHeight]
			jmp[AircraftMaxHeight1JumpBack]
	}
}

JMP_CAVE CJmpProxy::AircraftMaxHeight2()
{
	__asm
	{
		fsub dword ptr[CGame::AircraftMaxHeight]
		jmp[AircraftMaxHeight2JumpBack]
	}
}

DWORD clipAmmo;
JMP_CAVE CJmpProxy::SwitchWeapon()
{
	__asm
	{
		cmp ecx, edx
		jnge DONE
		mov ecx, edx

		pushad
	}

	CGame::ClipAmmo[24] = 500;
	clipAmmo = CGame::ClipAmmo[*(int*)0x0BAA410];

	__asm
	{
		popad
		mov ecx, [clipAmmo]
		jmp DONE

	DONE:
		jmp[SwitchWeaponJumpBack]
	}

}

JMP_CAVE CJmpProxy::RadioHook()
{
	__asm
	{
		mov [esi + 0xAD], bl

		pushad

		push ebx

		call CGame::OnRadioChange
		popad

		jmp[RadioHookJmpBack]

	}
}

JMP_CAVE CJmpProxy::DrinkSprunkHook()
{
	__asm
	{
		fld dword ptr[esp + 18]

		call CGame::OnDrinkSprunk

		jmp[DrinkSprunkJmpBack]
	}
}