#pragma once

#include <stdafx.h>

class CJmpProxy
{
public:
	static void MenuAction1();
	static void MenuAction2();
	static void MenuAction3();
	static void MenuSwitch();
	static void WorldCreate();

	static DWORD MenuJumpBack1;
	static DWORD MenuJumpBack2;
	static DWORD MenuJumpBack3;
	static DWORD MenuSwitchJumpBack;
	static DWORD MenuSwitchEndJumpBack;
	static DWORD WorldCreateJumpBack;
};