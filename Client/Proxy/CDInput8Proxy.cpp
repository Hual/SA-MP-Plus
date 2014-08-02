#include <SAMP+/client/Client.h>
#include <SAMP+/client/Proxy/CDInput8Proxy.h>
#include <SAMP+/client/Proxy/CDInput8DeviceProxy.h>

CDInput8Proxy::CDInput8Proxy(IDirectInput8A* device)
{
    pDevice = device;
}

CDInput8Proxy::~CDInput8Proxy() { }

HRESULT CDInput8Proxy::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    return pDevice->QueryInterface(riid, ppvObj);
}

ULONG CDInput8Proxy::AddRef(VOID)
{
    return pDevice->AddRef();
}

ULONG CDInput8Proxy::Release(VOID)
{
	ULONG ulRefCount = pDevice->Release();
    if (ulRefCount == 0)
		delete this;

	return ulRefCount;
}

HRESULT CDInput8Proxy::CreateDevice(REFGUID a, LPDIRECTINPUTDEVICE8A *b, LPUNKNOWN c)
{
    HRESULT hResult;
    hResult = pDevice->CreateDevice(a, b, c);
    if (hResult == DI_OK)
        *b = new CDInput8DeviceProxy(this, *b);

    return hResult;
}

HRESULT CDInput8Proxy::EnumDevices(DWORD a, LPDIENUMDEVICESCALLBACKA b, LPVOID c, DWORD d)
{
    HRESULT hRes = pDevice->EnumDevices(a, b, c, d);
	return hRes;
}

HRESULT CDInput8Proxy::GetDeviceStatus(REFGUID a)
{
    return pDevice->GetDeviceStatus(a);
}

HRESULT CDInput8Proxy::RunControlPanel(HWND a, DWORD b)
{
    return pDevice->RunControlPanel(a, b);
}

HRESULT CDInput8Proxy::Initialize(HINSTANCE a, DWORD b)
{
    return pDevice->Initialize(a, b);
}

HRESULT CDInput8Proxy::FindDevice(REFGUID a, LPCSTR b, LPGUID c)
{
    return pDevice->FindDevice(a, b, c);
}

HRESULT CDInput8Proxy::EnumDevicesBySemantics(LPCSTR a, LPDIACTIONFORMATA b, LPDIENUMDEVICESBYSEMANTICSCBA c, LPVOID d, DWORD e)
{
    return pDevice->EnumDevicesBySemantics(a, b, c, d, e);
}

HRESULT CDInput8Proxy::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a, LPDICONFIGUREDEVICESPARAMSA b, DWORD c, LPVOID d)
{
    return pDevice->ConfigureDevices(a, b, c, d);
}