#include <SAMP+/client/Client.h>
#include <SAMP+/client/Proxy/CD3D9Proxy.h>
#include <SAMP+/client/Proxy/CD3D9DeviceProxy.h>

CD3D9Proxy::CD3D9Proxy(IDirect3D9* pDirect3D)
{
	m_pDirect3D9 = pDirect3D;
}

CD3D9Proxy::~CD3D9Proxy() {}

HRESULT CD3D9Proxy::QueryInterface(const IID &riid, void **ppvObj)
{
   return m_pDirect3D9->QueryInterface(riid, ppvObj);
}

ULONG CD3D9Proxy::AddRef()
{
   return m_pDirect3D9->AddRef();
}

ULONG CD3D9Proxy::Release()
{
	ULONG count = m_pDirect3D9->Release();
	if(count == 0)
		delete this;

	return count;
}

HRESULT CD3D9Proxy::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return m_pDirect3D9->RegisterSoftwareDevice(pInitializeFunction);
}

UINT CD3D9Proxy::GetAdapterCount()
{
	return m_pDirect3D9->GetAdapterCount();
}

HRESULT CD3D9Proxy::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return m_pDirect3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT CD3D9Proxy::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pDirect3D9->GetAdapterModeCount(Adapter, Format);
}

HRESULT CD3D9Proxy::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return m_pDirect3D9->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT CD3D9Proxy::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pDirect3D9->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT CD3D9Proxy::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pDirect3D9->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT CD3D9Proxy::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT CD3D9Proxy::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
	return m_pDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT CD3D9Proxy::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT CD3D9Proxy::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pDirect3D9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT CD3D9Proxy::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return m_pDirect3D9->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR CD3D9Proxy::GetAdapterMonitor(UINT Adapter)
{
	return m_pDirect3D9->GetAdapterMonitor(Adapter);
}

HRESULT CD3D9Proxy::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
	IDirect3DDevice9* pDirect3DDevice9;
	HRESULT hRes = m_pDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &pDirect3DDevice9);
	*ppReturnedDeviceInterface = new CD3D9DeviceProxy(pDirect3DDevice9, this, pPresentationParameters);
	return hRes;
}
