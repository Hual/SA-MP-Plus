#include <stdafx.h>
#include "CMessageProxy.h"
#include "../Game/CGame.h"
#include "../Game/CGraphics.h"

HWND CMessageProxy::m_hWindowOrig;
WNDPROC CMessageProxy::m_wProcOrig;

void CMessageProxy::Initialize(HWND hWindow)
{
	if (m_wProcOrig != NULL || m_hWindowOrig == hWindow)
		return;

	m_wProcOrig = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG)(UINT*)Process);
	m_hWindowOrig = hWindow;
}

HWND CMessageProxy::GetWindowHandle()
{
	return m_hWindowOrig;
}

void CMessageProxy::Uninitialize()
{
	if (m_hWindowOrig == NULL)
		return;

	SetWindowLong(m_hWindowOrig, GWL_WNDPROC, (LONG)(UINT*)m_wProcOrig);
}

WNDPROC CMessageProxy::GetOriginalProcedure()
{
	return m_wProcOrig;
}

//TODO: use Process for something useful
LRESULT CALLBACK CMessageProxy::Process(HWND wnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (!CGame::Playing())
		goto retnOriginal;

	UINT vKey = (UINT)wparam;

	switch (umsg)
	{
	case WM_MOUSEMOVE:
	{
		return 0;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if (vKey == VK_F2 && (GetKeyState(VK_SHIFT) & 0x8000))
		{
			CGraphics::ToggleCursor(!CGraphics::IsCursorEnabled());
			return 0;
		}
	}
	}

retnOriginal:
	return CallWindowProc(CMessageProxy::GetOriginalProcedure(), wnd, umsg, wparam, lparam);
}

BOOL CMessageProxy::OnSetCursorPos(int iX, int iY)
{
	return CGame::OnCursorMove(iX, iY);
}