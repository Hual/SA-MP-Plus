#include <SAMP+/client/CGraphics.h>

CPoint2D CGraphics::m_pResolution;
IDirect3D9* CGraphics::m_pDirect3D;
IDirect3DDevice9* CGraphics::m_pDevice;
bool CGraphics::m_bCursorEnabled;

Sprite* CGraphics::logo;

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


	CLog::Write("CGraphics::Initialize");

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	logo = new Sprite(width / 2, height / 2);

	CLog::Write("Width: %d Height: %d", width, height);

	if (!logo->Init(pDevice, 311, 152))
	{
		CLog::Write("Couldn't load the SA-MP+ logo");
	}
	else
	{
		//logo->Resize(311, 152);
		//logo->Rotate(50);
		CLog::Write("Loaded the SA-MP+ logo successfully");
	}

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
	CLog::Write("CGraphics::OnReset");
	if (logo)
		logo->OnLostDevice();
}

void CGraphics::PostDeviceReset()
{
	CLog::Write("CGraphics::PostDeviceReset");
	if (logo)
		logo->OnResetDevice();
}

void CGraphics::PreEndScene()
{
	
	if (!CGame::IsLoaded())
	{
		if (logo->isInitialized())
		{
			logo->Draw();
		}
	}
	else
	{
		if (logo)
		{
			delete logo;
			logo = NULL;
		}
	}

	

	/*if (CGame::Playing())
	{

	}*/
}

void CGraphics::BeginScene()
{

}

void CGraphics::CleanUp()
{
	CLog::Write("CGraphics::CleanUp");
	if (logo)
		delete logo;
}