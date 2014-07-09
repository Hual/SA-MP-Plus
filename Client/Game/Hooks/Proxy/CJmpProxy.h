#pragma once

#include <stdafx.h>
#include "../Shared/Game/Definitions.h"
#include "../Game/CLocalPlayer.h"

#define JMP_CAVE __declspec(naked) void

class CJmpProxy
{
public:
	static void MenuAction1();
	static void MenuAction2();
	static void MenuAction3();
	static void MenuSwitch();
	static void WorldCreate();
	//static void RaceCheckpointUnknown();
	static void PositiveMoneyDraw();
	//static void UnknownMoneyDraw1();
	static void NegativeMoneyDraw();
	static void ArmourBarDraw();
	static void HealthBarDraw();
	static void BreathBarDraw();
	static void AmmoDraw();
	static void WantedLevelDraw();
	static void ActiveRadioDraw();
	static void InactiveRadioDraw();
	static void DriveByUnknown();
	static void StuntBonus();
	static void StuntInfo();
	static void ChangeResolution();
	static void FreezePed();
	static void FreezeVehicle();
	static void PedAnims();
	static void SwitchWeapon();

	static void TestDraw();

	static DWORD MenuJumpBack1;
	static DWORD MenuJumpBack2;
	static DWORD MenuJumpBack3;
	static DWORD MenuSwitchJumpBack;
	static DWORD MenuSwitchEndJumpBack;
	static DWORD WorldCreateJumpBack;
	//static DWORD RaceCheckpointUnknownJumpBack;
	static DWORD PositiveMoneyDrawJumpBack;
	//static DWORD UnknownMoneyDraw1JumpBack;
	static DWORD NegativeMoneyDrawJumpBack;
	static DWORD ArmourBarDrawJumpBack;
	static DWORD HealthBarDrawJumpBack;
	static DWORD BreathBarDrawJumpBack;
	static DWORD AmmoDrawJumpBack;
	static DWORD WantedLevelDrawJumpBack;
	static DWORD InactiveRadioDrawJumpBack;
	static DWORD DriveByUnknownJumpBack;
	static DWORD StuntBonusJumpBack;
	static DWORD StuntInfoJumpBack;
	static DWORD ChangeResolutionJumpBack;
	static DWORD FreezePedJumpBack;
	static DWORD FreezeVehicleJumpBack;
	static DWORD PedAnimsJumpBack;
	static DWORD SwitchWeaponJumpBack;

	static DWORD HUDColourList[];
	static sStuntDetails StuntDetails;

	/*static BYTE RaceCheckpointByteRed;
	static BYTE RaceCheckpointByteGreen;
	static BYTE RaceCheckpointByteBlue;*/

};