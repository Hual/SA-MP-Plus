#include <SAMP+/client/CGraphics.h>

CPoint2D CGraphics::m_pResolution;
IDirect3D9* CGraphics::m_pDirect3D;
IDirect3DDevice9* CGraphics::m_pDevice;
bool CGraphics::m_bCursorEnabled;

VOID CGraphics::SetScreenResolution(UINT uiWidth, UINT uiHeight)
{
	m_pResolution.X() = uiWidth;
	m_pResolution.Y() = uiHeight;
}

CPoint2D& CGraphics::GetScreenResolution()
{
	return m_pResolution;
}

void CGraphics::Initialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	m_pDirect3D = pDirect3D;
	m_bCursorEnabled = false;
	UpdateScreenResolution();
}

void CGraphics::UpdateScreenResolution()
{
	D3DDISPLAYMODE dm;
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	SetScreenResolution(dm.Width, dm.Height);
}

HRESULT CGraphics::ToggleCursor(bool toggle)
{
	m_bCursorEnabled = toggle;
	return m_pDevice->ShowCursor(toggle);
}

bool CGraphics::IsCursorEnabled()
{
	return m_bCursorEnabled;
}

void CGraphics::OnReset()
{

}

void CGraphics::PreEndScene()
{
	/*if (CGame::Playing())
	{

	}*/
}