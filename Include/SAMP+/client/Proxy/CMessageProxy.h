#pragma once

#include <Windows.h>

class CMessageProxy
{
public:
	static void Initialize(HWND hWindow);
	static void Uninitialize();

	static HWND GetWindowHandle();
	static WNDPROC GetOriginalProcedure();
	static BOOL OnSetCursorPos(int iX, int iY);

private:
	static LRESULT CALLBACK Process(HWND wnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	static HWND m_hWindowOrig;
	static WNDPROC m_wProcOrig;

};
